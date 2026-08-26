#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userhome.h"
#include <QCryptographicHash>

QString getMd5(QString str)
{
    QByteArray hashData = QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5);
    return hashData.toHex();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_selectedButton(NoSelection)
    , m_mibaoLayoutVisible(false)
{
    ui->setupUi(this);
    setWindowTitle("九玄聊天室");
    SQLite_init("./data.db");

    ui->username->setFocus();

    ui->username->installEventFilter(this);
    ui->password->installEventFilter(this);
    ui->inputmbwt->installEventFilter(this);
    ui->inputmbda->installEventFilter(this);
    
    updateButtonStyles();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        
        // 处理回车键
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            if (watched == ui->password) {
                if (m_selectedButton == RegisterButton) {
                    qDebug() << "[MainWindow] 密码框回车，选中注册按钮，触发注册";
                    on_userregister_clicked();
                    return true;
                } else if (m_selectedButton == LoginButton) {
                    qDebug() << "[MainWindow] 密码框回车，选中登录按钮，触发登录";
                    on_userlogin_clicked();
                    return true;
                } else {
                    qDebug() << "[MainWindow] 密码框回车，没有选中按钮，默认登录";
                    on_userlogin_clicked();
                    return true;
                }
            } else if (watched == ui->username) {
                qDebug() << "[MainWindow] 用户名输入框回车，切换到密码框";
                ui->password->setFocus();
                return true;
            } else if (watched == ui->inputmbwt) {
                qDebug() << "[MainWindow] 密保问题输入框回车，切换到密保答案输入框";
                ui->inputmbda->setFocus();
                return true;
            } else if (watched == ui->inputmbda) {
                qDebug() << "[MainWindow] 密保答案输入框回车，执行注册";
                on_userregister_clicked();
                return true;
            }
        }
        
        // 处理退格键在空密码框的情况
        if (watched == ui->password && keyEvent->key() == Qt::Key_Backspace && ui->password->text().isEmpty())
        {
            qDebug() << "[MainWindow] 密码框为空，按退格，切换到用户名框";
            ui->username->setFocus();
            return true;
        }
        
        // 处理上键
        if (keyEvent->key() == Qt::Key_Up) {
            if (watched == ui->inputmbwt) {
                qDebug() << "[MainWindow] 密保问题输入框按上，移动到密码框";
                ui->password->setFocus();
                return true;
            } else if (watched == ui->inputmbda) {
                qDebug() << "[MainWindow] 密保答案输入框按上，移动到密保问题输入框";
                ui->inputmbwt->setFocus();
                return true;
            } else {
                qDebug() << "[MainWindow] 按下上键，移动到用户名框";
                ui->username->setFocus();
                return true;
            }
        }
        
        // 处理下键
        if (keyEvent->key() == Qt::Key_Down) {
            if (watched == ui->password) {
                qDebug() << "[MainWindow] 密码框按下，移动到密保问题输入框";
                ui->inputmbwt->setFocus();
                return true;
            } else if (watched == ui->inputmbwt) {
                qDebug() << "[MainWindow] 密保问题输入框按下，移动到密保答案输入框";
                ui->inputmbda->setFocus();
                return true;
            } else {
                qDebug() << "[MainWindow] 按下下键，移动到密码框";
                ui->password->setFocus();
                return true;
            }
        }
        
        // 处理左键和右键选择按钮
        if (keyEvent->key() == Qt::Key_Left) {
            qDebug() << "[MainWindow] 按下左键，选中注册按钮";
            m_selectedButton = RegisterButton;
            updateButtonStyles();
            return true;
        }
        
        if (keyEvent->key() == Qt::Key_Right) {
            qDebug() << "[MainWindow] 按下右键，选中登录按钮";
            m_selectedButton = LoginButton;
            updateButtonStyles();
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

MainWindow::~MainWindow()
{
    DB.close();
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 注意：不要清理homeWindow！因为我们要让它继续运行
    // homeWindow 现在是独立窗口，有自己的 closeEvent 来处理退出
    homeWindow = nullptr;
    QMainWindow::closeEvent(event);
}

void MainWindow::SQLite_init(QString filename)
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(filename);

    if (!DB.open())
    {
        qDebug() << ">>> 数据库连接失败";
        exit(0);
    }
    qDebug() << ">>> 数据库连接成功";

    if (DB.isOpen())
    {
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT count(*) FROM sqlite_master WHERE type='table' AND name=:tableName");
        checkQuery.bindValue(":tableName", "userinfo");

        bool tableExists = false;
        if (checkQuery.exec() && checkQuery.next())
        {
            tableExists = (checkQuery.value(0).toInt() > 0);
        }

        QSqlQuery createQuery;
        QString sql = "CREATE TABLE IF NOT EXISTS userinfo ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT, "
                      "password TEXT, "
                      "ip TEXT, "
                      "touxiang BLOB, "
                      "nicheng TEXT, "
                      "status INTEGER DEFAULT 0, "
                      "mibaowenti TEXT DEFAULT '', "
                      "mibaodaan TEXT DEFAULT ''"
                      ");";

        if (createQuery.exec(sql))
        {
            if (tableExists)
            {
                qDebug() << ">>> userinfo 表已存在，无需创建。";
            }
            else
            {
                qDebug() << ">>> userinfo 表刚刚创建成功！";
            }
        }
        else
        {
            qDebug() << ">>> 控制台错误：创建表失败！" << createQuery.lastError().text();
            return;
        }

        QSqlQuery dataCheckQuery("SELECT count(*) FROM userinfo");
        int recordCount = 0;
        if (dataCheckQuery.exec() && dataCheckQuery.next())
        {
            recordCount = dataCheckQuery.value(0).toInt();
        }

        if (recordCount == 0)
        {
            qDebug() << ">>> 检测到表中无数据，正在插入默认管理员账号...";

            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO userinfo (username, password, ip, touxiang, nicheng) "
                                "VALUES (:username, :password, :ip, :touxiang, :nicheng)");

            insertQuery.bindValue(":username", "admin");
            insertQuery.bindValue(":password", getMd5("1234"));
            insertQuery.bindValue(":ip", "");
            insertQuery.bindValue(":touxiang", QByteArray());
            insertQuery.bindValue(":nicheng", "初始用户");

            if (insertQuery.exec())
            {
                qDebug() << ">>> 默认数据插入成功！(ID:1, admin)";
            }
            else
            {
                qDebug() << ">>> 默认数据插入失败：" << insertQuery.lastError().text();
            }
        }
        else
        {
            qDebug() << ">>> 表中已有" << recordCount << "条数据";

            QSqlQuery query("SELECT id, username, password, nicheng, ip FROM userinfo");

            qDebug() << "ID"
                     << "用户名"
                     << "密码(MD5)"
                     << "昵称"
                     << "IP";

            while (query.next())
            {
                int id = query.value("id").toInt();
                QString user = query.value("username").toString();
                QString pwd = query.value("password").toString();
                QString name = query.value("nicheng").toString();
                QString ip = query.value("ip").toString();

                qDebug() << id << "\t" << user << "\t" << pwd << "\t" << name << "\t" << ip;
            }
        }
    }
}

