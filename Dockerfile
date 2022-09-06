FROM opencpu/ubuntu-20.04:v2.2.8-1

RUN R -e 'install.packages("renv")'
RUN apt-get update && apt-get install -y clang-10
RUN add-apt-repository --update -y ppa:ubuntu-toolchain-r/test
RUN apt-get update -y
RUN apt-get -y --fix-broken install gcc-11 g++-11

RUN mkdir ~/.R
RUN echo "CXX20=clang++-10" > ~/.R/Makevars

COPY . /tmp/iLincsCor

RUN R -e 'renv::install("/tmp/iLincsCor")'
RUN R -e 'renv::install("/tmp/iLincsCor/iLincsCorSrv")'
