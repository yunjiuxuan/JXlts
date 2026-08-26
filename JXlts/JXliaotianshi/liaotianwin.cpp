#include "liaotianwin.h"
#include "ui_liaotianwin.h"
#include "userhome.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>
#include <QScrollBar>
#include <QCalendarWidget>
#include <QSqlQuery>
#include <QHeaderView>
#include <QMessageBox>
#include <QTimer>
#include <QStandardItemModel>
#include <exception>

liaotianWin::liaotianWin(int targetId, const QString &targetName, UserHome *userHome, QWidget *parent,
                         bool isUserOnline, bool isGroup)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::liaotianWin)
    , m_targetId(targetId)
    , m_targetName(targetName)
    , m_userHome(userHome)
    , m_isConnected(false)
    , m_isUserOnline(isUserOnline)
    , m_isGroup(isGroup)
    , m_mediaModel(nullptr)
    , m_groupMemberModel(nullptr)
    , m_mediaPlayer(new QMediaPlayer(this))
    , m_currentPlayingFile("")
    , m_lastClickedFile("")
    , m_mediaPlayerWindow(nullptr)
    , m_isSendingFile(false)
{
    ui->setupUi(this);
    setWindowTitle("九玄聊天室");
    ui->targetName->setText(targetName);

    ui->calendarWidget->hide();
    ui->dateEdit->setDate(QDate::currentDate());

    if (m_isGroup)
    {
        ui->targetStatus->setText("加载中...");
        QTimer::singleShot(100, this, [this]() {
            updateGroupStatus();
            loadGroupMemberModel();
            if (m_userHome)
            {
                connect(m_userHome, &UserHome::groupMessageReceived, this, &liaotianWin::onGroupMessageReceived, Qt::UniqueConnection);
                connect(m_userHome, &UserHome::groupStatusChanged, this, [this](int groupId) {
                    if (groupId == m_targetId)
                    {
                        updateGroupStatus();
                        loadGroupMemberModel();
                    }
                });
            }
        });
    }
    else
    {
        loadTargetInfo(targetId);
    }

    qDebug() << "[liaotianWin]" << (m_isGroup ? "群聊" : "私聊") << ":" << targetName << "，ID:" << targetId;

    connect(ui->send, &QPushButton::clicked, this, &liaotianWin::onSendButtonClicked);
    connect(ui->cancel, &QPushButton::clicked, this, &liaotianWin::onCancelButtonClicked);
    connect(ui->sendFile, &QPushButton::clicked, this, &liaotianWin::onSendFileButtonClicked);
    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, &liaotianWin::onCalendarSelectionChanged);
    connect(ui->QMediaPlayer, &QTableView::clicked, this, &liaotianWin::onMediaPlayerClicked);
    connect(ui->QMediaPlayer, &QTableView::doubleClicked, this, &liaotianWin::onMediaPlayerDoubleClicked);

    ui->sendmsg->installEventFilter(this);
    ui->dateEdit->installEventFilter(this);

    if (m_userHome)
    {
        QStringList cachedMessages;
        if (m_isGroup)
        {
            cachedMessages = m_userHome->loadGroupMessagesFromFile();
        }
        else
        {
            cachedMessages = m_userHome->getCachedMessages(targetId);
        }

        if (!cachedMessages.isEmpty())
        {
            qDebug() << "[liaotianWin] 加载缓存消息，数量:" << cachedMessages.size();
            for (const QString &msg : cachedMessages)
            {
                ui->liaotianInfo->append("");
                ui->liaotianInfo->append(msg);
                ui->liaotianInfo->append("");
            }
            ui->liaotianInfo->append("------------------------------以上是历史信息");
        }
        if (!m_isGroup)
        {
            connect(m_userHome, &UserHome::fileReceived, this, &liaotianWin::onFileReceived, Qt::UniqueConnection);
            connect(m_userHome, &UserHome::fileProgress, this, &liaotianWin::onFileProgress, Qt::UniqueConnection);
            connect(m_userHome, &UserHome::mediaFileAdded, this, &liaotianWin::onMediaFileAdded, Qt::UniqueConnection);
            connect(m_userHome, &UserHome::fileCancelled, this, &liaotianWin::onFileCancelled, Qt::UniqueConnection);
            connect(m_userHome, &UserHome::fileReceiveCancelled, this, &liaotianWin::onFileReceiveCancelled, Qt::UniqueConnection);
            connect(m_userHome, &UserHome::sendResult, this, &liaotianWin::onSendResult, Qt::UniqueConnection);
            connect(m_userHome, &UserHome::receiveResult, this, &liaotianWin::onReceiveResult, Qt::UniqueConnection);
        }
    }

    if (!m_isGroup && m_userHome && m_userHome->isUserConnected(targetId))
    {
        qDebug() << "[liaotianWin] UserHome已经连接了，直接设置为已连接";
        m_isConnected = true;
    }
    else if (!m_isGroup)
    {
        qDebug() << "[liaotianWin] 等待UserHome建立连接";
    }

    initMediaPlayerTable();

    updateSendButtonsEnabled(m_isGroup || m_isUserOnline);

    if (m_isGroup)
    {
        ui->sendFile->setEnabled(false);
        ui->sendFile->setToolTip("群聊不支持文件传输");
        ui->dateEdit->hide();
        ui->calendarWidget->hide();
    }
}

