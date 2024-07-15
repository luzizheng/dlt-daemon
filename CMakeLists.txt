# Set minimum Cmake version and setup policy behavior
cmake_minimum_required(VERSION 3.3)

if(${CMAKE_VERSION} VERSION_GREATER "3.20" OR ${CMAKE_VERSION} VERSION_EQUAL "3.20")
    cmake_policy(SET CMP0115 OLD)
endif()
project(automotive-dlt VERSION 2.18.10)


mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

include(GNUInstallDirs)
# Set version parameters
set(DLT_VERSION_STATE STABLE)

execute_process(COMMAND git describe --tags WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE DLT_REVISION
    ERROR_VARIABLE GIT_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
if(DLT_REVISION MATCHES "^$")
    set(PRINT_REVISION "Git revision unavailable")
else(DLT_REVISION MATCHES "")
    string(REPLACE "-" "_" DLT_REVISION ${DLT_REVISION})
    set(PRINT_REVISION ${DLT_REVISION})
endif()

# 如果用户没有定义，则设置默认构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
                         "选择建造类型: Debug, Release, RelWithDebInfo, MinSizeRel."
                         FORCE)
    message(STATUS "未定义构建类型。使用默认构建类型 "RelWithDebInfo.")
endif()

include(CMakeDependentOption)

# 一组独立选项
option(BUILD_SHARED_LIBS "设置为 OFF 可构建静态库"                                                      ON)
option(WITH_SYSTEMD "设置为 ON 可在 dlt-daemon 启动时创建单元文件并进行 systemd 检查"                         OFF)
option(WITH_SYSTEMD_WATCHDOG "设置为 ON 可在 dlt-daemon 中使用 systemd 进程监视程序"                                   OFF)
option(WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX "设为 ON，只有在上次触发后收到信息时才触发 dlt-daemon 的 systemd 进程监视程序"  OFF)
option(WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX_DLT_SYSTEM "设为 ON，只有在上一次触发后收到信息时才触发 dlt-system 的 systemd 进程监视程序"     OFF)
option(WITH_SYSTEMD_JOURNAL "设置为 ON，可在 dlt-system 中使用 systemd 日志"                                     OFF)
option(WITH_SYSTEMD_SOCKET_ACTIVATION "设置为 ON 可使用 systemd socket 激活"                                   OFF)
option(WITH_DOC "设置为 "ON"，以构建文档Target"                                                            OFF)
option(WITH_MAN "设置为 "ON"，以构建手册页面"                                                                       OFF)
option(WITH_CHECK_CONFIG_FILE "设置为 ON 时，将创建 CheckIncludeFiles、CheckFunctionExists 的配置文件。"       OFF)
option(WITH_TESTSCRIPTS "设置为 ON 可在测试脚本中运行 CMakeLists.txt"                                             OFF)
option(WITH_GPROF "设置 -pg 为编译标志"                                                                         OFF)
option(WITH_DLTTEST "设置为 "ON "时，将进行修改后的构建，以测试带损坏报文的用户--守护进程通信"  OFF)
option(WITH_DLT_SHM_ENABLE "实验！设置为 "ON "可将共享内存用作 IPC。试验性！"                      OFF)
option(WITH_DLT_ADAPTOR "设置为 ON 可构建 src/adaptor 二进制文件"                                                    OFF)
option(WITH_DLT_ADAPTOR_STDIN "设置为 ON 可构建 src/adaptor/stdin 二进制文件"                                        OFF)
option(WITH_DLT_ADAPTOR_UDP "设置为 ON 可构建 src/adaptor/udp 二进制文件"                                            OFF)
option(WITH_DLT_CONSOLE "设置为 ON 可构建 src/console 二进制文件"                                                    ON)
option(WITH_DLT_CONSOLE_WO_CTRL "设置为开，不在 src/console 下构建控制命令"                          OFF)
option(WITH_DLT_CONSOLE_WO_SBTM "设置为 ON 时，不在 src/console 下构建 dlt-sortbytimestamp"                       OFF)
option(WITH_DLT_CONSOLE_RECEIVE "设置为 OFF 时跳过构建 dlt_receive。"                                            ON)
option(WITH_DLT_CONSOLE_CONVERT "设置为 OFF 可跳过构建 dlt_convert"                                            ON)
option(WITH_DLT_CONSOLE_CONTROL "设置为 OFF 可跳过构建 dlt_control"                                            ON)
option(WITH_DLT_CONSOLE_PASSIVE_NODE_CTRL "设置为 OFF 可跳过构建 dlt_passive_node_ctrl"                        ON)

option(WITH_DLT_EXAMPLES "设置为 ON 可构建 src/examples 二进制文件"                                                  ON)
option(WITH_DLT_FILETRANSFER "设置为 ON 可构建支持文件传输的 dlt 系统"                               OFF)
option(WITH_DLT_SYSTEM "设置为 ON 可构建 src/system 二进制文件"                                                      OFF)
option(WITH_DLT_DBUS "设置为 ON 可构建 src/dbus 二进制文件"                                                          OFF)
option(WITH_DLT_TESTS "设置为 ON 可构建 src/test 二进制文件"                                                         ON)
option(WITH_DLT_UNIT_TESTS "设置为 "开启"，以构建 gtest 框架和测试/二进制文件"                                   OFF)
cmake_dependent_option(WITH_DLT_INSTALLED_TESTS "设置为 "开启 "可安装测试/二进制文件"                                OFF WITH_DLT_UNIT_TESTS OFF)
option(WITH_DLT_COVERAGE "设置为 ON，可生成 dlt-daemon 源代码的覆盖率报告"                          OFF)
option(BUILD_GMOCK "设置为 ON 可启用 gmock 构建"                                                                 OFF)
option(WITH_GIT_SUBMODULE "设置为 ON 时，在构建过程中更新子模块"                                              OFF)
option(WITH_DLT_QNX_SYSTEM "设置为 ON 可构建 QNX 系统二进制 dlt-qnx-system"                                     OFF)
option(WITH_DLT_FILE_LOGGING_SYSLOG_FALLBACK "设置为 ON 可在 dlt 记录到文件失败时启用回退到系统日志"   OFF)
option(WITH_DLT_NETWORK_TRACE "设置为 ON 可启用网络跟踪（如果支持消息队列）"                    ON)
option(WITH_DLT_LOG_LEVEL_APP_CONFIG "设置为 ON 可启用基于应用程序 ID 的默认日志级别"               OFF)

set(DLT_IPC "FIFO"
    CACHE STRING "UNIX_SOCKET,FIFO")
set(DLT_USER "bydos"
    CACHE STRING "为不以 root 用户身份运行的进程设置用户")
set(DLT_QNX_SLOG_ADAPTER_WAIT_BUFFER_TIMEOUT_MS "100"
    CACHE STRING "当输入缓冲区已满时,在丢弃信息前等待的超时,以毫秒为单位")

option(WITH_DLT_PKGCONFIG "设置为 ON 可生成 pkgconfig .pc 文件"                                                ON)
option(WITH_DLT_CXX11_EXT "设置为 "开启 "可构建 C++11 扩展"                                                      OFF)
option(WITH_DLT_COREDUMPHANDLER "实验！设置为 ON 可构建 src/core_dump_handler 二进制文件。试验性"      OFF)
option(WITH_DLT_LOGSTORAGE_CTRL_UDEV "PROTOTYPE！设置为 ON，以建立支持 udev 的日志存储控制"            OFF)
option(WITH_DLT_LOGSTORAGE_GZIP "设置为 ON，以构建支持 gzip 压缩的日志存储控制"                OFF)
option(WITH_DLT_USE_IPv6 "设置为 ON 以支持 IPv6"                                                                ON)
option(WITH_DLT_KPI "设置为 ON 可构建 src/kpi 二进制文件"                                                            OFF)
option(WITH_DLT_FATAL_LOG_TRAP "设置为 ON 可启用 DLT_LOG_FATAL 陷阱（在 dlt-user 库内触发 segv)"        OFF)
option(WITH_UDP_CONNECTION "设置为 ON 可启用 dlt UDP 多播支持"                                           OFF)
option(WITH_LIB_SHORT_VERSION "设置为 "ON "时，构建的程序库版本中只有主版本号" OFF)
option(WITH_DLT_DISABLE_MACRO "设置为 "ON"，可在不支持宏接口的情况下构建代码" OFF)
option(WITH_LEGACY_INCLUDE_PATH "设置为 ON 时，除了 <prefix> 以外，还将 <prefix>/dlt 添加到 CMake 配置文件的包含路径中。" ON)
option(WITH_EXTENDED_FILTERING "设置为 OFF 则不使用扩展过滤功能。Json 过滤器仅支持使用 json-c 和 QNX 的 Linux 系统" OFF)

option(WITH_DLT_DAEMON_VSOCK_IPC "设为 ON 可在守护进程中启用 VSOCK 支持" OFF)
option(WITH_DLT_LIB_VSOCK_IPC "设置为 ON 可启用库中的 VSOCK 支持（库中不使用 DLT_IPC）" OFF)

set(DLT_VSOCK_PORT "13490"
    CACHE STRING "用于记录流量的 VSOCK 端口号")
set(DLT_WRITEV_TIMEOUT_SEC "1"
    CACHE STRING "为 writev 设置秒超时，以防止无限阻塞")
set(DLT_WRITEV_TIMEOUT_USEC "0"
    CACHE STRING "为 writev 设置 usec 超时，以防止无限阻塞")

# RPM 设置
set(COVESA_RPM_RELEASE "1")  # ${DLT_REVISION}
set(LICENSE "Mozilla Public License Version 2.0")

# 构建、项目和包含设置
find_package(Threads REQUIRED)
if(WITH_DLT_LOGSTORAGE_GZIP)
    find_package(ZLIB 1.2.9 REQUIRED)
    set(ZLIB_LIBRARY "ZLIB::ZLIB")
elseif(WITH_DLT_COREDUMPHANDLER OR WITH_DLT_FILETRANSFER)
    find_package(ZLIB REQUIRED)
    set(ZLIB_LIBRARY "ZLIB::ZLIB")
else()
    set(ZLIB_LIBRARY "")
endif()

if(WITH_DLT_DBUS)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(DBUS REQUIRED dbus-1)
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}/include/dlt
    ${PROJECT_SOURCE_DIR}/include/dlt
    ${PROJECT_SOURCE_DIR}/src/shared
    ${PROJECT_SOURCE_DIR}/src/core_dump_handler
    ${PROJECT_SOURCE_DIR}/src/offlinelogstorage
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/daemon
    ${PROJECT_SOURCE_DIR}/src/console
    ${PROJECT_SOURCE_DIR}/src/gateway
    ${PROJECT_SOURCE_DIR}/systemd/3rdparty
)

