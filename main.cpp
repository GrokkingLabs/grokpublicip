#include "main.hpp"
#include "models/IPFormat.hpp"
#include "models/UpStatus.hpp"
#include "utils/Constants.hpp"
#include "utils/Logger.hpp"
#include "utils/StringUtils.hpp"
#ifdef ENABLE_EASY_PROFILER
//#include <easy/profiler.h>
#endif
#include <App.h>
#include <argh.h>
#include <fmt/core.h>
#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char **argv) {
  using namespace std;
  using namespace grok;
  using namespace uWS;
  using namespace argh;
#ifdef ENABLE_EASY_PROFILER
  EASY_PROFILER_ENABLE;
  profiler::startListen();
  profiler::dumpBlocksToFile("test_profile.prof");
#endif
  parser cmdl(argv);
  glog.info("Starting the application");
  u_int64_t port = 8080;
  cmdl("port", 8080) >> port;
  bool useMultiplethreads = false;
  cmdl("threaded", false) >> useMultiplethreads;
  const auto hardwareConcurrency = thread::hardware_concurrency();
  const auto concurrency = useMultiplethreads
                               ? hardwareConcurrency
                               : Constants::DEFAULT_NUMBER_OF_THREADS;
  glog.info(
      "Command line parameters: port={}, threaded={}/{}. Default threads={}",
      port, useMultiplethreads, hardwareConcurrency,
      Constants::DEFAULT_NUMBER_OF_THREADS);
  vector<thread *> threads(concurrency);

  mutex stdoutMutex;
  transform(
      threads.begin(), threads.end(), threads.begin(), [&](thread * /*t*/) {
        return new thread([&]() {
          auto app = App();

          /// @fn health
          /// @brief Get the health status of the application
          app.get("/health", [&](HttpResponse<false> *res, HttpRequest *req) {
            static UpStatus status;
            res->writeStatus(Constants::HTTP_OK);
            res->end(StringUtils::objToJsonString(status));
          });

          /// @fn /
          /// @brief Get the public IP of the calling service
          /// @details Returns the IP of the caller. This is done by
          /// X-Forwarded-For For more details see below links
          /// @link
          /// https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Forwarded-For
          /// @link https://en.wikipedia.org/wiki/X-Forwarded-For
          app.get("/", [&](HttpResponse<false> *res, HttpRequest *req) {
            // Fetch the X_Forwarded_For header
            const auto xForwardFor = req->getHeader(Constants::X_FORWARDED_FOR);
            string forwardedIp = Constants::NA;
            if (!xForwardFor.empty()) {
              // The first IP is the original IP. So split the header string
              const auto split_ips = StringUtils::splitStringView(
                  xForwardFor, Constants::X_FORWARDED_FOR_IP_SEPARATOR);
              if (!split_ips.empty()) {
                // get the first vector element
                forwardedIp = split_ips.at(0);
              } else {
                glog.warn("X_FORWARDED_FOR={} is not proper", xForwardFor);
              }
            } else {
              glog.warn("Could not find X_FORWARDED_FOR header");
            }
            // If format is mentioned as json then create the json object
            const auto format = req->getQuery(Constants::FORMAT);
            if (format == Constants::JSON_FORMAT) {
              const IPFormat ip(forwardedIp);
              forwardedIp = StringUtils::objToJsonString(ip);
              res->writeHeader(Constants::CONTENT_TYPE,
                               Constants::CONTENT_TYPE_JSON);
            } else {
              res->writeHeader(Constants::CONTENT_TYPE,
                               Constants::CONTENT_TYPE_TEXT);
            }

            res->writeStatus(Constants::HTTP_OK);
            res->end(forwardedIp);
          });
          // Add listen port
          app.listen(port, [&](auto *listenSocket) {
            stdoutMutex.lock();
            if (listenSocket) {
              cout << "Thread Id: " << this_thread::get_id()
                   << " listening on port: " << port << endl;
            }
            stdoutMutex.unlock();
          });
          // Run the application
          app.run();
        });
      });
  // Join the threads
  for_each(threads.begin(), threads.end(), [](thread *t) {
    if (t->joinable()) {
      t->join();
      cout << "Joining Thread Id: " << t->get_id() << endl;
    }
  });
  return 0;
}
