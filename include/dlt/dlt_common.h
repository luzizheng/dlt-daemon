/*
 * SPDX license identifier: MPL-2.0
 *
 * Copyright (C) 2011-2015, BMW AG
 *
 * This file is part of COVESA Project DLT - Diagnostic Log and Trace.
 *
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License (MPL), v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For further information see http://www.covesa.org/.
 */

/*!
 * \author Alexander Wenzel <alexander.aw.wenzel@bmw.de>
 *
 * \copyright Copyright © 2011-2015 BMW AG. \n
 * License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
 *
 * \file dlt_common.h
 */

/*******************************************************************************
**                                                                            **
**  SRC-MODULE: dlt_common.h                                                  **
**                                                                            **
**  TARGET    : linux                                                         **
**                                                                            **
**  PROJECT   : DLT                                                           **
**                                                                            **
**  AUTHOR    : Alexander Wenzel Alexander.AW.Wenzel@bmw.de                   **
**              Markus Klein                                                  **
**                                                                            **
**  PURPOSE   :                                                               **
**                                                                            **
**  REMARKS   :                                                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Author Identity                                       **
********************************************************************************
**                                                                            **
** Initials     Name                       Company                            **
** --------     -------------------------  ---------------------------------- **
**  aw          Alexander Wenzel           BMW                                **
**  mk          Markus Klein               Fraunhofer ESK                     **
*******************************************************************************/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/

/*
 * $LastChangedRevision: 1670 $
 * $LastChangedDate: 2011-04-08 15:12:06 +0200 (Fr, 08. Apr 2011) $
 * $LastChangedBy$
 * Initials    Date         Comment
 * aw          13.01.2010   initial
 */
#ifndef DLT_COMMON_H
#   define DLT_COMMON_H

/**
 * \defgroup commonapi DLT 通用应用程序接口
 * \addtogroup commonapi
 \{
 */

#   include <netinet/in.h>
#   include <stdio.h>
#   include <stdbool.h>
#   ifdef __linux__
#      include <linux/limits.h>
#      include <sys/socket.h>
#   else
#      include <limits.h>
#   endif

#   if !defined(_MSC_VER)
#      include <unistd.h>
#      include <time.h>
#   endif

#   if defined(__GNUC__)
#      define PURE_FUNCTION __attribute__((pure))
#      define PRINTF_FORMAT(a,b) __attribute__ ((format (printf, a, b)))
#   else
#      define PURE_FUNCTION /* nothing */
#      define PRINTF_FORMAT(a,b) /* nothing */
#   endif

#   if !defined (__WIN32__) && !defined(_MSC_VER)
#      include <termios.h>
#   endif

#   include "dlt_types.h"
#   include "dlt_protocol.h"
#   include "dlt_log.h"

#   define DLT_PACKED __attribute__((aligned(1), packed))

#   if defined (__MSDOS__) || defined (_MSC_VER)
/* 改为在 Visual C++ 配置中设置 /Zp8 标志 */
#      undef DLT_PACKED
#      define DLT_PACKED
#   endif

/*
 * 交换字节序的宏
 */
#   define DLT_SWAP_64(value) ((((uint64_t)DLT_SWAP_32((value) & 0xffffffffull)) << 32) | (DLT_SWAP_32((value) >> 32)))

#   define DLT_SWAP_16(value) ((((value) >> 8) & 0xff) | (((value) << 8) & 0xff00))
#   define DLT_SWAP_32(value) ((((value) >> 24) & 0xff) | (((value) << 8) & 0xff0000) | (((value) >> 8) & 0xff00) | \
                               (((value) << 24) & 0xff000000))

/* 如果未定义，则将大端和小端设置为初始值 */
#   if !defined __USE_BSD
#      ifndef LITTLE_ENDIAN
#         define LITTLE_ENDIAN 1234
#      endif

#      ifndef BIG_ENDIAN
#         define BIG_ENDIAN    4321
#      endif
#   endif /* __USE_BSD */

/* 如果未定义字节序，则默认为小端顺序 */
#   if !defined __USE_BSD
#      ifndef BYTE_ORDER
#         define BYTE_ORDER LITTLE_ENDIAN
#      endif
#   endif /* __USE_BSD */

/* 检查字节序 */
#   if (BYTE_ORDER == BIG_ENDIAN)
/* #warning "大端架构!" */
#      define DLT_HTOBE_16(x) ((x))
#      define DLT_HTOLE_16(x) DLT_SWAP_16((x))
#      define DLT_BETOH_16(x) ((x))
#      define DLT_LETOH_16(x) DLT_SWAP_16((x))

#      define DLT_HTOBE_32(x) ((x))
#      define DLT_HTOLE_32(x) DLT_SWAP_32((x))
#      define DLT_BETOH_32(x) ((x))
#      define DLT_LETOH_32(x) DLT_SWAP_32((x))

#      define DLT_HTOBE_64(x) ((x))
#      define DLT_HTOLE_64(x) DLT_SWAP_64((x))
#      define DLT_BETOH_64(x) ((x))
#      define DLT_LETOH_64(x) DLT_SWAP_64((x))
#   else
/* #warning "小端架构!" */
#      define DLT_HTOBE_16(x) DLT_SWAP_16((x))
#      define DLT_HTOLE_16(x) ((x))
#      define DLT_BETOH_16(x) DLT_SWAP_16((x))
#      define DLT_LETOH_16(x) ((x))

#      define DLT_HTOBE_32(x) DLT_SWAP_32((x))
#      define DLT_HTOLE_32(x) ((x))
#      define DLT_BETOH_32(x) DLT_SWAP_32((x))
#      define DLT_LETOH_32(x) ((x))

#      define DLT_HTOBE_64(x) DLT_SWAP_64((x))
#      define DLT_HTOLE_64(x) ((x))
#      define DLT_BETOH_64(x) DLT_SWAP_64((x))
#      define DLT_LETOH_64(x) ((x))
#   endif

#   define DLT_ENDIAN_GET_16(htyp, x) ((((htyp) & DLT_HTYP_MSBF) > 0) ? DLT_BETOH_16(x) : DLT_LETOH_16(x))
#   define DLT_ENDIAN_GET_32(htyp, x) ((((htyp) & DLT_HTYP_MSBF) > 0) ? DLT_BETOH_32(x) : DLT_LETOH_32(x))
#   define DLT_ENDIAN_GET_64(htyp, x) ((((htyp) & DLT_HTYP_MSBF) > 0) ? DLT_BETOH_64(x) : DLT_LETOH_64(x))

#   if defined (__WIN32__) || defined (_MSC_VER)
#      define LOG_EMERG     0
#      define LOG_ALERT     1
#      define LOG_CRIT      2
#      define LOG_ERR       3
#      define LOG_WARNING   4
#      define LOG_NOTICE    5
#      define LOG_INFO      6
#      define LOG_DEBUG     7

#      define LOG_PID     0x01
#      define LOG_DAEMON  (3 << 3)
#   endif


/**
 * 用于 DLT 守护进程的标准 TCP 端口，可在启动 dlt-daemon 时通过 -p\<port\> 进行覆盖
 */
