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
    CAN g_canBus{}; // 40 defines the message buffer size btw

    // auto generated signals!
#ifdef RX_PDM
    // PDM_Current Signals
    MakeSignedCANSignal(float, 0, 32, 0.01, 0.0) s_PDM_Current_Unreg_Amps{};
    MakeSignedCANSignal(float, 32, 32, 0.01, 0.0) s_PDM_Current_FiveVolt_Amps{};
#endif
#ifdef RX_WHEEL
    // Wheel_Temp_Front Signals
    MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) s_Wheel_Temp_Front_Wheel_Temp_FrontL1{};
    MakeSignedCANSignal(float, 16, 16, 0.01, 0.0) s_Wheel_Temp_Front_Wheel_Temp_FrontL2{};
    MakeSignedCANSignal(float, 32, 16, 0.01, 0.0) s_Wheel_Temp_Front_Wheel_Temp_FrontR1{};
    MakeSignedCANSignal(float, 48, 16, 0.01, 0.0) s_Wheel_Temp_Front_Wheel_Temp_FrontR2{};
    // Wheel_Speed_Front Signals
    MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) s_Wheel_Speed_Front_Wheel_Speed_FrontL{};
    MakeSignedCANSignal(float, 16, 16, 0.01, 0.0) s_Wheel_Speed_Front_Wheel_Speed_FrontR{};
    // Wheel_Temp_Back Signals
    MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) s_Wheel_Temp_Back_Wheel_Temp_BackL1{};
    MakeSignedCANSignal(float, 16, 16, 0.01, 0.0) s_Wheel_Temp_Back_Wheel_Temp_BackL2{};
    MakeSignedCANSignal(float, 32, 16, 0.01, 0.0) s_Wheel_Temp_Back_Wheel_Temp_BackR1{};
    MakeSignedCANSignal(float, 48, 16, 0.01, 0.0) s_Wheel_Temp_Back_Wheel_Temp_BackR2{};
#endif
#ifdef RX_COOLANT
    // Coolant_Temp_Message Signals
    MakeSignedCANSignal(float, 0, 32, 1.0, -40.0) s_Coolant_Temp_Message_Coolant_Temp{};
    // Coolant_Flow_Message Signals
    MakeSignedCANSignal(float, 0, 32, 1.0, 0.0) s_Coolant_Flow_Message_Coolant_Flow{};
#endif
#ifdef RX_SHUTDOWN
    // Shutdown_Status Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_Shutdown_Status_Voltage_Sag{};
#endif
#ifdef RX_ETC
    // Throttle_tx Signals
    MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) s_Throttle_tx_Throttle_percent{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, 0.0) s_Throttle_tx_Throttle_active{};
    // Brake_tx Signals
    MakeSignedCANSignal(bool, 24, 8, 1.0, 0.0) s_Brake_tx_Brake_pedal{};
#endif
#ifdef RX_VCU
    // Drive_Status Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_Drive_Status_Drive_State{};
#endif
#ifdef RX_SUSPENSION
    // Sus_Pots Signals
    MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) s_Sus_Pots_Sus_Front{};
#endif


    // auto generated messages!
#ifdef RX_PDM
    // PDM_Current
    CANRXMessage<2> m_PDM_Current { g_canBus, 0x270, [](){}, s_PDM_Current_Unreg_Amps, s_PDM_Current_FiveVolt_Amps };
#endif
#ifdef RX_WHEEL
    // Wheel_Temp_Front
    CANRXMessage<4> m_Wheel_Temp_Front { g_canBus, 0x410, [](){}, s_Wheel_Temp_Front_Wheel_Temp_FrontL1, s_Wheel_Temp_Front_Wheel_Temp_FrontL2, s_Wheel_Temp_Front_Wheel_Temp_FrontR1, s_Wheel_Temp_Front_Wheel_Temp_FrontR2 };
    // Wheel_Speed_Front
    CANRXMessage<2> m_Wheel_Speed_Front { g_canBus, 0x411, [](){}, s_Wheel_Speed_Front_Wheel_Speed_FrontL, s_Wheel_Speed_Front_Wheel_Speed_FrontR };
    // Wheel_Temp_Back
    CANRXMessage<4> m_Wheel_Temp_Back { g_canBus, 0x412, [](){}, s_Wheel_Temp_Back_Wheel_Temp_BackL1, s_Wheel_Temp_Back_Wheel_Temp_BackL2, s_Wheel_Temp_Back_Wheel_Temp_BackR1, s_Wheel_Temp_Back_Wheel_Temp_BackR2 };
#endif
#ifdef RX_COOLANT
    // Coolant_Temp_Message
    CANRXMessage<1> m_Coolant_Temp_Message { g_canBus, 0x420, [](){}, s_Coolant_Temp_Message_Coolant_Temp };
    // Coolant_Flow_Message
    CANRXMessage<1> m_Coolant_Flow_Message { g_canBus, 0x420, [](){}, s_Coolant_Flow_Message_Coolant_Flow };
