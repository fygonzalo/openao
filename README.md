This is a proof of concept game server.
There is currently no compatible client to play.
This is an educational project on distributed systems.

## Build

### Requirements

* CMake:3.22
* GCC:11.3.1

### Commands

```bash
mkdir build
cmake -B build
make --directory build
```

## Run

### Requirements

* Liquibase 4.12
* Postgresql

### Commands

```bash
make
```

To update the database data on the fly, run `make seed` from the root directory.

## Supported platforms

* Fedora 36

## Goals

* Build with a single command
* Run a develop build with a single command
* Configuration as code
* Centralized management
* Upgradable without downtime

## Contribute

* Include tests
* Database changelogs must not act on themselves when working on feature branches
* Maintain project conventions