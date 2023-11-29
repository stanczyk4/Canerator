cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Canerator)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.cpp

    src/lvgl_demo/assets/img_clothes.c
    src/lvgl_demo/assets/img_demo_widgets_avatar.c
    src/lvgl_demo/assets/img_lvgl_logo.c
    src/lvgl_demo/lv_demo_widgets.c
)

include(cmake/CPM.cmake)
set(MESSAGE_QUIET ON)

CPMAddPackage("gh:JamesBoer/ImFrame#5e9fb2ceb6d2bf170e7937ec908b90350cf52569")

set(LV_CONF_PATH ${CMAKE_CURRENT_LIST_DIR}/src/lv_conf.h CACHE STRING "" FORCE)
CPMAddPackage("gh:lvgl/lvgl#v8.3.10")

unset(MESSAGE_QUIET)

# https://github.com/jordanvrtanoski/luacpp
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/luacpp)

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ImFrame
    luacpp
    lvgl::lvgl
)

if(MSVC)
    # target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
