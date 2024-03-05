# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB rnoh_mjrefresh_SRC CONFIGURE_DEPENDS *.cpp)
add_library(rnoh_mjrefresh SHARED ${rnoh_mjrefresh_SRC})
target_include_directories(rnoh_mjrefresh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rnoh_mjrefresh PUBLIC rnoh)
