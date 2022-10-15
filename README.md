This is a proof of concept network server.
This is an educational project on distributed systems.

## Goals

* Build with a single command
* Local environment runnable with single command
* Configuration as code

## Contribute

* Maintain project conventions

## Development

#### Requirements

The minimal requirement to build and run the project is `make` and `docker`.

#### Building the project

The simplest way to build the project is executing the command `make build`,
which generates a image tagged `localhost/openao:local`.

#### Spin up a local environment

The makefile includes a target `make up` that starts up a postgres container,
runs changelogs using liquibase, initializes the database with seed data, then
starts the openao container.

If only need the database, then run `make up.database`.

If want to re-run the database seed, then run `make up.database.seed`

To clean it up use `make down`.