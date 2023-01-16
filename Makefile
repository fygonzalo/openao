.PHONY: build coverage up down

build:
	docker build . -f Dockerfile -t localhost/openao_server:latest

coverage:
	mkdir -p coverage && \
	docker build . -f Dockerfile -v $$PWD/coverage:/usr/src/openao/coverage:Z --build-arg ENABLE_CODECOVERAGE=True

up:
	docker-compose up -d

down:
	docker-compose down

format:
	find src/ -regex '.*\.\(cpp\|h\|hpp\|cc\|cxx\)' -exec clang-format --style=file:.clang-format -i {} \;