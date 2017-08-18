# xwidgets

**THIS IS AN EARLY PREVIEW OF THE C++ WIDGETS, PLEASE DON'T USE IT JUST YET**

## Installation

First, install xeus-cling and notebook from conda

```bash
conda install cling      -c QuantStack -c conda-forge
conda install xeus-cling -c QuantStack -c conda-forge
conda install xproperty  -c QuantStack -c conda-forge
conda install notebook   -c QuantStack -c conda-forge
```

Install and enable the Jupyter widgets notebook extension.

```bash
pip install widgetsnbextension --pre
jupyter nbextension enable --py --sys-prefix widgetsnbextension
```

## Requirements

 - widgetsnbextension ~3.0.0
 - xeus ~0.5.3
 - xproperty 0.2.2
