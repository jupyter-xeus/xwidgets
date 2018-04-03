/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_CONFIG_HPP
#define XWIDGETS_CONFIG_HPP

// Visual C++ declspec macors
#ifdef _WIN32
    #ifdef XWIDGETS_EXPORTS
        #define XWIDGETS_API __declspec(dllexport)
    #else
        #define XWIDGETS_API __declspec(dllimport)
    #endif
#else
    #define XWIDGETS_API
#endif

// Project version
#define XWIDGETS_VERSION_MAJOR 0
#define XWIDGETS_VERSION_MINOR 8
#define XWIDGETS_VERSION_PATCH 2

// Binary version
#define XWIDGETS_BINARY_CURRENT 1
#define XWIDGETS_BINARY_REVISION 0
#define XWIDGETS_BINARY_AGE 1

// Protocol version
#define XWIDGETS_PROTOCOL_VERSION_MAJOR 2
#define XWIDGETS_PROTOCOL_VERSION_MINOR 0
#define XWIDGETS_PROTOCOL_VERSION_PATCH 0

// Semver requirement for @jupyter-widgets/base
#define XWIDGETS_BASE_VERSION_MAJOR 1
#define XWIDGETS_BASE_VERSION_MINOR 0
#define XWIDGETS_BASE_VERSION_PATCH 0

// Semver requirement for @jupyter-widgets/output
#define XWIDGETS_OUTPUT_VERSION_MAJOR 1
#define XWIDGETS_OUTPUT_VERSION_MINOR 0
#define XWIDGETS_OUTPUT_VERSION_PATCH 0

// Semver requirement for @jupyter-widgets/controls
#define XWIDGETS_CONTROLS_VERSION_MAJOR 1
#define XWIDGETS_CONTROLS_VERSION_MINOR 1
#define XWIDGETS_CONTROLS_VERSION_PATCH 0

// Composing the protocol version string from major, minor and patch
#define XWIDGETS_CONCATENATE(A, B) XWIDGETS_CONCATENATE_IMPL(A, B)
#define XWIDGETS_CONCATENATE_IMPL(A, B) A##B
#define XWIDGETS_STRINGIFY(a) XWIDGETS_STRINGIFY_IMPL(a)
#define XWIDGETS_STRINGIFY_IMPL(a) #a

#define XWIDGETS_PROTOCOL_VERSION XWIDGETS_STRINGIFY(XWIDGETS_CONCATENATE(XWIDGETS_PROTOCOL_VERSION_MAJOR,   \
                              XWIDGETS_CONCATENATE(.,XWIDGETS_CONCATENATE(XWIDGETS_PROTOCOL_VERSION_MINOR,   \
                                                   XWIDGETS_CONCATENATE(.,XWIDGETS_PROTOCOL_VERSION_PATCH)))))

#define XWIDGETS_BASE_VERSION XWIDGETS_STRINGIFY(XWIDGETS_CONCATENATE(XWIDGETS_BASE_VERSION_MAJOR,   \
                          XWIDGETS_CONCATENATE(.,XWIDGETS_CONCATENATE(XWIDGETS_BASE_VERSION_MINOR,   \
                                               XWIDGETS_CONCATENATE(.,XWIDGETS_BASE_VERSION_PATCH)))))

#define XWIDGETS_OUTPUT_VERSION XWIDGETS_STRINGIFY(XWIDGETS_CONCATENATE(XWIDGETS_OUTPUT_VERSION_MAJOR,   \
                            XWIDGETS_CONCATENATE(.,XWIDGETS_CONCATENATE(XWIDGETS_OUTPUT_VERSION_MINOR,   \
                                                 XWIDGETS_CONCATENATE(.,XWIDGETS_OUTPUT_VERSION_PATCH)))))

#define XWIDGETS_CONTROLS_VERSION XWIDGETS_STRINGIFY(XWIDGETS_CONCATENATE(XWIDGETS_CONTROLS_VERSION_MAJOR,   \
                              XWIDGETS_CONCATENATE(.,XWIDGETS_CONCATENATE(XWIDGETS_CONTROLS_VERSION_MINOR,   \
                                                   XWIDGETS_CONCATENATE(.,XWIDGETS_CONTROLS_VERSION_PATCH)))))

#ifdef __CLING__
#include "xwidgets_config_cling.hpp"
#endif

#endif
