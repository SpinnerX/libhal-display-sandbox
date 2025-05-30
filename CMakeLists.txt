# Copyright 2024 Khalil Estell
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.25)

project(app.elf LANGUAGES CXX)

# Always check that the $ENV{LIBHAL_PLATFORM_LIBRARY} & $ENV{LIBHAL_PLATFORM}
# environment variables are set by the profile.
if("$ENV{LIBHAL_PLATFORM_LIBRARY}" STREQUAL "")
    message(FATAL_ERROR
        "Build environment variable LIBHAL_PLATFORM_LIBRARY is required for " "this project.")
endif()
if("$ENV{LIBHAL_PLATFORM}" STREQUAL "")
    message(FATAL_ERROR
        "Build environment variable LIBHAL_PLATFORM is required for "
        "this project.")
endif()

find_package(libhal-$ENV{LIBHAL_PLATFORM_LIBRARY} REQUIRED CONFIG)
find_package(libhal-util REQUIRED CONFIG)

add_executable(${PROJECT_NAME}
    src/display_application.cpp
    src/main.cpp
    platforms/$ENV{LIBHAL_PLATFORM}.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall -Wextra --save-temps)
target_include_directories(${PROJECT_NAME} PUBLIC include .)
target_link_libraries(${PROJECT_NAME} PRIVATE
    libhal::$ENV{LIBHAL_PLATFORM_LIBRARY}
    libhal::util)

libhal_post_build(${PROJECT_NAME})
libhal_disassemble(${PROJECT_NAME})
