############################################################################
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille and Loid Gouarin       #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.8)
project(xwidgets)

message(STATUS "Forcing tests build type to Release")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

set(XWIDGETS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XWIDGETS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configuration
# =============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(XWIDGETS_INSTALL_LIBRARY_DIR "\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"")

configure_file (
    "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config_cling.hpp.in"
    "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config_cling.hpp"
)

# Versionning
# ===========

file(STRINGS "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp" xwidgets_version_defines
     REGEX "#define XWIDGETS_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xwidgets_version_defines})
    if(ver MATCHES "#define XWIDGETS_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XWIDGETS_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XWIDGETS_VERSION
    ${XWIDGETS_VERSION_MAJOR}.${XWIDGETS_VERSION_MINOR}.${XWIDGETS_VERSION_PATCH})
message(STATUS "xwidgets version: v${XWIDGETS_VERSION}")

# Binary version
# See the following URL for explanations about the binary versionning
# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html#Updating-version-info
file(STRINGS "${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp" xwidgets_version_defines
    REGEX "#define XWIDGETS_BINARY_(CURRENT|REVISION|AGE)")
foreach(ver ${xwidgets_version_defines})
    if(ver MATCHES "#define XWIDGETS_BINARY_(CURRENT|REVISION|AGE) +([^ ]+)$")
        set(XWIDGETS_BINARY_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XWIDGETS_BINARY_VERSION
    ${XWIDGETS_BINARY_CURRENT}.${XWIDGETS_BINARY_REVISION}.${XWIDGETS_BINARY_AGE})
message(STATUS "xwidgets binary version: v${XWIDGETS_BINARY_VERSION}")

# Dependencies
# ============

find_package(cppzmq 4.3.0 REQUIRED)
find_package(xtl 0.4.8 REQUIRED)
find_package(xeus 0.14.1 REQUIRED)
find_package(xproperty 0.7 REQUIRED)

# Source files
# ============

set(XWIDGETS_HEADERS
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xaccordion.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xaudio.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xbinary.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xbox.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xboolean.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xbutton.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xcheckbox.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xcolor.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xcolor_picker.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xcontroller.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xdropdown.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xeither.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xfactory.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xholder.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xhtml.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/ximage.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xlabel.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xlayout.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xlink.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xmaterialize.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xmedia.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xmaker.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xnumber.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xnumeral.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xobject.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xpassword.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xplay.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xprogress.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xselect.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xselection.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xselection_container.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xselectionslider.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xslider.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xstring.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xstyle.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xradiobuttons.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtab.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtext.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtextarea.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtogglebutton.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtogglebuttons.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtransport.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xvalid.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xvideo.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidget.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config_cling.hpp
)

set(XWIDGETS_SOURCES
    ${XWIDGETS_SOURCE_DIR}/xaccordion.cpp
    ${XWIDGETS_SOURCE_DIR}/xaudio.cpp
    ${XWIDGETS_SOURCE_DIR}/xbox.cpp
    ${XWIDGETS_SOURCE_DIR}/xbutton.cpp
    ${XWIDGETS_SOURCE_DIR}/xcheckbox.cpp
    ${XWIDGETS_SOURCE_DIR}/xcolor_picker.cpp
    ${XWIDGETS_SOURCE_DIR}/xcontroller.cpp
    ${XWIDGETS_SOURCE_DIR}/xdropdown.cpp
    ${XWIDGETS_SOURCE_DIR}/xhtml.cpp
    ${XWIDGETS_SOURCE_DIR}/ximage.cpp
    ${XWIDGETS_SOURCE_DIR}/xlabel.cpp
    ${XWIDGETS_SOURCE_DIR}/xlayout.cpp
    ${XWIDGETS_SOURCE_DIR}/xlink.cpp
    ${XWIDGETS_SOURCE_DIR}/xnumeral.cpp
    ${XWIDGETS_SOURCE_DIR}/xpassword.cpp
    ${XWIDGETS_SOURCE_DIR}/xplay.cpp
    ${XWIDGETS_SOURCE_DIR}/xprogress.cpp
    ${XWIDGETS_SOURCE_DIR}/xselect.cpp
    ${XWIDGETS_SOURCE_DIR}/xslider.cpp
    ${XWIDGETS_SOURCE_DIR}/xselectionslider.cpp
    ${XWIDGETS_SOURCE_DIR}/xtab.cpp
    ${XWIDGETS_SOURCE_DIR}/xtext.cpp
    ${XWIDGETS_SOURCE_DIR}/xtextarea.cpp
    ${XWIDGETS_SOURCE_DIR}/xtogglebutton.cpp
    ${XWIDGETS_SOURCE_DIR}/xtogglebuttons.cpp
    ${XWIDGETS_SOURCE_DIR}/xradiobuttons.cpp
    ${XWIDGETS_SOURCE_DIR}/xvalid.cpp
    ${XWIDGETS_SOURCE_DIR}/xvideo.cpp
)

# Output
# ======

add_library(xwidgets SHARED ${XWIDGETS_SOURCES} ${XWIDGETS_HEADERS})
target_include_directories(xwidgets PUBLIC $<BUILD_INTERFACE:${XWIDGETS_INCLUDE_DIR}>
                                           $<INSTALL_INTERFACE:include>)

target_link_libraries(xwidgets
                      PUBLIC xtl
                      PUBLIC xeus)

set_target_properties(xwidgets PROPERTIES
                      PUBLIC_HEADER "${XWIDGETS_HEADERS}"
                      COMPILE_DEFINITIONS "XWIDGETS_EXPORTS"
                      PREFIX ""
                      VERSION ${XWIDGETS_BINARY_VERSION}
                      SOVERSION ${XWIDGETS_BINARY_CURRENT}
                      OUTPUT_NAME "libxwidgets")

# Compilation flags
# =================

include(CheckCXXCompilerFlag)
string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)
OPTION(DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)

set_target_properties(xwidgets PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED 14)

target_compile_features(xwidgets PRIVATE cxx_std_14)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(xwidgets PUBLIC -Wunused-parameter -Wextra -Wreorder)
    if (DISABLE_ARCH_NATIVE)
        target_compile_options(xwidgets PUBLIC -mtune=generic)
    else()
        target_compile_options(xwidgets PUBLIC -march=native)
    endif()

    # Enable link time optimization and set the default symbol
    # visibility to hidden (very important to obtain small binaries)
    if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        # Check for Link Time Optimization support
        # (GCC/Clang)
        CHECK_CXX_COMPILER_FLAG("-flto" HAS_LTO_FLAG)
        if (HAS_LTO_FLAG)
            target_compile_options(xwidgets PUBLIC -flto)
        endif()

        # Intel equivalent to LTO is called IPO
        if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
            CHECK_CXX_COMPILER_FLAG("-ipo" HAS_IPO_FLAG)
            if (HAS_IPO_FLAG)
                target_compile_options(xwidgets PUBLIC -ipo)
            endif()
        endif()
    endif()
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

if(MSVC)
    target_compile_definitions(xwidgets PUBLIC -DNOMINMAX)
    target_compile_options(xwidgets PUBLIC /DGUID_WINDOWS /MP /bigobj)
    target_compile_options(xwidgets PUBLIC /wd4251 /wd 4996)
    # Allows to compile in debug without requiring each dependencies to
    # be compiled in debug
    if(${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        set(CMAKE_CXX_FLAGS_DEBUG "/DNDEBUG /MD /Zi /Ob0 /Od /RTC1")
        message(STATUS "Overriding CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
    endif()
endif()

# Tests
# =====

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

set(XWIDGETS_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for xwidgetsConfig.cmake")

install(TARGETS xwidgets
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xwidgets)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR})
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${XWIDGETS_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
              DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR})
