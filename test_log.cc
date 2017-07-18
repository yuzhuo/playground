
#include "log.h"

// LOG_OFF();

int main()
{
    LOG_SET_LEVEL("critical");

    LOG_DEBUG("debug msg");
    LOG_INFO("info msg");
    LOG_WARNING("warning msg");
    LOG_ERROR("error msg");
    LOG_CRITICAL("critical msg");

    LOG_METHOD();

    return 0;
}
