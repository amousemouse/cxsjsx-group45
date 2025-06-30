

#include "monthlystatistics.h"
#include "dayinputdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QTextCharFormat>
#include <QCalendarWidget>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ui_dayinputdialog.h"
#include "ui_monthlystatistics.h"
extern QString g_curUsername;
MonthlyStatistics::MonthlyStatistics(QWidget *parent) :
    QMainWindow(parent), currentUser("default")
{
    // 初始化饮品咖啡因含量
    drinkCaffeine  = {
        {"coffee", 150.0},
        {"milktea", 120.0},
        {"tea", 100.0},
    };

    loadDrinksFromFile();
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 创建返回按钮
    QPushButton *backButton = new QPushButton("返回主界面");
    connect(backButton, &QPushButton::clicked, this, &MonthlyStatistics::onBackButtonClicked);

    // 日历控件 - 设置固定大小
    calendar = new QCalendarWidget;
    calendar->setFixedSize(1400, 900);
//    calendar->move(-700, -500);

    adviceButton = new QPushButton(this);
    adviceButton->setFixedSize(300,200);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();
    //buttonLayout->addWidget(adviceButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(calendar, 0, Qt::AlignCenter);
    setCentralWidget(centralWidget);

    connect(calendar, &QCalendarWidget::clicked, this, &MonthlyStatistics::onDayClicked);
    //connect(adviceButton, &QPushButton::clicked, this, &MonthlyStatistics::onAdviceButtonClicked);

    // 加载当前用户数据
    loadUserData();
    updateCalendarColors();
}

void MonthlyStatistics::setCurrentUser(const QString &username)
{
    currentUser = username;
    dailyRecords.clear();
    loadUserData();
    updateCalendarColors();
}

void MonthlyStatistics::saveUserData()
{
    QFile file("coffee_data.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning() << "无法打开数据文件保存";
        return;
    }

//    // 读取现有数据
//    QByteArray existingData = file.readAll();
//    QJsonObject root;
//    if (!existingData.isEmpty()) {
//        QJsonDocument existingDoc = QJsonDocument::fromJson(existingData);
//        if (!existingDoc.isNull()) {
//            root = existingDoc.object();
//        }
//    }

//    // 更新当前用户数据
//    QJsonObject userData;
//    QJsonObject recordsObject;

//    for (auto it = dailyRecords.begin(); it != dailyRecords.end(); ++it) {
//        QJsonArray dayRecords;
//        for (const auto &record : it.value()) {
//            QJsonObject drinkRecord;
//            drinkRecord["drink"] = record.first;
//            drinkRecord["count"] = record.second;
//            dayRecords.append(drinkRecord);
//        }
//        recordsObject[it.key().toString("yyyy-MM-dd")] = dayRecords;
//    }

//    userData["records"] = recordsObject;
//    root[currentUser] = userData;

    QJsonObject rootObj;
    for(int i=0;i<m_userData.size();i++)
    {
        QJsonObject jsonObj;
        QString userName = m_userData.keys().at(i);
        JsonInfo info = m_userData.value(userName);
        QJsonArray recordsList;
        for(int j = 0;j<info.items.size();j++)
        {
            QJsonObject recordObj;
            JsonItem item = info.items.at(j);

            recordObj["time"] = item.time;

            QJsonArray drinkObjList;
            for(int k = 0;k<item.drinks.size();k++)
            {
                Drink drink = item.drinks.at(k);
                QJsonObject obj;
                obj.insert("name", drink.name);
                obj.insert("count", drink.count);
                drinkObjList.append(obj);
            }
            recordObj["drink"] = drinkObjList;
            recordsList.append(recordObj);
        }

        jsonObj["records"] = recordsList;
        rootObj[userName] = jsonObj;
    }

    QJsonDocument document;
    document.setObject(rootObj);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    file.write(byteArray);
    file.close();
}

void MonthlyStatistics::loadUserData()
{
    QFile file("coffee_data.json");
    if (!file.exists()) return;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray byte = file.readAll();
        QJsonParseError json_error;
        QJsonDocument doc(QJsonDocument::fromJson(byte, &json_error));
        file.close();
        QMap<QString,JsonInfo> infos;
        if(json_error.error == QJsonParseError::NoError)
        {
            JsonInfo info;
            QJsonObject jsonObj = doc.object();
            // 遍历所有用户
            for (auto userIt = jsonObj.begin(); userIt != jsonObj.end(); ++userIt) {
                QString userName = userIt.key();
                QJsonObject userData = userIt.value().toObject();
                info.userName = userName;
                qDebug() << "用户:" << userName;

                // 获取records数组
                QJsonArray recordsArray = userData["records"].toArray();

                // 遍历所有记录
                QList<JsonItem> items;
                for (const QJsonValue& recordValue : recordsArray) {
                    JsonItem item;
                    QJsonObject recordObj = recordValue.toObject();
                    QString date = recordObj["time"].toString();
                    QJsonArray drinksArray = recordObj["drink"].toArray();
                    item.time = date;

                    qDebug() << "  日期:" << date;

                    QList<Drink> drinks;
                    // 遍历当天的所有饮品记录
                    for (const QJsonValue& drinkValue : drinksArray) {
                        Drink drink;
                        QJsonObject drinkObj = drinkValue.toObject();
                        QString drinkName = drinkObj["name"].toString();
                        int count = drinkObj["count"].toInt();

                        drink.name = drinkName;
                        drink.count = count;
                        qDebug() << "    饮品:" << drinkName << "数量:" << count;
                        drinks.append(drink);
                    }
                    item.drinks = drinks;
                    items.append(item);
                }
                qDebug() << "-----------------------";
                info.items = items;
                infos.insert(info.userName,info);
            }

       }
        m_userData = infos;
        int z = 0;
        int a = z;
    } else {
        qWarning() << "无法打开数据文件读取";
    }

    //saveUserData();
}

