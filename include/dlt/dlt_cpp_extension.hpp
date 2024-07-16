#ifndef DLT_CPP_EXTENSION_HPP
#define DLT_CPP_EXTENSION_HPP

#include <string>
#include <vector>
#include <list>
#include <map>

#include "dlt.h"

template<typename T>
int32_t logToDlt(DltContextData &log, T const &value) = delete;

template<>
inline int32_t logToDlt(DltContextData &log, int8_t const &value)
{
    return dlt_user_log_write_int8(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, int16_t const &value)
{
    return dlt_user_log_write_int16(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, int32_t const &value)
{
    return dlt_user_log_write_int32(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, int64_t const &value)
{
    return dlt_user_log_write_int64(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, uint8_t const &value)
{
    return dlt_user_log_write_uint8(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, uint16_t const &value)
{
    return dlt_user_log_write_uint16(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, uint32_t const &value)
{
    return dlt_user_log_write_uint32(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, uint64_t const &value)
{
    return dlt_user_log_write_uint64(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, float32_t const &value)
{
    return dlt_user_log_write_float32(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, double const &value)
{
    return dlt_user_log_write_float64(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, bool const &value)
{
    return dlt_user_log_write_bool(&log, value);
}

static inline int32_t logToDlt(DltContextData &log, char const * const value)
{
    return dlt_user_log_write_utf8_string(&log, value);
}

static inline int32_t logToDlt(DltContextData &log, char * const value)
{
    return dlt_user_log_write_utf8_string(&log, value);
}

template<>
inline int32_t logToDlt(DltContextData &log, std::string const &value)
{
    return dlt_user_log_write_utf8_string(&log, value.c_str());
}

/* stl types */
template<>
int32_t logToDlt(DltContextData &log, std::string const &value);

template<typename _Tp, typename _Alloc = std::allocator<_Tp>>
static inline int32_t logToDlt(DltContextData &log, std::vector<_Tp, _Alloc> const & value)
{
    int result = 0;

    for (auto elem : value)
        result += logToDlt(log, elem);

    if (result != 0)
        result = -1;

    return result;
}

template<typename _Tp, typename _Alloc = std::allocator<_Tp>>
static inline int32_t logToDlt(DltContextData &log, std::list<_Tp, _Alloc> const & value)
{
    int result = 0;

    for (auto elem : value)
        result += logToDlt(log, elem);

    if (result != 0)
        result = -1;

    return result;
}

template<typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
                typename _Alloc = std::allocator<std::pair<const _Key, _Tp>>>
static inline int32_t logToDlt(DltContextData &log, std::map<_Key, _Tp, _Compare, _Alloc> const & value)
{
    int result = 0;

    for (auto elem : value)
    {
        result += logToDlt(log, elem.first);
        result += logToDlt(log, elem.second);
    }

    if (result != 0)
        result = -1;

    return result;
}

//variadic functions using C11 standard
template<typename First>
static inline int32_t logToDltVariadic(DltContextData &log, First const &valueA)
{
    return logToDlt(log, valueA);
}

template<typename First, typename ... Rest>
static inline int32_t logToDltVariadic(DltContextData &log, First const &valueA, const Rest&... valueB)
{
    int result = logToDlt(log, valueA) + logToDltVariadic(log, valueB...);

    if (result != 0)
        result = -1;

    return result;
}

/**
 * @brief 宏，用于编写日志信息，参数数量可变，且无需指定日志数据类型
 *
 * 该宏可用于任何提供 logToDlt 函数的类型。
 *
 * Example:
 * DLT_LOG_CXX(dltContext, DLT_LV_X, "text", valueA, valueB, ...)
 */
#define DLT_LOG_CXX(CONTEXT, LOGLEVEL, ...)\
    do\
    {\
        DltContextData log;\
        if (dlt_user_log_write_start(&CONTEXT,&log,LOGLEVEL)>0)\
        {\
            logToDltVariadic(log, ##__VA_ARGS__);\
            dlt_user_log_write_finish(&log);\
        }\
    }\
    while(false)

/**
 * @brief 宏，用于编写日志信息，参数数量可变，且无需指定日志数据类型.
 *
 * 该宏可用于任何提供 logToDlt 函数的类型。
 * 这包括代码生成的所有类型.
 *
 * 该宏类似于 \c DLT_LOG_CXX。不过，它将当前函数名添加为第一个日志参数。
 *
 * Example:
 * DLT_LOG_FCN_CXX(dltContext, DLT_LV_X, "text", valueA, valueB, ...)
 */
#define DLT_LOG_FCN_CXX(CONTEXT, LOGLEVEL, ...) \
    do\
    {\
        DltContextData log;\
        if (dlt_user_log_write_start(&CONTEXT, &log, LOGLEVEL) > 0)\
        {\
            dlt_user_log_write_string(&log, __PRETTY_FUNCTION__);\
            logToDltVariadic(log, ##__VA_ARGS__);\
            dlt_user_log_write_finish(&log);\
        }\
  }\
  while(false)

#endif /* DLT_CPP_EXTENSION_HPP */
