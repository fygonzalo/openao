.PHONY: build

all: build up

build:
	docker build . -f Dockerfile -t openao:local

up:	down up.database up.openao

up.database:
	docker run \
		--label project=openao \
		-e POSTGRES_USER=admin \
		-e POSTGRES_PASSWORD=admin \
		-e POSTGRES_DB=openao \
		-e POSTGRES_HOST_AUTH_METHOD=trust \
		-p 5432:5432 \
		-d --rm \
		postgres

	docker run \
		--label project=openao \
		--network host \
		--restart on-failure \
		--rm postgres \
		pg_isready -d openao -h localhost

	docker run \
		--label project=openao \
		-v ./db/changelog/:/liquibase/changelog \
		--network host \
		--rm \
		liquibase/liquibase \
		--username=admin --password=admin \
		--url "jdbc:postgresql://localhost:5432/openao" \
		--changeLogFile=db.changelog-root.yaml \
		update

	make up.database.seed

up.database.seed:
	docker run \
		--label project=openao \
		-v ./db/seed/:/liquibase/changelog \
		--network host \
		--rm \
		liquibase/liquibase \
		--username=admin --password=admin \
		--url "jdbc:postgresql://localhost:5432/openao" \
		--changeLogFile=db.changelog-root.yaml \
		update

up.openao:
	docker run \
		--label project=openao \
		--network host \
		--rm -d \
		localhost/openao:local

down:
	docker stop --filter label=project=openao

format:
	find src/ -regex '.*\.\(cpp\|h\|hpp\|cc\|cxx\)' -exec clang-format --style=file:.clang-format -i {} \;