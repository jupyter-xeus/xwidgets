# ~~~
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille and Loid Gouarin
#
# Distributed under the terms of the BSD 3-Clause License.
#
# The full license is in the file LICENSE, distributed with this software.
# ~~~

cmake_minimum_required(VERSION 3.8)
project(xwidgets)

set(XWIDGETS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XWIDGETS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configuration
# =============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(XWIDGETS_INSTALL_LIBRARY_DIR "\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"")

configure_file(
    "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config_cling.hpp.in"
    "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config_cling.hpp"
)

# Versionning
# ===========

file(
    STRINGS "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp" xwidgets_version_defines
    REGEX "#define XWIDGETS_VERSION_(MAJOR|MINOR|PATCH)"
)
foreach(ver ${xwidgets_version_defines})
    if(ver MATCHES "#define XWIDGETS_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(
            XWIDGETS_VERSION_${CMAKE_MATCH_1}
            "${CMAKE_MATCH_2}"
            CACHE INTERNAL ""
        )
    endif()
endforeach()
set(XWIDGETS_VERSION ${XWIDGETS_VERSION_MAJOR}.${XWIDGETS_VERSION_MINOR}.${XWIDGETS_VERSION_PATCH})
message(STATUS "xwidgets version: v${XWIDGETS_VERSION}")

# Binary version See the following URL for explanations about the binary versionning
# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html#Updating-version-info
file(
    STRINGS "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp" xwidgets_version_defines
    REGEX "#define XWIDGETS_BINARY_(CURRENT|REVISION|AGE)"
)
foreach(ver ${xwidgets_version_defines})
    if(ver MATCHES "#define XWIDGETS_BINARY_(CURRENT|REVISION|AGE) +([^ ]+)$")
        set(
            XWIDGETS_BINARY_${CMAKE_MATCH_1}
            "${CMAKE_MATCH_2}"
            CACHE INTERNAL ""
        )
    endif()
endforeach()
set(XWIDGETS_BINARY_VERSION ${XWIDGETS_BINARY_CURRENT}.${XWIDGETS_BINARY_REVISION}.${XWIDGETS_BINARY_AGE})
message(STATUS "xwidgets binary version: v${XWIDGETS_BINARY_VERSION}")

# Build options
# =============

option(XWIDGETS_BUILD_SHARED_LIBS "Build xwidgets shared library." ON)
option(XWIDGETS_BUILD_STATIC_LIBS "Build xwidgets static library (default if BUILD_SHARED_LIBS is OFF)." ON)

# Dependencies
# ============

set(xtl_REQUIRED_VERSION 0.7.0)
set(xeus_REQUIRED_VERSION 5.0.0)
set(xproperty_REQUIRED_VERSION 0.11.0)

if(NOT TARGET xtl)
    find_package(xtl ${xtl_REQUIRED_VERSION} REQUIRED)
endif()

if(NOT TARGET xeus)
    find_package(xeus ${xeus_REQUIRED_VERSION} REQUIRED)
endif()

if(NOT TARGET xproperty)
    find_package(xproperty ${xproperty_REQUIRED_VERSION} REQUIRED)
endif()

# Source files
# ============

set(
    XWIDGETS_SOURCES
    ${XWIDGETS_SOURCE_DIR}/xaccordion.cpp
    ${XWIDGETS_SOURCE_DIR}/xaudio.cpp
    ${XWIDGETS_SOURCE_DIR}/xbinary.cpp
    ${XWIDGETS_SOURCE_DIR}/xbox.cpp
    ${XWIDGETS_SOURCE_DIR}/xbutton.cpp
    ${XWIDGETS_SOURCE_DIR}/xcheckbox.cpp
    ${XWIDGETS_SOURCE_DIR}/xcolor_picker.cpp
    ${XWIDGETS_SOURCE_DIR}/xcommon.cpp
    ${XWIDGETS_SOURCE_DIR}/xcontroller.cpp
    ${XWIDGETS_SOURCE_DIR}/xdropdown.cpp
    ${XWIDGETS_SOURCE_DIR}/xfactory.cpp
    ${XWIDGETS_SOURCE_DIR}/xholder.cpp
    ${XWIDGETS_SOURCE_DIR}/xholder_id.cpp
    ${XWIDGETS_SOURCE_DIR}/xhtml.cpp
    ${XWIDGETS_SOURCE_DIR}/ximage.cpp
    ${XWIDGETS_SOURCE_DIR}/xlabel.cpp
    ${XWIDGETS_SOURCE_DIR}/xlayout.cpp
    ${XWIDGETS_SOURCE_DIR}/xlink.cpp
    ${XWIDGETS_SOURCE_DIR}/xmedia.cpp
    ${XWIDGETS_SOURCE_DIR}/xnumber.cpp
    ${XWIDGETS_SOURCE_DIR}/xnumber_bounded.cpp
    ${XWIDGETS_SOURCE_DIR}/xmixin_description.cpp
    ${XWIDGETS_SOURCE_DIR}/xoutput.cpp
    ${XWIDGETS_SOURCE_DIR}/xpassword.cpp
    ${XWIDGETS_SOURCE_DIR}/xplay.cpp
    ${XWIDGETS_SOURCE_DIR}/xprogress.cpp
    ${XWIDGETS_SOURCE_DIR}/xradiobuttons.cpp
    ${XWIDGETS_SOURCE_DIR}/xregistry.cpp
    ${XWIDGETS_SOURCE_DIR}/xselect.cpp
    ${XWIDGETS_SOURCE_DIR}/xselectionslider.cpp
    ${XWIDGETS_SOURCE_DIR}/xslider.cpp
    ${XWIDGETS_SOURCE_DIR}/xtab.cpp
    ${XWIDGETS_SOURCE_DIR}/xtarget.cpp
    ${XWIDGETS_SOURCE_DIR}/xtarget.hpp
    ${XWIDGETS_SOURCE_DIR}/xtext.cpp
    ${XWIDGETS_SOURCE_DIR}/xtextarea.cpp
    ${XWIDGETS_SOURCE_DIR}/xtogglebutton.cpp
    ${XWIDGETS_SOURCE_DIR}/xtogglebuttons.cpp
    ${XWIDGETS_SOURCE_DIR}/xvalid.cpp
    ${XWIDGETS_SOURCE_DIR}/xvideo.cpp
)

# Targets and link
# ================

include(CheckCXXCompilerFlag)

macro(xwidgets_create_target target_name linkage output_name)
    string(TOUPPER "${linkage}" linkage_upper)

    if(NOT ${linkage_upper} MATCHES "^(SHARED|STATIC)$")
        message(FATAL_ERROR "Invalid library linkage: ${linkage}")
    endif()

    if(${linkage_upper} STREQUAL "STATIC")
        set(XEUS_TARGET_NAME xeus-static)
    else()
        set(XEUS_TARGET_NAME xeus)
    endif()

    # Output
    # ======

    add_library(${target_name} ${linkage_upper} ${XWIDGETS_SOURCES})
    target_include_directories(
        ${target_name} PUBLIC $<BUILD_INTERFACE:${XWIDGETS_INCLUDE_DIR}> $<INSTALL_INTERFACE:include>
    )

    target_link_libraries(${target_name} PUBLIC xtl ${XEUS_TARGET_NAME} xproperty)

    set_target_properties(
        ${target_name}
        PROPERTIES
            COMPILE_DEFINITIONS "XWIDGETS_EXPORTS"
            PREFIX ""
            VERSION ${XWIDGETS_BINARY_VERSION}
            SOVERSION ${XWIDGETS_BINARY_CURRENT}
            OUTPUT_NAME "lib${output_name}"
    )

    # Compilation flags
    # =================

    string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

    set_target_properties(${target_name} PROPERTIES CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED 17)

    target_compile_features(${target_name} PRIVATE cxx_std_17)

    if(
        CMAKE_CXX_COMPILER_ID MATCHES "Clang"
        OR CMAKE_CXX_COMPILER_ID MATCHES "GNU"
        OR CMAKE_CXX_COMPILER_ID MATCHES "Intel"
    )
        target_compile_options(${target_name} PUBLIC -Wunused-parameter -Wextra -Wreorder)

        message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    endif()

    if(${linkage_upper} STREQUAL "STATIC")
        target_compile_definitions(${target_name} PUBLIC XWIGDETS_STATIC_LIB)
    endif()

    if(MSVC)
        target_compile_definitions(${target_name} PUBLIC -DNOMINMAX)
        target_compile_options(${target_name} PUBLIC /DGUID_WINDOWS /MP /bigobj)
        target_compile_options(${target_name} PUBLIC /wd4251 /wd4996)
        # Allows to compile in debug without requiring each dependencies to be compiled in debug
        if(${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
            set(CMAKE_CXX_FLAGS_DEBUG "/DNDEBUG /MD /Zi /Ob0 /Od /RTC1")
            message(STATUS "Overriding CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
        endif()
    endif()
endmacro()

set(xwidgets_targets "")

if(XWIDGETS_BUILD_SHARED_LIBS)
    xwidgets_create_target(xwidgets SHARED xwidgets)
    list(APPEND xwidgets_targets xwidgets)
endif()

if(XWIDGETS_BUILD_STATIC_LIBS)
    # On Windows, a static library should use a different output name to avoid the conflict with the import
    # library of a shared one.
    if(CMAKE_HOST_WIN32)
        xwidgets_create_target(xwidgets-static STATIC xwidgets-static)
    else()
        xwidgets_create_target(xwidgets-static STATIC xwidgets)
    endif()

    list(APPEND xwidgets_targets xwidgets-static)
endif()

# Tests =====

option(XWIDGETS_BUILD_TESTS "xwidgets test suite" OFF)

include(CTest)

if(XWIDGETS_BUILD_TESTS)
    set(BUILD_TESTING ON)
    add_subdirectory(test)
endif()

# Installation
# ============

set(
    XWIDGETS_CMAKECONFIG_INSTALL_DIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
    CACHE STRING "install path for xwidgetsConfig.cmake"
)

install(
    TARGETS ${xwidgets_targets}
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install headers and generated headers
install(
    DIRECTORY "${XWIDGETS_INCLUDE_DIR}/xwidgets"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING
    PATTERN "*.hpp"
)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

# Configure 'xwidgetsConfig.cmake' for a build tree
set(XWIDGETS_CONFIG_CODE "####### Expanded from \@XWIDGETS_CONFIG_CODE\@ #######\n")
set(
    XWIDGETS_CONFIG_CODE
    "${XWIDGETS_CONFIG_CODE}set(CMAKE_MODULE_PATH \"${CMAKE_CURRENT_SOURCE_DIR}/cmake;\${CMAKE_MODULE_PATH}\")\n"
)
set(XWIDGETS_CONFIG_CODE "${XWIDGETS_CONFIG_CODE}##################################################")
configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${PROJECT_BINARY_DIR}
)

# Configure 'xwidgetsConfig.cmake' for an install tree
set(XWIDGETS_CONFIG_CODE "")
configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR}
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${XWIDGETS_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR}
)
install(
    EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR}
)
