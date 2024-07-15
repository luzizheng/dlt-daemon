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
 * \file dlt_common_api.h
 */

/*******************************************************************************
**                                                                            **
**  SRC-MODULE: dlt_commpn_api.h                                              **
**                                                                            **
**  TARGET    : linux                                                         **
**                                                                            **
**  PROJECT   : DLT                                                           **
**                                                                            **
**  AUTHOR    : Alexander Wenzel Alexander.AW.Wenzel@bmw.de                   **
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
*******************************************************************************/

#ifndef DLT_COMMON_API_H
#define DLT_COMMON_API_H

#include "dlt.h"

/**
 * 为新上下文创建对象。
 * 嵌入 DLT 的通用应用程序接口
 * 每次都必须先调用这个宏.
 * @param CONTEXT 对象，其中包含一个特殊日志上下文的信息
 */
/* #define DLT_DECLARE_CONTEXT(CONTEXT) */
/* UNCHANGED */

/**
 * 使用另一个模块创建的新上下文对象。
 * 嵌入 DLT 的通用应用程序接口
 * 每次都必须先调用这个宏.
 * @param CONTEXT 对象，其中包含一个特殊日志上下文的信息
 */
/* #define DLT_IMPORT_CONTEXT(CONTEXT) */
/* UNCHANGED */

/**
 * 注册应用
 * 嵌入 DLT 的通用应用程序接口
 * @param APPID 应用程序 ID，最多四个字符
 * @param DESCRIPTION 包含说明的 ASCII 字符串
 */
/* #define DLT_REGISTER_APP(APPID,DESCRIPTION) */
/* UNCHANGED */

/**
 * 注册上下文，包括应用程序（默认日志级别和默认跟踪状态）
 * 嵌入 DLT 的通用应用程序接口
 * @param CONTEXT 对象，其中包含一个特殊日志上下文的信息
 * @param CONTEXTID 最多四个字符的上下文 ID
 * @param APPID 最多四个字符的应用 ID
 * @param DESCRIPTION ASCII string containing description
 */
#define DLT_REGISTER_CONTEXT_APP(CONTEXT, CONTEXTID, APPID, DESCRIPTION) \
    DLT_REGISTER_CONTEXT(CONTEXT, CONTEXTID, DESCRIPTION)

/**
 * 发送包含可变信息列表的日志信息（用于冗余模式）
 * 嵌入 DLT 的通用应用程序接口
 * @param CONTEXT 对象，其中包含一个特殊日志上下文的信息
 * @param LOGLEVEL 日志信息的日志级别
 * @param ARGS 变量参数表
 */
/*****************************************/
#define DLT_LOG0(CONTEXT, LOGLEVEL) \
    DLT_LOG(CONTEXT, LOGLEVEL)
/*****************************************/
#define DLT_LOG1(CONTEXT, LOGLEVEL, ARGS1) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1)
/*****************************************/
#define DLT_LOG2(CONTEXT, LOGLEVEL, ARGS1, ARGS2) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2)
/*****************************************/
#define DLT_LOG3(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3)
/*****************************************/
#define DLT_LOG4(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4)
/*****************************************/
#define DLT_LOG5(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5)
/*****************************************/
#define DLT_LOG6(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6)
/*****************************************/
#define DLT_LOG7(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7)
/*****************************************/
#define DLT_LOG8(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8)
/*****************************************/
#define DLT_LOG9(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9)
/*****************************************/
#define DLT_LOG10(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10)
/*****************************************/
#define DLT_LOG11(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10, ARGS11) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10, ARGS11)
/*****************************************/
#define DLT_LOG12(CONTEXT, \
                  LOGLEVEL, \
                  ARGS1, \
                  ARGS2, \
                  ARGS3, \
                  ARGS4, \
                  ARGS5, \
                  ARGS6, \
                  ARGS7, \
                  ARGS8, \
                  ARGS9, \
                  ARGS10, \
                  ARGS11, \
                  ARGS12) \
    DLT_LOG(CONTEXT, LOGLEVEL, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10, ARGS11, ARGS12)
/*****************************************/
#define DLT_LOG13(CONTEXT, \
                  LOGLEVEL, \
                  ARGS1, \
                  ARGS2, \
                  ARGS3, \
                  ARGS4, \
                  ARGS5, \
                  ARGS6, \
                  ARGS7, \
                  ARGS8, \
                  ARGS9, \
                  ARGS10, \
                  ARGS11, \
                  ARGS12, \
                  ARGS13) \
    DLT_LOG(CONTEXT, \
            LOGLEVEL, \
            ARGS1, \
            ARGS2, \
            ARGS3, \
            ARGS4, \
            ARGS5, \
            ARGS6, \
            ARGS7, \
            ARGS8, \
            ARGS9, \
            ARGS10, \
            ARGS11, \
            ARGS12, \
            ARGS13)
