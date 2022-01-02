#include <iostream>
#include <thread>
#include <vector>
#include "main.hpp"
#include "utils/Constants.hpp"
#include "utils/Logger.hpp"
#include "utils/StringUtils.hpp"
#include "models/UpStatus.hpp"
#include "models/IPFormat.hpp"
#include <App.h>
#include <argh.h>
#include <fmt/core.h>

int main(int argc, char **argv) {
  using namespace std;
  using namespace grok;
  using namespace uWS;
  using namespace argh;
  parser cmdl(argv);
  glog.info("{}", "Hello World - 1 !!!");
  //  using json = nlohmann::json;
  u_int64_t port = 8080;
  cmdl("port", 8080) >> port;
  bool useMultiplethreads = false;
  cmdl("threaded", false) >> useMultiplethreads;
  const auto concurrency =
      useMultiplethreads ? thread::hardware_concurrency() : 1;
  vector<thread *> threads(concurrency);
  glog.info("webApp hardware_concurrency: {}", concurrency);
  mutex stdoutMutex;
  transform(
      threads.begin(), threads.end(), threads.begin(), [&](thread * /*t*/) {
        return new thread([&]() {
          auto app = App();
          // Health endpoint
          /// @fn health
          /// @brief Get the health status of the application
          app.get("/health", [&](HttpResponse<false> *res, HttpRequest *req) {
            res->writeStatus(Constants::HTTP_OK);
            static UpStatus status;
            res->end(StringUtils::objToJsonString(status));
          });

          /// @fn /
          /// @brief Get the public IP of the calling service
          /// @details Returns the IP of the caller. This is done by
          /// X-Forwarded-For For more details see below links
          /// @link https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Forwarded-For
          /// @link https://en.wikipedia.org/wiki/X-Forwarded-For
          app.get("/", [&](HttpResponse<false> *res, HttpRequest *req) {
            const auto xForwardFor = req->getHeader(Constants::X_FORWARDED_FOR);
            string forwardedIp = Constants::NA;
            if (!xForwardFor.empty()) {
              const auto split_ips = StringUtils::splitStringView(xForwardFor, Constants::X_FORWARDED_FOR_IP_SEPARATOR);
              if(!split_ips.empty()) {
                forwardedIp = split_ips.at(0);
              }
            }
            const auto format = req->getQuery(Constants::FORMAT);
            if(format == Constants::JSON_FORMAT) {
              const IPFormat ip(forwardedIp);
              forwardedIp = StringUtils::objToJsonString(ip);
              res->writeHeader(Constants::CONTENT_TYPE, Constants::CONTENT_TYPE_JSON);
            } else {
              res->writeHeader(Constants::CONTENT_TYPE, Constants::CONTENT_TYPE_TEXT);
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
