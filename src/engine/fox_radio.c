/*
 * File: fox_title.c
 * System: Radio
 * Description: Starfox Radio Handler
 */

#include "prevent_bss_reordering.h"
#include "global.h"
#include "assets/ast_allies.h"
#include "assets/ast_corneria.h"
#include "assets/ast_meteo.h"
#include "assets/ast_training.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_star_wolf.h"
#include "assets/ast_great_fox.h"
#include "assets/ast_area_6.h"
#include "assets/ast_title.h"
#include "assets/ast_zoness.h"
#include "port/hooks/Events.h"
#include "port/mods/PortEnhancements.h"

u16** gRadioMsgList;
s32 gRadioMsgListIndex;
s32 gRadioPrintPosX;
s32 gRadioPrintPosY;
f32 gRadioTextBoxPosX;
f32 gRadioTextBoxPosY;
f32 gRadioTextBoxScaleX;
f32 gRadioPortraitPosX;
f32 gRadioPortraitPosY;

s32 gRadioMsgPri = 0;

void func_radio_800BA760(void) {
    RCP_SetupDL_36();
    if (gRadioTextBoxScaleY == 1.3f) {
        gMsgCharIsPrinting = Message_IsPrintingChar(gRadioMsg, gRadioMsgCharIndex);
    }
}

s32 func_radio_800BA7BC(u16* msg, s32 priority) {
    if (priority == gRadioMsgPri) {
        return 0;
    }

    if (priority < gRadioMsgPri) {
        return 1;
    }

    if (gRadioMsgPri < priority) {
        gRadioMsgPri = priority;
        return 2;
    }
}

