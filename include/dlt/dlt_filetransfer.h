#ifndef DLT_FILETRANSFER_H
#define DLT_FILETRANSFER_H

#include <limits.h>    /* Needed for LONG_MAX */
#include <sys/stat.h>  /* Needed for struct stat st*/
#include "dlt.h"       /* Needed for DLT Logs */
#include <signal.h>    /* Signal handling */
#include "errno.h"


/* ! dlt_user_log_file_complete 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_COMPLETE -300
/* ! dlt_user_log_file_complete 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_COMPLETE1 -301
/* ! dlt_user_log_file_complete 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_COMPLETE2 -302
/* ! dlt_user_log_file_complete 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_COMPLETE3 -303
/* ! dlt_user_log_file_head 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_HEAD -400
/* ! dlt_user_log_file_data 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_DATA -500
/* ! dlt_user_log_file_data 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_DATA_USER_BUFFER_FAILED -501
/* ! dlt_user_log_file_end 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_END -600
/* ! dlt_user_log_file_end 的错误代码 */
#define DLT_FILETRANSFER_ERROR_FILE_END_USER_CANCELLED -601
/* ! dlt_user_log_file_infoAbout 的错误代码 */
#define DLT_FILETRANSFER_ERROR_INFO_ABOUT -700
/* ! dlt_user_log_file_packagesCount 的错误代码 */
#define DLT_FILETRANSFER_ERROR_PACKAGE_COUNT -800
/* ! 获取序列号失败的错误代码 */
#define DLT_FILETRANSFER_FILE_SERIAL_NUMBER -900


/* !以多个 dlt 日志的形式传输完整文件。 */
/**该方法以多个 dlt 日志的形式传输完整文件。首先会检查文件是否存在。
 * 下一步，有关文件的一些通用信息将被记录到 dlt 中。
 * 现在，头信息将被记录到 dlt 中。更多信息请参阅方法 dlt_user_log_file_header。
 * 然后将调用方法 dlt_user_log_data，参数为在一定超时时间内循环记录所有软件包。
 * 最后，dlt_user_log_end 被调用，以提示文件传输已完成。这对 dlt 浏览器插件非常重要。
 * @param fileContext 将文件记录到 dlt 的特定上下文
 * @param 文件名 绝对文件路径
 * @param deleteFlag 文件传输后是否删除的标志。1-> 删除, 0-> 不删除
 * @param timeout 某些日志之间的超时（毫秒）。重要的是，dlt 的 FIFO 不会在短时间内被太多信息淹没。
 * @return 如果一切正常，则返回 0。如果出现故障，返回值 < 0。
 */
extern int dlt_user_log_file_complete(DltContext *fileContext, const char *filename, int deleteFlag, int timeout);


/* !This method gives information about the number of packages the file have */
/**Every file will be divided into several packages. Every package will be logged as a single dlt log.
 * The number of packages depends on the BUFFER_SIZE.
 * At first it will be checked if the file exist. Then the file will be divided into
 * several packages depending on the buffer size.
 * @param fileContext 将文件记录到 dlt 的特定上下文
 * @param 文件名 绝对文件路径
 * @return Returns 0 if everything was okey. If there was a failure value < 0 will be returned.
 */
extern int dlt_user_log_file_packagesCount(DltContext *fileContext, const char *filename);


/* !Logs specific file inforamtions to dlt */
/**The filename, file size, file serial number and the number of packages will be logged to dlt.
 * @param fileContext Specific context
 * @param 文件名 绝对文件路径
 * @return Returns 0 if everything was okey.If there was a failure value < 0 will be returned.
 */
extern int dlt_user_log_file_infoAbout(DltContext *fileContext, const char *filename);


/* !Transfer the head of the file as a dlt logs. */
/**The head of the file must be logged to dlt because the head contains inforamtion about the file serial number,
 * the file name, the file size, package number the file have and the buffer size.
 * All these informations are needed from the plugin of the dlt viewer.
 * See the Mainpages.c for more informations.
 * @param fileContext 将文件记录到 dlt 的特定上下文
 * @param 文件名 绝对文件路径
 * @param alias Alias for the file. An alternative name to show in the receiving end
 * @return Returns 0 if everything was okey. If there was a failure value < 0 will be returned.
 */
extern int dlt_user_log_file_header_alias(DltContext *fileContext, const char *filename, const char *alias);

/* !Transfer the head of the file as a dlt logs. */
/**The head of the file must be logged to dlt because the head contains inforamtion about the file serial number,
 * the file name, the file size, package number the file have and the buffer size.
 * All these informations are needed from the plugin of the dlt viewer.
 * See the Mainpages.c for more informations.
 * @param fileContext 将文件记录到 dlt 的特定上下文
 * @param 文件名 绝对文件路径
 * @return Returns 0 if everything was okey. If there was a failure value < 0 will be returned.
 */
extern int dlt_user_log_file_header(DltContext *fileContext, const char *filename);

//* !Transfer the content data of a file. */
/**See the Mainpages.c for more informations.
 * @param fileContext 将文件记录到 dlt 的特定上下文
 * @param 文件名 绝对文件路径
 * @param packageToTransfer Package number to transfer. If this param is LONG_MAX, the whole file will be transferred with a specific timeout
 * @param timeout Timeout to wait between dlt logs. Important because the dlt FIFO should not be flooded. Default is defined by MIN_TIMEOUT. The given timeout in ms can not be smaller than MIN_TIMEOUT.
 * @param fileCancelTransferFlag is a bool pointer to cancel the filetransfer on demand. For example in case of application shutdown event outstanding file transfer should abort and return
 * @return Returns 0 if everything was okey. If there was a failure value < 0 will be returned.
 */
extern int dlt_user_log_file_data_cancelable(DltContext *fileContext, const char *filename, int packageToTransfer, int timeout, bool *const fileCancelTransferFlag);


/* !Transfer the content data of a file. */
/**See the Mainpages.c for more informations.
 * @param fileContext 将文件记录到 dlt 的特定上下文
 * @param 文件名 绝对文件路径
 * @param packageToTransfer Package number to transfer. If this param is LONG_MAX, the whole file will be transferred with a specific timeout
 * @param timeout Timeout to wait between dlt logs. Important because the dlt FIFO should not be flooded. Default is defined by MIN_TIMEOUT. The given timeout in ms can not be smaller than MIN_TIMEOUT.
 * @return Returns 0 if everything was okey. If there was a failure value < 0 will be returned.
 */
extern int dlt_user_log_file_data(DltContext *fileContext, const char *filename, int packageToTransfer, int timeout);



/* !Transfer the end of the file as a dlt logs. */
/**The end of the file must be logged to dlt because the end contains inforamtion about the file serial number.
 * This informations is needed from the plugin of the dlt viewer.
 * See the Mainpages.c for more informations.
 * @param fileContext 将文件记录到 dlt 的特定上下文
 * @param 文件名 绝对文件路径
 * @param deleteFlag Flag to delete the file after the whole file is transferred (logged to dlt).1->delete,0->NotDelete
 * @return Returns 0 if everything was okey. If there was a failure value < 0 will be returned.
 */
extern int dlt_user_log_file_end(DltContext *fileContext, const char *filename, int deleteFlag);

#endif /* DLT_FILETRANSFER_H */
