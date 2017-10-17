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
set(XWIDGETS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

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

# Compilation flags
# =================

include(CheckCXXCompilerFlag)

string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

OPTION(DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter -Wextra -Wreorder")
    if (DISABLE_ARCH_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=generic")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()

    CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)

    if (HAS_CPP11_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(FATAL_ERROR "Unsupported compiler -- xeux requires c++14 support!")
    endif()

    # Enable link time optimization and set the default symbol
    # visibility to hidden (very important to obtain small binaries)
    if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        # Check for Link Time Optimization support
        # (GCC/Clang)
        CHECK_CXX_COMPILER_FLAG("-flto" HAS_LTO_FLAG)
        if (HAS_LTO_FLAG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
        endif()

        # Intel equivalent to LTO is called IPO
        if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
            CHECK_CXX_COMPILER_FLAG("-ipo" HAS_IPO_FLAG)
            if (HAS_IPO_FLAG)
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ipo")
            endif()
        endif()
    endif()
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

if(MSVC)
    add_definitions(-DNOMINMAX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251 /wd4996")
    # Allows to compile in debug without requiring each dependencies to
    # be compiled in debug
    if(${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        set(CMAKE_CXX_FLAGS_DEBUG "/DNDEBUG /MD /Zi /Ob0 /Od /RTC1")
        message(STATUS "Overriding CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
    endif()
endif()

# Dependencies
# ============

find_package(xeus REQUIRED)
include_directories(${xeus_INCLUDE_DIRS})

find_package(xproperty REQUIRED)
include_directories(${xproperty_INCLUDE_DIRS})

find_package(xtl REQUIRED)
include_directories(${xtl_INCLUDE_DIRS})

set(XWIDGETS_DEPENDENCIES ${xeus_LIBRARY})

# Source files
# ============

include_directories(${XWIDGETS_INCLUDE_DIR}/xwidgets)

set(XWIDGETS_HEADERS
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xbox.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xboolean.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xbutton.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xcheckbox.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xcontroller.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xfactory.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xholder.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xhtml.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xlabel.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xlayout.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xlink.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xmaterialize.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xnumber.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xnumeral.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xobject.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xpassword.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xplay.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xprogress.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xslider.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xstring.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xstyle.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtext.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtextarea.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtogglebutton.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xtransport.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xvalid.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidget.hpp
    ${XWIDGETS_INCLUDE_DIR}/xwidgets/xwidgets_config.hpp
)

# # Output
# # ======
# 
# set(XWIDGETS_TARGET xwidgets)
# add_library(${XWIDGETS_TARGET} SHARED ${XWIDGETS_SOURCES} ${XWIDGETS_HEADERS})
# target_link_libraries(${XWIDGETS_TARGET} ${XWIDGETS_DEPENDENCIES})
# set_target_properties(${XWIDGETS_TARGET} PROPERTIES
#                       PUBLIC_HEADER "${XWIDGETS_HEADERS}"
#                       COMPILE_DEFINITIONS "XWIDGETS_EXPORTS"
#                       PREFIX ""
#                       OUTPUT_NAME "libxwidgets")
# 
# get_property(XWIDGETS_NAME TARGET ${XWIDGETS_TARGET} PROPERTY OUTPUT_NAME)
# if(MSVC)
#     set(XWIDGETS_LINK_FILE ${XWIDGETS_NAME}${CMAKE_LINK_LIBRARY_SUFFIX})
#     set(XWIDGETS_RUNTIME_FILE ${XWIDGETS_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})
# else()
#     set(XWIDGETS_LINK_FILE ${XWIDGETS_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})
#     set(XWIDGETS_RUNTIME_FILE ${XWIDGETS_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX})
# endif()

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

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(FILES ${XWIDGETS_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xwidgets)

install(TARGETS ${XWIDGETS_TARGET}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xwidgets)

set(XWIDGETS_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for xwidgetsConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR})
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${XWIDGETS_CMAKECONFIG_INSTALL_DIR})