add_definitions(-D_GNU_SOURCE)
add_definitions(-DDLT_WRITEV_TIMEOUT_SEC=${DLT_WRITEV_TIMEOUT_SEC})
add_definitions(-DDLT_WRITEV_TIMEOUT_USEC=${DLT_WRITEV_TIMEOUT_USEC})
add_definitions(-DDLT_QNX_SLOG_ADAPTER_WAIT_BUFFER_TIMEOUT_MS=${DLT_QNX_SLOG_ADAPTER_WAIT_BUFFER_TIMEOUT_MS})

if(NOT DLT_IPC STREQUAL "UNIX_SOCKET" AND NOT DLT_IPC STREQUAL "FIFO")
    message(FATAL_ERROR "${DLT_IPC} is not a valid value for DLT_IPC")
endif()

add_definitions(-DDLT_DAEMON_USE_${DLT_IPC}_IPC)

if(WITH_DLT_DAEMON_VSOCK_IPC)
    add_definitions(-DDLT_DAEMON_VSOCK_IPC_ENABLE)
endif()

if(NOT WITH_DLT_LIB_VSOCK_IPC)
    add_definitions(-DDLT_LIB_USE_${DLT_IPC}_IPC)
else()
    add_definitions(-DDLT_LIB_USE_VSOCK_IPC)
