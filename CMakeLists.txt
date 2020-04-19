cmake_minimum_required(VERSION 3.10.2)

set(PROJ_NAME "httpHelloWorld")
set(EXECUTABLE_NAME "httpHelloWorld")

project(${PROJ_NAME})

set(CMAKE_CXX_STANDARD 14)

### ADD BOOST ###
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


add_executable(${EXECUTABLE_NAME} main.cpp hello_world_api.cpp hello_world_api.h)
target_link_libraries(${EXECUTABLE_NAME}
        PUBLIC
        pistache
        ${Boost_LIBRARIES}
        )
