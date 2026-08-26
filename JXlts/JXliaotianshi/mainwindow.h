#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFile>
#include <QFileDialog>
#include <QSqlRecord>
#include <QSqlError>
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <QCloseEvent>
#include <QSqlQueryModel>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <QMap>
#include <QKeyEvent>
#include <QShortcut>
#include <QObject>
#include <QRunnable>
#include <QHostAddress>

class UserHome;

struct UserInfo
{
    int id;
    QString username;
    QString nicheng;
    QString ip;
    int status;
    QByteArray touxiang;
    QString mibaowenti;
};

extern UserInfo curUserInfo;

void updateUserOfflineStatus(const QString &successPrefix, const QString &failPrefix);
QString getMd5(QString str);

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SQLite_init(QString filename);
    bool SQLite_query(QString sql, QString msg = "操作");

    void SQLite_Table(QString sql);

  private slots:
    void on_userlogin_clicked();

    void on_userregister_clicked();

  private:
    Ui::MainWindow *ui;
    QSqlDatabase DB;
    UserHome *homeWindow;
    
    enum SelectedButton {
        NoSelection,
        RegisterButton,
        LoginButton
    };
    SelectedButton m_selectedButton;
    
    bool m_mibaoLayoutVisible;
    
    void updateButtonStyles();

protected:
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // MAINWINDOW_H
