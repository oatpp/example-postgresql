cmake_minimum_required(VERSION 3.1)

set(project_name example-postgresql) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/App.cpp
        src/AppComponent.hpp
        src/ServiceComponent.hpp
        src/SwaggerComponent.hpp
        src/controller/UserController.cpp
        src/controller/UserController.hpp
        src/db/Database.cpp
        src/db/Database.hpp
        src/dto/ConfigDto.hpp
        src/dto/ErrorDto.hpp
        src/dto/UserDto.hpp
)

target_include_directories(${project_name}-lib PUBLIC src)

## link libs

find_package(oatpp          0.19.9 REQUIRED)
find_package(oatpp-swagger  0.19.9 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger
)

add_definitions(
        # Path to swagger-ui resources #
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        # Path to config file #
        -DCONFIG_PATH="${CMAKE_CURRENT_LIST_DIR}/resources/config.json"
)

#################################################################
## link postgresql client

include(FindPkgConfig)

set(ENV{PKG_CONFIG_PATH} "/usr/local/pgsql/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}") ## change this if needed

pkg_check_modules(PKG_PQ REQUIRED libpq)

message("PKG_PQ_INCLUDE_DIRS=${PKG_PQ_INCLUDE_DIRS}")
message("PKG_PQ_LIBRARY_DIRS=${PKG_PQ_LIBRARY_DIRS}")
message("PKG_PQ_LIBRARIES=${PKG_PQ_LIBRARIES}")

target_include_directories(${project_name}-lib
        PUBLIC ${PKG_PQ_INCLUDE_DIRS}
)

link_directories(
        ${PKG_PQ_LIBRARY_DIRS}
)

target_link_libraries(${project_name}-lib
        PUBLIC ${PKG_PQ_LIBRARIES}
)

#################################################################

## add executables

add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(project-tests ${project_name}-test)