#   define DLT_DAEMON_TCP_PORT 3490


/* 文件描述符的初始值 */
#   define DLT_FD_INIT -1

/* 文件描述符的最小值，POSIX 标准除外：stdin=0、stdout=1、stderr=2 */
#   define DLT_FD_MINIMUM 3

/**
 * DLT ID 的大小
 */
#   define DLT_ID_SIZE 4

#   define DLT_SIZE_WEID DLT_ID_SIZE
#   define DLT_SIZE_WSID (sizeof(uint32_t))
#   define DLT_SIZE_WTMS (sizeof(uint32_t))

/* 文本输出缓冲区的大小 */
#define DLT_CONVERT_TEXTBUFSIZE  10024

/**
 * GET_LOG_INFO 的定义
 */
#   define DLT_GET_LOG_INFO_HEADER 18  /* 获取响应文本中日志信息标头的大小 */
#   define GET_LOG_INFO_LENGTH 13
#   define SERVICE_OPT_LENGTH 3

/**
 * 获取额外报头参数的大小，取决于 htyp
 */
#   define DLT_STANDARD_HEADER_EXTRA_SIZE(htyp) ((DLT_IS_HTYP_WEID(htyp) ? DLT_SIZE_WEID : 0) + \
                                                 (DLT_IS_HTYP_WSID(htyp) ? DLT_SIZE_WSID : 0) + \
                                                 (DLT_IS_HTYP_WTMS(htyp) ? DLT_SIZE_WTMS : 0))


#   if defined (__MSDOS__) || defined (_MSC_VER)
#      define __func__ __FUNCTION__
#   endif

#   define PRINT_FUNCTION_VERBOSE(_verbose) \
    if (_verbose) \
        dlt_vlog(LOG_INFO, "%s()\n", __func__)

#   ifndef NULL
#      define NULL (char *)0
#   endif

#   define DLT_MSG_IS_CONTROL(MSG)          ((DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) && \
                                             (DLT_GET_MSIN_MSTP((MSG)->extendedheader->msin) == DLT_TYPE_CONTROL))

#   define DLT_MSG_IS_CONTROL_REQUEST(MSG)  ((DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) && \
                                             (DLT_GET_MSIN_MSTP((MSG)->extendedheader->msin) == DLT_TYPE_CONTROL) && \
                                             (DLT_GET_MSIN_MTIN((MSG)->extendedheader->msin) == DLT_CONTROL_REQUEST))

#   define DLT_MSG_IS_CONTROL_RESPONSE(MSG) ((DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) && \
                                             (DLT_GET_MSIN_MSTP((MSG)->extendedheader->msin) == DLT_TYPE_CONTROL) && \
                                             (DLT_GET_MSIN_MTIN((MSG)->extendedheader->msin) == DLT_CONTROL_RESPONSE))

#   define DLT_MSG_IS_CONTROL_TIME(MSG)     ((DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) && \
                                             (DLT_GET_MSIN_MSTP((MSG)->extendedheader->msin) == DLT_TYPE_CONTROL) && \
                                             (DLT_GET_MSIN_MTIN((MSG)->extendedheader->msin) == DLT_CONTROL_TIME))

#   define DLT_MSG_IS_NW_TRACE(MSG)         ((DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) && \
                                             (DLT_GET_MSIN_MSTP((MSG)->extendedheader->msin) == DLT_TYPE_NW_TRACE))

#   define DLT_MSG_IS_TRACE_MOST(MSG)       ((DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) && \
                                             (DLT_GET_MSIN_MSTP((MSG)->extendedheader->msin) == DLT_TYPE_NW_TRACE) && \
                                             (DLT_GET_MSIN_MTIN((MSG)->extendedheader->msin) == DLT_NW_TRACE_MOST))

#   define DLT_MSG_IS_NONVERBOSE(MSG)       (!(DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) || \
                                             ((DLT_IS_HTYP_UEH((MSG)->standardheader->htyp)) && \
                                              (!(DLT_IS_MSIN_VERB((MSG)->extendedheader->msin)))))

/*
 *
 * DLT 报文缓冲区溢出的定义
 */
#   define DLT_MESSAGE_BUFFER_NO_OVERFLOW     0x00/**< 未发生缓冲区溢出 */
#   define DLT_MESSAGE_BUFFER_OVERFLOW        0x01/**< 发生缓冲区溢出 */

/*
 * DLT 输出变量的定义
 */
#   define DLT_OUTPUT_HEX              1
#   define DLT_OUTPUT_ASCII            2
#   define DLT_OUTPUT_MIXED_FOR_PLAIN  3
#   define DLT_OUTPUT_MIXED_FOR_HTML   4
#   define DLT_OUTPUT_ASCII_LIMITED    5

#   define DLT_FILTER_MAX 30 /**< 过滤器的最大数量 */

#   define DLT_MSG_READ_VALUE(dst, src, length, type) \
    do { \
        if ((length < 0) || ((length) < ((int32_t)sizeof(type)))) \
        { length = -1; } \
        else \
        { dst = *((type *)src); src += sizeof(type); length -= sizeof(type); } \
    } while(false)

#   define DLT_MSG_READ_ID(dst, src, length) \
    do { \
        if ((length < 0) || ((length) < DLT_ID_SIZE)) \
        { length = -1; } \
        else \
        { memcpy(dst, src, DLT_ID_SIZE); src += DLT_ID_SIZE; length -= DLT_ID_SIZE; } \
    } while(false)

#   define DLT_MSG_READ_STRING(dst, src, maxlength, dstlength, length) \
    do { \
        if ((maxlength < 0) || (length <= 0) || (dstlength < length) || (maxlength < length)) \
        { \
            maxlength = -1; \
        } \
        else \
        { \
            memcpy(dst, src, length); \
            dlt_clean_string(dst, length); \
            dst[length] = 0; \
            src += length; \
            maxlength -= length; \
        } \
    } while(false)

#   define DLT_MSG_READ_NULL(src, maxlength, length) \
    do { \
        if (((maxlength) < 0) || ((length) < 0) || ((maxlength) < (length))) \
        { length = -1; } \
        else \
        { src += length; maxlength -= length; } \
    } while(false)

#   define DLT_HEADER_SHOW_NONE       0x0000
#   define DLT_HEADER_SHOW_TIME       0x0001
#   define DLT_HEADER_SHOW_TMSTP      0x0002
#   define DLT_HEADER_SHOW_MSGCNT     0x0004
#   define DLT_HEADER_SHOW_ECUID      0x0008
#   define DLT_HEADER_SHOW_APID       0x0010
#   define DLT_HEADER_SHOW_CTID       0x0020
#   define DLT_HEADER_SHOW_MSGTYPE    0x0040
#   define DLT_HEADER_SHOW_MSGSUBTYPE 0x0080
#   define DLT_HEADER_SHOW_VNVSTATUS  0x0100
#   define DLT_HEADER_SHOW_NOARG      0x0200
#   define DLT_HEADER_SHOW_ALL        0xFFFF