void Radio_PlayMessage(u16* msg, RadioCharacterId d) {
    TeamId teamId;
    s32 pad;
    s32 priority;
    msg = SEGMENTED_TO_VIRTUAL(msg);
    

    switch (msg[0]) {
        default:
        case MSGCHAR_PRI0:
            priority = 0;
            break;
        case MSGCHAR_PRI1:
            priority = 1;
            break;
        case MSGCHAR_PRI2:
            priority = 2;
            break;
        case MSGCHAR_PRI3:
            priority = 3;
            break;
    }

    if (gGameState == GSTATE_PLAY) {
        if ((d == RCID_FALCO) || (d == RCID_SLIPPY) || (d == RCID_PEPPY)) {
            if (d == RCID_FALCO) {
                teamId = TEAM_ID_FALCO;
            }
            if (d == RCID_SLIPPY) {
                teamId = TEAM_ID_SLIPPY;
            }
            if (d == RCID_PEPPY) {
                teamId = TEAM_ID_PEPPY;
            }
            if ((gTeamShields[teamId] <= 0) && (gTeamShields[teamId] != -2)) {
                return;
            }
        }
    }
    srand(time(NULL));
    RadioCharacterId character;
    if (CVarGetInteger("gPortraitRando", 0) == 1) {
        RadioCharacterId charIndex[] = { RCID_FALCO,         RCID_SLIPPY,       RCID_PEPPY,        RCID_FOX,
                                         RCID_KATT,          RCID_ANDROSS,      RCID_JAMES,        RCID_GEN_PEPPER,
                                         RCID_BOSS_CORNERIA, RCID_ROB64,        RCID_BOSS_METEO,   RCID_BOSS_CORNERIA2,
                                         RCID_BOSS_AREA6,    RCID_BOSS_ZONESS,  RCID_BOSS_SECTORX, RCID_BOSS_SECTORY,
                                         RCID_BILL,          RCID_CAIMAN_AREA6, RCID_BOSS_MACBETH, RCID_WOLF,
                                         RCID_PIGMA,         RCID_LEON,         RCID_ANDREW,       RCID_TR };
        character = charIndex[RAND_INT(ARRAY_COUNT(charIndex))];
    } else {
         character = d;
    }
    if (CVarGetInteger("gDialogueRando", 0) == 1) {
    u16* msgList[] = {
        gMsg_ID_1,     gMsg_ID_60,    gMsg_ID_10,    gMsg_ID_20,    gMsg_ID_30,    gMsg_ID_40,    gMsg_ID_50,
        gMsg_ID_1200,  gMsg_ID_1210,  gMsg_ID_1220,  gMsg_ID_1230,  gMsg_ID_1240,  gMsg_ID_1250,  gMsg_ID_1260,
        gMsg_ID_1270,  gMsg_ID_1280,  gMsg_ID_1290,  gMsg_ID_1300,  gMsg_ID_1310,  gMsg_ID_1320,  gMsg_ID_1330,
        gMsg_ID_1340,  gMsg_ID_1350,  gMsg_ID_1360,  gMsg_ID_1370,  gMsg_ID_1380,  gMsg_ID_1390,  gMsg_ID_1400,
        gMsg_ID_1410,  gMsg_ID_1420,  gMsg_ID_1430,  gMsg_ID_1440,  gMsg_ID_1450,  gMsg_ID_1460,  gMsg_ID_1470,
        gMsg_ID_2005,  gMsg_ID_2010,  gMsg_ID_2020,  gMsg_ID_2030,  gMsg_ID_2040,  gMsg_ID_2050,  gMsg_ID_2055,
        gMsg_ID_2058,  gMsg_ID_2061,  gMsg_ID_2062,  gMsg_ID_2080,  gMsg_ID_2090,  gMsg_ID_2095,  gMsg_ID_2110,
        gMsg_ID_2115,  gMsg_ID_2118,  gMsg_ID_2140,  gMsg_ID_2165,  gMsg_ID_2166,  gMsg_ID_2167,  gMsg_ID_2180,
        gMsg_ID_2181,  gMsg_ID_2185,  gMsg_ID_2188,  gMsg_ID_2200,  gMsg_ID_2210,  gMsg_ID_2220,  gMsg_ID_2225,
        gMsg_ID_2230,  gMsg_ID_2233,  gMsg_ID_2282,  gMsg_ID_2240,  gMsg_ID_2250,  gMsg_ID_2260,  gMsg_ID_2263,
        gMsg_ID_2265,  gMsg_ID_2270,  gMsg_ID_2275,  gMsg_ID_2280,  gMsg_ID_2290,  gMsg_ID_2291,  gMsg_ID_2292,
        gMsg_ID_2293,  gMsg_ID_2294,  gMsg_ID_2295,  gMsg_ID_2296,  gMsg_ID_2298,  gMsg_ID_2299,  gMsg_ID_2300,
        gMsg_ID_2305,  gMsg_ID_2310,  gMsg_ID_2320,  gMsg_ID_2335,  gMsg_ID_2336,  gMsg_ID_2337,  gMsg_ID_3005,
        gMsg_ID_3010,  gMsg_ID_3015,  gMsg_ID_3020,  gMsg_ID_3025,  gMsg_ID_3026,  gMsg_ID_3040,  gMsg_ID_3041,
        gMsg_ID_3042,  gMsg_ID_3050,  gMsg_ID_3100,  gMsg_ID_3110,  gMsg_ID_3120,  gMsg_ID_3300,  gMsg_ID_3310,
        gMsg_ID_3315,  gMsg_ID_3320,  gMsg_ID_3321,  gMsg_ID_3322,  gMsg_ID_3330,  gMsg_ID_3340,  gMsg_ID_3345,
        gMsg_ID_3350,  gMsg_ID_3360,  gMsg_ID_3370,  gMsg_ID_3371,  gMsg_ID_4010,  gMsg_ID_4011,  gMsg_ID_4012,
        gMsg_ID_4013,  gMsg_ID_4020,  gMsg_ID_4021,  gMsg_ID_4022,  gMsg_ID_4023,  gMsg_ID_4024,  gMsg_ID_4030,
        gMsg_ID_4031,  gMsg_ID_4040,  gMsg_ID_4050,  gMsg_ID_4075,  gMsg_ID_4080,  gMsg_ID_4082,  gMsg_ID_4083,
        gMsg_ID_4091,  gMsg_ID_4092,  gMsg_ID_4093,  gMsg_ID_4094,  gMsg_ID_4095,  gMsg_ID_4096,  gMsg_ID_4097,
        gMsg_ID_4098,  gMsg_ID_4099,  gMsg_ID_4100,  gMsg_ID_4101,  gMsg_ID_4102,  gMsg_ID_4103,  gMsg_ID_4110,
        gMsg_ID_4111,  gMsg_ID_4112,  gMsg_ID_4113,  gMsg_ID_5000,  gMsg_ID_5010,  gMsg_ID_5060,  gMsg_ID_5080,
        gMsg_ID_5100,  gMsg_ID_5110,  gMsg_ID_5130,  gMsg_ID_5220,  gMsg_ID_5230,  gMsg_ID_5300,  gMsg_ID_5310,
        gMsg_ID_5311,  gMsg_ID_5312,  gMsg_ID_5313,  gMsg_ID_5314,  gMsg_ID_5350,  gMsg_ID_5360,  gMsg_ID_5380,
        gMsg_ID_5400,  gMsg_ID_5410,  gMsg_ID_5420,  gMsg_ID_5430,  gMsg_ID_5460,  gMsg_ID_5470,  gMsg_ID_5473,
        gMsg_ID_5474,  gMsg_ID_5475,  gMsg_ID_5492,  gMsg_ID_5493,  gMsg_ID_5494,  gMsg_ID_5495,  gMsg_ID_5496,
        gMsg_ID_5497,  gMsg_ID_5498,  gMsg_ID_5499,  gMsg_ID_5500,  gMsg_ID_5501,  gMsg_ID_5502,  gMsg_ID_5503,
        gMsg_ID_5504,  gMsg_ID_5505,  gMsg_ID_5506,  gMsg_ID_6010,  gMsg_ID_6011,  gMsg_ID_6012,  gMsg_ID_6013,
        gMsg_ID_6014,  gMsg_ID_6020,  gMsg_ID_6021,  gMsg_ID_6024,  gMsg_ID_6025,  gMsg_ID_6026,  gMsg_ID_6027,
        gMsg_ID_6028,  gMsg_ID_6029,  gMsg_ID_6036,  gMsg_ID_6038,  gMsg_ID_6041,  gMsg_ID_6042,  gMsg_ID_6045,
        gMsg_ID_6050,  gMsg_ID_6051,  gMsg_ID_6055,  gMsg_ID_6066,  gMsg_ID_6067,  gMsg_ID_6068,  gMsg_ID_6069,
        gMsg_ID_6071,  gMsg_ID_6072,  gMsg_ID_6073,  gMsg_ID_6074,  gMsg_ID_6075,  gMsg_ID_6076,  gMsg_ID_6077,
        gMsg_ID_6078,  gMsg_ID_6079,  gMsg_ID_6080,  gMsg_ID_6081,  gMsg_ID_6082,  gMsg_ID_6090,  gMsg_ID_6100,
        gMsg_ID_6101,  gMsg_ID_7005,  gMsg_ID_7006,  gMsg_ID_7011,  gMsg_ID_7012,  gMsg_ID_7013,  gMsg_ID_7014,
        gMsg_ID_7020,  gMsg_ID_7043,  gMsg_ID_7050,  gMsg_ID_7051,  gMsg_ID_7052,  gMsg_ID_7053,  gMsg_ID_7054,
        gMsg_ID_7061,  gMsg_ID_7064,  gMsg_ID_7065,  gMsg_ID_7066,  gMsg_ID_7070,  gMsg_ID_7083,  gMsg_ID_7084,
        gMsg_ID_7085,  gMsg_ID_7086,  gMsg_ID_7087,  gMsg_ID_7093,  gMsg_ID_7094,  gMsg_ID_7095,  gMsg_ID_7096,
        gMsg_ID_7097,  gMsg_ID_7098,  gMsg_ID_7099,  gMsg_ID_7100,  gMsg_ID_8010,  gMsg_ID_8020,  gMsg_ID_8030,
        gMsg_ID_8040,  gMsg_ID_8045,  gMsg_ID_8050,  gMsg_ID_8060,  gMsg_ID_8070,  gMsg_ID_8080,  gMsg_ID_8100,
        gMsg_ID_8110,  gMsg_ID_8120,  gMsg_ID_8130,  gMsg_ID_8140,  gMsg_ID_8205,  gMsg_ID_8210,  gMsg_ID_8215,
        gMsg_ID_8220,  gMsg_ID_8230,  gMsg_ID_8240,  gMsg_ID_8250,  gMsg_ID_8255,  gMsg_ID_8260,  gMsg_ID_8265,
        gMsg_ID_8300,  gMsg_ID_8310,  gMsg_ID_8320,  gMsg_ID_9000,  gMsg_ID_9010,  gMsg_ID_9100,  gMsg_ID_9110,
        gMsg_ID_9120,  gMsg_ID_9130,  gMsg_ID_9140,  gMsg_ID_9150,  gMsg_ID_9151,  gMsg_ID_9152,  gMsg_ID_9153,
        gMsg_ID_9160,  gMsg_ID_9170,  gMsg_ID_9180,  gMsg_ID_9190,  gMsg_ID_9200,  gMsg_ID_9210,  gMsg_ID_9211,
        gMsg_ID_9212,  gMsg_ID_9213,  gMsg_ID_9220,  gMsg_ID_9230,  gMsg_ID_9240,  gMsg_ID_9250,  gMsg_ID_9260,
        gMsg_ID_9270,  gMsg_ID_9275,  gMsg_ID_9280,  gMsg_ID_9285,  gMsg_ID_9289,  gMsg_ID_9290,  gMsg_ID_9300,
        gMsg_ID_9310,  gMsg_ID_9320,  gMsg_ID_9322,  gMsg_ID_9323,  gMsg_ID_9324,  gMsg_ID_9325,  gMsg_ID_9330,
        gMsg_ID_9340,  gMsg_ID_9350,  gMsg_ID_9360,  gMsg_ID_9365,  gMsg_ID_9366,  gMsg_ID_9367,  gMsg_ID_9368,
        gMsg_ID_9369,  gMsg_ID_9375,  gMsg_ID_9380,  gMsg_ID_9385,  gMsg_ID_9390,  gMsg_ID_9395,  gMsg_ID_9400,
        gMsg_ID_9405,  gMsg_ID_9411,  gMsg_ID_9420,  gMsg_ID_9425,  gMsg_ID_9426,  gMsg_ID_9427,  gMsg_ID_9428,
        gMsg_ID_9429,  gMsg_ID_9430,  gMsg_ID_9431,  gMsg_ID_9432,  gMsg_ID_9433,  gMsg_ID_9434,  gMsg_ID_9436,
        gMsg_ID_9437,  gMsg_ID_9438,  gMsg_ID_10010, gMsg_ID_10020, gMsg_ID_10040, gMsg_ID_10050, gMsg_ID_10060,
        gMsg_ID_10070, gMsg_ID_10080, gMsg_ID_10200, gMsg_ID_10210, gMsg_ID_10220, gMsg_ID_10230, gMsg_ID_10255,
        gMsg_ID_10300, gMsg_ID_10310, gMsg_ID_10320, gMsg_ID_10321, gMsg_ID_10322, gMsg_ID_10323, gMsg_ID_10324,
        gMsg_ID_11010, gMsg_ID_11020, gMsg_ID_11030, gMsg_ID_11040, gMsg_ID_11050, gMsg_ID_11060, gMsg_ID_11100,
        gMsg_ID_11110, gMsg_ID_11120, gMsg_ID_11130, gMsg_ID_11150, gMsg_ID_11160, gMsg_ID_11200, gMsg_ID_11210,
        gMsg_ID_11220, gMsg_ID_11230, gMsg_ID_11240, gMsg_ID_11241, gMsg_ID_14020, gMsg_ID_14030, gMsg_ID_14040,
        gMsg_ID_14045, gMsg_ID_14050, gMsg_ID_14060, gMsg_ID_14070, gMsg_ID_14080, gMsg_ID_14100, gMsg_ID_14110,
        gMsg_ID_14120, gMsg_ID_14130, gMsg_ID_14140, gMsg_ID_14150, gMsg_ID_14160, gMsg_ID_14170, gMsg_ID_14180,
        gMsg_ID_14190, gMsg_ID_14200, gMsg_ID_14210, gMsg_ID_14220, gMsg_ID_14230, gMsg_ID_14300, gMsg_ID_14310,
        gMsg_ID_14320, gMsg_ID_14330, gMsg_ID_14340, gMsg_ID_14350, gMsg_ID_14360, gMsg_ID_14370, gMsg_ID_15010,
        gMsg_ID_15030, gMsg_ID_15040, gMsg_ID_15045, gMsg_ID_15050, gMsg_ID_15051, gMsg_ID_15052, gMsg_ID_15053,
        gMsg_ID_15054, gMsg_ID_15060, gMsg_ID_15100, gMsg_ID_15110, gMsg_ID_15120, gMsg_ID_15130, gMsg_ID_15140,
        gMsg_ID_15200, gMsg_ID_15210, gMsg_ID_15220, gMsg_ID_15230, gMsg_ID_15240, gMsg_ID_15250, gMsg_ID_15251,
        gMsg_ID_15252, gMsg_ID_15253, gMsg_ID_15254, gMsg_ID_16010, gMsg_ID_16020, gMsg_ID_16030, gMsg_ID_16040,
        gMsg_ID_16046, gMsg_ID_16047, gMsg_ID_16050, gMsg_ID_16055, gMsg_ID_16060, gMsg_ID_16080, gMsg_ID_16085,
        gMsg_ID_16090, gMsg_ID_16100, gMsg_ID_16110, gMsg_ID_16120, gMsg_ID_16125, gMsg_ID_16130, gMsg_ID_16135,
        gMsg_ID_16140, gMsg_ID_16150, gMsg_ID_16160, gMsg_ID_16165, gMsg_ID_16170, gMsg_ID_16175, gMsg_ID_16180,
        gMsg_ID_16185, gMsg_ID_16200, gMsg_ID_16210, gMsg_ID_16220, gMsg_ID_16230, gMsg_ID_16240, gMsg_ID_16250,
        gMsg_ID_16260, gMsg_ID_16270, gMsg_ID_16280, gMsg_ID_17010, gMsg_ID_17020, gMsg_ID_17030, gMsg_ID_17100,
        gMsg_ID_17110, gMsg_ID_17120, gMsg_ID_17130, gMsg_ID_17131, gMsg_ID_17140, gMsg_ID_17150, gMsg_ID_17160,
        gMsg_ID_17170, gMsg_ID_17300, gMsg_ID_17310, gMsg_ID_17320, gMsg_ID_17330, gMsg_ID_17350, gMsg_ID_17360,
        gMsg_ID_17370, gMsg_ID_17380, gMsg_ID_17390, gMsg_ID_17400, gMsg_ID_17410, gMsg_ID_17420, gMsg_ID_17430,
        gMsg_ID_17440, gMsg_ID_17450, gMsg_ID_17460, gMsg_ID_17470, gMsg_ID_17471, gMsg_ID_17472, gMsg_ID_17473,
        gMsg_ID_17474, gMsg_ID_17475, gMsg_ID_17476, gMsg_ID_18000, gMsg_ID_18005, gMsg_ID_18006, gMsg_ID_18007,
        gMsg_ID_18010, gMsg_ID_18015, gMsg_ID_18018, gMsg_ID_18020, gMsg_ID_18021, gMsg_ID_18022, gMsg_ID_18025,
        gMsg_ID_18030, gMsg_ID_18031, gMsg_ID_18035, gMsg_ID_18040, gMsg_ID_18045, gMsg_ID_18050, gMsg_ID_18055,
        gMsg_ID_18060, gMsg_ID_18065, gMsg_ID_18066, gMsg_ID_18070, gMsg_ID_18075, gMsg_ID_18080, gMsg_ID_18085,
        gMsg_ID_18090, gMsg_ID_18095, gMsg_ID_18100, gMsg_ID_18105, gMsg_ID_18120, gMsg_ID_18130, gMsg_ID_18140,
        gMsg_ID_18150, gMsg_ID_19010, gMsg_ID_19205, gMsg_ID_19200, gMsg_ID_19210, gMsg_ID_19220, gMsg_ID_19230,
        gMsg_ID_19240, gMsg_ID_19250, gMsg_ID_19325, gMsg_ID_19330, gMsg_ID_19335, gMsg_ID_19340, gMsg_ID_19350,
        gMsg_ID_19355, gMsg_ID_19360, gMsg_ID_19370, gMsg_ID_19400, gMsg_ID_19410, gMsg_ID_19420, gMsg_ID_19430,
        gMsg_ID_19440, gMsg_ID_19450, gMsg_ID_19451, gMsg_ID_19452, gMsg_ID_19453, gMsg_ID_19454, gMsg_ID_19455,
        gMsg_ID_19456, gMsg_ID_19457, gMsg_ID_19458, gMsg_ID_19459, gMsg_ID_19460, gMsg_ID_19461, gMsg_ID_19462,
        gMsg_ID_19463, gMsg_ID_19464, gMsg_ID_19465, gMsg_ID_19466, gMsg_ID_19467, gMsg_ID_19468, gMsg_ID_20010,
        gMsg_ID_20011, gMsg_ID_20012, gMsg_ID_20013, gMsg_ID_20014, gMsg_ID_20015, gMsg_ID_20016, gMsg_ID_20017,
        gMsg_ID_20018, gMsg_ID_20019, gMsg_ID_20020, gMsg_ID_20030, gMsg_ID_20040, gMsg_ID_20050, gMsg_ID_20060,
        gMsg_ID_20070, gMsg_ID_20080, gMsg_ID_20084, gMsg_ID_20085, gMsg_ID_20090, gMsg_ID_20091, gMsg_ID_20092,
        gMsg_ID_20150, gMsg_ID_20160, gMsg_ID_20170, gMsg_ID_20180, gMsg_ID_20190, gMsg_ID_20200, gMsg_ID_20210,
        gMsg_ID_20220, gMsg_ID_20221, gMsg_ID_20222, gMsg_ID_20230, gMsg_ID_20235, gMsg_ID_20236, gMsg_ID_20237,
        gMsg_ID_20238, gMsg_ID_20239, gMsg_ID_20250, gMsg_ID_20260, gMsg_ID_20261, gMsg_ID_20262, gMsg_ID_20263,
        gMsg_ID_20264, gMsg_ID_20265, gMsg_ID_20266, gMsg_ID_20267, gMsg_ID_20268, gMsg_ID_20269, gMsg_ID_20270,
        gMsg_ID_20271, gMsg_ID_20272, gMsg_ID_20273, gMsg_ID_20274, gMsg_ID_20275, gMsg_ID_20276, gMsg_ID_20277,
        gMsg_ID_20278, gMsg_ID_20279, gMsg_ID_20280, gMsg_ID_20281, gMsg_ID_20282, gMsg_ID_20283, gMsg_ID_20284,
        gMsg_ID_20285, gMsg_ID_20286, gMsg_ID_20287, gMsg_ID_20288, gMsg_ID_20289, gMsg_ID_20290, gMsg_ID_20291,
        gMsg_ID_20292, gMsg_ID_20294, gMsg_ID_20296, gMsg_ID_20297, gMsg_ID_20298, gMsg_ID_20299, gMsg_ID_20300,
        gMsg_ID_20301, gMsg_ID_20302, gMsg_ID_20303, gMsg_ID_20304, gMsg_ID_20305, gMsg_ID_20306, gMsg_ID_20307,
        gMsg_ID_20308, gMsg_ID_20309, gMsg_ID_20310, gMsg_ID_20311, gMsg_ID_20312, gMsg_ID_20313, gMsg_ID_20314,
        gMsg_ID_20315, gMsg_ID_20316, gMsg_ID_20317, gMsg_ID_20318, gMsg_ID_20319, gMsg_ID_20320, gMsg_ID_20321,
        gMsg_ID_20326, gMsg_ID_20327, gMsg_ID_20328, gMsg_ID_20329, gMsg_ID_20330, gMsg_ID_20331, gMsg_ID_20332,
        gMsg_ID_20333, gMsg_ID_20337, gMsg_ID_20338, gMsg_ID_20339, gMsg_ID_20340, gMsg_ID_20343, gMsg_ID_20344,
        gMsg_ID_20345, gMsg_ID_21010, gMsg_ID_21020, gMsg_ID_21030, gMsg_ID_21050, gMsg_ID_21060, gMsg_ID_21070,
        gMsg_ID_21071, gMsg_ID_21072, gMsg_ID_21073, gMsg_ID_21080, gMsg_ID_21081, gMsg_ID_21082, gMsg_ID_21083,
        gMsg_ID_21090, gMsg_ID_21091, gMsg_ID_21092, gMsg_ID_21093, gMsg_ID_22000, gMsg_ID_22001, gMsg_ID_22002,
        gMsg_ID_22003, gMsg_ID_22004, gMsg_ID_22005, gMsg_ID_22006, gMsg_ID_22007, gMsg_ID_22008, gMsg_ID_22009,
        gMsg_ID_22010, gMsg_ID_22011, gMsg_ID_22012, gMsg_ID_22013, gMsg_ID_22014, gMsg_ID_22015, gMsg_ID_22016,
        gMsg_ID_22017, gMsg_ID_22018, gMsg_ID_22019, gMsg_ID_22020, gMsg_ID_23000, gMsg_ID_23001, gMsg_ID_23002,
        gMsg_ID_23003, gMsg_ID_23004, gMsg_ID_23005, gMsg_ID_23006, gMsg_ID_23007, gMsg_ID_23008, gMsg_ID_23009,
        gMsg_ID_23010, gMsg_ID_23011, gMsg_ID_23012, gMsg_ID_23013, gMsg_ID_23014, gMsg_ID_23015, gMsg_ID_23016,
        gMsg_ID_23017, gMsg_ID_23018, gMsg_ID_23019, gMsg_ID_23020, gMsg_ID_23021, gMsg_ID_23022, gMsg_ID_23023,
        gMsg_ID_23024, gMsg_ID_23025, gMsg_ID_23026, gMsg_ID_23027, gMsg_ID_23028, gMsg_ID_23029, gMsg_ID_23030,
        gMsg_ID_23031, gMsg_ID_23032
    };
        msg = msgList[RAND_INT(ARRAY_COUNT(msgList))];
    }
    if ((gRadioState != 0) && (func_radio_800BA7BC(msg, priority) == 1)) {
        return;
    }
    int alternateChance = RAND_INT(100);
    gRadioMsgPri = priority;
    gRadioMsgRadioId = character;

    if (((character == RCID_FOX) || (character == RCID_FOX_RED)) && ((gExpertMode &&
        CVarGetInteger("gPortraitRando", 0) == 0) || ((CVarGetInteger("gPortraitRando", 0) == 1) && alternateChance < 50))) {
        gRadioMsgRadioId = RCID_FOX_EXPERT;
    }
    
    if ((CVarGetInteger("gPortraitRando", 0) == 0 && gCurrentLevel == LEVEL_VENOM_2) ||
        (CVarGetInteger("gPortraitRando", 0) == 1 && alternateChance < 50)) {
        switch (character) {
            case RCID_WOLF:
                gRadioMsgRadioId = RCID_WOLF_2;
                break;
            case RCID_PIGMA:
                gRadioMsgRadioId = RCID_PIGMA_2;
                break;
            case RCID_LEON:
                gRadioMsgRadioId = RCID_LEON_2;
                break;
            case RCID_ANDREW:
                gRadioMsgRadioId = RCID_ANDREW_2;
                break;
        }
    }

    gRadioMsg = msg;
    gRadioState = 100;

    gRadioMsgId = Message_IdFromPtr(msg);
    Audio_PlayVoice(gRadioMsgId);
}

