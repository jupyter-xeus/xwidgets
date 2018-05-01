.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Compiler workarounds
====================

This page tracks the workarounds for the various compiler issues that we
encountered in the development. This is mostly of interest for developers
interested in contributing to xwidgets.

Visual Studio 2017 and ``__declspec(dllexport)``
------------------------------------------------

In ``xwidgets.cpp`` a number of widget types are precompiled, in order to
improve the just-in-time compilation time in the context of the cling C++
interpreter.

However, with Visual Studio 2017, the introduction of ``__declspec(dllexport)``
instructions for certain widget types causes compilation errors. This is the
case for widget types that are used as properties for other widgets such as
``xlayout``` and style widgets.

The upstream `MSVC issue`_  issue appears to have been solved with VS2017 15.7
(Preview 3). The impacted build numbers for Visual Studio are
``_MSC_VER==1910``, ``_MSC_VER==1911```, ``_MSC_VER==1912```,
``_MSC_VER==1913```.

Visual Studio and CRTP bases
----------------------------

If we have ``template <class T> class Foo : public Bar<Foo<T>>``, then within
the implementation of ``Foo ``, ``Bar`` should be a template, and not refer to
``Bar<Foo<T>>``. However, unlike GCC and Clang, Visual Studio incorrectly makes
``Bar`` refer to the fully specialized template type.

.. _`MSVC issue`: https://developercommunity.visualstudio.com/content/problem/208938/compilation-error-c2057-expected-constant-expressi.html
