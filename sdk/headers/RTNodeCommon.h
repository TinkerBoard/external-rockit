/*
 * Copyright 2020 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *     author: <martin.cheng@rock-chips.com>
 *       date: 2020-05-20
 *     module: RTNodeCommon
 */

#ifndef SRC_RT_TASK_APP_GRAPH_RTNODECOMMON_H
#define SRC_RT_TASK_APP_GRAPH_RTNODECOMMON_H

#include <iterator>
#include <list>
#include <vector>

#include "rt_string_utils.h"

/*
 * "node_0": {
 *    "node_name":          "source_stream",
 *    "node_opts":        { "node_type": "rkisp" },
 *    "node_stream":      { "name":      "v4l2_capture" },
 *    "node_stream_opts": { "device":    "/dev/video0" }
 * }
 */

#define NODE_NAME_RKISP         "rkisp"
#define NODE_NAME_FREAD         "fread"
#define NODE_NAME_RKMPP_ENC     "rkmpp_enc"
#define NODE_NAME_RKMPP_DEC     "rkmpp_dec"
#define NODE_NAME_ROCKX         "rockx"
#define NODE_NAME_FWRITE        "fwrite"
#define NODE_NAME_RKRGA         "rkrga"
#define NODE_NAME_EPTZ          "rkeptz"
#define NODE_NAME_STASTERIA     "st_asteria"  // sensetime asteria
#define NODE_NAME_AIMATTING     "ai_matting"

#define NODE_NAME_RESAMPLE      "resample"
#define NODE_NAME_ALSA_CAPTURE  "alsa_capture"
#define NODE_NAME_ALSA_PLAYBACK "alsa_playback"
#define NODE_NAME_MULTI_CAPTURE "multi_cap"
#define NODE_NAME_ALGORITHM_3A  "alg_3a"
#define NODE_NAME_ALGORITHM_3A_ANR  "alg_anr"
#define NODE_NAME_ALGORITHM_SKV     "skv"
#define NODE_NAME_ALGORITHM_SKV_AEC "skv_aec"
#define NODE_NAME_ALGORITHM_SKV_AGC "skv_agc"
#define NODE_NAME_ALGORITHM_SKV_BF  "skv_bf"
#define NODE_NAME_ALGORITHM_SKV_DOA "skv_doa"
#define NODE_NAME_AUDIO_TRACK_MODE  "track_mode"

#define NODE_NAME_RKNN          "rknn"
#define NODE_NAME_FFM_DEMUXER   "ffm_demuxer"
#define NODE_NAME_VIDEO_SINK    "video_sink"
#define NODE_NAME_FILTER_IMAGE  "filter_image"
#define NODE_NAME_FILTER_SCALER "filter_scaler"
#define NODE_NAME_VOLUME        "filter_volume"
#define NODE_NAME_LINK_OUTPUT   "link_output"
#define NODE_NAME_SOURCE_EXTERNAL  "external_source"
#define NODE_NAME_AUDIO_DEC_FFMPEG  "audio_dec_ffmpeg"

#define NODE_PORT_SOURCE  "source"
#define NODE_PORT_DEVICE  "device"
#define NODE_PORT_SINK    "sink"

// task node names supported by rockchip co.
#define RT_NODE_DEVICE_RKISP             "node_rkisp"
#define RT_NODE_DEVICE_ALSA_CAPTURE      "node_alsa_capture"
#define RT_NODE_DEVICE_ALSA_PLAYBACK     "node_alsa_playback"
#define RT_NODE_CODEC_RKMPP              "node_rkmpp"
#define RT_NODE_CODEC_FFVIDEO            "node_ffvideo"    // ffmpeg codec video
#define RT_NODE_CODEC_FFAUDIO            "node_ffaudio"    // ffmpeg codec audio
#define RT_NODE_FILTER_RKRGA             "node_rkrga"
#define RT_NODE_FILTER_RKNN              "node_rknn"
#define RT_NODE_FILTER_RKFACE            "node_rkface"
#define RT_NODE_FILTER_RESAMPLE          "node_resample"



