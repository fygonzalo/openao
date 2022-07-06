all: stop start seed

stop:
	podman-compose -f ".docker/docker-compose.yaml" down

start:
	podman-compose -f ".docker/docker-compose.yaml" up -d
	sleep 10
	liquibase --headless=true --username=admin --password=admin --changelog-file="db/changelog/db.changelog-root.yaml" --url "jdbc:postgresql://localhost:5432/openao" update

seed:
	liquibase --headless=true --username=admin --password=admin --changelog-file="db/seed/db.changelog-seed.yaml" --url "jdbc:postgresql://localhost:5432/openao" update