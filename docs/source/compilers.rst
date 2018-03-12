.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Compiler workarounds
====================

This page tracks the workarounds for the various compiler issues that we encountered in the development. This is mostly of interest for developers interested in contributing to xwidgets.

Visual Studio 2017 and ``__declspec(dllexport)``
------------------------------------------------

In ``xwidgets.cpp`` a number of widget types are precompiled, in order to improve the just-in-time compilation time in the context of the cling C++ interpreter.

However, with Visual Studio 2017, the introduction of ``__declspec(dllexport)`` instructions for certain widget types causes compilation errors. This is the case for widget types that are used as properties for other widgets such as ``xlayout``` and style widgets.
