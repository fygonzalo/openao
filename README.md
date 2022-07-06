### Requirements
* CMake:3.22
* GCC:11.3.1

### Build
```bash
mkdir build
cmake -B build
make --directory build
```

### Database
```
podman run --name postgresql/openao -e POSTGRES_PASSWORD=password -d postgres
```
                  CORE
            -----------------
CLIENT <-->| AUTH <--> SVC  |<--> WEB
           |    INTEREST    |
           ------------------