// common root types for task node.
#define KEY_ROOT_PIPE_ID                 "pipe_"
#define KEY_ROOT_NODE_ID                 "node_"
#define KEY_ROOT_EXEC_ID                 "executor_"
#define KEY_ROOT_LINK_MODE_ID            "link_"
#define KEY_ROOT_INPUT_STREAM_ID         "stream_input_"
#define KEY_ROOT_OUTPUT_STREAM_ID        "stream_output_"
#define KEY_ROOT_NODE_OPTS               "node_opts"
#define KEY_ROOT_NODE_OPTS_EXTRA         "node_opts_extra"
#define KEY_ROOT_STREAM_OPTS             "stream_opts"
#define KEY_ROOT_STREAM_OPTS_EXTRA       "stream_opts_extra"
#define KEY_ROOT_EXEC_OPTS               "executor_opts"
#define KEY_ROOT_DEFAULT_LINK_MODE       "default_mode_link"

// common parameters for task node. subnodes of KEY_ROOT_NODE_OPTS
#define OPT_NODE_NAME                    "node_name"

#define OPT_LINK_NAME                    "link_name"
#define OPT_LINK_SHIP                    "link_ship"

// extra parameters for task node. subnodes of KEY_ROOT_NODE_OPTS_EXTRA
#define OPT_NODE_SOURCE_URI              "node_source_uri"
#define OPT_NODE_BUFFER_COUNT            "node_buff_count"
#define OPT_NODE_BUFFER_TYPE             "node_buff_type"
#define OPT_NODE_BUFFER_SIZE             "node_buff_size"
#define OPT_NODE_BUFFER_ALLOC_TYPE       "node_buff_alloc_type"
#define OPT_NODE_TRANS_RECT              "node_trans_rect"
#define OPT_NODE_DISPATCH_EXEC           "node_disp_exec"
#define OPT_NODE_MAX_INPUT_COUNT         "node_max_input_count"
#define OPT_NODE_BUFFER_STAT             "node_buffer_stat"
#define OPT_NODE_GATE_MODE               "node_gate_mode"

#define OPT_FILE_READ_SIZE               "opt_read_size"

// common parameters for node stream. subnodes of KEY_ROOT_NODE_STREAM
#define OPT_STREAM_UID                   "stream_uid"
#define OPT_STREAM_INPUT_NAME            "stream_input"
#define OPT_STREAM_OUTPUT_NAME           "stream_output"
#define OPT_STREAM_FMT_IN                "stream_fmt_in"
#define OPT_STREAM_FMT_OUT               "stream_fmt_out"
#define OPT_STREAM_FMT_IN_PREFIX         "stream_fmt_in_"
#define OPT_STREAM_FMT_OUT_PREFIX        "stream_fmt_out_"
#define OPT_STREAM_INPUT_MODE            "stream_mode_in"

#define OPT_CODEC_TYPE                   "opt_codec_type"
#define OPT_CODEC_ID                     "opt_codec_id"

// common parameters for codec video. subnodes of KEY_ROOT_NODE_STREAM_OPTS
#define OPT_VIDEO_SVC                    "opt_svc"
#define OPT_VIDEO_SMART                  "opt_smart"
#define OPT_VIDEO_GOP                    "opt_gop"
#define OPT_VIDEO_BITRATE                "opt_bitrate"
#define OPT_VIDEO_STREAMSMOOTH           "opt_smooth"
#define OPT_VIDEO_LEVEL                  "opt_level"
#define OPT_VIDEO_PROFILE                "opt_profile"
#define OPT_VIDEO_FRAME_RATE             "opt_frame_rate"
#define OPT_VIDEO_DIMENS                 "opt_dimens"            // veried, fixed
#define OPT_VIDEO_WIDTH                  "opt_width"
#define OPT_VIDEO_HEIGHT                 "opt_height"
#define OPT_VIDEO_VIR_WIDTH              "opt_vir_width"
#define OPT_VIDEO_VIR_HEIGHT             "opt_vir_height"
#define OPT_VIDEO_PIX_FORMAT             "opt_pix_format"
#define OPT_VIDEO_QUALITY_INIT           "opt_qp_init"
#define OPT_VIDEO_QUALITY_STEP           "opt_qp_step"
#define OPT_VIDEO_QUALITY_MIN            "opt_qp_min"
#define OPT_VIDEO_QUALITY_MAX            "opt_qp_max"
#define OPT_VIDEO_QUALITY_MIN_H265       "opt_qp_min_h265"
#define OPT_VIDEO_QUALITY_MAX_H265       "opt_qp_max_h265"
#define OPT_VIDEO_RC_MODE                "opt_rc_mode"
#define OPT_VIDEO_RC_QUALITY             "opt_rc_mode"
#define OPT_VIDEO_REGIONS_ROI            "opt_regions_roi"
#define OPT_VIDEO_REGIONS_RI             "opt_regions_ri"
#define OPT_VIDEO_TRANS_RECT             "opt_trans_rect"
#define OPT_VIDEO_COLOR_RANGE            "opt_color_range"
#define OPT_VIDEO_TIME_REF               "opt_time_ref"

