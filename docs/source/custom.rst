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

``set_patch_from_property(property, patch, buffers);``

where

- the first argument is a const reference to the property,
- the second argument (``patch``) is a reference to the JSON patch being
  written.
- the third argument (``buffers``) is a reference to the sequence of buffers of
  the message.

When the function is called, ``patch`` and ``buffers`` may already hold data
from earlier properties for which the function was called. New buffers may be
appended and new property names added to the ``patch`` argument.

**Overloading** ``set_patch_from_property``

To specify the serialization of an attribute of a widget, one can overload the
``set_patch_from_property`` function for the relevant property.

For example, the overload of ``set_patch_from_property`` for the ``value``
property of the image widget reads:

.. code::

    inline void set_patch_from_property(const decltype(image::value)& property,
                                        xeus::xjson& patch,
                                        xeus::buffer_sequence& buffers)
    {
        patch[property.name()] = xbuffer_reference_prefix() + std::to_string(buffers.size());
        buffers.emplace_back(property().data(), property().size());
    }

.. note::

    ``decltype(image::value)`` is the type of the ``value`` property of the
    image widget, which is unique to the image widget, (more precisely, its
    type is an internal class of the image class). No other attribute of
    another widget can have the same type.

    This specialization is a better match than the default one and is picked-up
    by argument-dependent lookup, however, this will not apply to properties of
    other widgets or other properties of this widget also holding a
    ``std::vector<char>``.

**Overloading** ``xwidgets_serialize``

The default implementation of ``set_patch_from_property`` reads:

.. code::

    template <class P>
    inline void set_patch_from_property(const P& property,
                                        xeus::xjson& patch,
                                        xeus::buffer_sequence& buffers)
    {
        xwidgets_serialize(property(), patch[property.name()], buffers);
    }

which means that the default behavior is to call into ``xwidgets_serialize``
with the value held by the property. A way to specify a serialization method
for a user-defined type is to overload the ``xwidgets_serialize`` method for
that type in the same namespace where the type is defined. Then, it will be
picked up by argument-dependent lookup, and apply to all xwidgets properties
holding values of that type.

.. note::

    The default implementation of ``xwidgets_serialize`` simply invokes the
    JSON serialization for that type. In most cases, overloading
    ``xwidgets_serialize`` or ``set_patch_from_property`` is not necessary.
    This is mostly relevant for properties for which one wants to bypass JSON
    serialization or make use of binary serialization.

**Deserialization**

The deserialization is handled by the free function

``set_property_from_patch(property, patch, buffers);``

where

- the first argument is a reference to the property,
- the second argument (``patch``) holds a const reference to the JSON patch
  being read.
- the third argument (``buffers``) holds a const reference to the sequence of
  buffers being read.

``set_property_from_patch`` is called for each property of the widget.

The default behavior of ``set_property_from_patch`` is to invoke the JSON
deserialization for each property. However, just like
``set_patch_from_property``, it can be overloaded for a specific property type.

For example, the overload of ``set_property_from_patch`` for the ``value``
property of the image widget reads:

.. code::

    inline void set_property_from_patch(decltype(image::value)& property,
                                        const xeus::xjson& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            using value_type = typename decltype(image::value)::value_type;
            std::size_t index = buffer_index(patch[property.name()].template get<std::string>());
            const auto& value_buffer = buffers[index];
            const char* value_buf = value_buffer.data<const char>();
            property = value_type(value_buf, value_buf + value_buffer.size());
        }
    }

.. note::

    ``decltype(image::value)`` is the type of the ``value`` property of the
    image widget, which is unique to the image widget, (more specifically, its
    type is an internal class of the image class).

    This specialization is a better match than the default one and is picked-up
    by argument-dependent lookup, however, this will not apply to properties of
    other widgets or other properties of this widget also holding a
    ``std::vector<char>``.

**Overloading** ``xwidgets_deserialize``

The default implementation of ``set_property_from_patch`` reads:

.. code::

    template <class P>
    inline void set_property_from_patch(P& property,
                                        const xeus::xjson& patch,
                                        const xeus::buffer_sequence& buffers)
    {
        auto it = patch.find(property.name());
        if (it != patch.end())
        {
            typename P::value_type value;
            xwidgets_deserialize(value, *it, buffers);
            property = value;
        }
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
    ``xwidgets_deserialize`` or ``set_property_from_patch`` is not necessary.
    This is mostly relevant for properties for which one wants to bypass JSON
    deserialization or make use of binary deserialization.

.. _`"JSON for Modern C++"`: https://github.com/nlohmann/json/
.. _DataView: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/DataView

