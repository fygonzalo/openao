FROM registry.access.redhat.com/ubi9/ubi-minimal

# Install system tools
RUN microdnf install -y gcc-c++ cmake vi which less nano git gdb libpq libpq-devel yum-utils shadow-utils java tar

# Install liquibase to execute migrations
RUN mkdir -p /opt/liquibase && \
    curl -LJO https://github.com/liquibase/liquibase/releases/download/v4.19.0/liquibase-4.19.0.tar.gz && \
    tar xf liquibase-4.19.0.tar.gz --directory /opt/liquibase && \
    rm liquibase-4.19.0.tar.gz && \
    ln -s /opt/liquibase/liquibase /usr/bin/liquibase

# Download ddl2cpp
RUN microdnf install -y python-pyparsing && \
    curl -LJO --output-dir /usr/local/bin https://raw.githubusercontent.com/rbock/sqlpp11/5b0eee1c4c753129b36ed77156903993f695869b/scripts/ddl2cpp && \
    chmod +x /usr/local/bin/ddl2cpp

WORKDIR /usr/src/openao
