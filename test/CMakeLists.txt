############################################################################
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille, and Loic Gouarin      #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.1)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    project(xwidgets-test)

    find_package(xwidgets REQUIRED CONFIG)
    find_package(xtl REQUIRED CONFIG)
    set(XWIDGETS_INCLUDE_DIR ${xwidgets_INCLUDE_DIRS})
endif ()

# Dependencies
# ============

find_package(doctest REQUIRED)
find_package(Threads)

# Source files
# ============

set(XWIDGETS_TESTS
    main.cpp
    test_xholder.cpp
    test_xwidgets.cpp
)

# Output
# ======

add_executable(test_xwidgets ${XWIDGETS_TESTS} ${XWIDGETS_HEADERS})

target_compile_features(test_xwidgets PRIVATE cxx_std_17)

target_link_libraries(test_xwidgets
                      PRIVATE xwidgets
                      PUBLIC  xtl
                      PRIVATE xeus
                      PRIVATE doctest::doctest
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(test_xwidgets PRIVATE XWIDGETS_INCLUDE_DIR)

add_test(NAME test_xwidgets
         COMMAND test_xwidgets)