void liaotianWin::onMessageReceived(int userId, const QString &message)
{
    if (!ui || userId != m_targetId)
    {
        return;
    }

    ui->liaotianInfo->append("");
    ui->liaotianInfo->append(message);
    ui->liaotianInfo->append("");
    QScrollBar *scrollBar = ui->liaotianInfo->verticalScrollBar();
    if (scrollBar)
    {
        scrollBar->setValue(scrollBar->maximum());
    }
    qDebug() << "[liaotianWin] 收到消息:" << message;
}

void liaotianWin::onGroupMessageReceived(int groupId, int senderId, const QString &senderName, const QString &message)
{
    if (!ui || groupId != m_targetId)
    {
        return;
    }

    ui->liaotianInfo->append("");
    ui->liaotianInfo->append(message);
    ui->liaotianInfo->append("");
    QScrollBar *scrollBar = ui->liaotianInfo->verticalScrollBar();
    if (scrollBar)
    {
        scrollBar->setValue(scrollBar->maximum());
    }
    qDebug() << "[liaotianWin] 收到群消息 - 群:" << groupId << "发送者:" << senderName << "消息:" << message;
}

void liaotianWin::onUserConnected(int userId)
{
    if (m_isGroup)
    {
        updateGroupStatus();
        loadGroupMemberModel();
        return;
    }

    if (userId != m_targetId)
    {
        return;
    }

    m_isConnected = true;
    m_isUserOnline = true;
    updateSendButtonsEnabled(true);
    ui->liaotianInfo->append("【系统】已成功连接到 " + m_targetName);
    qDebug() << "[liaotianWin] 用户" << userId << "连接成功";
}

void liaotianWin::onUserDisconnected(int userId)
{
    if (m_isGroup)
    {
        updateGroupStatus();
        loadGroupMemberModel();
        return;
    }

    if (userId != m_targetId)
    {
        return;
    }

    m_isConnected = false;
    m_isUserOnline = false;
    updateSendButtonsEnabled(false);
    qDebug() << "[liaotianWin] 连接已断开";
    ui->liaotianInfo->append("【系统】连接已断开");
}

void liaotianWin::updateSendButtonsEnabled(bool enabled)
{
    ui->send->setEnabled(enabled);
    ui->sendFile->setEnabled(enabled);
    qDebug() << "[liaotianWin] 更新发送按钮状态:" << (enabled ? "启用" : "禁用");
}

void liaotianWin::onSendResult(int userId, bool success, const QString &errorMsg)
{
    if (userId != m_targetId)
    {
        return;
    }

    if (success)
    {
        ui->sendmsg->clear();
        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        qDebug() << "[liaotianWin] 消息发送成功";
    }
    else
    {
        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        QMessageBox::warning(this, "发送失败", "消息发送失败：" + errorMsg);
        qDebug() << "[liaotianWin] 消息发送失败:" << errorMsg;
    }
}

