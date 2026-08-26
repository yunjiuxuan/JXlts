
#include "userhome.h"
#include "ui_userhome.h"
#include "liaotianwin.h"
#include <QDir>
#include <QRegularExpression>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QDataStream>
#include <QDateTime>
#include <QHeaderView>
#include <QMessageBox>

UserHome::UserHome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserHome)
    , statusTimer(nullptr)
    , model(nullptr)
    , m_tcpServer(nullptr)
    , m_mibaoLayoutVisible(false)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[定时器] 错误：数据库未打开";
        return;
    }
    ui->setupUi(this);

    // 隐藏密保区域
    ui->mibaoyout->setVisible(false);

    // 从结构体获取用户的密保问题并显示
    ui->mibaowentiLabel->setText(ui->mibaowentiLabel->text() + curUserInfo.mibaowenti);

    connect(qApp, &QApplication::aboutToQuit, this, &UserHome::onApplicationQuit);

    ui->show_myname->setText(curUserInfo.nicheng);

    ui->show_myname->installEventFilter(this);
    ui->newpswText->installEventFilter(this);
    ui->inputmbda->installEventFilter(this);
    model = new QSqlQueryModel(this);

    ui->show_ListInfo->setModel(model);
    ui->show_ListInfo->setColumnHidden(0, true);

    statusTimer = new QTimer(this);
    statusTimer->start(2000);

    connect(statusTimer, &QTimer::timeout, this, &UserHome::onCheckStatusTimeout);
    connect(ui->show_ListInfo, &QAbstractItemView::doubleClicked, this, &UserHome::onListClicked);

    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &UserHome::onNewConnection);

    if (m_tcpServer->listen(QHostAddress::Any, 0))
    {
        quint16 actualPort = m_tcpServer->serverPort();
        qDebug() << "[UserHome] TCP服务器启动成功，系统分配的监听端口:" << actualPort;
        
        QString localIp = getLocalIpAddress();
        QString ipWithPort = QString("%1:%2").arg(localIp).arg(actualPort);
        
        qDebug() << "[UserHome] 准备更新自己的IP和端口到数据库:" << ipWithPort;
        
        QSqlQuery query;
        query.prepare("UPDATE userinfo SET ip = :ip WHERE id = :id");
        query.bindValue(":ip", ipWithPort);
        query.bindValue(":id", curUserInfo.id);
        
        if (query.exec())
        {
            qDebug() << "[UserHome] 数据库更新成功：自己的IP和端口已更新为" << ipWithPort;
            curUserInfo.ip = ipWithPort;
        }
        else
        {
            qDebug() << "[UserHome] 数据库更新失败：" << query.lastError().text();
        }
    }
    else
    {
        qDebug() << "[UserHome] TCP服务器启动失败:" << m_tcpServer->errorString();
    }

    setWindowTitle("九玄聊天室");

    ensureChatDirectory();

    onCheckStatusTimeout();
    
    QTimer::singleShot(100, this, [this]() {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen())
        {
            QSqlQuery query;
            query.prepare("SELECT id FROM userinfo WHERE status = 1 AND id != :id");
            query.bindValue(":id", curUserInfo.id);
            if (query.exec())
            {
                while (query.next())
                {
                    int userId = query.value(0).toInt();
                    qDebug() << "[UserHome] 尝试连接在线用户:" << userId;
                    connectToUser(userId);
                }
            }
        }
    });
    
    // 延迟清除焦点，确保窗口显示后生效
    QTimer::singleShot(0, this, [this]() {
        ui->show_myname->clearFocus();
        ui->newpswText->clearFocus();
        ui->inputmbda->clearFocus();
        ui->show_ListInfo->setFocus();
        initGroupChatFile();
    });
}

void UserHome::closeEvent(QCloseEvent *event)
{
    qDebug() << "[UserHome关闭] 正在关闭主窗口，用户ID:" << curUserInfo.id;

    QList<liaotianWin*> windowsToClose = m_chatWindows.values();
    for (liaotianWin *win : windowsToClose)
    {
        if (win)
        {
            win->close();
        }
    }
    m_chatWindows.clear();

    for (auto it = m_activeSockets.begin(); it != m_activeSockets.end(); ++it)
    {
        QTcpSocket *socket = it.value();
        if (socket && socket->state() == QAbstractSocket::ConnectedState)
        {
            socket->disconnectFromHost();
        }
    }
    m_activeSockets.clear();

    if (m_tcpServer)
    {
        m_tcpServer->close();
    }

    qDebug() << "[UserHome关闭] 更新用户状态为离线...";
    QSqlQuery query;
    query.prepare("UPDATE userinfo SET status = 0 WHERE id = :id");
    query.bindValue(":id", curUserInfo.id);

    if (query.exec())
    {
        qDebug() << "[数据库] 用户状态已更新为离线";
        curUserInfo.status = 0;
    }
    else
    {
        qDebug() << "[数据库] 更新用户状态失败：" << query.lastError().text();
    }

    event->accept();

    cleanupGroupChatFile();
}

bool UserHome::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();

        if (key == Qt::Key_Return || key == Qt::Key_Enter)
        {
            if (watched == ui->newpswText)
            {
                qDebug() << "[UserHome] 修改密码输入框回车，触发修改密码";
                on_updatapsw_clicked();
                return true;
            }
        }

        if (key == Qt::Key_Up)
        {
            if (watched == ui->newpswText)
            {
                qDebug() << "[UserHome] 修改密码输入框上键，移动到昵称输入框";
                ui->show_myname->setFocus();
                return true;
            }
            if (watched == ui->inputmbda)
            {
                qDebug() << "[UserHome] 密保答案输入框上键，移动到修改密码输入框";
                ui->newpswText->setFocus();
                return true;
            }
        }

        if (key == Qt::Key_Down)
        {
            if (watched == ui->show_myname)
            {
                qDebug() << "[UserHome] 昵称输入框下键，移动到修改密码输入框";
                ui->newpswText->setFocus();
                return true;
            }
        }

        if (key == Qt::Key_Right)
        {
            if (watched == ui->show_myname)
            {
                qDebug() << "[UserHome] 昵称输入框右键，移动到密保答案输入框";
                ui->inputmbda->setFocus();
                return true;
            }
            if (watched == ui->newpswText)
            {
                qDebug() << "[UserHome] 修改密码输入框右键，移动到密保答案输入框";
                ui->inputmbda->setFocus();
                return true;
            }
        }

        if (key == Qt::Key_Left)
        {
            if (watched == ui->inputmbda)
            {
                qDebug() << "[UserHome] 密保答案输入框左键，移动到昵称输入框";
                ui->show_myname->setFocus();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void UserHome::onApplicationQuit()
{
    if (curUserInfo.status == 1)
    {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen())
        {
            QSqlQuery query;
            query.prepare("UPDATE userinfo SET status = 0 WHERE id = :id");
            query.bindValue(":id", curUserInfo.id);
            if (query.exec())
            {
                qDebug() << "[数据库]  用户状态已更新为离线";
                curUserInfo.status = 0;
            }
            else
            {
                qDebug() << "[数据库]  更新用户状态失败：" << query.lastError().text();
            }
        }
        else
        {
            qWarning() << "[程序退出] 数据库未打开，无法更新状态";
        }
    }
    else
    {
        qDebug() << "[程序退出] 当前状态已为离线";
    }

    cleanupGroupChatFile();
}

UserHome::~UserHome() { delete ui; }

void UserHome::onListClicked(const QModelIndex &index)
{
    qDebug() << "执行onListClicked";

    int userId = ui->show_ListInfo->model()->data(ui->show_ListInfo->model()->index(index.row(), 0)).toInt();
    qDebug() << "获取userId";

    if (userId == curUserInfo.id)
    {
        return;
    }

    QString statusText = ui->show_ListInfo->model()->data(ui->show_ListInfo->model()->index(index.row(), 3)).toString();

    if (m_chatWindows.contains(userId))
    {
        liaotianWin *win = m_chatWindows[userId];
        win->show();
        win->raise();
        win->activateWindow();
        return;
    }

    QString nickName = ui->show_ListInfo->model()->data(ui->show_ListInfo->model()->index(index.row(), 1)).toString();
    bool isUserOnline = (statusText == "在线");
    bool isGroupChat = isGroup(userId);
    qDebug() << "获取nickName，用户在线状态:" << isUserOnline << "是否是群聊:" << isGroupChat;

    liaotianWin *win = new liaotianWin(userId, nickName, this, nullptr, isUserOnline, isGroupChat);
    win->setAttribute(Qt::WA_DeleteOnClose);

    m_chatWindows[userId] = win;
    connect(this, &UserHome::userConnected, win, &liaotianWin::onUserConnected, Qt::UniqueConnection);
    connect(this, &UserHome::userDisconnected, win, &liaotianWin::onUserDisconnected, Qt::UniqueConnection);
    connect(this, &UserHome::sendResult, win, &liaotianWin::onSendResult, Qt::UniqueConnection);

    if (isGroupChat)
    {
        connect(this, &UserHome::groupMessageReceived, win, &liaotianWin::onGroupMessageReceived, Qt::UniqueConnection);
    }
    else
    {
        connect(this, &UserHome::messageReceived, win, &liaotianWin::onMessageReceived, Qt::UniqueConnection);

        if (!isUserConnected(userId))
        {
            connectToUser(userId);
        }
    }

    qDebug() << "点击了第" << index.row() << "行，用户ID:" << userId << "昵称:" << nickName;

    win->show();

    connect(win, &liaotianWin::destroyed, this, [this, userId]() {
        m_chatWindows.remove(userId);
        qDebug() << "[UserHome] 聊天窗口已关闭，用户ID:" << userId;
    });
}

void UserHome::onCheckStatusTimeout()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();

    if (!db.open())
    {
        qDebug() << "数据库重连失败:" << db.lastError().text();
        return;
    }

    QSqlQuery onlineCountQuery("SELECT COUNT(*) FROM userinfo WHERE status = 1");
    int onlineCount = 0;
    if (onlineCountQuery.exec() && onlineCountQuery.next())
    {
        onlineCount = onlineCountQuery.value(0).toInt();
    }

    QString sql = QString("SELECT "
                  "id, "
                  "nicheng, "
                  "status, "
                  "CASE "
                  "   WHEN username IS NULL OR username = '' THEN '%1人' "
                  "   WHEN status = 1 THEN '在线' "
                  "   ELSE '离线' "
                  "END AS status_text, "
                  "ip "
                  "FROM userinfo").arg(onlineCount);

    QSqlQuery query;
    query.prepare(sql);

    if (query.exec())
    {
        QMap<int, int> currentStatus;

        while (query.next())
        {
            int userId = query.value("id").toInt();
            int status = query.value("status").toInt();
            QString nickName = query.value("nicheng").toString();

            currentStatus[userId] = status;
            if (m_lastUserStatus.contains(userId))
            {
                int lastStatus = m_lastUserStatus[userId];
                if (lastStatus == 0 && status == 1 && userId != curUserInfo.id)
            {
                showUserOnlineNotification(nickName);
                connectToUser(userId);
            }
            }
            else
            {
                qDebug() << "[状态检测]   新用户，首次记录状态";
            }
        }

        m_lastUserStatus = currentStatus;
    }

    model->clear();
    model->setQuery(sql);

    if (model->lastError().isValid())
    {
        qDebug() << "查询错误:" << model->lastError().text();
    }

    model->setHeaderData(1, Qt::Horizontal, "用户昵称");
    model->setHeaderData(3, Qt::Horizontal, "状态");
    model->setHeaderData(4, Qt::Horizontal, "IP地址");

    ui->show_ListInfo->setColumnHidden(0, true);
    ui->show_ListInfo->setColumnHidden(2, true);

    ui->show_ListInfo->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->show_ListInfo->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->show_ListInfo->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
}