#define OPT_VIDEO_DEC_SPLIT_MODE         "opt_dec_split_mode"

// common parameters for codec audio. subnodes of KEY_ROOT_NODE_STREAM_OPTS
#define OPT_AUDIO_CHANNEL                "opt_channel"
#define OPT_AUDIO_CHANNEL_LAYOUT         "opt_channel_layout"
#define OPT_AUDIO_SAMPLE_RATE            "opt_samaple_rate"
#define OPT_AUDIO_BITRATE                "opt_bitrate"
#define OPT_AUDIO_SOURCE_URI             "opt_source_uri"
#define OPT_AUDIO_ANS                    "opt_ans"
#define OPT_AUDIO_FORMAT                 "opt_format"
#define OPT_AUDIO_REF_CHANNEL_LAYOUT     "opt_ref_channel_layout"    /*aec process of 3a filter*/
#define OPT_AUDIO_REC_CHANNEL_LAYOUT     "opt_rec_channel_layout"
#define OPT_AUDIO_REF_VOLUME             "opt_ref_volume"
#define OPT_AUDIO_REC_VOLUME             "opt_rec_volume"
#define OPT_AUDIO_ALSA_MODE              "opt_alsa_mode"
#define OPT_AUDIO_AGC_LEVEL              "opt_agc_level"
#define OPT_AUDIO_AGC_IS_SPEECH          "opt_agc_is_speech"
#define OPT_AUDIO_BF_MODE                "opt_bf_mode"
#define OPT_AUDIO_DOA_DISTANCE           "opt_doa_distance"
#define OPT_AUDIO_DOA_TARG               "opt_doa_targ"
#define OPT_AUDIO_ANR_DEGREE             "opt_anr_degree"
#define OPT_AUDIO_AEC_ENABLE             "opt_aec_enable"
#define OPT_AUDIO_AEC_DELAY              "opt_aec_delay"
#define OPT_AUDIO_AEC_NLP_URI            "opt_aec_nlp_uri"
#define OPT_AUDIO_AEC_NLP_PLUS_URI       "opt_aec_nlp_plus_uri"

#define OPT_PEROID_SIZE                  "opt_peroid_size"
#define OPT_PEROID_COUNT                 "opt_peroid_count"
#define OPT_AUDIO_MUTE                   "opt_mute"
#define OPT_AUDIO_VOLUME                 "opt_volume"
#define OPT_AUDIO_START_DELAY            "opt_start_delay"
#define OPT_AUDIO_STOP_DELAY             "opt_stop_delay"
#define OPT_ADEC_MODE                    "opt_adec_mode"

#define OPT_AV_PTS                       "opt_av_pts"
#define OPT_AV_DTS                       "opt_av_dts"
#define OPT_AV_SEQ                       "opt_av_seq"
#define OPT_AV_EOS                       "opt_av_eos"
#define OPT_AV_ERR                       "opt_av_err"
#define OPT_AV_DURATION                  "opt_av_duration"