void MonthlyStatistics::onBackButtonClicked()
{
    saveUserData(); // 关闭前保存
    if (parentWidget()) {
        parentWidget()->show();
    }
    emit windowClosed();
    this->hide();
}

void MonthlyStatistics::onDayClicked(const QDate &date) {
    DayInputDialog dialog(this);
    dialog.setDate(date);

    if (dailyRecords.contains(date)) {
        dialog.setDrinkRecords(dailyRecords[date]);
    }

    connect(&dialog, &DayInputDialog::recordsUpdated,
            this, &MonthlyStatistics::onRecordsUpdated, Qt::UniqueConnection);

    if (dialog.exec() == QDialog::Accepted) {
        saveUserData(); // 更新记录后保存
    }
}

void MonthlyStatistics::onRecordsUpdated(const QDate &date,
                                     const QList<QPair<QString, int>>& records) {
    qDebug() << "接收到记录:" << date.toString("yyyy-MM-dd");
    for (const auto& r : records) {
        qDebug() << " - " << r.first << "x" << r.second;
    }

    // 清空原有记录
    dailyRecords.remove(date);

    // 只添加含咖啡的记录
    QList<QPair<QString, int>> coffeeRecords;
    for (const auto& record : records) {
        qDebug() << "记录是:" << record.first << " " << record.second;
        if (drinkCaffeine.contains(record.first)) {
            qDebug() << "是咖啡饮品";
            coffeeRecords.append(record);
        }
    }

    if (!coffeeRecords.isEmpty()) {
        dailyRecords.insert(date, coffeeRecords);
    }

    updateCalendarColors();

    qDebug() << "更新记录:" << date.toString("yyyy-MM-dd")
             << "总咖啡因:" << calculateDayCaffeine(date);
}

void MonthlyStatistics::updateCalendarColors() {
    QTextCharFormat normalFormat, redFormat, yellowFormat, greenFormat;
    redFormat.setBackground(Qt::red);
    yellowFormat.setBackground(Qt::yellow);
    greenFormat.setBackground(Qt::green);

    QDate currentDate = QDate::currentDate();
    int year = currentDate.year();
    int month = currentDate.month();

    for (int day = 1; day <= currentDate.daysInMonth(); ++day) {
        QDate date(year, month, day);
        double caffeine = calculateDayCaffeine(date);

        if (dailyRecords.contains(date)) {
            if (caffeine > 200) {
                calendar->setDateTextFormat(date, redFormat);
            } else if (caffeine >= 100) {
                calendar->setDateTextFormat(date, yellowFormat);
            } else {
                calendar->setDateTextFormat(date, greenFormat);
            }
        } else {
            calendar->setDateTextFormat(date, greenFormat);
        }
    }
}

void MonthlyStatistics::setDatas(JsonInfo info)
{
    if(m_userData.keys().contains(g_curUsername))
    {
        m_userData.insert(g_curUsername,info);
        saveUserData();
    }
}

double MonthlyStatistics::calculateDayCaffeine(const QDate &date) {
    if (!dailyRecords.contains(date)) return 0.0;

    double total = 0.0;
    for (const auto& record : dailyRecords[date]) {
        if (drinkCaffeine.contains(record.first)) {
            total += drinkCaffeine[record.first] * record.second;
            qDebug() << "计算:" << record.first
                     << "x" << record.second
                     << "=" << drinkCaffeine[record.first] * record.second;
        }
    }
    return total;
}

double MonthlyStatistics::calculateMonthCaffeine() {
    double total = 0.0;
    for (const auto& date : dailyRecords.keys()) {
        total += calculateDayCaffeine(date);
    }
    return total;
}

void MonthlyStatistics::onAdviceButtonClicked() {
    double monthlyCaffeine = calculateMonthCaffeine();
    QString advice;

    if (monthlyCaffeine >= 1000) {
        advice = "⚠️ 警告：本月咖啡因已超过1000mg！请不要再喝咖啡了";
    } else if (monthlyCaffeine >= 500) {
        advice = "☕ 注意：本月咖啡因已过半(500mg)，请适量饮用";
    } else {
        advice = "👍 良好：本月咖啡因摄入较低(200mg以下)，请继续享受咖啡吧";
    }

    QMessageBox::information(this, "咖啡建议",
        QString("%1\n本月总摄入: %2mg").arg(advice).arg(monthlyCaffeine));
}

// dayinputdialog.cpp
DayInputDialog::~DayInputDialog() {
    // 清理资源（如果有）
}

void MonthlyStatistics::loadDrinksFromFile()
{
    QFile file("saved_names.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开饮品数据文件";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // 解析每行数据，格式："饮品名 咖啡因含量"
        QStringList parts = line.split(" ");
        if (parts.size() >= 2) {
            QString drinkName = parts[0];
            bool ok;
            double caffeine = parts[1].toDouble(&ok);

            if (ok && caffeine > 0) {
                drinkCaffeine[drinkName] = caffeine;
                qDebug() << "添加饮品:" << drinkName << "咖啡因含量:" << caffeine << "mg";
            }
        }
    }
    file.close();
}
