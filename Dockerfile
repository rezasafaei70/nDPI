FROM python:3.8.2-slim-buster

RUN apt upgrade
RUN apt update
RUN apt-get install -y git
RUN git clone -b develop https://github.com/rezasafaei70/nDPI.git
RUN export HTTP_PROXY=http://127.0.0.1:20171 && export HTTPS_PROXY=http://127.0.0.1:20171
COPY . ./code
WORKDIR ./code
RUN pip --timeout 1000000 install  -r socketndpi/requirements.txt

#RUN unset HTTP_PROXY && unset HTTPS_PROXY
RUN apt-get install -y build-essential git gettext flex bison libtool autoconf automake pkg-config libpcap-dev libjson-c-dev libnuma-dev libpcre2-dev libmaxminddb-dev librrd-dev
RUN ./autogen.sh
RUN ./configure
RUN make
RUN unset HTTP_PROXY && \
    unset HTTPS_PROXY





