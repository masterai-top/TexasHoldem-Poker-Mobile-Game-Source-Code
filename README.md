[简体中文](README.md) | [繁體中文](README.zh-TW.md) | [English](README.en.md)

# 移动端德州扑克源码：私人局、熟人局与俱乐部系统

这是一个面向 iOS、Android 与移动端产品形态的德州扑克源码展示项目。线上产品资料描述德州私人局、熟人局/朋友局、俱乐部、联盟、经典德州、奥马哈、短牌、大菠萝、AOF、SNG 与 MTT 等场景；当前公开仓库可验证的代码主要包括 C++/Tars 消息推送、在线与游戏状态、房间上报、俱乐部审核和俱乐部资金变更相关模块。

> 重要：当前公开仓库不是完整客户端与商业部署包。iOS、Android、H5、数据库、管理后台、语音视频和完整玩法是否包含，应以实际目录、授权和交付清单为准。并发量、日活、流水和运营时长需要公开压测或审计材料验证。

## 真实产品截图

| 移动端大厅 | 牌桌界面 | 俱乐部/熟人局入口 |
|---|---|---|
| ![移动端德州扑克大厅源码界面](docs/assets/screenshots/mobile-poker-08.jpg) | ![德州扑克移动端多人牌桌](docs/assets/screenshots/mobile-poker-07.jpg) | ![德州俱乐部和熟人局界面](docs/assets/screenshots/mobile-poker-06.jpg) |

| 私人局功能 | 游戏设置 | 战绩与账户页面 |
|---|---|---|
| ![德州私人局朋友局产品界面](docs/assets/screenshots/mobile-poker-05.jpg) | ![移动德州扑克设置页面](docs/assets/screenshots/mobile-poker-04.jpg) | ![德州扑克玩家战绩账户界面](docs/assets/screenshots/mobile-poker-03.jpg) |

## 产品功能

- **私人局/熟人局/朋友局**：产品资料描述为固定玩家创建和加入牌桌的社交场景，适用于熟人娱乐和内部活动。
- **俱乐部与联盟**：README 展示俱乐部、代理与联盟方向；公开代码包含 `AuditClubRequest`、俱乐部余额及资金变更请求模型。
- **移动端体验**：线上资料面向 iOS、Android 和 H5；仓库出现 Unity 风格 `.meta`、`link.xml` 与资源目录，但完整客户端工程需另行核对。
- **多人实时状态**：`UserStateProcessor` 处理玩家在线状态、游戏状态、房间地址和统计。
- **消息推送与广播**：`PushServantImp` 提供消息推送、广播、在线状态、批量游戏状态和房间用户上报接口。
- **房间与牌桌上报**：服务接口包含房间用户、盲注用户、在线人数、牌桌信息和游戏地址等字段。
- **配置模块**：仓库包含道具、奖励与排行榜配置的增删改查头文件。
- **多玩法产品方向**：资料列出经典德州、奥马哈、短牌、大菠萝、MTT、SNG 和 AOF；当前公开快照不足以逐项验证完整规则实现。

## 私人局与熟人局流程

1. 玩家登录移动端并进入大厅或俱乐部。
2. 房主创建私人桌/朋友局，设置可见的房间参数。
3. 熟人通过俱乐部、邀请或房间入口加入牌桌。
4. 服务端记录在线状态、游戏地址与房间信息，并向玩家推送状态。
5. 对局结束后展示结果和战绩；俱乐部资金、审核及权限应由完整授权系统处理。

## 可验证技术模块

| 模块 | 文件 | 可验证职责 |
|---|---|---|
| 推送服务 | `PushServant.tars`、`PushServantImp.cpp/.h`、`PushServer.cpp` | 单人消息、广播、状态和房间信息上报 |
| 用户状态 | `UserStateProto.tars`、`UserStateProcessor.cpp/.h` | 在线状态、游戏状态、房间和统计 |
| 俱乐部模型 | `audit_club.h`、`change_club_balance.h`、`change_club_fund.h` | 俱乐部审核、余额和资金变更请求/响应 |
| 游戏状态 | `gameconfig.cpp`、`gameparameter.cpp`、`gamebegin.h`、`onready.h` | 房间游戏初始化与状态处理样本 |
| 配置接口 | `props_config/`、`props_reward_config/`、`rank_board_config/` | 道具、奖励与排行榜配置模型 |
| 构建 | `makefile`、Tars 接口文件 | C++ 服务编译和接口定义入口 |

## 图文专题

- [德州扑克源码与移动服务](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/texas-holdem-source-code.html)
- [德州私人局源码与房间流程](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/private-poker-game.html)
- [德州熟人局、朋友局源码](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/friend-poker-game.html)
- [移动端德州俱乐部系统](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/poker-club-mobile.html)
- [English mobile poker source overview](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/en/texas-holdem-mobile-source-code.html)

## 获取与评估

```bash
git clone https://github.com/masterai-top/TexasHoldem-Poker-Mobile-Game-Source-Code.git
cd TexasHoldem-Poker-Mobile-Game-Source-Code
```

构建前需要检查 `makefile` 中的头文件、库和目标环境，并准备匹配版本的 C++ 与 Tars 依赖。克隆只获得当前公开快照，不代表包含可直接发布的完整移动客户端、数据库或运营后台。

## 合规与安全

私人局、俱乐部、虚拟道具、支付或类似功能可能受到当地游戏、支付、隐私和年龄法规限制。部署前应核对许可证、第三方素材、账户权限、消息安全、随机数、牌局日志、反作弊、支付与当地法律。严禁用于违法活动。

联系：Telegram `@xuzongbin001` · Email `ttpoker40@gmail.com` · [GitHub Issues](https://github.com/masterai-top/TexasHoldem-Poker-Mobile-Game-Source-Code/issues)

