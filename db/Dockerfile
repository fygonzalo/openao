FROM liquibase/liquibase

ARG TYPE

COPY db/${TYPE} /liquibase/changelog

ENTRYPOINT ["/liquibase/docker-entrypoint.sh", "--changeLogFile=db.changelog-root.yaml", "update"]
