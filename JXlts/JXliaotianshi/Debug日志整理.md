# JXliaotianshi 项目全部 Debug 日志整理

> **项目路径**: `d:\develop\linux\public\YQ_VScode\JieDuan_3\project\project3jxlts\JXliaotianshi`
> **日志前缀说明**: `[模块名]` 表示日志所属模块，便于筛选

---

## 一、main.cpp (4条)

### 1. 函数 `main()` | 行号: 115-116

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 115 | `"程序启动"` | 程序启动时 |
| 116 | `"Qt版本:" << QT_VERSION_STR` | 程序启动时 |

### 2. 函数 `updateUserOfflineStatus()` | 行号: 31-33

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 31 | `"用户" << curUserInfo.username << "已下线"` (成功前缀) | 退出时更新数据库成功 |
| 33 | `updateQuery.lastError().text()` (失败前缀) | 退出时更新数据库失败 |

---

## 二、mainwindow.cpp (31条)

### 1. 函数 `eventFilter()` | 行号: 43-94

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 43 | `"[MainWindow] 密码框回车，选中注册按钮，触发注册"` | 密码框回车 + 注册按钮高亮 |
| 47 | `"[MainWindow] 密码框回车，选中登录按钮，触发登录"` | 密码框回车 + 登录按钮高亮 |
| 51 | `"[MainWindow] 密码框回车，没有选中按钮，默认登录"` | 密码框回车 + 无按钮高亮 |
| 57 | `"[MainWindow] 用户名输入框回车，切换到密码框"` | 用户名框回车 |
| 66 | `"[MainWindow] 密码框为空，按退格，切换到用户名框"` | 密码框为空 + 退格键 |
| 73 | `"[MainWindow] 按下上键，移动到用户名框"` | 按↑键 |
| 80 | `"[MainWindow] 按下下键，移动到密码框"` | 按↓键 |
| 87 | `"[MainWindow] 按下左键，选中注册按钮"` | 按←键 |
| 94 | `"[MainWindow] 按下右键，选中登录按钮"` | 按→键 |

### 2. 函数 `SQLite_init()` | 行号: 124-227

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 124 | `">>> 数据库连接失败"` | `DB.open()` 返回 false |
| 127 | `">>> 数据库连接成功"` | `DB.open()` 返回 true |
| 156 | `">>> userinfo 表已存在，无需创建。"` | 表已存在 |
| 160 | `">>> userinfo 表刚刚创建成功！"` | 表刚被创建 |
| 165 | `">>> 控制台错误：创建表失败！" << lastError` | CREATE TABLE 失败 |
| 178 | `">>> 检测到表中无数据，正在插入默认管理员账号..."` | 表为空 |
| 192 | `">>> 默认数据插入成功！(ID:1, admin)"` | 插入默认用户成功 |
| 196 | `">>> 默认数据插入失败：" << lastError` | 插入默认用户失败 |
| 201 | `">>> 表中已有" << recordCount << "条数据"` | 表非空 |
| 205 | `">>> ID \t USERNAME \t PASSWORD \t NICKNAME \t IP"` | 表头 (打印所有记录前) |
| 219 | `id << "\t" << user << "\t" << pwd << "\t" << name << "\t" << ip` | 逐行打印所有用户记录 |
| 227 | `sql` | SQLite_query 被调用时 (该函数当前未被调用) |

### 3. 函数 `on_userlogin_clicked()` | 行号: 259-326

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 259 | `">>> 数据库查询失败：" << lastError` | SELECT 查询失败 |
| 280 | `">>> 用户" << inputUsername << "已在线，提示确认"` | 用户已在线 (status=1) |
| 291 | `">>> 用户取消登录"` | 用户点"否"取消强制登录 |
| 294 | `">>> 用户确认登录，继续"` | 用户点"是"确认强制登录 |
| 319 | `">>> 数据库状态更新成功：用户" << curUserInfo.username << "已上线"` | 更新 status=1 成功 |
| 323 | `">>> 用户状态更新失败！" << lastError` | 更新 status=1 失败 |
| 326 | `">>> 登录成功！欢迎用户：" << curUserInfo.nicheng` | 登录成功，跳转前 |