bool MainWindow::SQLite_query(QString sql, QString msg)
{
    qDebug() << sql;
    QSqlQuery query;
    bool flag = query.exec(sql);
    if (flag)
    {
        QMessageBox::information(this, "提示", msg + "成功");
    }
    else
    {
        QMessageBox::warning(this, "错误", msg + "失败：" + query.lastError().text());
    }
    return flag;
}

void MainWindow::on_userlogin_clicked()
{
    QString inputUsername = ui->username->text().trimmed();
    QString inputPassword = ui->password->text().trimmed();

    if (inputUsername.isEmpty() || inputPassword.isEmpty())
    {
        QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
        return;
    }

    QSqlQuery query;

    query.prepare("SELECT id, username, password, nicheng, ip, touxiang, status, mibaowenti FROM userinfo WHERE username = :name");
    query.bindValue(":name", inputUsername);

    if (!query.exec())
    {
        qDebug() << ">>> 数据库查询失败：" << query.lastError().text();
        QMessageBox::critical(this, "错误", "系统繁忙，请稍后再试！");
        return;
    }

    if (query.next())
    {
        QString dbPassword = query.value("password").toString();
        int currentStatus = query.value("status").toInt();
        
      

        QString encryptedInputPassword = getMd5(inputPassword);

        if (encryptedInputPassword == dbPassword)
        {


  // 检查用户是否已在线
        if (currentStatus == 1)
        {
            qDebug() << ">>> 用户" << inputUsername << "已在线，提示确认";
            QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                "重复登录提醒",
                QString("该账号 \"%1\" 已在其他地方登录！\n\n是否仍要在此处登录？\n（原登录将被强制下线）").arg(inputUsername),
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No
            );
            
            if (reply == QMessageBox::No)
            {
                qDebug() << ">>> 用户取消登录";
                return;
            }
            qDebug() << ">>> 用户确认登录，继续";
        }










            curUserInfo.id = query.value("id").toInt();
            curUserInfo.username = query.value("username").toString();
            curUserInfo.nicheng = query.value("nicheng").toString();
            curUserInfo.ip = query.value("ip").toString();
            curUserInfo.touxiang = query.value("touxiang").toByteArray();
            curUserInfo.status = 1;
            curUserInfo.mibaowenti = query.value("mibaowenti").toString();

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE userinfo SET status = 1 WHERE id = :id");
            updateQuery.bindValue(":id", curUserInfo.id);

            if (updateQuery.exec())
            {
                qDebug() << ">>> 数据库状态更新成功：用户" << curUserInfo.username << "已上线";
            }
            else
            {
                qDebug() << ">>> 用户状态更新失败！" << updateQuery.lastError().text();
            }

            qDebug() << ">>> 登录成功！欢迎用户：" << curUserInfo.nicheng;

            // 先创建并显示 UserHome 窗口
            homeWindow = new UserHome(nullptr);
            homeWindow->show();
            homeWindow->raise();
            homeWindow->activateWindow();
            
         
            // 现在关闭主窗口
            this->close();
        }
        else
        {
            QMessageBox::warning(this, "登录失败", "密码错误，请重新输入！");
        }
    }
    else
    {
        QMessageBox::warning(this, "登录失败", "该用户名未注册！");
    }
}