void liaotianWin::onReceiveResult(int userId, bool success, const QString &errorMsg)
{
    if (userId != m_targetId)
    {
        return;
    }

    if (success)
    {
        ui->sendmsg->clear();
        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        qDebug() << "[liaotianWin] 消息接收成功";
    }
    else
    {
        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        QMessageBox::warning(this, "接收失败", "消息接收失败：" + errorMsg);
        qDebug() << "[liaotianWin] 消息接收失败:" << errorMsg;
    }
}

void liaotianWin::onSendButtonClicked()
{
    QString message = ui->sendmsg->toPlainText().trimmed();
    if (message.isEmpty())
    {
        QMessageBox::warning(this, "提示", "请输入消息内容");
        return;
    }

    if (!m_isGroup && !m_isConnected && !m_userHome->isUserConnected(m_targetId))
    {
        QMessageBox::warning(this, "提示", "未连接到对方，无法发送消息");
        return;
    }

    QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString formattedMessage = "[" + currentTime + "] 我: \n" + message;

    if (m_userHome)
    {
        if (m_isGroup)
        {
            ui->liaotianInfo->append("");
            ui->liaotianInfo->append(formattedMessage);
            ui->liaotianInfo->append("");
            m_userHome->sendGroupMessage(m_targetId, message);
            qDebug() << "[liaotianWin] 通过UserHome发送群消息:" << message;
        }
        else
        {
            m_userHome->addMessageToCache(m_targetId, formattedMessage);
            ui->liaotianInfo->append("");
            ui->liaotianInfo->append(formattedMessage);
            ui->liaotianInfo->append("");
            m_userHome->sendMessageToUser(m_targetId, message, 0);
            qDebug() << "[liaotianWin] 通过UserHome发送消息:" << message;
        }
    }
}

void liaotianWin::onCancelButtonClicked()
{
    try
    {
        if (ui->progressBar->isVisible() && m_userHome)
        {
            if (m_isSendingFile)
            {
                qDebug() << "[liaotianWin] 点击取消，停止文件发送";
                m_userHome->cancelFileSend(m_targetId);
            }
            else
            {
                qDebug() << "[liaotianWin] 点击取消，停止文件接收";
                m_userHome->cancelFileReceive(m_targetId);
            }
        }
        else
        {
            ui->sendmsg->clear();
        }
    }
    catch (const std::exception &e)
    {
        qCritical() << "[liaotianWin] 取消文件异常:" << e.what();
    }
    catch (...)
    {
        qCritical() << "[liaotianWin] 取消文件未知异常";
    }
}

void liaotianWin::loadTargetInfo(int userId)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        ui->targetStatus->setText("离线");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT status, ip FROM userinfo WHERE id = :id");
    query.bindValue(":id", userId);

    if (query.exec() && query.next())
    {
        int status = query.value(0).toInt();
        ui->targetStatus->setText(status == 1 ? "在线" : "离线");
    }
    else
    {
        ui->targetStatus->setText("离线");
    }
}

