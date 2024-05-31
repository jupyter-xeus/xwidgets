# ![xwidgets](docs/source/xwidgets.svg)

[![GithubActions](https://github.com/jupyter-xeus/xwidgets/actions/workflows/main.yml/badge.svg)](https://github.com/jupyter-xeus/xwidgets/actions/workflows/main.yml)
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

We provide a package for the mamba (or conda) package manager.

- Installing `xwidgets` and the C++ kernel

```bash
mamba install xeus-cling xwidgets -c conda-forge
```

Then, the front-end extension must be installed for either the classic notebook
or JupyterLab.

- Installing the extension for the classic notebook

```
mamba install widgetsnbextension -c conda-forge
```

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

All the dependencies of xwidgets are available for the mamba (or conda) package manager.

| `xwidgets` | `jupyterlab_widgets` | `widgetsnbextension` | `xproperty`    | `xeus`         | `nlohmann_json` |
|------------|----------------------|----------------------|----------------|----------------|-----------------|
|  main      | ^3.0.0               | ^4.0.0               | >=0.11.0,<0.12 | >=5.0,<6.0     | >=3.11.3,<3.12  |
|  0.29.0    | ^3.0.0               | ^4.0.0               | >=0.11.0,<0.12 | >=5.0,<6.0     | >=3.11.3,<3.12  |

Versions prior to 0.29 also depend on the xtl:

| `xwidgets` | `jupyterlab_widgets` | `widgetsnbextension` | `xtl`          | `xproperty`    | `xeus`         | `nlohmann_json` |
|------------|----------------------|----------------------|----------------|----------------|----------------|-----------------|
|  master    | ^3.0.0               | ^4.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=3.2,<4.0     | >=3.9.1,<3.10   |
|  0.28.1    | ^3.0.0               | ^4.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=3.2,<4.0     | >=3.9.1,<3.10   |
|  0.28.0    | ^3.0.0               | ^4.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=3.0,<4.0     | >=3.9.1,<3.10   |
|  0.27.3    |                      | ^3.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=3.0,<4.0     | >=3.9.1,<3.10   |
|  0.27.2    |                      | ^3.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=3.0,<4.0     | >=3.9.1,<3.10   |
|  0.27.1    |                      | ^3.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=3.0,<4.0     | >=3.9.1,<3.10   |
|  0.27.0    |                      | ^3.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=3.0,<4.0     | >=3.9.1,<3.10   |
|  0.26.1    |                      | ^3.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=2.0,<3.0     | >=3.9.1,<3.10   |
|  0.26.0    |                      | ^3.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=2.0,<3.0     | >=3.9.1,<3.10   |
|  0.25.0    |                      | ^3.0.0               | >=0.7,<0.8     | >=0.11.0,<0.12 | >=1.0,<2.0     | >=3.6.1,<4.0    |

Packages `jupyterlab_widgets` and `widgetsnbextension` are not dependencies *per se*, but
hold the frontend counterparts for JupyterLab and the classic notebook respectively that must be installed
in the environment of the Jupyter server.

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license.
See the [LICENSE](LICENSE) file for details.
