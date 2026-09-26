[简体中文](README.md) | **繁體中文** | [English](README.en.md)

# 行動端德州撲克原始碼：私人局、熟人局與俱樂部系統

这是一个面向 iOS、Android 与行動端產品形态的德州撲克原始碼展示项目。线上產品资料描述德州私人局、熟人局/朋友局、俱樂部、联盟、经典德州、奥马哈、短牌、大菠萝、AOF、SNG 与 MTT 等场景；目前公开倉庫可验证的程式碼主要包括 C++/Tars 訊息推送、線上与遊戲狀態、房間上报、俱樂部审核和俱樂部资金变更相关模組。

> 重要：目前公开倉庫不是完整客戶端与商业部署包。iOS、Android、H5、資料库、管理后台、语音视频和完整玩法是否包含，应以实际目錄、授权和交付清单为准。并发量、日活、流水和營運时长需要公开压测或审计材料验证。

## 真实產品截图

| 行動端大厅 | 牌桌界面 | 俱樂部/熟人局入口 |
|---|---|---|
| ![行動端德州撲克大厅原始碼界面](docs/assets/screenshots/mobile-poker-08.jpg) | ![德州撲克行動端多人牌桌](docs/assets/screenshots/mobile-poker-07.jpg) | ![德州俱樂部和熟人局界面](docs/assets/screenshots/mobile-poker-06.jpg) |

| 私人局功能 | 遊戲設定 | 战绩与帳戶页面 |
|---|---|---|
| ![德州私人局朋友局產品界面](docs/assets/screenshots/mobile-poker-05.jpg) | ![移动德州撲克設定页面](docs/assets/screenshots/mobile-poker-04.jpg) | ![德州撲克玩家战绩帳戶界面](docs/assets/screenshots/mobile-poker-03.jpg) |

## 產品功能

- **私人局/熟人局/朋友局**：產品资料描述为固定玩家建立和加入牌桌的社交场景，适用于熟人娱乐和内部活动。
- **俱樂部与联盟**：README 展示俱樂部、代理与联盟方向；公开程式碼包含 `AuditClubRequest`、俱樂部余额及资金变更请求模型。
- **行動端体验**：线上资料面向 iOS、Android 和 H5；倉庫出现 Unity 风格 `.meta`、`link.xml` 与资源目錄，但完整客戶端工程需另行核对。
- **多人实时狀態**：`UserStateProcessor` 处理玩家線上狀態、遊戲狀態、房間地址和统计。
- **訊息推送与广播**：`PushServantImp` 提供訊息推送、广播、線上狀態、批量遊戲狀態和房間使用者上报介面。
- **房間与牌桌上报**：服务介面包含房間使用者、盲注使用者、線上人数、牌桌信息和遊戲地址等字段。
- **設定模組**：倉庫包含道具、奖励与排行榜設定的增删改查头檔案。
- **多玩法產品方向**：资料列出经典德州、奥马哈、短牌、大菠萝、MTT、SNG 和 AOF；目前公开快照不足以逐项验证完整规则实现。

## 私人局与熟人局流程

1. 玩家登录行動端并进入大厅或俱樂部。
2. 房主建立私人桌/朋友局，設定可见的房間参数。
3. 熟人通过俱樂部、邀请或房間入口加入牌桌。
4. 伺服器端记录線上狀態、遊戲地址与房間信息，并向玩家推送狀態。
5. 对局结束后展示结果和战绩；俱樂部资金、审核及权限应由完整授权系統处理。

## 可验证技術模組

| 模組 | 檔案 | 可验证职责 |
|---|---|---|
| 推送服务 | `PushServant.tars`、`PushServantImp.cpp/.h`、`PushServer.cpp` | 单人訊息、广播、狀態和房間信息上报 |
| 使用者狀態 | `UserStateProto.tars`、`UserStateProcessor.cpp/.h` | 線上狀態、遊戲狀態、房間和统计 |
| 俱樂部模型 | `audit_club.h`、`change_club_balance.h`、`change_club_fund.h` | 俱樂部审核、余额和资金变更请求/响应 |
| 遊戲狀態 | `gameconfig.cpp`、`gameparameter.cpp`、`gamebegin.h`、`onready.h` | 房間遊戲初始化与狀態处理样本 |
| 設定介面 | `props_config/`、`props_reward_config/`、`rank_board_config/` | 道具、奖励与排行榜設定模型 |
| 建置 | `makefile`、Tars 介面檔案 | C++ 服务编译和介面定义入口 |

## 图文专题

- [德州撲克原始碼与移动服务](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/texas-holdem-source-code.html)
- [德州私人局原始碼与房間流程](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/private-poker-game.html)
- [德州熟人局、朋友局原始碼](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/friend-poker-game.html)
- [行動端德州俱樂部系統](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/zh-cn/poker-club-mobile.html)
- [English mobile poker source overview](https://masterai-top.github.io/TexasHoldem-Poker-Mobile-Game-Source-Code/en/texas-holdem-mobile-source-code.html)

## 取得与評估

```bash
git clone https://github.com/masterai-top/TexasHoldem-Poker-Mobile-Game-Source-Code.git
cd TexasHoldem-Poker-Mobile-Game-Source-Code
```

建置前需要检查 `makefile` 中的头檔案、库和目标環境，并准备匹配版本的 C++ 与 Tars 依赖。克隆只获得目前公开快照，不代表包含可直接发布的完整移动客戶端、資料库或營運后台。

## 合规与安全

私人局、俱樂部、虚拟道具、付款或类似功能可能受到当地遊戲、付款、隐私和年龄法规限制。部署前应核对许可证、第三方素材、帳戶权限、訊息安全、随机数、牌局日誌、反作弊、付款与当地法律。严禁用于违法活动。

聯絡：Telegram `@xuzongbin001` · Email `ttpoker40@gmail.com` · [GitHub Issues](https://github.com/masterai-top/TexasHoldem-Poker-Mobile-Game-Source-Code/issues)

