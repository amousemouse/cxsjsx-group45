//#ifndef LOGINWINDOW_H
//#define LOGINWINDOW_H

//#include <QWidget>
//#include <QMap>
//#include "usermanager.h"

//class User;

//QT_BEGIN_NAMESPACE
//namespace Ui {
//class Loginwindow;
//}
//QT_END_NAMESPACE

//class Loginwindow : public QWidget{
//    Q_OBJECT
//public:
//    explicit Loginwindow(UserManager *parent = nullptr, QWidget *qparent = nullptr);
//    ~Loginwindow();

//signals:
//    void loginSuccess(const QString& username);

//private slots:
//    void onLoginClicked();
//    void onRegisterClicked();

//private:
//    Ui::Loginwindow *ui;
//    QMap<QString, User*> Users; // 用户名到用户的映射

//    void loadUsers();
//    void saveUsers();
//};

//#endif // LOGINWINDOW_H


#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "usermanager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow(UserManager *userManager, QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccess(const QString &username);

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    Ui::LoginWindow *ui;
    UserManager *m_userManager;  // 使用UserManager管理用户
};

#endif // LOGINWINDOW_H
