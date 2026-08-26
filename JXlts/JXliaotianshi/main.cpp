#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QMessageLogContext>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <csignal>
#include <cstdlib>
#include <iostream>

UserInfo curUserInfo;

void updateUserOfflineStatus(const QString &successPrefix, const QString &failPrefix)
{
    if (curUserInfo.id <= 0) {
        return;
    }
    
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        return;
    }
    
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE userinfo SET status = 0 WHERE id = :id");
    updateQuery.bindValue(":id", curUserInfo.id);
    
    if (updateQuery.exec()) {
        qDebug() << successPrefix << "用户" << curUserInfo.username << "已下线";
    } else {
        qDebug() << failPrefix << updateQuery.lastError().text();
    }
}

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "[%s] [DEBUG] %s (%s:%u, %s)\n", timestamp.toLocal8Bit().constData(), localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "[%s] [INFO] %s (%s:%u, %s)\n", timestamp.toLocal8Bit().constData(), localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "[%s] [WARNING] %s (%s:%u, %s)\n", timestamp.toLocal8Bit().constData(), localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "[%s] [CRITICAL] %s (%s:%u, %s)\n", timestamp.toLocal8Bit().constData(), localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "[%s] [FATAL] %s (%s:%u, %s)\n", timestamp.toLocal8Bit().constData(), localMsg.constData(), file, context.line, function);
        abort();
    }
}

void signalHandler(int signal)
{
    const char* signalName = "";
    switch(signal) {
        case SIGSEGV: signalName = "SIGSEGV (Segmentation Fault)"; break;
        case SIGINT: signalName = "SIGINT (Ctrl+C)"; break;
        case SIGTERM: signalName = "SIGTERM (Terminated)"; break;
        case SIGABRT: signalName = "SIGABRT (Aborted)"; break;
        case SIGFPE: signalName = "SIGFPE (Arithmetic Error)"; break;
        case SIGQUIT: signalName = "SIGQUIT (Ctrl+\\)"; break;
        case SIGHUP: signalName = "SIGHUP (Hangup/Terminal Closed)"; break;
        default: signalName = "Unknown Signal"; break;
    }
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    fprintf(stderr, "[%s] [FATAL ERROR] Received signal %d: %s\n", timestamp.toLocal8Bit().constData(), signal, signalName);
    fprintf(stderr, "[%s] Stack trace (if available):\n", timestamp.toLocal8Bit().constData());
    
    // 信号发生时更新用户状态为离线
    if (curUserInfo.id > 0) {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen()) {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE userinfo SET status = 0 WHERE id = :id");
            updateQuery.bindValue(":id", curUserInfo.id);
            if (updateQuery.exec()) {
                QString logMsg = QString("[%1] [SIGNAL] 数据库状态更新成功：用户%2已下线").arg(timestamp).arg(curUserInfo.username);
                fprintf(stderr, "%s\n", logMsg.toLocal8Bit().constData());
            } else {
                QString logMsg = QString("[%1] [SIGNAL] 用户状态更新失败！%2").arg(timestamp).arg(updateQuery.lastError().text());
                fprintf(stderr, "%s\n", logMsg.toLocal8Bit().constData());
            }
        }
    }
    
    std::exit(signal);
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageHandler);
    
    signal(SIGSEGV, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGQUIT, signalHandler);
    signal(SIGHUP, signalHandler);
    
    QApplication a(argc, argv);
    
    qDebug() << "程序启动";
    qDebug() << "Qt版本:" << QT_VERSION_STR;
    
    try {
        MainWindow w;
        w.show();
        int result = a.exec();
        
        // 正常退出时也更新状态为离线
        updateUserOfflineStatus(">>> 数据库状态更新成功：", ">>> 用户状态更新失败！");
        
        return result;
    } catch (const std::exception &e) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        fprintf(stderr, "[%s] [EXCEPTION] %s\n", timestamp.toLocal8Bit().constData(), e.what());
        
        // 异常时更新用户状态为离线
        updateUserOfflineStatus(">>> 数据库状态更新成功（异常退出）：", ">>> 用户状态更新失败！");
        
        return -1;
    } catch (...) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        fprintf(stderr, "[%s] [EXCEPTION] Unknown exception occurred\n", timestamp.toLocal8Bit().constData());
        
        // 异常时更新用户状态为离线
        updateUserOfflineStatus(">>> 数据库状态更新成功（异常退出）：", ">>> 用户状态更新失败！");
        
        return -2;
    }
}