### 4. 函数 `on_userregister_clicked()` | 行号: 382-397

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 382 | `">>> 新用户注册成功，ID:" << newUserId` | 注册成功 |
| 393 | `">>> 已为新用户创建QMediaPlayer表:" << tableName` | 媒体表创建成功 |
| 397 | `">>> 创建QMediaPlayer表失败:" << lastError` | 媒体表创建失败 |

---

## 三、userhome.cpp (100条)

### 1. 函数 `UserHome::UserHome()` 构造函数 | 行号: 26-98

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 26 | `"[定时器] 错误：数据库未打开"` | 定时器触发时数据库未打开 |
| 52 | `"[UserHome] TCP服务器启动成功，系统分配的监听端口:" << actualPort` | TCP服务器启动成功 |
| 57 | `"[UserHome] 准备更新自己的IP和端口到数据库:" << ipWithPort` | 更新IP前 |
| 66 | `"[UserHome] 数据库更新成功：自己的IP和端口已更新为" << ipWithPort` | 更新成功 |
| 71 | `"[UserHome] 数据库更新失败：" << lastError` | 更新失败 |
| 76 | `"[UserHome] TCP服务器启动失败:" << errorString` | TCP服务器启动失败 |
| 98 | `"[UserHome] 尝试连接在线用户:" << userId` | 遍历在线用户并尝试连接 |

### 2. 函数 `UserHome::closeEvent()` | 行号: 118

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 118 | `"[UserHome关闭] 正在关闭主窗口，用户ID:" << curUserInfo.id` | 窗口关闭事件触发 |

### 3. 函数 `UserHome::updateUserOfflineStatus()` (UserHome内同名函数) | 行号: 145-192

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 145 | `"[UserHome关闭] 更新用户状态为离线..."` | 开始更新状态 |
| 152 | `"[数据库] 用户状态已更新为离线"` | 更新成功 (路径1) |
| 157 | `"[数据库] 更新用户状态失败：" << lastError` | 更新失败 (路径1) |
| 177 | `"[数据库] 用户状态已更新为离线"` | 更新成功 (路径2) |
| 182 | `"[数据库] 更新用户状态失败：" << lastError` | 更新失败 (路径2) |
| 192 | `"[程序退出] 当前状态已为离线"` | 状态已是0，无需更新 |

### 4. 函数 `UserHome::onListClicked()` | 行号: 202-256

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 202 | `"执行onListClicked"` | 用户列表被点击 |
| 205 | `"获取userId"` | 获取选中行的userId |
| 226 | `"获取nickName，用户在线状态:" << isUserOnline << "是否是群聊:" << isGroupChat` | 获取昵称和状态后 |
| 250 | `"点击了第" << index.row() << "行，用户ID:" << userId << "昵称:" << nickName` | 创建/显示聊天窗口前 |
| 256 | `"[UserHome] 聊天窗口已关闭，用户ID:" << userId` | 检测到窗口已关闭并清理 |

### 5. 函数 `UserHome::onCheckStatusTimeout()` | 行号: 267-320

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 267 | `"数据库重连失败:" << lastError` | `db.open()` 重连失败 |
| 308 | `"[状态检测] 新用户，首次记录状态"` | 首次检测到某用户 (不在m_lastUserStatus中) |
| 320 | `"查询错误:" << model->lastError().text()` | model->setQuery 失败 |

### 6. 函数 `UserHome::showUserOnlineNotification()` | 行号: 337-359

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 337 | `"[提示窗口] 准备显示用户上线提示，昵称:" << nickName` | 开始创建提示窗口 |
| 349 | `"[提示窗口] 窗口位置:" << pos` | 计算窗口位置后 |
| 353 | `"[提示窗口] 提示窗口已显示"` | 窗口show()后 |
| 356 | `"[提示窗口] 2秒时间到，关闭提示窗口，昵称:" << nickName` | 定时器2秒后 |
| 359 | `"[提示窗口] 窗口已关闭"` | 窗口关闭后 |

