# ##############################################################################
#
# Defines the base image to build the application

FROM registry.access.redhat.com/ubi9/ubi-init AS builder

RUN dnf install -y gcc-c++ cmake libpq libpq-devel

COPY . /usr/src/openao

WORKDIR /usr/src/openao

# Configure
RUN mkdir -p build && \
    cmake . -B build

RUN cmake --build build --target \
    openao_framework \
    openao_framework_test \
    openao_login \
    openao_login_test \
    openao_game \
    openao_game_test

