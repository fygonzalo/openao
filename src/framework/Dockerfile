# ##############################################################################
#
# Defines the base image to build the application

FROM registry.access.redhat.com/ubi9/ubi-init AS builder

RUN dnf install -y gcc-c++ cmake libpq-devel

# ##############################################################################
#
# Builds the application and tests if neccesary

FROM builder AS build

COPY . /usr/src/openao

# Configure
RUN cd /usr/src/openao \
    && mkdir -p build \
    && cmake . -B build

# Build static library
RUN cd /usr/src/openao \
    && cmake --build build --target openao_framework

# Build tests if not explicitly disabled
RUN if [ -z "$SKIP_TEST" ]; then \
      cd /usr/src/openao && \
      cmake --build build --target openao_framework_test && \
      ./build/test/framework/openao_framework_test; \
    fi

ENTRYPOINT ["sh", "-c", "exit 0"]