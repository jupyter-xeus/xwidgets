/***************************************************************************
* Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XWIDGETS_CONFIG_HPP
#define XWIDGETS_CONFIG_HPP

#define XWIDGETS_VERSION_MAJOR 0
#define XWIDGETS_VERSION_MINOR 6
#define XWIDGETS_VERSION_PATCH 1

#define XWIDGETS_PROTOCOL_VERSION_MAJOR 2
#define XWIDGETS_PROTOCOL_VERSION_MINOR 0
#define XWIDGETS_PROTOCOL_VERSION_PATCH 0

// Composing the protocol version string from major, minor and patch

#define XWIDGETS_CONCATENATE(A, B) XWIDGETS_CONCATENATE_IMPL(A, B)
#define XWIDGETS_CONCATENATE_IMPL(A, B) A##B
#define XWIDGETS_STRINGIFY(a) XWIDGETS_STRINGIFY_IMPL(a)
#define XWIDGETS_STRINGIFY_IMPL(a) #a

#define XWIDGETS_PROTOCOL_VERSION XWIDGETS_STRINGIFY(XWIDGETS_CONCATENATE(XWIDGETS_PROTOCOL_VERSION_MAJOR,   \
                              XWIDGETS_CONCATENATE(.,XWIDGETS_CONCATENATE(XWIDGETS_PROTOCOL_VERSION_MINOR,   \
                                                   XWIDGETS_CONCATENATE(.,XWIDGETS_PROTOCOL_VERSION_PATCH)))))

#ifdef _WIN32
    #ifdef XWIDGETS_EXPORTS
        #define XWIDGETS_API __declspec(dllexport)
    #else
        #define XWIDGETS_API __declspec(dllimport)
    #endif
#else
    #define XWIDGETS_API
#endif

#endif
