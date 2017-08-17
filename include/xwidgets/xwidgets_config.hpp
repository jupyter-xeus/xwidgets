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
#define XWIDGETS_VERSION_MINOR 1
#define XWIDGETS_VERSION_PATCH 0

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
