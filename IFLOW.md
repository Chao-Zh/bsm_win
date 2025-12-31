# BSM_WIN 收费管理系统 - iFlow 上下文文档

## 项目概述

**BSM_WIN** 是一个基于C++开发的收费管理系统，主要用于网吧、机房等场所的计算机使用计费管理。项目采用传统的C语言风格编写，包含完整的卡管理、计费、充值、消费统计等功能。

### 项目类型
- **语言**: C/C++
- **架构**: 控制台应用程序
- **数据存储**: 二进制文件存储（.ams格式）
- **平台**: 跨平台（支持Linux和Windows，包含完整的平台兼容性解决方案）

## 目录结构

```
bsm_win/
├── include/           # 头文件目录
│   ├── billing_file.h     # 计费文件操作
│   ├── billing_service.h  # 计费服务
│   ├── card_file.h        # 卡文件操作
│   ├── card_service.h     # 卡服务
│   ├── global.h           # 全局定义
│   ├── menu.h             # 菜单界面
│   ├── model.h            # 数据结构定义
│   ├── money_file.h       # 资金文件操作
│   ├── platform_compat.h  # 平台兼容性头文件
│   ├── service.h          # 核心服务接口
│   └── tool.h             # 工具函数
├── src/               # 源文件目录
│   ├── billing_file.cpp     # 计费文件实现
│   ├── billing_service.cpp  # 计费服务实现
│   ├── card_file.cpp        # 卡文件实现
│   ├── card_service.cpp     # 卡服务实现
│   ├── main.cpp             # 程序入口
│   ├── menu.cpp             # 菜单实现
│   ├── money_file.cpp       # 资金文件实现
│   ├── service.cpp          # 服务实现
│   └── tool.cpp             # 工具函数实现
└── data/             # 数据文件目录
    ├── billing.ams   # 计费记录数据
    ├── card.ams      # 卡信息数据
    └── money.ams     # 资金流水数据
```

## 核心功能模块

### 1. 卡管理
- **添加卡**: 创建新的用户卡
- **查询卡**: 根据卡号查询卡信息
- **注销卡**: 停用用户卡
- **卡统计**: 统计可用卡数量

### 2. 上机/下机管理
- **上机操作**: 用户登录使用计算机
- **下机操作**: 用户结束使用并结算费用
- **自动计费**: 根据使用时间计算费用

### 3. 资金管理
- **充值**: 为用户卡增加余额
- **消费**: 从用户卡扣除费用
- **退费**: 退还用户余额

### 4. 统计报表
- **消费记录查询**: 查看历史消费记录
- **总营业额统计**: 统计系统总收入
- **月度营业额统计**: 按月统计收入

## 数据结构

### 主要结构体定义（model.h）
- **Card**: 卡信息结构（卡号、密码、状态、余额等）
- **Billing**: 消费记录结构（上机时间、下机时间、消费金额等）
- **LogonInfo**: 上机信息结构
- **SettleInfo**: 下机信息结构
- **Money**: 资金流水结构（充值/退费记录）

## 平台兼容性

### platform_compat.h
项目提供了完整的平台兼容性头文件 `platform_compat.h`，用于解决Windows和Linux之间的兼容性问题：

1. **清屏命令统一**:
   - Windows: `CLEAR_SCREEN` 宏定义为 `"cls"`
   - Linux: `CLEAR_SCREEN` 宏定义为 `"clear"`

2. **时间函数包装**:
   - 提供了 `safe_localtime_r()` 函数，统一Windows的 `localtime_s` 和Linux的 `localtime_r`
   - 函数原型: `inline struct tm* safe_localtime_r(const time_t* timer, struct tm* result)`

3. **类型定义**:
   - 为Windows平台定义了 `__int64_t` 类型

### 当前使用状态
- **已迁移到新方案的文件**:
  - `main.cpp`: 使用 `CLEAR_SCREEN` 宏进行清屏
  - `billing_file.cpp`: 包含 platform_compat.h
  - `card_file.cpp`: 包含 platform_compat.h
  - `menu.cpp`: 包含 platform_compat.h，正确使用 `localtime()` 和 `safe_localtime_r()`
  - `tool.cpp`: 包含 platform_compat.h，使用 `safe_localtime_r`

- **未包含 platform_compat.h 的文件**:
  - `billing_service.cpp`: 使用 `time(NULL)` 但未使用 localtime 相关函数
  - `card_service.cpp`: 未使用时间相关函数
  - `money_file.cpp`: 未使用时间相关函数
  - `service.cpp`: 使用 `time(NULL)` 但未使用 localtime 相关函数

## 构建和运行

### 编译方法
由于项目没有提供构建配置文件，需要手动编译：

#### Windows (使用MinGW或Visual Studio)
```bash
# 使用g++编译
g++ -o bsm_win src/*.cpp -Iinclude

# 或者逐个编译
g++ -c src/*.cpp -Iinclude
g++ *.o -o bsm_win
```

#### Linux
```bash
# 使用g++编译
g++ -o bsm_win src/*.cpp -Iinclude

# 注意：项目已包含完整的平台兼容性解决方案
# 可以使用统一的 CLEAR_SCREEN 宏和 safe_localtime_r 函数
```

### 运行程序
```bash
./bsm_win  # Linux
bsm_win.exe  # Windows
```

## 开发约定

### 代码风格
1. **命名约定**:
   - 函数名: 小写字母，使用动词开头（如 `addCardInfo`, `queryCardInfo`）
   - 变量名: 小写字母，描述性名称（如 `choice`, `pName`）
   - 结构体: 首字母大写（如 `Card`, `Billing`）
   - 指针变量: 前缀 `p`（如 `pCard`, `pInfo`）

2. **文件组织**:
   - 头文件使用 `#pragma once` 防止重复包含
   - 源文件与头文件一一对应
   - 公共接口在头文件中声明，实现在对应的源文件中

3. **错误处理**:
   - 使用返回值表示操作状态（0表示成功，非0表示失败）
   - 输入验证在用户界面层进行

### 数据存储
- 使用二进制文件（.ams格式）存储数据
- 数据文件位于 `data/` 目录
- 文件操作通过对应的 `*_file.cpp` 模块处理

## 已知问题与注意事项

1. **平台兼容性**:
   - 项目已添加 `platform_compat.h` 解决平台兼容性问题
   - `main.cpp` 迁移到新的平台兼容性方案，使用 `CLEAR_SCREEN` 宏
   - 大部分源文件已包含 platform_compat.h

2. **输入验证**:
   - 菜单选择有基本的输入验证
   - 但某些功能可能缺少完整的输入验证

3. **内存管理**:
   - 使用链表存储数据，需要正确释放内存
   - `releaseList()` 函数用于释放链表内存

## 快速开始

1. **编译项目**:
   ```bash
   g++ -o bsm_win src/*.cpp -Iinclude
   ```

2. **运行程序**:
   ```bash
   ./bsm_win  # 或 bsm_win.exe
   ```

3. **使用系统**:
   - 按照菜单提示操作
   - 主要功能包括：添加卡、查询卡、上机、下机、充值、消费、统计等

---

*本文档最后更新: 2025-12-31*
*项目状态: 功能完整，包含完整平台兼容性解决方案的控制台应用程序*