### 7. 函数 `UserHome::showNewMessageNotification()` | 行号: 365-394

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 365 | `"[提示窗口] 准备显示新消息提示，昵称:" << nickName << "内容:" << content` | 开始创建提示窗口 |
| 384 | `"[提示窗口] 窗口位置:" << pos` | 计算窗口位置后 |
| 388 | `"[提示窗口] 新消息提示窗口已显示"` | 窗口show()后 |
| 391 | `"[提示窗口] 3秒时间到，关闭新消息提示窗口，昵称:" << nickName` | 定时器3秒后 |
| 394 | `"[提示窗口] 新消息提示窗口已关闭"` | 窗口关闭后 |

### 8. 函数 `UserHome::onStatusSwitch()` | 行号: 435-456

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 435 | `"[UserHome] 状态切换:" << statusText` | 状态切换按钮点击时 |
| 444 | `"[UserHome] 状态更新为在线"` | 切换到在线成功 |
| 446 | `"[UserHome] 状态更新失败:" << lastError` | 切换到在线失败 |
| 454 | `"[UserHome] 状态更新为隐身"` | 切换到隐身成功 |
| 456 | `"[UserHome] 状态更新失败:" << lastError` | 切换到隐身失败 |

### 9. 函数 `UserHome::onNameChanged()` | 行号: 478-482

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 478 | `"[UserHome] 用户昵称更新成功：" << newName` | 昵称更新成功 |
| 482 | `"[UserHome] 用户昵称更新失败：" << lastError` | 昵称更新失败 |

### 10. 函数 `UserHome::onNewConnection()` | 行号: 490-511

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 490 | `"[UserHome] 收到新的连接请求"` | TCP服务器收到新连接 |
| 499 | `"[UserHome] === 新连接信息 ==="` | 打印新连接信息头 |
| 500 | `"[UserHome] Socket描述符:" << socketDescriptor` | 新连接的socket描述符 |
| 501 | `"[UserHome] 对端地址:" << peerAddress` | 对端IP地址 |
| 502 | `"[UserHome] 对端端口:" << peerPort` | 对端端口号 |
| 503 | `"[UserHome] ==================="` | 新连接信息尾 |
| 511 | `"[UserHome] 分配临时ID:" << tempId` | 分配临时ID (>=10000) |

### 11. 函数 `UserHome::setupSocketSignals()` | 行号: 534

> 该函数只绑定信号, 无实际 debug 输出, 但被 onNewConnection 和 registerSocket 调用。

### 12. 函数 `UserHome::onSocketReadyRead()` | 行号: 534-729

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 534 | `"[UserHome] ========== 收到新数据 =========="` | socket触发readyRead |
| 535 | `"[UserHome] 读取到" << newData.size() << "字节新数据"` | readAll()后 |
| 536 | `"[UserHome] Socket描述符:" << socketDescriptor` | socket描述符 |
| 537 | `"[UserHome] 当前Socket ID:" << m_activeSockets.key(socket, 0)` | 当前绑定的用户ID |
| 538 | `"[UserHome] Socket状态:" << socket->state()` | socket连接状态 |
| 543 | `"[UserHome] 缓冲区总大小:" << buffer.size() << "字节"` | 追加数据后缓冲区大小 |
| 549 | `"[UserHome] 缓冲区数据不足，等待更多数据:" << buffer.size() << "< 4"` | 不足4字节长度头 |
| 558 | `"[UserHome] 解析到消息长度头:" << blockSize << "字节"` | 成功读取消息长度 |
| 562 | `"[UserHome] 消息不完整，等待更多数据:" << buffer.size() << "<" << (4+blockSize)` | 消息体不完整 |
| 575 | `"[UserHome] 成功提取完整JSON消息:" << jsonMessage` | 成功提取JSON |
| 576 | `"[UserHome] 缓冲区剩余大小:" << buffer.size() << "字节"` | 移除已处理数据后 |
| 590 | `"[UserHome] JSON解析成功 - 发送者ID:" << senderId << "目标ID:" << targetId` | JSON解析成功 |
| 605 | `"[UserHome] Socket当前绑定ID:" << socketId` | 查找socket对应的ID |
| 611 | `"[UserHome] 用户" << senderId << "已存在连接，关闭新连接避免重复"` | 检测到重复连接 |
| 618 | `"[UserHome] 更新临时ID" << socketId << "为真实ID" << senderId` | 临时ID→真实ID |
| 622 | `"[UserHome] ID更新完成，新ID:" << socketId` | ID更新完成 |
| 627 | `"[UserHome] 最终发送者ID:" << socketId` | 最终确定的发送者ID |
| 628 | `"[UserHome] 当前m_activeSockets中的用户ID:" << m_activeSockets.keys()` | 当前所有已连接用户 |
| 649 | `"[UserHome] 收到握手消息，不显示在聊天界面"` | type=HANDSHAKE |
| 653 | `"[UserHome] 收到文件头，文件名:" << content` | type=1 文件头 |
| 697 | `"[UserHome] 文件创建失败:" << savePath` | 创建文件失败 |
| 709 | `"[UserHome] 准备接收文件，保存路径:" << savePath` | 文件接收初始化完成 |
| 716 | `"[UserHome] 收到文件数据块"` | type=2 文件数据 |
| 723 | `"[UserHome] Base64解码失败或数据为空"` | Base64解码失败 |
| 729 | `"[UserHome] 文件写入失败，期望:" << data.size() << "实际:" << bytesWritten` | 写入字节不匹配 |

