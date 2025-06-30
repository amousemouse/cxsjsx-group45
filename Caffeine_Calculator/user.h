//#ifndef USER_H
//#define USER_H

//#include <QString>
//#include <QMap>
//#include <QDate>
//#include <QList>
//#include <QPair>
//#include <QObject>

//class User : public QObject{
//    Q_OBJECT
//public:
//    User(const QString& username, const QString& password);

//    bool verifyPassword(const QString& password) const;
//    void addDailyRecord(const QDate& date, const QList<QPair<QString, int>>& records);
//    QList<QPair<QString, int>> getDailyRecords(const QDate& date) const;
//    double calculateMonthCaffeine(int year, int month) const;

//    QString getUsername() const { return username; }
//    QString getPasswordHash() const { return QString::fromUtf8(password);}

//    friend QDataStream &operator<<(QDataStream &out, const User &user);
//    friend QDataStream &operator>>(QDataStream &in, User &user);

//private:
//    QString username;
//    QByteArray password; // 实际应用中应该存储哈希值而非明文
//    QMap<QDate, QList<QPair<QString, int>>> dailyRecords;

//signals:
//};

//#endif // USER_H

#ifndef USER_H
#define USER_H

#include <QString>
#include <QMap>
#include <QDate>
#include <QList>
#include <QPair>
#include <QJsonObject>

class User
{
public:
    User(const QString& username, const QString& password);

    // 用户验证
    bool verifyPassword(const QString& password) const;
    QString getpassword() const;  // 返回明文密码
    QString passwordHash() const; // 保持接口兼容性，实际返回明文
    QString getusername() const { return username; }

    // 记录管理
    void addDailyRecord(const QDate& date, const QList<QPair<QString, int>>& records);
    void setUsername(const QString &newUsername);
    QList<QPair<QString, int>> getDailyRecords(const QDate& date) const;

    // 计算功能
    double calculateMonthCaffeine(int year, int month, const QMap<QString, double>& drinkCaffeine) const;
    void setMonthlyCaffeineGoal(double goal);
    double getMonthlyCaffeineGoal() const;

    // JSON序列化
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& json);

private:
    QString username;
    QString password;  // 明文存储密码
    QMap<QDate, QList<QPair<QString, int>>> dailyRecords;
    double monthlyCaffeineGoal = -1;
};

#endif // USER_H
