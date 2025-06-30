//#include "user.h"
//#include <QCryptographicHash>

//User::User(const QString& username, const QString& password)
//    : username(username) {
//    // 简单哈希处理，实际应用应该加盐
//    passwordHash = QCryptographicHash::hash(
//        password.toUtf8(),
//        QCryptographicHash::Sha256
//    ).toHex();
//}

//bool User::verifyPassword(const QString& password) const {
//    QByteArray hash = QCryptographicHash::hash(
//        password.toUtf8(),
//        QCryptographicHash::Sha256
//    ).toHex();
//    return hash == passwordHash;
//}

//void User::addDailyRecord(const QDate& date, const QList<QPair<QString, int>>& records) {
//    dailyRecords[date] = records;
//}

//QList<QPair<QString, int>> User::getDailyRecords(const QDate& date) const {
//    return dailyRecords.value(date);
//}

//double User::calculateMonthCaffeine(int year, int month) const {
//    double total = 0.0;
//    for (auto it = dailyRecords.begin(); it != dailyRecords.end(); ++it) {
//        if (it.key().year() == year && it.key().month() == month) {
//            for (const auto& record : it.value()) {
//                // 假设有全局饮品咖啡因数据
//                total += getDrinkCaffeine(record.first) * record.second;
//            }
//        }
//    }
//    return total;
//}

//QDataStream &operator<<(QDataStream &out, const User &user)
//{
//    out << user.username << user.passwordHash;
//    return out;
//}

//QDataStream &operator>>(QDataStream &in, User &user)
//{
//    in >> user.username >> user.passwordHash;
//    return in;
//}

#include "user.h"
#include <QJsonObject>
#include <QJsonArray>

User::User(const QString& username, const QString& password)
    : username(username), password(password)  // 存储明文密码
{
}

bool User::verifyPassword(const QString& password) const {
    return this->password == password;  // 直接比较明文密码
}

QString User::passwordHash() const {
    return password;  // 返回明文密码(虽然方法名是Hash，但按需求使用明文)
}

QString User::getpassword() const {
    return password;  // 返回明文密码
}

void User::addDailyRecord(const QDate& date, const QList<QPair<QString, int>>& records) {
    dailyRecords[date] = records;
}

QList<QPair<QString, int>> User::getDailyRecords(const QDate& date) const {
    return dailyRecords.value(date);
}

double User::calculateMonthCaffeine(int year, int month, const QMap<QString, double>& drinkCaffeine) const {
    double total = 0.0;
    for (auto it = dailyRecords.begin(); it != dailyRecords.end(); ++it) {
        if (it.key().year() == year && it.key().month() == month) {
            for (const auto& record : it.value()) {
                if (drinkCaffeine.contains(record.first)) {
                    total += drinkCaffeine[record.first] * record.second;
                }
            }
        }
    }
    return total;
}

QJsonObject User::toJson() const {
    QJsonObject obj;
    obj["username"] = username;
    obj["password"] = password;  // 存储明文密码

    // 转换每日记录为JSON
    QJsonObject recordsObj;
    for (auto it = dailyRecords.begin(); it != dailyRecords.end(); ++it) {
        QJsonArray dayRecords;
        for (const auto& record : it.value()) {
            QJsonObject drinkRecord;
            drinkRecord["drink"] = record.first;
            drinkRecord["count"] = record.second;
            dayRecords.append(drinkRecord);
        }
        recordsObj[it.key().toString("yyyy-MM-dd")] = dayRecords;
    }
    obj["records"] = recordsObj;

    return obj;
}

void User::fromJson(const QJsonObject& json) {
    username = json["username"].toString();
    password = json["password"].toString();  // 读取明文密码

    // 解析每日记录
    dailyRecords.clear();
    QJsonObject recordsObj = json["records"].toObject();
    for (auto it = recordsObj.begin(); it != recordsObj.end(); ++it) {
        QDate date = QDate::fromString(it.key(), "yyyy-MM-dd");
        if (date.isValid()) {
            QList<QPair<QString, int>> dayRecords;
            QJsonArray recordsArray = it->toArray();
            for (const QJsonValue& value : recordsArray) {
                QJsonObject record = value.toObject();
                dayRecords.append(qMakePair(
                    record["drink"].toString(),
                    record["count"].toInt()
                ));
            }
            dailyRecords[date] = dayRecords;
        }
    }
}

// 设置月度咖啡因目标
void User::setMonthlyCaffeineGoal(double goal) {
    monthlyCaffeineGoal = goal;
}

// 获取月度咖啡因目标
double User::getMonthlyCaffeineGoal() const {
    return monthlyCaffeineGoal;
}

void User::setUsername(const QString &newUsername) {
    username = newUsername;
}