void UserHome::showUserOnlineNotification(const QString &nickName)
{
    qDebug() << "[提示窗口] 准备显示用户上线提示，昵称:" << nickName;

    QLabel *notification = new QLabel(this);
    notification->setWindowFlags(Qt::ToolTip | Qt::WindowStaysOnTopHint);
    notification->setTextFormat(Qt::RichText);
    notification->setText(QString("<b>%1</b> 上线了！").arg(nickName));
    notification->setStyleSheet(
        "QLabel { background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px; font-size: 14px; }");
    notification->setAlignment(Qt::AlignCenter);
    notification->setMinimumWidth(200);

    QPoint pos = this->mapToGlobal(QPoint(this->width() - 220, 10));
    qDebug() << "[提示窗口] 窗口位置:" << pos;

    notification->move(pos);
    notification->show();
    qDebug() << "[提示窗口] 提示窗口已显示";

    QTimer::singleShot(2000, notification, [notification, nickName]() {
        qDebug() << "[提示窗口] 2秒时间到，关闭提示窗口，昵称:" << nickName;
        notification->close();
        notification->deleteLater();
        qDebug() << "[提示窗口] 窗口已关闭";
    });
}

void UserHome::showNewMessageNotification(const QString &nickName, const QString &content)
{
    qDebug() << "[提示窗口] 准备显示新消息提示，昵称:" << nickName << "内容:" << content;

    QLabel *notification = new QLabel(this);
    notification->setWindowFlags(Qt::ToolTip | Qt::WindowStaysOnTopHint);
    notification->setTextFormat(Qt::RichText);
    
    // 截断过长的消息
    QString displayContent = content;
    if (displayContent.length() > 20) {
        displayContent = displayContent.left(20) + "...";
    }
    
    notification->setText(QString("<b>%1</b> 发来消息：<br>%2").arg(nickName).arg(displayContent));
    notification->setStyleSheet(
        "QLabel { background-color: #2196F3; color: white; padding: 10px; border-radius: 5px; font-size: 13px; }");
    notification->setAlignment(Qt::AlignCenter);
    notification->setMinimumWidth(250);

    QPoint pos = this->mapToGlobal(QPoint(this->width() - 270, 10));
    qDebug() << "[提示窗口] 窗口位置:" << pos;

    notification->move(pos);
    notification->show();
    qDebug() << "[提示窗口] 新消息提示窗口已显示";

    QTimer::singleShot(3000, notification, [notification, nickName]() {
        qDebug() << "[提示窗口] 3秒时间到，关闭新消息提示窗口，昵称:" << nickName;
        notification->close();
        notification->deleteLater();
        qDebug() << "[提示窗口] 新消息提示窗口已关闭";
    });
}

void UserHome::on_updatapsw_clicked()
{
    QString newPsw = ui->newpswText->text().trimmed();
    if (newPsw.isEmpty())
    {
        QMessageBox::warning(this, "错误", "新密码不能为空！");
        return;
    }

    QString mibaoDaanInput = ui->inputmbda->text().trimmed();
    if (mibaoDaanInput.isEmpty())
    {
        if (!m_mibaoLayoutVisible)
        {
            m_mibaoLayoutVisible = true;
            ui->mibaoyout->setVisible(true);
            ui->inputmbda->setFocus();
            qDebug() << "[UserHome] 修改密码：显示密保区域";
            return;
        }
        else
        {
            QMessageBox::warning(this, "提示", "密保答案不能为空！");
            return;
        }
    }

    QSqlQuery query;
    query.prepare("SELECT mibaodaan FROM userinfo WHERE id = :id");
    query.bindValue(":id", curUserInfo.id);

    if (query.exec() && query.next())
    {
        QString storedMibaoDaan = query.value("mibaodaan").toString();
        QString inputMibaoDaanMd5 = getMd5(mibaoDaanInput);
        qDebug() << "[密保验证-修改密码] 数据库中存储的密保答案(MD5):" << storedMibaoDaan;
        qDebug() << "[密保验证-修改密码] 用户输入的密保答案(MD5):" << inputMibaoDaanMd5;
        if (inputMibaoDaanMd5 != storedMibaoDaan)
        {
            QMessageBox::warning(this, "错误", "密保答案不正确！");
            return;
        }
    }
    else
    {
        QMessageBox::warning(this, "错误", "无法获取密保信息！");
        return;
    }

    query.prepare("UPDATE userinfo SET password = :password WHERE id = :id");
    query.bindValue(":password", getMd5(newPsw));
    query.bindValue(":id", curUserInfo.id);

    if (query.exec())
    {
        QMessageBox::information(this, "成功", "密码修改成功！");
        ui->newpswText->clear();
        ui->inputmbda->clear();
        m_mibaoLayoutVisible = false;
        ui->mibaoyout->setVisible(false);
        ui->newpswText->setFocus();
        qDebug() << "[UserHome] 密码修改成功";
    }
    else
    {
        QMessageBox::critical(this, "错误", "密码修改失败：" + query.lastError().text());
    }
}

