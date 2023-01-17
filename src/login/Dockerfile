# ##############################################################################
#
# Defines the base image to build the application

FROM localhost/openao_framework:latest AS build

# Build static library
RUN cd /usr/src/openao \
    && cmake --build build --target openao_login_server

# Build tests if not explicitly disabled
RUN if [ -z "$SKIP_TEST" ]; then \
      cd /usr/src/openao && \
      cmake --build build --target openao_login_test && \
      ./build/test/login/openao_login_test; \
    fi

# ##############################################################################
#
# Defines the base image to run the application

FROM registry.access.redhat.com/ubi9/ubi-minimal AS runner

RUN microdnf install -y libpq && microdnf clean all

COPY --from=build /usr/src/openao/build/src/login/openao_login_server /usr/local/bin/openao_login_server

ENTRYPOINT [ "./usr/local/bin/openao_login_server" ]