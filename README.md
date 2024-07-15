# 诊断日志和跟踪


[![Build Status](https://github.com/COVESA/dlt-daemon/actions/workflows/cmake-ctest.yml/badge.svg)]( https://github.com/COVESA/dlt-daemon/actions/workflows/cmake-ctest.yml)
[![CodeQL](https://github.com/COVESA/dlt-daemon/actions/workflows/codeql-analysis.yml/badge.svg?branch=master)](https://github.com/COVESA/dlt-daemon/actions/workflows/codeql-analysis.yml)
[![Page-build-deployment](https://github.com/COVESA/dlt-daemon/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/COVESA/dlt-daemon/actions/workflows/pages/pages-build-deployment)

**Code coverage reports online** 📄 [LCOV - code coverage report](https://COVESA.github.io/dlt-daemon/dlt_lcov_report/index.html)

# 诊断日志和跟踪

欢迎来到 COVESA 诊断日志和跟踪 (DLT). If you are familiar with DLT
and want to know what's new, check the [Release Notes](ReleaseNotes.md).

**DLT 新手？太好了！欢迎加入。** 我们为您准备了一份简短的[概述](#overview)
以及如何立即[开始](#get-started)的一些信息。在熟悉了 DLT 的基本机制后，您可以 [了解更多](#learn-more) 高级概念和功能。

## Overview

COVESA DLT 基于[AUTOSAR 经典平台 R19-11 DLT]()中指定的标准化协议，提供日志和跟踪接口。
[AUTOSAR Classic Platform R19-11 DLT](https://www.autosar.org/fileadmin/standards/R19-11/CP/AUTOSAR_SWS_DiagnosticLogAndTrace.pdf)中指定的标准化协议为基础，提供了日志和跟踪接口。
它被其他 COVESA 组件使用，但也可用作与 COVESA 无关的其他应用程序的日志框架。
最重要的术语和部分如下图所示。请参阅[术语表](doc/dlt_glossary.md)，全面了解 DLT 专用术语。

![alt text](doc/images/dlt_overview.png "DLT Overview")

- 从本质上讲，**DLT 用户**是一个应用程序，它服务于各自的（与 DLT 无关的）目的，并生成 DLT 日志信息。它利用 DLT 库来制作和传输这些信息。
- DLT 库**为 DLT 用户（即应用程序）创建 DLT 日志信息并将其发送给 DLT 守护进程提供了便捷的应用程序接口。如果后者不可用，该库会将信息缓存在一个环形缓冲区中，这样它们就不会立即丢失。
- DLT 守护进程是 ECU 的 DLT 通信接口。它收集和缓冲来自 ECU 上运行的一个或多个 DLT 用户的日志信息，并应 DLT 客户的要求提供给他们。守护进程还接受来自客户端的控制信息，以调整守护进程或应用程序的行为。
- **DLT 客户端**通过从 DLT 守护进程中获取 DLT 用户的日志信息来接收和使用这些信息。它还可以发出控制信息，以控制 DLT 守护进程或其连接的 DLT 用户的行为。DLT 客户端甚至可以通过注入信息向 DLT 用户传输用户定义的数据。

这只是所有用例中最简单的一种，您将在[开始](#get-start)部分进一步了解这些用例。
[开始](#get-started) 部分进一步探讨。一旦你想[了解更多](#learn-more)、
你就会发现，软件源包含了利用多个
适配器和控制台实用程序以及测试应用程序。

## Get Started
在本节中，你可以学习如何[构建和安装](#build-and-install) DLT。然后，你可以选择[运行 DLT 演示](#run-a-dlt-demo) 设置，或者从[开发自己的 DLT 功能应用程序](#develop-your-own-dlt-featured-application) 开始。

### Build and install

需要安装以下软件包，才能构建和安装 DLT 守护进程：

- cmake
- zlib
- dbus
- json-c (仅 dlt-receives 扩展过滤需要)

在 Ubuntu 上，可以使用以下命令安装这些依赖项:

```bash
sudo apt-get install cmake zlib1g-dev libdbus-glib-1-dev build-essential
optional: sudo apt-get install libjson-c-dev # 如果您想使用 dlt-receives 扩展过滤功能
```

然后继续下载 DLT（如果尚未下载）。我们建议克隆版本库，但下载并解压压缩包也可以。
```bash
cd /path/to/workspace
git clone https://github.com/COVESA/dlt-daemon.git
```

按照以下步骤构建和安装 DLT 守护进程:

```bash
cd /path/to/workspace/dlt-daemon
mkdir build
cd build
cmake ..
make
optional: sudo make install
optional: sudo ldconfig # 万一你执行了 make install
```

关于 Cygwin 上的 DLT，请参阅[在 Cygwin 上构建和安装 DLT](doc/dlt_on_Cygwin.md)。

CMake 接受大量的[编译选项]（doc/dlt_build_options.md）来配置编译以满足您的需求。

### Run a DLT demo
如果您还没有看过[概述](#overview)，现在是了解最重要术语和了解数据缓冲位置的最佳时机。
然后继续阅读我们的[如何设置 DLT 演示设置]指南（doc/dlt_demo_setup.md）。

### Develop your own DLT-featured application

既然您已经看到了 DLT 的实际应用，您可能想使用 DLT 开发自己的应用程序。
您可以在我们的["应用程序开发人员的 DLT "指南（doc/dlt_for_developers.md）]中找到所需的一切。

提示：如果您想阅读 API 文档，目前必须在本地构建。
API 文档由 _doxygen 生成。
要编译它，请在运行 cmake 时使用 ```-DWITH_DOC=ON``` 选项，例如：

```bash
mkdir build
cd build
cmake -DWITH_DOC=ON ..
make doc
```

### Build DLT debian package

要为自己的目的构建 DLT debian 软件包，请按照以下步骤操作:

```bash
dpkg-buildpackage -us -uc
```

## Learn more
当您开发出第一个应用程序后，您可能想了解更多。
了解 DLT 的[高级主题](#advanced-topics)，
学习如何[配置、控制和接口](#configure-control-and-interface) DLT，
或通过查看[设计规范（./doc/dlt_design_specification.md）]来研究其内部结构。

### Advanced Topics
COVESA DLT 实现的功能远不止 "发送 "日志信息。本节将为您介绍高级功能。请点击链接了解相关概念的更多信息。

| Document | Description |
|----|----|
| [Build Options](./doc/dlt_build_options.md) | The CMake build system provides a large amount of build options. They let you turn on or off certain features and provide alternative implementation details. |
| [LogStorage](doc/dlt_offline_logstorage.md) | The DLT Daemon as well as the DLT libary provide buffers for caching log data during absence of a consumer. However, some use cases require to write large amounts of log message e.g. to mass storages for long term storage or because no other means of exfiltrating the log data is available. |
| [MultiNode](doc/dlt_multinode.md) | A DLT Daemon can run as a gateway to connect multiple passive nodes. Each passive node has its owns DLT Applications and runs its own daemon. The gateway node connects to all of them, collects the logs and routes them to the DLT Client. |
| [Extended Network Trace](doc/dlt_extended_network_trace.md) | Normal DLT messages are limited in size. To overcome this limitation the feature network trace message allows the user to send or truncate messages which would not fit into a normal DLT message. |
| [DLT Filetransfer](doc/dlt_filetransfer.md) | Although not originally designed for this, files can be transmitted over DLT. A corresponding DLT Client (e.g. DLT Viewer) can receive and decode them accordingly. |
| [DLT KPI](doc/dlt_kpi.md) | Valueable status information about the monitored system can be read via DLT as well. The information under `/proc` of the target system is at your hands easily. |
| [DLT Core Dump Handler](/doc/dlt_cdh.md) | This tool collects and extracts debug information then utilize [DLT Filetransfer](doc/dlt_filetransfer.md) to transfer the information to client. |

### Configure, Control and Interface

关于 DLT，我们还有很多东西需要探索。如果使用 cmake 选项 "```-DWITH_MAN=ON```"打开 manpages 的生成，
你就能了解如何配置 DLT 以完全满足你的需求，如何控制运行实例的行为，以及如何通过提供的适配器将 DLT 与现有系统连接起来。

手册是用 *pandoc* 生成的，它还需要 *asciidoc* 作为依赖项。

用以下方法生成手册（初始或因为某些内容发生变化），例如
```bash
mkdir build
cd build
cmake -DWITH_MAN=ON ..
make generate_man
```

| Document | Description |
|----|----|
| *配置* ||
|[dlt-daemon(1)](doc/dlt-daemon.1.md) | 如何启动 DLT-Daemon |
|[dlt.conf(5)](doc/dlt.conf.5.md) | 配置 DLT 框架以反映您的使用情况|
| *控制运行中的 DLT 实例*||
|[dlt-receive(1)](doc/dlt-receive.1.md)| 从守护进程接收 DLT 信息，并打印或存储日志信息. |
|[dlt-control(1)](doc/dlt-control.1.md)| 向守护进程发送控制信息. |
|[dlt-logstorage-ctrl(1)](doc/dlt-logstorage-ctrl.1.md)| 向守护进程发送连接/断开特定日志存储设备的触发器，或发送将内部缓冲区数据同步到日志存储文件的要求. |
|[dlt-passive-node-ctrl(1)](doc/dlt-passive-node-ctrl.1.md)| 向守护进程发送触发器，以连接/断开被动守护进程. |
| *连接 DLT* ||
|[dlt-system(1)](doc/dlt-system.1.md) | DLT-System 提供了一种通过 DLT 直接访问系统日志的方法 |
|[dlt-system.conf(5)](doc/dlt-system.conf.5.md) | 配置 DLT 系统 |
|[dlt-adaptor-stdin(1)](doc/dlt-adaptor-stdin.1.md)| 从 stdin 向守护进程转发输入的适配器. |
|[dlt-adaptor-udp(1)](doc/dlt-adaptor-udp.1.md)| 将收到的 UDP 信息转发给守护进程的适配器. |
|[dlt-convert(1)](doc/dlt-convert.1.md)| 将 DLT 文件转换为人类可读格式. |
|[dlt-sortbytimestamp(1)](doc/dlt-sortbytimestamp.1.md)| 从 DLT 文件中读取日志信息，按时间戳排序，然后重新存储. |
|[dlt-qnx-system(1)](doc/dlt-qnx-system.md) | 使用 DLT 在 QNX 中访问系统日志 |

## Contribution

开始工作，最好的做法是在工作期间提交较小的、可编译的片段，以便日后处理。

如果您想提交更改，请在 Github 上创建 [Pull Request](https://github.com/covesa/dlt-daemon/pulls)。
请务必遵守 [提交信息规则 (https://at.projects.covesa.org/wiki/display/PROJ/Rules+for+Commit+Messages)

### Coding Rules

该项目现在使用 clang-format 代替 uncrustify.

为方便起见，任何代码变更都将在提交前通过钩子/预提交进行统一.

- 安装 clang-format

- 安装预提交脚本:

  ```bash
  cp scripts/pre-commit.sample .git/hooks/pre-commit
  ```

- 配置: .clang-format

有关 clang-format 的参考信息，您可以通过:
[Configurator](https://zed0.co.uk/clang-format-configurator/)查询

## Known issues

未决问题清单见
[Github](https://github.com/COVESA/dlt-daemon/issues)

- DLT 库: 在 ARM 目标机上使用 dlt\_user\_log\_write\_float64() 和 DLT\_FLOAT64() 会导致 "非法指令（内核已转储）"。
- DLT 库: 不支持对 DLT\_LOG\_ ...的嵌套调用，这将导致死锁。
- 对于非 Linux 平台（如 QNX），支持的 IPC 是 UNIX/_SOCKET。对于 Linux 平台，同时支持 IPC FIFO 和 UNIX\_SOCKET

## Software/Hardware

使用 Ubuntu Linux 16 64 位/英特尔 PC 开发和测试

## License

有关本软件许可证的完整信息，请参阅 "LICENSE "文件。
关于 cityhash 代码许可证的完整信息，请参阅 src/core\_dump\_handler/cityhash\_c 中的 "COPYING "文件。


## Contact
Michael Methner <Michael.Methner@de.bosch.com>; Minh Luu Quang <Minh.LuuQuang@vn.bosch.com>

![alt text](doc/images/covesa-logo.png "COVESA logo")