#endif
#ifdef RX_SHUTDOWN
    // Shutdown_Status
    CANRXMessage<1> m_Shutdown_Status { g_canBus, 0x310, [](){}, s_Shutdown_Status_Voltage_Sag };
#endif
#ifdef RX_ETC
    // Throttle_tx
    CANRXMessage<2> m_Throttle_tx { g_canBus, 0x010, [](){}, s_Throttle_tx_Throttle_percent, s_Throttle_tx_Throttle_active };
    // Brake_tx
    CANRXMessage<1> m_Brake_tx { g_canBus, 0x010, [](){}, s_Brake_tx_Brake_pedal };
#endif
#ifdef RX_VCU
    // Drive_Status
    CANRXMessage<1> m_Drive_Status { g_canBus, 0x000, [](){}, s_Drive_Status_Drive_State };
#endif
#ifdef RX_SUSPENSION
    // Sus_Pots
    CANRXMessage<1> m_Sus_Pots { g_canBus, 0x520, [](){}, s_Sus_Pots_Sus_Front };
#endif


    void initializeCAN()
    {
        g_canBus.Initialize(ICAN::BaudRate::kBaud1M);
        g_timerGroup.AddTimer(10, [](){ g_canBus.Tick();});
    }

    void updateSignals()
    {
#ifdef RX_PDM
    // PDM_Current
    daqser::set("PDM_Current.Unreg_Amps", (float)s_PDM_Current_Unreg_Amps);
    daqser::set("PDM_Current.FiveVolt_Amps", (float)s_PDM_Current_FiveVolt_Amps);
#endif
#ifdef RX_WHEEL
    // Wheel_Temp_Front
    daqser::set("Wheel_Temp_Front.Wheel_Temp_FrontL1", (float)s_Wheel_Temp_Front_Wheel_Temp_FrontL1);
    daqser::set("Wheel_Temp_Front.Wheel_Temp_FrontL2", (float)s_Wheel_Temp_Front_Wheel_Temp_FrontL2);
    daqser::set("Wheel_Temp_Front.Wheel_Temp_FrontR1", (float)s_Wheel_Temp_Front_Wheel_Temp_FrontR1);
    daqser::set("Wheel_Temp_Front.Wheel_Temp_FrontR2", (float)s_Wheel_Temp_Front_Wheel_Temp_FrontR2);
    // Wheel_Speed_Front
    daqser::set("Wheel_Speed_Front.Wheel_Speed_FrontL", (float)s_Wheel_Speed_Front_Wheel_Speed_FrontL);
    daqser::set("Wheel_Speed_Front.Wheel_Speed_FrontR", (float)s_Wheel_Speed_Front_Wheel_Speed_FrontR);
    // Wheel_Temp_Back
    daqser::set("Wheel_Temp_Back.Wheel_Temp_BackL1", (float)s_Wheel_Temp_Back_Wheel_Temp_BackL1);
    daqser::set("Wheel_Temp_Back.Wheel_Temp_BackL2", (float)s_Wheel_Temp_Back_Wheel_Temp_BackL2);
    daqser::set("Wheel_Temp_Back.Wheel_Temp_BackR1", (float)s_Wheel_Temp_Back_Wheel_Temp_BackR1);
    daqser::set("Wheel_Temp_Back.Wheel_Temp_BackR2", (float)s_Wheel_Temp_Back_Wheel_Temp_BackR2);
#endif
#ifdef RX_COOLANT
    // Coolant_Temp_Message
    daqser::set("Coolant_Temp_Message.Coolant_Temp", (float)s_Coolant_Temp_Message_Coolant_Temp);
    // Coolant_Flow_Message
    daqser::set("Coolant_Flow_Message.Coolant_Flow", (float)s_Coolant_Flow_Message_Coolant_Flow);
#endif
#ifdef RX_SHUTDOWN
    // Shutdown_Status
    daqser::set("Shutdown_Status.Voltage_Sag", (bool)s_Shutdown_Status_Voltage_Sag);
#endif
#ifdef RX_ETC
    // Throttle_tx
    daqser::set("Throttle_tx.Throttle_percent", (float)s_Throttle_tx_Throttle_percent);
    daqser::set("Throttle_tx.Throttle_active", (bool)s_Throttle_tx_Throttle_active);
    // Brake_tx
    daqser::set("Brake_tx.Brake_pedal", (bool)s_Brake_tx_Brake_pedal);
#endif
#ifdef RX_VCU
    // Drive_Status
    daqser::set("Drive_Status.Drive_State", (bool)s_Drive_Status_Drive_State);
#endif
#ifdef RX_SUSPENSION
    // Sus_Pots
    daqser::set("Sus_Pots.Sus_Front", (float)s_Sus_Pots_Sus_Front);
#endif

    }

    void tickCAN()
    {
        g_timerGroup.Tick(millis());
        g_canBus.Tick();
    }

}

#endif // !NATIVE

#endif // __DAQSER_CAN_H__