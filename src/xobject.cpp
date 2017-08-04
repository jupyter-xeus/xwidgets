#include "xobject.hpp"

namespace xeus
{
    const char* get_widget_target_name()
    {
        return "jupyter.widget";
    }

    xtarget* get_widget_target()
    {
        return get_interpreter().comm_manager().target(get_widget_target_name());
    }

    void xobject_comm_opened(const xcomm& /*comm*/, const xmessage& /*msg*/)
    {
    }

    bool register_comm_target()
    {
        get_interpreter().comm_manager().register_comm_target(get_widget_target_name(), xobject_comm_opened);
        return true;
    }
}

namespace
{
    bool registered = ::xeus::register_comm_target();
}