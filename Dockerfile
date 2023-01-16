# ##############################################################################
#
# Defines the base image to build the application

FROM registry.access.redhat.com/ubi9/ubi-init AS builder

RUN dnf install -y gcc-c++ cmake libpq-devel

# ##############################################################################
#
# Defines the base image to execute and ship the application

FROM registry.access.redhat.com/ubi9/ubi-minimal AS runner

RUN microdnf install -y libpq && \
    microdnf clean all

# ##############################################################################
#
# Defines the base image generate coverage
FROM builder AS coverage

ARG ENABLE_CODECOVERAGE
ARG SKIP_TEST

RUN if [ -z "$SKIP_TEST" ] && [ -n "$ENABLE_CODECOVERAGE" ]; then \
      curl -LJO https://github.com/linux-test-project/lcov/releases/download/v1.16/lcov-1.16-1.noarch.rpm && \
      dnf install -y lcov-1.16-1.noarch.rpm; \
    fi

# ##############################################################################
#
# Builds the application and tests if neccesary
FROM builder AS build

ARG ENABLE_CODECOVERAGE
ARG SKIP_TEST

COPY . /usr/src/openao

# Configure
RUN cd /usr/src/openao \
    && mkdir -p build \
    && cmake . -B build -DENABLE_CODECOVERAGE=$ENABLE_CODECOVERAGE

# Build static library
RUN cd /usr/src/openao \
    && cmake --build build --target openao

# Build executable
RUN cd /usr/src/openao \
    && cmake --build build --target openao_server

# Build tests if not explicitly disabled
RUN if [ -z "$SKIP_TEST" ]; then \
      cd /usr/src/openao && \
      cmake --build build --target openao_test; \
    fi

# ##############################################################################
#
# Executes tests in the same environment that will be shipped
FROM runner AS test

ARG ENABLE_CODECOVERAGE
ARG SKIP_TEST

COPY --from=build /usr/src/openao/ /usr/src/openao

# Execute tests if not explicitly disabled
RUN if [ -z "$SKIP_TEST" ]; then \
      cd /usr/src/openao && \
      ./build/test/openao_test; \
    fi

# ##############################################################################
#
# Process coverage data if neccesary
FROM coverage AS coverage

ARG ENABLE_CODECOVERAGE
ARG SKIP_TEST

COPY --from=test /usr/src/openao/ /usr/src/openao

# Process coverage if applies
RUN if [ -z "$SKIP_TEST" ] && [ -n "$ENABLE_CODECOVERAGE" ]; then \
      cd /usr/src/openao && \
      lcov --base-directory src/ --directory build/test --no-external -c -o coverage/coverage.info && \
      genhtml coverage/coverage.info -o coverage; \
    fi

# ##############################################################################
#
# Generates the final image
FROM runner

COPY --from=coverage /usr/src/openao/build/src/openao_server /usr/local/bin

ENTRYPOINT ["openao_server"]