bool liaotianWin::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->sendmsg && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            if (!(keyEvent->modifiers() & Qt::ShiftModifier))
            {
                onSendButtonClicked();
                return true;
            }
        }
    }
    if (obj == ui->dateEdit && event->type() == QEvent::MouseButtonPress)
    {
        onDateEditClicked();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void liaotianWin::onDateEditClicked()
{
    // 切换calendarWidget的显示/隐藏
    if (ui->calendarWidget->isVisible())
    {
        ui->calendarWidget->hide();
    }
    else
    {
        ui->calendarWidget->show();
    }
}

void liaotianWin::onCalendarSelectionChanged()
{
    // 获取选择的日期
    QDate date = ui->calendarWidget->selectedDate();

    // 隐藏calendarWidget
    ui->calendarWidget->hide();

    // 更新dateEdit显示选择的日期
    ui->dateEdit->setDate(date);

    if (!m_userHome)
    {
        return;
    }

    // 清空当前显示的内容
    ui->liaotianInfo->clear();

    // 从UserHome获取指定日期的历史消息
    QStringList messages = m_userHome->getMessagesForDate(m_targetId, date);

    if (messages.isEmpty())
    {
        ui->liaotianInfo->append("【系统】该日期没有历史消息");
    }
    else
    {
        // 从顶部开始插入消息
        for (const QString &msg : messages)
        {
            ui->liaotianInfo->append("");
            ui->liaotianInfo->append(msg);
            ui->liaotianInfo->append("");
        }
        ui->liaotianInfo->append("------------------------------以上是历史信息");
    }

    // 设置滚动条到顶部
    ui->liaotianInfo->verticalScrollBar()->setValue(0);
}

void liaotianWin::onSendFileButtonClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择要发送的文件");
    if (filePath.isEmpty())
    {
        return;
    }

    QFileInfo fileInfo(filePath);
    ui->progressBar->setMaximum(fileInfo.size());
    ui->progressBar->setValue(0);
    ui->progressBar->show();

    if (m_userHome)
    {
        m_isSendingFile = true;
        m_userHome->sendFileToUser(m_targetId, filePath);
        QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
        QString formattedMessage = "[" + currentTime + "] 我: 发送文件 " + fileInfo.fileName() + " (" +
                                   QString::number(fileInfo.size()) + " 字节)";
        ui->liaotianInfo->append(formattedMessage);
        m_userHome->addMessageToCache(m_targetId, formattedMessage);
    }
}

void liaotianWin::onFileReceived(int userId, const QString &fileName, const QString &filePath)
{
    if (userId != m_targetId)
    {
        return;
    }

    m_isSendingFile = false;
    ui->progressBar->hide();
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(0);
}

void liaotianWin::onFileCancelled(int userId, const QString &fileName)
{
    try
    {
        if (!ui || userId != m_targetId)
        {
            return;
        }

        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        ui->progressBar->setMaximum(0);

        qDebug() << "[liaotianWin] 文件发送已取消:" << fileName;
    }
    catch (const std::exception &e)
    {
        qCritical() << "[liaotianWin] onFileCancelled异常:" << e.what();
    }
    catch (...)
    {
        qCritical() << "[liaotianWin] onFileCancelled未知异常";
    }
}

void liaotianWin::onFileReceiveCancelled(int userId, const QString &fileName)
{
    try
    {
        if (!ui || userId != m_targetId)
        {
            return;
        }

        m_isSendingFile = false;
        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        ui->progressBar->setMaximum(0);

        qDebug() << "[liaotianWin] 接收方取消文件接收:" << fileName;
    }
    catch (const std::exception &e)
    {
        qCritical() << "[liaotianWin] onFileReceiveCancelled异常:" << e.what();
    }
    catch (...)
    {
        qCritical() << "[liaotianWin] onFileReceiveCancelled未知异常";
    }
}

void liaotianWin::onMediaFileAdded(int userId, const QString &filePath)
{
    if (userId == m_targetId)
    {
        refreshMediaPlayer();
    }
}

void liaotianWin::onFileProgress(int userId, qint64 bytesSent, qint64 totalBytes)
{
    if (userId != m_targetId)
    {
        return;
    }

    // 当收到初始进度（bytesSent=0）时，强制重置并显示进度条
    if (bytesSent == 0 && totalBytes > 0)
    {
        ui->progressBar->setMaximum(totalBytes);
        ui->progressBar->setValue(0);
        ui->progressBar->show();
        ui->progressBar->raise();
    }
    else
    {
        ui->progressBar->setValue(bytesSent);
    }

    if (bytesSent >= totalBytes && totalBytes > 0)
    {
        ui->progressBar->hide();
        ui->progressBar->setValue(0);
        ui->progressBar->setMaximum(0);
    }
}