void UserHome::on_comboBox_currentTextChanged(const QString &statusText)
{
    qDebug() << "[UserHome] 状态切换:" << statusText;
    
    QSqlQuery query;
    
    if (statusText == "在线") {
        query.prepare("UPDATE userinfo SET status = 1 WHERE id = :id");
        query.bindValue(":id", curUserInfo.id);
        if (query.exec()) {
            curUserInfo.status = 1;
            qDebug() << "[UserHome] 状态更新为在线";
        } else {
            qDebug() << "[UserHome] 状态更新失败:" << query.lastError().text();
            ui->comboBox->setCurrentText("隐身");
        }
    } else if (statusText == "隐身") {
        query.prepare("UPDATE userinfo SET status = 0 WHERE id = :id");
        query.bindValue(":id", curUserInfo.id);
        if (query.exec()) {
            curUserInfo.status = 0;
            qDebug() << "[UserHome] 状态更新为隐身";
        } else {
            qDebug() << "[UserHome] 状态更新失败:" << query.lastError().text();
            ui->comboBox->setCurrentText("在线");
        }
    }
}

void UserHome::on_show_myname_returnPressed()
{
    QString newName = ui->show_myname->text().trimmed();
    if (newName.isEmpty())
    {
        return;
    }

    QString mibaoDaanInput = ui->inputmbda->text().trimmed();
    if (mibaoDaanInput.isEmpty())
    {
        if (!m_mibaoLayoutVisible)
        {
            m_mibaoLayoutVisible = true;
            ui->mibaoyout->setVisible(true);
            ui->inputmbda->setFocus();
            qDebug() << "[UserHome] 修改昵称：显示密保区域";
            return;
        }
        else
        {
            QMessageBox::warning(this, "提示", "密保答案不能为空！");
            return;
        }
    }

    QSqlQuery query;
    query.prepare("SELECT mibaodaan FROM userinfo WHERE id = :id");
    query.bindValue(":id", curUserInfo.id);

    if (query.exec() && query.next())
    {
        QString storedMibaoDaan = query.value("mibaodaan").toString();
        QString inputMibaoDaanMd5 = getMd5(mibaoDaanInput);
        qDebug() << "[密保验证-修改昵称] 数据库中存储的密保答案(MD5):" << storedMibaoDaan;
        qDebug() << "[密保验证-修改昵称] 用户输入的密保答案(MD5):" << inputMibaoDaanMd5;
        if (inputMibaoDaanMd5 != storedMibaoDaan)
        {
            QMessageBox::warning(this, "错误", "密保答案不正确！");
            return;
        }
    }
    else
    {
        QMessageBox::warning(this, "错误", "无法获取密保信息！");
        return;
    }

    query.prepare("UPDATE userinfo SET nicheng = :nicheng WHERE id = :id");
    query.bindValue(":nicheng", newName);
    query.bindValue(":id", curUserInfo.id);

    if (query.exec())
    {
        curUserInfo.nicheng = newName;
        qDebug() << "[UserHome] 用户昵称更新成功：" << newName;
        ui->show_myname->clearFocus();
        m_mibaoLayoutVisible = false;
        ui->mibaoyout->setVisible(false);
    }
    else
    {
        qDebug() << "[UserHome] 用户昵称更新失败：" << query.lastError().text();
    }

    ui->show_myname->clearFocus();
}

void UserHome::onNewConnection()
{
    qDebug() << "[UserHome] 收到新的连接请求";

    QTcpSocket *socket = m_tcpServer->nextPendingConnection();
    if (!socket)
    {
        qWarning() << "[UserHome] 获取客户端socket失败";
        return;
    }

    qDebug() << "[UserHome] === 新连接信息 ===";
    qDebug() << "[UserHome] Socket描述符:" << socket->socketDescriptor();
    qDebug() << "[UserHome] 对端地址:" << socket->peerAddress().toString();
    qDebug() << "[UserHome] 对端端口:" << socket->peerPort();
    qDebug() << "[UserHome] ===================";

    int tempId = 10000;
    while (m_activeSockets.contains(tempId))
    {
        tempId++;
    }

    qDebug() << "[UserHome] 分配临时ID:" << tempId;

    m_activeSockets[tempId] = socket;
    setupSocketSignals(socket);
}

void UserHome::setupSocketSignals(QTcpSocket *socket)
{
    connect(socket, &QTcpSocket::readyRead, this, [this, socket]() { onSocketReadyRead(socket); }, Qt::UniqueConnection);
    connect(socket, &QTcpSocket::disconnected, this, [this, socket]() { onSocketDisconnected(socket); }, Qt::UniqueConnection);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)), Qt::UniqueConnection);
    connect(socket, &QTcpSocket::bytesWritten, this, [this, socket](qint64 bytes) { onSocketBytesWritten(socket, bytes); }, Qt::UniqueConnection);
}

