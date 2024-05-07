#ifndef __DAQSER_CAN_H__
#define __DAQSER_CAN_H__
#ifndef NATIVE

#include <CAN.h>
#include <map>
#include <vector>

#include <frame.hpp>
#include <daqser.hpp>

namespace daqser
{
    VirtualTimerGroup g_timerGroup;
    CAN g_canBus{};

    // auto generated signals!

#ifdef RX_IMD
    // IMD Signals
    MakeSignedCANSignal(float, 0, 16, 1e-05, 0.0) s_IMD_transmit_resistance{};
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
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_0_Cell_OCV_Offset_0{};
    // BMS_Voltages_1 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_7{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_8{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_9{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_10{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_11{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_12{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_1_Cell_V_13{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_1_Cell_OCV_Offset_1{};
    // BMS_Voltages_2 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_14{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_15{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_16{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_17{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_18{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_19{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_2_Cell_V_20{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_2_Cell_OCV_Offset_2{};
    // BMS_Voltages_3 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_21{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_22{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_23{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_24{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_25{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_26{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_3_Cell_V_27{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_3_Cell_OCV_Offset_3{};
    // BMS_Voltages_4 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_28{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_29{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_30{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_31{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_32{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_33{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_4_Cell_V_34{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_4_Cell_OCV_Offset_4{};
    // BMS_Voltages_5 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_35{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_36{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_37{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_38{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_39{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_40{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_5_Cell_V_41{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_5_Cell_OCV_Offset_5{};
    // BMS_Voltages_6 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_42{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_43{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_44{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_45{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_46{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_47{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_6_Cell_V_48{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_6_Cell_OCV_Offset_6{};
    // BMS_Voltages_7 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_49{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_50{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_51{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_52{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_53{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_54{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_7_Cell_V_55{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_7_Cell_OCV_Offset_7{};
    // BMS_Voltages_8 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_56{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_57{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_58{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_59{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_60{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_61{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_8_Cell_V_62{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_8_Cell_OCV_Offset_8{};
    // BMS_Voltages_9 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_63{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_64{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_65{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_66{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_67{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_68{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_9_Cell_V_69{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_9_Cell_OCV_Offset_9{};
    // BMS_Voltages_10 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_70{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_71{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_72{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_73{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_74{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_75{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_10_Cell_V_76{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_10_Cell_OCV_Offset_110{};
    // BMS_Voltages_11 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_77{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_78{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_79{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_80{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_81{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_82{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_11_Cell_V_83{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_11_Cell_OCV_Offset_211{};
    // BMS_Voltages_12 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_84{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_85{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_86{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_87{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_88{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_89{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_12_Cell_V_90{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_12_Cell_OCV_Offset_212{};
    // BMS_Voltages_13 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_91{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_92{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_93{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_94{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_95{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_96{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_13_Cell_V_97{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_13_Cell_OCV_Offset_213{};
    // BMS_Voltages_14 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_98{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_99{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_100{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_101{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_102{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_103{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_14_Cell_V_104{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_14_Cell_OCV_Offset_214{};
    // BMS_Voltages_15 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_105{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_106{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_107{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_108{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_109{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_110{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_15_Cell_V_111{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_15_Cell_OCV_Offset_115{};
    // BMS_Voltages_16 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_112{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_113{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_114{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_115{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_116{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_117{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_16_Cell_V_118{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_16_Cell_OCV_Offset_216{};
    // BMS_Voltages_17 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_119{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_120{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_121{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_122{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_123{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_124{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_17_Cell_V_125{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_17_Cell_OCV_Offset_217{};
    // BMS_Voltages_18 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_126{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_127{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_128{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_129{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_130{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_131{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_18_Cell_V_132{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_18_Cell_OCV_Offset_218{};
    // BMS_Voltages_19 Signals
    MakeSignedCANSignal(bool, 0, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_133{};
    MakeSignedCANSignal(bool, 8, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_134{};
    MakeSignedCANSignal(bool, 16, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_135{};
    MakeSignedCANSignal(bool, 24, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_136{};
    MakeSignedCANSignal(bool, 32, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_137{};
    MakeSignedCANSignal(bool, 40, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_138{};
    MakeSignedCANSignal(bool, 48, 8, 0.012, 2.0) s_BMS_Voltages_19_Cell_V_139{};
    MakeSignedCANSignal(bool, 56, 8, 0.004, 0.0) s_BMS_Voltages_19_Cell_OCV_Offset_219{};
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
    MakeSignedCANSignal(double, 0, 32, 0.001, 0.0) s_PDM_Current_Sensing_Unreg_A{};
    MakeSignedCANSignal(double, 32, 32, 0.001, 0.0) s_PDM_Current_Sensing_FiveVolt_A{};
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
    CANRXMessage<2> m_IMD { 0x300, [](){}, s_IMD_transmit_resistance, s_IMD_transmit_status };
#endif
#ifdef RX_BMS
    // BMS_Voltages_0
    CANRXMessage<8> m_BMS_Voltages_0 { 0x200, [](){}, s_BMS_Voltages_0_Cell_V_0, s_BMS_Voltages_0_Cell_V_1, s_BMS_Voltages_0_Cell_V_2, s_BMS_Voltages_0_Cell_V_3, s_BMS_Voltages_0_Cell_V_4, s_BMS_Voltages_0_Cell_V_5, s_BMS_Voltages_0_Cell_V_6, s_BMS_Voltages_0_Cell_OCV_Offset_0 };
    // BMS_Voltages_1
    CANRXMessage<8> m_BMS_Voltages_1 { 0x201, [](){}, s_BMS_Voltages_1_Cell_V_7, s_BMS_Voltages_1_Cell_V_8, s_BMS_Voltages_1_Cell_V_9, s_BMS_Voltages_1_Cell_V_10, s_BMS_Voltages_1_Cell_V_11, s_BMS_Voltages_1_Cell_V_12, s_BMS_Voltages_1_Cell_V_13, s_BMS_Voltages_1_Cell_OCV_Offset_1 };
    // BMS_Voltages_2
    CANRXMessage<8> m_BMS_Voltages_2 { 0x202, [](){}, s_BMS_Voltages_2_Cell_V_14, s_BMS_Voltages_2_Cell_V_15, s_BMS_Voltages_2_Cell_V_16, s_BMS_Voltages_2_Cell_V_17, s_BMS_Voltages_2_Cell_V_18, s_BMS_Voltages_2_Cell_V_19, s_BMS_Voltages_2_Cell_V_20, s_BMS_Voltages_2_Cell_OCV_Offset_2 };
    // BMS_Voltages_3
    CANRXMessage<8> m_BMS_Voltages_3 { 0x203, [](){}, s_BMS_Voltages_3_Cell_V_21, s_BMS_Voltages_3_Cell_V_22, s_BMS_Voltages_3_Cell_V_23, s_BMS_Voltages_3_Cell_V_24, s_BMS_Voltages_3_Cell_V_25, s_BMS_Voltages_3_Cell_V_26, s_BMS_Voltages_3_Cell_V_27, s_BMS_Voltages_3_Cell_OCV_Offset_3 };
    // BMS_Voltages_4
    CANRXMessage<8> m_BMS_Voltages_4 { 0x204, [](){}, s_BMS_Voltages_4_Cell_V_28, s_BMS_Voltages_4_Cell_V_29, s_BMS_Voltages_4_Cell_V_30, s_BMS_Voltages_4_Cell_V_31, s_BMS_Voltages_4_Cell_V_32, s_BMS_Voltages_4_Cell_V_33, s_BMS_Voltages_4_Cell_V_34, s_BMS_Voltages_4_Cell_OCV_Offset_4 };
    // BMS_Voltages_5
    CANRXMessage<8> m_BMS_Voltages_5 { 0x205, [](){}, s_BMS_Voltages_5_Cell_V_35, s_BMS_Voltages_5_Cell_V_36, s_BMS_Voltages_5_Cell_V_37, s_BMS_Voltages_5_Cell_V_38, s_BMS_Voltages_5_Cell_V_39, s_BMS_Voltages_5_Cell_V_40, s_BMS_Voltages_5_Cell_V_41, s_BMS_Voltages_5_Cell_OCV_Offset_5 };
    // BMS_Voltages_6
    CANRXMessage<8> m_BMS_Voltages_6 { 0x206, [](){}, s_BMS_Voltages_6_Cell_V_42, s_BMS_Voltages_6_Cell_V_43, s_BMS_Voltages_6_Cell_V_44, s_BMS_Voltages_6_Cell_V_45, s_BMS_Voltages_6_Cell_V_46, s_BMS_Voltages_6_Cell_V_47, s_BMS_Voltages_6_Cell_V_48, s_BMS_Voltages_6_Cell_OCV_Offset_6 };
    // BMS_Voltages_7
    CANRXMessage<8> m_BMS_Voltages_7 { 0x207, [](){}, s_BMS_Voltages_7_Cell_V_49, s_BMS_Voltages_7_Cell_V_50, s_BMS_Voltages_7_Cell_V_51, s_BMS_Voltages_7_Cell_V_52, s_BMS_Voltages_7_Cell_V_53, s_BMS_Voltages_7_Cell_V_54, s_BMS_Voltages_7_Cell_V_55, s_BMS_Voltages_7_Cell_OCV_Offset_7 };
    // BMS_Voltages_8
    CANRXMessage<8> m_BMS_Voltages_8 { 0x208, [](){}, s_BMS_Voltages_8_Cell_V_56, s_BMS_Voltages_8_Cell_V_57, s_BMS_Voltages_8_Cell_V_58, s_BMS_Voltages_8_Cell_V_59, s_BMS_Voltages_8_Cell_V_60, s_BMS_Voltages_8_Cell_V_61, s_BMS_Voltages_8_Cell_V_62, s_BMS_Voltages_8_Cell_OCV_Offset_8 };
    // BMS_Voltages_9
    CANRXMessage<8> m_BMS_Voltages_9 { 0x209, [](){}, s_BMS_Voltages_9_Cell_V_63, s_BMS_Voltages_9_Cell_V_64, s_BMS_Voltages_9_Cell_V_65, s_BMS_Voltages_9_Cell_V_66, s_BMS_Voltages_9_Cell_V_67, s_BMS_Voltages_9_Cell_V_68, s_BMS_Voltages_9_Cell_V_69, s_BMS_Voltages_9_Cell_OCV_Offset_9 };
    // BMS_Voltages_10
    CANRXMessage<8> m_BMS_Voltages_10 { 0x20a, [](){}, s_BMS_Voltages_10_Cell_V_70, s_BMS_Voltages_10_Cell_V_71, s_BMS_Voltages_10_Cell_V_72, s_BMS_Voltages_10_Cell_V_73, s_BMS_Voltages_10_Cell_V_74, s_BMS_Voltages_10_Cell_V_75, s_BMS_Voltages_10_Cell_V_76, s_BMS_Voltages_10_Cell_OCV_Offset_110 };
    // BMS_Voltages_11
    CANRXMessage<8> m_BMS_Voltages_11 { 0x20b, [](){}, s_BMS_Voltages_11_Cell_V_77, s_BMS_Voltages_11_Cell_V_78, s_BMS_Voltages_11_Cell_V_79, s_BMS_Voltages_11_Cell_V_80, s_BMS_Voltages_11_Cell_V_81, s_BMS_Voltages_11_Cell_V_82, s_BMS_Voltages_11_Cell_V_83, s_BMS_Voltages_11_Cell_OCV_Offset_211 };
    // BMS_Voltages_12
    CANRXMessage<8> m_BMS_Voltages_12 { 0x20c, [](){}, s_BMS_Voltages_12_Cell_V_84, s_BMS_Voltages_12_Cell_V_85, s_BMS_Voltages_12_Cell_V_86, s_BMS_Voltages_12_Cell_V_87, s_BMS_Voltages_12_Cell_V_88, s_BMS_Voltages_12_Cell_V_89, s_BMS_Voltages_12_Cell_V_90, s_BMS_Voltages_12_Cell_OCV_Offset_212 };
    // BMS_Voltages_13
    CANRXMessage<8> m_BMS_Voltages_13 { 0x20d, [](){}, s_BMS_Voltages_13_Cell_V_91, s_BMS_Voltages_13_Cell_V_92, s_BMS_Voltages_13_Cell_V_93, s_BMS_Voltages_13_Cell_V_94, s_BMS_Voltages_13_Cell_V_95, s_BMS_Voltages_13_Cell_V_96, s_BMS_Voltages_13_Cell_V_97, s_BMS_Voltages_13_Cell_OCV_Offset_213 };
    // BMS_Voltages_14
    CANRXMessage<8> m_BMS_Voltages_14 { 0x20e, [](){}, s_BMS_Voltages_14_Cell_V_98, s_BMS_Voltages_14_Cell_V_99, s_BMS_Voltages_14_Cell_V_100, s_BMS_Voltages_14_Cell_V_101, s_BMS_Voltages_14_Cell_V_102, s_BMS_Voltages_14_Cell_V_103, s_BMS_Voltages_14_Cell_V_104, s_BMS_Voltages_14_Cell_OCV_Offset_214 };
    // BMS_Voltages_15
    CANRXMessage<8> m_BMS_Voltages_15 { 0x20f, [](){}, s_BMS_Voltages_15_Cell_V_105, s_BMS_Voltages_15_Cell_V_106, s_BMS_Voltages_15_Cell_V_107, s_BMS_Voltages_15_Cell_V_108, s_BMS_Voltages_15_Cell_V_109, s_BMS_Voltages_15_Cell_V_110, s_BMS_Voltages_15_Cell_V_111, s_BMS_Voltages_15_Cell_OCV_Offset_115 };
    // BMS_Voltages_16
    CANRXMessage<8> m_BMS_Voltages_16 { 0x210, [](){}, s_BMS_Voltages_16_Cell_V_112, s_BMS_Voltages_16_Cell_V_113, s_BMS_Voltages_16_Cell_V_114, s_BMS_Voltages_16_Cell_V_115, s_BMS_Voltages_16_Cell_V_116, s_BMS_Voltages_16_Cell_V_117, s_BMS_Voltages_16_Cell_V_118, s_BMS_Voltages_16_Cell_OCV_Offset_216 };
    // BMS_Voltages_17
    CANRXMessage<8> m_BMS_Voltages_17 { 0x211, [](){}, s_BMS_Voltages_17_Cell_V_119, s_BMS_Voltages_17_Cell_V_120, s_BMS_Voltages_17_Cell_V_121, s_BMS_Voltages_17_Cell_V_122, s_BMS_Voltages_17_Cell_V_123, s_BMS_Voltages_17_Cell_V_124, s_BMS_Voltages_17_Cell_V_125, s_BMS_Voltages_17_Cell_OCV_Offset_217 };
    // BMS_Voltages_18
    CANRXMessage<8> m_BMS_Voltages_18 { 0x212, [](){}, s_BMS_Voltages_18_Cell_V_126, s_BMS_Voltages_18_Cell_V_127, s_BMS_Voltages_18_Cell_V_128, s_BMS_Voltages_18_Cell_V_129, s_BMS_Voltages_18_Cell_V_130, s_BMS_Voltages_18_Cell_V_131, s_BMS_Voltages_18_Cell_V_132, s_BMS_Voltages_18_Cell_OCV_Offset_218 };
    // BMS_Voltages_19
    CANRXMessage<8> m_BMS_Voltages_19 { 0x213, [](){}, s_BMS_Voltages_19_Cell_V_133, s_BMS_Voltages_19_Cell_V_134, s_BMS_Voltages_19_Cell_V_135, s_BMS_Voltages_19_Cell_V_136, s_BMS_Voltages_19_Cell_V_137, s_BMS_Voltages_19_Cell_V_138, s_BMS_Voltages_19_Cell_V_139, s_BMS_Voltages_19_Cell_OCV_Offset_219 };
    // BMS_Temperatures_0
    CANRXMessage<7> m_BMS_Temperatures_0 { 0x220, [](){}, s_BMS_Temperatures_0_Cell_T_0, s_BMS_Temperatures_0_Cell_T_1, s_BMS_Temperatures_0_Cell_T_2, s_BMS_Temperatures_0_Cell_T_3, s_BMS_Temperatures_0_Cell_T_4, s_BMS_Temperatures_0_Cell_T_5, s_BMS_Temperatures_0_Cell_T_6 };
    // BMS_Temperatures_1
    CANRXMessage<7> m_BMS_Temperatures_1 { 0x221, [](){}, s_BMS_Temperatures_1_Cell_T_7, s_BMS_Temperatures_1_Cell_T_8, s_BMS_Temperatures_1_Cell_T_9, s_BMS_Temperatures_1_Cell_T_10, s_BMS_Temperatures_1_Cell_T_11, s_BMS_Temperatures_1_Cell_T_12, s_BMS_Temperatures_1_Cell_T_13 };
    // BMS_Temperatures_2
    CANRXMessage<7> m_BMS_Temperatures_2 { 0x222, [](){}, s_BMS_Temperatures_2_Cell_T_14, s_BMS_Temperatures_2_Cell_T_15, s_BMS_Temperatures_2_Cell_T_16, s_BMS_Temperatures_2_Cell_T_17, s_BMS_Temperatures_2_Cell_T_18, s_BMS_Temperatures_2_Cell_T_19, s_BMS_Temperatures_2_Cell_T_20 };
    // BMS_Temperatures_3
    CANRXMessage<7> m_BMS_Temperatures_3 { 0x223, [](){}, s_BMS_Temperatures_3_Cell_T_21, s_BMS_Temperatures_3_Cell_T_22, s_BMS_Temperatures_3_Cell_T_23, s_BMS_Temperatures_3_Cell_T_24, s_BMS_Temperatures_3_Cell_T_25, s_BMS_Temperatures_3_Cell_T_26, s_BMS_Temperatures_3_Cell_T_27 };
    // BMS_Temperatures_4
    CANRXMessage<7> m_BMS_Temperatures_4 { 0x224, [](){}, s_BMS_Temperatures_4_Cell_T_28, s_BMS_Temperatures_4_Cell_T_29, s_BMS_Temperatures_4_Cell_T_30, s_BMS_Temperatures_4_Cell_T_31, s_BMS_Temperatures_4_Cell_T_32, s_BMS_Temperatures_4_Cell_T_33, s_BMS_Temperatures_4_Cell_T_34 };
    // BMS_Temperatures_5
    CANRXMessage<7> m_BMS_Temperatures_5 { 0x225, [](){}, s_BMS_Temperatures_5_Cell_T_35, s_BMS_Temperatures_5_Cell_T_36, s_BMS_Temperatures_5_Cell_T_37, s_BMS_Temperatures_5_Cell_T_38, s_BMS_Temperatures_5_Cell_T_39, s_BMS_Temperatures_5_Cell_T_40, s_BMS_Temperatures_5_Cell_T_41 };
    // BMS_Temperatures_6
    CANRXMessage<7> m_BMS_Temperatures_6 { 0x226, [](){}, s_BMS_Temperatures_6_Cell_T_42, s_BMS_Temperatures_6_Cell_T_43, s_BMS_Temperatures_6_Cell_T_44, s_BMS_Temperatures_6_Cell_T_45, s_BMS_Temperatures_6_Cell_T_46, s_BMS_Temperatures_6_Cell_T_47, s_BMS_Temperatures_6_Cell_T_48 };
    // BMS_Temperatures_7
    CANRXMessage<7> m_BMS_Temperatures_7 { 0x227, [](){}, s_BMS_Temperatures_7_Cell_T_49, s_BMS_Temperatures_7_Cell_T_50, s_BMS_Temperatures_7_Cell_T_51, s_BMS_Temperatures_7_Cell_T_52, s_BMS_Temperatures_7_Cell_T_53, s_BMS_Temperatures_7_Cell_T_54, s_BMS_Temperatures_7_Cell_T_55 };
    // BMS_Temperatures_8
    CANRXMessage<7> m_BMS_Temperatures_8 { 0x228, [](){}, s_BMS_Temperatures_8_Cell_T_56, s_BMS_Temperatures_8_Cell_T_57, s_BMS_Temperatures_8_Cell_T_58, s_BMS_Temperatures_8_Cell_T_59, s_BMS_Temperatures_8_Cell_T_60, s_BMS_Temperatures_8_Cell_T_61, s_BMS_Temperatures_8_Cell_T_62 };
    // BMS_Temperatures_9
    CANRXMessage<7> m_BMS_Temperatures_9 { 0x229, [](){}, s_BMS_Temperatures_9_Cell_T_63, s_BMS_Temperatures_9_Cell_T_64, s_BMS_Temperatures_9_Cell_T_65, s_BMS_Temperatures_9_Cell_T_66, s_BMS_Temperatures_9_Cell_T_67, s_BMS_Temperatures_9_Cell_T_68, s_BMS_Temperatures_9_Cell_T_69 };
    // BMS_Temperatures_10
    CANRXMessage<7> m_BMS_Temperatures_10 { 0x22a, [](){}, s_BMS_Temperatures_10_Cell_T_70, s_BMS_Temperatures_10_Cell_T_71, s_BMS_Temperatures_10_Cell_T_72, s_BMS_Temperatures_10_Cell_T_73, s_BMS_Temperatures_10_Cell_T_74, s_BMS_Temperatures_10_Cell_T_75, s_BMS_Temperatures_10_Cell_T_76 };
    // BMS_Temperatures_11
    CANRXMessage<7> m_BMS_Temperatures_11 { 0x22b, [](){}, s_BMS_Temperatures_11_Cell_T_77, s_BMS_Temperatures_11_Cell_T_78, s_BMS_Temperatures_11_Cell_T_79, s_BMS_Temperatures_11_Cell_T_80, s_BMS_Temperatures_11_Cell_T_81, s_BMS_Temperatures_11_Cell_T_82, s_BMS_Temperatures_11_Cell_T_83 };
    // BMS_Temperatures_12
    CANRXMessage<7> m_BMS_Temperatures_12 { 0x22c, [](){}, s_BMS_Temperatures_12_Cell_T_84, s_BMS_Temperatures_12_Cell_T_85, s_BMS_Temperatures_12_Cell_T_86, s_BMS_Temperatures_12_Cell_T_87, s_BMS_Temperatures_12_Cell_T_88, s_BMS_Temperatures_12_Cell_T_89, s_BMS_Temperatures_12_Cell_T_90 };
    // BMS_Temperatures_13
    CANRXMessage<7> m_BMS_Temperatures_13 { 0x22d, [](){}, s_BMS_Temperatures_13_Cell_T_91, s_BMS_Temperatures_13_Cell_T_92, s_BMS_Temperatures_13_Cell_T_93, s_BMS_Temperatures_13_Cell_T_94, s_BMS_Temperatures_13_Cell_T_95, s_BMS_Temperatures_13_Cell_T_96, s_BMS_Temperatures_13_Cell_T_97 };
    // BMS_Temperatures_14
    CANRXMessage<7> m_BMS_Temperatures_14 { 0x22e, [](){}, s_BMS_Temperatures_14_Cell_T_98, s_BMS_Temperatures_14_Cell_T_99, s_BMS_Temperatures_14_Cell_T_100, s_BMS_Temperatures_14_Cell_T_101, s_BMS_Temperatures_14_Cell_T_102, s_BMS_Temperatures_14_Cell_T_103, s_BMS_Temperatures_14_Cell_T_104 };
    // BMS_Temperatures_15
    CANRXMessage<7> m_BMS_Temperatures_15 { 0x22f, [](){}, s_BMS_Temperatures_15_Cell_T_105, s_BMS_Temperatures_15_Cell_T_106, s_BMS_Temperatures_15_Cell_T_107, s_BMS_Temperatures_15_Cell_T_108, s_BMS_Temperatures_15_Cell_T_109, s_BMS_Temperatures_15_Cell_T_110, s_BMS_Temperatures_15_Cell_T_111 };
    // BMS_SOE
    CANRXMessage<5> m_BMS_SOE { 0x240, [](){}, s_BMS_SOE_Max_Discharge_Current, s_BMS_SOE_Max_Regen_Current, s_BMS_SOE_Battery_Voltage, s_BMS_SOE_Battery_Temperature, s_BMS_SOE_Battery_Current };
    // BMS_Faults
    CANRXMessage<8> m_BMS_Faults { 0x250, [](){}, s_BMS_Faults_Fault_Summary, s_BMS_Faults_Undervoltage_Fault, s_BMS_Faults_Overvoltage_Fault, s_BMS_Faults_Undertemperature_Fault, s_BMS_Faults_Overtemperature_Fault, s_BMS_Faults_Overcurrent_Fault, s_BMS_Faults_External_Kill_Fault, s_BMS_Faults_Open_Wire_Fault };
    // BMS_Status
    CANRXMessage<5> m_BMS_Status { 0x241, [](){}, s_BMS_Status_Max_Cell_Temp, s_BMS_Status_Min_Cell_Temp, s_BMS_Status_Max_Cell_Voltage, s_BMS_Status_Min_Cell_Voltage, s_BMS_Status_BMS_SOC };
#endif
#ifdef RX_PDM
    // PDM_Current_Sensing
    CANRXMessage<2> m_PDM_Current_Sensing { 0x, [](){}, s_PDM_Current_Sensing_Unreg_A, s_PDM_Current_Sensing_FiveVolt_A };
#endif
#ifdef RX_WHEEL
    // Wheel_Message
    CANRXMessage<2> m_Wheel_Message { 0x410, [](){}, s_Wheel_Message_Wheel_Temp, s_Wheel_Message_Wheel_Speed };
#endif
#ifdef RX_SHUTDOWN
    // Shutdown_Status
    CANRXMessage<1> m_Shutdown_Status { 0x310, [](){}, s_Shutdown_Status_Voltage_Sag };
    // Shutdown_1
    CANRXMessage<1> m_Shutdown_1 { 0x310, [](){}, s_Shutdown_1_Voltage_Sag };
    // Shutdown_2
    CANRXMessage<1> m_Shutdown_2 { 0x310, [](){}, s_Shutdown_2_Voltage_Sag };
    // Shutdown_3
    CANRXMessage<1> m_Shutdown_3 { 0x310, [](){}, s_Shutdown_3_Voltage_Sag };
    // Shutdown_4
    CANRXMessage<1> m_Shutdown_4 { 0x310, [](){}, s_Shutdown_4_Voltage_Sag };
    // Shutdown_5
    CANRXMessage<1> m_Shutdown_5 { 0x310, [](){}, s_Shutdown_5_Voltage_Sag };
    // Shutdown_6
    CANRXMessage<1> m_Shutdown_6 { 0x310, [](){}, s_Shutdown_6_Voltage_Sag };
#endif
#ifdef RX_ETC
    // throttle_tx
    CANRXMessage<2> m_throttle_tx { 0x010, [](){}, s_throttle_tx_Throttle_percent, s_throttle_tx_Throttle_active };
    // brake_tx
    CANRXMessage<1> m_brake_tx { 0x011, [](){}, s_brake_tx_Brake_pedal };
#endif
#ifdef RX_VCU
    // Drive_Status
    CANRXMessage<1> m_Drive_Status { 0x000, [](){}, s_Drive_Status_Drive_State };
#endif


    // functions to update daqser

    void updateSignals()
    {
#ifdef RX_IMD
    // IMD
    daqser::set("Car_Data.IMD.transmit_resistance", (float)s_IMD_transmit_resistance);
    daqser::set("Car_Data.IMD.transmit_status", (bool)s_IMD_transmit_status);
#endif
#ifdef RX_BMS
    // BMS_Voltages_0
    daqser::set("Car_Data.BMS_Voltages_0.Cell_V_0", (bool)s_BMS_Voltages_0_Cell_V_0);
    daqser::set("Car_Data.BMS_Voltages_0.Cell_V_1", (bool)s_BMS_Voltages_0_Cell_V_1);
    daqser::set("Car_Data.BMS_Voltages_0.Cell_V_2", (bool)s_BMS_Voltages_0_Cell_V_2);
    daqser::set("Car_Data.BMS_Voltages_0.Cell_V_3", (bool)s_BMS_Voltages_0_Cell_V_3);
    daqser::set("Car_Data.BMS_Voltages_0.Cell_V_4", (bool)s_BMS_Voltages_0_Cell_V_4);
    daqser::set("Car_Data.BMS_Voltages_0.Cell_V_5", (bool)s_BMS_Voltages_0_Cell_V_5);
    daqser::set("Car_Data.BMS_Voltages_0.Cell_V_6", (bool)s_BMS_Voltages_0_Cell_V_6);
    daqser::set("Car_Data.BMS_Voltages_0.Cell_OCV_Offset_0", (bool)s_BMS_Voltages_0_Cell_OCV_Offset_0);
    // BMS_Voltages_1
    daqser::set("Car_Data.BMS_Voltages_1.Cell_V_7", (bool)s_BMS_Voltages_1_Cell_V_7);
    daqser::set("Car_Data.BMS_Voltages_1.Cell_V_8", (bool)s_BMS_Voltages_1_Cell_V_8);
    daqser::set("Car_Data.BMS_Voltages_1.Cell_V_9", (bool)s_BMS_Voltages_1_Cell_V_9);
    daqser::set("Car_Data.BMS_Voltages_1.Cell_V_10", (bool)s_BMS_Voltages_1_Cell_V_10);
    daqser::set("Car_Data.BMS_Voltages_1.Cell_V_11", (bool)s_BMS_Voltages_1_Cell_V_11);
    daqser::set("Car_Data.BMS_Voltages_1.Cell_V_12", (bool)s_BMS_Voltages_1_Cell_V_12);
    daqser::set("Car_Data.BMS_Voltages_1.Cell_V_13", (bool)s_BMS_Voltages_1_Cell_V_13);
    daqser::set("Car_Data.BMS_Voltages_1.Cell_OCV_Offset_1", (bool)s_BMS_Voltages_1_Cell_OCV_Offset_1);
    // BMS_Voltages_2
    daqser::set("Car_Data.BMS_Voltages_2.Cell_V_14", (bool)s_BMS_Voltages_2_Cell_V_14);
    daqser::set("Car_Data.BMS_Voltages_2.Cell_V_15", (bool)s_BMS_Voltages_2_Cell_V_15);
    daqser::set("Car_Data.BMS_Voltages_2.Cell_V_16", (bool)s_BMS_Voltages_2_Cell_V_16);
    daqser::set("Car_Data.BMS_Voltages_2.Cell_V_17", (bool)s_BMS_Voltages_2_Cell_V_17);
    daqser::set("Car_Data.BMS_Voltages_2.Cell_V_18", (bool)s_BMS_Voltages_2_Cell_V_18);
    daqser::set("Car_Data.BMS_Voltages_2.Cell_V_19", (bool)s_BMS_Voltages_2_Cell_V_19);
    daqser::set("Car_Data.BMS_Voltages_2.Cell_V_20", (bool)s_BMS_Voltages_2_Cell_V_20);
    daqser::set("Car_Data.BMS_Voltages_2.Cell_OCV_Offset_2", (bool)s_BMS_Voltages_2_Cell_OCV_Offset_2);
    // BMS_Voltages_3
    daqser::set("Car_Data.BMS_Voltages_3.Cell_V_21", (bool)s_BMS_Voltages_3_Cell_V_21);
    daqser::set("Car_Data.BMS_Voltages_3.Cell_V_22", (bool)s_BMS_Voltages_3_Cell_V_22);
    daqser::set("Car_Data.BMS_Voltages_3.Cell_V_23", (bool)s_BMS_Voltages_3_Cell_V_23);
    daqser::set("Car_Data.BMS_Voltages_3.Cell_V_24", (bool)s_BMS_Voltages_3_Cell_V_24);
    daqser::set("Car_Data.BMS_Voltages_3.Cell_V_25", (bool)s_BMS_Voltages_3_Cell_V_25);
    daqser::set("Car_Data.BMS_Voltages_3.Cell_V_26", (bool)s_BMS_Voltages_3_Cell_V_26);
    daqser::set("Car_Data.BMS_Voltages_3.Cell_V_27", (bool)s_BMS_Voltages_3_Cell_V_27);
    daqser::set("Car_Data.BMS_Voltages_3.Cell_OCV_Offset_3", (bool)s_BMS_Voltages_3_Cell_OCV_Offset_3);
    // BMS_Voltages_4
    daqser::set("Car_Data.BMS_Voltages_4.Cell_V_28", (bool)s_BMS_Voltages_4_Cell_V_28);
    daqser::set("Car_Data.BMS_Voltages_4.Cell_V_29", (bool)s_BMS_Voltages_4_Cell_V_29);
    daqser::set("Car_Data.BMS_Voltages_4.Cell_V_30", (bool)s_BMS_Voltages_4_Cell_V_30);
    daqser::set("Car_Data.BMS_Voltages_4.Cell_V_31", (bool)s_BMS_Voltages_4_Cell_V_31);
    daqser::set("Car_Data.BMS_Voltages_4.Cell_V_32", (bool)s_BMS_Voltages_4_Cell_V_32);
    daqser::set("Car_Data.BMS_Voltages_4.Cell_V_33", (bool)s_BMS_Voltages_4_Cell_V_33);
    daqser::set("Car_Data.BMS_Voltages_4.Cell_V_34", (bool)s_BMS_Voltages_4_Cell_V_34);
    daqser::set("Car_Data.BMS_Voltages_4.Cell_OCV_Offset_4", (bool)s_BMS_Voltages_4_Cell_OCV_Offset_4);
    // BMS_Voltages_5
    daqser::set("Car_Data.BMS_Voltages_5.Cell_V_35", (bool)s_BMS_Voltages_5_Cell_V_35);
    daqser::set("Car_Data.BMS_Voltages_5.Cell_V_36", (bool)s_BMS_Voltages_5_Cell_V_36);
    daqser::set("Car_Data.BMS_Voltages_5.Cell_V_37", (bool)s_BMS_Voltages_5_Cell_V_37);
    daqser::set("Car_Data.BMS_Voltages_5.Cell_V_38", (bool)s_BMS_Voltages_5_Cell_V_38);
    daqser::set("Car_Data.BMS_Voltages_5.Cell_V_39", (bool)s_BMS_Voltages_5_Cell_V_39);
    daqser::set("Car_Data.BMS_Voltages_5.Cell_V_40", (bool)s_BMS_Voltages_5_Cell_V_40);
    daqser::set("Car_Data.BMS_Voltages_5.Cell_V_41", (bool)s_BMS_Voltages_5_Cell_V_41);
    daqser::set("Car_Data.BMS_Voltages_5.Cell_OCV_Offset_5", (bool)s_BMS_Voltages_5_Cell_OCV_Offset_5);
    // BMS_Voltages_6
    daqser::set("Car_Data.BMS_Voltages_6.Cell_V_42", (bool)s_BMS_Voltages_6_Cell_V_42);
    daqser::set("Car_Data.BMS_Voltages_6.Cell_V_43", (bool)s_BMS_Voltages_6_Cell_V_43);
    daqser::set("Car_Data.BMS_Voltages_6.Cell_V_44", (bool)s_BMS_Voltages_6_Cell_V_44);
    daqser::set("Car_Data.BMS_Voltages_6.Cell_V_45", (bool)s_BMS_Voltages_6_Cell_V_45);
    daqser::set("Car_Data.BMS_Voltages_6.Cell_V_46", (bool)s_BMS_Voltages_6_Cell_V_46);
    daqser::set("Car_Data.BMS_Voltages_6.Cell_V_47", (bool)s_BMS_Voltages_6_Cell_V_47);
    daqser::set("Car_Data.BMS_Voltages_6.Cell_V_48", (bool)s_BMS_Voltages_6_Cell_V_48);
    daqser::set("Car_Data.BMS_Voltages_6.Cell_OCV_Offset_6", (bool)s_BMS_Voltages_6_Cell_OCV_Offset_6);
    // BMS_Voltages_7
    daqser::set("Car_Data.BMS_Voltages_7.Cell_V_49", (bool)s_BMS_Voltages_7_Cell_V_49);
    daqser::set("Car_Data.BMS_Voltages_7.Cell_V_50", (bool)s_BMS_Voltages_7_Cell_V_50);
    daqser::set("Car_Data.BMS_Voltages_7.Cell_V_51", (bool)s_BMS_Voltages_7_Cell_V_51);
    daqser::set("Car_Data.BMS_Voltages_7.Cell_V_52", (bool)s_BMS_Voltages_7_Cell_V_52);
    daqser::set("Car_Data.BMS_Voltages_7.Cell_V_53", (bool)s_BMS_Voltages_7_Cell_V_53);
    daqser::set("Car_Data.BMS_Voltages_7.Cell_V_54", (bool)s_BMS_Voltages_7_Cell_V_54);
    daqser::set("Car_Data.BMS_Voltages_7.Cell_V_55", (bool)s_BMS_Voltages_7_Cell_V_55);
    daqser::set("Car_Data.BMS_Voltages_7.Cell_OCV_Offset_7", (bool)s_BMS_Voltages_7_Cell_OCV_Offset_7);
    // BMS_Voltages_8
    daqser::set("Car_Data.BMS_Voltages_8.Cell_V_56", (bool)s_BMS_Voltages_8_Cell_V_56);
    daqser::set("Car_Data.BMS_Voltages_8.Cell_V_57", (bool)s_BMS_Voltages_8_Cell_V_57);
    daqser::set("Car_Data.BMS_Voltages_8.Cell_V_58", (bool)s_BMS_Voltages_8_Cell_V_58);
    daqser::set("Car_Data.BMS_Voltages_8.Cell_V_59", (bool)s_BMS_Voltages_8_Cell_V_59);
    daqser::set("Car_Data.BMS_Voltages_8.Cell_V_60", (bool)s_BMS_Voltages_8_Cell_V_60);
    daqser::set("Car_Data.BMS_Voltages_8.Cell_V_61", (bool)s_BMS_Voltages_8_Cell_V_61);
    daqser::set("Car_Data.BMS_Voltages_8.Cell_V_62", (bool)s_BMS_Voltages_8_Cell_V_62);
    daqser::set("Car_Data.BMS_Voltages_8.Cell_OCV_Offset_8", (bool)s_BMS_Voltages_8_Cell_OCV_Offset_8);
    // BMS_Voltages_9
    daqser::set("Car_Data.BMS_Voltages_9.Cell_V_63", (bool)s_BMS_Voltages_9_Cell_V_63);
    daqser::set("Car_Data.BMS_Voltages_9.Cell_V_64", (bool)s_BMS_Voltages_9_Cell_V_64);
    daqser::set("Car_Data.BMS_Voltages_9.Cell_V_65", (bool)s_BMS_Voltages_9_Cell_V_65);
    daqser::set("Car_Data.BMS_Voltages_9.Cell_V_66", (bool)s_BMS_Voltages_9_Cell_V_66);
    daqser::set("Car_Data.BMS_Voltages_9.Cell_V_67", (bool)s_BMS_Voltages_9_Cell_V_67);
    daqser::set("Car_Data.BMS_Voltages_9.Cell_V_68", (bool)s_BMS_Voltages_9_Cell_V_68);
    daqser::set("Car_Data.BMS_Voltages_9.Cell_V_69", (bool)s_BMS_Voltages_9_Cell_V_69);
    daqser::set("Car_Data.BMS_Voltages_9.Cell_OCV_Offset_9", (bool)s_BMS_Voltages_9_Cell_OCV_Offset_9);
    // BMS_Voltages_10
    daqser::set("Car_Data.BMS_Voltages_10.Cell_V_70", (bool)s_BMS_Voltages_10_Cell_V_70);
    daqser::set("Car_Data.BMS_Voltages_10.Cell_V_71", (bool)s_BMS_Voltages_10_Cell_V_71);
    daqser::set("Car_Data.BMS_Voltages_10.Cell_V_72", (bool)s_BMS_Voltages_10_Cell_V_72);
    daqser::set("Car_Data.BMS_Voltages_10.Cell_V_73", (bool)s_BMS_Voltages_10_Cell_V_73);
    daqser::set("Car_Data.BMS_Voltages_10.Cell_V_74", (bool)s_BMS_Voltages_10_Cell_V_74);
    daqser::set("Car_Data.BMS_Voltages_10.Cell_V_75", (bool)s_BMS_Voltages_10_Cell_V_75);
    daqser::set("Car_Data.BMS_Voltages_10.Cell_V_76", (bool)s_BMS_Voltages_10_Cell_V_76);
    daqser::set("Car_Data.BMS_Voltages_10.Cell_OCV_Offset_110", (bool)s_BMS_Voltages_10_Cell_OCV_Offset_110);
    // BMS_Voltages_11
    daqser::set("Car_Data.BMS_Voltages_11.Cell_V_77", (bool)s_BMS_Voltages_11_Cell_V_77);
    daqser::set("Car_Data.BMS_Voltages_11.Cell_V_78", (bool)s_BMS_Voltages_11_Cell_V_78);
    daqser::set("Car_Data.BMS_Voltages_11.Cell_V_79", (bool)s_BMS_Voltages_11_Cell_V_79);
    daqser::set("Car_Data.BMS_Voltages_11.Cell_V_80", (bool)s_BMS_Voltages_11_Cell_V_80);
    daqser::set("Car_Data.BMS_Voltages_11.Cell_V_81", (bool)s_BMS_Voltages_11_Cell_V_81);
    daqser::set("Car_Data.BMS_Voltages_11.Cell_V_82", (bool)s_BMS_Voltages_11_Cell_V_82);
    daqser::set("Car_Data.BMS_Voltages_11.Cell_V_83", (bool)s_BMS_Voltages_11_Cell_V_83);
    daqser::set("Car_Data.BMS_Voltages_11.Cell_OCV_Offset_211", (bool)s_BMS_Voltages_11_Cell_OCV_Offset_211);
    // BMS_Voltages_12
    daqser::set("Car_Data.BMS_Voltages_12.Cell_V_84", (bool)s_BMS_Voltages_12_Cell_V_84);
    daqser::set("Car_Data.BMS_Voltages_12.Cell_V_85", (bool)s_BMS_Voltages_12_Cell_V_85);
    daqser::set("Car_Data.BMS_Voltages_12.Cell_V_86", (bool)s_BMS_Voltages_12_Cell_V_86);
    daqser::set("Car_Data.BMS_Voltages_12.Cell_V_87", (bool)s_BMS_Voltages_12_Cell_V_87);
    daqser::set("Car_Data.BMS_Voltages_12.Cell_V_88", (bool)s_BMS_Voltages_12_Cell_V_88);
    daqser::set("Car_Data.BMS_Voltages_12.Cell_V_89", (bool)s_BMS_Voltages_12_Cell_V_89);
    daqser::set("Car_Data.BMS_Voltages_12.Cell_V_90", (bool)s_BMS_Voltages_12_Cell_V_90);
    daqser::set("Car_Data.BMS_Voltages_12.Cell_OCV_Offset_212", (bool)s_BMS_Voltages_12_Cell_OCV_Offset_212);
    // BMS_Voltages_13
    daqser::set("Car_Data.BMS_Voltages_13.Cell_V_91", (bool)s_BMS_Voltages_13_Cell_V_91);
    daqser::set("Car_Data.BMS_Voltages_13.Cell_V_92", (bool)s_BMS_Voltages_13_Cell_V_92);
    daqser::set("Car_Data.BMS_Voltages_13.Cell_V_93", (bool)s_BMS_Voltages_13_Cell_V_93);
    daqser::set("Car_Data.BMS_Voltages_13.Cell_V_94", (bool)s_BMS_Voltages_13_Cell_V_94);
    daqser::set("Car_Data.BMS_Voltages_13.Cell_V_95", (bool)s_BMS_Voltages_13_Cell_V_95);
    daqser::set("Car_Data.BMS_Voltages_13.Cell_V_96", (bool)s_BMS_Voltages_13_Cell_V_96);
    daqser::set("Car_Data.BMS_Voltages_13.Cell_V_97", (bool)s_BMS_Voltages_13_Cell_V_97);
    daqser::set("Car_Data.BMS_Voltages_13.Cell_OCV_Offset_213", (bool)s_BMS_Voltages_13_Cell_OCV_Offset_213);
    // BMS_Voltages_14
    daqser::set("Car_Data.BMS_Voltages_14.Cell_V_98", (bool)s_BMS_Voltages_14_Cell_V_98);
    daqser::set("Car_Data.BMS_Voltages_14.Cell_V_99", (bool)s_BMS_Voltages_14_Cell_V_99);
    daqser::set("Car_Data.BMS_Voltages_14.Cell_V_100", (bool)s_BMS_Voltages_14_Cell_V_100);
    daqser::set("Car_Data.BMS_Voltages_14.Cell_V_101", (bool)s_BMS_Voltages_14_Cell_V_101);
    daqser::set("Car_Data.BMS_Voltages_14.Cell_V_102", (bool)s_BMS_Voltages_14_Cell_V_102);
    daqser::set("Car_Data.BMS_Voltages_14.Cell_V_103", (bool)s_BMS_Voltages_14_Cell_V_103);
    daqser::set("Car_Data.BMS_Voltages_14.Cell_V_104", (bool)s_BMS_Voltages_14_Cell_V_104);
    daqser::set("Car_Data.BMS_Voltages_14.Cell_OCV_Offset_214", (bool)s_BMS_Voltages_14_Cell_OCV_Offset_214);
    // BMS_Voltages_15
    daqser::set("Car_Data.BMS_Voltages_15.Cell_V_105", (bool)s_BMS_Voltages_15_Cell_V_105);
    daqser::set("Car_Data.BMS_Voltages_15.Cell_V_106", (bool)s_BMS_Voltages_15_Cell_V_106);
    daqser::set("Car_Data.BMS_Voltages_15.Cell_V_107", (bool)s_BMS_Voltages_15_Cell_V_107);
    daqser::set("Car_Data.BMS_Voltages_15.Cell_V_108", (bool)s_BMS_Voltages_15_Cell_V_108);
    daqser::set("Car_Data.BMS_Voltages_15.Cell_V_109", (bool)s_BMS_Voltages_15_Cell_V_109);
    daqser::set("Car_Data.BMS_Voltages_15.Cell_V_110", (bool)s_BMS_Voltages_15_Cell_V_110);
    daqser::set("Car_Data.BMS_Voltages_15.Cell_V_111", (bool)s_BMS_Voltages_15_Cell_V_111);
    daqser::set("Car_Data.BMS_Voltages_15.Cell_OCV_Offset_115", (bool)s_BMS_Voltages_15_Cell_OCV_Offset_115);
    // BMS_Voltages_16
    daqser::set("Car_Data.BMS_Voltages_16.Cell_V_112", (bool)s_BMS_Voltages_16_Cell_V_112);
    daqser::set("Car_Data.BMS_Voltages_16.Cell_V_113", (bool)s_BMS_Voltages_16_Cell_V_113);
    daqser::set("Car_Data.BMS_Voltages_16.Cell_V_114", (bool)s_BMS_Voltages_16_Cell_V_114);
    daqser::set("Car_Data.BMS_Voltages_16.Cell_V_115", (bool)s_BMS_Voltages_16_Cell_V_115);
    daqser::set("Car_Data.BMS_Voltages_16.Cell_V_116", (bool)s_BMS_Voltages_16_Cell_V_116);
    daqser::set("Car_Data.BMS_Voltages_16.Cell_V_117", (bool)s_BMS_Voltages_16_Cell_V_117);
    daqser::set("Car_Data.BMS_Voltages_16.Cell_V_118", (bool)s_BMS_Voltages_16_Cell_V_118);
    daqser::set("Car_Data.BMS_Voltages_16.Cell_OCV_Offset_216", (bool)s_BMS_Voltages_16_Cell_OCV_Offset_216);
    // BMS_Voltages_17
    daqser::set("Car_Data.BMS_Voltages_17.Cell_V_119", (bool)s_BMS_Voltages_17_Cell_V_119);
    daqser::set("Car_Data.BMS_Voltages_17.Cell_V_120", (bool)s_BMS_Voltages_17_Cell_V_120);
    daqser::set("Car_Data.BMS_Voltages_17.Cell_V_121", (bool)s_BMS_Voltages_17_Cell_V_121);
    daqser::set("Car_Data.BMS_Voltages_17.Cell_V_122", (bool)s_BMS_Voltages_17_Cell_V_122);
    daqser::set("Car_Data.BMS_Voltages_17.Cell_V_123", (bool)s_BMS_Voltages_17_Cell_V_123);
    daqser::set("Car_Data.BMS_Voltages_17.Cell_V_124", (bool)s_BMS_Voltages_17_Cell_V_124);
    daqser::set("Car_Data.BMS_Voltages_17.Cell_V_125", (bool)s_BMS_Voltages_17_Cell_V_125);
    daqser::set("Car_Data.BMS_Voltages_17.Cell_OCV_Offset_217", (bool)s_BMS_Voltages_17_Cell_OCV_Offset_217);
    // BMS_Voltages_18
    daqser::set("Car_Data.BMS_Voltages_18.Cell_V_126", (bool)s_BMS_Voltages_18_Cell_V_126);
    daqser::set("Car_Data.BMS_Voltages_18.Cell_V_127", (bool)s_BMS_Voltages_18_Cell_V_127);
    daqser::set("Car_Data.BMS_Voltages_18.Cell_V_128", (bool)s_BMS_Voltages_18_Cell_V_128);
    daqser::set("Car_Data.BMS_Voltages_18.Cell_V_129", (bool)s_BMS_Voltages_18_Cell_V_129);
    daqser::set("Car_Data.BMS_Voltages_18.Cell_V_130", (bool)s_BMS_Voltages_18_Cell_V_130);
    daqser::set("Car_Data.BMS_Voltages_18.Cell_V_131", (bool)s_BMS_Voltages_18_Cell_V_131);
    daqser::set("Car_Data.BMS_Voltages_18.Cell_V_132", (bool)s_BMS_Voltages_18_Cell_V_132);
    daqser::set("Car_Data.BMS_Voltages_18.Cell_OCV_Offset_218", (bool)s_BMS_Voltages_18_Cell_OCV_Offset_218);
    // BMS_Voltages_19
    daqser::set("Car_Data.BMS_Voltages_19.Cell_V_133", (bool)s_BMS_Voltages_19_Cell_V_133);
    daqser::set("Car_Data.BMS_Voltages_19.Cell_V_134", (bool)s_BMS_Voltages_19_Cell_V_134);
    daqser::set("Car_Data.BMS_Voltages_19.Cell_V_135", (bool)s_BMS_Voltages_19_Cell_V_135);
    daqser::set("Car_Data.BMS_Voltages_19.Cell_V_136", (bool)s_BMS_Voltages_19_Cell_V_136);
    daqser::set("Car_Data.BMS_Voltages_19.Cell_V_137", (bool)s_BMS_Voltages_19_Cell_V_137);
    daqser::set("Car_Data.BMS_Voltages_19.Cell_V_138", (bool)s_BMS_Voltages_19_Cell_V_138);
    daqser::set("Car_Data.BMS_Voltages_19.Cell_V_139", (bool)s_BMS_Voltages_19_Cell_V_139);
    daqser::set("Car_Data.BMS_Voltages_19.Cell_OCV_Offset_219", (bool)s_BMS_Voltages_19_Cell_OCV_Offset_219);
    // BMS_Temperatures_0
    daqser::set("Car_Data.BMS_Temperatures_0.Cell_T_0", (bool)s_BMS_Temperatures_0_Cell_T_0);
    daqser::set("Car_Data.BMS_Temperatures_0.Cell_T_1", (bool)s_BMS_Temperatures_0_Cell_T_1);
    daqser::set("Car_Data.BMS_Temperatures_0.Cell_T_2", (bool)s_BMS_Temperatures_0_Cell_T_2);
    daqser::set("Car_Data.BMS_Temperatures_0.Cell_T_3", (bool)s_BMS_Temperatures_0_Cell_T_3);
    daqser::set("Car_Data.BMS_Temperatures_0.Cell_T_4", (bool)s_BMS_Temperatures_0_Cell_T_4);
    daqser::set("Car_Data.BMS_Temperatures_0.Cell_T_5", (bool)s_BMS_Temperatures_0_Cell_T_5);
    daqser::set("Car_Data.BMS_Temperatures_0.Cell_T_6", (bool)s_BMS_Temperatures_0_Cell_T_6);
    // BMS_Temperatures_1
    daqser::set("Car_Data.BMS_Temperatures_1.Cell_T_7", (bool)s_BMS_Temperatures_1_Cell_T_7);
    daqser::set("Car_Data.BMS_Temperatures_1.Cell_T_8", (bool)s_BMS_Temperatures_1_Cell_T_8);
    daqser::set("Car_Data.BMS_Temperatures_1.Cell_T_9", (bool)s_BMS_Temperatures_1_Cell_T_9);
    daqser::set("Car_Data.BMS_Temperatures_1.Cell_T_10", (bool)s_BMS_Temperatures_1_Cell_T_10);
    daqser::set("Car_Data.BMS_Temperatures_1.Cell_T_11", (bool)s_BMS_Temperatures_1_Cell_T_11);
    daqser::set("Car_Data.BMS_Temperatures_1.Cell_T_12", (bool)s_BMS_Temperatures_1_Cell_T_12);
    daqser::set("Car_Data.BMS_Temperatures_1.Cell_T_13", (bool)s_BMS_Temperatures_1_Cell_T_13);
    // BMS_Temperatures_2
    daqser::set("Car_Data.BMS_Temperatures_2.Cell_T_14", (bool)s_BMS_Temperatures_2_Cell_T_14);
    daqser::set("Car_Data.BMS_Temperatures_2.Cell_T_15", (bool)s_BMS_Temperatures_2_Cell_T_15);
    daqser::set("Car_Data.BMS_Temperatures_2.Cell_T_16", (bool)s_BMS_Temperatures_2_Cell_T_16);
    daqser::set("Car_Data.BMS_Temperatures_2.Cell_T_17", (bool)s_BMS_Temperatures_2_Cell_T_17);
    daqser::set("Car_Data.BMS_Temperatures_2.Cell_T_18", (bool)s_BMS_Temperatures_2_Cell_T_18);
    daqser::set("Car_Data.BMS_Temperatures_2.Cell_T_19", (bool)s_BMS_Temperatures_2_Cell_T_19);
    daqser::set("Car_Data.BMS_Temperatures_2.Cell_T_20", (bool)s_BMS_Temperatures_2_Cell_T_20);
    // BMS_Temperatures_3
    daqser::set("Car_Data.BMS_Temperatures_3.Cell_T_21", (bool)s_BMS_Temperatures_3_Cell_T_21);
    daqser::set("Car_Data.BMS_Temperatures_3.Cell_T_22", (bool)s_BMS_Temperatures_3_Cell_T_22);
    daqser::set("Car_Data.BMS_Temperatures_3.Cell_T_23", (bool)s_BMS_Temperatures_3_Cell_T_23);
    daqser::set("Car_Data.BMS_Temperatures_3.Cell_T_24", (bool)s_BMS_Temperatures_3_Cell_T_24);
    daqser::set("Car_Data.BMS_Temperatures_3.Cell_T_25", (bool)s_BMS_Temperatures_3_Cell_T_25);
    daqser::set("Car_Data.BMS_Temperatures_3.Cell_T_26", (bool)s_BMS_Temperatures_3_Cell_T_26);
    daqser::set("Car_Data.BMS_Temperatures_3.Cell_T_27", (bool)s_BMS_Temperatures_3_Cell_T_27);
    // BMS_Temperatures_4
    daqser::set("Car_Data.BMS_Temperatures_4.Cell_T_28", (bool)s_BMS_Temperatures_4_Cell_T_28);
    daqser::set("Car_Data.BMS_Temperatures_4.Cell_T_29", (bool)s_BMS_Temperatures_4_Cell_T_29);
    daqser::set("Car_Data.BMS_Temperatures_4.Cell_T_30", (bool)s_BMS_Temperatures_4_Cell_T_30);
    daqser::set("Car_Data.BMS_Temperatures_4.Cell_T_31", (bool)s_BMS_Temperatures_4_Cell_T_31);
    daqser::set("Car_Data.BMS_Temperatures_4.Cell_T_32", (bool)s_BMS_Temperatures_4_Cell_T_32);
    daqser::set("Car_Data.BMS_Temperatures_4.Cell_T_33", (bool)s_BMS_Temperatures_4_Cell_T_33);
    daqser::set("Car_Data.BMS_Temperatures_4.Cell_T_34", (bool)s_BMS_Temperatures_4_Cell_T_34);
    // BMS_Temperatures_5
    daqser::set("Car_Data.BMS_Temperatures_5.Cell_T_35", (bool)s_BMS_Temperatures_5_Cell_T_35);
    daqser::set("Car_Data.BMS_Temperatures_5.Cell_T_36", (bool)s_BMS_Temperatures_5_Cell_T_36);
    daqser::set("Car_Data.BMS_Temperatures_5.Cell_T_37", (bool)s_BMS_Temperatures_5_Cell_T_37);
    daqser::set("Car_Data.BMS_Temperatures_5.Cell_T_38", (bool)s_BMS_Temperatures_5_Cell_T_38);
    daqser::set("Car_Data.BMS_Temperatures_5.Cell_T_39", (bool)s_BMS_Temperatures_5_Cell_T_39);
    daqser::set("Car_Data.BMS_Temperatures_5.Cell_T_40", (bool)s_BMS_Temperatures_5_Cell_T_40);
    daqser::set("Car_Data.BMS_Temperatures_5.Cell_T_41", (bool)s_BMS_Temperatures_5_Cell_T_41);
    // BMS_Temperatures_6
    daqser::set("Car_Data.BMS_Temperatures_6.Cell_T_42", (bool)s_BMS_Temperatures_6_Cell_T_42);
    daqser::set("Car_Data.BMS_Temperatures_6.Cell_T_43", (bool)s_BMS_Temperatures_6_Cell_T_43);
    daqser::set("Car_Data.BMS_Temperatures_6.Cell_T_44", (bool)s_BMS_Temperatures_6_Cell_T_44);
    daqser::set("Car_Data.BMS_Temperatures_6.Cell_T_45", (bool)s_BMS_Temperatures_6_Cell_T_45);
    daqser::set("Car_Data.BMS_Temperatures_6.Cell_T_46", (bool)s_BMS_Temperatures_6_Cell_T_46);
    daqser::set("Car_Data.BMS_Temperatures_6.Cell_T_47", (bool)s_BMS_Temperatures_6_Cell_T_47);
    daqser::set("Car_Data.BMS_Temperatures_6.Cell_T_48", (bool)s_BMS_Temperatures_6_Cell_T_48);
    // BMS_Temperatures_7
    daqser::set("Car_Data.BMS_Temperatures_7.Cell_T_49", (bool)s_BMS_Temperatures_7_Cell_T_49);
    daqser::set("Car_Data.BMS_Temperatures_7.Cell_T_50", (bool)s_BMS_Temperatures_7_Cell_T_50);
    daqser::set("Car_Data.BMS_Temperatures_7.Cell_T_51", (bool)s_BMS_Temperatures_7_Cell_T_51);
    daqser::set("Car_Data.BMS_Temperatures_7.Cell_T_52", (bool)s_BMS_Temperatures_7_Cell_T_52);
    daqser::set("Car_Data.BMS_Temperatures_7.Cell_T_53", (bool)s_BMS_Temperatures_7_Cell_T_53);
    daqser::set("Car_Data.BMS_Temperatures_7.Cell_T_54", (bool)s_BMS_Temperatures_7_Cell_T_54);
    daqser::set("Car_Data.BMS_Temperatures_7.Cell_T_55", (bool)s_BMS_Temperatures_7_Cell_T_55);
    // BMS_Temperatures_8
    daqser::set("Car_Data.BMS_Temperatures_8.Cell_T_56", (bool)s_BMS_Temperatures_8_Cell_T_56);
    daqser::set("Car_Data.BMS_Temperatures_8.Cell_T_57", (bool)s_BMS_Temperatures_8_Cell_T_57);
    daqser::set("Car_Data.BMS_Temperatures_8.Cell_T_58", (bool)s_BMS_Temperatures_8_Cell_T_58);
    daqser::set("Car_Data.BMS_Temperatures_8.Cell_T_59", (bool)s_BMS_Temperatures_8_Cell_T_59);
    daqser::set("Car_Data.BMS_Temperatures_8.Cell_T_60", (bool)s_BMS_Temperatures_8_Cell_T_60);
    daqser::set("Car_Data.BMS_Temperatures_8.Cell_T_61", (bool)s_BMS_Temperatures_8_Cell_T_61);
    daqser::set("Car_Data.BMS_Temperatures_8.Cell_T_62", (bool)s_BMS_Temperatures_8_Cell_T_62);
    // BMS_Temperatures_9
    daqser::set("Car_Data.BMS_Temperatures_9.Cell_T_63", (bool)s_BMS_Temperatures_9_Cell_T_63);
    daqser::set("Car_Data.BMS_Temperatures_9.Cell_T_64", (bool)s_BMS_Temperatures_9_Cell_T_64);
    daqser::set("Car_Data.BMS_Temperatures_9.Cell_T_65", (bool)s_BMS_Temperatures_9_Cell_T_65);
    daqser::set("Car_Data.BMS_Temperatures_9.Cell_T_66", (bool)s_BMS_Temperatures_9_Cell_T_66);
    daqser::set("Car_Data.BMS_Temperatures_9.Cell_T_67", (bool)s_BMS_Temperatures_9_Cell_T_67);
    daqser::set("Car_Data.BMS_Temperatures_9.Cell_T_68", (bool)s_BMS_Temperatures_9_Cell_T_68);
    daqser::set("Car_Data.BMS_Temperatures_9.Cell_T_69", (bool)s_BMS_Temperatures_9_Cell_T_69);
    // BMS_Temperatures_10
    daqser::set("Car_Data.BMS_Temperatures_10.Cell_T_70", (bool)s_BMS_Temperatures_10_Cell_T_70);
    daqser::set("Car_Data.BMS_Temperatures_10.Cell_T_71", (bool)s_BMS_Temperatures_10_Cell_T_71);
    daqser::set("Car_Data.BMS_Temperatures_10.Cell_T_72", (bool)s_BMS_Temperatures_10_Cell_T_72);
    daqser::set("Car_Data.BMS_Temperatures_10.Cell_T_73", (bool)s_BMS_Temperatures_10_Cell_T_73);
    daqser::set("Car_Data.BMS_Temperatures_10.Cell_T_74", (bool)s_BMS_Temperatures_10_Cell_T_74);
    daqser::set("Car_Data.BMS_Temperatures_10.Cell_T_75", (bool)s_BMS_Temperatures_10_Cell_T_75);
    daqser::set("Car_Data.BMS_Temperatures_10.Cell_T_76", (bool)s_BMS_Temperatures_10_Cell_T_76);
    // BMS_Temperatures_11
    daqser::set("Car_Data.BMS_Temperatures_11.Cell_T_77", (bool)s_BMS_Temperatures_11_Cell_T_77);
    daqser::set("Car_Data.BMS_Temperatures_11.Cell_T_78", (bool)s_BMS_Temperatures_11_Cell_T_78);
    daqser::set("Car_Data.BMS_Temperatures_11.Cell_T_79", (bool)s_BMS_Temperatures_11_Cell_T_79);
    daqser::set("Car_Data.BMS_Temperatures_11.Cell_T_80", (bool)s_BMS_Temperatures_11_Cell_T_80);
    daqser::set("Car_Data.BMS_Temperatures_11.Cell_T_81", (bool)s_BMS_Temperatures_11_Cell_T_81);
    daqser::set("Car_Data.BMS_Temperatures_11.Cell_T_82", (bool)s_BMS_Temperatures_11_Cell_T_82);
    daqser::set("Car_Data.BMS_Temperatures_11.Cell_T_83", (bool)s_BMS_Temperatures_11_Cell_T_83);
    // BMS_Temperatures_12
    daqser::set("Car_Data.BMS_Temperatures_12.Cell_T_84", (bool)s_BMS_Temperatures_12_Cell_T_84);
    daqser::set("Car_Data.BMS_Temperatures_12.Cell_T_85", (bool)s_BMS_Temperatures_12_Cell_T_85);
    daqser::set("Car_Data.BMS_Temperatures_12.Cell_T_86", (bool)s_BMS_Temperatures_12_Cell_T_86);
    daqser::set("Car_Data.BMS_Temperatures_12.Cell_T_87", (bool)s_BMS_Temperatures_12_Cell_T_87);
    daqser::set("Car_Data.BMS_Temperatures_12.Cell_T_88", (bool)s_BMS_Temperatures_12_Cell_T_88);
    daqser::set("Car_Data.BMS_Temperatures_12.Cell_T_89", (bool)s_BMS_Temperatures_12_Cell_T_89);
    daqser::set("Car_Data.BMS_Temperatures_12.Cell_T_90", (bool)s_BMS_Temperatures_12_Cell_T_90);
    // BMS_Temperatures_13
    daqser::set("Car_Data.BMS_Temperatures_13.Cell_T_91", (bool)s_BMS_Temperatures_13_Cell_T_91);
    daqser::set("Car_Data.BMS_Temperatures_13.Cell_T_92", (bool)s_BMS_Temperatures_13_Cell_T_92);
    daqser::set("Car_Data.BMS_Temperatures_13.Cell_T_93", (bool)s_BMS_Temperatures_13_Cell_T_93);
    daqser::set("Car_Data.BMS_Temperatures_13.Cell_T_94", (bool)s_BMS_Temperatures_13_Cell_T_94);
    daqser::set("Car_Data.BMS_Temperatures_13.Cell_T_95", (bool)s_BMS_Temperatures_13_Cell_T_95);
    daqser::set("Car_Data.BMS_Temperatures_13.Cell_T_96", (bool)s_BMS_Temperatures_13_Cell_T_96);
    daqser::set("Car_Data.BMS_Temperatures_13.Cell_T_97", (bool)s_BMS_Temperatures_13_Cell_T_97);
    // BMS_Temperatures_14
    daqser::set("Car_Data.BMS_Temperatures_14.Cell_T_98", (bool)s_BMS_Temperatures_14_Cell_T_98);
    daqser::set("Car_Data.BMS_Temperatures_14.Cell_T_99", (bool)s_BMS_Temperatures_14_Cell_T_99);
    daqser::set("Car_Data.BMS_Temperatures_14.Cell_T_100", (bool)s_BMS_Temperatures_14_Cell_T_100);
    daqser::set("Car_Data.BMS_Temperatures_14.Cell_T_101", (bool)s_BMS_Temperatures_14_Cell_T_101);
    daqser::set("Car_Data.BMS_Temperatures_14.Cell_T_102", (bool)s_BMS_Temperatures_14_Cell_T_102);
    daqser::set("Car_Data.BMS_Temperatures_14.Cell_T_103", (bool)s_BMS_Temperatures_14_Cell_T_103);
    daqser::set("Car_Data.BMS_Temperatures_14.Cell_T_104", (bool)s_BMS_Temperatures_14_Cell_T_104);
    // BMS_Temperatures_15
    daqser::set("Car_Data.BMS_Temperatures_15.Cell_T_105", (bool)s_BMS_Temperatures_15_Cell_T_105);
    daqser::set("Car_Data.BMS_Temperatures_15.Cell_T_106", (bool)s_BMS_Temperatures_15_Cell_T_106);
    daqser::set("Car_Data.BMS_Temperatures_15.Cell_T_107", (bool)s_BMS_Temperatures_15_Cell_T_107);
    daqser::set("Car_Data.BMS_Temperatures_15.Cell_T_108", (bool)s_BMS_Temperatures_15_Cell_T_108);
    daqser::set("Car_Data.BMS_Temperatures_15.Cell_T_109", (bool)s_BMS_Temperatures_15_Cell_T_109);
    daqser::set("Car_Data.BMS_Temperatures_15.Cell_T_110", (bool)s_BMS_Temperatures_15_Cell_T_110);
    daqser::set("Car_Data.BMS_Temperatures_15.Cell_T_111", (bool)s_BMS_Temperatures_15_Cell_T_111);
    // BMS_SOE
    daqser::set("Car_Data.BMS_SOE.Max_Discharge_Current", (float)s_BMS_SOE_Max_Discharge_Current);
    daqser::set("Car_Data.BMS_SOE.Max_Regen_Current", (float)s_BMS_SOE_Max_Regen_Current);
    daqser::set("Car_Data.BMS_SOE.Battery_Voltage", (float)s_BMS_SOE_Battery_Voltage);
    daqser::set("Car_Data.BMS_SOE.Battery_Temperature", (bool)s_BMS_SOE_Battery_Temperature);
    daqser::set("Car_Data.BMS_SOE.Battery_Current", (float)s_BMS_SOE_Battery_Current);
    // BMS_Faults
    daqser::set("Car_Data.BMS_Faults.Fault_Summary", (bool)s_BMS_Faults_Fault_Summary);
    daqser::set("Car_Data.BMS_Faults.Undervoltage_Fault", (bool)s_BMS_Faults_Undervoltage_Fault);
    daqser::set("Car_Data.BMS_Faults.Overvoltage_Fault", (bool)s_BMS_Faults_Overvoltage_Fault);
    daqser::set("Car_Data.BMS_Faults.Undertemperature_Fault", (bool)s_BMS_Faults_Undertemperature_Fault);
    daqser::set("Car_Data.BMS_Faults.Overtemperature_Fault", (bool)s_BMS_Faults_Overtemperature_Fault);
    daqser::set("Car_Data.BMS_Faults.Overcurrent_Fault", (bool)s_BMS_Faults_Overcurrent_Fault);
    daqser::set("Car_Data.BMS_Faults.External_Kill_Fault", (bool)s_BMS_Faults_External_Kill_Fault);
    daqser::set("Car_Data.BMS_Faults.Open_Wire_Fault", (bool)s_BMS_Faults_Open_Wire_Fault);
    // BMS_Status
    daqser::set("Car_Data.BMS_Status.Max_Cell_Temp", (bool)s_BMS_Status_Max_Cell_Temp);
    daqser::set("Car_Data.BMS_Status.Min_Cell_Temp", (bool)s_BMS_Status_Min_Cell_Temp);
    daqser::set("Car_Data.BMS_Status.Max_Cell_Voltage", (bool)s_BMS_Status_Max_Cell_Voltage);
    daqser::set("Car_Data.BMS_Status.Min_Cell_Voltage", (bool)s_BMS_Status_Min_Cell_Voltage);
    daqser::set("Car_Data.BMS_Status.BMS_SOC", (bool)s_BMS_Status_BMS_SOC);
#endif
#ifdef RX_PDM
    // PDM_Current_Sensing
    daqser::set("Car_Data.PDM_Current_Sensing.Unreg_A", (double)s_PDM_Current_Sensing_Unreg_A);
    daqser::set("Car_Data.PDM_Current_Sensing.FiveVolt_A", (double)s_PDM_Current_Sensing_FiveVolt_A);
#endif
#ifdef RX_WHEEL
    // Wheel_Message
    daqser::set("Car_Data.Wheel_Message.Wheel_Temp", (float)s_Wheel_Message_Wheel_Temp);
    daqser::set("Car_Data.Wheel_Message.Wheel_Speed", (float)s_Wheel_Message_Wheel_Speed);
#endif
#ifdef RX_SHUTDOWN
    // Shutdown_Status
    daqser::set("Car_Data.Shutdown_Status.Voltage_Sag", (bool)s_Shutdown_Status_Voltage_Sag);
    // Shutdown_1
    daqser::set("Car_Data.Shutdown_1.Voltage_Sag", (bool)s_Shutdown_1_Voltage_Sag);
    // Shutdown_2
    daqser::set("Car_Data.Shutdown_2.Voltage_Sag", (bool)s_Shutdown_2_Voltage_Sag);
    // Shutdown_3
    daqser::set("Car_Data.Shutdown_3.Voltage_Sag", (bool)s_Shutdown_3_Voltage_Sag);
    // Shutdown_4
    daqser::set("Car_Data.Shutdown_4.Voltage_Sag", (bool)s_Shutdown_4_Voltage_Sag);
    // Shutdown_5
    daqser::set("Car_Data.Shutdown_5.Voltage_Sag", (bool)s_Shutdown_5_Voltage_Sag);
    // Shutdown_6
    daqser::set("Car_Data.Shutdown_6.Voltage_Sag", (bool)s_Shutdown_6_Voltage_Sag);
#endif
#ifdef RX_ETC
    // throttle_tx
    daqser::set("Car_Data.throttle_tx.Throttle_percent", (bool)s_throttle_tx_Throttle_percent);
    daqser::set("Car_Data.throttle_tx.Throttle_active", (bool)s_throttle_tx_Throttle_active);
    // brake_tx
    daqser::set("Car_Data.brake_tx.Brake_pedal", (bool)s_brake_tx_Brake_pedal);
#endif
#ifdef RX_VCU
    // Drive_Status
    daqser::set("Car_Data.Drive_Status.Drive_State", (bool)s_Drive_Status_Drive_State);
#endif

    }

}

#endif // !NATIVE

#endif // __DAQSER_CAN_H__