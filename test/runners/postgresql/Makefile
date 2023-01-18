test:
	docker-compose up -d postgres
	docker-compose up migration
	docker-compose up test
	docker-compose down
