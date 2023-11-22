cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Canerator)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.cpp
)

include(cmake/CPM.cmake)
set(MESSAGE_QUIET ON)
CPMAddPackage("gh:JamesBoer/ImFrame#5e9fb2ceb6d2bf170e7937ec908b90350cf52569")
unset(MESSAGE_QUIET)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/luacpp)

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PRIVATE ImFrame luacpp)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
