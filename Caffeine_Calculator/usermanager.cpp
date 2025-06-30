////#include "usermanager.h"
////#include <QFile>
////#include <QDataStream>
////#include <QCryptographicHash>

////UserManager::UserManager(QObject *parent) : QObject(parent)
////{
////    loadUsers();
////}

////bool UserManager::registerUser(const QString &username, const QString &password)
////{
////    if (m_users.contains(username)) {
////        emit loginFailed("用户名已存在");
////        return false;
////    }

////    User *newUser = new User(username, password);
////    m_users.insert(username, newUser);
////    saveUsers();
////    return true;
////}

////bool UserManager::login(const QString &username, const QString &password)
////{
////    if (!m_users.contains(username)) {
////        emit loginFailed("用户不存在");
////        return false;
////    }

////    User *user = m_users.value(username);
////    if (user->verifyPassword(password)) {
////        m_currentUser = user;
////        emit loginSuccess();
////        return true;
////    }

////    emit loginFailed("密码错误");
////    return false;
////}

////void UserManager::logout()
////{
////    m_currentUser = nullptr;
////}

////User* UserManager::currentUser() const
////{
////    return m_currentUser;
////}

////bool UserManager::loadUsers()
////{
////    QFile file(m_dataPath);
////    if (!file.open(QIODevice::ReadOnly))
////        return false;

////    QDataStream in(&file);
////    in >> m_users;
////    file.close();
////    return true;
////}

////bool UserManager::saveUsers()
////{
////    QFile file(m_dataPath);
////    if (!file.open(QIODevice::WriteOnly))
////        return false;

////    QDataStream out(&file);
////    out << m_users;
////    file.close();
////    return true;
////}

//#include "usermanager.h"
//#include <QFile>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>

//UserManager::UserManager(QObject *parent) : QObject(parent), m_dataPath("users.json")
//{
//    loadUsers();
//}

//bool UserManager::registerUser(const QString &username, const QString &password)
//{
//    if (m_users.contains(username)) {
//        emit loginFailed("用户名已存在");
//        return false;
//    }

//    User *newUser = new User(username, password);
//    m_users.insert(username, newUser);

//    // Create empty data file for the new user
//    initializeUserDataFile(username);

//    saveUsers();
//    return true;
//}

//bool UserManager::login(const QString &username, const QString &password)
//{
//    if (!m_users.contains(username)) {
//        emit loginFailed("用户不存在");
//        return false;
//    }

//    User *user = m_users.value(username);
//    if (user->verifyPassword(password)) {
//        m_currentUser = user;
//        emit loginSuccess();
//        return true;
//    }

//    emit loginFailed("密码错误");
//    return false;
//}

//void UserManager::logout()
//{
//    m_currentUser = nullptr;
//}

//User* UserManager::currentUser() const
//{
//    return m_currentUser;
//}

//bool UserManager::loadUsers()
//{
//    QFile file(m_dataPath);
//    if (!file.open(QIODevice::ReadOnly)) {
//        // File doesn't exist yet - that's okay
//        return true;
//    }

//    QByteArray data = file.readAll();
//    file.close();

//    QJsonDocument doc = QJsonDocument::fromJson(data);
//    if (doc.isNull()) {
//        return false;
//    }

//    QJsonObject root = doc.object();
//    m_users.clear();

//    for (auto it = root.begin(); it != root.end(); ++it) {
//        QString username = it.key();
//        QJsonObject userObj = it->toObject();

//        QString password = userObj["password"].toString();
//        m_users.insert(username, new User(username, password));
//    }

//    return true;
//}

//bool UserManager::saveUsers()
//{
//    QJsonObject root;

//    for (auto it = m_users.begin(); it != m_users.end(); ++it) {
//        QJsonObject userObj;
//        userObj["password"] = it.value()->password();
//        root[it.key()] = userObj;
//    }

//    QFile file(m_dataPath);
//    if (!file.open(QIODevice::WriteOnly)) {
//        return false;
//    }

//    file.write(QJsonDocument(root).toJson());
//    file.close();
//    return true;
//}

//void UserManager::initializeUserDataFile(const QString &username)
//{
//    // Create empty data structure for new user
//    QJsonObject root;
//    QJsonObject userData;
//    userData["records"] = QJsonObject(); // Empty records object
//    root[username] = userData;

//    // Save to coffee_data.json
//    QFile file("coffee_data.json");
//    if (file.open(QIODevice::ReadWrite)) {
//        // If file exists, merge with existing data
//        QByteArray existingData = file.readAll();
//        if (!existingData.isEmpty()) {
//            QJsonDocument existingDoc = QJsonDocument::fromJson(existingData);
//            if (!existingDoc.isNull()) {
//                QJsonObject existingRoot = existingDoc.object();
//                for (auto it = root.begin(); it != root.end(); ++it) {
//                    existingRoot[it.key()] = it.value();
//                }
//                root = existingRoot;
//            }
//        }

