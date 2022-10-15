FROM registry.access.redhat.com/ubi9/ubi-minimal AS builder

RUN microdnf install -y gcc-c++ cmake libpq-devel \
    && microdnf clean all

COPY . /usr/src/openao

RUN cd /usr/src/openao \
    && cmake . \
    && cmake --build . --target openao_server

FROM registry.access.redhat.com/ubi9/ubi-minimal AS runner

RUN microdnf install -y libpq \
    && microdnf clean all

COPY --from=builder /usr/src/openao/src/openao_server /usr/local/bin

ENTRYPOINT ["openao_server"]
