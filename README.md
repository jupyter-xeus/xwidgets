# ![xwidgets](http://quantstack.net/assets/images/xwidgets.svg)

[![Binder](https://img.shields.io/badge/launch-binder-brightgreen.svg)](https://beta.mybinder.org/v2/gh/QuantStack/xwidgets/0.5.0?filepath=notebooks/xwidgets.ipynb)
[![Join the Gitter Chat](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/QuantStack/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

The C++ backend for Jupyter interactive widgets.

**xwidgets is an early developer preview, and is not suitable for general usage yet. Features and implementation are subject to change.**

## Introduction

`xwidgets` is a C++ implementation of the Jupyter interactive widgets protocol. The Python reference implementation is available in the [ipywidgets](https://github.com/jupyter-widgets/ipywidgets) project.

`xwidgets` enables the use of the Jupyter interactive widgets in the C++ notebook, powered by the `xeus-cling` kernel and the `cling` C++ interpreter from CERN. `xwidgets` can also be used to create applications making use of the Jupyter interactive widgets without the C++ kernel *per se*.

## Usage

Launch the jupyter notebook with `jupyter notebook` and launch a new C++ notebook by selecting the **xeus C++14** kernel in the *new* dropdown.

![Widgets](widgets.gif)

## Installation

We provide a `xeus-cling` package for the conda package manager.

```bash
conda install xeus-cling notebook xwidgets widgetsnbextension -c QuantStack
```

Or you can directly install it from the sources if you have all the dependencies already installed:

```bash
cmake -D CMAKE_INSTALL_PREFIX=your_install_prefix
make install
```

## Dependencies

All the dependencies of xwidgets are available for the conda package manager. 

| `xwidgets` | `widgetsnbextension`  |     `xtl`      | `xproperty`   | `xeus`       |
|------------|-----------------------|----------------|---------------|--------------|
|  master    |      ~3.0.0           |  >=0.3.4,<0.4  | >=0.4.2,<0.5  | >=0.8.0,<0.9 |
|  0.5.1     |      ~3.0.0           |  >=0.3.4,<0.4  | >=0.4.2,<0.5  | >=0.8.0,<0.9 |
|  0.5.0     |      ~3.0.0           |  >=0.3.4,<0.4  | >=0.4.1,<0.5  | >=0.8.0,<0.9 |
|  0.4.0     |      ~3.0.0           |  >=0.2.5,<0.3  | >=0.4.0,<0.5  | >=0.7.0,<0.8 |
|  0.3.0     |      ~3.0.0           |  >=0.2.5,<0.3  | >=0.4.0,<0.5  | >=0.6.0,<0.7 |

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