endif()

if(WITH_DLT_DAEMON_VSOCK_IPC OR WITH_DLT_LIB_VSOCK_IPC)
    add_definitions(-DDLT_VSOCK_PORT=${DLT_VSOCK_PORT})
endif()

if(NOT DLT_USER_IPC_PATH)
    set(DLT_USER_IPC_PATH "/tmp")
endif()

add_definitions(-DDLT_USER_IPC_PATH="${DLT_USER_IPC_PATH}")

if(WITH_DLTTEST)
    add_definitions(-DDLT_TEST_ENABLE)
endif()

if(WITH_DLT_UNIT_TESTS)
    add_definitions(-DDLT_UNIT_TESTS)
endif()

if(WITH_DLT_SHM_ENABLE)
    add_definitions(-DDLT_SHM_ENABLE)
endif()

if(WITH_DLT_USE_IPv6)
    add_definitions(-DDLT_USE_IPv6)
endif()

if(WITH_DLT_QNX_SYSTEM AND NOT "${CMAKE_C_COMPILER}" MATCHES "nto-qnx|qcc|ntoaarch64-gcc|ntox86_64-gcc")
    message(FATAL_ERROR "Can only compile for QNX with a QNX compiler, but found '${CMAKE_C_COMPILER}'.")
endif()

