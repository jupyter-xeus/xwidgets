.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Serialization and Deserialization of Widget Attributes
======================================================

Properties of xobjects are automatically synchronized with the counterpart
front-end object. The synchronization involves the serialization and
deserialization of the modified properties.

Standard case: JSON serialization of properties
-----------------------------------------------

By default, if the type held by the property is JSON-serializable, the behavior
of xwidgets will be to make use of the JSON serialization for that type to
synchronize the property value between the kernel and the front-end.

By JSON-serializable, we mean that the type has to be convertible from and to
the ``json`` type of the ``nlohmann_json`` package, a.k.a `"JSON for Modern C++"`_.
Integral types, floating points, and standard STL containers are supported by
``nlohmann_json``.

JSON serialization and deserialization for a user-defined type can be specified
by providing an overload of the ``to_json`` and ``from_json`` functions in the
same namespace where it is defined.

For example, the serialization of a type ``ns::person`` with attributes "name",
"address" and "age" can be specified in the following fashion:

.. code::

    using nlohmann::json;

    namespace ns
    {
        void to_json(json& j, const person& p)
        {
            j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
        }

        void from_json(const json& j, person& p)
        {
            p.name = j.at("name").get<std::string>();
            p.address = j.at("address").get<std::string>();
            p.age = j.at("age").get<int>();
        }
    }

Upon serialization and deserialization of ``ns::person`` objects, the overloads
of ``to_json`` and ``from_json`` are picked up by argument-dependent lookup
(ADL).

Eventually, patches sent to and received from the front-end are JSON objects
whose keys are the names of the attributes, and the values are the JSON
representations of the new value.

For example, the JSON patch for a slider widget corresponding to a change of
attributes "value", "min", "readout_format" looks like:

.. code::

    {
        "value" : 10,
        "min": 0,
        "readout_format": ".2f"
    }

Advanced use cases: making use of binary serialization
------------------------------------------------------

The Jupyter Widgets communication protocol allows for the communication of raw
binary buffers to the front-end. This is especially convenient in visualization
packages where large numerical arrays may be sent across the wire, or when
serializing images and such.

The Jupyter binary serialization protocol
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Upon modification of properties in the front-end or the back-end, the content
of the comm message sent to or from the front-end is

 - a JSON patch holding the JSON-serialized values of the modified attributes
 - optionally a number of binary frames holding raw data.

On the JavaScript side, the first stage of the deserialization consists in

1. deserializing the JSON into nested JavaScript objects and arrays.
2. inserting the binary frames in the deserialized JSON in the form of
   DataView_ objects at locations specified in a companion ``buffer_paths``
   array sent across the wire alongside the list of buffers.

For example, in the ``image`` widget, the ``value`` attribute holds the binary
data for the image (encoded in the format specified with the ``format`` string
attribute). A patch for a change if the ``value`` and ``format`` attribute will
look like

.. code::

    // JSON patch:

    {
        "format": "png"
    }

    // buffer paths
    [["value"]]

    // Buffers
    [ { -- Binary png buffer -- } ]

On the JavaSCript side, this gets deserialized into

.. code::

    {
        "format": "png",
        "value": DataView({ -- Binary png buffer -- })}
    }

On the C++ side, the internal machinery of ``xwidgets`` automatically composes
this list of paths for the user. Custom widget authors must compose a message
of the form

.. code::

    // JSON patch:

    {
        "format": "png",
        "value": "@buffer_reference@0"
    }

    // Buffers
    [ { -- Binary png buffer -- } ]

Instead of specifying the buffer paths in a separate array, the location where
the buffer is to be inserted holds a placeholder string indicating the index of
the corresponding buffer in the list, prefixed with ``@buffer_reference@``.

Making use of the Jupyter serialization protocol in ``xwidgets``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Serialization**

The serialization is handled by the free function

``xwidgets_serialize(value, patch, buffers);``

where

- the first argument is a const reference to the value,
- the second argument (``patch``) to the JSON object being written.
- the third argument (``buffers``) is a reference to the sequence of buffers of
  the message.

picked up by argument-dependent lookup, and apply to all xwidgets properties
holding values of that type.

.. note::

    The default implementation of ``xwidgets_serialize`` simply invokes the
    JSON serialization for that type. In most cases, overloading
    ``xwidgets_serialize`` is not necessary. This is mostly relevant for
    properties for which one wants to bypass JSON serialization or make
    use of binary serialization.

**Deserialization**

The deserialization of properties from the patch is handled by calling `apply_patch_to_registered_properties` on the widget instance.

This member function is responsible for deserializing the patch by iterating over the registered properties.
These properties self-register upon construction in the class.

A property that defines a custom serialization / deserialization should use
the `xwidgets_serialize` / `xwidgets_deserialize` functions.

The default implementation of `xwidgets_deserialize` reads:

.. code::

    template <class T>
    inline void xwidgets_deserialize(T& value, const nl::json& j, const xeus::buffer_sequence& buffers)
    {
        value = j.template get<T>();
    }

which means that the default behavior is to call into ``xwidgets_deserialize``
with the value held by the property. A way to specify a deserialization method
for a user-defined type is to overload the ``xwidgets_deserialize`` method for
that type in the same namespace where the type is defined. Then, it will be
picked up by argument-dependent lookup, and apply to all xwidgets properties
holding values of that type.

.. note::

    The default implementation of ``xwidgets_deserialize`` simply invokes the
    JSON deserialization for that type. In most cases, overloading
    ``xwidgets_deserialize`` or a custom `xwidgets_deserialize` is not necessary.
    This is mostly relevant for properties for which one wants to bypass JSON
    deserialization or make use of binary deserialization.

.. _`"JSON for Modern C++"`: https://github.com/nlohmann/json/
.. _DataView: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/DataView