### 13. 函数 `UserHome::onSocketReadyRead()` (续: 文件接收完成) | 行号: 743-868

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 743 | `"[UserHome] 文件接收完成:" << fileName << "大小:" << fileSize` | 文件接收完毕 |
| 758 | `"[UserHome] 文件是媒体文件，移动至Media目录"` | 检测到媒体扩展名 |
| 775 | `"[UserHome] 移动媒体文件失败:" << lastError` | QFile::rename 失败 |
| 787 | `"[UserHome] 媒体文件已记录到数据库，相对路径:" << relativePath` | 数据库插入成功 |
| 793 | `"[UserHome] 记录媒体文件到数据库失败:" << lastError` | 数据库插入失败 |
| 800 | `"[UserHome] 发送文件接收成功通知:" << fileName` | 发送成功通知消息 |
| 814 | `"[UserHome] 接收方缓存中已有" << cachedMessages.size() << "条消息"` | 获取缓存消息 |
| 825 | `"[UserHome] 已通知接收方文件接收成功"` | 文件接收处理完成 |
| 828 | `"[UserHome] ========== 收到群消息 =========="` | type=10 群消息 |
| 834 | `"[UserHome] 群消息已保存到日志文件"` | 保存到群聊日志文件 |
| 837 | `"[UserHome] 群消息已显示到UI，不存入私聊缓存"` | 发射信号后 |
| 843 | `"[UserHome] 收到普通文本消息，内容:" << message` | type=其他 文本消息 |
| 850 | `"[UserHome] 消息已存入缓存"` | addMessageToCache 后 |
| 860 | `"[UserHome] 已发送新消息通知"` | showNewMessageNotification 后 |

### 14. 函数 `UserHome::onSocketDisconnected()` | 行号: 868-880

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 868 | `"[UserHome] ========== 连接已断开 =========="` | socket触发disconnected |
| 869 | `"[UserHome] Socket描述符:" << socketDescriptor` | socket描述符 |
| 870 | `"[UserHome] 当前Socket ID:" << m_activeSockets.key(socket, 0)` | 当前绑定的用户ID |
| 871 | `"[UserHome] 当前m_activeSockets中的用户ID:" << m_activeSockets.keys()` | 断开前所有连接用户 |

### 15. 函数 `UserHome::onSocketError()` | 行号: 878-880

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 878 | `"[UserHome] ========== Socket错误 =========="` | socket触发error |
| 879 | `"[UserHome] 错误类型:" << error` | 错误类型枚举值 |
| 880 | `"[UserHome] 错误信息:" << socket->errorString()` | 错误描述文本 |

