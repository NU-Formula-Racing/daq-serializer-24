#ifndef __DAQSER_CAN_H__
#define __DAQSER_CAN_H__
#ifndef NATIVE

#include <CAN.h>
#include <map>
#include <vector>

#include <frame.hpp>
#include <daqser.hpp>

/// @brief 
/// This file is a template for the CAN communication of the daqser project.
/// This file is generated via a python script, and based on the current DBC file for the car
/// To enable listening to CANMessages, define macros for the messages you want to listen to
/// The macros are folllw the following format:
/// #define RX_<BoardName>
// This is not intended for use in for boards that listen to a small number of messages
// Rather, it is intended for use in interface boards that listen to a large number of messages
// Primarily, Wireless and Logger boards

namespace daqser
{
    VirtualTimerGroup g_timerGroup;
    CAN g_canBus{};

    // auto generated signals!
    // <INSERT_SIGNALS_HERE>

    // auto generated messages!
    // <INSERT_MESSAGES_HERE>

    void updateSignals()
    {
        // <INSERT_UPDATE_SIGNALS_HERE>
    }

}

#endif // !NATIVE

#endif // __DAQSER_CAN_H__