/* dlt_receiver_check_and_get 标志 */
#   define DLT_RCV_NONE        0
#   define DLT_RCV_SKIP_HEADER (1 << 0)
#   define DLT_RCV_REMOVE      (1 << 1)

/**
 * 在 DLT 中，路径的最大长度
 * DLT 限制了路径长度，并没有采取任何其他措施来确定实际值，
 * 因为 DLT 运行的任何系统支持的最小值都是 1024 字节。
 */
#   define DLT_PATH_MAX 1024

/**
 * 安装路径的最大长度
 */
#   define DLT_MOUNT_PATH_MAX  1024

/**
 * 条目的最大长度
 */
#   define DLT_ENTRY_MAX 100

/**
 * 最大 IPC 路径长度
 */
#   define DLT_IPC_PATH_MAX 100

/**
 * 应用信息的最大接收缓冲区大小
 */
#   define DLT_RECEIVE_BUFSIZE 65535

/**
 * 最大线路长度
 */
#   define DLT_LINE_LEN 1024

/**
 * 网络跟踪宏
 */
#define DLT_TRACE_NW_TRUNCATED "NWTR"
#define DLT_TRACE_NW_START "NWST"
#define DLT_TRACE_NW_SEGMENT "NWCH"
#define DLT_TRACE_NW_END "NWEN"

/**
 * 测试静态功能的规定
 */
#   ifndef DLT_UNIT_TESTS
#      define DLT_STATIC static
#   else
#      define DLT_STATIC
#   endif

/**
 * 指定接收的数据来自套接字还是文件/fifo 的类型
 */
typedef enum
{
    DLT_RECEIVE_SOCKET,
    DLT_RECEIVE_UDP_SOCKET,
    DLT_RECEIVE_FD
} DltReceiverType;

/**
 * 包含字符 "DLS" + 0x01 的串行报头定义。
 */
extern const char dltSerialHeader[DLT_ID_SIZE];

/**
 * 将包含字符 "DLS "+ 0x01 的串行标头定义为字符。
 */
extern char dltSerialHeaderChar[DLT_ID_SIZE];

#if defined DLT_DAEMON_USE_FIFO_IPC || defined DLT_LIB_USE_FIFO_IPC
/**
 * dlt-daemon-fifo 和应用程序生成的 fifo 的共同基本路径
 */
extern char dltFifoBaseDir[DLT_PATH_MAX];
#endif

#ifdef DLT_SHM_ENABLE
/**
 * dlt-daemon 和应用程序共享内存的通用名称
 */
extern char dltShmName[NAME_MAX + 1];
#endif

/**
 * DLT ID 的类型（上下文 ID、应用程序 ID 等）
 */
typedef char ID4[DLT_ID_SIZE];

/**
 * DLT 文件存储标头的结构。该标头用于每个存储的 DLT 信息之前。
 */
typedef struct
{
    char pattern[DLT_ID_SIZE]; /**< 该模式应为 DLT0x01 */
    uint32_t seconds;          /**< 自 1970 年 1 月 1 日起的秒数 */
    int32_t microseconds;      /**< 微秒 */
    char ecu[DLT_ID_SIZE];     /**< 如果 DLT 报文中没有 ECU ID，则将其添加进来 */
} DLT_PACKED DltStorageHeader;

/**
 * DLT 标准标头的结构。每个 DLT 报文都使用该标头。
 */
typedef struct
{
    uint8_t htyp;           /**< 该参数包含多项信息，请参见以下定义 */
    uint8_t mcnt;           /**< 每发送一条 DLT 信息，信息计数器都会增加 */
    uint16_t len;           /**< 完整报文的长度（不含存储标头) */
} DLT_PACKED DltStandardHeader;

/**
 * DLT 额外标头参数的结构。每个参数只有在 htyp 中启用后才会发送。
 */
typedef struct
{
    char ecu[DLT_ID_SIZE];       /**< ECU id */
    uint32_t seid;               /**< Session id (会话id)*/
    uint32_t tmsp;               /**< 系统启动后的时间戳，以 0.1 毫秒为单位 */
} DLT_PACKED DltStandardHeaderExtra;

/**
 * DLT 扩展标头的结构。只有在 htyp 参数中启用时，才会发送该标头。
 */
typedef struct
{
    uint8_t msin;              /**< messsage info 报文信息 */
    uint8_t noar;              /**< number of arguments 参数个数 */
    char apid[DLT_ID_SIZE];    /**< 应用 id */
    char ctid[DLT_ID_SIZE];    /**< 上下文 id */
} DLT_PACKED DltExtendedHeader;

/**
 * 组织 DLT 信息的结构。
 * 该结构由相应的函数使用。
 */
typedef struct sDltMessage
{
    /* 标记 */
    int8_t found_serialheader;

    /* 偏移 */
    int32_t resync_offset;

    /* size 参数 */
    int32_t headersize;    /**< 包括存储标头在内的整个标头的size */
    int32_t datasize;      /**< 完整有效载荷的size */

    /* 当前加载信息的缓冲区 */
    uint8_t headerbuffer[sizeof(DltStorageHeader) +
                         sizeof(DltStandardHeader) + sizeof(DltStandardHeaderExtra) + sizeof(DltExtendedHeader)]; /**< buffer for loading complete header */
    uint8_t *databuffer;         /**< 用于加载有效载荷的缓冲区 */
    int32_t databuffersize;

    /* 当前加载的报文的标头值 */
    DltStorageHeader *storageheader;        /**< 指向当前已加载标头的存储标头的指针 */
    DltStandardHeader *standardheader;      /**< 指向当前已加载的标头的标准标头指针 */
    DltStandardHeaderExtra headerextra;     /**< 当前已加载的标头的额外参数 */
    DltExtendedHeader *extendedheader;      /**< 指向当前已加载头扩展的指针 */
} DltMessage;

/**
 * DLT 服务 "获取日志信息 " 的请求结构
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t options;                /**< type of request (请求类型) */
    char apid[DLT_ID_SIZE];         /**< application id (应用ID)*/
    char ctid[DLT_ID_SIZE];         /**< context id (上下文ID)*/
    char com[DLT_ID_SIZE];          /**< communication interface (通信接口) */
} DLT_PACKED DltServiceGetLogInfoRequest;

typedef struct
{
    uint32_t service_id;            /**< service ID(服务ID) */
} DLT_PACKED DltServiceGetDefaultLogLevelRequest;

/**
 * DLT 服务 "获取日志信息 "的响应结构。
 */
typedef struct
{
    char context_id[DLT_ID_SIZE];
    int16_t log_level;
    int16_t trace_status;
    uint16_t len_context_description;
    char *context_description;
} ContextIDsInfoType;

typedef struct
{
    char app_id[DLT_ID_SIZE];
    uint16_t count_context_ids;
    ContextIDsInfoType *context_id_info; /**< 保存特定 con id 的信息 */
    uint16_t len_app_description;
    char *app_description;
} AppIDsType;

typedef struct
{
    uint16_t count_app_ids;
    AppIDsType *app_ids;            /**< 保存特定应用程序 ID 的信息 */
} LogInfoType;

