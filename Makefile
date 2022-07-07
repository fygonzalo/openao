all: stop start seed

stop:
	podman-compose -f ".docker/docker-compose.yaml" down

start:
	podman-compose -f ".docker/docker-compose.yaml" up -d
	until $$(psql -c "SELECT 1" postgresql://admin:admin@localhost:5432/openao 2&>/dev/null) ; do \
  		sleep 1 ; \
	done
	liquibase --headless=true --username=admin --password=admin --changelog-file="db/changelog/db.changelog-root.yaml" --url "jdbc:postgresql://localhost:5432/openao" update

seed:
	liquibase --headless=true --username=admin --password=admin --changelog-file="db/seed/db.changelog-seed.yaml" --url "jdbc:postgresql://localhost:5432/openao" update

clang-format:
	find src/ -regex '.*\.\(cpp\|h\|hpp\|cc\|cxx\)' -exec clang-format --style=file:.clang-format -i {} \;