void Radio_CalculatePositions() {
    if (CVarGetInteger("gRadioCommBox.expand", 0) == 1) {
        switch (gGameState) {
            case GSTATE_TITLE:
                gRadioPrintPosY = 176;
                gRadioPrintPosX = OTRGetRectDimensionFromLeftEdgeOverride(85.0f);
                gRadioTextBoxPosX = OTRGetRectDimensionFromLeftEdgeOverride(80.0f);
                gRadioTextBoxPosY = 174.0f;
                gRadioTextBoxScaleX = 4.63f;
                gRadioPortraitPosX = OTRGetRectDimensionFromLeftEdgeOverride(32.0f);
                gRadioPortraitPosY = 174.0f;
                break;

            case GSTATE_ENDING:
                gRadioPrintPosY = 176;
                gRadioPrintPosX = 85.0f;
                gRadioTextBoxPosX = 80.0f;
                gRadioTextBoxPosY = 174.0f;
                gRadioTextBoxScaleX = 4.63f;
                gRadioPortraitPosX = 32.0f;
                gRadioPortraitPosY = 174.0f;
                break;

            case GSTATE_PLAY:
                gRadioPrintPosY = 180;
                gRadioPrintPosX = OTRGetRectDimensionFromLeftEdgeOverride(79.0f);
                gRadioTextBoxPosX = OTRGetRectDimensionFromLeftEdgeOverride(74.0f);
                gRadioTextBoxPosY = 178.0f;
                gRadioTextBoxScaleX = 4.53f;
                gRadioPortraitPosX = OTRGetRectDimensionFromLeftEdgeOverride(26.0f);
                gRadioPortraitPosY = 178.0f;
                break;
        }
    } else {
        switch (gGameState) {
            case GSTATE_TITLE:
            case GSTATE_ENDING:
                gRadioPrintPosY = 176;
                gRadioPrintPosX = 85;
                gRadioTextBoxPosX = 80.0f;
                gRadioTextBoxPosY = 174.0f;
                gRadioTextBoxScaleX = 4.63f;
                gRadioPortraitPosX = 32.0f;
                gRadioPortraitPosY = 174.0f;
                break;

            case GSTATE_PLAY:
                gRadioPrintPosY = 180;
                gRadioPrintPosX = 79;
                gRadioTextBoxPosX = 74.0f;
                gRadioTextBoxPosY = 178.0f;
                gRadioTextBoxScaleX = 4.53f;
                gRadioPortraitPosX = 26.0f;
                gRadioPortraitPosY = 178.0f;
                break;
        }
    }
}

