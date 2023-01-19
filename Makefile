.PHONY: build test

all: prerequisites configure build test package

prerequisites:
	docker build -f ./tools/builder/Dockerfile \
	-t localhost/openao-builder:latest .
	docker build -f ./tools/runner/Dockerfile \
    -t localhost/openao-runner:latest .

configure:
	docker run -v $$(pwd):/usr/src/openao:Z \
	localhost/openao-builder:latest cmake -B build .

build:
	docker run -v $$(pwd):/usr/src/openao:Z localhost/openao-builder:latest cmake \
	--build build --target openao_login_server openao_game_server

test:
	docker run -v $$(pwd):/usr/src/openao:Z localhost/openao-builder:latest cmake \
	--build build --target openao_framework_test openao_login_test openao_game_test
	docker run -v $$(pwd)/build/test/framework/openao_framework_test:/usr/local/bin/openao_framework_test:Z \
	localhost/openao-runner:latest openao_framework_test
	docker run -v $$(pwd)/build/test/login/openao_login_test:/usr/local/bin/openao_login_test:Z \
	localhost/openao-runner:latest openao_login_test
	docker run -v $$(pwd)/build/test/game/openao_game_test:/usr/local/bin/openao_game_test:Z \
	localhost/openao-runner:latest openao_game_test

package:
	docker build -f ./tools/packager/Dockerfile \
	-t localhost/openao-server:latest .

publish:
	docker tag localhost/openao-server:latest \
	ghcr.io/fygonzalo/openao-server:latest
	docker push ghcr.io/fygonzalo/openao-server:latest