/*****************************************/
#define DLT_LOG14(CONTEXT, \
                  LOGLEVEL, \
                  ARGS1, \
                  ARGS2, \
                  ARGS3, \
                  ARGS4, \
                  ARGS5, \
                  ARGS6, \
                  ARGS7, \
                  ARGS8, \
                  ARGS9, \
                  ARGS10, \
                  ARGS11, \
                  ARGS12, \
                  ARGS13, \
                  ARGS14) \
    DLT_LOG(CONTEXT, \
            LOGLEVEL, \
            ARGS1, \
            ARGS2, \
            ARGS3, \
            ARGS4, \
            ARGS5, \
            ARGS6, \
            ARGS7, \
            ARGS8, \
            ARGS9, \
            ARGS10, \
            ARGS11, \
            ARGS12, \
            ARGS13, \
            ARGS14)
/*****************************************/
#define DLT_LOG15(CONTEXT, \
                  LOGLEVEL, \
                  ARGS1, \
                  ARGS2, \
                  ARGS3, \
                  ARGS4, \
                  ARGS5, \
                  ARGS6, \
                  ARGS7, \
                  ARGS8, \
                  ARGS9, \
                  ARGS10, \
                  ARGS11, \
                  ARGS12, \
                  ARGS13, \
                  ARGS14, \
                  ARGS15) \
    DLT_LOG(CONTEXT, \
            LOGLEVEL, \
            ARGS1, \
            ARGS2, \
            ARGS3, \
            ARGS4, \
            ARGS5, \
            ARGS6, \
            ARGS7, \
            ARGS8, \
            ARGS9, \
            ARGS10, \
            ARGS11, \
            ARGS12, \
            ARGS13, \
            ARGS14, \
            ARGS15)
/*****************************************/
#define DLT_LOG16(CONTEXT, \
                  LOGLEVEL, \
                  ARGS1, \
                  ARGS2, \
                  ARGS3, \
                  ARGS4, \
                  ARGS5, \
                  ARGS6, \
                  ARGS7, \
                  ARGS8, \
                  ARGS9, \
                  ARGS10, \
                  ARGS11, \
                  ARGS12, \
                  ARGS13, \
                  ARGS14, \
                  ARGS15, \
                  ARGS16) \
    DLT_LOG(CONTEXT, \
            LOGLEVEL, \
            ARGS1, \
            ARGS2, \
            ARGS3, \
            ARGS4, \
            ARGS5, \
            ARGS6, \
            ARGS7, \
            ARGS8, \
            ARGS9, \
            ARGS10, \
            ARGS11, \
            ARGS12, \
            ARGS13, \
            ARGS14, \
            ARGS15, \
            ARGS16)

/**
 * 发送包含可变信息列表的日志信息（用于非冗余模式）
 * 嵌入 DLT 的通用应用程序接口
 * @param CONTEXT 对象，其中包含一个特殊日志上下文的信息
 * @param LOGLEVEL 日志信息的日志级别
 * @param MSGID 日志报文的报文 ID
 * @param ARGS 变量参数表:
 * calls to DLT_STRING(), DLT_BOOL(), DLT_FLOAT32(), DLT_FLOAT64(),
 * DLT_INT(), DLT_UINT(), DLT_RAW()
 */
/*****************************************/
#define DLT_LOG_ID0(CONTEXT, LOGLEVEL, MSGID) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID)
/*****************************************/
#define DLT_LOG_ID1(CONTEXT, LOGLEVEL, MSGID, ARGS1) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1)
/*****************************************/
#define DLT_LOG_ID2(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2)
/*****************************************/
#define DLT_LOG_ID3(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3)
/*****************************************/
#define DLT_LOG_ID4(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4)
/*****************************************/
#define DLT_LOG_ID5(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5)
/*****************************************/
#define DLT_LOG_ID6(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6)
/*****************************************/
#define DLT_LOG_ID7(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7)
/*****************************************/
#define DLT_LOG_ID8(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8)
/*****************************************/
#define DLT_LOG_ID9(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9)
/*****************************************/
#define DLT_LOG_ID10(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10)
/*****************************************/
#define DLT_LOG_ID11(CONTEXT, \
                     LOGLEVEL, \
                     MSGID, \
                     ARGS1, \
                     ARGS2, \
                     ARGS3, \
                     ARGS4, \
                     ARGS5, \
                     ARGS6, \
                     ARGS7, \
                     ARGS8, \
                     ARGS9, \
                     ARGS10, \
                     ARGS11) \
    DLT_LOG_ID(CONTEXT, LOGLEVEL, MSGID, ARGS1, ARGS2, ARGS3, ARGS4, ARGS5, ARGS6, ARGS7, ARGS8, ARGS9, ARGS10, ARGS11)