// common parameters for filter: RKNN with move detection.
// subnodes of KEY_ROOT_NODE_STREAM_OPTS
#define OPT_FILTER_WIDTH                 "opt_width"
#define OPT_FILTER_HEIGHT                "opt_height"
#define OPT_FILTER_VIR_WIDTH             "opt_vir_width"
#define OPT_FILTER_VIR_HEIGHT            "opt_vir_height"
#define OPT_FILTER_TRANS_RECT            "opt_trans_rect"
#define OPT_FILTER_TRANS_ROTATE          "opt_trans_rotate"
#define OPT_FILTER_MD_DS_WIDTH           "opt_md_ds_width"
#define OPT_FILTER_MD_DS_HEIGHT          "opt_md_ds_height"
#define OPT_FILTER_MD_ORI_WIDTH          "opt_md_ori_width"
#define OPT_FILTER_MD_ORI_HEIGHT         "opt_md_ori_height"
#define OPT_FILTER_MD_ROI_CNT            "opt_md_roi_cnt"
#define OPT_FILTER_MD_ROI_RECT           "opt_md_roi_rect"
#define OPT_FILTER_MD_SINGLE_REF         "opt_md_single"
#define OPT_FILTER_RECT_X                "opt_rect_x"
#define OPT_FILTER_RECT_Y                "opt_rect_y"
#define OPT_FILTER_RECT_W                "opt_rect_w"
#define OPT_FILTER_RECT_H                "opt_rect_h"
#define OPT_FILTER_DST_RECT_X            "opt_dst_rect_x"
#define OPT_FILTER_DST_RECT_Y            "opt_dst_rect_y"
#define OPT_FILTER_DST_RECT_W            "opt_dst_rect_w"
#define OPT_FILTER_DST_RECT_H            "opt_dst_rect_h"
#define OPT_FILTER_DST_VIR_WIDTH         "opt_dst_vir_width"
#define OPT_FILTER_DST_VIR_HEIGHT        "opt_dst_vir_height"

#define OPT_V4L2_BUF_TYPE               "opt_buf_type"
#define OPT_V4L2_MEM_TYPE               "opt_mem_type"
#define OPT_V4L2_USE_LIBV4L2            "opt_use_libv4l2"
#define OPT_V4L2_COLORSPACE             "opt_colorspace"
#define OPT_V4L2_WIDTH                  "opt_width"
#define OPT_V4L2_HEIGHT                 "opt_height"
#define OPT_V4L2_ENTITY_NAME            "opt_entity_name"
#define OPT_V4L2_QUANTIZATION           "opt_quantiztion"
#define OPT_V4L2_CAMERA_INDEX           "opt_camera_index"

#define OPT_ROCKX_MODEL                 "opt_rockx_model"

#define OPT_ROCKX_LIB_PATH              "opt_rockx_lib_path"
#define OPT_ROCKX_SKIP_FRAME            "opt_rockx_skip_frame"

#define OPT_AI_DETECT_RESULT            "opt_ai_detect_result"
#define OPT_AI_ALGORITHM                "opt_ai_algorithm"

#define OPT_AIMATTING_OUT_RESULT        "aimatting_out_result"

#define OPT_EPTZ_CLIP_RATIO             "opt_clip_ratio"
#define OPT_EPTZ_CLIP_WIDTH             "opt_clip_width"
#define OPT_EPTZ_CLIP_HEIGHT            "opt_clip_height"

#define OPT_AUDIO_ALGORITHM             "opt_audio_algorithm"

#define OPT_EXEC_THREAD_NUM             "exec_thread_num"

#define OPT_IO_STREAM_MODE              "opt_io_stream_mode"
/*
 * AI Server  -- {DBUS | RNDIS} -- Remote HOST(TV AI)
 *
 * We communicate with the remote HOST through RNDIS.
 * DBus is an interactive interface, CMDs are as follows
 */
#define OPT_DBUS_LEVEL_HIGHEST          "dbus_highest"
#define OPT_DBUS_LEVEL_HIGHER           "dbus_higher"
#define OPT_DBUS_LEVEL_HIGH             "dbus_high"
#define OPT_DBUS_LEVEL_MEDIUM           "dbus_medium"
#define OPT_DBUS_LEVEL_LOW              "dbus_low"
#define OPT_DBUS_LEVEL_LOWER            "dbus_lower"
#define OPT_DBUS_LEVEL_LOWEST           "dbus_lowest"
#define OPT_DBUS_RC_MODE_CBR            "dbus_rc_mode_cbr"
#define OPT_DBUS_RC_MODE_VBR            "dbus_rc_mode_vbr"

