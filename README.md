# OpenAO

Implementation of a network server. This project is for educational purposes,
as a playground for development practices.

## Goals

* Build with a single command.
* Local environment runnable with single command.
* Configuration as code.

## Contribute

* Maintain project conventions.
* Follow [conventional commits guide](https://www.conventionalcommits.org/en/v1.0.0/#summary).
* Follow [github flow](https://docs.github.com/en/get-started/quickstart/github-flow#following-github-flow).

## Development

#### Requirements

The minimal requirement to build and run the project is `make` and `docker`.

#### Build the project

The simplest way to build the project is executing the command `make build`,
which generates a image tagged `localhost/openao:local`.

#### Spin up a local environment

The makefile includes a target `make up` that starts up a postgres container,
runs changelogs using liquibase, initializes the database with seed data, then
starts the openao container.

If only need the database, then run `make up.database`.

If want to re-run the database seed, then run `make up.database.seed`.

To clean it up use `make down`.