/*****************************************/
#define DLT_LOG_ID12(CONTEXT, \
                     LOGLEVEL, \
                     MSGID, \
                     ARGS1, \
                     ARGS2, \
                     ARGS3, \
                     ARGS4, \
                     ARGS5, \
                     ARGS6, \
                     ARGS7, \
                     ARGS8, \
                     ARGS9, \
                     ARGS10, \
                     ARGS11, \
                     ARGS12) \
    DLT_LOG_ID(CONTEXT, \
               LOGLEVEL, \
               MSGID, \
               ARGS1, \
               ARGS2, \
               ARGS3, \
               ARGS4, \
               ARGS5, \
               ARGS6, \
               ARGS7, \
               ARGS8, \
               ARGS9, \
               ARGS10, \
               ARGS11, \
               ARGS12)
/*****************************************/
#define DLT_LOG_ID13(CONTEXT, \
                     LOGLEVEL, \
                     MSGID, \
                     ARGS1, \
                     ARGS2, \
                     ARGS3, \
                     ARGS4, \
                     ARGS5, \
                     ARGS6, \
                     ARGS7, \
                     ARGS8, \
                     ARGS9, \
                     ARGS10, \
                     ARGS11, \
                     ARGS12, \
                     ARGS13) \
    DLT_LOG_ID(CONTEXT, \
               LOGLEVEL, \
               MSGID, \
               ARGS1, \
               ARGS2, \
               ARGS3, \
               ARGS4, \
               ARGS5, \
               ARGS6, \
               ARGS7, \
               ARGS8, \
               ARGS9, \
               ARGS10, \
               ARGS11, \
               ARGS12, \
               ARGS13)
/*****************************************/
#define DLT_LOG_ID14(CONTEXT, \
                     LOGLEVEL, \
                     MSGID, \
                     ARGS1, \
                     ARGS2, \
                     ARGS3, \
                     ARGS4, \
                     ARGS5, \
                     ARGS6, \
                     ARGS7, \
                     ARGS8, \
                     ARGS9, \
                     ARGS10, \
                     ARGS11, \
                     ARGS12, \
                     ARGS13, \
                     ARGS14) \
    DLT_LOG_ID(CONTEXT, \
               LOGLEVEL, \
               MSGID, \
               ARGS1, \
               ARGS2, \
               ARGS3, \
               ARGS4, \
               ARGS5, \
               ARGS6, \
               ARGS7, \
               ARGS8, \
               ARGS9, \
               ARGS10, \
               ARGS11, \
               ARGS12, \
               ARGS13, \
               ARGS14)
/*****************************************/
#define DLT_LOG_ID15(CONTEXT, \
                     LOGLEVEL, \
                     MSGID, \
                     ARGS1, \
                     ARGS2, \
                     ARGS3, \
                     ARGS4, \
                     ARGS5, \
                     ARGS6, \
                     ARGS7, \
                     ARGS8, \
                     ARGS9, \
                     ARGS10, \
                     ARGS11, \
                     ARGS12, \
                     ARGS13, \
                     ARGS14, \
                     ARGS15) \
    DLT_LOG_ID(CONTEXT, \
               LOGLEVEL, \
               MSGID, \
               ARGS1, \
               ARGS2, \
               ARGS3, \
               ARGS4, \
               ARGS5, \
               ARGS6, \
               ARGS7, \
               ARGS8, \
               ARGS9, \
               ARGS10, \
               ARGS11, \
               ARGS12, \
               ARGS13, \
               ARGS14, \
               ARGS15)
/*****************************************/
#define DLT_LOG_ID16(CONTEXT, \
                     LOGLEVEL, \
                     MSGID, \
                     ARGS1, \
                     ARGS2, \
                     ARGS3, \
                     ARGS4, \
                     ARGS5, \
                     ARGS6, \
                     ARGS7, \
                     ARGS8, \
                     ARGS9, \
                     ARGS10, \
                     ARGS11, \
                     ARGS12, \
                     ARGS13, \
                     ARGS14, \
                     ARGS15, \
                     ARGS16) \
    DLT_LOG_ID(CONTEXT, \
               LOGLEVEL, \
               MSGID, \
               ARGS1, \
               ARGS2, \
               ARGS3, \
               ARGS4, \
               ARGS5, \
               ARGS6, \
               ARGS7, \
               ARGS8, \
               ARGS9, \
               ARGS10, \
               ARGS11, \
               ARGS12, \
               ARGS13, \
               ARGS14, \
               ARGS15, \
               ARGS16)

/**
 * 取消注册上下文.
 * 嵌入 DLT 的通用应用程序接口
 * @param CONTEXT 对象，其中包含一个特殊日志上下文的信息
 */
/* #define DLT_UNREGISTER_CONTEXT(CONTEXT) */
/* UNCHANGED */

/**
 * 取消注册应用程序.
 * 嵌入 DLT 的通用应用程序接口
 */
/* #define DLT_UNREGISTER_APP() */
/* UNCHANGED */

/**
 * 在日志信息中添加字符串参数.
 * 嵌入 DLT 的通用应用程序接口
 * 今后，在非冗余模式下，字符串将不会通过 DLT 信息发送。.
 * @param TEXT ASCII string
 */
/* #define DLT_CSTRING(TEXT) */
/* UNCHANGED */

#endif /* DLT_COMMON_API_H */