typedef struct
{
    uint32_t service_id;            /**< service ID(服务ID) */
    uint8_t status;                 /**< type of request (请求类型) */
    LogInfoType log_info_type;      /**< log info type  */
    char com[DLT_ID_SIZE];      /**< 通信接口 */
} DltServiceGetLogInfoResponse;

/**
 * DLT服务设置日志级别的结构
 */
typedef struct
{

    uint32_t service_id;            /**< service ID (服务ID) */
    char apid[DLT_ID_SIZE];         /**< application id (应用ID) */
    char ctid[DLT_ID_SIZE];         /**< context id (上下文ID) */
    uint8_t log_level;              /**< 需要设置的日志级别 */
    char com[DLT_ID_SIZE];          /**< 通信接口 */
} DLT_PACKED DltServiceSetLogLevel;

/**
 * DLT服务设置默认级别的结构
 */
typedef struct
{
    uint32_t service_id;                /**< service ID (服务ID) */
    uint8_t log_level;                  /**< 需要设置的默认级别 */
    char com[DLT_ID_SIZE];              /**< communication interface (通信接口) */
} DLT_PACKED DltServiceSetDefaultLogLevel;

/**
 * DLT服务设置冗余模式的结构
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t new_status;             /**< 需要设置的status */
} DLT_PACKED DltServiceSetVerboseMode;

/**
 * DLT服务设置通信接口状态的结构体
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    char com[DLT_ID_SIZE];          /**< communication interface (通信接口) */
    uint8_t new_status;             /**< 需要设置的status */
} DLT_PACKED DltServiceSetCommunicationInterfaceStatus;

/**
 * DLT服务设置通信最大带宽的结构 
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    char com[DLT_ID_SIZE];          /**< communication interface (通信接口) */
    uint32_t max_bandwidth;         /**< 最大带宽 */
} DLT_PACKED DltServiceSetCommunicationMaximumBandwidth;

typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
} DLT_PACKED DltServiceResponse;

typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
    uint8_t log_level;              /**< 日志级别 */
} DLT_PACKED DltServiceGetDefaultLogLevelResponse;

typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
    uint8_t overflow;               /**< 溢出状态 */
    uint32_t overflow_counter;      /**< 溢出计数 */
} DLT_PACKED DltServiceMessageBufferOverflowResponse;

typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
} DLT_PACKED DltServiceGetSoftwareVersion;

typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
    uint32_t length;                /**< 以下有效负载长度 */
    char *payload;                  /**< 有效负载 */
} DLT_PACKED DltServiceGetSoftwareVersionResponse;

/**
 * DLT 服务 取消注册上下文 的结构体
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
    char apid[DLT_ID_SIZE];         /**< application id (应用ID) */
    char ctid[DLT_ID_SIZE];         /**< context id (上下文ID) */
    char comid[DLT_ID_SIZE];        /**< communication interface (通信接口) */
} DLT_PACKED DltServiceUnregisterContext;

/**
 * DLT服务 连接信息 的结构体
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
    uint8_t state;                  /**< 新状态 */
    char comid[DLT_ID_SIZE];        /**< communication interface (通信接口) */
} DLT_PACKED DltServiceConnectionInfo;

/**
 * DLT 服务 时区 结构体
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
    int32_t timezone;               /**< 时区（秒 */
    uint8_t isdst;                  /**< 是否夏令时 */
} DLT_PACKED DltServiceTimezone;

/**
 * DLT 服务标记的结构
 */
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint8_t status;                 /**< 响应状态 */
} DLT_PACKED DltServiceMarker;

/***
 * DLT 服务离线日志存储的结构
 */
typedef struct
{
    uint32_t service_id;                  /**< service ID (服务ID) */
    char mount_point[DLT_MOUNT_PATH_MAX]; /**< 存储设备挂载点 */
    uint8_t connection_type;              /**< 连接设备的连接状态 已连接/断开 */
    char comid[DLT_ID_SIZE];              /**< communication interface (通信接口) */
} DLT_PACKED DltServiceOfflineLogstorage;

/** 
* Dlt 服务无源节点连接
*/
typedef struct
{
    uint32_t service_id;            /**< service ID (服务ID) */
    uint32_t connection_status;     /**< 连接/断开 */
    char node_id[DLT_ID_SIZE];      /**< 无源节点 ID */
} DLT_PACKED DltServicePassiveNodeConnect;

/**
 * DLT 服务无源节点连接状态的结构
 */
typedef struct
{
    uint32_t service_id;                       /**< service ID (服务ID) */
    uint8_t status;                            /**< 应答状态 */
    uint32_t num_connections;                  /**< 连接数 */
    uint8_t connection_status[DLT_ENTRY_MAX];  /**< 连接状态列表 */
    char node_id[DLT_ENTRY_MAX];               /**< 无源节点 ID 列表 */
} DLT_PACKED DltServicePassiveNodeConnectionInfo;

/**
 * 用于存储过滤器参数的结构。
 * ID 最多为四个字符。未使用的值用零填充。
 * 如果过滤器的每个值都有效，则 ID 应为空，只有零值。
 */
typedef struct
{
    char apid[DLT_FILTER_MAX][DLT_ID_SIZE]; /**< application id (应用ID) */
    char ctid[DLT_FILTER_MAX][DLT_ID_SIZE]; /**< context id (上下文ID) */
    int log_level[DLT_FILTER_MAX];          /**< 日志等级 */
    int32_t payload_max[DLT_FILTER_MAX];        /**< 有效负载上边界 */
    int32_t payload_min[DLT_FILTER_MAX];        /**< 有效负载下边界 */
    int counter;                            /**< 过滤器的数量 */
} DltFilter;

/**
 * 组织访问 DLT 文件的结构
 * 该结构由相应的函数使用
 */
typedef struct sDltFile
{
    /* 文件句柄和索引，以便快速访问 */
    FILE *handle;      /**< 已打开的 DLT 文件的文件句柄 */
    long *index;       /**< 所有 DLT 信息的文件位置，以便快速访问文件，仅过滤信息 */

    /* size 参数 */
    int32_t counter;       /**< 有过滤器的 DLT 文件中的信息数量 */
    int32_t counter_total; /**< 不带过滤器的 DLT 文件中的信息数量 */
    int32_t position;      /**< DLT 文件中已解析信息的当前索引，从 0 开始 */
    uint64_t file_length;    /**< 文件长度 */
    uint64_t file_position;  /**< 文件中的当前位置 */

    /* 错误计数器 */
    int32_t error_messages; /**< 在文件解析过程中发现的不完整 DLT 信息的数量 */

    /* filter parameters */
    DltFilter *filter;      /**< 过滤器列表指针。如果没有设置过滤器，则为零。 */
    int32_t filter_counter; /**< 过滤器数量 */

    /* 当前加载的信息 */
    DltMessage msg;     /**< 信息指针 */

} DltFile;

/**
 * 结构用于组织数据接收
 * 包括缓冲区处理
 * 该结构由相应的函数使用
 */