s32 sRadioUseRedBox;

void func_radio_800BAAE8(void) {
    static f32 D_800D4A74 = -1.0f;
    u16* radioPortraitTex = NULL;
    s32 mirror;
    s32 i;
    f32 sp38;
    f32 temp_fa0;

    sRadioUseRedBox = false;

    mirror = false;
    CALL_EVENT(PreSetupRadioMsgEvent, &sRadioUseRedBox);
    switch (gCurrentRadioPortrait) {
        case RCID_FOX_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FOX:
            radioPortraitTex = aFoxPortraitTex;
            break;
        case RCID_FOX_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FOX + 1:
            radioPortraitTex = D_1006000;
            break;
        case RCID_FOX_EXPERT:
            radioPortraitTex = D_1006F20;
            break;
        case RCID_FOX_EXPERT + 1:
            radioPortraitTex = D_1007E40;
            break;
        case RCID_FALCO_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FALCO:
            radioPortraitTex = aFalcoPortraitTex;
            break;
        case RCID_FALCO_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FALCO + 1:
            radioPortraitTex = D_10041C0;
            break;
        case RCID_SLIPPY_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_SLIPPY:
            radioPortraitTex = aSlippyPortraitTex;
            break;
        case RCID_SLIPPY_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_SLIPPY + 1:
            radioPortraitTex = D_100E820;
            break;
        case RCID_PEPPY_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_PEPPY:
            radioPortraitTex = aPeppyPortraitTex;
            break;
        case RCID_PEPPY_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_PEPPY + 1:
            radioPortraitTex = D_100C9E0;
            break;
        case RCID_WOLF:
            radioPortraitTex = D_STAR_WOLF_F00B580;
            break;
        case RCID_WOLF + 1:
            radioPortraitTex = D_STAR_WOLF_F00C4A0;
            break;
        case RCID_PIGMA:
            radioPortraitTex = D_STAR_WOLF_F003C80;
            break;
        case RCID_PIGMA + 1:
            radioPortraitTex = D_STAR_WOLF_F004BA0;
            break;
        case RCID_LEON:
            radioPortraitTex = D_STAR_WOLF_F007900;
            break;
        case RCID_LEON + 1:
            radioPortraitTex = D_STAR_WOLF_F008820;
            break;
        case RCID_ANDREW:
            radioPortraitTex = D_STAR_WOLF_F000000;
            break;
        case RCID_ANDREW + 1:
            radioPortraitTex = D_STAR_WOLF_F000F20;
            break;
        case RCID_WOLF_2:
            radioPortraitTex = D_STAR_WOLF_F00D3C0;
            break;
        case RCID_WOLF_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F00E2E0;
            break;
        case RCID_PIGMA_2:
            radioPortraitTex = D_STAR_WOLF_F005AC0;
            break;
        case RCID_PIGMA_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F0069E0;
            break;
        case RCID_LEON_2:
            radioPortraitTex = D_STAR_WOLF_F009740;
            break;
        case RCID_LEON_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F00A660;
            break;
        case RCID_ANDREW_2:
            radioPortraitTex = D_STAR_WOLF_F001E40;
            break;
        case RCID_ANDREW_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F002D60;
            break;
        case RCID_BOSS_CORNERIA:
            radioPortraitTex = D_CO_6026420;
            break;
        case RCID_BOSS_CORNERIA + 1:
            radioPortraitTex = D_CO_6027340;
            break;
        case RCID_BOSS_CORNERIA2:
            radioPortraitTex = D_CO_60245E0;
            break;
        case RCID_BOSS_CORNERIA2 + 1:
            radioPortraitTex = D_CO_6025500;
            break;
        case RCID_BOSS_METEO:
            radioPortraitTex = D_ME_601C8E0;
            break;
        case RCID_BOSS_METEO + 1:
            radioPortraitTex = D_ME_601D800;
            break;
        case RCID_BOSS_AREA6:
            radioPortraitTex = D_A6_60047E0;
            break;
        case RCID_BOSS_AREA6 + 1:
            radioPortraitTex = D_A6_6005700;
            break;
        case RCID_CAIMAN_AREA6:
            radioPortraitTex = D_A6_60029A0;
            break;
        case RCID_CAIMAN_AREA6 + 1:
            radioPortraitTex = D_A6_60038C0;
            break;
        case RCID_BOSS_ZONESS:
            radioPortraitTex = D_ZO_6014510;
            break;
        case RCID_BOSS_ZONESS + 1:
            radioPortraitTex = D_ZO_6015430;
            break;
        case RCID_BOSS_SECTORX:
            radioPortraitTex = D_SX_6020FB0;
            break;
        case RCID_BOSS_SECTORX + 1:
            radioPortraitTex = D_SX_6021ED0;
            break;
        case RCID_BOSS_SECTORY:
            radioPortraitTex = D_SY_6018F30;
            break;
        case RCID_BOSS_SECTORY + 1:
            radioPortraitTex = D_SY_6019E50;
            break;
        case RCID_BOSS_MACBETH:
            radioPortraitTex = D_MA_6010C20;
            break;
        case RCID_BOSS_MACBETH + 1:
            radioPortraitTex = D_MA_6011B40;
            break;
        case RCID_ROB64_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_ROB64:
        case RCID_ROB64_2:
            radioPortraitTex = D_1009C80;
            break;
        case RCID_ROB64_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_ROB64 + 1:
        case RCID_ROB64_2 + 1:
            radioPortraitTex = D_100ABA0;
            break;
        case RCID_KATT:
            radioPortraitTex = D_D003DF0;
            break;
        case RCID_KATT + 1:
            radioPortraitTex = D_D004D10;
            break;
        case RCID_ANDROSS_RED:
        case RCID_ANDROSS:
            radioPortraitTex = D_D000170;
            if ((gGameState == GSTATE_PLAY) && (gCurrentLevel == LEVEL_AREA_6)) {
                radioPortraitTex = D_A6_6000B60;
            }
            sRadioUseRedBox = true;
            break;
        case RCID_ANDROSS_RED + 1:
        case RCID_ANDROSS + 1:
            radioPortraitTex = D_D001090;
            if ((gGameState == GSTATE_PLAY) && (gCurrentLevel == LEVEL_AREA_6)) {
                radioPortraitTex = D_A6_6001A80;
            }
            sRadioUseRedBox = true;
            break;
        case RCID_JAMES:
            radioPortraitTex = D_D005C30;
            break;
        case RCID_JAMES + 1:
            radioPortraitTex = D_D006B50;
            break;
        case RCID_BILL:
            radioPortraitTex = D_D001FB0;
            break;
        case RCID_BILL + 1:
            radioPortraitTex = D_D002ED0;
            break;
        case RCID_GEN_PEPPER:
            radioPortraitTex = D_D007A70;
            break;
        case RCID_GEN_PEPPER + 1:
            radioPortraitTex = D_D008990;
            break;
        case RCID_ROB64_TITLE:
            radioPortraitTex = D_GREAT_FOX_E00E100;
            break;
        case RCID_ROB64_TITLE + 1:
            radioPortraitTex = D_GREAT_FOX_E00F020;
            break;
        case RCID_GEN_PEPPER_TITLE:
            radioPortraitTex = D_GREAT_FOX_E00FF40;
            break;
        case RCID_GEN_PEPPER_TITLE + 1:
            radioPortraitTex = D_GREAT_FOX_E010E60;
            break;
        case RCID_TR:
            radioPortraitTex = D_TR_6000900;
            break;
        case RCID_TR + 1:
            radioPortraitTex = D_TR_6001820;
            break;
        case RCID_STATIC + 1:
            mirror = true;
            /* fallthrough */
        case RCID_STATIC:
            switch (gGameState) {
                default:
                    radioPortraitTex = NULL;
                    break;
                case GSTATE_PLAY:
                    radioPortraitTex = D_1008D60;
                    break;
                case GSTATE_TITLE:
                case GSTATE_ENDING:
                    radioPortraitTex = gTitleRadioStatic;
                    break;
            }
            if (((s32) gRadioMsgRadioId == RCID_ANDROSS) || ((s32) gRadioMsgRadioId == RCID_ANDROSS_RED)) {
                sRadioUseRedBox = true;
            }
            break;
    }
    if ((radioPortraitTex != NULL) && (gRadioPortraitScaleY != 0.0f)) {
        temp_fa0 = (2.0f * gRadioPortraitScaleY) + gRadioPortraitPosY;
        if ((gRadioPortraitPosY + 20.0f) <= temp_fa0) {
            D_800D4A74 = 1.0f;
        }
        if (temp_fa0 <= gRadioPortraitPosY) {
            D_800D4A74 = -1.0f;
        }
        sp38 = gRadioPortraitScaleY * 20.0f * D_800D4A74;
        gSPDisplayList(gMasterDisp++, gRcpSetupDLs[SETUPDL_76_OPTIONAL]);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);

        if (mirror) {
            Lib_TextureRect_RGBA16_MirX(&gMasterDisp, radioPortraitTex, 44, 44, gRadioPortraitPosX,
                                        gRadioPortraitPosY + 20.0f + sp38 + gRadioPortraitScaleY, 1.0f,
                                        gRadioPortraitScaleY);
        } else {
            Lib_TextureRect_RGBA16(&gMasterDisp, radioPortraitTex, 44, 44, gRadioPortraitPosX,
                                   gRadioPortraitPosY + 20.0f + sp38 + gRadioPortraitScaleY, 1.0f,
                                   gRadioPortraitScaleY);
        }
    }
}

