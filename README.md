# example-postgresql [![Build Status](https://dev.azure.com/lganzzzo/lganzzzo/_apis/build/status/oatpp.example-postgresql?branchName=master)](https://dev.azure.com/lganzzzo/lganzzzo/_build/latest?definitionId=17&branchName=master)

Example of a production grade entity service storing information in PostgreSQL. With Swagger-UI and configuration profiles.  
*Libpq is used to communicate with PostgreSQL database.*  
*Dockerfile and docker-compose.yaml files included.*

See more:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)

## Overview

This project is using [oatpp](https://github.com/oatpp/oatpp) and [oatpp-swagger](https://github.com/oatpp/oatpp-swagger) modules.

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- src/
|    |
|    |- controller/                      // Folder containing Controller where all endpoints are declared
|    |- db/                              // Database class is here 
|    |- dto/                             // DTOs are declared here
|    |- ServiceComponent.hpp             // Service configuration (port, ObjectMapper, Database)
|    |- SwaggerComponent.hpp             // Configuration for swagger-ui
|    |- AppComponent.hpp                 // Service configuration is loaded here
|    |- App.cpp                          // main() is here
|    
|- test/                                 // test folder
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.
|- resources/config.json                 // configuration file with configuration profiles
|- Dockerfile                            // Dockerfile
|- docker-compose.yaml                   // Docker-compose with this service and postgresql
```

---

## Build and Run

### Using CMake

**Requires** 

- libpq installed. To install libpq:  
   - On Mac `$ brew install libpq`
   - On Alpine `$ apk add postgresql-dev`
   - On Ubuntu - goto [Install PostgreSQL Client From Sources](#install-postgresql-client-from-sources)
   
- `oatpp` and `oatpp-swagger` modules installed. You may run `utility/install-oatpp-modules.sh` 
script to install required oatpp modules.   

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./example-postgresql-exe  # - run application.
```

*PostgreSQL is expected running as for `dev` config profile*

### In Docker

#### Dockerfile

```
$ docker build -t example-postgresql .
$ docker run -p 8000:8000 -e CONFIG_PROFILE='dev' -t example-postgresql
```

#### docker-compose

```
$ docker-compose up
```

*docker-compose will run service with `local-docker` config profile*

### After run

Go to [http://localhost:8000/swagger/ui](http://localhost:8000/swagger/ui) to try endpoints.

## Install PostgreSQL Client From Sources

- Download sources from [https://www.postgresql.org/ftp/source/](https://www.postgresql.org/ftp/source/)
   ```
   $ wget https://ftp.postgresql.org/pub/source/v11.1/postgresql-11.1.tar.gz
   ```
   
- Untar
   ```
   $ tar -xvzf postgresql-11.1.tar.gz
   ```

- CD to postgresql-11.1, configure, make:
   ```
   $ cd postgresql-11.1
   $ ./configure
   $ make
   ```
- Install PostgreSQL client-only  
   *For this particular example we don't need full PostgreSQL installation.* 
   ```
   $ make -C src/include install 
   $ make -C src/interfaces install
   ```

For more information see [PostgreSQL installation guide](https://www.postgresql.org/docs/11/install-procedure.html#INSTALL)
