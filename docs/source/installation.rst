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
  :height: 50px

Using the conda-forge package
-----------------------------
We provide a package for the mamba (or conda) package manager.
Installing `xwidgets` and the C++ kernel

.. code:: bash

   mamba install -c conda-forge xeus-cpp xwidget

Then, the front-end extension must be installed for either the classic notebook or JupyterLab.

- Installing the extension for JupyterLab
  .. code:: bash

     mamba install -c conda-forge jupyterlab_widgets

- Installing the extension for the classic notebook
  .. code::

     mamba install -c conda-forge widgetsnbextension

.. image:: cmake.svg
  :height: 50px

From source with cmake
----------------------

You can also install ``xwidgets`` from source with cmake.
However, you need to make sure to have the required libraries available on your machine.
See `environment-dev.yml <https://github.com/jupyter-xeus/xwidgets/blob/main/environment-dev.yml>`_
for the development dependencies on Conda-Forge.

.. code::

    cmake -B build/ -G Ninja -D CMAKE_INSTALL_PREFIX=/path/to/prefix -D CMAKE_BUILD_TYPE=Release
    cmake --build build/
    cmake --install build/
