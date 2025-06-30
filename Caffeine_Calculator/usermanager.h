////#ifndef USERMANAGER_H
////#define USERMANAGER_H

////#include <QObject>
////#include <QMap>
////#include <QString>
////#include "user.h"

////class UserManager : public QObject
////{
////    Q_OBJECT
////public:
////    explicit UserManager(QObject *parent = nullptr);

////    // 用户管理
////    bool registerUser(const QString &username, const QString &password);
////    bool login(const QString &username, const QString &password);
////    void logout();
////    User* currentUser() const;

////    // 数据持久化
////    bool loadUsers();
////    bool saveUsers();

////signals:
////    void loginSuccess();
////    void loginFailed(const QString &reason);

////private:
////    QMap<QString, User*> m_users;  // 用户名->用户对象
////    User* m_currentUser = nullptr; // 当前用户
////    QString m_dataPath = "users.dat";
////};

////#endif // USERMANAGER_H

//#ifndef USERMANAGER_H
//#define USERMANAGER_H

//#include <QObject>
//#include <QMap>
//#include <QString>
//#include "user.h"

//class UserManager : public QObject
//{
//    Q_OBJECT
//public:
//    explicit UserManager(QObject *parent = nullptr);

//    // 用户管理接口
//    bool registerUser(const QString &username, const QString &password);
//    bool login(const QString &username, const QString &password);
//    void logout();
//    User* currentUser() const;
//    QString getCurrentUsername() const;  // 新增方法，获取当前用户名

//    // 数据持久化接口
//    bool loadUsers();
//    bool saveUsers();

//signals:
//    void loginSuccess();
//    void loginFailed(const QString &reason);

//private:
//    // 初始化新用户数据文件
//    void initializeUserDataFile(const QString &username);

//    // 获取用户数据文件路径
//    QString getUserDataPath(const QString &username) const;

//private:
//    QMap<QString, User*> m_users;      // 用户名->用户对象映射
//    User* m_currentUser = nullptr;     // 当前登录用户指针
//    QString m_dataPath = "users.json"; // 用户数据存储路径(改为json格式)
//};

//#endif // USERMANAGER_H

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include "user.h"

class UserManager : public QObject
{
    Q_OBJECT
public:
    explicit UserManager(QObject *parent = nullptr);

    // 用户管理
    bool registerUser(const QString &username, const QString &password);
    bool login(const QString &username, const QString &password);
    void logout();
    User* currentUser() const;
    QString getCurrentUsername() const;
    bool changeUsername(const QString &oldUsername, const QString &newUsername);
    bool setUserMonthlyCaffeineGoal(const QString &username, double goal);
    double getUserMonthlyCaffeineGoal(const QString &username) const;
    // 数据持久化
    bool loadUsers();
    bool saveUsers();

signals:
    void loginSuccess();
    void loginFailed(const QString &reason);
    void usernameChangeSuccess();
    void usernameChangeFailed(const QString &reason);
    void goalUpdateSuccess();
    void goalUpdateFailed(const QString &reason);

private:
    void initializeUserDataFile(const QString &username);
    QString getUserDataPath(const QString &username) const;

private:
    QMap<QString, User*> m_users;  // 用户名->用户对象
    User* m_currentUser = nullptr; // 当前用户
    QString m_dataPath = "users.json"; // 改为JSON格式存储
};

#endif // USERMANAGER_H
