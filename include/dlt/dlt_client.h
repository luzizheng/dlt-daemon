#ifndef DLT_CLIENT_H
#   define DLT_CLIENT_H

/**
 * \defgroup clientapi DLT 客户端应用程序接口
 * \addtogroup clientapi
 \{
 */

#   include "dlt_types.h"
#   include "dlt_common.h"
#include <stdbool.h>

typedef enum
{
    DLT_CLIENT_MODE_UNDEFINED = -1,
    DLT_CLIENT_MODE_TCP,
    DLT_CLIENT_MODE_SERIAL,
    DLT_CLIENT_MODE_UNIX,
    DLT_CLIENT_MODE_UDP_MULTICAST
} DltClientMode;

typedef struct
{
    DltReceiver receiver;  /**< 指向 dlt 接收器结构的接收器指针 */
    int sock;              /**< 套接字连接句柄 */
    char *servIP;          /**< servIP 网络接口的IP地址/主机名 */
    char *hostip;          /**< hostip UDP 主机接收器网络接口的 IP 地址 */
    int port;              /**< 用于 TCP 连接的端口（可选） */
    char *serialDevice;    /**< serialDevice 串行设备的设备名 */
    char *socketPath;      /**< socketPath Unix 套接字路径 */
    char ecuid[4];         /**< ECUiD */
    speed_t baudrate;      /**< 波特率 串行接口的波特率，以 speed_t 表示 */
    DltClientMode mode;    /**< DltClientMode */
    int send_serial_header;    /**< (Boolean）发送带串行报文头的 DLT 报文 */
    int resync_serial_header;  /**< (Boolean) 在所有连接上重新同步到串行标头 */
} DltClient;