### 16. 函数 `UserHome::onSocketBytesWritten()` | 行号: 1000-1056

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1001 | `"[UserHome] bytesWritten触发，当前状态:" << bytesSent << "/" << fileSize` | bytesWritten信号触发 |
| 1005 | `"[UserHome] 文件发送已被取消，停止发送"` | state.cancelled == true |
| 1021 | `"[UserHome] 文件已发送完毕:" << state.fileName` | bytesSent >= fileSize |
| 1031 | `"[UserHome] 文件已读完，发送完毕:" << state.fileName` | read()返回空(文件读完) |
| 1045 | `"[UserHome] 发送下一个数据块，已发送:" << bytesSent << "/" << fileSize` | 继续发送数据块 |
| 1056 | `"[UserHome] 发送数据块失败，期望:" << data.size() << "实际:" << bytesWritten` | write()返回0 |

### 17. 函数 `UserHome::sendMessageToUser()` | 行号: 1101-1148

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1105 | `"[UserHome] 当前m_activeSockets中的用户ID:" << m_activeSockets.keys()` | 发送前检查连接 |
| 1109 | `"[UserHome] 未找到用户" << userId << "的连接！"` | userId不在m_activeSockets |
| 1117 | `"[UserHome] 用户" << userId << "的Socket未连接！当前状态:" << state` | socket未处于ConnectedState |
| 1132 | `"[UserHome] 准备发送的JSON:" << jsonString` | 发送前打印JSON内容 |
| 1143 | `"[UserHome] 实际写入字节数:" << bytesWritten << "总字节数:" << block.size()` | write()返回值 |
| 1146 | `"[UserHome] 已调用flush()"` | flush()调用后 |
| 1148 | `"[UserHome] 消息已发送给用户" << userId` | 发送完成 |

### 18. 函数 `UserHome::sendFileToUser()` | 行号: 1154-1261

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1154 | `"[UserHome] ========== 发送文件 =========="` | 开始文件发送 |
| 1155 | `"[UserHome] 尝试发送文件到用户ID:" << userId << "文件路径:" << filePath` | 函数入口 |
| 1159 | `"[UserHome] 未找到用户" << userId << "的连接！"` | userId不在m_activeSockets |
| 1167 | `"[UserHome] 文件不存在:" << filePath` | QFileInfo::exists() == false |
| 1175 | `"[UserHome] 用户" << userId << "的Socket未连接！"` | socket未连接 |
| 1195 | `"[UserHome] 准备发送文件头:" << jsonString` | 发送文件头前 |
| 1206 | `"[UserHome] 文件头发送字节数:" << bytesWritten` | 文件头write()返回值 |
| 1211 | `"[UserHome] 文件打开失败:" << filePath` | file->open()失败 |
| 1228 | `"[UserHome] 文件头已发送，准备发送数据，文件大小:" << fileSize` | 文件头发送完成 |
| 1261 | `"[UserHome] 发送第一个数据块，已发送:" << bytesSent << "/" << fileSize` | 发送第一个数据块 |

### 19. 函数 `UserHome::cancelFileSend()` | 行号: 1289

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1289 | `"[UserHome] 取消文件发送，用户ID:" << targetUserId << "文件名:" << state.fileName` | 取消文件发送 |

### 20. 函数 `UserHome::registerSocket()` | 行号: 1334

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1334 | `"[UserHome] 注册Socket，用户ID:" << userId` | 注册socket到m_activeSockets |

### 21. 函数 `UserHome::connectToUser()` | 行号: 1348-1401

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1348 | `"[UserHome] 等待对方主动连接，避免重复连接，用户ID:" << userId` | 自己ID >= 对方ID |
| 1355 | `"[UserHome] 数据库未打开，无法获取用户信息"` | QSqlDatabase未打开 |
| 1365 | `"[UserHome] 无法获取用户" << userId << "的信息"` | SELECT 查询失败或无结果 |
| 1372 | `"[UserHome] 用户" << userId << "是群聊(nicheng=" << nicheng << ")，不需要TCP连接"` | username为空(群聊) |
| 1379 | `"[UserHome] 用户" << userId << "IP为空，无法连接"` | IP字段为空 |
| 1396 | `"[UserHome] 准备连接到用户" << userId << "，地址:" << targetIp << ":" << targetPort` | 调用connectToHost前 |
| 1401 | `"[UserHome] 连接到用户" << userId << "成功"` | connected信号触发(槽内) |