void UserHome::onSocketReadyRead(QTcpSocket *socket)
{
    if (!socket)
    {
        return;
    }

    try {
        QByteArray newData = socket->readAll();
    qDebug() << "[UserHome] ========== 收到新数据 ==========";
    qDebug() << "[UserHome] 读取到" << newData.size() << "字节新数据";
    qDebug() << "[UserHome] Socket描述符:" << socket->socketDescriptor();
    qDebug() << "[UserHome] 当前Socket ID:" << m_activeSockets.key(socket, 0);
    qDebug() << "[UserHome] Socket状态:" << socket->state();

    m_socketBuffers[socket].append(newData);
    QByteArray &buffer = m_socketBuffers[socket];

    qDebug() << "[UserHome] 缓冲区总大小:" << buffer.size() << "字节";

    while (true)
    {
        if (buffer.size() < (int)sizeof(qint32))
        {
            qDebug() << "[UserHome] 缓冲区数据不足，等待更多数据:" << buffer.size() << "< 4";
            return;
        }

        qint32 blockSize = 0;
        QDataStream sizeStream(&buffer, QIODevice::ReadOnly);
        sizeStream.setVersion(QDataStream::Qt_5_12);
        sizeStream >> blockSize;

        qDebug() << "[UserHome] 解析到消息长度头:" << blockSize << "字节";

        if (buffer.size() < (int)(sizeof(qint32) + blockSize))
        {
            qDebug() << "[UserHome] 消息不完整，等待更多数据:" << buffer.size() << "<" << (sizeof(qint32) + blockSize);
            return;
        }

        QDataStream readStream(&buffer, QIODevice::ReadOnly);
        readStream.setVersion(QDataStream::Qt_5_12);
        qint32 skipSize;
        QString jsonMessage;
        readStream >> skipSize;
        readStream >> jsonMessage;

        buffer.remove(0, sizeof(qint32) + blockSize);

        qDebug() << "[UserHome] 成功提取完整JSON消息:" << jsonMessage;
        qDebug() << "[UserHome] 缓冲区剩余大小:" << buffer.size() << "字节";

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonMessage.toUtf8(), &parseError);
        
        int senderId = 0;
        int targetId = 0;

        if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();
            senderId = jsonObj["sender_id"].toInt();
            targetId = jsonObj["target_id"].toInt();
            
            qDebug() << "[UserHome] JSON解析成功 - 发送者ID:" << senderId << "目标ID:" << targetId;
        }
        else
        {
            qWarning() << "[UserHome] JSON解析失败，错误:" << parseError.errorString();
        }

        int socketId = m_activeSockets.key(socket, 0);
        
        if (socketId == 0)
        {
            qWarning() << "[UserHome] 未找到Socket对应的ID，跳过此消息";
            continue;
        }

        qDebug() << "[UserHome] Socket当前绑定ID:" << socketId;

        if (senderId > 0 && socketId != senderId && socketId >= 10000)
        {
            if (m_activeSockets.contains(senderId))
            {
                qDebug() << "[UserHome] 用户" << senderId << "已存在连接，关闭新连接避免重复";
                m_activeSockets.remove(socketId);
                socket->close();
                socket->deleteLater();
                return;
            }

            qDebug() << "[UserHome] 更新临时ID" << socketId << "为真实ID" << senderId;
            m_activeSockets.remove(socketId);
            m_activeSockets[senderId] = socket;
            socketId = senderId;
            qDebug() << "[UserHome] ID更新完成，新ID:" << socketId;
            emit userConnected(socketId);
            emit groupStatusChanged(0);
        }

        qDebug() << "[UserHome] 最终发送者ID:" << socketId;
        qDebug() << "[UserHome] 当前m_activeSockets中的用户ID:" << m_activeSockets.keys();

        if (parseError.error != QJsonParseError::NoError || !jsonDoc.isObject())
        {
            qWarning() << "[UserHome] JSON解析失败";
            continue;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if (!jsonObj.contains("timestamp") || !jsonObj.contains("content") || !jsonObj.contains("type"))
        {
            qWarning() << "[UserHome] JSON缺少必要字段";
            continue;
        }

        QString fullTimestamp = jsonObj["timestamp"].toString();
        QString content = jsonObj["content"].toString();
        int type = jsonObj["type"].toInt(-1);

        if (content == "HANDSHAKE")
        {
            qDebug() << "[UserHome] 收到握手消息，不显示在聊天界面";
        }
        else if (type == 1)
        {
            qDebug() << "[UserHome] 收到文件头，文件名:" << content;
            qint64 fileSize = jsonObj["file_size"].toVariant().toLongLong();
            QString timeOnly = fullTimestamp;
            if (fullTimestamp.contains(" "))
            {
                QStringList timeParts = fullTimestamp.split(" ");
                if (timeParts.size() >= 2)
                {
                    timeOnly = timeParts.at(1);
                }
            }

            QString nickName = getNickNameById(socketId);
            QString notifyMessage = "[" + timeOnly + "] " + nickName + " 发送文件: \n" + content + " (" + QString::number(fileSize) + " 字节)";
            addMessageToCache(socketId, notifyMessage);
            emit messageReceived(socketId, notifyMessage);

            QString saveDir = QDir::currentPath() + "/chat_logs/" + QString::number(curUserInfo.id) + "_" + QString::number(socketId) + "/downfile";
            QDir dir;
            dir.mkpath(saveDir);
            
            QString baseName = QFileInfo(content).baseName();
            QString suffix = QFileInfo(content).suffix();
            QString finalFileName = content;
            int counter = 1;
            
            while (QFile::exists(saveDir + "/" + finalFileName))
            {
                if (suffix.isEmpty())
                {
                    finalFileName = baseName + "_" + QString::number(counter);
                }
                else
                {
                    finalFileName = baseName + "_" + QString::number(counter) + "." + suffix;
                }
                counter++;
            }
            
            QString savePath = saveDir + "/" + finalFileName;

            QFile *file = new QFile(savePath);
            if (!file->open(QIODevice::WriteOnly))
            {
                qDebug() << "[UserHome] 文件创建失败:" << savePath;
                delete file;
            }
            else
            {
                FileTransferState state;
                state.fileName = finalFileName;
                state.fileSize = fileSize;
                state.bytesReceived = 0;
                state.file = file;
                state.originalSenderId = socketId;
                m_receiveFileState[socketId] = state;
                qDebug() << "[UserHome] 准备接收文件，保存路径:" << savePath;
                
                emit fileProgress(socketId, 0, fileSize);
            }
        }
        else if (type == 2)
        {
            qDebug() << "[UserHome] 收到文件数据块";
            if (m_receiveFileState.contains(socketId))
            {
                FileTransferState &state = m_receiveFileState[socketId];
                QByteArray data = QByteArray::fromBase64(content.toLatin1());
                if (data.isEmpty())
                {
                    qDebug() << "[UserHome] Base64解码失败或数据为空";
                    continue;
                }
                qint64 bytesWritten = state.file->write(data);
                if (bytesWritten != data.size())
                {
                    qDebug() << "[UserHome] 文件写入失败，期望:" << data.size() << "实际:" << bytesWritten;
                }
                state.bytesReceived += data.size();

                emit fileProgress(socketId, state.bytesReceived, state.fileSize);
                qDebug() << "[UserHome] 已接收:" << state.bytesReceived << "/" << state.fileSize;

                if (state.bytesReceived >= state.fileSize)
                {
                    state.file->close();
                    QString absolutePath = state.file->fileName();
                    QString fileName = state.fileName;
                    int senderId = state.originalSenderId;
                    delete state.file;
                    
                    QDir currentDir(QDir::currentPath());
                    QString relativePath = currentDir.relativeFilePath(absolutePath);
                    
                    m_receiveFileState.remove(socketId);
                    qDebug() << "[UserHome] 文件接收完成:" << absolutePath;
                    
                    QString timeOnly = fullTimestamp;
                    if (fullTimestamp.contains(" "))
                    {
                        QStringList timeParts = fullTimestamp.split(" ");
                        if (timeParts.size() >= 2)
                        {
                            timeOnly = timeParts.at(1);
                        }
                    }
                    QString notifyMessage = "[" + timeOnly + "] 文件接收成功: \n" + fileName + " (保存路径: " + relativePath + ")";
                    addMessageToCache(senderId, notifyMessage);
                    emit messageReceived(senderId, notifyMessage);
                    emit fileReceived(senderId, fileName, absolutePath);
                    
                    QString suffix = QFileInfo(fileName).suffix().toLower();
                    QStringList mediaExtensions = {"mp3", "wav", "flac", "ogg", "aac", "wma",
                                                  "mp4", "avi", "mkv", "mov", "wmv", "flv", "webm"};
                    
                    if (mediaExtensions.contains(suffix))
                    {
                        qDebug() << "[UserHome] 检测到媒体文件，保存到 Media 文件夹";
                        
                        QString chatDir = QString::number(curUserInfo.id) + "_" + QString::number(senderId);
                        QString mediaDir = QDir::currentPath() + "/chat_logs/" + chatDir + "/downfile/Media";
                        QDir dir;
                        dir.mkpath(mediaDir);
                        
                        QString baseName = QFileInfo(fileName).baseName();
                        QString finalMediaFileName = fileName;
                        int counter = 1;
                        while (QFile::exists(mediaDir + "/" + finalMediaFileName))
                        {
                            finalMediaFileName = baseName + "_" + QString::number(counter) + "." + suffix;
                            counter++;
                        }
                        
                        QString mediaPath = mediaDir + "/" + finalMediaFileName;
                        if (QFile::rename(absolutePath, mediaPath))
                        {
                            qDebug() << "[UserHome] 媒体文件已移动到 Media 文件夹:" << mediaPath;
                            
                            QString mediaRelativePath = currentDir.relativeFilePath(mediaPath);
                            
                            QString tableName = QString("QMediaPlayer%1").arg(curUserInfo.id);
                            QSqlQuery insertQuery;
                            insertQuery.prepare(QString("INSERT INTO %1 (targetId, url) VALUES (:targetId, :url)").arg(tableName));
                            insertQuery.bindValue(":targetId", senderId);
                            insertQuery.bindValue(":url", mediaRelativePath);
                            
                            if (insertQuery.exec())
                            {
                                qDebug() << "[UserHome] 媒体文件信息已存入数据库:" << tableName;
                                emit mediaFileAdded(senderId, mediaRelativePath);
                            }
                            else
                            {
                                qDebug() << "[UserHome] 插入数据库失败:" << insertQuery.lastError().text();
                            }
                        }
                        else
                        {
                            qDebug() << "[UserHome] 移动媒体文件失败";
                        }
                    }
                }
            }
        }
        else if (type == 3)
        {
            try
            {
                qDebug() << "[UserHome] 收到文件取消通知";
                QString fileName = content;
                
                if (m_receiveFileState.contains(socketId))
                {
                    FileTransferState &state = m_receiveFileState[socketId];
                    
                    state.file->close();
                    QString filePath = state.file->fileName();
                    delete state.file;
                    m_receiveFileState.remove(socketId);
                    
                    qDebug() << "[UserHome] 删除不完整文件:" << filePath;
                    QFile::remove(filePath);
                    
                    qDebug() << "[UserHome] 接收方文件状态已清理";
                }
                
                QString nickName = getNickNameById(socketId);
                QString timeOnly = fullTimestamp;
                if (fullTimestamp.contains(" "))
                {
                    QStringList timeParts = fullTimestamp.split(" ");
                    if (timeParts.size() >= 2)
                    {
                        timeOnly = timeParts.at(1);
                    }
                }
                QString notifyMessage = "[" + timeOnly + "] " + nickName + ": 取消发送文件 " + fileName;
            addMessageToCache(socketId, notifyMessage);
            emit messageReceived(socketId, notifyMessage);
            emit fileCancelled(socketId, fileName);
            
            qDebug() << "[UserHome] 接收方取消通知处理完成，信号已发射";
            }
            catch (const std::exception &e)
            {
                qCritical() << "[UserHome] 处理取消通知异常:" << e.what();
            }
            catch (...)
            {
                qCritical() << "[UserHome] 处理取消通知未知异常";
            }
        }
        else if (type == 4)
        {
            try
            {
                qDebug() << "[UserHome] 收到接收方取消文件接收通知";
                QString fileName = content;
                
                // 发送方取消文件发送状态（m_sendFileState的key是QTcpSocket*）
                if (m_sendFileState.contains(socket))
                {
                    SendFileState &state = m_sendFileState[socket];
                    
                    qDebug() << "[UserHome] 清理发送方文件状态";
                    if (state.file)
                    {
                        state.file->close();
                        delete state.file;
                        state.file = nullptr;
                    }
                    m_sendFileState.remove(socket);
                    
                    qDebug() << "[UserHome] 发送方文件状态已清理";
                }
                
                QString nickName = getNickNameById(socketId);
                QString timeOnly = fullTimestamp;
                if (fullTimestamp.contains(" "))
                {
                    QStringList timeParts = fullTimestamp.split(" ");
                    if (timeParts.size() >= 2)
                    {
                        timeOnly = timeParts.at(1);
                    }
                }
                QString notifyMessage = "[" + timeOnly + "] " + nickName + ": 取消接收文件 " + fileName;
                addMessageToCache(socketId, notifyMessage);
                emit messageReceived(socketId, notifyMessage);
                emit fileReceiveCancelled(socketId, fileName);
                
                qDebug() << "[UserHome] 发送方接收方取消通知处理完成，信号已发射";
            }
            catch (const std::exception &e)
            {
                qCritical() << "[UserHome] 处理接收方取消通知异常:" << e.what();
            }
            catch (...)
            {
                qCritical() << "[UserHome] 处理接收方取消通知未知异常";
            }
        }
        else if (type == 10)
        {
            int groupId = jsonObj["group_id"].toInt();
            QString timeOnly = fullTimestamp;
            if (fullTimestamp.contains(" "))
            {
                QStringList timeParts = fullTimestamp.split(" ");
                if (timeParts.size() >= 2)
                {
                    timeOnly = timeParts.at(1);
                }
            }

            QString senderName = getNickNameById(socketId);
            QString groupMessage = "[" + timeOnly + "] " + senderName + ": \n" + content;

            qDebug() << "[UserHome] 收到群消息 - 群ID:" << groupId << "发送者:" << senderName;

            saveGroupMessageToFile(groupMessage);

            emit groupMessageReceived(groupId, socketId, senderName, groupMessage);
        }
        else
        {
            QString timeOnly = fullTimestamp;
            if (fullTimestamp.contains(" "))
            {
                QStringList timeParts = fullTimestamp.split(" ");
                if (timeParts.size() >= 2)
                {
                    timeOnly = timeParts.at(1);
                }
            }

            QString nickName = getNickNameById(socketId);
            QString formattedMessage = "[" + timeOnly + "] " + nickName + ": \n" + content;
            qDebug() << "[UserHome] 格式化后的消息:" << formattedMessage;

            qDebug() << "[UserHome] 保存消息到文件，用户ID:" << socketId;
            addMessageToCache(socketId, formattedMessage);

            qDebug() << "[UserHome] 发射messageReceived信号，用户ID:" << socketId;
            emit messageReceived(socketId, formattedMessage);
            
            // 如果该用户的聊天窗口没打开，显示新消息提示
            if (!m_chatWindows.contains(socketId)) {
                qDebug() << "[UserHome] 用户" << socketId << "的聊天窗口未打开，显示新消息提示";
                showNewMessageNotification(nickName, content);
            } else {
                qDebug() << "[UserHome] 用户" << socketId << "的聊天窗口已打开，不显示新消息提示";
            }
        }
        
        qDebug() << "[UserHome] ========== 消息处理完成 ==========";
    }
    } catch (const std::exception &e) {
        qCritical() << "[UserHome] 异常:" << e.what();
        
        // 异常时更新当前用户状态为离线
        updateUserOfflineStatus("[UserHome] 数据库状态更新成功（异常处理）：", "[UserHome] 用户状态更新失败！");
    } catch (...) {
        qCritical() << "[UserHome] 未知异常";
        
        // 异常时更新当前用户状态为离线
        updateUserOfflineStatus("[UserHome] 数据库状态更新成功（异常处理）：", "[UserHome] 用户状态更新失败！");
    }
}

