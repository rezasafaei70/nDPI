FROM ubuntu

RUN apt upgrade
RUN apt update
RUN #export HTTP_PROXY="127.0.0.1:20171" && export HTTPS_PROXY="127.0.0.1:20171" && apt install -y make
COPY . ./code
WORKDIR ./code
#RUN pip --timeout 1000000 install  -r socketndpi/requirements.txt

#RUN unset HTTP_PROXY && unset HTTPS_PROXY
RUN apt-get install -y build-essential git gettext flex bison libtool autoconf automake pkg-config libpcap-dev libjson-c-dev libnuma-dev libpcre2-dev libmaxminddb-dev librrd-dev
RUN ./autogen.sh
RUN ./configure
#RUN make





