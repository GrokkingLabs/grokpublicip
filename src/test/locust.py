# This Python file uses the following encoding: utf-8
from locust import HttpUser, between, task


class WebsiteUser(HttpUser):
    wait_time = between(1, 5)

    def on_start(self):
      pass

    @task
    def about(self):
        self.client.get(
            "/ip/myip")


if __name__ == "__main__":
    pass