void UserHome::onSocketDisconnected(QTcpSocket *socket)
{
    try
    {
        qDebug() << "[UserHome] onSocketDisconnected被触发，socket:" << socket;
        
        int socketId = m_activeSockets.key(socket, 0);
        
        if (socketId > 0)
        {
            qDebug() << "[UserHome] 用户" << socketId << "断开连接";
            m_activeSockets.remove(socketId);
            emit userDisconnected(socketId);
            emit groupStatusChanged(0);
        }

        // 清理发送文件状态（可能已被cancelFileSend清理）
        if (m_sendFileState.contains(socket))
        {
            qDebug() << "[UserHome] 检测到发送文件状态需要清理，socket:" << socket;
            SendFileState &state = m_sendFileState[socket];
            if (state.file)
            {
                qDebug() << "[UserHome] 关闭并删除发送文件:" << state.file->fileName();
                state.file->close();
                delete state.file;
                state.file = nullptr;
            }
            m_sendFileState.remove(socket);
            qDebug() << "[UserHome] 已清理发送文件状态，用户ID:" << socketId;
        }
        else
        {
            qDebug() << "[UserHome] 发送文件状态已被清理（可能是cancelFileSend操作的）";
        }
        
        // 清理正在接收的文件，删除不完整文件
        if (m_receiveFileState.contains(socketId))
        {
            qDebug() << "[UserHome] 检测到接收文件状态需要清理，用户ID:" << socketId;
            FileTransferState &state = m_receiveFileState[socketId];
            if (state.file)
            {
                if (state.bytesReceived < state.fileSize)
                {
                    qDebug() << "[UserHome] Socket断开，删除不完整文件:" << state.file->fileName();
                    QString filePath = state.file->fileName();
                    state.file->close();
                    delete state.file;
                    state.file = nullptr;
                    QFile::remove(filePath);
                    
                    emit fileCancelled(socketId, state.fileName);
                }
                else
                {
                    qDebug() << "[UserHome] 文件已接收完成，关闭文件:" << state.file->fileName();
                    state.file->close();
                    delete state.file;
                    state.file = nullptr;
                }
            }
            m_receiveFileState.remove(socketId);
            qDebug() << "[UserHome] 已清理接收文件状态，用户ID:" << socketId;
        }
        else
        {
            qDebug() << "[UserHome] 无接收文件状态需要清理，用户ID:" << socketId;
        }
        
        m_socketBuffers.remove(socket);
        qDebug() << "[UserHome] 已清理socket缓冲区";
        
        if (socket)
        {
            socket->deleteLater();
            qDebug() << "[UserHome] 已标记socket为deleteLater";
        }
    }
    catch (const std::exception &e)
    {
        qCritical() << "[UserHome] onSocketDisconnected异常:" << e.what();
    }
    catch (...)
    {
        qCritical() << "[UserHome] onSocketDisconnected未知异常";
    }
}

void UserHome::onSocketError(QAbstractSocket::SocketError error)
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
    {
        qDebug() << "[UserHome] Socket错误:" << error << socket->errorString();

        // 清理发送文件状态
        if (m_sendFileState.contains(socket))
        {
            SendFileState &state = m_sendFileState[socket];
            if (state.file)
            {
                state.file->close();
                delete state.file;
            }
            m_sendFileState.remove(socket);
        }
    }
}

