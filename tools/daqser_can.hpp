#ifndef __DAQSER_CAN_H__
#define __DAQSER_CAN_H__
#ifndef NATIVE

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

    MakeSignedCANSignal(int8_t, 0, 8, 1, 0) exampleSignal{}; // one byte

    // IMD Signals
    MakeSignedCANSignal(float, 0, 16, 1e-05, 0.0) s_transmit_resistance{};
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_transmit_status{};
    // BMS_Voltages_0 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_0{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_1{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_2{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_3{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_4{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_5{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_6{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_0{};
    // BMS_Voltages_1 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_7{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_8{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_9{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_10{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_11{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_12{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_13{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_1{};
    // BMS_Voltages_2 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_14{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_15{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_16{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_17{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_18{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_19{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_20{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_2{};
    // BMS_Voltages_3 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_21{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_22{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_23{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_24{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_25{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_26{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_27{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_3{};
    // BMS_Voltages_4 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_28{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_29{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_30{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_31{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_32{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_33{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_34{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_4{};
    // BMS_Voltages_5 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_35{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_36{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_37{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_38{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_39{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_40{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_41{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_5{};
    // BMS_Voltages_6 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_42{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_43{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_44{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_45{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_46{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_47{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_48{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_6{};
    // BMS_Voltages_7 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_49{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_50{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_51{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_52{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_53{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_54{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_55{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_7{};
    // BMS_Voltages_8 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_56{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_57{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_58{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_59{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_60{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_61{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_62{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_8{};
    // BMS_Voltages_9 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_63{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_64{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_65{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_66{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_67{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_68{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_69{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_9{};
    // BMS_Voltages_10 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_70{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_71{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_72{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_73{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_74{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_75{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_76{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_110{};
    // BMS_Voltages_11 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_77{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_78{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_79{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_80{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_81{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_82{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_83{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_211{};
    // BMS_Voltages_12 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_84{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_85{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_86{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_87{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_88{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_89{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_90{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_212{};
    // BMS_Voltages_13 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_91{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_92{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_93{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_94{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_95{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_96{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_97{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_213{};
    // BMS_Voltages_14 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_98{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_99{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_100{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_101{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_102{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_103{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_104{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_214{};
    // BMS_Voltages_15 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_105{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_106{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_107{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_108{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_109{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_110{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_111{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_115{};
    // BMS_Voltages_16 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_112{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_113{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_114{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_115{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_116{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_117{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_118{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_216{};
    // BMS_Voltages_17 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_119{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_120{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_121{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_122{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_123{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_124{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_125{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_217{};
    // BMS_Voltages_18 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_126{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_127{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_128{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_129{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_130{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_131{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_132{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_218{};
    // BMS_Voltages_19 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_Cell_V_133{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_Cell_V_134{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_Cell_V_135{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Cell_V_136{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Cell_V_137{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_Cell_V_138{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_Cell_V_139{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_Cell_OCV_Offset_219{};
    // BMS_Temperatures_0 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_0{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_1{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_2{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_3{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_4{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_5{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_6{};
    // BMS_Temperatures_1 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_7{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_8{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_9{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_10{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_11{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_12{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_13{};
    // BMS_Temperatures_2 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_14{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_15{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_16{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_17{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_18{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_19{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_20{};
    // BMS_Temperatures_3 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_21{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_22{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_23{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_24{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_25{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_26{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_27{};
    // BMS_Temperatures_4 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_28{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_29{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_30{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_31{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_32{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_33{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_34{};
    // BMS_Temperatures_5 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_35{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_36{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_37{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_38{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_39{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_40{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_41{};
    // BMS_Temperatures_6 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_42{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_43{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_44{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_45{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_46{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_47{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_48{};
    // BMS_Temperatures_7 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_49{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_50{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_51{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_52{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_53{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_54{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_55{};
    // BMS_Temperatures_8 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_56{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_57{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_58{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_59{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_60{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_61{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_62{};
    // BMS_Temperatures_9 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_63{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_64{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_65{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_66{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_67{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_68{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_69{};
    // BMS_Temperatures_10 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_70{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_71{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_72{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_73{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_74{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_75{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_76{};
    // BMS_Temperatures_11 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_77{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_78{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_79{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_80{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_81{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_82{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_83{};
    // BMS_Temperatures_12 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_84{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_85{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_86{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_87{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_88{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_89{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_90{};
    // BMS_Temperatures_13 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_91{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_92{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_93{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_94{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_95{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_96{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_97{};
    // BMS_Temperatures_14 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_98{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_99{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_100{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_101{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_102{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_103{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_104{};
    // BMS_Temperatures_15 Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, -40.0) s_Cell_T_105{};
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Cell_T_106{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Cell_T_107{};
    MakeSignedCANSignal(bool, 24, 8, 1.0, -40.0) s_Cell_T_108{};
    MakeSignedCANSignal(bool, 32, 8, 1.0, -40.0) s_Cell_T_109{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Cell_T_110{};
    MakeSignedCANSignal(bool, 48, 8, 1.0, -40.0) s_Cell_T_111{};
    // BMS_SOE Signals
    MakeSignedCANSignal(float, 0, 12, 0.1, 0.0) s_Max_Discharge_Current{};
    MakeSignedCANSignal(float, 12, 12, 0.1, 0.0) s_Max_Regen_Current{};
    MakeSignedCANSignal(float, 24, 16, 0.01, 0.0) s_Battery_Voltage{};
    MakeSignedCANSignal(bool, 40, 8, 1.0, -40.0) s_Battery_Temperature{};
    MakeSignedCANSignal(float, 48, 16, 0.01, 0.0) s_Battery_Current{};
    // BMS_Faults Signals
    MakeSignedCANSignal(bool, 0, 1, 1.0, 0.0) s_Fault_Summary{};
    MakeSignedCANSignal(bool, 1, 1, 1.0, 0.0) s_Undervoltage_Fault{};
    MakeSignedCANSignal(bool, 2, 1, 1.0, 0.0) s_Overvoltage_Fault{};
    MakeSignedCANSignal(bool, 3, 1, 1.0, 0.0) s_Undertemperature_Fault{};
    MakeSignedCANSignal(bool, 4, 1, 1.0, 0.0) s_Overtemperature_Fault{};
    MakeSignedCANSignal(bool, 5, 1, 1.0, 0.0) s_Overcurrent_Fault{};
    MakeSignedCANSignal(bool, 6, 1, 1.0, 0.0) s_External_Kill_Fault{};
    MakeSignedCANSignal(bool, 7, 1, 1.0, 0.0) s_Open_Wire_Fault{};
    // BMS_Status Signals
    MakeSignedCANSignal(bool, 8, 8, 1.0, -40.0) s_Max_Cell_Temp{};
    MakeSignedCANSignal(bool, 16, 8, 1.0, -40.0) s_Min_Cell_Temp{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_Max_Cell_Voltage{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_Min_Cell_Voltage{};
    MakeSignedCANSignal(bool, 40, 8, 0.5, 0.0) s_BMS_SOC{};
    // PDM_Current_Sensing Signals
    MakeSignedCANSignal(double, 0, 32, 0.001, 0.0) s_Unreg_A{};
    MakeSignedCANSignal(double, 32, 32, 0.001, 0.0) s_FiveVolt_A{};
    // Wheel_Message Signals
    MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) s_Wheel_Temp{};
    MakeSignedCANSignal(float, 16, 16, 0.01, 0.0) s_Wheel_Speed{};
    // Shutdown_Status Signals
    MakeSignedCANSignal(bool, 0, 1, 1.0, 0.0) s_Voltage_Sag{};
    // Shutdown_1 Signals
    MakeSignedCANSignal(bool, 1, 1, 1.0, 0.0) s_Voltage_Sag{};
    // Shutdown_2 Signals
    MakeSignedCANSignal(bool, 2, 1, 1.0, 0.0) s_Voltage_Sag{};
    // Shutdown_3 Signals
    MakeSignedCANSignal(bool, 3, 1, 1.0, 0.0) s_Voltage_Sag{};
    // Shutdown_4 Signals
    MakeSignedCANSignal(bool, 4, 1, 1.0, 0.0) s_Voltage_Sag{};
    // Shutdown_5 Signals
    MakeSignedCANSignal(bool, 5, 1, 1.0, 0.0) s_Voltage_Sag{};
    // Shutdown_6 Signals
    MakeSignedCANSignal(bool, 6, 1, 1.0, 0.0) s_Voltage_Sag{};
    // throttle_tx Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_Throttle_percent{};
    MakeSignedCANSignal(bool, 9, 8, 1.0, 0.0) s_Throttle_active{};
    // brake_tx Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_Brake_pedal{};
    // Drive_Status Signals
    MakeSignedCANSignal(bool, 0, 8, 1.0, 0.0) s_Drive_State{};


    // auto generated messages!

    // IMD
    CANRXMessage<2> m_IMD { 0x300, [](){}, s_transmit_resistance, s_transmit_status };
    // BMS_Voltages_0
    CANRXMessage<8> m_BMS_Voltages_0 { 0x200, [](){}, s_Cell_V_0, s_Cell_V_1, s_Cell_V_2, s_Cell_V_3, s_Cell_V_4, s_Cell_V_5, s_Cell_V_6, s_Cell_OCV_Offset_0 };
    // BMS_Voltages_1
    CANRXMessage<8> m_BMS_Voltages_1 { 0x201, [](){}, s_Cell_V_7, s_Cell_V_8, s_Cell_V_9, s_Cell_V_10, s_Cell_V_11, s_Cell_V_12, s_Cell_V_13, s_Cell_OCV_Offset_1 };
    // BMS_Voltages_2
    CANRXMessage<8> m_BMS_Voltages_2 { 0x202, [](){}, s_Cell_V_14, s_Cell_V_15, s_Cell_V_16, s_Cell_V_17, s_Cell_V_18, s_Cell_V_19, s_Cell_V_20, s_Cell_OCV_Offset_2 };
    // BMS_Voltages_3
    CANRXMessage<8> m_BMS_Voltages_3 { 0x203, [](){}, s_Cell_V_21, s_Cell_V_22, s_Cell_V_23, s_Cell_V_24, s_Cell_V_25, s_Cell_V_26, s_Cell_V_27, s_Cell_OCV_Offset_3 };
    // BMS_Voltages_4
    CANRXMessage<8> m_BMS_Voltages_4 { 0x204, [](){}, s_Cell_V_28, s_Cell_V_29, s_Cell_V_30, s_Cell_V_31, s_Cell_V_32, s_Cell_V_33, s_Cell_V_34, s_Cell_OCV_Offset_4 };
    // BMS_Voltages_5
    CANRXMessage<8> m_BMS_Voltages_5 { 0x205, [](){}, s_Cell_V_35, s_Cell_V_36, s_Cell_V_37, s_Cell_V_38, s_Cell_V_39, s_Cell_V_40, s_Cell_V_41, s_Cell_OCV_Offset_5 };
    // BMS_Voltages_6
    CANRXMessage<8> m_BMS_Voltages_6 { 0x206, [](){}, s_Cell_V_42, s_Cell_V_43, s_Cell_V_44, s_Cell_V_45, s_Cell_V_46, s_Cell_V_47, s_Cell_V_48, s_Cell_OCV_Offset_6 };
    // BMS_Voltages_7
    CANRXMessage<8> m_BMS_Voltages_7 { 0x207, [](){}, s_Cell_V_49, s_Cell_V_50, s_Cell_V_51, s_Cell_V_52, s_Cell_V_53, s_Cell_V_54, s_Cell_V_55, s_Cell_OCV_Offset_7 };
    // BMS_Voltages_8
    CANRXMessage<8> m_BMS_Voltages_8 { 0x208, [](){}, s_Cell_V_56, s_Cell_V_57, s_Cell_V_58, s_Cell_V_59, s_Cell_V_60, s_Cell_V_61, s_Cell_V_62, s_Cell_OCV_Offset_8 };
    // BMS_Voltages_9
    CANRXMessage<8> m_BMS_Voltages_9 { 0x209, [](){}, s_Cell_V_63, s_Cell_V_64, s_Cell_V_65, s_Cell_V_66, s_Cell_V_67, s_Cell_V_68, s_Cell_V_69, s_Cell_OCV_Offset_9 };
    // BMS_Voltages_10
    CANRXMessage<8> m_BMS_Voltages_10 { 0x20a, [](){}, s_Cell_V_70, s_Cell_V_71, s_Cell_V_72, s_Cell_V_73, s_Cell_V_74, s_Cell_V_75, s_Cell_V_76, s_Cell_OCV_Offset_110 };
    // BMS_Voltages_11
    CANRXMessage<8> m_BMS_Voltages_11 { 0x20b, [](){}, s_Cell_V_77, s_Cell_V_78, s_Cell_V_79, s_Cell_V_80, s_Cell_V_81, s_Cell_V_82, s_Cell_V_83, s_Cell_OCV_Offset_211 };
    // BMS_Voltages_12
    CANRXMessage<8> m_BMS_Voltages_12 { 0x20c, [](){}, s_Cell_V_84, s_Cell_V_85, s_Cell_V_86, s_Cell_V_87, s_Cell_V_88, s_Cell_V_89, s_Cell_V_90, s_Cell_OCV_Offset_212 };
    // BMS_Voltages_13
    CANRXMessage<8> m_BMS_Voltages_13 { 0x20d, [](){}, s_Cell_V_91, s_Cell_V_92, s_Cell_V_93, s_Cell_V_94, s_Cell_V_95, s_Cell_V_96, s_Cell_V_97, s_Cell_OCV_Offset_213 };
    // BMS_Voltages_14
    CANRXMessage<8> m_BMS_Voltages_14 { 0x20e, [](){}, s_Cell_V_98, s_Cell_V_99, s_Cell_V_100, s_Cell_V_101, s_Cell_V_102, s_Cell_V_103, s_Cell_V_104, s_Cell_OCV_Offset_214 };
    // BMS_Voltages_15
    CANRXMessage<8> m_BMS_Voltages_15 { 0x20f, [](){}, s_Cell_V_105, s_Cell_V_106, s_Cell_V_107, s_Cell_V_108, s_Cell_V_109, s_Cell_V_110, s_Cell_V_111, s_Cell_OCV_Offset_115 };
    // BMS_Voltages_16
    CANRXMessage<8> m_BMS_Voltages_16 { 0x210, [](){}, s_Cell_V_112, s_Cell_V_113, s_Cell_V_114, s_Cell_V_115, s_Cell_V_116, s_Cell_V_117, s_Cell_V_118, s_Cell_OCV_Offset_216 };
    // BMS_Voltages_17
    CANRXMessage<8> m_BMS_Voltages_17 { 0x211, [](){}, s_Cell_V_119, s_Cell_V_120, s_Cell_V_121, s_Cell_V_122, s_Cell_V_123, s_Cell_V_124, s_Cell_V_125, s_Cell_OCV_Offset_217 };
    // BMS_Voltages_18
    CANRXMessage<8> m_BMS_Voltages_18 { 0x212, [](){}, s_Cell_V_126, s_Cell_V_127, s_Cell_V_128, s_Cell_V_129, s_Cell_V_130, s_Cell_V_131, s_Cell_V_132, s_Cell_OCV_Offset_218 };
    // BMS_Voltages_19
    CANRXMessage<8> m_BMS_Voltages_19 { 0x213, [](){}, s_Cell_V_133, s_Cell_V_134, s_Cell_V_135, s_Cell_V_136, s_Cell_V_137, s_Cell_V_138, s_Cell_V_139, s_Cell_OCV_Offset_219 };
    // BMS_Temperatures_0
    CANRXMessage<7> m_BMS_Temperatures_0 { 0x220, [](){}, s_Cell_T_0, s_Cell_T_1, s_Cell_T_2, s_Cell_T_3, s_Cell_T_4, s_Cell_T_5, s_Cell_T_6 };
    // BMS_Temperatures_1
    CANRXMessage<7> m_BMS_Temperatures_1 { 0x221, [](){}, s_Cell_T_7, s_Cell_T_8, s_Cell_T_9, s_Cell_T_10, s_Cell_T_11, s_Cell_T_12, s_Cell_T_13 };
    // BMS_Temperatures_2
    CANRXMessage<7> m_BMS_Temperatures_2 { 0x222, [](){}, s_Cell_T_14, s_Cell_T_15, s_Cell_T_16, s_Cell_T_17, s_Cell_T_18, s_Cell_T_19, s_Cell_T_20 };
    // BMS_Temperatures_3
    CANRXMessage<7> m_BMS_Temperatures_3 { 0x223, [](){}, s_Cell_T_21, s_Cell_T_22, s_Cell_T_23, s_Cell_T_24, s_Cell_T_25, s_Cell_T_26, s_Cell_T_27 };
    // BMS_Temperatures_4
    CANRXMessage<7> m_BMS_Temperatures_4 { 0x224, [](){}, s_Cell_T_28, s_Cell_T_29, s_Cell_T_30, s_Cell_T_31, s_Cell_T_32, s_Cell_T_33, s_Cell_T_34 };
    // BMS_Temperatures_5
    CANRXMessage<7> m_BMS_Temperatures_5 { 0x225, [](){}, s_Cell_T_35, s_Cell_T_36, s_Cell_T_37, s_Cell_T_38, s_Cell_T_39, s_Cell_T_40, s_Cell_T_41 };
    // BMS_Temperatures_6
    CANRXMessage<7> m_BMS_Temperatures_6 { 0x226, [](){}, s_Cell_T_42, s_Cell_T_43, s_Cell_T_44, s_Cell_T_45, s_Cell_T_46, s_Cell_T_47, s_Cell_T_48 };
    // BMS_Temperatures_7
    CANRXMessage<7> m_BMS_Temperatures_7 { 0x227, [](){}, s_Cell_T_49, s_Cell_T_50, s_Cell_T_51, s_Cell_T_52, s_Cell_T_53, s_Cell_T_54, s_Cell_T_55 };
    // BMS_Temperatures_8
    CANRXMessage<7> m_BMS_Temperatures_8 { 0x228, [](){}, s_Cell_T_56, s_Cell_T_57, s_Cell_T_58, s_Cell_T_59, s_Cell_T_60, s_Cell_T_61, s_Cell_T_62 };
    // BMS_Temperatures_9
    CANRXMessage<7> m_BMS_Temperatures_9 { 0x229, [](){}, s_Cell_T_63, s_Cell_T_64, s_Cell_T_65, s_Cell_T_66, s_Cell_T_67, s_Cell_T_68, s_Cell_T_69 };
    // BMS_Temperatures_10
    CANRXMessage<7> m_BMS_Temperatures_10 { 0x22a, [](){}, s_Cell_T_70, s_Cell_T_71, s_Cell_T_72, s_Cell_T_73, s_Cell_T_74, s_Cell_T_75, s_Cell_T_76 };
    // BMS_Temperatures_11
    CANRXMessage<7> m_BMS_Temperatures_11 { 0x22b, [](){}, s_Cell_T_77, s_Cell_T_78, s_Cell_T_79, s_Cell_T_80, s_Cell_T_81, s_Cell_T_82, s_Cell_T_83 };
    // BMS_Temperatures_12
    CANRXMessage<7> m_BMS_Temperatures_12 { 0x22c, [](){}, s_Cell_T_84, s_Cell_T_85, s_Cell_T_86, s_Cell_T_87, s_Cell_T_88, s_Cell_T_89, s_Cell_T_90 };
    // BMS_Temperatures_13
    CANRXMessage<7> m_BMS_Temperatures_13 { 0x22d, [](){}, s_Cell_T_91, s_Cell_T_92, s_Cell_T_93, s_Cell_T_94, s_Cell_T_95, s_Cell_T_96, s_Cell_T_97 };
    // BMS_Temperatures_14
    CANRXMessage<7> m_BMS_Temperatures_14 { 0x22e, [](){}, s_Cell_T_98, s_Cell_T_99, s_Cell_T_100, s_Cell_T_101, s_Cell_T_102, s_Cell_T_103, s_Cell_T_104 };
    // BMS_Temperatures_15
    CANRXMessage<7> m_BMS_Temperatures_15 { 0x22f, [](){}, s_Cell_T_105, s_Cell_T_106, s_Cell_T_107, s_Cell_T_108, s_Cell_T_109, s_Cell_T_110, s_Cell_T_111 };
    // BMS_SOE
    CANRXMessage<5> m_BMS_SOE { 0x240, [](){}, s_Max_Discharge_Current, s_Max_Regen_Current, s_Battery_Voltage, s_Battery_Temperature, s_Battery_Current };
    // BMS_Faults
    CANRXMessage<8> m_BMS_Faults { 0x250, [](){}, s_Fault_Summary, s_Undervoltage_Fault, s_Overvoltage_Fault, s_Undertemperature_Fault, s_Overtemperature_Fault, s_Overcurrent_Fault, s_External_Kill_Fault, s_Open_Wire_Fault };
    // BMS_Status
    CANRXMessage<5> m_BMS_Status { 0x241, [](){}, s_Max_Cell_Temp, s_Min_Cell_Temp, s_Max_Cell_Voltage, s_Min_Cell_Voltage, s_BMS_SOC };
    // PDM_Current_Sensing
    CANRXMessage<2> m_PDM_Current_Sensing { 0x?, [](){}, s_Unreg_A, s_FiveVolt_A };
    // Wheel_Message
    CANRXMessage<2> m_Wheel_Message { 0x410, [](){}, s_Wheel_Temp, s_Wheel_Speed };
    // Shutdown_Status
    CANRXMessage<1> m_Shutdown_Status { 0x310, [](){}, s_Voltage_Sag };
    // Shutdown_1
    CANRXMessage<1> m_Shutdown_1 { 0x310, [](){}, s_Voltage_Sag };
    // Shutdown_2
    CANRXMessage<1> m_Shutdown_2 { 0x310, [](){}, s_Voltage_Sag };
    // Shutdown_3
    CANRXMessage<1> m_Shutdown_3 { 0x310, [](){}, s_Voltage_Sag };
    // Shutdown_4
    CANRXMessage<1> m_Shutdown_4 { 0x310, [](){}, s_Voltage_Sag };
    // Shutdown_5
    CANRXMessage<1> m_Shutdown_5 { 0x310, [](){}, s_Voltage_Sag };
    // Shutdown_6
    CANRXMessage<1> m_Shutdown_6 { 0x310, [](){}, s_Voltage_Sag };
    // throttle_tx
    CANRXMessage<2> m_throttle_tx { 0x"010", [](){}, s_Throttle_percent, s_Throttle_active };
    // brake_tx
    CANRXMessage<1> m_brake_tx { 0x"011", [](){}, s_Brake_pedal };
    // Drive_Status
    CANRXMessage<1> m_Drive_Status { 0x"000", [](){}, s_Drive_State };


    // functions to update daqser

    std::map<std::string, std::function<void()>> g_signalMap = {
        {"exampleSignal", []()
         {
             daqser::set("exampleSignal", (std::int8_t)exampleSignal);
         }},

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

#endif // !NATIVE

#endif // __DAQSER_CAN_H__