QString liaotianWin::getMediaPlayerTableName() { return QString("QMediaPlayer%1").arg(curUserInfo.id); }

void liaotianWin::initMediaPlayerTable()
{
    if (m_isGroup)
    {
        qDebug() << "[liaotianWin] 群聊模式，跳过媒体播放器表初始化";
        return;
    }

    QString tableName = getMediaPlayerTableName();

    QSqlQuery query;
    QString createSql = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "targetId INTEGER, "
                                "url TEXT)")
                            .arg(tableName);

    if (query.exec(createSql))
    {
        qDebug() << "[liaotianWin] 媒体播放器表创建成功或已存在:" << tableName;
    }
    else
    {
        qDebug() << "[liaotianWin] 创建媒体播放器表失败:" << query.lastError().text();
    }

    m_mediaModel = new MediaUrlModel(this);
    loadMediaPlayerData();

    if (ui->QMediaPlayer)
    {
        ui->QMediaPlayer->setModel(m_mediaModel);
        m_mediaModel->setHeaderData(2, Qt::Horizontal, "历史接收到的文件");

        ui->QMediaPlayer->setColumnHidden(0, true);
        ui->QMediaPlayer->setColumnHidden(1, true);

        ui->QMediaPlayer->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    }
}

void liaotianWin::loadMediaPlayerData()
{
    if (!m_mediaModel)
    {
        return;
    }

    if (m_isGroup)
    {
        return;
    }

    QString tableName = getMediaPlayerTableName();

    QString selectSql = QString("SELECT * FROM %1 WHERE targetId = %2").arg(tableName).arg(m_targetId);
    m_mediaModel->setQuery(selectSql);

    if (m_mediaModel->lastError().isValid())
    {
        qDebug() << "[liaotianWin] 加载媒体播放器数据失败:" << m_mediaModel->lastError().text();
    }
    else
    {
        qDebug() << "[liaotianWin] 媒体播放器数据加载成功:" << tableName;
    }
}

void liaotianWin::refreshMediaPlayer()
{
    if (m_mediaModel)
    {
        loadMediaPlayerData();
        qDebug() << "[liaotianWin] 媒体播放器数据已刷新";
    }
}

void liaotianWin::onMediaPlayerClicked(const QModelIndex &index)
{
    if (!index.isValid() || !m_mediaModel)
    {
        return;
    }

    // 使用 EditRole 获取数据库中的原始 url 值，而不是显示数据
    QString filePath = m_mediaModel->data(m_mediaModel->index(index.row(), 2), Qt::EditRole).toString();

    if (filePath.isEmpty())
    {
        return;
    }

    QString fullPath = QDir::currentPath() + "/" + filePath;

    qDebug() << "[liaotianWin] 当前路径:" << QDir::currentPath();
    qDebug() << "[liaotianWin] 数据库路径:" << filePath;
    qDebug() << "[liaotianWin] 完整路径:" << fullPath;
    qDebug() << "[liaotianWin] 文件存在:" << QFile::exists(fullPath);

    if (!QFile::exists(fullPath))
    {
        qDebug() << "[liaotianWin] 文件不存在!";
        return;
    }

    if (m_lastClickedFile == fullPath)
    {
        if (m_mediaPlayer->state() == QMediaPlayer::PlayingState)
        {
            m_mediaPlayer->pause();
            qDebug() << "[liaotianWin] 暂停播放";
        }
        else if (m_mediaPlayer->state() == QMediaPlayer::PausedState)
        {
            m_mediaPlayer->play();
            qDebug() << "[liaotianWin] 继续播放";
        }
    }
    else
    {
        if (m_mediaPlayer->state() == QMediaPlayer::PlayingState || m_mediaPlayer->state() == QMediaPlayer::PausedState)
        {
            m_mediaPlayer->stop();
        }

        m_mediaPlayer->setMedia(QUrl::fromLocalFile(fullPath));
        m_mediaPlayer->setVolume(50);
        m_mediaPlayer->play();
        m_currentPlayingFile = fullPath;
        m_lastClickedFile = fullPath;
        qDebug() << "[liaotianWin] 开始播放:" << fullPath;
    }
}