typedef struct
{
    int32_t lastBytesRcvd;    /**< 上次接收呼叫中收到的字节数 */
    int32_t bytesRcvd;        /**< 收到的字节数 */
    int32_t totalBytesRcvd;   /**< 接收字节总数 */
    char *buffer;         /**< 接收器缓冲区指针 */
    char *buf;            /**< 接收器缓冲区内的位置指针 */
    char *backup_buf;     /** 指向包含部分信息的缓冲区（如果有）的指针* */
    int fd;               /**< 连接句柄 */
    DltReceiverType type;     /**< 连接句柄类型 */
    int32_t buffersize;       /**< 接收器缓冲区大小 */
    struct sockaddr_in addr;  /**< 套接字地址信息 */
} DltReceiver;

typedef struct
{
    unsigned char *shm; /* 指向共享内存起点的指针 */
    unsigned int size;  /* 共享内存中数据区的大小 */
    unsigned char *mem; /* 指向共享内存中数据区的指针 */

    uint32_t min_size;     /**< 缓冲区的最小尺寸 */
    uint32_t max_size;     /**< 缓冲区的最大尺寸 */
    uint32_t step_size;    /**< 缓冲区的步幅 */
} DltBuffer;

typedef struct
{
    int write;
    int read;
    int count;
} DltBufferHead;

#   define DLT_BUFFER_HEAD "SHM"

typedef struct
{
    char head[4];
    unsigned char status;
    int size;
} DltBufferBlockHead;

#   ifdef DLT_USE_IPv6
#      define DLT_IP_SIZE (INET6_ADDRSTRLEN)
#   else
#      define DLT_IP_SIZE (INET_ADDRSTRLEN)
#   endif
typedef struct DltBindAddress
{
    char ip[DLT_IP_SIZE];
    struct DltBindAddress *next;
} DltBindAddress_t;

#   define DLT_MESSAGE_ERROR_OK       0
#   define DLT_MESSAGE_ERROR_UNKNOWN -1
#   define DLT_MESSAGE_ERROR_SIZE    -2
#   define DLT_MESSAGE_ERROR_CONTENT -3

