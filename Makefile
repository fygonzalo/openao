.PHONY: build coverage up down

up:
	docker-compose pull && \
	docker-compose up -d

down:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml down

build:
	docker-compose -f docker-compose.build.yaml build

local:
	docker-compose -f docker-compose.yaml -f docker-compose.build.yaml up -d