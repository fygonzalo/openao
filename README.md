### Requirements

* CMake:3.22
* GCC:11.3.1

### Build

```bash
mkdir build
cmake -B build
make --directory build
```
## Supported platforms
- Fedora 36

## Goals

- Build having the listed requirements with a single command
- Run a develop build with a single command
- Configuration as code
- Centralized management
- Easy to upgrade

## Contribute

- Add as much tests as possible. Networking is hard, async io is hard, serialization is hard, develop a game server is
  hard, writting tests is easy and helps to ensure that everything is working as expected.
- Database changelogs must not act on themselves when working on feature branches, this helps to keep it simple.