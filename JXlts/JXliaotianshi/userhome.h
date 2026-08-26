#ifndef USERHOME_H
#define USERHOME_H

#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QFile>
#include <QFileInfo>
#include <QDir>

class liaotianWin;

namespace Ui
{
class UserHome;
}

class UserHome : public QWidget
{
    Q_OBJECT

public:
    explicit UserHome(QWidget *parent = nullptr);
    ~UserHome();

    void sendMessageToUser(int userId, const QString &message, int messageType = 0);
    void sendGroupMessage(int groupId, const QString &message);
    void sendFileToUser(int userId, const QString &filePath);
    void cancelFileSend(int targetUserId);
    void cancelFileReceive(int targetUserId);
    liaotianWin *getChatWindow(int userId);
    bool isUserConnected(int userId);
    bool isGroup(int userId);
    int getGroupOnlineCount(int groupId);
    int getGroupTotalCount(int groupId);
    QStringList getCachedMessages(int userId);
    void registerSocket(int userId, QTcpSocket *socket);
    QStringList getMessagesForDate(int userId, const QDate &date);
    void addMessageToCache(int userId, const QString &message);
    void addMessageToCache(int userId, const QString &message, const QDate &date);
    void connectToUser(int userId);
    QString getGroupMembersString(int groupId);
    void initGroupChatFile();
    void saveGroupMessageToFile(const QString &message);
    QStringList loadGroupMessagesFromFile();
    void cleanupGroupChatFile();

signals:
    void messageReceived(int userId, const QString &message);
    void groupMessageReceived(int groupId, int senderId, const QString &senderName, const QString &message);
    void userConnected(int userId);
    void userDisconnected(int userId);
    void sendResult(int userId, bool success, const QString &errorMsg);
    void receiveResult(int userId, bool success, const QString &errorMsg);
    void fileReceived(int userId, const QString &fileName, const QString &filePath);
    void fileProgress(int userId, qint64 bytesSent, qint64 totalBytes);
    void mediaFileAdded(int userId, const QString &filePath);
    void fileCancelled(int userId, const QString &fileName);
    void fileReceiveCancelled(int userId, const QString &fileName);
    void groupStatusChanged(int groupId);

private slots:
    void onCheckStatusTimeout();
    void on_show_myname_returnPressed();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_updatapsw_clicked();
    void onListClicked(const QModelIndex &index);
    
    void onNewConnection();
    void onSocketReadyRead(QTcpSocket *socket);
    void onSocketDisconnected(QTcpSocket *socket);
    void onSocketError(QAbstractSocket::SocketError error);
    void onSocketBytesWritten(QTcpSocket *socket, qint64 bytes);
    void onApplicationQuit();

private:
    Ui::UserHome *ui;
    QTimer *statusTimer;
    QSqlQueryModel *model;
    QMap<int, liaotianWin *> m_chatWindows;
    
    bool m_mibaoLayoutVisible;
    
    QTcpServer *m_tcpServer;
    QMap<int, QTcpSocket*> m_activeSockets;
    QMap<QTcpSocket*, QByteArray> m_socketBuffers;
    
    QMap<int, int> m_lastUserStatus;
    int m_nextTempUserId;
    
    struct FileTransferState {
        QString fileName;
        qint64 fileSize;
        qint64 bytesReceived;
        QFile *file;
        int originalSenderId;
    };
    QMap<int, FileTransferState> m_receiveFileState;
    
    struct SendFileState {
        QString fileName;
        qint64 fileSize;
        qint64 bytesSent;
        QFile *file;
        int targetUserId;
        QString filePath;
        QString timestamp;
        bool cancelled;
    };
    QMap<QTcpSocket*, SendFileState> m_sendFileState;

    QString getChatFileName(int userId);
    QString getChatFileName(int userId, const QDate &date);
    void saveMessageToFile(int userId, const QString &message);
    void saveMessageToFile(int userId, const QString &message, const QDate &date);
    QStringList loadMessagesFromFile(int userId);
    QStringList loadMessagesFromFile(int userId, const QDate &date);
    void ensureChatDirectory();
    quint16 loadMyPort();
    QString getLocalIpAddress();
    void updateMyIpAndPort();
    QString getNickNameById(int userId);
    void showUserOnlineNotification(const QString &nickName);
    void showNewMessageNotification(const QString &nickName, const QString &content);
    void setupSocketSignals(QTcpSocket *socket);

protected:
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // USERHOME_H
