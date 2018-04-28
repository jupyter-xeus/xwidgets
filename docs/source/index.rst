.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

.. image:: xwidgets.svg

The C++ backend for Jupyter interactive widgets.

Introduction
------------

``xwidgets`` is a C++ implementation of the Jupyter interactive widgets protocol. The Python reference implementation is available in the ipywidgets_ project.

xwidgets enables the use of the Jupyter interactive widgets in the C++ notebook, powered by the cling_ C++ interpreter and the xeus-cling_ kernel. xwidgets can also be used to create applications making use of the Jupyter interactive widgets without the C++ kernel per se.

``xwidgets`` and its dependencies require a modern C++ compiler supporting C++14. The following C++ compilers are supported:

- On Windows platforms, Visual C++ 2015 Update 2, or more recent
- On Unix platforms, gcc 4.9 or a recent version of Clang

Licensing
---------

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the LICENSE file for details.

.. toctree::
   :caption: INSTALLATION
   :maxdepth: 2

   installation

.. toctree::
   :caption: USAGE
   :maxdepth: 2

   usage

.. toctree::
   :caption: AUTHORING CUSTOM WIDGETS
   :maxdepth: 2

   custom

.. toctree::
   :caption: DEVELOPER ZONE

   compilers
   releasing

.. toctree::
   :caption: MISCELLANEOUS

   related_projects

.. _ipywidgets: https://github.com/jupyter-widgets/ipywidgets
.. _xeus-cling: https://github.com/QuantStack/xeus-cling
.. _cling: https://root.cern.ch/cling
