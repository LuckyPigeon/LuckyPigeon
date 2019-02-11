FROM ubuntu:18.04

ADD . /

WORKDIR /cert-api/

RUN apt update && apt install nodejs npm git
RUN npm install && npm link ../cert-contract ../common

EXPOSE 3000

CMD npm start
