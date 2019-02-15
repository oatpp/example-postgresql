# example-postgresql [![Build Status](https://dev.azure.com/lganzzzo/lganzzzo/_apis/build/status/oatpp.example-postgresql?branchName=master)](https://dev.azure.com/lganzzzo/lganzzzo/_build/latest?definitionId=17&branchName=master)

Example of a production grade entity service storing information in PostgreSQL. With Swagger-UI and configuration profiles. 
*Libpq is used to communicate with PostgreSQL database.*  
*Dockerfile and docker-compose.yaml files included.*

#### More about oat++:
- Website: [https://oatpp.io](https://oatpp.io)
- Docs: [https://oatpp.io/docs/start](https://oatpp.io/docs/start)
- Oat++ Repo: [https://github.com/oatpp/oatpp](https://github.com/oatpp/oatpp)

## Overview
This project is using `oatpp` and `oatpp-swagger` modules.

### Project layout

```

|- CMakeLists.txt               // project loader script. load and build dependencies 
|- main/                        // main project directory
|    |
|    |- CMakeLists.txt          // project's CMakeLists.txt
|    |- src/                    // source folder
|    |- test/                   // test folder
|    |- resources/
|         |
|         |- config.json        // configuration file with configuration profiles
|
|- Dockerfile                   // Dockerfile
|- docker-compose.yaml          // Docker-compose with this service and postgresql

```
```
- src/
    |
    |- controller/              // Folder containing Controller where all endpoints are declared
    |- db/                      // Database class is here 
    |- dto/                     // DTOs are declared here
    |- ServiceComponent.hpp     // Service configuration (port, ObjectMapper, Database)
    |- SwaggerComponent.hpp     // Configuration for swagger-ui
    |- AppComponent.hpp         // Service configuration is loaded here
    |- Logger.hpp               // Application Logger
    |- App.cpp                  // main() is here
    
```

---

### Build and Run

#### Using CMake

*Requires libpq installed*
Tip: To install libpq on Mac - `$ brew install libpq`. To install libpq on Linux-Alpine - `apk add postgresql-dev`

```
$ mkdir build && cd build
$ cmake ..
$ make run        ## Download, build, and install all dependencies. Run project
```

*PostgreSQL is expected running as for `dev` config profile*

#### In Docker

##### Dockerfile

```
$ docker build -t example-postgresql .
$ docker run -p 8000:8000 -e CONFIG_PROFILE='dev' -t example-postgresql
```

##### docker-compose

```
$ docker-compose up
```

*docker-compose will run service with `local-docker` config profile*

---

### After run

Go to [http://localhost:8000/swagger/ui](http://localhost:8000/swagger/ui) to try endpoints.

---

Enjoy
