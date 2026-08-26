#ifndef LIAOTIANWIN_H
#define LIAOTIANWIN_H

#include "mainwindow.h"
#include "media.h"
#include <QTcpSocket>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QStandardItemModel>

class MediaUrlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit MediaUrlModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {}
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DisplayRole && index.column() == 2)
        {
            QString url = QSqlQueryModel::data(index, role).toString();
            QFileInfo fileInfo(url);
            return fileInfo.fileName();
        }
        return QSqlQueryModel::data(index, role);
    }
};

class UserHome;

namespace Ui
{
class liaotianWin;
}

class liaotianWin : public QWidget
{
    Q_OBJECT

public:
    explicit liaotianWin(int targetId, const QString &targetName, UserHome *userHome, QWidget *parent = nullptr, bool isUserOnline = true, bool isGroup = false);
    ~liaotianWin();

public slots:
    void onMessageReceived(int userId, const QString &message);
    void onUserConnected(int userId);
    void onUserDisconnected(int userId);
    void onSendResult(int userId, bool success, const QString &errorMsg);
    void onReceiveResult(int userId, bool success, const QString &errorMsg);
    void onFileReceived(int userId, const QString &fileName, const QString &filePath);
    void onFileProgress(int userId, qint64 bytesSent, qint64 totalBytes);
    void onMediaFileAdded(int userId, const QString &filePath);
    void onFileCancelled(int userId, const QString &fileName);
    void onFileReceiveCancelled(int userId, const QString &fileName);
    void onGroupMessageReceived(int groupId, int senderId, const QString &senderName, const QString &message);

private slots:
    void onSendButtonClicked();
    void onCancelButtonClicked();
    void onSendFileButtonClicked();
    void onDateEditClicked();
    void onCalendarSelectionChanged();
    void onMediaPlayerClicked(const QModelIndex &index);
    void onMediaPlayerDoubleClicked(const QModelIndex &index);

private:
    Ui::liaotianWin *ui;
    int m_targetId;
    QString m_targetName;
    UserHome *m_userHome;
    bool m_isConnected;
    bool m_isUserOnline;
    bool m_isGroup;
    MediaUrlModel *m_mediaModel;
    QStandardItemModel *m_groupMemberModel;
    QMediaPlayer *m_mediaPlayer;
    QString m_currentPlayingFile;
    QString m_lastClickedFile;
    Media *m_mediaPlayerWindow;
    bool m_isSendingFile;

    void loadTargetInfo(int userId);
    void initMediaPlayerTable();
    void loadMediaPlayerData();
    QString getMediaPlayerTableName();
    void updateSendButtonsEnabled(bool enabled);
    void refreshMediaPlayer();
    void loadGroupMemberModel();
    void updateGroupStatus();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // LIAOTIANWIN_H