void UserHome::onSocketBytesWritten(QTcpSocket *socket, qint64 bytes)
{
    Q_UNUSED(bytes);
    
    if (!m_sendFileState.contains(socket))
    {
        return;
    }

    SendFileState &state = m_sendFileState[socket];
    qDebug() << "[UserHome] bytesWritten触发，当前状态:" << state.bytesSent << "/" << state.fileSize;
    
    if (state.cancelled)
    {
        qDebug() << "[UserHome] 文件发送已被取消，停止发送";
        if (state.file)
        {
            state.file->close();
            delete state.file;
            state.file = nullptr;
        }
        m_sendFileState.remove(socket);
        return;
    }

    if (!state.file)
    {
        qWarning() << "[UserHome] state.file为空，可能已被清理";
        m_sendFileState.remove(socket);
        return;
    }

    if (state.bytesSent >= state.fileSize)
    {
        qDebug() << "[UserHome] 文件已全部发送完毕";
        state.file->close();
        delete state.file;
        state.file = nullptr;
        
        QString timePart = state.timestamp;
        if (timePart.contains(" "))
        {
            QStringList parts = timePart.split(" ");
            if (parts.size() >= 2)
            {
                timePart = parts.at(1);
            }
        }
        QString fileName = state.fileName;
        QString filePath = state.filePath;
        int targetUserId = state.targetUserId;
        
        m_sendFileState.remove(socket);
        qDebug() << "[UserHome] 文件发送完成";
        
        QString notifyMessage = "[" + timePart + "] 文件发送成功: \n" + fileName + " (文件路径: " + filePath + ")";
        addMessageToCache(targetUserId, notifyMessage);
        emit messageReceived(targetUserId, notifyMessage);
        emit sendResult(targetUserId, true, "文件发送完成");
        return;
    }

    QByteArray data = state.file->read(1024 * 64);
    if (data.isEmpty())
    {
        qDebug() << "[UserHome] 文件读取完毕，已发送:" << state.bytesSent << "/" << state.fileSize;
        state.file->close();
        delete state.file;
        state.file = nullptr;
        
        QString timePart = state.timestamp;
        if (timePart.contains(" "))
        {
            QStringList parts = timePart.split(" ");
            if (parts.size() >= 2)
            {
                timePart = parts.at(1);
            }
        }
        QString fileName = state.fileName;
        QString filePath = state.filePath;
        int targetUserId = state.targetUserId;
        
        m_sendFileState.remove(socket);
        qDebug() << "[UserHome] 文件发送完成";
        
        QString notifyMessage = "[" + timePart + "] 文件发送成功: \n" + fileName + " (文件路径: " + filePath + ")";
        addMessageToCache(targetUserId, notifyMessage);
        emit messageReceived(targetUserId, notifyMessage);
        emit sendResult(targetUserId, true, "文件发送完成");
        return;
    }

    QJsonObject jsonObj;
    jsonObj["sender_id"] = curUserInfo.id;
    jsonObj["target_id"] = state.targetUserId;
    jsonObj["content"] = QString::fromLatin1(data.toBase64());
    jsonObj["type"] = 2;
    jsonObj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QJsonDocument jsonDoc(jsonObj);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << (qint32)0;
    out << jsonString;
    out.device()->seek(0);
    out << (qint32)(block.size() - sizeof(qint32));

    qint64 written = socket->write(block);
    if (written > 0)
    {
        state.bytesSent += data.size();
        emit fileProgress(state.targetUserId, state.bytesSent, state.fileSize);
        qDebug() << "[UserHome] 发送文件数据块，已发送:" << state.bytesSent << "/" << state.fileSize;
    }
}

void UserHome::addMessageToCache(int userId, const QString &message)
{
    saveMessageToFile(userId, message);
    qDebug() << "[UserHome] 消息已保存到文件，用户ID:" << userId;
}

void UserHome::addMessageToCache(int userId, const QString &message, const QDate &date)
{
    saveMessageToFile(userId, message, date);
}

void UserHome::sendMessageToUser(int userId, const QString &message, int messageType)
{
    qDebug() << "[UserHome] ========== 发送消息 ==========";
    qDebug() << "[UserHome] 尝试发送消息到用户ID:" << userId << "内容:" << message;
    qDebug() << "[UserHome] 当前m_activeSockets中的用户ID:" << m_activeSockets.keys();

    if (!m_activeSockets.contains(userId))
    {
        qDebug() << "[UserHome] 未找到用户" << userId << "的连接！";
        emit sendResult(userId, false, "未找到用户连接");
        return;
    }

    QTcpSocket *socket = m_activeSockets[userId];
    if (!socket || socket->state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "[UserHome] 用户" << userId << "的Socket未连接！当前状态:" << (socket ? socket->state() : -1);
        emit sendResult(userId, false, "Socket未连接");
        return;
    }

    QJsonObject jsonObj;
    jsonObj["sender_id"] = curUserInfo.id;
    jsonObj["target_id"] = userId;
    jsonObj["content"] = message;
    jsonObj["type"] = messageType;
    jsonObj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QJsonDocument jsonDoc(jsonObj);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    qDebug() << "[UserHome] 准备发送的JSON:" << jsonString;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << (qint32)0;
    out << jsonString;
    out.device()->seek(0);
    out << (qint32)(block.size() - sizeof(qint32));

    qint64 bytesWritten = socket->write(block);
    qDebug() << "[UserHome] 实际写入字节数:" << bytesWritten << "总字节数:" << block.size();

    socket->flush();
    qDebug() << "[UserHome] 已调用flush()";

    qDebug() << "[UserHome] 消息已发送给用户" << userId;
    emit sendResult(userId, true, "");
}

void UserHome::sendFileToUser(int userId, const QString &filePath)
{
    qDebug() << "[UserHome] ========== 发送文件 ==========";
    qDebug() << "[UserHome] 尝试发送文件到用户ID:" << userId << "文件路径:" << filePath;

    if (!m_activeSockets.contains(userId))
    {
        qDebug() << "[UserHome] 未找到用户" << userId << "的连接！";
        emit sendResult(userId, false, "未找到用户连接");
        return;
    }

    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists())
    {
        qDebug() << "[UserHome] 文件不存在:" << filePath;
        emit sendResult(userId, false, "文件不存在");
        return;
    }

    QTcpSocket *socket = m_activeSockets[userId];
    if (!socket || socket->state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "[UserHome] 用户" << userId << "的Socket未连接！";
        emit sendResult(userId, false, "Socket未连接");
        return;
    }

    QString fileName = fileInfo.fileName();
    qint64 fileSize = fileInfo.size();
    QString currentTimestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QJsonObject jsonObj;
    jsonObj["sender_id"] = curUserInfo.id;
    jsonObj["target_id"] = userId;
    jsonObj["content"] = fileName;
    jsonObj["file_size"] = (qint64)fileSize;
    jsonObj["type"] = 1;
    jsonObj["timestamp"] = currentTimestamp;

    QJsonDocument jsonDoc(jsonObj);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    qDebug() << "[UserHome] 准备发送文件头:" << jsonString;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << (qint32)0;
    out << jsonString;
    out.device()->seek(0);
    out << (qint32)(block.size() - sizeof(qint32));

    qint64 bytesWritten = socket->write(block);
    qDebug() << "[UserHome] 文件头发送字节数:" << bytesWritten;

    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "[UserHome] 文件打开失败:" << filePath;
        delete file;
        emit sendResult(userId, false, "文件打开失败");
        return;
    }

    SendFileState state;
    state.fileName = fileName;
    state.fileSize = fileSize;
    state.bytesSent = 0;
    state.file = file;
    state.targetUserId = userId;
    state.filePath = QFileInfo(filePath).absoluteFilePath();
    state.timestamp = currentTimestamp;
    state.cancelled = false;
    m_sendFileState[socket] = state;

    qDebug() << "[UserHome] 文件头已发送，准备发送数据，文件大小:" << fileSize;

    // 手动发送第一个数据块，启动传输流程
    if (state.bytesSent < state.fileSize)
    {
        QByteArray data = state.file->read(1024 * 64);
        if (!data.isEmpty())
        {
            QJsonObject jsonObj;
            jsonObj["sender_id"] = curUserInfo.id;
            jsonObj["target_id"] = userId;
            jsonObj["content"] = QString::fromLatin1(data.toBase64());
            jsonObj["type"] = 2;
            jsonObj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

            QJsonDocument jsonDoc(jsonObj);
            QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_12);
            out << (qint32)0;
            out << jsonString;
            out.device()->seek(0);
            out << (qint32)(block.size() - sizeof(qint32));

            qint64 written = socket->write(block);
            if (written > 0)
            {
                m_sendFileState[socket].bytesSent += data.size();
            }

            emit fileProgress(userId, m_sendFileState[socket].bytesSent, state.fileSize);
            qDebug() << "[UserHome] 发送第一个数据块，已发送:" << m_sendFileState[socket].bytesSent << "/" << state.fileSize;
        }
    }
}

liaotianWin *UserHome::getChatWindow(int userId)
{
    if (m_chatWindows.contains(userId))
    {
        return m_chatWindows[userId];
    }
    return nullptr;
}

bool UserHome::isUserConnected(int userId)
{
    return m_activeSockets.contains(userId);
}