#   ifdef __cplusplus
extern "C"
{
#   endif

/**
 * 以十六进制打印字节数组的辅助函数
 * @param ptr 字节数组的指针
 * @param size 要打印的字节数
 */
void dlt_print_hex(uint8_t *ptr, int size);
/**
 * 将十六进制字节数组打印成字符串的辅助函数
 * @param text 指向 ASCII 字符串的指针，文本写入其中
 * @param textlength 文本缓冲区的最大尺寸
 * @param ptr 字节数组的指针
 * @param size 要打印的字节数
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_print_hex_string(char *text, int textlength, uint8_t *ptr, int size);
/**
 * Helper function to print a byte array in hex and ascii into a string.
 * @param text pointer to a ASCII string, in which the text is written
 * @param textlength maximal size of text buffer
 * @param ptr pointer to the byte array.
 * @param size number of bytes to be printed.
 * @param html output is html? 0 - false, 1 - true
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_print_mixed_string(char *text, int textlength, uint8_t *ptr, int size, int html);
/**
 * Helper function to print a byte array in ascii into a string.
 * @param text pointer to a ASCII string, in which the text is written
 * @param textlength maximal size of text buffer
 * @param ptr pointer to the byte array.
 * @param size number of bytes to be printed.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_print_char_string(char **text, int textlength, uint8_t *ptr, int size);

/**
 * Helper function to determine a bounded length of a string.
 * This function returns zero if @a str is a null pointer,
 * and it returns @a maxsize if the null character was not found in the first @a maxsize bytes of @a str.
 * This is a re-implementation of C11's strnlen_s, which we cannot yet assume to be available.
 * @param str pointer to string whose length is to be determined
 * @param maxsize maximal considered length of @a str
 * @return the bounded length of the string
 */
PURE_FUNCTION size_t dlt_strnlen_s(const char* str, size_t maxsize);

/**
 * Helper function to print an id.
 * @param text pointer to ASCII string where to write the id
 * @param id four byte char array as used in DLT mesages as IDs.
 */
void dlt_print_id(char *text, const char *id);

/**
 * Helper function to set an ID parameter.
 * @param id four byte char array as used in DLT mesages as IDs.
 * @param text string to be copied into char array.
 */
void dlt_set_id(char *id, const char *text);

/**
 * Helper function to remove not nice to print characters, e.g. NULL or carage return.
 * @param text pointer to string to be cleaned.
 * @param length length of string excluding terminating zero.
 */
void dlt_clean_string(char *text, int length);

/**
 * Initialise the filter list.
 * This function must be called before using further dlt filter.
 * @param filter pointer to structure of organising DLT filter
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_filter_init(DltFilter *filter, int verbose);
/**
 * Free the used memory by the organising structure of filter.
 * @param filter pointer to structure of organising DLT filter
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_filter_free(DltFilter *filter, int verbose);
/**
 * Load filter list from file.
 * @param filter pointer to structure of organising DLT filter
 * @param filename filename to load filters from
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_filter_load(DltFilter *filter, const char *filename, int verbose);
/**
 * Save filter in space separated list to text file.
 * @param filter pointer to structure of organising DLT filter
 * @param filename filename to safe filters into
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_filter_save(DltFilter *filter, const char *filename, int verbose);
/**
 * Find index of filter in filter list
 * @param filter pointer to structure of organising DLT filter
 * @param apid application id to be found in filter list
 * @param ctid context id to be found in filter list
 * @param log_level log level to be found in filter list
 * @param payload_min minimum payload lenght to be found in filter list
 * @param payload_max maximum payload lenght to be found in filter list
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值 (or not found), else return index of filter
 */
int dlt_filter_find(DltFilter *filter, const char *apid, const char *ctid, const int log_level,
                                const int32_t payload_min, const int32_t payload_max, int verbose);
/**
 * Add new filter to filter list.
 * @param filter pointer to structure of organising DLT filter
 * @param apid application id to be added to filter list (must always be set).
 * @param ctid context id to be added to filter list. empty equals don't care.
 * @param log_level log level to be added to filter list. 0 equals don't care.
 * @param payload_min min lenght of payload to be added to filter list. 0 equals don't care.
 * @param payload_max max lenght of payload to be added to filter list. INT32_MAX equals don't care.
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_filter_add(DltFilter *filter, const char *apid, const char *ctid, const int log_level,
                                const int32_t payload_min, const int32_t payload_max, int verbose);
/**
 * Delete filter from filter list
 * @param filter pointer to structure of organising DLT filter
 * @param apid application id to be deleted from filter list
 * @param ctid context id to be deleted from filter list
 * @param log_level log level to be deleted from filter list
 * @param payload_min minimum payload lenght to be deleted from filter list
 * @param payload_max maximum payload lenght to be deleted from filter list
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_filter_delete(DltFilter *filter, const char *apid, const char *ctid, const int log_level,
                                const int32_t payload_min, const int32_t payload_max, int verbose);

/**
 * Initialise the structure used to access a DLT message.
 * This function must be called before using further dlt_message functions.
 * @param msg pointer to structure of organising access to DLT messages
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_init(DltMessage *msg, int verbose);
/**
 * Free the used memory by the organising structure of file.
 * @param msg pointer to structure of organising access to DLT messages
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_free(DltMessage *msg, int verbose);
/**
 * Print Header into an ASCII string.
 * This function calls dlt_message_header_flags() with flags=DLT_HEADER_SHOW_ALL
 * @param msg pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the header is written
 * @param textlength maximal size of text buffer
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_header(DltMessage *msg, char *text, size_t textlength, int verbose);
/**
 * Print Header into an ASCII string, selective.
 * @param msg pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the header is written
 * @param textlength maximal size of text buffer
 * @param flags select, bit-field to select, what should be printed (DLT_HEADER_SHOW_...)
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_header_flags(DltMessage *msg, char *text, size_t textlength, int flags, int verbose);
/**
 * Print Payload into an ASCII string.
 * @param msg pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the header is written
 * @param textlength maximal size of text buffer
 * @param type 1 = payload as hex, 2 = payload as ASCII.
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_payload(DltMessage *msg, char *text, size_t textlength, int type, int verbose);
/**
 * Check if message is filtered or not. All filters are applied (logical OR).
 * @param msg pointer to structure of organising access to DLT messages
 * @param filter pointer to filter
 * @param verbose if set to true verbose information is printed out.
 * @return 1 = filter matches, 0 = filter does not match, 如果出现错误则为负值
 */
DltReturnValue dlt_message_filter_check(DltMessage *msg, DltFilter *filter, int verbose);

/**
 * Read message from memory buffer.
 * Message in buffer has no storage header.
 * @param msg pointer to structure of organising access to DLT messages
 * @param buffer pointer to memory buffer
 * @param length length of message in buffer
 * @param resync if set to true resync to serial header is enforced
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
int dlt_message_read(DltMessage *msg, uint8_t *buffer, unsigned int length, int resync, int verbose);

/**
 * Get standard header extra parameters
 * @param msg pointer to structure of organising access to DLT messages
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_get_extraparameters(DltMessage *msg, int verbose);

/**
 * Set standard header extra parameters
 * @param msg pointer to structure of organising access to DLT messages
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_set_extraparameters(DltMessage *msg, int verbose);

/**
 * Initialise the structure used to access a DLT file.
 * This function must be called before using further dlt_file functions.
 * @param file pointer to structure of organising access to DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_init(DltFile *file, int verbose);
/**
 * Set a list to filters.
 * This function should be called before loading a DLT file, if filters should be used.
 * A filter list is an array of filters. Several filters are combined logically by or operation.
 * The filter list is not copied, so take care to keep list in memory.
 * @param file pointer to structure of organising access to DLT file
 * @param filter pointer to filter list array
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_set_filter(DltFile *file, DltFilter *filter, int verbose);
/**
 * Initialising loading a DLT file.
 * @param file pointer to structure of organising access to DLT file
 * @param filename filename of DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_open(DltFile *file, const char *filename, int verbose);
/**
 * This function reads DLT file and parse DLT message one by one.
 * Each message will be written into new file.
 * If a filter is set, the filter list is used.
 * @param file pointer to structure of organizing access to DLT file
 * @param filename file to contain parsed DLT messages.
 * @param type 1 = payload as hex, 2 = payload as ASCII.
 * @param verbose if set to true verbose information is printed out.
 * @return 0 = message does not match filter, 1 = message was read, 如果出现错误则为负值
 */
DltReturnValue dlt_file_quick_parsing(DltFile *file, const char *filename, int type, int verbose);
/**
 * Find next message in the DLT file and parse them.
 * This function finds the next message in the DLT file.
 * If a filter is set, the filter list is used.
 * @param file pointer to structure of organising access to DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 0 = message does not match filter, 1 = message was read, 如果出现错误则为负值
 */
DltReturnValue dlt_file_read(DltFile *file, int verbose);
/**
 * Find next message in the DLT file in RAW format (without storage header) and parse them.
 * This function finds the next message in the DLT file.
 * If a filter is set, the filter list is used.
 * @param file pointer to structure of organising access to DLT file
 * @param resync Resync to serial header when set to true
 * @param verbose if set to true verbose information is printed out.
 * @return 0 = message does not match filter, 1 = message was read, 如果出现错误则为负值
 */
DltReturnValue dlt_file_read_raw(DltFile *file, int resync, int verbose);
/**
 * Closing loading a DLT file.
 * @param file pointer to structure of organising access to DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_close(DltFile *file, int verbose);
/**
 * Load standard header of a message from file
 * @param file pointer to structure of organising access to DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_read_header(DltFile *file, int verbose);
/**
 * Load standard header of a message from file in RAW format (without storage header)
 * @param file pointer to structure of organising access to DLT file
 * @param resync Resync to serial header when set to true
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_read_header_raw(DltFile *file, int resync, int verbose);
/**
 * Load, if available in message, extra standard header fields and
 * extended header of a message from file
 * (dlt_file_read_header() must have been called before this call!)
 * @param file pointer to structure of organising access to DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_read_header_extended(DltFile *file, int verbose);
/**
 * Load payload of a message from file
 * (dlt_file_read_header() must have been called before this call!)
 * @param file pointer to structure of organising access to DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_read_data(DltFile *file, int verbose);
/**
 * Load headers and payload of a message selected by the index.
 * If filters are set, index is based on the filtered list.
 * @param file pointer to structure of organising access to DLT file
 * @param index position of message in the files beginning from zero
 * @param verbose if set to true verbose information is printed out.
 * @return number of messages loaded, 如果出现错误则为负值
 */
DltReturnValue dlt_file_message(DltFile *file, int index, int verbose);
/**
 * Free the used memory by the organising structure of file.
 * @param file pointer to structure of organising access to DLT file
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_file_free(DltFile *file, int verbose);

#if defined DLT_DAEMON_USE_FIFO_IPC || defined DLT_LIB_USE_FIFO_IPC
/**
 * Set FIFO base direction
 * @param pipe_dir the pipe direction
 */
void dlt_log_set_fifo_basedir(const char *pipe_dir);
#endif

/**
 * Set whether to print "name" and "unit" attributes in console output
 * @param state  true = with attributes, false = without attributes
 */
void dlt_print_with_attributes(bool state);

/**
 * Initialising a dlt receiver structure
 * @param receiver pointer to dlt receiver structure
 * @param _fd handle to file/socket/fifo, fram which the data should be received
 * @param type specify whether received data is from socket or file/fifo
 * @param _buffersize size of data buffer for storing the received data
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_receiver_init(DltReceiver *receiver, int _fd, DltReceiverType type, int _buffersize);
/**
 * De-Initialize a dlt receiver structure
 * @param receiver pointer to dlt receiver structure
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_receiver_free(DltReceiver *receiver);
/**
 * Initialising a dlt receiver structure
 * @param receiver pointer to dlt receiver structure
 * @param fd handle to file/socket/fifo, fram which the data should be received
 * @param type specify whether received data is from socket or file/fifo
 * @param buffer data buffer for storing the received data
 * @return 如果出现错误则为负值 and zero if success
 */
DltReturnValue dlt_receiver_init_global_buffer(DltReceiver *receiver, int fd, DltReceiverType type, char **buffer);
/**
 * De-Initialize a dlt receiver structure
 * @param receiver pointer to dlt receiver structure
 * @return 如果出现错误则为负值 and zero if success
 */
DltReturnValue dlt_receiver_free_global_buffer(DltReceiver *receiver);
/**
 * Receive data from socket or file/fifo using the dlt receiver structure
 * @param receiver pointer to dlt receiver structure
 * @return number of received bytes or 如果出现错误则为负值
 */
int dlt_receiver_receive(DltReceiver *receiver);
/**
 * Remove a specific size of bytes from the received data
 * @param receiver pointer to dlt receiver structure
 * @param size amount of bytes to be removed
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_receiver_remove(DltReceiver *receiver, int size);
/**
 * Move data from last receive call to front of receive buffer
 * @param receiver pointer to dlt receiver structure
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_receiver_move_to_begin(DltReceiver *receiver);

/**
 * Check whether to_get amount of data is available in receiver and
 * copy it to dest. Skip the DltUserHeader if skip_header is set to 1.
 * @param receiver pointer to dlt receiver structure
 * @param dest pointer to the destination buffer
 * @param to_get size of the data to copy in dest
 * @param skip_header whether if the DltUserHeader must be skipped.
 */
int dlt_receiver_check_and_get(DltReceiver *receiver,
                               void *dest,
                               unsigned int to_get,
                               unsigned int skip_header);

/**
 * Fill out storage header of a dlt message
 * @param storageheader pointer to storage header of a dlt message
 * @param ecu name of ecu to be set in storage header
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_set_storageheader(DltStorageHeader *storageheader, const char *ecu);
/**
 * Check if a storage header contains its marker
 * @param storageheader pointer to storage header of a dlt message
 * @return 0 no, 1 yes, 如果出现错误则为负值
 */
DltReturnValue dlt_check_storageheader(DltStorageHeader *storageheader);

/**
 * Checks if received size is big enough for expected data
 * @param received size
 * @param required size
 * @return negative value if required size is not sufficient
 * */
DltReturnValue dlt_check_rcv_data_size(int received, int required);

/**
 * Initialise static ringbuffer with a size of size.
 * Initialise as server. Init counters.
 * Memory is already allocated.
 * @param buf Pointer to ringbuffer structure
 * @param ptr Ptr to ringbuffer memory
 * @param size Maximum size of buffer in bytes
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_buffer_init_static_server(DltBuffer *buf, const unsigned char *ptr, uint32_t size);

/**
 * Initialize static ringbuffer with a size of size.
 * Initialise as a client. Do not change counters.
 * Memory is already allocated.
 * @param buf Pointer to ringbuffer structure
 * @param ptr Ptr to ringbuffer memory
 * @param size Maximum size of buffer in bytes
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_buffer_init_static_client(DltBuffer *buf, const unsigned char *ptr, uint32_t size);

/**
 * Initialize dynamic ringbuffer with a size of size.
 * Initialise as a client. Do not change counters.
 * Memory will be allocated starting with min_size.
 * If more memory is needed size is increased wit step_size.
 * The maximum size is max_size.
 * @param buf Pointer to ringbuffer structure
 * @param min_size Minimum size of buffer in bytes
 * @param max_size Maximum size of buffer in bytes
 * @param step_size size of which ringbuffer is increased
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_buffer_init_dynamic(DltBuffer *buf, uint32_t min_size, uint32_t max_size, uint32_t step_size);

/**
 * Deinitilaise usage of static ringbuffer
 * @param buf Pointer to ringbuffer structure
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_buffer_free_static(DltBuffer *buf);

/**
 * Release and free memory used by dynamic ringbuffer
 * @param buf Pointer to ringbuffer structure
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_buffer_free_dynamic(DltBuffer *buf);

/**
 * Check if message fits into buffer.
 * @param buf Pointer to buffer structure
 * @param needed Needed size
 * @return DLT_RETURN_OK if enough space, DLT_RETURN_ERROR otherwise
 */
DltReturnValue dlt_buffer_check_size(DltBuffer *buf, int needed);

/**
 * Write one entry to ringbuffer
 * @param buf Pointer to ringbuffer structure
 * @param data Pointer to data to be written to ringbuffer
 * @param size Size of data in bytes to be written to ringbuffer
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_buffer_push(DltBuffer *buf, const unsigned char *data, unsigned int size);

/**
 * Write up to three entries to ringbuffer.
 * Entries are joined to one block.
 * @param buf Pointer to ringbuffer structure
 * @param data1 Pointer to data to be written to ringbuffer
 * @param size1 Size of data in bytes to be written to ringbuffer
 * @param data2 Pointer to data to be written to ringbuffer
 * @param size2 Size of data in bytes to be written to ringbuffer
 * @param data3 Pointer to data to be written to ringbuffer
 * @param size3 Size of data in bytes to be written to ringbuffer
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_buffer_push3(DltBuffer *buf,
                                const unsigned char *data1,
                                unsigned int size1,
                                const unsigned char *data2,
                                unsigned int size2,
                                const unsigned char *data3,
                                unsigned int size3);

/**
 * Read one entry from ringbuffer.
 * Remove it from ringbuffer.
 * @param buf Pointer to ringbuffer structure
 * @param data Pointer to data read from ringbuffer
 * @param max_size Max size of read data in bytes from ringbuffer
 * @return size of read data, zero if no data available, 如果出现错误则为负值
 */
int dlt_buffer_pull(DltBuffer *buf, unsigned char *data, int max_size);

/**
 * Read one entry from ringbuffer.
 * Do not remove it from ringbuffer.
 * @param buf Pointer to ringbuffer structure
 * @param data Pointer to data read from ringbuffer
 * @param max_size Max size of read data in bytes from ringbuffer
 * @return size of read data, zero if no data available, 如果出现错误则为负值
 */
int dlt_buffer_copy(DltBuffer *buf, unsigned char *data, int max_size);

/**
 * Remove entry from ringbuffer.
 * @param buf Pointer to ringbuffer structure
 * @return size of read data, zero if no data available, 如果出现错误则为负值
 */
int dlt_buffer_remove(DltBuffer *buf);

/**
 * Print information about buffer and log to internal DLT log.
 * @param buf Pointer to ringbuffer structure
 */
void dlt_buffer_info(DltBuffer *buf);

/**
 * Print status of buffer and log to internal DLT log.
 * @param buf Pointer to ringbuffer structure
 */
void dlt_buffer_status(DltBuffer *buf);

/**
 * Get total size in bytes of ringbuffer.
 * If buffer is dynamic, max size is returned.
 * @param buf Pointer to ringbuffer structure
 * @return total size of buffer
 */
uint32_t dlt_buffer_get_total_size(DltBuffer *buf);

/**
 * Get used size in bytes of ringbuffer.
 * @param buf Pointer to ringbuffer structure
 * @return used size of buffer
 */
int dlt_buffer_get_used_size(DltBuffer *buf);

/**
 * Get number of entries in ringbuffer.
 * @param buf Pointer to ringbuffer structure
 * @return number of entries
 */
int dlt_buffer_get_message_count(DltBuffer *buf);

#   if !defined (__WIN32__)

/**
 * Helper function: Setup serial connection
 * @param fd File descriptor of serial tty device
 * @param speed Serial line speed, as defined in termios.h
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_setup_serial(int fd, speed_t speed);

/**
 * Helper function: Convert serial line baudrate (as number) to line speed (as defined in termios.h)
 * @param baudrate Serial line baudrate (as number)
 * @return Serial line speed, as defined in termios.h
 */
speed_t dlt_convert_serial_speed(int baudrate);

/**
 * Print dlt version and dlt svn version to buffer
 * @param buf Pointer to buffer
 * @param size size of buffer
 */
void dlt_get_version(char *buf, size_t size);

/**
 * Print dlt major version to buffer
 * @param buf Pointer to buffer
 * @param size size of buffer
 */
void dlt_get_major_version(char *buf, size_t size);

/**
 * Print dlt minor version to buffer
 * @param buf Pointer to buffer
 * @param size size of buffer
 */
void dlt_get_minor_version(char *buf, size_t size);

#   endif

/* Function prototypes which should be used only internally */
/*                                                          */

/**
 * Common part of initialisation. Evaluates the following environment variables
 * and stores them in dlt_user struct:
 * - DLT_DISABLE_EXTENDED_HEADER_FOR_NONVERBOSE
 * - DLT_LOCAL_PRINT_MODE (AUTOMATIC: 0, FORCE_ON: 2, FORCE_OFF: 3)
 * - DLT_INITIAL_LOG_LEVEL (e.g. APPx:CTXa:6;APPx:CTXb:5)
 * - DLT_FORCE_BLOCKING
 * - DLT_USER_BUFFER_MIN
 * - DLT_USER_BUFFER_MAX
 * - DLT_USER_BUFFER_STEP
 * - DLT_LOG_MSG_BUF_LEN
 * - DLT_DISABLE_INJECTION_MSG_AT_USER
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_init_common(void);

/**
 * Return the uptime of the system in 0.1 ms resolution
 * @return 0 if there was an error
 */
uint32_t dlt_uptime(void);

/**
 * Print header of a DLT message
 * @param message pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the header is written
 * @param size maximal size of text buffer
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_print_header(DltMessage *message, char *text, uint32_t size, int verbose);

/**
 * Print payload of a DLT message as Hex-Output
 * @param message pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the output is written
 * @param size maximal size of text buffer
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_print_hex(DltMessage *message, char *text, uint32_t size, int verbose);

/**
 * Print payload of a DLT message as ASCII-Output
 * @param message pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the output is written
 * @param size maximal size of text buffer
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_print_ascii(DltMessage *message, char *text, uint32_t size, int verbose);

/**
 * Print payload of a DLT message as Mixed-Ouput (Hex and ASCII), for plain text output
 * @param message pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the output is written
 * @param size maximal size of text buffer
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_print_mixed_plain(DltMessage *message, char *text, uint32_t size, int verbose);

/**
 * Print payload of a DLT message as Mixed-Ouput (Hex and ASCII), for HTML text output
 * @param message pointer to structure of organising access to DLT messages
 * @param text pointer to a ASCII string, in which the output is written
 * @param size maximal size of text buffer
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_print_mixed_html(DltMessage *message, char *text, uint32_t size, int verbose);

/**
 * Decode and print a argument of a DLT message
 * @param msg pointer to structure of organising access to DLT messages
 * @param type_info Type of argument
 * @param ptr pointer to pointer to data (pointer to data is changed within this function)
 * @param datalength pointer to datalength (datalength is changed within this function)
 * @param text pointer to a ASCII string, in which the output is written
 * @param textlength maximal size of text buffer
 * @param byteLength If argument is a string, and this value is 0 or greater, this value will be taken as string length
 * @param verbose if set to true verbose information is printed out.
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_message_argument_print(DltMessage *msg,
                                          uint32_t type_info,
                                          uint8_t **ptr,
                                          int32_t *datalength,
                                          char *text,
                                          size_t textlength,
                                          int byteLength,
                                          int verbose);

/**
 * Check environment variables.
 */
void dlt_check_envvar(void);

/**
 * Parse the response text and identifying service id and its options.
 *
 * @param resp_text   char *
 * @param service_id  int *
 * @param service_opt int *
 * @return pointer to resp_text
 */
int dlt_set_loginfo_parse_service_id(char *resp_text, uint32_t *service_id, uint8_t *service_opt);

/**
 * Convert get log info from ASCII to uint16
 *
 * @param rp        char
 * @param rp_count  int
 * @return length
 */
int16_t dlt_getloginfo_conv_ascii_to_uint16_t(char *rp, int *rp_count);

/**
 * Convert get log info from ASCII to int16
 *
 * @param rp        char
 * @param rp_count  int
 * @return length
 */
int16_t dlt_getloginfo_conv_ascii_to_int16_t(char *rp, int *rp_count);


/**
 * Convert get log info from ASCII to string (with '\0' termination)
 *
 * @param rp        char
 * @param rp_count  int
 * @param wp        char Array needs to be 1 byte larger than len to store '\0'
 * @param len       int
 */
void dlt_getloginfo_conv_ascii_to_string(char *rp, int *rp_count, char *wp, int len);


/**
 * Convert get log info from ASCII to ID (without '\0' termination)
 *
 * @param rp        char
 * @param rp_count  int
 * @param wp        char
 * @param len       int
 * @return position of last read character in wp
 */
int dlt_getloginfo_conv_ascii_to_id(char *rp, int *rp_count, char *wp, int len);

/**
 * Convert from hex ASCII to binary
 * @param ptr    const char
 * @param binary uint8_t
 * @param size   int
 */
void dlt_hex_ascii_to_binary(const char *ptr, uint8_t *binary, int *size);

/**
 * Helper function to execute the execvp function in a new child process.
 * @param filename file path to store the stdout of command (NULL if not required)
 * @param command execution command followed by arguments with NULL-termination
 * @return 如果出现错误则为负值
 */
int dlt_execute_command(char *filename, char *command, ...);

/**
 * Return the extension of given file name.
 * @param filename Only file names without prepended path allowed.
 * @return pointer to extension
 */
char *get_filename_ext(const char *filename);

/**
 * Extract the base name of given file name (without the extension).
 * @param abs_file_name Absolute path to file name.
 * @param base_name Base name it is extracted to.
 * @param base_name_length Base name length.
 * @return indicating success
 */
bool dlt_extract_base_name_without_ext(const char* const abs_file_name, char* base_name, long base_name_len);

#   ifdef __cplusplus
}
#   endif

/**
 \}
 */

#endif /* DLT_COMMON_H */
