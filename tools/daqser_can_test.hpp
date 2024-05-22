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
#ifdef RX_IMD
    // IMD Signals
    MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) s_IMD_transmit_resistance{};
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_IMD_transmit_status{};
#endif
#ifdef RX_BMS
    // BMS_Voltages_0 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_0_Cell_V_0{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_0_Cell_V_1{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_0_Cell_V_2{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_0_Cell_V_3{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_0_Cell_V_4{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_0_Cell_V_5{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_0_Cell_V_6{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_0_Cell_OCV_Offset_0{};
    // BMS_Voltages_1 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_7{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_8{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_9{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_10{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_11{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_12{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_13{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_1_Cell_OCV_Offset_1{};
    // BMS_Voltages_2 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_14{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_15{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_16{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_17{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_18{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_19{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_20{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_2_Cell_OCV_Offset_2{};
    // BMS_Voltages_3 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_21{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_22{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_23{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_24{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_25{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_26{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_27{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_3_Cell_OCV_Offset_3{};
    // BMS_Voltages_4 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_28{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_29{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_30{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_31{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_32{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_33{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_34{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_4_Cell_OCV_Offset_4{};
    // BMS_Voltages_5 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_35{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_36{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_37{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_38{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_39{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_40{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_41{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_5_Cell_OCV_Offset_5{};
    // BMS_Voltages_6 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_42{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_43{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_44{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_45{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_46{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_47{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_48{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_6_Cell_OCV_Offset_6{};
    // BMS_Voltages_7 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_49{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_50{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_51{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_52{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_53{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_54{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_55{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_7_Cell_OCV_Offset_7{};
    // BMS_Voltages_8 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_56{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_57{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_58{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_59{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_60{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_61{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_62{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_8_Cell_OCV_Offset_8{};
    // BMS_Voltages_9 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_63{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_64{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_65{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_66{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_67{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_68{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_69{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_9_Cell_OCV_Offset_9{};
    // BMS_Voltages_10 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_70{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_71{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_72{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_73{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_74{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_75{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_76{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_10_Cell_OCV_Offset_110{};
    // BMS_Voltages_11 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_77{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_78{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_79{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_80{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_81{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_82{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_83{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_11_Cell_OCV_Offset_211{};
    // BMS_Voltages_12 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_84{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_85{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_86{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_87{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_88{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_89{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_90{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_12_Cell_OCV_Offset_212{};
    // BMS_Voltages_13 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_91{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_92{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_93{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_94{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_95{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_96{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_97{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_13_Cell_OCV_Offset_213{};
    // BMS_Voltages_14 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_98{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_99{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_100{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_101{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_102{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_103{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_104{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_14_Cell_OCV_Offset_214{};
    // BMS_Voltages_15 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_105{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_106{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_107{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_108{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_109{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_110{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_111{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_15_Cell_OCV_Offset_115{};
    // BMS_Voltages_16 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_112{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_113{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_114{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_115{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_116{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_117{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_118{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_16_Cell_OCV_Offset_216{};
    // BMS_Voltages_17 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_119{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_120{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_121{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_122{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_123{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_124{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_125{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_17_Cell_OCV_Offset_217{};
    // BMS_Voltages_18 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_126{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_127{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_128{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_129{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_130{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_131{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_132{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_18_Cell_OCV_Offset_218{};
    // BMS_Voltages_19 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_133{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_134{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_135{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_136{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_137{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_138{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_139{};
    MakeSignedCANSignal(bool, 56, 8, 0.01, 0.0) s_BMS_Voltages_19_Cell_OCV_Offset_219{};
    // BMS_Temperatures_0 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_0_Cell_T_0{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_0_Cell_T_1{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_0_Cell_T_2{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_0_Cell_T_3{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_0_Cell_T_4{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_0_Cell_T_5{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_0_Cell_T_6{};
    // BMS_Temperatures_1 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_1_Cell_T_7{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_1_Cell_T_8{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_1_Cell_T_9{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_1_Cell_T_10{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_1_Cell_T_11{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_1_Cell_T_12{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_1_Cell_T_13{};
    // BMS_Temperatures_2 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_2_Cell_T_14{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_2_Cell_T_15{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_2_Cell_T_16{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_2_Cell_T_17{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_2_Cell_T_18{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_2_Cell_T_19{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_2_Cell_T_20{};
    // BMS_Temperatures_3 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_3_Cell_T_21{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_3_Cell_T_22{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_3_Cell_T_23{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_3_Cell_T_24{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_3_Cell_T_25{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_3_Cell_T_26{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_3_Cell_T_27{};
    // BMS_Temperatures_4 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_4_Cell_T_28{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_4_Cell_T_29{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_4_Cell_T_30{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_4_Cell_T_31{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_4_Cell_T_32{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_4_Cell_T_33{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_4_Cell_T_34{};
    // BMS_Temperatures_5 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_5_Cell_T_35{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_5_Cell_T_36{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_5_Cell_T_37{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_5_Cell_T_38{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_5_Cell_T_39{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_5_Cell_T_40{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_5_Cell_T_41{};
    // BMS_Temperatures_6 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_6_Cell_T_42{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_6_Cell_T_43{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_6_Cell_T_44{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_6_Cell_T_45{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_6_Cell_T_46{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_6_Cell_T_47{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_6_Cell_T_48{};
    // BMS_Temperatures_7 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_7_Cell_T_49{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_7_Cell_T_50{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_7_Cell_T_51{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_7_Cell_T_52{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_7_Cell_T_53{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_7_Cell_T_54{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_7_Cell_T_55{};
    // BMS_Temperatures_8 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_8_Cell_T_56{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_8_Cell_T_57{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_8_Cell_T_58{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_8_Cell_T_59{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_8_Cell_T_60{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_8_Cell_T_61{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_8_Cell_T_62{};
    // BMS_Temperatures_9 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_9_Cell_T_63{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_9_Cell_T_64{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_9_Cell_T_65{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_9_Cell_T_66{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_9_Cell_T_67{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_9_Cell_T_68{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_9_Cell_T_69{};
    // BMS_Temperatures_10 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_10_Cell_T_70{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_10_Cell_T_71{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_10_Cell_T_72{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_10_Cell_T_73{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_10_Cell_T_74{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_10_Cell_T_75{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_10_Cell_T_76{};
    // BMS_Temperatures_11 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_11_Cell_T_77{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_11_Cell_T_78{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_11_Cell_T_79{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_11_Cell_T_80{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_11_Cell_T_81{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_11_Cell_T_82{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_11_Cell_T_83{};
    // BMS_Temperatures_12 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_12_Cell_T_84{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_12_Cell_T_85{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_12_Cell_T_86{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_12_Cell_T_87{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_12_Cell_T_88{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_12_Cell_T_89{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_12_Cell_T_90{};
    // BMS_Temperatures_13 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_13_Cell_T_91{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_13_Cell_T_92{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_13_Cell_T_93{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_13_Cell_T_94{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_13_Cell_T_95{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_13_Cell_T_96{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_13_Cell_T_97{};
    // BMS_Temperatures_14 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_14_Cell_T_98{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_14_Cell_T_99{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_14_Cell_T_100{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_14_Cell_T_101{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_14_Cell_T_102{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_14_Cell_T_103{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_14_Cell_T_104{};
    // BMS_Temperatures_15 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_BMS_Temperatures_15_Cell_T_105{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Temperatures_15_Cell_T_106{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Temperatures_15_Cell_T_107{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_BMS_Temperatures_15_Cell_T_108{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_BMS_Temperatures_15_Cell_T_109{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_Temperatures_15_Cell_T_110{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_BMS_Temperatures_15_Cell_T_111{};
    // BMS_SOE Signals
    MakeSignedCANSignal(float, 0, 12, 0.1, 0.0) s_BMS_SOE_Max_Discharge_Current{};
    MakeSignedCANSignal(float, 12, 12, 0.1, 0.0) s_BMS_SOE_Max_Regen_Current{};
    MakeSignedCANSignal(float, 24, 16, 0.01, 0.0) s_BMS_SOE_Battery_Voltage{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_BMS_SOE_Battery_Temperature{};
    MakeSignedCANSignal(float, 48, 16, 0.01, 0.0) s_BMS_SOE_Battery_Current{};
    // BMS_Faults Signals
    MakeSignedCANSignal(bool, 0, 1, 1.0, 0.0) s_BMS_Faults_Fault_Summary{};
    MakeSignedCANSignal(bool, 1, 1, 1.0, 0.0) s_BMS_Faults_Undervoltage_Fault{};
    MakeSignedCANSignal(bool, 2, 1, 1.0, 0.0) s_BMS_Faults_Overvoltage_Fault{};
    MakeSignedCANSignal(bool, 3, 1, 1.0, 0.0) s_BMS_Faults_Undertemperature_Fault{};
    MakeSignedCANSignal(bool, 4, 1, 1.0, 0.0) s_BMS_Faults_Overtemperature_Fault{};
    MakeSignedCANSignal(bool, 5, 1, 1.0, 0.0) s_BMS_Faults_Overcurrent_Fault{};
    MakeSignedCANSignal(bool, 6, 1, 1.0, 0.0) s_BMS_Faults_External_Kill_Fault{};
    MakeSignedCANSignal(bool, 7, 1, 1.0, 0.0) s_BMS_Faults_Open_Wire_Fault{};
    // BMS_Status Signals
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_BMS_Status_Max_Cell_Temp{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_BMS_Status_Min_Cell_Temp{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Status_Max_Cell_Voltage{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Status_Min_Cell_Voltage{};
    MakeSignedCANSignal(bool, 40, 8, 0.5, 0.0) s_BMS_Status_BMS_SOC{};
#endif
#ifdef RX_PDM
    // PDM_Current_Sensing Signals
    MakeSignedCANSignal(double, 0, 32, 0.01, 0.0) s_PDM_Current_Sensing_Unreg_A{};
    MakeSignedCANSignal(double, 32, 32, 0.01, 0.0) s_PDM_Current_Sensing_FiveVolt_A{};
#endif
#ifdef RX_WHEEL
    // Wheel_Message Signals
    MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) s_Wheel_Message_Wheel_Temp{};
    MakeSignedCANSignal(float, 16, 16, 0.01, 0.0) s_Wheel_Message_Wheel_Speed{};
#endif
#ifdef RX_SHUTDOWN
    // Shutdown_Status Signals
    MakeSignedCANSignal(bool, 0, 1, 1.0, 0.0) s_Shutdown_Status_Voltage_Sag{};
    // Shutdown_1 Signals
    MakeSignedCANSignal(bool, 1, 1, 1.0, 0.0) s_Shutdown_1_Voltage_Sag{};
    // Shutdown_2 Signals
    MakeSignedCANSignal(bool, 2, 1, 1.0, 0.0) s_Shutdown_2_Voltage_Sag{};
    // Shutdown_3 Signals
    MakeSignedCANSignal(bool, 3, 1, 1.0, 0.0) s_Shutdown_3_Voltage_Sag{};
    // Shutdown_4 Signals
    MakeSignedCANSignal(bool, 4, 1, 1.0, 0.0) s_Shutdown_4_Voltage_Sag{};
    // Shutdown_5 Signals
    MakeSignedCANSignal(bool, 5, 1, 1.0, 0.0) s_Shutdown_5_Voltage_Sag{};
    // Shutdown_6 Signals
    MakeSignedCANSignal(bool, 6, 1, 1.0, 0.0) s_Shutdown_6_Voltage_Sag{};
#endif
#ifdef RX_ETC
    // throttle_tx Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_throttle_tx_Throttle_percent{};
    MakeSignedCANSignal(bool, 9, 8, 1.0, 0.0) s_throttle_tx_Throttle_active{};
    // brake_tx Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_brake_tx_Brake_pedal{};
#endif
#ifdef RX_VCU
    // Drive_Status Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_Drive_Status_Drive_State{};
#endif


    // auto generated messages!
#ifdef RX_IMD
    // IMD
    CANTXMessage<2> m_IMD { g_canBus, 0x300, 3, 100, g_timerGroup, s_IMD_transmit_resistance, s_IMD_transmit_status };
#endif
#ifdef RX_BMS
    // BMS_Voltages_0
    CANTXMessage<8> m_BMS_Voltages_0 { g_canBus, 0x200, 8, 100, g_timerGroup, s_BMS_Voltages_0_Cell_V_0, s_BMS_Voltages_0_Cell_V_1, s_BMS_Voltages_0_Cell_V_2, s_BMS_Voltages_0_Cell_V_3, s_BMS_Voltages_0_Cell_V_4, s_BMS_Voltages_0_Cell_V_5, s_BMS_Voltages_0_Cell_V_6, s_BMS_Voltages_0_Cell_OCV_Offset_0 };
    // BMS_Voltages_1
    CANTXMessage<8> m_BMS_Voltages_1 { g_canBus, 0x201, 8, 100, g_timerGroup, s_BMS_Voltages_1_Cell_V_7, s_BMS_Voltages_1_Cell_V_8, s_BMS_Voltages_1_Cell_V_9, s_BMS_Voltages_1_Cell_V_10, s_BMS_Voltages_1_Cell_V_11, s_BMS_Voltages_1_Cell_V_12, s_BMS_Voltages_1_Cell_V_13, s_BMS_Voltages_1_Cell_OCV_Offset_1 };
    // BMS_Voltages_2
    CANTXMessage<8> m_BMS_Voltages_2 { g_canBus, 0x202, 8, 100, g_timerGroup, s_BMS_Voltages_2_Cell_V_14, s_BMS_Voltages_2_Cell_V_15, s_BMS_Voltages_2_Cell_V_16, s_BMS_Voltages_2_Cell_V_17, s_BMS_Voltages_2_Cell_V_18, s_BMS_Voltages_2_Cell_V_19, s_BMS_Voltages_2_Cell_V_20, s_BMS_Voltages_2_Cell_OCV_Offset_2 };
    // BMS_Voltages_3
    CANTXMessage<8> m_BMS_Voltages_3 { g_canBus, 0x203, 8, 100, g_timerGroup, s_BMS_Voltages_3_Cell_V_21, s_BMS_Voltages_3_Cell_V_22, s_BMS_Voltages_3_Cell_V_23, s_BMS_Voltages_3_Cell_V_24, s_BMS_Voltages_3_Cell_V_25, s_BMS_Voltages_3_Cell_V_26, s_BMS_Voltages_3_Cell_V_27, s_BMS_Voltages_3_Cell_OCV_Offset_3 };
    // BMS_Voltages_4
    CANTXMessage<8> m_BMS_Voltages_4 { g_canBus, 0x204, 8, 100, g_timerGroup, s_BMS_Voltages_4_Cell_V_28, s_BMS_Voltages_4_Cell_V_29, s_BMS_Voltages_4_Cell_V_30, s_BMS_Voltages_4_Cell_V_31, s_BMS_Voltages_4_Cell_V_32, s_BMS_Voltages_4_Cell_V_33, s_BMS_Voltages_4_Cell_V_34, s_BMS_Voltages_4_Cell_OCV_Offset_4 };
    // BMS_Voltages_5
    CANTXMessage<8> m_BMS_Voltages_5 { g_canBus, 0x205, 8, 100, g_timerGroup, s_BMS_Voltages_5_Cell_V_35, s_BMS_Voltages_5_Cell_V_36, s_BMS_Voltages_5_Cell_V_37, s_BMS_Voltages_5_Cell_V_38, s_BMS_Voltages_5_Cell_V_39, s_BMS_Voltages_5_Cell_V_40, s_BMS_Voltages_5_Cell_V_41, s_BMS_Voltages_5_Cell_OCV_Offset_5 };
    // BMS_Voltages_6
    CANTXMessage<8> m_BMS_Voltages_6 { g_canBus, 0x206, 8, 100, g_timerGroup, s_BMS_Voltages_6_Cell_V_42, s_BMS_Voltages_6_Cell_V_43, s_BMS_Voltages_6_Cell_V_44, s_BMS_Voltages_6_Cell_V_45, s_BMS_Voltages_6_Cell_V_46, s_BMS_Voltages_6_Cell_V_47, s_BMS_Voltages_6_Cell_V_48, s_BMS_Voltages_6_Cell_OCV_Offset_6 };
    // BMS_Voltages_7
    CANTXMessage<8> m_BMS_Voltages_7 { g_canBus, 0x207, 8, 100, g_timerGroup, s_BMS_Voltages_7_Cell_V_49, s_BMS_Voltages_7_Cell_V_50, s_BMS_Voltages_7_Cell_V_51, s_BMS_Voltages_7_Cell_V_52, s_BMS_Voltages_7_Cell_V_53, s_BMS_Voltages_7_Cell_V_54, s_BMS_Voltages_7_Cell_V_55, s_BMS_Voltages_7_Cell_OCV_Offset_7 };
    // BMS_Voltages_8
    CANTXMessage<8> m_BMS_Voltages_8 { g_canBus, 0x208, 8, 100, g_timerGroup, s_BMS_Voltages_8_Cell_V_56, s_BMS_Voltages_8_Cell_V_57, s_BMS_Voltages_8_Cell_V_58, s_BMS_Voltages_8_Cell_V_59, s_BMS_Voltages_8_Cell_V_60, s_BMS_Voltages_8_Cell_V_61, s_BMS_Voltages_8_Cell_V_62, s_BMS_Voltages_8_Cell_OCV_Offset_8 };
    // BMS_Voltages_9
    CANTXMessage<8> m_BMS_Voltages_9 { g_canBus, 0x209, 8, 100, g_timerGroup, s_BMS_Voltages_9_Cell_V_63, s_BMS_Voltages_9_Cell_V_64, s_BMS_Voltages_9_Cell_V_65, s_BMS_Voltages_9_Cell_V_66, s_BMS_Voltages_9_Cell_V_67, s_BMS_Voltages_9_Cell_V_68, s_BMS_Voltages_9_Cell_V_69, s_BMS_Voltages_9_Cell_OCV_Offset_9 };
    // BMS_Voltages_10
    CANTXMessage<8> m_BMS_Voltages_10 { g_canBus, 0x20a, 8, 100, g_timerGroup, s_BMS_Voltages_10_Cell_V_70, s_BMS_Voltages_10_Cell_V_71, s_BMS_Voltages_10_Cell_V_72, s_BMS_Voltages_10_Cell_V_73, s_BMS_Voltages_10_Cell_V_74, s_BMS_Voltages_10_Cell_V_75, s_BMS_Voltages_10_Cell_V_76, s_BMS_Voltages_10_Cell_OCV_Offset_110 };
    // BMS_Voltages_11
    CANTXMessage<8> m_BMS_Voltages_11 { g_canBus, 0x20b, 8, 100, g_timerGroup, s_BMS_Voltages_11_Cell_V_77, s_BMS_Voltages_11_Cell_V_78, s_BMS_Voltages_11_Cell_V_79, s_BMS_Voltages_11_Cell_V_80, s_BMS_Voltages_11_Cell_V_81, s_BMS_Voltages_11_Cell_V_82, s_BMS_Voltages_11_Cell_V_83, s_BMS_Voltages_11_Cell_OCV_Offset_211 };
    // BMS_Voltages_12
    CANTXMessage<8> m_BMS_Voltages_12 { g_canBus, 0x20c, 8, 100, g_timerGroup, s_BMS_Voltages_12_Cell_V_84, s_BMS_Voltages_12_Cell_V_85, s_BMS_Voltages_12_Cell_V_86, s_BMS_Voltages_12_Cell_V_87, s_BMS_Voltages_12_Cell_V_88, s_BMS_Voltages_12_Cell_V_89, s_BMS_Voltages_12_Cell_V_90, s_BMS_Voltages_12_Cell_OCV_Offset_212 };
    // BMS_Voltages_13
    CANTXMessage<8> m_BMS_Voltages_13 { g_canBus, 0x20d, 8, 100, g_timerGroup, s_BMS_Voltages_13_Cell_V_91, s_BMS_Voltages_13_Cell_V_92, s_BMS_Voltages_13_Cell_V_93, s_BMS_Voltages_13_Cell_V_94, s_BMS_Voltages_13_Cell_V_95, s_BMS_Voltages_13_Cell_V_96, s_BMS_Voltages_13_Cell_V_97, s_BMS_Voltages_13_Cell_OCV_Offset_213 };
    // BMS_Voltages_14
    CANTXMessage<8> m_BMS_Voltages_14 { g_canBus, 0x20e, 8, 100, g_timerGroup, s_BMS_Voltages_14_Cell_V_98, s_BMS_Voltages_14_Cell_V_99, s_BMS_Voltages_14_Cell_V_100, s_BMS_Voltages_14_Cell_V_101, s_BMS_Voltages_14_Cell_V_102, s_BMS_Voltages_14_Cell_V_103, s_BMS_Voltages_14_Cell_V_104, s_BMS_Voltages_14_Cell_OCV_Offset_214 };
    // BMS_Voltages_15
    CANTXMessage<8> m_BMS_Voltages_15 { g_canBus, 0x20f, 8, 100, g_timerGroup, s_BMS_Voltages_15_Cell_V_105, s_BMS_Voltages_15_Cell_V_106, s_BMS_Voltages_15_Cell_V_107, s_BMS_Voltages_15_Cell_V_108, s_BMS_Voltages_15_Cell_V_109, s_BMS_Voltages_15_Cell_V_110, s_BMS_Voltages_15_Cell_V_111, s_BMS_Voltages_15_Cell_OCV_Offset_115 };
    // BMS_Voltages_16
    CANTXMessage<8> m_BMS_Voltages_16 { g_canBus, 0x210, 8, 100, g_timerGroup, s_BMS_Voltages_16_Cell_V_112, s_BMS_Voltages_16_Cell_V_113, s_BMS_Voltages_16_Cell_V_114, s_BMS_Voltages_16_Cell_V_115, s_BMS_Voltages_16_Cell_V_116, s_BMS_Voltages_16_Cell_V_117, s_BMS_Voltages_16_Cell_V_118, s_BMS_Voltages_16_Cell_OCV_Offset_216 };
    // BMS_Voltages_17
    CANTXMessage<8> m_BMS_Voltages_17 { g_canBus, 0x211, 8, 100, g_timerGroup, s_BMS_Voltages_17_Cell_V_119, s_BMS_Voltages_17_Cell_V_120, s_BMS_Voltages_17_Cell_V_121, s_BMS_Voltages_17_Cell_V_122, s_BMS_Voltages_17_Cell_V_123, s_BMS_Voltages_17_Cell_V_124, s_BMS_Voltages_17_Cell_V_125, s_BMS_Voltages_17_Cell_OCV_Offset_217 };
    // BMS_Voltages_18
    CANTXMessage<8> m_BMS_Voltages_18 { g_canBus, 0x212, 8, 100, g_timerGroup, s_BMS_Voltages_18_Cell_V_126, s_BMS_Voltages_18_Cell_V_127, s_BMS_Voltages_18_Cell_V_128, s_BMS_Voltages_18_Cell_V_129, s_BMS_Voltages_18_Cell_V_130, s_BMS_Voltages_18_Cell_V_131, s_BMS_Voltages_18_Cell_V_132, s_BMS_Voltages_18_Cell_OCV_Offset_218 };
    // BMS_Voltages_19
    CANTXMessage<8> m_BMS_Voltages_19 { g_canBus, 0x213, 8, 100, g_timerGroup, s_BMS_Voltages_19_Cell_V_133, s_BMS_Voltages_19_Cell_V_134, s_BMS_Voltages_19_Cell_V_135, s_BMS_Voltages_19_Cell_V_136, s_BMS_Voltages_19_Cell_V_137, s_BMS_Voltages_19_Cell_V_138, s_BMS_Voltages_19_Cell_V_139, s_BMS_Voltages_19_Cell_OCV_Offset_219 };
    // BMS_Temperatures_0
    CANTXMessage<7> m_BMS_Temperatures_0 { g_canBus, 0x220, 7, 100, g_timerGroup, s_BMS_Temperatures_0_Cell_T_0, s_BMS_Temperatures_0_Cell_T_1, s_BMS_Temperatures_0_Cell_T_2, s_BMS_Temperatures_0_Cell_T_3, s_BMS_Temperatures_0_Cell_T_4, s_BMS_Temperatures_0_Cell_T_5, s_BMS_Temperatures_0_Cell_T_6 };
    // BMS_Temperatures_1
    CANTXMessage<7> m_BMS_Temperatures_1 { g_canBus, 0x221, 7, 100, g_timerGroup, s_BMS_Temperatures_1_Cell_T_7, s_BMS_Temperatures_1_Cell_T_8, s_BMS_Temperatures_1_Cell_T_9, s_BMS_Temperatures_1_Cell_T_10, s_BMS_Temperatures_1_Cell_T_11, s_BMS_Temperatures_1_Cell_T_12, s_BMS_Temperatures_1_Cell_T_13 };
    // BMS_Temperatures_2
    CANTXMessage<7> m_BMS_Temperatures_2 { g_canBus, 0x222, 7, 100, g_timerGroup, s_BMS_Temperatures_2_Cell_T_14, s_BMS_Temperatures_2_Cell_T_15, s_BMS_Temperatures_2_Cell_T_16, s_BMS_Temperatures_2_Cell_T_17, s_BMS_Temperatures_2_Cell_T_18, s_BMS_Temperatures_2_Cell_T_19, s_BMS_Temperatures_2_Cell_T_20 };
    // BMS_Temperatures_3
    CANTXMessage<7> m_BMS_Temperatures_3 { g_canBus, 0x223, 7, 100, g_timerGroup, s_BMS_Temperatures_3_Cell_T_21, s_BMS_Temperatures_3_Cell_T_22, s_BMS_Temperatures_3_Cell_T_23, s_BMS_Temperatures_3_Cell_T_24, s_BMS_Temperatures_3_Cell_T_25, s_BMS_Temperatures_3_Cell_T_26, s_BMS_Temperatures_3_Cell_T_27 };
    // BMS_Temperatures_4
    CANTXMessage<7> m_BMS_Temperatures_4 { g_canBus, 0x224, 7, 100, g_timerGroup, s_BMS_Temperatures_4_Cell_T_28, s_BMS_Temperatures_4_Cell_T_29, s_BMS_Temperatures_4_Cell_T_30, s_BMS_Temperatures_4_Cell_T_31, s_BMS_Temperatures_4_Cell_T_32, s_BMS_Temperatures_4_Cell_T_33, s_BMS_Temperatures_4_Cell_T_34 };
    // BMS_Temperatures_5
    CANTXMessage<7> m_BMS_Temperatures_5 { g_canBus, 0x225, 7, 100, g_timerGroup, s_BMS_Temperatures_5_Cell_T_35, s_BMS_Temperatures_5_Cell_T_36, s_BMS_Temperatures_5_Cell_T_37, s_BMS_Temperatures_5_Cell_T_38, s_BMS_Temperatures_5_Cell_T_39, s_BMS_Temperatures_5_Cell_T_40, s_BMS_Temperatures_5_Cell_T_41 };
    // BMS_Temperatures_6
    CANTXMessage<7> m_BMS_Temperatures_6 { g_canBus, 0x226, 7, 100, g_timerGroup, s_BMS_Temperatures_6_Cell_T_42, s_BMS_Temperatures_6_Cell_T_43, s_BMS_Temperatures_6_Cell_T_44, s_BMS_Temperatures_6_Cell_T_45, s_BMS_Temperatures_6_Cell_T_46, s_BMS_Temperatures_6_Cell_T_47, s_BMS_Temperatures_6_Cell_T_48 };
    // BMS_Temperatures_7
    CANTXMessage<7> m_BMS_Temperatures_7 { g_canBus, 0x227, 7, 100, g_timerGroup, s_BMS_Temperatures_7_Cell_T_49, s_BMS_Temperatures_7_Cell_T_50, s_BMS_Temperatures_7_Cell_T_51, s_BMS_Temperatures_7_Cell_T_52, s_BMS_Temperatures_7_Cell_T_53, s_BMS_Temperatures_7_Cell_T_54, s_BMS_Temperatures_7_Cell_T_55 };
    // BMS_Temperatures_8
    CANTXMessage<7> m_BMS_Temperatures_8 { g_canBus, 0x228, 7, 100, g_timerGroup, s_BMS_Temperatures_8_Cell_T_56, s_BMS_Temperatures_8_Cell_T_57, s_BMS_Temperatures_8_Cell_T_58, s_BMS_Temperatures_8_Cell_T_59, s_BMS_Temperatures_8_Cell_T_60, s_BMS_Temperatures_8_Cell_T_61, s_BMS_Temperatures_8_Cell_T_62 };
    // BMS_Temperatures_9
    CANTXMessage<7> m_BMS_Temperatures_9 { g_canBus, 0x229, 7, 100, g_timerGroup, s_BMS_Temperatures_9_Cell_T_63, s_BMS_Temperatures_9_Cell_T_64, s_BMS_Temperatures_9_Cell_T_65, s_BMS_Temperatures_9_Cell_T_66, s_BMS_Temperatures_9_Cell_T_67, s_BMS_Temperatures_9_Cell_T_68, s_BMS_Temperatures_9_Cell_T_69 };
    // BMS_Temperatures_10
    CANTXMessage<7> m_BMS_Temperatures_10 { g_canBus, 0x22a, 7, 100, g_timerGroup, s_BMS_Temperatures_10_Cell_T_70, s_BMS_Temperatures_10_Cell_T_71, s_BMS_Temperatures_10_Cell_T_72, s_BMS_Temperatures_10_Cell_T_73, s_BMS_Temperatures_10_Cell_T_74, s_BMS_Temperatures_10_Cell_T_75, s_BMS_Temperatures_10_Cell_T_76 };
    // BMS_Temperatures_11
    CANTXMessage<7> m_BMS_Temperatures_11 { g_canBus, 0x22b, 7, 100, g_timerGroup, s_BMS_Temperatures_11_Cell_T_77, s_BMS_Temperatures_11_Cell_T_78, s_BMS_Temperatures_11_Cell_T_79, s_BMS_Temperatures_11_Cell_T_80, s_BMS_Temperatures_11_Cell_T_81, s_BMS_Temperatures_11_Cell_T_82, s_BMS_Temperatures_11_Cell_T_83 };
    // BMS_Temperatures_12
    CANTXMessage<7> m_BMS_Temperatures_12 { g_canBus, 0x22c, 7, 100, g_timerGroup, s_BMS_Temperatures_12_Cell_T_84, s_BMS_Temperatures_12_Cell_T_85, s_BMS_Temperatures_12_Cell_T_86, s_BMS_Temperatures_12_Cell_T_87, s_BMS_Temperatures_12_Cell_T_88, s_BMS_Temperatures_12_Cell_T_89, s_BMS_Temperatures_12_Cell_T_90 };
    // BMS_Temperatures_13
    CANTXMessage<7> m_BMS_Temperatures_13 { g_canBus, 0x22d, 7, 100, g_timerGroup, s_BMS_Temperatures_13_Cell_T_91, s_BMS_Temperatures_13_Cell_T_92, s_BMS_Temperatures_13_Cell_T_93, s_BMS_Temperatures_13_Cell_T_94, s_BMS_Temperatures_13_Cell_T_95, s_BMS_Temperatures_13_Cell_T_96, s_BMS_Temperatures_13_Cell_T_97 };
    // BMS_Temperatures_14
    CANTXMessage<7> m_BMS_Temperatures_14 { g_canBus, 0x22e, 7, 100, g_timerGroup, s_BMS_Temperatures_14_Cell_T_98, s_BMS_Temperatures_14_Cell_T_99, s_BMS_Temperatures_14_Cell_T_100, s_BMS_Temperatures_14_Cell_T_101, s_BMS_Temperatures_14_Cell_T_102, s_BMS_Temperatures_14_Cell_T_103, s_BMS_Temperatures_14_Cell_T_104 };
    // BMS_Temperatures_15
    CANTXMessage<7> m_BMS_Temperatures_15 { g_canBus, 0x22f, 7, 100, g_timerGroup, s_BMS_Temperatures_15_Cell_T_105, s_BMS_Temperatures_15_Cell_T_106, s_BMS_Temperatures_15_Cell_T_107, s_BMS_Temperatures_15_Cell_T_108, s_BMS_Temperatures_15_Cell_T_109, s_BMS_Temperatures_15_Cell_T_110, s_BMS_Temperatures_15_Cell_T_111 };
    // BMS_SOE
    CANTXMessage<5> m_BMS_SOE { g_canBus, 0x240, 8, 100, g_timerGroup, s_BMS_SOE_Max_Discharge_Current, s_BMS_SOE_Max_Regen_Current, s_BMS_SOE_Battery_Voltage, s_BMS_SOE_Battery_Temperature, s_BMS_SOE_Battery_Current };
    // BMS_Faults
    CANTXMessage<8> m_BMS_Faults { g_canBus, 0x250, 1, 100, g_timerGroup, s_BMS_Faults_Fault_Summary, s_BMS_Faults_Undervoltage_Fault, s_BMS_Faults_Overvoltage_Fault, s_BMS_Faults_Undertemperature_Fault, s_BMS_Faults_Overtemperature_Fault, s_BMS_Faults_Overcurrent_Fault, s_BMS_Faults_External_Kill_Fault, s_BMS_Faults_Open_Wire_Fault };
    // BMS_Status
    CANTXMessage<5> m_BMS_Status { g_canBus, 0x241, 5, 100, g_timerGroup, s_BMS_Status_Max_Cell_Temp, s_BMS_Status_Min_Cell_Temp, s_BMS_Status_Max_Cell_Voltage, s_BMS_Status_Min_Cell_Voltage, s_BMS_Status_BMS_SOC };
#endif
#ifdef RX_PDM
    // PDM_Current_Sensing
    CANTXMessage<2> m_PDM_Current_Sensing { g_canBus, 0x, 8, 100, g_timerGroup, s_PDM_Current_Sensing_Unreg_A, s_PDM_Current_Sensing_FiveVolt_A };
#endif
#ifdef RX_WHEEL
    // Wheel_Message
    CANTXMessage<2> m_Wheel_Message { g_canBus, 0x410, 4, 100, g_timerGroup, s_Wheel_Message_Wheel_Temp, s_Wheel_Message_Wheel_Speed };
#endif
#ifdef RX_SHUTDOWN
    // Shutdown_Status
    CANTXMessage<1> m_Shutdown_Status { g_canBus, 0x310, 0, 100, g_timerGroup, s_Shutdown_Status_Voltage_Sag };
    // Shutdown_1
    CANTXMessage<1> m_Shutdown_1 { g_canBus, 0x310, 0, 100, g_timerGroup, s_Shutdown_1_Voltage_Sag };
    // Shutdown_2
    CANTXMessage<1> m_Shutdown_2 { g_canBus, 0x310, 0, 100, g_timerGroup, s_Shutdown_2_Voltage_Sag };
    // Shutdown_3
    CANTXMessage<1> m_Shutdown_3 { g_canBus, 0x310, 0, 100, g_timerGroup, s_Shutdown_3_Voltage_Sag };
    // Shutdown_4
    CANTXMessage<1> m_Shutdown_4 { g_canBus, 0x310, 0, 100, g_timerGroup, s_Shutdown_4_Voltage_Sag };
    // Shutdown_5
    CANTXMessage<1> m_Shutdown_5 { g_canBus, 0x310, 0, 100, g_timerGroup, s_Shutdown_5_Voltage_Sag };
    // Shutdown_6
    CANTXMessage<1> m_Shutdown_6 { g_canBus, 0x310, 0, 100, g_timerGroup, s_Shutdown_6_Voltage_Sag };
#endif
#ifdef RX_ETC
    // throttle_tx
    CANTXMessage<2> m_throttle_tx { g_canBus, 0x010, 2, 100, g_timerGroup, s_throttle_tx_Throttle_percent, s_throttle_tx_Throttle_active };
    // brake_tx
    CANTXMessage<1> m_brake_tx { g_canBus, 0x011, 1, 100, g_timerGroup, s_brake_tx_Brake_pedal };
#endif
#ifdef RX_VCU
    // Drive_Status
    CANTXMessage<1> m_Drive_Status { g_canBus, 0x000, 1, 100, g_timerGroup, s_Drive_Status_Drive_State };
#endif


    void sendSignals()
    {
#ifdef RX_IMD
        // IMD
        s_IMD_transmit_resistance = (float)0;
        s_IMD_transmit_status = (bool)1;
#endif
#ifdef RX_BMS
        // BMS_Voltages_0
        s_BMS_Voltages_0_Cell_V_0 = (bool)2;
        s_BMS_Voltages_0_Cell_V_1 = (bool)3;
        s_BMS_Voltages_0_Cell_V_2 = (bool)4;
        s_BMS_Voltages_0_Cell_V_3 = (bool)5;
        s_BMS_Voltages_0_Cell_V_4 = (bool)6;
        s_BMS_Voltages_0_Cell_V_5 = (bool)7;
        s_BMS_Voltages_0_Cell_V_6 = (bool)8;
        s_BMS_Voltages_0_Cell_OCV_Offset_0 = (bool)9;
        // BMS_Voltages_1
        s_BMS_Voltages_1_Cell_V_7 = (bool)10;
        s_BMS_Voltages_1_Cell_V_8 = (bool)11;
        s_BMS_Voltages_1_Cell_V_9 = (bool)12;
        s_BMS_Voltages_1_Cell_V_10 = (bool)13;
        s_BMS_Voltages_1_Cell_V_11 = (bool)14;
        s_BMS_Voltages_1_Cell_V_12 = (bool)15;
        s_BMS_Voltages_1_Cell_V_13 = (bool)16;
        s_BMS_Voltages_1_Cell_OCV_Offset_1 = (bool)17;
        // BMS_Voltages_2
        s_BMS_Voltages_2_Cell_V_14 = (bool)18;
        s_BMS_Voltages_2_Cell_V_15 = (bool)19;
        s_BMS_Voltages_2_Cell_V_16 = (bool)20;
        s_BMS_Voltages_2_Cell_V_17 = (bool)21;
        s_BMS_Voltages_2_Cell_V_18 = (bool)22;
        s_BMS_Voltages_2_Cell_V_19 = (bool)23;
        s_BMS_Voltages_2_Cell_V_20 = (bool)24;
        s_BMS_Voltages_2_Cell_OCV_Offset_2 = (bool)25;
        // BMS_Voltages_3
        s_BMS_Voltages_3_Cell_V_21 = (bool)26;
        s_BMS_Voltages_3_Cell_V_22 = (bool)27;
        s_BMS_Voltages_3_Cell_V_23 = (bool)28;
        s_BMS_Voltages_3_Cell_V_24 = (bool)29;
        s_BMS_Voltages_3_Cell_V_25 = (bool)30;
        s_BMS_Voltages_3_Cell_V_26 = (bool)31;
        s_BMS_Voltages_3_Cell_V_27 = (bool)32;
        s_BMS_Voltages_3_Cell_OCV_Offset_3 = (bool)33;
        // BMS_Voltages_4
        s_BMS_Voltages_4_Cell_V_28 = (bool)34;
        s_BMS_Voltages_4_Cell_V_29 = (bool)35;
        s_BMS_Voltages_4_Cell_V_30 = (bool)36;
        s_BMS_Voltages_4_Cell_V_31 = (bool)37;
        s_BMS_Voltages_4_Cell_V_32 = (bool)38;
        s_BMS_Voltages_4_Cell_V_33 = (bool)39;
        s_BMS_Voltages_4_Cell_V_34 = (bool)40;
        s_BMS_Voltages_4_Cell_OCV_Offset_4 = (bool)41;
        // BMS_Voltages_5
        s_BMS_Voltages_5_Cell_V_35 = (bool)42;
        s_BMS_Voltages_5_Cell_V_36 = (bool)43;
        s_BMS_Voltages_5_Cell_V_37 = (bool)44;
        s_BMS_Voltages_5_Cell_V_38 = (bool)45;
        s_BMS_Voltages_5_Cell_V_39 = (bool)46;
        s_BMS_Voltages_5_Cell_V_40 = (bool)47;
        s_BMS_Voltages_5_Cell_V_41 = (bool)48;
        s_BMS_Voltages_5_Cell_OCV_Offset_5 = (bool)49;
        // BMS_Voltages_6
        s_BMS_Voltages_6_Cell_V_42 = (bool)50;
        s_BMS_Voltages_6_Cell_V_43 = (bool)51;
        s_BMS_Voltages_6_Cell_V_44 = (bool)52;
        s_BMS_Voltages_6_Cell_V_45 = (bool)53;
        s_BMS_Voltages_6_Cell_V_46 = (bool)54;
        s_BMS_Voltages_6_Cell_V_47 = (bool)55;
        s_BMS_Voltages_6_Cell_V_48 = (bool)56;
        s_BMS_Voltages_6_Cell_OCV_Offset_6 = (bool)57;
        // BMS_Voltages_7
        s_BMS_Voltages_7_Cell_V_49 = (bool)58;
        s_BMS_Voltages_7_Cell_V_50 = (bool)59;
        s_BMS_Voltages_7_Cell_V_51 = (bool)60;
        s_BMS_Voltages_7_Cell_V_52 = (bool)61;
        s_BMS_Voltages_7_Cell_V_53 = (bool)62;
        s_BMS_Voltages_7_Cell_V_54 = (bool)63;
        s_BMS_Voltages_7_Cell_V_55 = (bool)64;
        s_BMS_Voltages_7_Cell_OCV_Offset_7 = (bool)65;
        // BMS_Voltages_8
        s_BMS_Voltages_8_Cell_V_56 = (bool)66;
        s_BMS_Voltages_8_Cell_V_57 = (bool)67;
        s_BMS_Voltages_8_Cell_V_58 = (bool)68;
        s_BMS_Voltages_8_Cell_V_59 = (bool)69;
        s_BMS_Voltages_8_Cell_V_60 = (bool)70;
        s_BMS_Voltages_8_Cell_V_61 = (bool)71;
        s_BMS_Voltages_8_Cell_V_62 = (bool)72;
        s_BMS_Voltages_8_Cell_OCV_Offset_8 = (bool)73;
        // BMS_Voltages_9
        s_BMS_Voltages_9_Cell_V_63 = (bool)74;
        s_BMS_Voltages_9_Cell_V_64 = (bool)75;
        s_BMS_Voltages_9_Cell_V_65 = (bool)76;
        s_BMS_Voltages_9_Cell_V_66 = (bool)77;
        s_BMS_Voltages_9_Cell_V_67 = (bool)78;
        s_BMS_Voltages_9_Cell_V_68 = (bool)79;
        s_BMS_Voltages_9_Cell_V_69 = (bool)80;
        s_BMS_Voltages_9_Cell_OCV_Offset_9 = (bool)81;
        // BMS_Voltages_10
        s_BMS_Voltages_10_Cell_V_70 = (bool)82;
        s_BMS_Voltages_10_Cell_V_71 = (bool)83;
        s_BMS_Voltages_10_Cell_V_72 = (bool)84;
        s_BMS_Voltages_10_Cell_V_73 = (bool)85;
        s_BMS_Voltages_10_Cell_V_74 = (bool)86;
        s_BMS_Voltages_10_Cell_V_75 = (bool)87;
        s_BMS_Voltages_10_Cell_V_76 = (bool)88;
        s_BMS_Voltages_10_Cell_OCV_Offset_110 = (bool)89;
        // BMS_Voltages_11
        s_BMS_Voltages_11_Cell_V_77 = (bool)90;
        s_BMS_Voltages_11_Cell_V_78 = (bool)91;
        s_BMS_Voltages_11_Cell_V_79 = (bool)92;
        s_BMS_Voltages_11_Cell_V_80 = (bool)93;
        s_BMS_Voltages_11_Cell_V_81 = (bool)94;
        s_BMS_Voltages_11_Cell_V_82 = (bool)95;
        s_BMS_Voltages_11_Cell_V_83 = (bool)96;
        s_BMS_Voltages_11_Cell_OCV_Offset_211 = (bool)97;
        // BMS_Voltages_12
        s_BMS_Voltages_12_Cell_V_84 = (bool)98;
        s_BMS_Voltages_12_Cell_V_85 = (bool)99;
        s_BMS_Voltages_12_Cell_V_86 = (bool)100;
        s_BMS_Voltages_12_Cell_V_87 = (bool)101;
        s_BMS_Voltages_12_Cell_V_88 = (bool)102;
        s_BMS_Voltages_12_Cell_V_89 = (bool)103;
        s_BMS_Voltages_12_Cell_V_90 = (bool)104;
        s_BMS_Voltages_12_Cell_OCV_Offset_212 = (bool)105;
        // BMS_Voltages_13
        s_BMS_Voltages_13_Cell_V_91 = (bool)106;
        s_BMS_Voltages_13_Cell_V_92 = (bool)107;
        s_BMS_Voltages_13_Cell_V_93 = (bool)108;
        s_BMS_Voltages_13_Cell_V_94 = (bool)109;
        s_BMS_Voltages_13_Cell_V_95 = (bool)110;
        s_BMS_Voltages_13_Cell_V_96 = (bool)111;
        s_BMS_Voltages_13_Cell_V_97 = (bool)112;
        s_BMS_Voltages_13_Cell_OCV_Offset_213 = (bool)113;
        // BMS_Voltages_14
        s_BMS_Voltages_14_Cell_V_98 = (bool)114;
        s_BMS_Voltages_14_Cell_V_99 = (bool)115;
        s_BMS_Voltages_14_Cell_V_100 = (bool)116;
        s_BMS_Voltages_14_Cell_V_101 = (bool)117;
        s_BMS_Voltages_14_Cell_V_102 = (bool)118;
        s_BMS_Voltages_14_Cell_V_103 = (bool)119;
        s_BMS_Voltages_14_Cell_V_104 = (bool)120;
        s_BMS_Voltages_14_Cell_OCV_Offset_214 = (bool)121;
        // BMS_Voltages_15
        s_BMS_Voltages_15_Cell_V_105 = (bool)122;
        s_BMS_Voltages_15_Cell_V_106 = (bool)123;
        s_BMS_Voltages_15_Cell_V_107 = (bool)124;
        s_BMS_Voltages_15_Cell_V_108 = (bool)125;
        s_BMS_Voltages_15_Cell_V_109 = (bool)126;
        s_BMS_Voltages_15_Cell_V_110 = (bool)127;
        s_BMS_Voltages_15_Cell_V_111 = (bool)128;
        s_BMS_Voltages_15_Cell_OCV_Offset_115 = (bool)129;
        // BMS_Voltages_16
        s_BMS_Voltages_16_Cell_V_112 = (bool)130;
        s_BMS_Voltages_16_Cell_V_113 = (bool)131;
        s_BMS_Voltages_16_Cell_V_114 = (bool)132;
        s_BMS_Voltages_16_Cell_V_115 = (bool)133;
        s_BMS_Voltages_16_Cell_V_116 = (bool)134;
        s_BMS_Voltages_16_Cell_V_117 = (bool)135;
        s_BMS_Voltages_16_Cell_V_118 = (bool)136;
        s_BMS_Voltages_16_Cell_OCV_Offset_216 = (bool)137;
        // BMS_Voltages_17
        s_BMS_Voltages_17_Cell_V_119 = (bool)138;
        s_BMS_Voltages_17_Cell_V_120 = (bool)139;
        s_BMS_Voltages_17_Cell_V_121 = (bool)140;
        s_BMS_Voltages_17_Cell_V_122 = (bool)141;
        s_BMS_Voltages_17_Cell_V_123 = (bool)142;
        s_BMS_Voltages_17_Cell_V_124 = (bool)143;
        s_BMS_Voltages_17_Cell_V_125 = (bool)144;
        s_BMS_Voltages_17_Cell_OCV_Offset_217 = (bool)145;
        // BMS_Voltages_18
        s_BMS_Voltages_18_Cell_V_126 = (bool)146;
        s_BMS_Voltages_18_Cell_V_127 = (bool)147;
        s_BMS_Voltages_18_Cell_V_128 = (bool)148;
        s_BMS_Voltages_18_Cell_V_129 = (bool)149;
        s_BMS_Voltages_18_Cell_V_130 = (bool)150;
        s_BMS_Voltages_18_Cell_V_131 = (bool)151;
        s_BMS_Voltages_18_Cell_V_132 = (bool)152;
        s_BMS_Voltages_18_Cell_OCV_Offset_218 = (bool)153;
        // BMS_Voltages_19
        s_BMS_Voltages_19_Cell_V_133 = (bool)154;
        s_BMS_Voltages_19_Cell_V_134 = (bool)155;
        s_BMS_Voltages_19_Cell_V_135 = (bool)156;
        s_BMS_Voltages_19_Cell_V_136 = (bool)157;
        s_BMS_Voltages_19_Cell_V_137 = (bool)158;
        s_BMS_Voltages_19_Cell_V_138 = (bool)159;
        s_BMS_Voltages_19_Cell_V_139 = (bool)160;
        s_BMS_Voltages_19_Cell_OCV_Offset_219 = (bool)161;
        // BMS_Temperatures_0
        s_BMS_Temperatures_0_Cell_T_0 = (bool)162;
        s_BMS_Temperatures_0_Cell_T_1 = (bool)163;
        s_BMS_Temperatures_0_Cell_T_2 = (bool)164;
        s_BMS_Temperatures_0_Cell_T_3 = (bool)165;
        s_BMS_Temperatures_0_Cell_T_4 = (bool)166;
        s_BMS_Temperatures_0_Cell_T_5 = (bool)167;
        s_BMS_Temperatures_0_Cell_T_6 = (bool)168;
        // BMS_Temperatures_1
        s_BMS_Temperatures_1_Cell_T_7 = (bool)169;
        s_BMS_Temperatures_1_Cell_T_8 = (bool)170;
        s_BMS_Temperatures_1_Cell_T_9 = (bool)171;
        s_BMS_Temperatures_1_Cell_T_10 = (bool)172;
        s_BMS_Temperatures_1_Cell_T_11 = (bool)173;
        s_BMS_Temperatures_1_Cell_T_12 = (bool)174;
        s_BMS_Temperatures_1_Cell_T_13 = (bool)175;
        // BMS_Temperatures_2
        s_BMS_Temperatures_2_Cell_T_14 = (bool)176;
        s_BMS_Temperatures_2_Cell_T_15 = (bool)177;
        s_BMS_Temperatures_2_Cell_T_16 = (bool)178;
        s_BMS_Temperatures_2_Cell_T_17 = (bool)179;
        s_BMS_Temperatures_2_Cell_T_18 = (bool)180;
        s_BMS_Temperatures_2_Cell_T_19 = (bool)181;
        s_BMS_Temperatures_2_Cell_T_20 = (bool)182;
        // BMS_Temperatures_3
        s_BMS_Temperatures_3_Cell_T_21 = (bool)183;
        s_BMS_Temperatures_3_Cell_T_22 = (bool)184;
        s_BMS_Temperatures_3_Cell_T_23 = (bool)185;
        s_BMS_Temperatures_3_Cell_T_24 = (bool)186;
        s_BMS_Temperatures_3_Cell_T_25 = (bool)187;
        s_BMS_Temperatures_3_Cell_T_26 = (bool)188;
        s_BMS_Temperatures_3_Cell_T_27 = (bool)189;
        // BMS_Temperatures_4
        s_BMS_Temperatures_4_Cell_T_28 = (bool)190;
        s_BMS_Temperatures_4_Cell_T_29 = (bool)191;
        s_BMS_Temperatures_4_Cell_T_30 = (bool)192;
        s_BMS_Temperatures_4_Cell_T_31 = (bool)193;
        s_BMS_Temperatures_4_Cell_T_32 = (bool)194;
        s_BMS_Temperatures_4_Cell_T_33 = (bool)195;
        s_BMS_Temperatures_4_Cell_T_34 = (bool)196;
        // BMS_Temperatures_5
        s_BMS_Temperatures_5_Cell_T_35 = (bool)197;
        s_BMS_Temperatures_5_Cell_T_36 = (bool)198;
        s_BMS_Temperatures_5_Cell_T_37 = (bool)199;
        s_BMS_Temperatures_5_Cell_T_38 = (bool)200;
        s_BMS_Temperatures_5_Cell_T_39 = (bool)201;
        s_BMS_Temperatures_5_Cell_T_40 = (bool)202;
        s_BMS_Temperatures_5_Cell_T_41 = (bool)203;
        // BMS_Temperatures_6
        s_BMS_Temperatures_6_Cell_T_42 = (bool)204;
        s_BMS_Temperatures_6_Cell_T_43 = (bool)205;
        s_BMS_Temperatures_6_Cell_T_44 = (bool)206;
        s_BMS_Temperatures_6_Cell_T_45 = (bool)207;
        s_BMS_Temperatures_6_Cell_T_46 = (bool)208;
        s_BMS_Temperatures_6_Cell_T_47 = (bool)209;
        s_BMS_Temperatures_6_Cell_T_48 = (bool)210;
        // BMS_Temperatures_7
        s_BMS_Temperatures_7_Cell_T_49 = (bool)211;
        s_BMS_Temperatures_7_Cell_T_50 = (bool)212;
        s_BMS_Temperatures_7_Cell_T_51 = (bool)213;
        s_BMS_Temperatures_7_Cell_T_52 = (bool)214;
        s_BMS_Temperatures_7_Cell_T_53 = (bool)215;
        s_BMS_Temperatures_7_Cell_T_54 = (bool)216;
        s_BMS_Temperatures_7_Cell_T_55 = (bool)217;
        // BMS_Temperatures_8
        s_BMS_Temperatures_8_Cell_T_56 = (bool)218;
        s_BMS_Temperatures_8_Cell_T_57 = (bool)219;
        s_BMS_Temperatures_8_Cell_T_58 = (bool)220;
        s_BMS_Temperatures_8_Cell_T_59 = (bool)221;
        s_BMS_Temperatures_8_Cell_T_60 = (bool)222;
        s_BMS_Temperatures_8_Cell_T_61 = (bool)223;
        s_BMS_Temperatures_8_Cell_T_62 = (bool)224;
        // BMS_Temperatures_9
        s_BMS_Temperatures_9_Cell_T_63 = (bool)225;
        s_BMS_Temperatures_9_Cell_T_64 = (bool)226;
        s_BMS_Temperatures_9_Cell_T_65 = (bool)227;
        s_BMS_Temperatures_9_Cell_T_66 = (bool)228;
        s_BMS_Temperatures_9_Cell_T_67 = (bool)229;
        s_BMS_Temperatures_9_Cell_T_68 = (bool)230;
        s_BMS_Temperatures_9_Cell_T_69 = (bool)231;
        // BMS_Temperatures_10
        s_BMS_Temperatures_10_Cell_T_70 = (bool)232;
        s_BMS_Temperatures_10_Cell_T_71 = (bool)233;
        s_BMS_Temperatures_10_Cell_T_72 = (bool)234;
        s_BMS_Temperatures_10_Cell_T_73 = (bool)235;
        s_BMS_Temperatures_10_Cell_T_74 = (bool)236;
        s_BMS_Temperatures_10_Cell_T_75 = (bool)237;
        s_BMS_Temperatures_10_Cell_T_76 = (bool)238;
        // BMS_Temperatures_11
        s_BMS_Temperatures_11_Cell_T_77 = (bool)239;
        s_BMS_Temperatures_11_Cell_T_78 = (bool)240;
        s_BMS_Temperatures_11_Cell_T_79 = (bool)241;
        s_BMS_Temperatures_11_Cell_T_80 = (bool)242;
        s_BMS_Temperatures_11_Cell_T_81 = (bool)243;
        s_BMS_Temperatures_11_Cell_T_82 = (bool)244;
        s_BMS_Temperatures_11_Cell_T_83 = (bool)245;
        // BMS_Temperatures_12
        s_BMS_Temperatures_12_Cell_T_84 = (bool)246;
        s_BMS_Temperatures_12_Cell_T_85 = (bool)247;
        s_BMS_Temperatures_12_Cell_T_86 = (bool)248;
        s_BMS_Temperatures_12_Cell_T_87 = (bool)249;
        s_BMS_Temperatures_12_Cell_T_88 = (bool)250;
        s_BMS_Temperatures_12_Cell_T_89 = (bool)251;
        s_BMS_Temperatures_12_Cell_T_90 = (bool)252;
        // BMS_Temperatures_13
        s_BMS_Temperatures_13_Cell_T_91 = (bool)253;
        s_BMS_Temperatures_13_Cell_T_92 = (bool)254;
        s_BMS_Temperatures_13_Cell_T_93 = (bool)255;
        s_BMS_Temperatures_13_Cell_T_94 = (bool)256;
        s_BMS_Temperatures_13_Cell_T_95 = (bool)257;
        s_BMS_Temperatures_13_Cell_T_96 = (bool)258;
        s_BMS_Temperatures_13_Cell_T_97 = (bool)259;
        // BMS_Temperatures_14
        s_BMS_Temperatures_14_Cell_T_98 = (bool)260;
        s_BMS_Temperatures_14_Cell_T_99 = (bool)261;
        s_BMS_Temperatures_14_Cell_T_100 = (bool)262;
        s_BMS_Temperatures_14_Cell_T_101 = (bool)263;
        s_BMS_Temperatures_14_Cell_T_102 = (bool)264;
        s_BMS_Temperatures_14_Cell_T_103 = (bool)265;
        s_BMS_Temperatures_14_Cell_T_104 = (bool)266;
        // BMS_Temperatures_15
        s_BMS_Temperatures_15_Cell_T_105 = (bool)267;
        s_BMS_Temperatures_15_Cell_T_106 = (bool)268;
        s_BMS_Temperatures_15_Cell_T_107 = (bool)269;
        s_BMS_Temperatures_15_Cell_T_108 = (bool)270;
        s_BMS_Temperatures_15_Cell_T_109 = (bool)271;
        s_BMS_Temperatures_15_Cell_T_110 = (bool)272;
        s_BMS_Temperatures_15_Cell_T_111 = (bool)273;
        // BMS_SOE
        s_BMS_SOE_Max_Discharge_Current = (float)274;
        s_BMS_SOE_Max_Regen_Current = (float)275;
        s_BMS_SOE_Battery_Voltage = (float)276;
        s_BMS_SOE_Battery_Temperature = (bool)277;
        s_BMS_SOE_Battery_Current = (float)278;
        // BMS_Faults
        s_BMS_Faults_Fault_Summary = (bool)279;
        s_BMS_Faults_Undervoltage_Fault = (bool)280;
        s_BMS_Faults_Overvoltage_Fault = (bool)281;
        s_BMS_Faults_Undertemperature_Fault = (bool)282;
        s_BMS_Faults_Overtemperature_Fault = (bool)283;
        s_BMS_Faults_Overcurrent_Fault = (bool)284;
        s_BMS_Faults_External_Kill_Fault = (bool)285;
        s_BMS_Faults_Open_Wire_Fault = (bool)286;
        // BMS_Status
        s_BMS_Status_Max_Cell_Temp = (bool)287;
        s_BMS_Status_Min_Cell_Temp = (bool)288;
        s_BMS_Status_Max_Cell_Voltage = (bool)289;
        s_BMS_Status_Min_Cell_Voltage = (bool)290;
        s_BMS_Status_BMS_SOC = (bool)291;
#endif
#ifdef RX_PDM
        // PDM_Current_Sensing
        s_PDM_Current_Sensing_Unreg_A = (double)292;
        s_PDM_Current_Sensing_FiveVolt_A = (double)293;
#endif
#ifdef RX_WHEEL
        // Wheel_Message
        s_Wheel_Message_Wheel_Temp = (float)294;
        s_Wheel_Message_Wheel_Speed = (float)295;
#endif
#ifdef RX_SHUTDOWN
        // Shutdown_Status
        s_Shutdown_Status_Voltage_Sag = (bool)296;
        // Shutdown_1
        s_Shutdown_1_Voltage_Sag = (bool)297;
        // Shutdown_2
        s_Shutdown_2_Voltage_Sag = (bool)298;
        // Shutdown_3
        s_Shutdown_3_Voltage_Sag = (bool)299;
        // Shutdown_4
        s_Shutdown_4_Voltage_Sag = (bool)300;
        // Shutdown_5
        s_Shutdown_5_Voltage_Sag = (bool)301;
        // Shutdown_6
        s_Shutdown_6_Voltage_Sag = (bool)302;
#endif
#ifdef RX_ETC
        // throttle_tx
        s_throttle_tx_Throttle_percent = (bool)303;
        s_throttle_tx_Throttle_active = (bool)304;
        // brake_tx
        s_brake_tx_Brake_pedal = (bool)305;
#endif
#ifdef RX_VCU
        // Drive_Status
        s_Drive_Status_Drive_State = (bool)306;
#endif

    }

}

#endif // !NATIVE

#endif // __DAQSER_CAN_H__