void func_radio_800BB388(void) {
    static f32 D_800D4A78 = -1.0f;
    f32 temp_fa0;
    u8* texture;
    u16* palette;
    f32 sp30;

    Radio_CalculatePositions();

    if ((gGameState != GSTATE_MAP) && (gRadioTextBoxScaleY != 0.0f)) {
        temp_fa0 = (gRadioTextBoxScaleY / 0.26f) * 3.0f;
        if ((gRadioTextBoxPosY + 16.0f) <= (temp_fa0 + gRadioTextBoxPosY)) {
            D_800D4A78 = 1.0f;
        }
        if (temp_fa0 + gRadioTextBoxPosY <= gRadioTextBoxPosY) {
            D_800D4A78 = -1.0f;
        }

        sp30 = temp_fa0 * D_800D4A78;

        RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);

        switch (gGameState) {
            case GSTATE_TITLE:
            case GSTATE_ENDING:
                texture = aNoControllerBgTex;
                palette = aNoControllerBgTLUT;
                break;

            case GSTATE_PLAY:
                texture = aMsgWindowBgTex;
                palette = aMsgWindowBgTLUT;
                break;
        }

        if (sRadioUseRedBox == true) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 25, 25, 170);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 60, 60, 255, 170);
        }

        Lib_TextureRect_CI8(&gMasterDisp, texture, palette, 32, 32, gRadioTextBoxPosX, gRadioTextBoxPosY + 16.0f + sp30,
                            gRadioTextBoxScaleX, gRadioTextBoxScaleY);
    }

    if (gRadioTextBoxScaleY == 1.3f) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);
        gMsgCharIsPrinting =
            Message_DisplayText(&gMasterDisp, gRadioMsg, gRadioPrintPosX, gRadioPrintPosY, gRadioMsgCharIndex);
    }
}