void MainWindow::on_userregister_clicked()
{
    if (!m_mibaoLayoutVisible)
    {
        m_mibaoLayoutVisible = true;
        ui->layoutWidget2->setVisible(true);
        ui->inputmbwt->setFocus();
        qDebug() << "[MainWindow] 注册按钮：显示密保区域";
        return;
    }

    QString regUsername = ui->username->text().trimmed();
    QString regPassword = ui->password->text().trimmed();
    QString mibaoWenti = ui->inputmbwt->text().trimmed();
    QString mibaoDaan = ui->inputmbda->text().trimmed();

    if (regUsername.isEmpty() || regPassword.isEmpty())
    {
        QMessageBox::warning(this, "提示", "注册信息不能为空！");
        return;
    }

    if (mibaoWenti.isEmpty() || mibaoDaan.isEmpty())
    {
        QMessageBox::warning(this, "提示", "密保问题和密保答案不能为空！");
        return;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT count(*) FROM userinfo WHERE username = :name");
    checkQuery.bindValue(":name", regUsername);

    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0)
    {
        QMessageBox::warning(this, "注册失败", "该用户名已被注册，请换一个！");
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO userinfo (username, password, ip, touxiang, nicheng, mibaowenti, mibaodaan) "
                        "VALUES (:username, :password, :ip, :touxiang, :nicheng, :mibaowenti, :mibaodaan)");

    insertQuery.bindValue(":username", regUsername);
    insertQuery.bindValue(":password", getMd5(regPassword));
    insertQuery.bindValue(":ip", "");
    insertQuery.bindValue(":touxiang", QByteArray());
    insertQuery.bindValue(":nicheng", regUsername);
    insertQuery.bindValue(":mibaowenti", mibaoWenti);
    insertQuery.bindValue(":mibaodaan", getMd5(mibaoDaan));

    if (insertQuery.exec())
    {
        int newUserId = insertQuery.lastInsertId().toInt();
        qDebug() << ">>> 新用户注册成功，ID:" << newUserId;
        
        QString tableName = QString("QMediaPlayer%1").arg(newUserId);
        QSqlQuery createMediaTableQuery;
        QString createSql = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    "targetId INTEGER, "
                                    "url TEXT)").arg(tableName);
        
        if (createMediaTableQuery.exec(createSql))
        {
            qDebug() << ">>> 已为新用户创建QMediaPlayer表:" << tableName;
        }
        else
        {
            qDebug() << ">>> 创建QMediaPlayer表失败:" << createMediaTableQuery.lastError().text();
        }
        
        QMessageBox::information(this, "注册成功", "注册成功！");
      
        ui->password->clear();
        ui->username->clear();
        ui->inputmbwt->clear();
        ui->inputmbda->clear();
        m_mibaoLayoutVisible = false;
        ui->layoutWidget2->setVisible(false);
    }
    else
    {
        QMessageBox::critical(this, "注册失败", "系统错误：" + insertQuery.lastError().text());
    }
}

void MainWindow::updateButtonStyles()
{
    QString normalStyle = "QPushButton { padding: 5px 15px; border: 1px solid #ccc; border-radius: 3px; }";
    QString selectedStyle = "QPushButton { padding: 5px 15px; border: 3px solid #2196F3; border-radius: 3px; background-color: #E3F2FD; font-weight: bold; }";
    
    if (m_selectedButton == RegisterButton) {
        ui->userregister->setStyleSheet(selectedStyle);
        ui->userlogin->setStyleSheet(normalStyle);
    } else if (m_selectedButton == LoginButton) {
        ui->userregister->setStyleSheet(normalStyle);
        ui->userlogin->setStyleSheet(selectedStyle);
    } else {
        ui->userregister->setStyleSheet(normalStyle);
        ui->userlogin->setStyleSheet(normalStyle);
    }
}
