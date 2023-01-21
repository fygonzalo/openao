.PHONY: build test

CR ?= localhost

all: prerequisites configure build test package

prerequisites:
	docker build -f ./tools/builder/Dockerfile -t localhost/openao-builder:latest .
	docker build -f ./tools/runner/Dockerfile -t localhost/openao-runner:latest .

configure:
	docker run --rm -v $$(pwd):/usr/src/openao:Z localhost/openao-builder:latest cmake -B build .

build:
	docker run --rm -v $$(pwd):/usr/src/openao:Z localhost/openao-builder:latest \
	cmake --build build -j 4

test:
	docker run --rm -v $$(pwd)/build/test:/usr/src/openao:Z localhost/openao-runner:latest \
		bash -c "./framework/openao_framework_test && ./login/openao_login_test && ./game/openao_game_test"

package:
	docker build -f ./tools/packager/Dockerfile -t ${CR}/openao-server:latest .
	docker build -f ./tools/migrator/Dockerfile -t ${CR}/openao-migrator:latest .

publish:
	docker push ${CR}/openao-server:latest
	docker push ${CR}/openao-migrator:latest

local:
	@echo -e "\033[36mDeploying server using local images, this may take some time.\033[0m"
	@docker-compose -f docker-compose.yaml -f docker-compose.local.yaml up \
		-d --force-recreate --build --remove-orphans &> /dev/null
	@echo -e "\033[36mServer deployed successfully.\033[0m"

remote:
	@echo -e "\033[36mDeploying server using remote images, this may take some time.\033[0m"
	@docker-compose -f docker-compose.yaml up --pull --force-recreate &> /dev/null
	@echo -e "\033[36mServer deployed successfully.\033[0m"

down:
	@docker-compose -f docker-compose.yaml -f docker-compose.local.yaml down &> /dev/null
	@echo -e "\033[36mServer shutdown successfully.\033[0m"

database:
	@echo -e "\033[36mInitiating database\033[0m"
	@docker-compose -f docker-compose.yaml -f docker-compose.local.yaml up \
		-d --force-recreate --build --remove-orphans database changelog seed &> /dev/null
	@echo -e "\033[36mDatabase started successfully.\033[0m"

seed:
	@echo -e "\033[36mSeeding database\033[0m"
	@docker-compose -f docker-compose.yaml -f docker-compose.local.yaml up \
		--force-recreate --build --remove-orphans seed &> /dev/null
	@echo -e "\033[36mDatabase updated successfully\033[0m"

style:
	pre-commit run --hook-stage commit --all-files
