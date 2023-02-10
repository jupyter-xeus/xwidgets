/***************************************************************************
 * Copyright (c) 2017, Sylvain Corlay and Johan Mabille                     *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XWIDGETS_TARGET_HPP
#define XWIDGETS_TARGET_HPP

#include <xeus/xcomm.hpp>

namespace xw
{
    /**
     * Return the ``jupyter.widget`` Xeus target.
     *
     * This target is used by the comms of the widgets to synchronize state between the frontend
     * (_e.g._ jupyterlab) and the backend (kernel).
     * This function will register the target with Xeus upon first call.
     */
    xeus::xtarget* get_widget_target();
}

#endif
