#ifndef DLT_COMMON_LOG_H
#define DLT_COMMON_LOG_H

#include <stdio.h>
#include <stdbool.h>
#include "dlt_types.h"

#   if defined(__GNUC__)
#      define PURE_FUNCTION __attribute__((pure))
#      define PRINTF_FORMAT(a,b) __attribute__ ((format (printf, a, b)))
#   else
#      define PURE_FUNCTION /* nothing */
#      define PRINTF_FORMAT(a,b) /* nothing */
#   endif

typedef enum {
    DLT_LOG_TO_CONSOLE = 0,
    DLT_LOG_TO_SYSLOG = 1,
    DLT_LOG_TO_FILE = 2,
    DLT_LOG_TO_STDERR = 3,
    DLT_LOG_DROPPED = 4
} DltLoggingMode;

/* initialize this variables in dlt_log.c */
extern DltLoggingMode logging_mode;
extern FILE *logging_handle;

#   ifdef __cplusplus
extern "C"
{
#   endif

/**
 * Set internal logging filename if mode 2
 * @param filename the filename
 */
void dlt_log_set_filename(const char *filename);

/**
 * Set internal logging level
 * @param level the level
 */
void dlt_log_set_level(int level);

/**
 * 初始化（外部）日志记录设施
 * @param mode positive, 0 = log to stdout, 1 = log to syslog, 2 = log to file, 3 = log to stderr
 */
void dlt_log_init(int mode);

/**
 * 初始化（外部）日志记录设施
 * @param mode DltLoggingMode, 0 = log to stdout, 1 = log to syslog, 2 = log to file, 3 = log to stderr
 * @param enable_multiple_logfiles, true if multiple logfiles (incl. size limits) should be use
 * @param logging_file_size, maximum size in bytes of one logging file
 * @param logging_files_max_size, maximum size in bytes of all logging files
 */
DltReturnValue dlt_log_init_multiple_logfiles_support(DltLoggingMode mode, bool enable_multiple_logfiles, int logging_file_size, int logging_files_max_size);

/**
 * 为单个日志文件初始化（外部）日志记录设施。
 */
DltReturnValue dlt_log_init_single_logfile();

/**
 * 初始化（外部）多文件日志记录设施。
 */
DltReturnValue dlt_log_init_multiple_logfiles(int logging_file_size, int logging_files_max_size);

/**
 * 通过 DLT_LOG_MODE 环境变量，使用变量参数向指定的文件描述符打印（类似 fprintf）。
 * @param format 消息格式字符串
 * @return 如果出现错误则为负值 或成功时返回写入的字符总数
 */
int dlt_user_printf(const char *format, ...) PRINTF_FORMAT(1, 2);

/**
 * Log ASCII string with null-termination to (external) logging facility
 * @param prio priority (see syslog() call)
 * @param s Pointer to ASCII string with null-termination
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_log(int prio, const char *s);

/**
 * Log with variable arguments to (external) logging facility (like printf)
 * @param prio priority (see syslog() call)
 * @param format format string for log message
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_vlog(int prio, const char *format, ...) PRINTF_FORMAT(2, 3);

/**
 * Log size bytes with variable arguments to (external) logging facility (similar to snprintf)
 * @param prio priority (see syslog() call)
 * @param size number of bytes to log
 * @param format format string for log message
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_vnlog(int prio, size_t size, const char *format, ...) PRINTF_FORMAT(3, 4);

/**
 * Logs into log files represented by the multiple files buffer.
 * @param format First element in a specific format that will be logged.
 * @param ... Further elements in a specific format that will be logged.
 */
void dlt_log_multiple_files_write(const char* format, ...);

/**
 * De-Initialize (external) logging facility
 */
void dlt_log_free(void);

void dlt_log_free_single_logfile();

void dlt_log_free_multiple_logfiles();

/**
 * Checks whether (internal) logging in multiple files is active.
 */
bool dlt_is_log_in_multiple_files_active();

#   ifdef __cplusplus
}
#   endif

#endif /* DLT_COMMON_LOG_H */
