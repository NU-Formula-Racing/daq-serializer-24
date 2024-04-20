#ifndef __DAQSER_CAN_H__
#define __DAQSER_CAN_H__
// #ifndef NATIVE

#include <CAN.h>
#include <map>
#include <vector>

#include "frame.hpp"
#include "daqser.hpp"

namespace daqser
{
    VirtualTimerGroup g_timerGroup;
    CAN g_canBus{};

    // auto generated signals!

    // <INSERT_SIGNALS_HERE>

    // auto generated messages!

    // <INSERT_MESSAGES_HERE>

    // functions to update daqser

    std::map<std::string, std::function<void()>> g_signalMap =
    {
        // <INSERT_SIGNAL_MAP_HERE>
    };



    void updateSignals(std::vector<std::string> signalNames)
    {
        for (auto signalName : signalNames)
        {
            g_signalMap[signalName]();
        }

        g_canBus.Tick();
    }
}

// #endif // !NATIVE

#endif // __DAQSER_CAN_H__