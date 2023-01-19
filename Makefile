.PHONY: build test

all: configure build test

configure:
	cmake -B build .

build:
	cmake --build build --target openao_login_server openao_game_server

test:
	cmake --build build --target openao_framework_test openao_login_test openao_game_test
	./build/test/framework/openao_framework_test
	./build/test/login/openao_login_test
	./build/test/game/openao_game_test
