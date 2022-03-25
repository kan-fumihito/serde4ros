FROM ubuntu:20.04

ADD Makefile /src
ADD *.cc /src
ADD ./include /src
ADD ./src /src

RUN cd /src && make all
