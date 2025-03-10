/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"

#define CONFIG_UAC_SPEAKER_CHANNEL_NUM  2
#define CONFIG_UAC_MIC_CHANNEL_NUM      2
#define CONFIG_UAC_SAMPLE_RATE          48000
#define CONFIG_UAC_SPK_INTERVAL_MS      (10)
#define CONFIG_UAC_MIC_INTERVAL_MS      (10)
#define CONFIG_UAC_SPK_NEW_PLAY_INTERVAL (100)
#define CONFIG_TUSB_VID                 (0x303A)
#define CONFIG_TUSB_PID                 (0x82BE)
#define CONFIG_TUSB_SERIAL_NUM          "00000000"
#define CONFIG_TUSB_MANUFACTURER        "SONULAB"
#define CONFIG_TUSB_PRODUCT             "Stompstation"
//#define CONFIG_TUP_RHPORT_HIGHSPEED    0

#define SPEAK_CHANNEL_NUM    CONFIG_UAC_SPEAKER_CHANNEL_NUM  /*!< SPEAKER */
#define MIC_CHANNEL_NUM      CONFIG_UAC_MIC_CHANNEL_NUM      /*!< MIC */
#define DEFAULT_SAMPLE_RATE  CONFIG_UAC_SAMPLE_RATE          /*!< SAMPLE RATE */
#define SPK_INTERVAL_MS      CONFIG_UAC_SPK_INTERVAL_MS      /*!< READ INTERVAL in ms*/
#define MIC_INTERVAL_MS      CONFIG_UAC_MIC_INTERVAL_MS      /*!< WRITE INTERVAL in ms*/

#define IN_CTRL_CH_VALUE U32_TO_U8S_LE(AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS)

#if SPEAK_CHANNEL_NUM == 1
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif SPEAK_CHANNEL_NUM == 2
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif SPEAK_CHANNEL_NUM == 3
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif SPEAK_CHANNEL_NUM == 4
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif SPEAK_CHANNEL_NUM == 5
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif SPEAK_CHANNEL_NUM == 6
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif SPEAK_CHANNEL_NUM == 7
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif SPEAK_CHANNEL_NUM == 8
#define INPUT_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#endif

#if MIC_CHANNEL_NUM == 1
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif MIC_CHANNEL_NUM == 2
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif MIC_CHANNEL_NUM == 3
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif MIC_CHANNEL_NUM == 4
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif MIC_CHANNEL_NUM == 5
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif MIC_CHANNEL_NUM == 6
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif MIC_CHANNEL_NUM == 7
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#elif MIC_CHANNEL_NUM == 8
#define MIC_CTRL      IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE, IN_CTRL_CH_VALUE
#endif

/* Feature Unit Descriptor(4.7.2.8) */
// N - Channels
#define TUD_AUDIO_DESC_SPK_FEATURE_UNIT_N_CHANNEL_LEN   (6+(SPEAK_CHANNEL_NUM+1)*4)
#define TUD_AUDIO_DESC_MIC_FEATURE_UNIT_N_CHANNEL_LEN   (6+(MIC_CHANNEL_NUM+1)*4)
#define TUD_AUDIO_DESC_FEATURE_UNIT_N_CHANNEL(_length ,_unitid, _srcid, _stridx, ...) \
  _length, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_FEATURE_UNIT, _unitid, _srcid, __VA_ARGS__, _stridx

#ifdef __cplusplus
}
#endif
