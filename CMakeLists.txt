cmake_minimum_required(VERSION 3.15)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)


# project
project(
    coman
    LANGUAGES CXX
    VERSION 0.0.1
    HOMEPAGE_URL https://github.com/pluveto/coman
    DESCRIPTION "Another command helper"
)
message(STATUS "> ${PROJECT_NAME} ${PROJECT_VERSION}")

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 871ed52d350214a034f6ef8a3b8f51c5ce1bd400) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)
FetchContent_MakeAvailable(spdlog)

add_executable(${PROJECT_NAME})

aux_source_directory(src PROJ_SOURCES)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PUBLIC ${PROJ_SOURCES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

set($ENV{ENV_PROJECT_NAME} ${PROJECT_NAME})