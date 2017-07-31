############################################################################
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille and Loid Gouarin       #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.1)
project(xwidgets)

set(XWIDGETS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Versionning
# ===========

file(STRINGS "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp" xwidgets_version_defines
     REGEX "#define XWIDGETS_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xwidgets_version_defines})
    if(ver MATCHES "#define XWIDGETS_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XWIDGETS_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION 
    ${XWIDGETS_VERSION_MAJOR}.${XWIDGETS_VERSION_MINOR}.${XWIDGETS_VERSION_PATCH})
message(STATUS "xwidgets v${${PROJECT_NAME}_VERSION}")


# Build
# =====

find_package(xeus REQUIRED)
include_directories(${xeus_INCLUDE_DIRS})

find_package(xproperty REQUIRED)
include_directories(${xproperty_INCLUDE_DIRS})

set(XWIDGETS_HEADERS
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xobject.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidget.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xslider.hpp
)

OPTION(BUILD_TESTS "xwidgets test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

# Installation
# ============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(FILES ${XWIDGETS_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xwidgets)

set(XWIDGETS_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for xwidgetsConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR})

# xwidgets is header-only and does not depend on the architecture.
# Remove CMAKE_SIZEOF_VOID_P from xwidgetsConfigVersion.cmake so that an xwidgetsConfig.cmake
# generated for a 64 bit target can be used for 32 bit targets and vice versa.
set(_XWIDGETS_CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
unset(CMAKE_SIZEOF_VOID_P)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
set(CMAKE_SIZEOF_VOID_P ${_XWIDGETS_CMAKE_SIZEOF_VOID_P})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR})
