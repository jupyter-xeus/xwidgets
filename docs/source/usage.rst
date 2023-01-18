.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

User Guide
==========

What are Widgets?
-----------------

Widgets are eventful C++ objects that have a representation in the browser, often a control like a slider, a textbox etc.

Widgets can be used to build interactive GUIs in Jupyter notebooks. They can also be used to synchronize information between C++ and JavaScript.

Using Widgets
-------------

Widgets can be used in the Jupyter notebook with the xeus-cling C++ kernel simply by importing headers of the ``xwidgets`` library. For example, including the ``xslider`` headers makes the slider widget available.

.. code:: cpp

    #include "xwidgets/xslider.hpp"

Displaying Widgets
~~~~~~~~~~~~~~~~~~

Widgets can be displayed using Jupyter's display framework.


.. code:: cpp

    xw::slider<double> slider;
    slider.display();

The Model-View-Controller Pattern
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you display the same widget twice, the displayed instances in the front-end will remain in sync with each other. Dragging one slider will modify the value for the other slider. The reason for that is that each time a widget is displayed, a new visual representation is created, reflecting the same underlying object, or model. This Model-View-Controller (MVC) architectural pattern is applied. Each C++ instance of a widget type is a new instance of the model.

.. image:: widget-mvc.svg
   :alt: model-view controller

The Value Semantics in ``xwidgets``
-----------------------------------

The ``xwidgets`` framework differs from most common C++ widgets framework in that widgets have a *value semantics* instead of an *entity semantics*. Not dynamic polymorphism is at play, but static polymorphism based on the CRTP pattern.

A consequence, is that if a widget is *copied*, the resulting widget instance will have a new counterpart in the front-end. In the following example, ``slider2`` is a *copy* of ``slider1``. Upon creation, a new front-end widget is created, reflecting the state of that new widget instance. The states of ``slider1`` and ``slider2`` are *not* synchronized.

.. code:: cpp

    xw::slider<double> slider1;
    auto slider2 = slider1;
    slider2.value = 50.0;
    slider1.display();
    slider2.display();

However, if ``slider2`` was a reference on ``slider1``, or if ``slider1`` had been moved to ``slider2``, ``slider2`` would still refer to the same widget model in the front-end.

Resource Acquisition is Initialization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``xwidgets`` framework makes use of the ``RAII`` pattern (Resource Acquisition is Initialization). Creating a new widget instance results in the creation of the counterpart in the HTML/JavaScript frontend. The destructor triggers the destruction of the frontend model and all the views, unless the object being destructed has already been *moved from*.

This architecture ties the lifetime of the front-end object to that of the C++ model.

Naming Conventions and Widget Generators
----------------------------------------

CRTP bases and final classes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Widget classes with names prefixed by ``x`` are not meant to be directly instantiated. For example, ``xslider`` is the top-most CRTP base of ``slider``.

Widget classes with names that are not prefixed by ``x`` can be instantiated, but are *final*, i.e. they cannot be inherited from.

In fact, these final classes are typedefs on a special template parameterized by its base. For example, we have:

.. code:: cpp

    using button = xmaterialize<xbutton>;

Similarly, for template widget types, we also make use of the ``xmaterialize`` class, which

.. code:: cpp

    template <class T>
    using slider = xmaterialize<xslider, T>;

The ``xmaterialize`` class only implements the final inheritance closing the CRTP, together with the RAII logic, which is to be done at the top-most inheritance level, so that widget creation messages are sent after all the bases have been initialized.

Generator classes
~~~~~~~~~~~~~~~~~

Simple widget types such as ``slider`` may have a large number of attributes that can be set by the user, such as ``handle_color``, ``orientation``, ``min``, ``max``, ``value``, ``step``, ``readout_format``.

Providing a constructor for ``slider`` with a large number of such attributes would make the use of ``xwidgets`` very cumbersome, because users would need to know all the positional arguments to modify only one value. Instead, we mimick a keyword argument initialization with a method-chaining mechanism.

.. code:: cpp

    auto button = xw::slider<double>::initialize()
        .min(1.0)
        .max(9.0)
        .value(4.0)
        .orientation("vertical")
        .finalize();

This is a classical approach: calls to ``min``, ``max``, ``value`` and ``orientation`` all return the ``slider`` instance (by rvalue reference, which is optimized with C++ move semantics and copy ellision). The ``finalize()`` triggers the creation of the front-end object with the data.

Widget Events
-------------

Special Events
~~~~~~~~~~~~~~

Certain widget types such as ``button`` are not used to represent data types. Instead, the button widget is used to handle mouse clicks. The ``on_click`` method of the ``button`` widget can be used to register functions to be called when the button is clicked.

.. code:: cpp

    xw::button button;

    void foo()
    {
        std::cout << "Clicked!" << std::endl;
    }

    button.on_click(foo);
    button.display();

Xproperty Events
~~~~~~~~~~~~~~~~

The observer pattern of ``xwidgets`` relies upon the xproperty_ library.

``xproperty`` can be used to

 - register callbacks on changes of widget properties
 - register custom validators to only accept certain values
 - link properties of different widgets

Registering an Observer
^^^^^^^^^^^^^^^^^^^^^^^

In this example, we register an observer for a slider value, triggering the printing of the new slider value.

.. code:: cpp

    xw::slider<double> slider;
    slider.display()
    XOBSERVE(slider, value, [](const auto& s) {
        std::cout << "Observer: New Slider value: " << s.value << std::endl;
    });

Registering a Validator
^^^^^^^^^^^^^^^^^^^^^^^

In this example, we validate the proposed values for a numerical text. Negative values are rejected.

.. code:: cpp

    xw::numeral<double> number;
    number.min = -100
    number.display()
    XVALIDATE(number, value, [](const auto&, double proposal) {
        std::cout << "Validator: Proposal: " << proposal << std::endl;
        if (proposal < 0)
        {
            throw std::runtime_error("Only non-negative values are valid.");
        }
        return proposal;
    });

For more details about the API for ``xproperty``, we refer to the ``xproperty`` documentation.

.. _xproperty: https://github.com/jupyter-xeus/xproperty