### 22. 函数 `UserHome::onSocketDisconnected()` (connected回调内) | 行号: 1431

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1431 | `"[UserHome] 与用户" << userId << "的连接已断开"` | connected回调内的disconnected处理 |

### 23. 函数 `UserHome::onSocketError()` (connectToUser内) | 行号: 1439

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1439 | `"[UserHome] 连接用户" << userId << "失败:" << error << errorString` | socket error信号触发 |

### 24. 函数 `UserHome::loadMyPort()` | 行号: 1453-1456

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1453 | `"[UserHome] 从数据库加载端口:" << port` | 从ip字段解析到端口 |
| 1456 | `"[UserHome] 使用默认端口:8888"` | ip字段无端口信息 |

### 25. 函数 `UserHome::getLocalIpAddress()` | 行号: 1480

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1480 | `"[UserHome] 获取本机IP地址:" << localIp` | 获取到本机IPv4后 |

### 26. 函数 `UserHome::updateMyIpAndPort()` | 行号: 1490-1504

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1490 | `"[UserHome] 准备更新自己的IP和端口到数据库:" << ipWithPort` | 更新前 |
| 1499 | `"[UserHome] 数据库更新成功：自己的IP和端口已更新为" << ipWithPort` | 更新成功 |
| 1504 | `"[UserHome] 数据库更新失败：" << lastError` | 更新失败 |

### 27. 函数 `UserHome::saveMessageToFile()` | 行号: 1558-1562

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1558 | `"[UserHome] 消息已追加到文件:" << fileName` | 文件写入成功 |
| 1562 | `"[UserHome] 无法打开文件写入:" << fileName << "错误:" << errorString` | 文件打开失败 |

### 28. 函数 `UserHome::loadMessagesFromFile()` | 行号: 1589-1609

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1589 | `"[UserHome] 聊天记录文件不存在:" << fileName` | QFile::exists() == false |
| 1605 | `"[UserHome] 已从文件加载" << messages.size() << "条消息:" << fileName` | 加载成功 |
| 1609 | `"[UserHome] 无法打开文件读取:" << fileName << "错误:" << errorString` | 文件打开失败 |

### 29. 函数 `UserHome::ensureChatDirectory()` | 行号: 1621

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1621 | `"[UserHome] 聊天记录目录已创建"` | chat_logs 目录创建成功 |

### 30. 函数 `UserHome::sendGroupMessage()` | 行号: 1710-1776

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1710 | `"[UserHome] ========== 发送群消息 =========="` | 开始群消息广播 |
| 1711 | `"[UserHome] 群ID:" << groupId << "内容:" << message` | 函数入口 |
| 1716 | `"[UserHome] 数据库未打开，无法发送群消息"` | 数据库未打开 |
| 1727 | `"[UserHome] 查询在线用户失败:" << lastError` | SELECT 查询失败 |
| 1742 | `"[UserHome] 在线成员:" << onlineMembers` | 查询到在线成员列表 |
| 1771 | `"[UserHome] 群消息已发送给成员:" << memberId` | 消息发送给某成员成功 |
| 1776 | `"[UserHome] 群消息广播完成，共发送给" << onlineMembers.size() << "个成员"` | 广播完成 |

### 31. 函数 `UserHome::initGroupChatFile()` | 行号: 1788-1801

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1788 | `"[UserHome] 群聊日志文件已存在，清空内容:" << filePath` | 文件已存在 |
| 1792 | `"[UserHome] 群聊日志文件已清空"` | 清空成功 |
| 1797 | `"[UserHome] 群聊日志文件不存在，创建新文件:" << filePath` | 文件不存在 |
| 1801 | `"[UserHome] 群聊日志文件已创建"` | 创建成功 |