if(WITH_DLT_FILE_LOGGING_SYSLOG_FALLBACK)
    add_definitions(-DWITH_DLT_FILE_LOGGING_SYSLOG_FALLBACK)
endif()

if(WITH_DLT_LOGSTORAGE_GZIP)
    add_definitions(-DDLT_LOGSTORAGE_USE_GZIP)
endif()

if(WITH_GPROF)
    add_compile_options(-pg)
endif()

if(WITH_DLT_COVERAGE)
    add_definitions(-DWITH_DLT_COVERAGE)
    set(WITH_DLT_UNIT_TESTS ON)

    if(WITH_DLT_UNIT_TESTS)
        add_definitions(-DDLT_UNIT_TESTS)
    endif()

    set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_compile_options(
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99>
    $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++14>
    -Wall
    -Wextra
    # -pedantic
    -Wno-variadic-macros
    -Wno-strict-aliasing
)

if(WITH_DOC STREQUAL "OFF")
    set(PACKAGE_DOC "#")
else()
    set(PACKAGE_DOC "")
endif()

if(BUILD_SHARED_LIBS)
    set(CMAKE_STATIC_LIB_PATH "")
else()
    set(CMAKE_STATIC_LIB_PATH "-L\$\{libdir\}/static")
endif()

if(WITH_DLT_PKGCONFIG)
    configure_file(${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.spec.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.spec)
    configure_file(${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.pc.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
    install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig COMPONENT devel)
endif()

if(WITH_DLT_CXX11_EXT AND WITH_DLT_PKGCONFIG)
    configure_file(${PROJECT_SOURCE_DIR}/${PROJECT_NAME}-c++.pc.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-c++.pc @ONLY)
    install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-c++.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig COMPONENT devel)
endif()

set(CONFIGURATION_FILES_DIR ${CMAKE_INSTALL_SYSCONFDIR})

add_definitions(-DCONFIGURATION_FILES_DIR="${CMAKE_INSTALL_PREFIX}/${CONFIGURATION_FILES_DIR}")

add_subdirectory(cmake)

if(WITH_DLT_NETWORK_TRACE)
    # Message queue
    if(HAVE_MQUEUE_H AND HAVE_FUNC_MQOPEN AND HAVE_FUNC_MQCLOSE AND
       HAVE_FUNC_MQUNLINK AND HAVE_FUNC_MQSEND AND HAVE_FUNC_MQRECEIVE)
        add_definitions(-DDLT_NETWORK_TRACE_ENABLE)
        set(DLT_NETWORK_TRACE_ENABLE 1)
    else()
        message(STATUS "Disable network trace interface since message queue is not supported")
    endif()
else()
    message(STATUS "Network trace interface disabled")
endif()

if(WITH_SYSTEMD
    OR WITH_SYSTEMD_WATCHDOG
    OR WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX
    OR WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX_DLT_SYSTEM
    OR WITH_SYSTEMD_JOURNAL
    OR WITH_SYSTEMD_SOCKET_ACTIVATION)

    find_package(PkgConfig REQUIRED)
    execute_process(COMMAND pkg-config --modversion systemd OUTPUT_VARIABLE SYSTEMD_VERSION)
    string(REPLACE "\n" "" SYSTEMD_VERSION ${SYSTEMD_VERSION})

    if(WITH_SYSTEMD)
        add_definitions(-DDLT_SYSTEMD_ENABLE)
    endif()

    if(WITH_SYSTEMD_WATCHDOG)
        add_definitions(-DDLT_SYSTEMD_WATCHDOG_ENABLE)
    endif()

    if(WITH_SYSTEMD_JOURNAL)
        add_definitions(-DDLT_SYSTEMD_JOURNAL_ENABLE)
    endif()

    if(WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX)
        add_definitions(-DDLT_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX_ENABLE)
    endif()

    if(WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX_DLT_SYSTEM)
        add_definitions(-DDLT_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX_ENABLE_DLT_SYTSTEM)
    endif()

    if(WITH_SYSTEMD_SOCKET_ACTIVATION)
        if(NOT DLT_IPC STREQUAL "UNIX_SOCKET")
            message(FATAL_ERROR "WITH_SYSTEMD_SOCKET_ACTIVATION is only supported for UNIX_SOCKET")
        endif()
        add_definitions(-DDLT_SYSTEM_SOCKET_ACTIVATION_ENABLE)
    endif()

    set(systemd_SRCS ${PROJECT_SOURCE_DIR}/systemd/3rdparty/sd-daemon.c)

    set(SYSTEMD_UNITDIR "${CMAKE_INSTALL_PREFIX}/lib/systemd/system" CACHE PATH
        "Set directory to install systemd unit files")

    add_subdirectory(systemd)
else()
    set(systemd_SRCS "")
endif()

if(WITH_DLT_LOGSTORAGE_CTRL_UDEV)
    add_definitions(-DDLT_LOGSTORAGE_CTRL_UDEV_ENABLE)
endif()

if(WITH_DLT_FATAL_LOG_TRAP)
    add_definitions(-DDLT_FATAL_LOG_RESET_ENABLE)
endif()

if(WITH_DLT_FILTER_BACKEND_PROP)
   add_definitions(-DHAS_PROPRIETARY_FILTER_BACKEND)
endif()

if(WITH_EXTENDED_FILTERING)
    if(("${CMAKE_SYSTEM_NAME}" MATCHES "Linux") OR ("${CMAKE_SYSTEM_NAME}" MATCHES "Android"))
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(JSON REQUIRED json-c)
        set(DLT_JSON_LIBRARY ${JSON_LIBRARIES})
    elseif("${CMAKE_SYSTEM_NAME}" MATCHES "QNX")
        set(DLT_JSON_LIBRARY json)
    else()
        message(FATAL_ERROR "OS does not support extended filtering.
                Please build without cmake option '-DWITH_EXTENDED_FILTERING=OFF'")
    endif()
    add_definitions(-DEXTENDED_FILTERING)
else()
    set(DLT_JSON_LIBRARY "")
endif()

if(WITH_DLT_LOG_LEVEL_APP_CONFIG)
    add_definitions(-DDLT_LOG_LEVEL_APP_CONFIG)
endif()

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(testscripts)

if(WITH_GIT_SUBMODULE)
    add_definitions(-DWITH_GIT_SUBMODULE)
endif()

if(WITH_DLT_UNIT_TESTS)
    find_package(GTest)
    if(GTEST_FOUND)
        find_package(PkgConfig REQUIRED)
        execute_process(COMMAND pkg-config --modversion gtest OUTPUT_VARIABLE GTEST_VERSION)
        string(REPLACE "\n" "" GTEST_VERSION ${GTEST_VERSION})
        if(${GTEST_VERSION} VERSION_LESS 1.7.0)
            message(WARNING "Please use Gtest version greater or equal to 1.7.0,
                    or use option 'WITH_GIT_SUBMODULE' for latest version")
        endif()
    else()
        message(STATUS "No Gtest package found, preparing submodule ...")
        set(WITH_GIT_SUBMODULE ON)
    endif()

    if(WITH_GIT_SUBMODULE)
        find_package(Git QUIET)
        if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
            message(STATUS "Submodule updating ...")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}.
                        Please checkout submodule")
            endif()
        endif()

        if(NOT EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
            message(FATAL_ERROR "The submodule preparation failed. Please update submodule and try again!")
        else()
            add_subdirectory(googletest)
            if(NOT BUILD_GMOCK)
                add_definitions(-DBUILD_GMOCK)
            endif()
        endif()
    endif()

    enable_testing()
    add_subdirectory(tests)
endif()

message(STATUS)
message(STATUS "-------------------------------------------------------------------------------")
message(STATUS "Build for Version ${PROJECT_VERSION} build ${DLT_REVISION} version state ${DLT_VERSION_STATE}")
message(STATUS "WITH_SYSTEMD = ${WITH_SYSTEMD}")
message(STATUS "WITH_SYSTEMD_WATCHDOG = ${WITH_SYSTEMD_WATCHDOG}")
message(STATUS "WITH_SYSTEMD_JOURNAL = ${WITH_SYSTEMD_JOURNAL}")
message(STATUS "WITH_DOC = ${WITH_DOC}")
message(STATUS "WITH_MAN = ${WITH_MAN}")
message(STATUS "WITH_DLT_ADAPTOR = ${WITH_DLT_ADAPTOR}")
message(STATUS "WITH_DLT_ADAPTOR_UDP = ${WITH_DLT_ADAPTOR_UDP}")
message(STATUS "WITH_DLT_CONSOLE = ${WITH_DLT_CONSOLE}")
message(STATUS "WITH_DLT_CONSOLE_WO_CTRL = ${WITH_DLT_CONSOLE_WO_CTRL}")
message(STATUS "WITH_DLT_CONSOLE_WO_SBTM = ${WITH_DLT_CONSOLE_WO_SBTM}")
message(STATUS "WITH_DLT_EXAMPLES = ${WITH_DLT_EXAMPLES}")
message(STATUS "WITH_DLT_SYSTEM = ${WITH_DLT_SYSTEM}")
message(STATUS "WITH_DLT_FILETRANSFER = ${WITH_DLT_FILETRANSFER}")
message(STATUS "WITH_DLT_DBUS = ${WITH_DLT_DBUS}")
message(STATUS "WITH_DLT_TESTS = ${WITH_DLT_TESTS}")
message(STATUS "WITH_DLT_UNIT_TESTS = ${WITH_DLT_UNIT_TESTS}")
if(WITH_DLT_UNIT_TESTS)
    message(STATUS "WITH_DLT_INSTALLED_TESTS = ${WITH_DLT_INSTALLED_TESTS}")
endif(WITH_DLT_UNIT_TESTS)
if(GTEST_FOUND)
    message(STATUS "GTEST_VERSION = ${GTEST_VERSION}")
endif()
message(STATUS "WITH_DLT_COVERAGE = ${WITH_DLT_COVERAGE}")
message(STATUS "WITH_DLT_SHM_ENABLE = ${WITH_DLT_SHM_ENABLE}")
message(STATUS "WITH_DLTTEST = ${WITH_DLTTEST}")
message(STATUS "BUILD_GMOCK = ${BUILD_GMOCK}")
message(STATUS "WITH_GIT_SUBMODULE = ${WITH_GIT_SUBMODULE}")
message(STATUS "WITH_DLT_PKGCONFIG = ${WITH_DLT_PKGCONFIG}")
message(STATUS "WITH_DLT_CXX11_EXT = ${WITH_DLT_CXX11_EXT}")
message(STATUS "WITH_DLT_COREDUMPHANDLER = ${WITH_DLT_COREDUMPHANDLER}")
message(STATUS "WITH_DLT_KPI = ${WITH_DLT_KPI}")
message(STATUS "WITH_DLT_FATAL_LOG_TRAP = ${WITH_DLT_FATAL_LOG_TRAP}")
message(STATUS "WITH_CHECK_CONFIG_FILE = ${WITH_CHECK_CONFIG_FILE}")
message(STATUS "WITH_TESTSCRIPTS = ${WITH_TESTSCRIPTS}")
message(STATUS "WITH_GPROF = ${WITH_GPROF}")
message(STATUS "WITH_DLT_USE_IPv6 = ${WITH_DLT_USE_IPv6}")
message(STATUS "DLT_USER = ${DLT_USER}")
message(STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message(STATUS "TARGET_CPU_NAME = ${TARGET_CPU_NAME}")
if(WITH_SYSTEMD OR WITH_SYSTEMD_WATCHDOG OR WITH_SYSTEMD_JOURNAL)
    message(STATUS "SYSTEMD_VERSION = ${SYSTEMD_VERSION}")
    message(STATUS "SYSTEMD_UNITDIR = ${SYSTEMD_UNITDIR}")
    message(STATUS "WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX = ${WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX}")
    message(STATUS "WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX_DLT_SYSTEM = ${WITH_SYSTEMD_WATCHDOG_ENFORCE_MSG_RX_DLT_SYSTEM}")
endif()
message(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR = ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "WITH_DLT_LOGSTORAGE_CTRL_UDEV = ${WITH_DLT_LOGSTORAGE_CTRL_UDEV}")
message(STATUS "WITH_DLT_LOGSTORAGE_GZIP = ${WITH_DLT_LOGSTORAGE_GZIP}")
message(STATUS "DLT_IPC = ${DLT_IPC}(Path: ${DLT_USER_IPC_PATH})")
message(STATUS "WITH_DLT_DAEMON_VSOCK_IPC = ${WITH_DLT_DAEMON_VSOCK_IPC}")
message(STATUS "WITH_DLT_LIB_VSOCK_IPC = ${WITH_DLT_LIB_VSOCK_IPC}")
message(STATUS "DLT_VSOCK_PORT = ${DLT_VSOCK_PORT}")
message(STATUS "WITH_UDP_CONNECTION = ${WITH_UDP_CONNECTION}")
message(STATUS "WITH_DLT_QNX_SYSTEM = ${WITH_DLT_QNX_SYSTEM}")
message(STATUS "WITH_DLT_NETWORK_TRACE = ${WITH_DLT_NETWORK_TRACE}")
message(STATUS "WITH_LIB_NO_VERSION = ${WITH_LIB_NO_VERSION}")
message(STATUS "WITH_LIB_SHORT_VERSION = ${WITH_LIB_SHORT_VERSION}")
message(STATUS "WITH_LEGACY_INCLUDE_PATH = ${WITH_LEGACY_INCLUDE_PATH}")
message(STATUS "WITH_EXTENDED_FILTERING = ${WITH_EXTENDED_FILTERING}")
message(STATUS "WITH_DLT_DISABLE_MACRO = ${WITH_DLT_DISABLE_MACRO}")
message(STATUS "WITH_DLT_FILE_LOGGING_SYSLOG_FALLBACK = ${WITH_DLT_FILE_LOGGING_SYSLOG_FALLBACK}")
message(STATUS "WITH_DLT_LOG_LEVEL_APP_CONFIG = ${WITH_DLT_LOG_LEVEL_APP_CONFIG}")
message(STATUS "Change a value with: cmake -D<Variable>=<Value>")
message(STATUS "-------------------------------------------------------------------------------")
message(STATUS)
