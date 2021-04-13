.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.


.. raw:: html

   <style>
   .rst-content .section>img {
       width: 30px;
       margin-bottom: 0;
       margin-top: 0;
       margin-right: 15px;
       margin-left: 15px;
       float: left;
   }
   </style>

Installation
============

.. image:: conda.svg

Using the conda-forge package
-----------------------------

A package for xwidgets is available on the mamba (or conda) package manager.
The package will also pull all the dependencies.

.. code::

    mamba install xwidgets -c conda-forge

.. image:: cmake.svg

From source with cmake
----------------------

You can also install ``xwidgets`` from source with cmake. On Unix platforms, from the source directory:
However, you need to make sure to have the required libraries available on your machine.

.. code::

    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=/path/to/prefix ..
    make install

On Windows platforms, from the source directory:

.. code::

    mkdir build
    cd build
    cmake -G "NMake Makefiles" -DCMAKE_INSTALL_PREFIX=/path/to/prefix ..
    nmake
    nmake install
