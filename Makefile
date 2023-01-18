.PHONY: build coverage up down

up:
	docker-compose pull && \
	docker-compose up -d

up.database:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml up postgres -d

up.migration:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml down migration
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml up migration

up.seed:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml down seed
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml up seed

down:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml down

build:
	docker-compose -f docker-compose.build.yaml build

build.migration:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml build migration

build.seed:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml build migration

local:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml up -d

generate:
	docker-compose down
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml up postgres -d
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml build migration
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml up migration
	docker exec openao_postgres_1 pg_dump -U user -d openao -h localhost -p 5432 -s > database_dump.txt