void UserHome::cancelFileSend(int targetUserId)
{
    try
    {
        for (auto it = m_sendFileState.begin(); it != m_sendFileState.end(); ++it)
        {
            if (it.value().targetUserId == targetUserId)
            {
                QTcpSocket *socket = it.key();
                SendFileState &state = it.value();
                
                qDebug() << "[UserHome] 取消文件发送，用户ID:" << targetUserId << "文件名:" << state.fileName;
                
                // 先保存所有需要的值到局部变量
                QString fileName = state.fileName;
                QFile *file = state.file;
                
                state.cancelled = true;
                
                // 先关闭文件
                if (file)
                {
                    file->close();
                    delete file;
                }
                
                // 先 remove（防止 onSocketBytesWritten 触发时访问失效的 iterator）
                m_sendFileState.remove(socket);
                qDebug() << "[UserHome] 已清理发送文件状态，socket:" << socket;
                
                // 发送取消通知给对方（此时 onSocketBytesWritten 会因为 !contains(socket) 而直接返回）
                QJsonObject jsonObj;
                jsonObj["sender_id"] = curUserInfo.id;
                jsonObj["target_id"] = targetUserId;
                jsonObj["content"] = fileName;
                jsonObj["type"] = 3;
                jsonObj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                
                QJsonDocument jsonDoc(jsonObj);
                QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
                
                QByteArray block;
                QDataStream out(&block, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_12);
                out << (qint32)0;
                out << jsonString;
                out.device()->seek(0);
                out << (qint32)(block.size() - sizeof(qint32));
                
                socket->write(block);
                socket->flush();
                
                QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
                QString notifyMessage = "[" + currentTime + "] 我: 取消发送文件 " + fileName;
                addMessageToCache(targetUserId, notifyMessage);
                emit messageReceived(targetUserId, notifyMessage);
                
                emit fileCancelled(targetUserId, fileName);
                emit sendResult(targetUserId, false, "文件发送已取消");
                
                qDebug() << "[UserHome] 取消文件发送完成，信号已发射";
                return;
            }
        }
    }
    catch (const std::exception &e)
    {
        qCritical() << "[UserHome] cancelFileSend异常:" << e.what();
    }
    catch (...)
    {
        qCritical() << "[UserHome] cancelFileSend未知异常";
    }
}

void UserHome::cancelFileReceive(int targetUserId)
{
    try
    {
        if (m_receiveFileState.contains(targetUserId))
        {
            FileTransferState &state = m_receiveFileState[targetUserId];
            
            qDebug() << "[UserHome] 取消文件接收，用户ID:" << targetUserId << "文件名:" << state.fileName;
            
            // 先保存所有需要的值到局部变量
            QString fileName = state.fileName;
            QFile *file = state.file;
            
            // 先关闭文件
            if (file)
            {
                file->close();
                delete file;
            }
            
            // 先 remove（防止后续操作触发异常）
            m_receiveFileState.remove(targetUserId);
            qDebug() << "[UserHome] 已清理接收文件状态，用户ID:" << targetUserId;
            
            // 发送取消通知给对方（type == 4 表示接收方取消）
            QTcpSocket *socket = m_activeSockets.value(targetUserId, nullptr);
            if (socket && socket->state() == QAbstractSocket::ConnectedState)
            {
                QJsonObject jsonObj;
                jsonObj["sender_id"] = curUserInfo.id;
                jsonObj["target_id"] = targetUserId;
                jsonObj["content"] = fileName;
                jsonObj["type"] = 4;
                jsonObj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                
                QJsonDocument jsonDoc(jsonObj);
                QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
                
                QByteArray block;
                QDataStream out(&block, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_12);
                out << (qint32)0;
                out << jsonString;
                out.device()->seek(0);
                out << (qint32)(block.size() - sizeof(qint32));
                
                socket->write(block);
                socket->flush();
                qDebug() << "[UserHome] 已发送取消接收通知给用户:" << targetUserId;
            }
            else
            {
                qWarning() << "[UserHome] 无法发送取消通知，用户" << targetUserId << "未连接";
            }
            
            // 隐藏进度条
            emit fileCancelled(targetUserId, fileName);
            emit receiveResult(targetUserId, false, "文件接收已取消");
            
            qDebug() << "[UserHome] 取消文件接收完成，信号已发射";
        }
        else
        {
            qDebug() << "[UserHome] 没有找到用户" << targetUserId << "的接收文件状态";
        }
    }
    catch (const std::exception &e)
    {
        qCritical() << "[UserHome] cancelFileReceive异常:" << e.what();
    }
    catch (...)
    {
        qCritical() << "[UserHome] cancelFileReceive未知异常";
    }
}

void UserHome::registerSocket(int userId, QTcpSocket *socket)
{
    if (socket)
    {
        m_activeSockets[userId] = socket;
        setupSocketSignals(socket);
        qDebug() << "[UserHome] 注册Socket，用户ID:" << userId;
    }
}

void UserHome::connectToUser(int userId)
{
    if (userId == curUserInfo.id || isUserConnected(userId))
    {
        return;
    }

    // 只有当自己的ID < 目标用户ID时才主动连接，避免双方同时连接
    if (curUserInfo.id >= userId)
    {
        qDebug() << "[UserHome] 等待对方主动连接，避免重复连接，用户ID:" << userId;
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[UserHome] 数据库未打开，无法获取用户信息";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT username, ip FROM userinfo WHERE id = :id");
    query.bindValue(":id", userId);

    if (!query.exec() || !query.next())
    {
        qDebug() << "[UserHome] 无法获取用户" << userId << "的信息";
        return;
    }

    QString username = query.value("username").toString();
    if (username.isEmpty())
    {
        qDebug() << "[UserHome] 用户" << userId << "是群聊(nicheng=" << query.value("nicheng").toString() << ")，不需要TCP连接";
        return;
    }

    QString ipWithPort = query.value("ip").toString();
    if (ipWithPort.isEmpty())
    {
        qDebug() << "[UserHome] 用户" << userId << "IP为空，无法连接";
        return;
    }
    QStringList parts = ipWithPort.split(":");
    QString targetIp = "127.0.0.1";
    quint16 targetPort = 8888;

    if (parts.size() >= 2)
    {
        targetIp = parts[0];
        targetPort = parts[1].toUInt();
    }
    else if (!ipWithPort.isEmpty())
    {
        targetIp = ipWithPort;
    }

    qDebug() << "[UserHome] 准备连接到用户" << userId << "，地址:" << targetIp << ":" << targetPort;

    QTcpSocket *socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, [this, userId, socket]() {
        qDebug() << "[UserHome] 连接到用户" << userId << "成功";
        registerSocket(userId, socket);
        
        // 发送握手消息
        QJsonObject jsonObj;
        jsonObj["sender_id"] = curUserInfo.id;
        jsonObj["target_id"] = userId;
        jsonObj["content"] = "HANDSHAKE";
        jsonObj["type"] = 0;
        jsonObj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        QJsonDocument jsonDoc(jsonObj);
        QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_12);
        out << (qint32)0;
        out << jsonString;
        out.device()->seek(0);
        out << (qint32)(block.size() - sizeof(qint32));

        socket->write(block);
        socket->flush();

        emit userConnected(userId);
        emit groupStatusChanged(0);
    });

    connect(socket, &QTcpSocket::disconnected, this, [this, userId, socket]() {
        qDebug() << "[UserHome] 与用户" << userId << "的连接已断开";
        m_activeSockets.remove(userId);
        emit userDisconnected(userId);
        emit groupStatusChanged(0);
        socket->deleteLater();
    });

    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, [this, userId, socket](QAbstractSocket::SocketError error) {
        qDebug() << "[UserHome] 连接用户" << userId << "失败:" << error << socket->errorString();
        socket->deleteLater();
    });

    socket->connectToHost(targetIp, targetPort);
}

quint16 UserHome::loadMyPort()
{
    QString ipWithPort = curUserInfo.ip;
    QStringList parts = ipWithPort.split(":");
    if (parts.size() >= 2)
    {
        quint16 port = parts[1].toUInt();
        qDebug() << "[UserHome] 从数据库加载端口:" << port;
        return port;
    }
    qDebug() << "[UserHome] 使用默认端口:8888";
    return 8888;
}

QString UserHome::getLocalIpAddress()
{
    QString localIp;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    for (int i = 0; i < ipAddressesList.size(); i++)
    {
        QHostAddress addr = ipAddressesList.at(i);
        if (addr.protocol() == QAbstractSocket::IPv4Protocol && addr != QHostAddress::LocalHost && !addr.isLoopback())
        {
            localIp = addr.toString();
            break;
        }
    }

    if (localIp.isEmpty())
    {
        localIp = "127.0.0.1";
    }

    qDebug() << "[UserHome] 获取本机IP地址:" << localIp;
    return localIp;
}

void UserHome::updateMyIpAndPort()
{
    QString localIp = getLocalIpAddress();
    quint16 myPort = loadMyPort();
    QString ipWithPort = QString("%1:%2").arg(localIp).arg(myPort);

    qDebug() << "[UserHome] 准备更新自己的IP和端口到数据库:" << ipWithPort;

    QSqlQuery query;
    query.prepare("UPDATE userinfo SET ip = :ip WHERE id = :id");
    query.bindValue(":ip", ipWithPort);
    query.bindValue(":id", curUserInfo.id);

    if (query.exec())
    {
        qDebug() << "[UserHome] 数据库更新成功：自己的IP和端口已更新为" << ipWithPort;
        curUserInfo.ip = ipWithPort;
    }
    else
    {
        qDebug() << "[UserHome] 数据库更新失败：" << query.lastError().text();
    }
}