#define OPT_DBUS_ENCORDE_TYPE_H264      "H.264"
#define OPT_DBUS_ENCORDE_TYPE_H265      "H.265"
#define OPT_DBUS_ENCORDE_TYPE_MJPEG     "MJPEG"
#define OPT_DBUS_ENCORDE_TYPE_MPEG4     "MPEG4"

#define RT_MAX_CAM_NUM           4
#define RT_MAX_SOUND_NUM         3
#define RT_MAX_OSD_REGION_NUM    15
#define RT_MAX_ROI_REGION_NUM    4

#define RT_PARAM_STRING_APPEND(s, s1, s2)  \
        s.append(s1).append("=").append(s2).append("\n")

#define RT_STRING_LINK_STREAM(s, format, upNodeId, downNodeId)          \
        s.append(format).append("_").append(util_to_string(upNodeId))   \
        .append("_").append(util_to_string(downNodeId))

#define RT_NODE_CONFIG_STRING_APPEND(s, key, value) \
        s.append("\"").append(key).append("\"")     \
        .append(" : ").append("\"").append(value).append("\",\n")

#define RT_NODE_CONFIG_NUMBER_APPEND(s, key, value) \
        s.append("\"").append(key).append("\"")     \
        .append(" : ").append(util_to_string(value)).append(",\n")

#define RT_NODE_CONFIG_STRING_LAST_APPEND(s, key, value) \
        s.append("\"").append(key).append("\"")          \
        .append(" : ").append("\"").append(value).append("\"\n")

#define RT_NODE_CONFIG_NUMBER_LAST_APPEND(s, key, value) \
        s.append("\"").append(key).append("\"")          \
        .append(" : ").append(util_to_string(value)).append("\n")

#define RT_NODE_TAG_APPEND(s, id) \
        s.append("\"").append(KEY_ROOT_NODE_ID).append(util_to_string(id)).append("\": {\n")

#define RT_PIPE_TAG_APPEND(s, id) \
        s.append("\"").append(KEY_ROOT_PIPE_ID).append(util_to_string(id)).append("\": {\n")

#define RT_NODE_OPTS_APPEND(s) \
        s.append("\"").append(KEY_ROOT_NODE_OPTS).append("\": {\n")

#define RT_STREAM_OPTS_APPEND(s) \
        s.append("\"").append(KEY_ROOT_STREAM_OPTS).append("\": {\n")

#define RT_TAG_END(s) \
        s.append("},\n")

#define RT_TAG_LAST_END(s) \
        s.append("}\n")

typedef enum _RTStreamId {
    RT_STREAM_ID_MAIN = 0,
    RT_STREAM_ID_2ND,
    RT_STREAM_ID_3RD,
    RT_STREAM_ID_4TH,
} RTStreamId;

typedef enum _RTNodeType {
    RT_NODE_TYPE_UNKNOW = 0,
    RT_NODE_TYPE_DEVICE,
    RT_NODE_TYPE_SOURCE,
    RT_NODE_TYPE_CODEC,
    RT_NODE_TYPE_FILTER,
    RT_NODE_TYPE_SINK,
} RTNodeType;

typedef enum _RTStreamType {
    RT_STM_TYPE_UNKNOW,
    RT_STM_TYPE_VIDEO,
    RT_STM_TYPE_AUDIO,
    RT_STM_TYPE_SUBTI,
    RT_STM_TYPE_IMAGE,
    RT_STM_TYPE_GENERAL,
    RT_STM_TYPE_MAX,
} RTStreamType;

typedef enum _RTNodeGateMode {
    RT_NODE_GATE_NORMAL = 0,
    RT_NODE_GATE_AUTO,
    RT_NODE_GATE_DELAYOPEN,
    RT_NODE_GATE_MAX,
} RTNodeGateMode;

typedef std::pair<std::string, std::string>              RTTaskNodeOpt;
typedef std::vector<std::pair<std::string, std::string>> RTTaskNodeOpts;

#endif   // SRC_RT_TASK_APP_GRAPH_RTNODECOMMON_H