//        file.resize(0); // Clear the file
//        file.write(QJsonDocument(root).toJson());
//        file.close();
//    }
//}

//QString UserManager::getCurrentUsername() const
//{
//    return m_currentUser ? m_currentUser->username() : QString();
//}

#include "usermanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

UserManager::UserManager(QObject *parent) : QObject(parent), m_dataPath("users.json")
{
    loadUsers();
}

bool UserManager::registerUser(const QString &username, const QString &password)
{
    if (m_users.contains(username)) {
        emit loginFailed("用户名已存在");
        return false;
    }

    User *newUser = new User(username, password);
    m_users.insert(username, newUser);

    // Create empty data file for the new user
    initializeUserDataFile(username);

    saveUsers();
    return true;
}

bool UserManager::login(const QString &username, const QString &password)
{
    if (!m_users.contains(username)) {
        emit loginFailed("用户不存在");
        return false;
    }

    User *user = m_users.value(username);
    if (user->verifyPassword(password)) {
        m_currentUser = user;
        emit loginSuccess();
        return true;
    }

    emit loginFailed("密码错误");
    return false;
}

void UserManager::logout()
{
    m_currentUser = nullptr;
}

User* UserManager::currentUser() const
{
    return m_currentUser;
}

bool UserManager::loadUsers()
{
    QFile file(m_dataPath);
    if (!file.open(QIODevice::ReadOnly)) {
        // File doesn't exist yet - that's okay
        return true;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        return false;
    }

    QJsonObject root = doc.object();
    m_users.clear();

    for (auto it = root.begin(); it != root.end(); ++it) {
        QString username = it.key();
        QJsonObject userObj = it->toObject();

        QString password = userObj["password"].toString();
        m_users.insert(username, new User(username, password));
    }

    return true;
}

bool UserManager::saveUsers()
{
    QJsonObject root;

    for (auto it = m_users.begin(); it != m_users.end(); ++it) {
        QJsonObject userObj;
        userObj["password"] = it.value()->getpassword();
        root[it.key()] = userObj;
    }

    QFile file(m_dataPath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(QJsonDocument(root).toJson());
    file.close();
    return true;
}

void UserManager::initializeUserDataFile(const QString &username)
{
    // Create empty data structure for new user
    QJsonObject root;
    QJsonObject userData;
    userData["records"] = QJsonObject(); // Empty records object
    root[username] = userData;

    // Save to coffee_data.json
    QFile file("coffee_data.json");
    if (file.open(QIODevice::ReadWrite)) {
        // If file exists, merge with existing data
        QByteArray existingData = file.readAll();
        if (!existingData.isEmpty()) {
            QJsonDocument existingDoc = QJsonDocument::fromJson(existingData);
            if (!existingDoc.isNull()) {
                QJsonObject existingRoot = existingDoc.object();
                for (auto it = root.begin(); it != root.end(); ++it) {
                    existingRoot[it.key()] = it.value();
                }
                root = existingRoot;
            }
        }

        file.resize(0); // Clear the file
        file.write(QJsonDocument(root).toJson());
        file.close();
    }
}

QString UserManager::getCurrentUsername() const
{
    return m_currentUser ? m_currentUser->getusername() : QString();
}

bool UserManager::changeUsername(const QString &oldUsername, const QString &newUsername) {
    if (m_users.contains(newUsername)) {
        emit usernameChangeFailed("新用户名已存在");
        return false;
    }

    User *user = m_users.take(oldUsername); // 移除旧用户名
    user->setUsername(newUsername);        // 设置新用户名
    m_users.insert(newUsername, user);     // 重新插入

    // 如果当前登录用户是修改的用户，更新 currentUser
    if (m_currentUser && m_currentUser->getusername() == oldUsername) {
        m_currentUser = user;
    }

    // 保存到文件
    saveUsers();
    emit usernameChangeSuccess();
    return true;
}
// 设置用户月度咖啡因目标
bool UserManager::setUserMonthlyCaffeineGoal(const QString &username, double goal) {
    if (!m_users.contains(username)) {
        emit goalUpdateFailed("用户不存在");
        return false;
    }

    if (goal < 0) {
        emit goalUpdateFailed("目标值不能为负数");
        return false;
    }

    m_users[username]->setMonthlyCaffeineGoal(goal);
    saveUsers(); // 保存到文件
    emit goalUpdateSuccess();
    return true;
}

// 获取用户月度咖啡因目标
double UserManager::getUserMonthlyCaffeineGoal(const QString &username) const {
    if (!m_users.contains(username)) {
        return -1.0; // 返回 -1 表示用户不存在
    }
    return m_users[username]->getMonthlyCaffeineGoal();
}
