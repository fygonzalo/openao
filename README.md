# openao

Implementation of a network server. This project is for educational purposes,
as a playground for development practices.

# Running the project locally

Download the repository.
Make sure you have docker and docker-compose installed. Then in the project folder execute the following commands:

- Run `docker-compose up -d` to start a server listening on port `30000`.
- Run `docker-compose down` to shutdown the server and clean up the dependencies.

_If on linux, can use the convenience shortcuts `make remote` and `make down`._

Additional details:

- The server starts with prepopulated data by default.
- Use the username `bugs` and password `bunny` to log in into the default account.
- There are more users, take a look at [db/seed/accounts](db/seed/account.csv). The password is the username of the account.

# Project goals
* Quick onboard (no need of special tools on the developers machine).
* Build with a single command.
* Launch a local environment with a single command.
* Utilize configuration as code.
* Rely on tests.
* Perform continuous delivery.

# Contribute

This is mean to be a community driven project, everyone is welcomed. If you want to report a problem or discuss an idea, create an issue. If you think something can be improved and know how, make a PR and we will get the best of it.

Working in a group is much more fun than doing it alone and helps to progress faster.

### Before starting
This is not mandatory but tt would be great if you install the commits hooks. These help to perform some checks and code
formatting before pushing the changes. You can install it executing in the project folder (requires python-pip):

```bash
pip install pre-commit
pre-commit install -t commit-msg -t pre-commit
```
_This only affects to this repository, wont mess with your other projects_.

### Commits
When making commits, write them like this:

```
type: short description, less than 50 chararcters

A brief resume of WHAT changed and WHY, even if it's something
minor or simple, there is always a reason and it makes easier
to understand the changes when coming from the future.

Try to wrap the lines at 72 characters, makes easier to read in the
console.
```

The type could be any of the following:
- **feat:** introduces a new feature. It doesn't need to be big or complete, but something that is worth telling out. You implemented an event, enhanced a handler, added missing functionalities. We should be able to pick all these commits and generate an exciting changelog.
- **fix:** patches a bug in the codebase. Like feat, these help to automatically gather a list of fixes and generate the changelog.
- **chore:** introduces something new but isn't a feature by itself nor a fix. Example, you develop a utility component that will be used in other parts of the project. This should also be used for changes that doesn't fit in any of the other types.
- **refactor:** rewrites the existing codebase without adding features or fixes.
- **test:** changes solely related to tests that don't include things from other types.
- **build:** modifies the build process, this would be related to Makefile, CMakeLists.txt, Dockerfiles, and similar.
- **ci:** changes to github actions.
- **docs:** changes the documentation.

This is based on the [conventional commits guide](https://www.conventionalcommits.org/en/v1.0.0/#summary).

### Test

Write tests for the changes you are pushing. If you are not sure how to do so, take a look at other tests in the `test` folder. Because of the nature of the project, it can be hard to debug an error, so having automated tests will alleviate this.

- If you are working on the serialization/deserialization of an event, then write a tests that checks the output with an expected result.
- If you are working on a controller, then test that given an state and a command, it generates the expected events.


# Setting up a development environment

Based on experience, having to configure a development environment can turn people around, even so to myself when going back to older projects. It's also a hassle when everyone has something installed on a different path, different version, etc. Then there is the problem that the developers have a totally different environment that the one used by the integration server

That's why the project relies solely on docker and docker-compose to build and run the application.
- The development/build environment is a docker container.
- The tests are run on a docker container. 
- The binaries are package into containers. 
- The project is run using docker-compose.

The best part of it is that the integration server shares the same environment. If it works on your machine, it will also work on the integration server.

## Linux users (+ WSL)

Clone the project and execute the command `make` to build.

The initial build will take some seconds, subsequent builds should be faster.

Other commands you may want to use:

- `make prerequisites`: builds the docker image used to actually build the application.
- `make configure`: generates cmake configuration.
- `make build`: builds the application.
- `make test`: builds and executes tests.
- `make package`: builds the ready to use, self contained, docker images to run the server. 
- `make publish`: publishes the images to the public registry. This is for the CD pipeline, you should not need to run locally.
- `make local`: runs the server with the local docker images.
- `make remote`: runs the server with the latest published images.
- `make style`: applies formatting and lint (requires pre-commit).

I recommend you to inspect the `Makefile` in the project root folder to understand what's going on.

_If on fedora, make an alias `docker=podman`, and `docker-compose=podman-compose` and you are good to go._

## Windows users

My recommendation is to configure the [Windows Subsystem for Linux](https://learn.microsoft.com/es-es/windows/wsl/install). It should have docker and docker-compose enabled. Then follow the steps for written above.

If you still want to use windows, make sure you have docker and docker-compose installed. That's all you need.

I haven't written a convenience script to execute all the operations like on linux. You will need to inspect the `Makefile` and execute those `docker build/run` manually. I guess it's possible to make a powershell script that replicates the `Makefile`, if you do so, add it to the project, so the next windows developer have it easy.

## Tips and tricks

Most IDEs now support using docker containers as development/build environment. I recommend you to configure it to get all the benefits of the IDE while still having the same environment as the integration server.

I advise against installing the dependencies and building directly on your host.

# Adding features

#TODO