void liaotianWin::onMediaPlayerDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid() || !m_mediaModel)
    {
        return;
    }

    QString filePath = m_mediaModel->data(m_mediaModel->index(index.row(), 2), Qt::EditRole).toString();

    if (filePath.isEmpty())
    {
        return;
    }

    QString fullPath = QDir::currentPath() + "/" + filePath;

    if (!QFile::exists(fullPath))
    {
        qDebug() << "[liaotianWin] 文件不存在!";
        return;
    }

    QString fileName = QFileInfo(fullPath).fileName();

    try
    {
        // 停止聊天窗口内置的播放器
        if (m_mediaPlayer->state() == QMediaPlayer::PlayingState || m_mediaPlayer->state() == QMediaPlayer::PausedState)
        {
            m_mediaPlayer->stop();
            m_currentPlayingFile = "";
            qDebug() << "[liaotianWin] 已停止内置播放器";
        }

        if (!m_mediaPlayerWindow)
        {
            m_mediaPlayerWindow = new Media();
        }

        m_mediaPlayerWindow->show();
        m_mediaPlayerWindow->raise();
        m_mediaPlayerWindow->activateWindow();

        m_mediaPlayerWindow->playMedia(fileName, fullPath);
    }
    catch (const std::exception &e)
    {
        qCritical() << "[liaotianWin] 打开媒体播放器异常:" << e.what();

        ::updateUserOfflineStatus("[liaotianWin] 数据库状态更新成功（异常处理）：", "[liaotianWin] 用户状态更新失败！");

        QMessageBox::critical(this, "异常", "打开媒体播放器时发生异常：" + QString(e.what()));
    }
    catch (...)
    {
        qCritical() << "[liaotianWin] 打开媒体播放器未知异常";

        ::updateUserOfflineStatus("[liaotianWin] 数据库状态更新成功（异常处理）：", "[liaotianWin] 用户状态更新失败！");

        QMessageBox::critical(this, "异常", "打开媒体播放器时发生未知异常");
    }
}

void liaotianWin::updateGroupStatus()
{
    if (!m_isGroup || !m_userHome)
    {
        return;
    }

    int online = m_userHome->getGroupOnlineCount(m_targetId);
    int total = m_userHome->getGroupTotalCount(m_targetId);

    QString statusText = QString("在线人数: %1 / 总人数: %2").arg(online).arg(total);
    ui->targetStatus->setText(statusText);
    qDebug() << "[liaotianWin] 群聊状态已更新:" << statusText;
}

void liaotianWin::loadGroupMemberModel()
{
    if (!m_isGroup || !ui->QMediaPlayer)
    {
        return;
    }

    if (!m_groupMemberModel)
    {
        m_groupMemberModel = new QStandardItemModel(this);
        m_groupMemberModel->setColumnCount(1);
        m_groupMemberModel->setHeaderData(0, Qt::Horizontal, "在线群成员");
        ui->QMediaPlayer->setModel(m_groupMemberModel);
        ui->QMediaPlayer->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }
    else
    {
        m_groupMemberModel->clear();
        m_groupMemberModel->setColumnCount(1);
        m_groupMemberModel->setHeaderData(0, Qt::Horizontal, "在线群成员");
        ui->QMediaPlayer->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT nicheng FROM userinfo WHERE status = 1 AND username IS NOT NULL AND username != '' ORDER BY nicheng");

    int row = 0;
    if (query.exec())
    {
        while (query.next())
        {
            QString nickName = query.value(0).toString();
            m_groupMemberModel->setItem(row, 0, new QStandardItem(nickName));
            row++;
        }
    }

    qDebug() << "[liaotianWin] 群成员列表已加载，共" << row << "人";
}

liaotianWin::~liaotianWin()
{
    if (m_mediaPlayer)
    {
        m_mediaPlayer->stop();
    }
    delete m_mediaPlayerWindow;
    delete ui;
}