s32 D_radio_80178748; // set to 1, never used
s32 sRadioCheckMouthFlag;

void Radio_Draw(void) {
    s32 idx;
    RadioCharacterId radioCharId;
    u32 ret;
    s32 fakeTemp;

    if ((gPlayState == PLAY_PAUSE) && (gGameState != GSTATE_ENDING)) {
        return;
    }

    if (gRadioStateTimer > 0) {
        gRadioStateTimer--;
    }

    if (gRadioMouthTimer > 0) {
        gRadioMouthTimer--;
    }

    switch (gRadioState) {
        case 100:
            D_radio_80178748 = 1;
            gCurrentRadioPortrait = RCID_1000;
            gRadioState = 1;
            gRadioMsgCharIndex = 0;
            gRadioPortraitScaleY = 0.0f;
            gRadioTextBoxScaleY = 0.0f;
            sRadioCheckMouthFlag = 0;
            if (gCamCount != 1) {
                gRadioState = 0;
            }
            break;

        case 1:
            gRadioPortraitScaleY += 0.25f;
            if (gRadioPortraitScaleY == 1.0f) {
                gRadioState++;
                gRadioStateTimer = 10;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            break;

        case 2:
            if (gRadioStateTimer == 0) {
                gRadioState++;
                gRadioStateTimer = 10;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            break;

        case 3:
            if (gRadioStateTimer == 0) {
                gRadioState++;
                ret = Message_GetWidth(gRadioMsg);
                if (gVIsPerFrame == 3) {
                    gRadioStateTimer = ret + 16;
                } else {
                    gRadioStateTimer = (2 * ret) + 16;
                }
                if ((gGameState == GSTATE_TITLE) || (gGameState == GSTATE_ENDING)) {
                    gRadioStateTimer = ret * 2;
                }
            }
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            gRadioTextBoxScaleY += 0.26f;
            if (gRadioTextBoxScaleY > 1.3f) {
                gRadioTextBoxScaleY = 1.3f;
            }
            break;

        case 31:
            gRadioState++;
            gRadioStateTimer = 80 - gRadioStateTimer;
            break;

        case 32:
            if (Audio_GetCurrentVoice() == 0) {
                gRadioMsgListIndex++;
                gRadioMsg = SEGMENTED_TO_VIRTUAL(gRadioMsgList[gRadioMsgListIndex]);
                Audio_PlayVoice(Message_IdFromPtr(gRadioMsg));
                gRadioMsgCharIndex = 0;
                sRadioCheckMouthFlag = 0;
                gRadioStateTimer = 80;
                gRadioStateTimer = Message_GetWidth(gRadioMsg) * 2;
                gRadioState = 4;
            }
            break;

        case 4:
            if ((Audio_GetCurrentVoice() == 0) && (gRadioStateTimer == 0)) {
                gRadioStateTimer = 10;
                gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
                gRadioState = 6;
            }
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            if (gRadioMouthTimer > 0) {
                gCurrentRadioPortrait = (s32) gRadioMsgRadioId + 1;
            }

            if (!gVIsPerFrame) {}

            if (1) {
                fakeTemp = 0;
            }

            if (!(fakeTemp)) {
                ret = Audio_GetCurrentVoiceStatus();

                if (gRadioMsgCharIndex < 60 && gRadioMsg[gRadioMsgCharIndex + 1] != MSGCHAR_END) {
                    if (gRadioMsg[gRadioMsgCharIndex + 1] == MSGCHAR_NXT) {
                        if (ret == 0) {
                            gRadioState = 31;
                        }
                    } else {
                        gRadioMsgCharIndex++;
                    }
                } else if (gRadioMsgCharIndex < 60) {
                    gRadioMsgCharIndex = 60;
                }

                if (sRadioCheckMouthFlag) {
                    if ((gRadioMsgId >= 23000) && (gRadioMsgId < 23033)) {
                        if (gMsgCharIsPrinting) {
                            gRadioMouthTimer = 2;
                            AUDIO_PLAY_SFX(NA_SE_MESSAGE_MOVE, gDefaultSfxSource, 4);
                        }
                    } else if (ret == 1) {
                        gRadioMouthTimer = 2;
                    } else {
                        gRadioMouthTimer = 0;
                    }
                }
            }
            sRadioCheckMouthFlag ^= 1;
            break;

        case 5:
            if (gRadioStateTimer == 0) {
                gRadioState++;
                gRadioStateTimer = 10;
            }
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            break;

        case 6:
            if (gRadioStateTimer == 0) {
                if (gGameState == GSTATE_ENDING) {
                    Audio_ClearVoice();
                } else {
                    Audio_PlayVoice(0);
                }
                gRadioState++;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            gRadioTextBoxScaleY -= 0.26f;
            if (gRadioTextBoxScaleY < 0.0f) {
                gRadioTextBoxScaleY = 0.0f;
            }
            break;

        case 7:
            gRadioPortraitScaleY -= 0.25f;
            if (gRadioPortraitScaleY == 0) {
                gHideRadio = false;
                gRadioMsgPri = 0;
                gRadioState = 0;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            break;

        case 8:
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            gRadioTextBoxScaleY = 1.3f;
            gRadioPortraitScaleY = 1.0f;
            break;

        case 0:
            break;
    }

    if (((gRadioState > 0) && (gRadioState != 100)) && !gHideRadio) {
        func_radio_800BAAE8();
        func_radio_800BB388();

        radioCharId = (s32) gRadioMsgRadioId;

        if (((radioCharId == RCID_FALCO) || (radioCharId == RCID_SLIPPY)) || (radioCharId == RCID_PEPPY)) {
            if (radioCharId == RCID_FALCO) {
                idx = TEAM_ID_FALCO;
            }
            if (radioCharId == RCID_SLIPPY) {
                idx = TEAM_ID_SLIPPY;
            }
            if (radioCharId == RCID_PEPPY) {
                idx = TEAM_ID_PEPPY;
            }
            if ((gTeamShields[idx] <= 0) && (gGameFrameCount & 4) && (gTeamShields[idx] != -2) &&
                (gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1) &&
                (gCurrentRadioPortrait != RCID_1000)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                if (CVarGetInteger("gRadioCommBox.expand", 0) == 1) {
                    Graphics_DisplaySmallText(OTRGetRectDimensionFromLeftEdgeOverride(31.0f), 167, 1.0f, 1.0f, "DOWN");
                } else {
                    Graphics_DisplaySmallText(31, 167, 1.0f, 1.0f, "DOWN");
                }
                HUD_TeamDownWrench_Draw(1);
            }
            if (((gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1)) &&
                (gCurrentRadioPortrait != RCID_1000)) {
                if (CVarGetInteger("gRadioCommBox.expand", 0) == 1) {
                    HUD_TeamShields_Draw(OTRGetRectDimensionFromLeftEdgeOverride(22.0f), 165.0f, gTeamShields[idx]);
                } else {
                    HUD_TeamShields_Draw(22.0f, 165.0f, gTeamShields[idx]);
                }
            }
        }

        radioCharId = (s32) gRadioMsgRadioId;

        if (((radioCharId == RCID_WOLF) || (radioCharId == RCID_PIGMA) || (radioCharId == RCID_LEON) ||
            (radioCharId == RCID_ANDREW) || (radioCharId == RCID_WOLF_2) || (radioCharId == RCID_PIGMA_2) ||
             (radioCharId == RCID_LEON_2) || (radioCharId == RCID_ANDREW_2)) &&
                (gCurrentLevel == LEVEL_FORTUNA ||
            gCurrentLevel == LEVEL_BOLSE || gCurrentLevel == LEVEL_VENOM_2)) {
            switch (radioCharId) {
                case RCID_WOLF:

                case RCID_WOLF_2:
                    idx = 4;
                    break;

                case RCID_LEON:

                case RCID_LEON_2:
                    idx = 5;
                    break;

                case RCID_PIGMA:

                case RCID_PIGMA_2:
                    idx = 6;
                    break;

                case RCID_ANDREW:

                case RCID_ANDREW_2:
                    idx = 7;
                    break;

                default:
                    idx = 0;
                    break;
            }

            if ((gActors[idx].obj.status != OBJ_ACTIVE) && (gGameFrameCount & 4) &&
                (gPlayer[0].state == PLAYERSTATE_ACTIVE) && (gCurrentRadioPortrait != RCID_STATIC) &&
                (gCurrentRadioPortrait != RCID_STATIC + 1) && (gCurrentRadioPortrait != RCID_1000)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                if (CVarGetInteger("gRadioCommBox.expand", 0) == 1) {
                    Graphics_DisplaySmallText(OTRGetRectDimensionFromLeftEdgeOverride(31.0f), 167, 1.0f, 1.0f, "DOWN");
                } else {
                    Graphics_DisplaySmallText(31.0f, 167, 1.0f, 1.0f, "DOWN");
                }
            }
            if (((gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1)) &&
                (gCurrentRadioPortrait != RCID_1000)) {
                if (CVarGetInteger("gRadioCommBox.expand", 0) == 1) {
                    HUD_TeamShields_Draw(OTRGetRectDimensionFromLeftEdgeOverride(22.0f), 165.0f,
                                         gActors[idx].health * 2.55f);
                } else {
                    HUD_TeamShields_Draw(22.0f, 165.0f, gActors[idx].health * 2.55f);
                }
            }
        }
        if (((gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1)) &&
            (gCurrentRadioPortrait != RCID_1000)) {
            HUD_RadioCharacterName_Draw();
        }
    }

    if (gHideRadio == true) {
        func_radio_800BA760();
    }
}

// Unused in VERSION_US and absent in VERSION_EU, probably a leftover from VERSION_JP ?
void func_radio_800BC040(void) {
    if (gPlayState != PLAY_PAUSE) {
        if (gRadioStateTimer > 0) {
            gRadioStateTimer--;
        }
        if (gRadioMouthTimer > 0) {
            gRadioMouthTimer--;
        }

        switch (gRadioState) {
            case 100:
                gCurrentRadioPortrait = RCID_1000;
                gRadioState = 1;
                gRadioPortraitScaleY = 0.0f;
                gRadioTextBoxScaleY = 0.0f;
                gRadioMsgCharIndex = Message_GetWidth(gRadioMsg);
                if (gCamCount != 1) {
                    gRadioState = 0;
                }
                break;

            case 1:
                gRadioPortraitScaleY += 0.02f;
                if (gRadioPortraitScaleY == 0.04f) {
                    gRadioState++;
                    gRadioStateTimer = 5;
                }
                break;

            case 2:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 5;
                }

                gCurrentRadioPortrait = RCID_STATIC;

                if ((gGameFrameCount % 2) != 0) {
                    gCurrentRadioPortrait = RCID_STATIC + 1;
                }
                break;

            case 3:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 5;

                    if (gGameState == GSTATE_TITLE) {
                        gRadioStateTimer = 30;
                    }
                }

                gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
                gRadioTextBoxScaleY += 0.015f;

                if (gRadioTextBoxScaleY > 0.07f) {
                    gRadioTextBoxScaleY = 0.07f;
                }
                break;

            case 4:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 10;
                }
                break;

            case 5:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 5;
                }
                gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
                break;

            case 6:
                if (gRadioStateTimer == 0) {
                    Audio_PlayVoice(0);
                    gRadioState++;
                }

                gCurrentRadioPortrait = RCID_STATIC;

                if ((gGameFrameCount % 2) != 0) {
                    gCurrentRadioPortrait = RCID_STATIC + 1;
                }

                gRadioTextBoxScaleY -= 0.015f;

                if (gRadioTextBoxScaleY < 0.0f) {
                    gRadioTextBoxScaleY = 0.0f;
                }
                break;

            case 7:
                gRadioPortraitScaleY -= 0.02f;
                if (gRadioPortraitScaleY == 0) {
                    gRadioState = 0;
                    gRadioStateTimer = 5;
                }
                gCurrentRadioPortrait = RCID_STATIC;
                if ((gGameFrameCount % 2) != 0) {
                    gCurrentRadioPortrait = RCID_STATIC + 1;
                }
                break;

            case 0:
                break;
        }

        if ((gRadioState > 0) && (gRadioState != 100)) {
            func_radio_800BAAE8();
            func_radio_800BB388();
            if (((s32) gRadioMsgRadioId == RCID_FALCO) || ((s32) gRadioMsgRadioId == RCID_SLIPPY) ||
                ((s32) gRadioMsgRadioId == RCID_PEPPY)) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL_36();
                Matrix_Translate(gGfxMatrix, -150.0f, -115.0f, -443.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.068f, 0.068f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gPlayerNum = 0;
                Matrix_Pop(&gGfxMatrix);
            }
        }
    }
}