### 32. 函数 `UserHome::saveGroupMessageToFile()` | 行号: 1820

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1820 | `"[UserHome] 保存群消息到文件失败:" << filePath` | 文件打开失败 |

### 33. 函数 `UserHome::loadGroupMessagesFromFile()` | 行号: 1833-1852

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1833 | `"[UserHome] 群聊日志文件不存在:" << filePath` | 文件不存在 |
| 1852 | `"[UserHome] 读取群聊日志文件失败:" << filePath` | 文件打开失败 |

### 34. 函数 `UserHome::cleanupGroupChatFile()` | 行号: 1868-1877

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 1868 | `"[UserHome] 群聊日志文件已删除:" << filePath` | 删除成功 |
| 1872 | `"[UserHome] 删除群聊日志文件失败:" << filePath` | 删除失败 |
| 1877 | `"[UserHome] 群聊日志文件不存在，无需删除:" << filePath` | 文件不存在 |

---

## 四、liaotianwin.cpp (33条)

### 1. 函数 `liaotianWin::liaotianWin()` 构造函数 | 行号: 65-116

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 65 | `"[liaotianWin]" << (群聊?"群聊":"私聊") << ":" << targetName << "，ID:" << targetId` | 窗口创建时 |
| 91 | `"[liaotianWin] 加载缓存消息，数量:" << cachedMessages.size()` | 有缓存消息时 |
| 111 | `"[liaotianWin] UserHome已经连接了，直接设置为已连接"` | isUserConnected 返回true |
| 116 | `"[liaotianWin] 等待UserHome建立连接"` | isUserConnected 返回false |

### 2. 函数 `liaotianWin::onMessageReceived()` | 行号: 143

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 143 | `"[liaotianWin] 收到消息:" << message` | 收到私聊消息 |

### 3. 函数 `liaotianWin::onGroupMessageReceived()` | 行号: 157

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 157 | `"[liaotianWin] 收到群消息 - 群:" << groupId << "发送者:" << senderName << "消息:" << message` | 收到群消息 |

### 4. 函数 `liaotianWin::onUserConnected()` | 行号: 178

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 178 | `"[liaotianWin] 用户" << userId << "连接成功"` | 对方连接成功 |

### 5. 函数 `liaotianWin::onUserDisconnected()` | 行号: 198

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 198 | `"[liaotianWin] 连接已断开"` | 对方断开连接 |

### 6. 函数 `liaotianWin::updateSendButtonsEnabled()` | 行号: 206

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 206 | `"[liaotianWin] 更新发送按钮状态:" << (启用?"启用":"禁用")` | 按钮状态变化时 |

### 7. 函数 `liaotianWin::onSendResult()` | 行号: 221-228

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 221 | `"[liaotianWin] 消息发送成功"` | 发送成功 |
| 228 | `"[liaotianWin] 消息发送失败:" << errorMsg` | 发送失败 |

### 8. 函数 `liaotianWin::onSendButtonClicked()` | 行号: 258-267

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 258 | `"[liaotianWin] 通过UserHome发送群消息:" << message` | 群聊模式发送消息 |
| 267 | `"[liaotianWin] 通过UserHome发送消息:" << message` | 私聊模式发送消息 |

### 9. 函数 `liaotianWin::onCancelButtonClicked()` | 行号: 276

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 276 | `"[liaotianWin] 点击取消，停止文件发送"` | 进度条可见时点取消 |

### 10. 函数 `liaotianWin::initMediaPlayerTable()` | 行号: 478-497

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 478 | `"[liaotianWin] 群聊模式，跳过媒体播放器表初始化"` | 群聊模式 (m_isGroup=true) |
| 493 | `"[liaotianWin] 媒体播放器表创建成功或已存在:" << tableName` | 表创建/已存在 |
| 497 | `"[liaotianWin] 创建媒体播放器表失败:" << lastError` | 表创建失败 |

