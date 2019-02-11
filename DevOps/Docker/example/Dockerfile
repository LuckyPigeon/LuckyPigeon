# FROM ubuntu:18.04
FROM alpine

ADD . /

WORKDIR /cert-api/

RUN apk update && apk add nodejs npm git python make g++
RUN npm install && npm link ../cert-contract ../common

EXPOSE 3000

CMD npm start
