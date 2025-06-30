//#include "loginwindow.h"
//#include "user.h"
//#include "mainwindow.h"
//#include <QFile>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QMessageBox>
//#include <QPushButton>
//#include "ui_loginwindow.h"

//Loginwindow::Loginwindow(UserManager *parent, QWidget *qparent) :
//    QWidget(qparent),
//    ui(new Ui::Loginwindow),
//{
//    ui->setupUi(this);
//    loadUsers();

//    connect(ui->loginButton, &QPushButton::clicked, this, &Loginwindow::onLoginClicked);
//    connect(ui->registerButton, &QPushButton::clicked, this, &Loginwindow::onRegisterClicked);
//}

//void Loginwindow::onLoginClicked() {
//    QString username = ui->usernameEdit->text();
//    QString password = ui->passwordEdit->text();

//    if (Users.contains(username) && Users[username]->verifyPassword(password)) {
//        emit loginSuccess(username);
//        this->hide();
//    } else {
//        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
//    }
//}

//void Loginwindow::onRegisterClicked() {
//    QString username = ui->usernameEdit->text();
//    QString password = ui->passwordEdit->text();

//    if (Users.contains(username)) {
//        QMessageBox::warning(this, "注册失败", "用户名已存在");
//    } else {
//        Users[username] = new User(username, password);
//        saveUsers();
//        QMessageBox::information(this, "注册成功", "账号已创建");
//    }
//}

//void Loginwindow::loadUsers() {
//    QFile file("users.json");
//    if (file.open(QIODevice::ReadOnly)) {
//        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
//        QJsonObject obj = doc.object();

//        for (const QString& username : obj.keys()) {
//            QString password = obj[username].toString();
//            Users[username] = new User(username, password);
//        }
//    }
//}

//void Loginwindow::saveUsers() {
//    QJsonObject obj;
//    for (const QString& username : Users.keys()) {
//        // 注意：实际应用中应该只存储哈希值
//        obj[username] = Users[username]->getPasswordHash();
//    }

//    QFile file("users.json");
//    if (file.open(QIODevice::WriteOnly)) {
//        file.write(QJsonDocument(obj).toJson());
//    }
//}

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>

QString g_curUsername;
LoginWindow::LoginWindow(UserManager *userManager, QWidget *parent) :
    QWidget(parent),
    m_userManager(userManager),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("咖啡因计算器");
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(m_userManager, &UserManager::loginFailed, this, [this](const QString &error) {
            QString title = "登录失败";
            QString message;

            if (error == "用户不存在") {
                message = "用户不存在！\n请检查输入或注册新用户。";
            } else if (error == "密码错误") {
                message = "密码错误！\n请重新输入";
            } else if (error == "用户名已存在"){
                title="注册失败";
                message="用户名已存在！\n请更换用户名";
            }
            QMessageBox::critical(this, title, message, QMessageBox::Ok);
        });
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);
}

void LoginWindow::onLoginClicked() {
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    ui->passwordEdit->clear(); // 清空密码框
    m_userManager->login(username, password);
    if (m_userManager->login(username, password)) {
        g_curUsername  = username;
        emit loginSuccess(username);
        this->hide();
    }
}

void LoginWindow::onRegisterClicked() {
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (m_userManager->registerUser(username, password)) {
        QMessageBox::information(this, "注册成功", "账号已创建");
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
