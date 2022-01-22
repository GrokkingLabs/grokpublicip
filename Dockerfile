FROM ubuntu:20.04

EXPOSE 8080
ADD build/rabri app
RUN /bin/sh -c 'touch /rabri'
ENTRYPOINT ["rabri"]