#   ifdef __cplusplus
extern "C" {
#   endif

void dlt_client_register_message_callback(int (*registerd_callback)(DltMessage *message, void *data));
void dlt_client_register_fetch_next_message_callback(bool (*registerd_callback)(void *data));

/**
 * 使用特定端口初始化 dlt 客户端结构
 * @param client 指向 dlt 客户端结构的指针
 * @param port tcp 连接的端口
 * @param verbose 如果设置为 "true"，则会打印出详细的信息。
 * @return 如果出现错误则为负值
 */
int dlt_client_init_port(DltClient *client, int port, int verbose);

/**
 * 初始化 dlt 客户端结构
 * @param client 指向 dlt 客户端结构的指针
 * @param verbose 如果设置为 "true"，则会打印出详细的信息。
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_init(DltClient *client, int verbose);
/**
 * 使用 dlt 客户端结构中的信息连接 dlt 守护进程
 * @param client 指向 dlt 客户端结构的指针
 * @param verbose 如果设置为 "true"，则会打印出详细的信息。
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_connect(DltClient *client, int verbose);
/**
 * 清理 dlt 客户端结构
 * @param client 指向 dlt 客户端结构的指针
 * @param verbose 如果设置为 "true"，则会打印出详细的信息。
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_cleanup(DltClient *client, int verbose);
/**
 * dlt 客户端应用程序的主要循环
 * @param client 指向 dlt 客户端结构的指针
 * @param data 指向要提供给主循环的数据的指针
 * @param verbose 如果设置为 "true"，则会打印出详细的信息。
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_main_loop(DltClient *client, void *data, int verbose);

/**
 * 通过套接字向守护进程发送信息。
 * @param client 指向 dlt 客户端结构的指针。
 * @param msg 以 DLT 格式发送的信息。
 * @return 来自 DltReturnValue 枚举的值.
 */
DltReturnValue dlt_client_send_message_to_socket(DltClient *client, DltMessage *msg);

/**
 * 向 dlt 守护进程发送控制信息
 * @param client 指向 dlt 客户端结构的指针
 * @param apid 应用ID
 * @param ctid context id
 * @param payload 装满控制信息数据的缓冲区
 * @param size 控制信息数据的大小
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_ctrl_msg(DltClient *client, char *apid, char *ctid, uint8_t *payload, uint32_t size);
/**
 * 向 dlt 守护进程发送注入信息
 * @param client 指向 dlt 客户端结构的指针
 * @param apid 应用ID
 * @param ctid 上下文ID
 * @param serviceID service id
 * @param buffer 注入信息数据的缓冲区
 * @param size 缓冲区内注入数据的大小
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_inject_msg(DltClient *client,
                                          char *apid,
                                          char *ctid,
                                          uint32_t serviceID,
                                          uint8_t *buffer,
                                          uint32_t size);
/**
 * 向 dlt 守护进程发送设置日志级别信息
 * @param client 指向 dlt 客户端结构的指针
 * @param apid 应用ID
 * @param ctid context id
 * @param logLevel Log 等级
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_log_level(DltClient *client, char *apid, char *ctid, uint8_t logLevel);
/**
 * 向 dlt 守护进程发送获取日志信息的请求
 * @param client 指向 dlt 客户端结构的指针
 * @return 如果出现错误则为负值
 */
int dlt_client_get_log_info(DltClient *client);
/**
 * 向 dlt 守护进程发送获取默认日志级别的请求
 * @param client 指向 dlt 客户端结构的指针
 * @return 如果出现错误则为负值
 */
DltReturnValue dlt_client_get_default_log_level(DltClient *client);
/**
 * 向 dlt 守护进程发送获取软件版本的请求
 * @param client 指向 dlt 客户端结构的指针
 * @return 如果出现错误则为负值
 */
int dlt_client_get_software_version(DltClient *client);
/**
 * 初始化获取日志信息结构
 * @return void
 */
void dlt_getloginfo_init(void);
/**
 * 释放为获取日志信息中的应用程序描述分配的内存
 * @return void
 */
void dlt_getloginfo_free(void);
/**
 * 向 dlt 守护进程发送设置跟踪状态信息
 * @param client 指向 dlt 客户端结构的指针
 * @param apid 应用ID
 * @param ctid context id
 * @param traceStatus 默认 Trace 状态
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_trace_status(DltClient *client, char *apid, char *ctid, uint8_t traceStatus);
/**
 * 向 dlt 守护进程发送默认日志级别
 * @param client 指向 dlt 客户端结构的指针
 * @param defaultLogLevel 默认Log等级
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_default_log_level(DltClient *client, uint8_t defaultLogLevel);
/**
 * 向 dlt 守护进程注册的所有上下文发送日志级别
 * @param client 指向 dlt 客户端结构的指针
 * @param logLevel 要设置的 Log 等级
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_all_log_level(DltClient *client, uint8_t LogLevel);
/**
 * 向 dlt 守护进程发送默认跟踪状态
 * @param client 指向 dlt 客户端结构的指针
 * @param defaultTraceStatus 默认跟踪状态
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_default_trace_status(DltClient *client, uint8_t defaultTraceStatus);
/**
 * 向 dlt 守护进程注册的所有上下文发送跟踪状态
 * @param client 指向 dlt 客户端结构的指针
 * @param traceStatus trace status to be set
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_all_trace_status(DltClient *client, uint8_t traceStatus);
/**
 * 向 dlt 守护进程发送定时包状态
 * @param client 指向 dlt 客户端结构的指针
 * @param timingPakets 启用定时包
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_timing_pakets(DltClient *client, uint8_t timingPakets);
/**
 * 向 dlt 守护进程发送存储配置命令
 * @param client 指向 dlt 客户端结构的指针
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_store_config(DltClient *client);
/**
 * 向 dlt 守护进程发送重置为出厂默认设置的命令
 * @param client 指向 dlt 客户端结构的指针
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_send_reset_to_factory_default(DltClient *client);

/**
 * 在 dlt 客户端结构内设置波特率
 * @param client 指向 dlt 客户端结构的指针
 * @param baudrate Baudrate
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_setbaudrate(DltClient *client, int baudrate);

/**
 * 在 dlt 客户端结构内设置模式
 * @param client 指向 dlt 客户端结构的指针
 * @param mode DltClientMode
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_set_mode(DltClient *client, DltClientMode mode);

/**
 * 设置服务器IP
 * @param client 指向 dlt 客户端结构的指针
 * @param ipaddr 指向命令行参数的指针
 * @return 如果出现错误则为负值
 */
int dlt_client_set_server_ip(DltClient *client, char *ipaddr);

/**
 * 设置服务器 UDP 主机接收器接口地址
 * @param client 指向 dlt 客户端结构的指针
 * @param hostip 指向多播组地址的指针
 * @return 如果出现错误则为负值
 */
int dlt_client_set_host_if_address(DltClient *client, char *hostip);

/**
 * 设置串行设备
 * @param client 指向 dlt 客户端结构的指针
 * @param serial_device 指向命令行参数的指针
 * @return 如果出现错误则为负值
 */
int dlt_client_set_serial_device(DltClient *client, char *serial_device);

/**
 * 设置套接字路径
 * @param client 指向 dlt 客户端结构的指针
 * @param socket_path 指向套接字路径字符串的指针
 * @return 如果出现错误则为负值
 */
int dlt_client_set_socket_path(DltClient *client, char *socket_path);

/**
 * 解析 GET_LOG_INFO 应答的文本 
 * @param resp      GET_LOG_INFO 应答
 * @param resp_text 用 ASCII 表示的应答文本
 * @return 来自 DltReturnValue 枚举的值
 */
DltReturnValue dlt_client_parse_get_log_info_resp_text(DltServiceGetLogInfoResponse *resp,
                                                       char *resp_text);

/**
 * 释放为获取日志信息分配的内存
 * @param resp 应答
 * @return 成功时为 0，否则为 -1
 */
int dlt_client_cleanup_get_log_info(DltServiceGetLogInfoResponse *resp);
#   ifdef __cplusplus
}
#   endif

/**
 \}
 */

#endif /* DLT_CLIENT_H */
