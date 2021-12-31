#include "main.hpp"
#include "utils/Constants.hpp"
#include "utils/Logger.hpp"
#include "utils/StringUtils.hpp"
#include <App.h>
//#include <json.hpp>
#include <iostream>
#include <thread>
#include <vector>

#define GROK_SERVER_MULTIPLE_THREAD 0

int main() {
  using namespace std;
  using namespace grok;
  using namespace uWS;
  INFO_LOG("{}", "Hello World!!!");
  //  using json = nlohmann::json;
  const auto concurrency =
      GROK_SERVER_MULTIPLE_THREAD ? thread::hardware_concurrency() : 1;
  vector<thread *> threads(concurrency);
  log.info("webApp hardware_concurrency: {}", concurrency);
  mutex stdoutMutex;
  const u_int64_t port = 8080;
  transform(
      threads.begin(), threads.end(), threads.begin(), [&](thread * /*t*/) {
        return new thread([&]() {
          auto app = App();
          // Health endpoint
          app.get("/health", [&](HttpResponse<false> *res, HttpRequest *req) {
            res->writeStatus(Constants::HTTP_OK);
            res->end(R"({"status": "UP"})");
          });
          // Get the public IP of the calling service
          app.get("/", [&](HttpResponse<false> *res, HttpRequest *req) {
            const auto url = req->getUrl();
            res->writeStatus(Constants::HTTP_OK);
            res->end(R"({"status": "ServerUp"})");
          });
          // Add listen port
          app.listen(port, [&](auto *listenSocket) {
            stdoutMutex.lock();
            if (listenSocket) {
              cout << "Thread: " << this_thread::get_id()
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
      //      const auto id = StringUtils::toString(t->get_id());
      cout << "Joining thread with id: " << t->get_id() << endl;
    }
  });
  return 0;
}