QString UserHome::getNickNameById(int userId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        return "未知";
    }

    QSqlQuery query;
    query.prepare("SELECT nicheng FROM userinfo WHERE id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next())
    {
        return query.value(0).toString();
    }

    return "未知";
}

QString UserHome::getChatFileName(int userId)
{
    return getChatFileName(userId, QDate::currentDate());
}

QString UserHome::getChatFileName(int userId, const QDate &date)
{
    QDir chatDir = QDir::current();
    // 使用"自己id_对方id"的格式，确保每个用户的聊天记录独立
    QString userDir = "chat_logs/" + QString::number(curUserInfo.id) + "_" + QString::number(userId);
    chatDir.mkpath(userDir);
    chatDir.cd(userDir);
    return chatDir.filePath(date.toString("yyyy-MM-dd") + ".txt");
}

void UserHome::saveMessageToFile(int userId, const QString &message)
{
    saveMessageToFile(userId, message, QDate::currentDate());
}

void UserHome::saveMessageToFile(int userId, const QString &message, const QDate &date)
{
    QString fileName = getChatFileName(userId, date);
    QFile file(fileName);

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << message << "\n";
        file.close();
        qDebug() << "[UserHome] 消息已追加到文件:" << fileName;
    }
    else
    {
        qDebug() << "[UserHome] 无法打开文件写入:" << fileName << "错误:" << file.errorString();
    }
}

QStringList UserHome::getCachedMessages(int userId)
{
    return loadMessagesFromFile(userId, QDate::currentDate());
}

QStringList UserHome::getMessagesForDate(int userId, const QDate &date)
{
    return loadMessagesFromFile(userId, date);
}

QStringList UserHome::loadMessagesFromFile(int userId)
{
    return loadMessagesFromFile(userId, QDate::currentDate());
}

QStringList UserHome::loadMessagesFromFile(int userId, const QDate &date)
{
    QStringList messages;
    QString fileName = getChatFileName(userId, date);
    QFile file(fileName);

    if (!file.exists())
    {
        qDebug() << "[UserHome] 聊天记录文件不存在:" << fileName;
        return messages;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (!line.trimmed().isEmpty())
            {
                messages.append(line);
            }
        }
        file.close();
        qDebug() << "[UserHome] 已从文件加载" << messages.size() << "条消息:" << fileName;
    }
    else
    {
        qDebug() << "[UserHome] 无法打开文件读取:" << fileName << "错误:" << file.errorString();
    }

    return messages;
}

void UserHome::ensureChatDirectory()
{
    QDir chatDir = QDir::current();
    if (!chatDir.exists("chat_logs"))
    {
        chatDir.mkdir("chat_logs");
        qDebug() << "[UserHome] 聊天记录目录已创建";
    }
}

bool UserHome::isGroup(int userId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT username FROM userinfo WHERE id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next())
    {
        QString username = query.value(0).toString();
        return username.isEmpty();
    }

    return false;
}

int UserHome::getGroupTotalCount(int groupId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        return 0;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM userinfo WHERE username IS NOT NULL AND username != ''");

    if (query.exec() && query.next())
    {
        return query.value(0).toInt();
    }

    return 0;
}

int UserHome::getGroupOnlineCount(int groupId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        return 0;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM userinfo WHERE status = 1 AND username IS NOT NULL AND username != ''");

    if (query.exec() && query.next())
    {
        return query.value(0).toInt();
    }

    return 0;
}

QString UserHome::getGroupMembersString(int groupId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        return "";
    }

    QSqlQuery query;
    query.prepare("SELECT nicheng FROM userinfo WHERE status = 1 AND id != :id AND username IS NOT NULL AND username != ''");
    query.bindValue(":id", groupId);

    QStringList members;
    if (query.exec())
    {
        while (query.next())
        {
            members.append(query.value(0).toString());
        }
    }

    return members.join(", ");
}

void UserHome::sendGroupMessage(int groupId, const QString &message)
{
    qDebug() << "[UserHome] ========== 发送群消息 ==========";
    qDebug() << "[UserHome] 群ID:" << groupId << "内容:" << message;

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "[UserHome] 数据库未打开，无法发送群消息";
        emit sendResult(groupId, false, "数据库未打开");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id FROM userinfo WHERE status = 1 AND id != :id AND username IS NOT NULL AND username != ''");
    query.bindValue(":id", groupId);

    if (!query.exec())
    {
        qDebug() << "[UserHome] 查询在线用户失败:" << query.lastError().text();
        emit sendResult(groupId, false, "查询在线用户失败");
        return;
    }

    QList<int> onlineMembers;
    while (query.next())
    {
        int memberId = query.value(0).toInt();
        if (memberId != curUserInfo.id)
        {
            onlineMembers.append(memberId);
        }
    }

    qDebug() << "[UserHome] 在线成员:" << onlineMembers;

    for (int memberId : onlineMembers)
    {
        if (m_activeSockets.contains(memberId))
        {
            QTcpSocket *socket = m_activeSockets[memberId];
            if (socket && socket->state() == QAbstractSocket::ConnectedState)
            {
                QJsonObject jsonObj;
                jsonObj["sender_id"] = curUserInfo.id;
                jsonObj["target_id"] = memberId;
                jsonObj["group_id"] = groupId;
                jsonObj["content"] = message;
                jsonObj["type"] = 10;
                jsonObj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

                QJsonDocument jsonDoc(jsonObj);
                QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

                QByteArray block;
                QDataStream out(&block, QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_5_12);
                out << (qint32)0;
                out << jsonString;
                out.device()->seek(0);
                out << (qint32)(block.size() - sizeof(qint32));

                socket->write(block);
                qDebug() << "[UserHome] 群消息已发送给成员:" << memberId;
            }
        }
    }

    qDebug() << "[UserHome] 群消息广播完成，共发送给" << onlineMembers.size() << "个成员";
    emit sendResult(groupId, true, "");
}

void UserHome::initGroupChatFile()
{
    QString fileName = QString("群聊_%1").arg(curUserInfo.id);
    QString filePath = QDir::currentPath() + "/chat_logs/" + fileName;

    QFile file(filePath);
    if (file.exists())
    {
        qDebug() << "[UserHome] 群聊日志文件已存在，清空内容:" << filePath;
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            file.close();
            qDebug() << "[UserHome] 群聊日志文件已清空";
        }
    }
    else
    {
        qDebug() << "[UserHome] 群聊日志文件不存在，创建新文件:" << filePath;
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
            qDebug() << "[UserHome] 群聊日志文件已创建";
        }
    }
}

void UserHome::saveGroupMessageToFile(const QString &message)
{
    QString fileName = QString("群聊_%1").arg(curUserInfo.id);
    QString filePath = QDir::currentPath() + "/chat_logs/" + fileName;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << message << "\n";
        file.close();
    }
    else
    {
        qDebug() << "[UserHome] 保存群消息到文件失败:" << filePath;
    }
}

QStringList UserHome::loadGroupMessagesFromFile()
{
    QStringList messages;
    QString fileName = QString("群聊_%1").arg(curUserInfo.id);
    QString filePath = QDir::currentPath() + "/chat_logs/" + fileName;

    QFile file(filePath);
    if (!file.exists())
    {
        qDebug() << "[UserHome] 群聊日志文件不存在:" << filePath;
        return messages;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (!line.trimmed().isEmpty())
            {
                messages.append(line);
            }
        }
        file.close();
    }
    else
    {
        qDebug() << "[UserHome] 读取群聊日志文件失败:" << filePath;
    }

    return messages;
}

void UserHome::cleanupGroupChatFile()
{
    QString fileName = QString("群聊_%1").arg(curUserInfo.id);
    QString filePath = QDir::currentPath() + "/chat_logs/" + fileName;

    QFile file(filePath);
    if (file.exists())
    {
        if (file.remove())
        {
            qDebug() << "[UserHome] 群聊日志文件已删除:" << filePath;
        }
        else
        {
            qDebug() << "[UserHome] 删除群聊日志文件失败:" << filePath;
        }
    }
    else
    {
        qDebug() << "[UserHome] 群聊日志文件不存在，无需删除:" << filePath;
    }
}
