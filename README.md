# ![xwidgets](docs/source/xwidgets.svg)

[![Travis](https://travis-ci.org/jupyter-xeus/xwidgets.svg?branch=master)](https://travis-ci.org/jupyter-xeus/xwidgets)
[![Appveyor](https://ci.appveyor.com/api/projects/status/kjoatvulm28dpr3r?svg=true)](https://ci.appveyor.com/project/jupyter-xeus/xwidgets)
[![Documentation](http://readthedocs.org/projects/xwidgets/badge/?version=latest)](https://xwidgets.readthedocs.io/en/latest/?badge=latest)
[![Binder](https://img.shields.io/badge/launch-binder-brightgreen.svg)](https://mybinder.org/v2/gh/jupyter-xeus/xwidgets/stable?filepath=notebooks/xwidgets.ipynb)
[![Join the Gitter Chat](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/QuantStack/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

A C++ backend for Jupyter interactive widgets.

## Introduction

`xwidgets` is a C++ implementation of the Jupyter interactive widgets protocol.
The Python reference implementation is available in the
[ipywidgets](https://github.com/jupyter-widgets/ipywidgets) project.

`xwidgets` enables the use of the Jupyter interactive widgets in the C++
notebook, powered by the `xeus-cling` kernel and the `cling` C++ interpreter
from CERN. `xwidgets` can also be used to create applications making use of the
Jupyter interactive widgets without the C++ kernel *per se*.

## Usage

Launch the jupyter notebook with `jupyter notebook` and launch a new C++
notebook by selecting the **xeus C++14** kernel in the *new* dropdown.

![Widgets](widgets.gif)

## Installation

We provide a package for the conda package manager.

- Installing `xwidgets` and the C++ kernel

```bash
conda install xeus-cling xwidgets -c conda-forge
```

Then, the front-end extension must be installed for either the classic notebook
or JupyterLab.

- Installing the extension for the classic notebook

```
conda install widgetsnbextension -c conda-forge
```

- Installing the JupyterLab extension

```
jupyter labextension install @jupyter-widgets/jupyterlab-manager
```

This command defaults to installing the latest version of the JupyterLab
extension. Depending on the version of `xwidgets` and `jupyterlab` you have
installed you may need an older version.

## Installation from sources

Or you can directly install it from the sources if you have all the
dependencies already installed:

```bash
cmake -D CMAKE_INSTALL_PREFIX=your_install_prefix
make install
```

## Trying it online

To try out xwidgets interactively in your web browser, just click on the binder
link:

[![Binder](binder-logo.svg)](https://mybinder.org/v2/gh/jupyter-xeus/xwidgets/stable?filepath=notebooks/xwidgets.ipynb)

## Documentation

To get started with using `xwidgets`, check out the full documentation

http://xwidgets.readthedocs.io/

## Dependencies

All the dependencies of xwidgets are available for the conda package manager.

| `xwidgets` | `widgetsnbextension`  |     `xtl`       | `xproperty`    | `xeus`          | `nlohmann_json` |
|------------|-----------------------|-----------------|----------------|-----------------|-----------------|
|  master    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.24.0    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.23.0    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.22.1    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.22.0    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.21.1    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.21.0    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.20.2    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.25  | >=3.6.1,<4.0    |
|  0.20.1    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.24  | >=3.6.1,<4.0    |
|  0.20.0    |      ^3.0.0           |  >=0.6.11,<0.7  | >=0.10.0,<0.11 | >=0.21.1,<0.24  | >=3.6.1,<4.0    |
|  0.19.0    |      ^3.0.0           |  >=0.6.5,<0.7   | >=0.8.1,<0.9   | >=0.21.1,<0.22  | >=3.6.1,<4.0    |
|  0.18.0    |      ^3.0.0           |  >=0.6.5,<0.7   | >=0.8.1,<0.9   | >=0.20.0,<0.21  | >=3.6.1,<4.0    |
|  0.17.0    |      ^3.0.0           |  >=0.6.1,<0.7   | >=0.8.1,<0.9   | >=0.19.1,<0.20  | >=3.5.0,<4.0    |
|  0.16.1    |      ^3.0.0           |  >=0.5.2,<0.6   | >=0.8.1,<0.9   | >=0.18.1,<0.19  | >=3.3.0,<4.0    |
|  0.16.0    |      ^3.0.0           |  >=0.5.2,<0.6   | >=0.8.0,<0.9   | >=0.18.1,<0.19  | >=3.3.0,<4.0    |

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license.
See the [LICENSE](LICENSE) file for details.