### 11. 函数 `liaotianWin::loadMediaPlayerData()` | 行号: 534-538

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 534 | `"[liaotianWin] 加载媒体播放器数据失败:" << lastError` | model->lastError有效 |
| 538 | `"[liaotianWin] 媒体播放器数据加载成功:" << tableName` | 加载成功 |

### 12. 函数 `liaotianWin::refreshMediaPlayer()` | 行号: 547

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 547 | `"[liaotianWin] 媒体播放器数据已刷新"` | refreshMediaPlayer被调用 |

### 13. 函数 `liaotianWin::onMediaPlayerClicked()` | 行号: 568-604

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 568 | `"[liaotianWin] 当前路径:" << QDir::currentPath()` | 单击媒体文件 |
| 569 | `"[liaotianWin] 数据库路径:" << filePath` | 数据库中的路径 |
| 570 | `"[liaotianWin] 完整路径:" << fullPath` | 拼接后的完整路径 |
| 571 | `"[liaotianWin] 文件存在:" << QFile::exists(fullPath)` | 文件存在性检查 |
| 575 | `"[liaotianWin] 文件不存在!"` | 文件不存在 |
| 584 | `"[liaotianWin] 暂停播放"` | 暂停当前播放 |
| 589 | `"[liaotianWin] 继续播放"` | 继续播放 |
| 604 | `"[liaotianWin] 开始播放:" << fullPath` | 开始播放新文件 |

### 14. 函数 `liaotianWin::onMediaPlayerDoubleClicked()` | 行号: 626-639

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 626 | `"[liaotianWin] 文件不存在!"` | 双击时文件不存在 |
| 639 | `"[liaotianWin] 已停止内置播放器"` | 打开外部播放器前 |

### 15. 函数 `liaotianWin::updateGroupStatus()` | 行号: 683

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 683 | `"[liaotianWin] 群聊状态已更新:" << statusText` | 群聊状态更新完成 |

### 16. 函数 `liaotianWin::loadGroupMembers()` | 行号: 729

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 729 | `"[liaotianWin] 群成员列表已加载，共" << row << "人"` | 群成员列表加载完成 |

---

## 五、media.cpp (3条)

### 1. 函数 `Media::closeEvent()` | 行号: 18

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 18 | `"[Media关闭] 拦截关闭，改为隐藏窗口"` | 媒体播放器窗口关闭时 |

### 2. 函数 `Media::onPositionChanged()` / `onDurationChanged()` | 行号: 53-66

| 行号 | Debug 内容 | 触发条件 |
|------|-----------|---------|
| 53 | `duration` | 媒体时长变化时 (打印毫秒数) |
| 66 | `position` | 播放位置变化时 (打印毫秒数) |

---

## 六、Debug 统计汇总

| 文件 | Debug 数量 | 函数数量 |
|------|-----------|---------|
| main.cpp | 4 | 2 |
| mainwindow.cpp | 31 | 4 |
| userhome.cpp | 100 | 34 |
| liaotianwin.cpp | 33 | 16 |
| media.cpp | 3 | 2 |
| **总计** | **171** | **58** |

### 按模块分类

| 模块 | Debug 数量 | 占比 |
|------|-----------|------|
| 登录注册 (mainwindow.cpp) | 31 | 18.1% |
| TCP连接与消息处理 (userhome.cpp) | 100 | 58.5% |
| 私聊/群聊窗口 (liaotianwin.cpp) | 33 | 19.3% |
| 媒体播放器 (media.cpp) | 3 | 1.8% |
| 程序入口/退出 (main.cpp) | 4 | 2.3% |

### 按日志前缀分类

| 前缀 | 数量 | 说明 |
|------|------|------|
| `[UserHome]` | ~70 | TCP服务器、消息收发、文件传输 |
| `[liaotianWin]` | 33 | 聊天窗口操作 |
| `[提示窗口]` | 10 | 上线通知、新消息通知 |
| `>>>` | ~25 | 登录注册、数据库操作 |
| `[数据库]` | 4 | 数据库状态更新 |
| `[状态检测]` | 1 | 用户状态检测 |
| 无前缀 | ~28 | 列表点击、键盘事件等 |
