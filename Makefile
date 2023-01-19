.PHONY: build test

all: prerequisites configure build test package

SRCDIR = /usr/src/openao
OUTDIR = /usr/local/bin

prerequisites:
	docker build -f ./tools/builder/Dockerfile \
	-t localhost/openao-builder:latest .
	docker build -f ./tools/runner/Dockerfile \
    -t localhost/openao-runner:latest .

configure:
	docker run --rm -v $$(pwd):$(SRCDIR):Z \
	localhost/openao-builder:latest cmake -B build .

build:
	docker run --rm -v $$(pwd):$(SRCDIR):Z localhost/openao-builder:latest \
	cmake --build build --target openao_login_server openao_game_server

test:
	docker run --rm -v $$(pwd):$(SRCDIR):Z localhost/openao-builder:latest \
	cmake --build build --target openao_framework_test openao_login_test openao_game_test
	docker run --rm -v \
	$$(pwd)/build/test/framework/openao_framework_test:$(OUTDIR)/openao_framework_test:Z \
	localhost/openao-runner:latest openao_framework_test
	docker run --rm -v \
	$$(pwd)/build/test/login/openao_login_test:$(OUTDIR)/openao_login_test:Z \
	localhost/openao-runner:latest openao_login_test
	docker run --rm -v \
	$$(pwd)/build/test/game/openao_game_test:$(OUTDIR)/openao_game_test:Z \
	localhost/openao-runner:latest openao_game_test

package:
	docker build -f ./tools/packager/Dockerfile \
	-t localhost/openao-server:latest .
	docker build -f ./tools/migrator/Dockerfile \
	-t localhost/openao-migrator:latest .

publish:
	docker tag localhost/openao-server:latest \
	ghcr.io/fygonzalo/openao-server:latest
	docker tag localhost/openao-migrator:latest \
    ghcr.io/fygonzalo/openao-migrator:latest
	docker push ghcr.io/fygonzalo/openao-server:latest
	docker push ghcr.io/fygonzalo/openao-migrator:latest

local:
	docker-compose -f docker-compose.yaml -f docker-compose.local.yaml down
	docker-compose -f docker-compose.yaml -f docker-compose.local.yaml up --pull

remote:
	docker-compose -f docker-compose.yaml -f docker-compose.local.yaml down
	docker-compose -f docker-compose.yaml up --pull

down:
	docker-compose -f docker-compose.yaml -f docker-compose.local.yaml down