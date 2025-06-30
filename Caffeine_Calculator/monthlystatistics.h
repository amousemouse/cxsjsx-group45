////#ifndef MONTHLYSTATISTICS_H
////#define MONTHLYSTATISTICS_H

////#include <QWidget>
////#include <QDate>
////#include <QMap>
////#include "dayinputdialog.h"

////QT_BEGIN_NAMESPACE
////namespace Ui {
////class MonthlyStatistics;
////}
////QT_END_NAMESPACE

////class MonthlyStatistics : public QWidget
////{
////    Q_OBJECT

////public:
////    explicit MonthlyStatistics(QWidget *parent = nullptr);
////    ~MonthlyStatistics();

////private slots:
////    void onBackButtonClicked();
////    void onDayClicked(const QDate &date);

////private:
////    Ui::MonthlyStatistics *ui;
////    DayInputDialog *inputDialog;
////    QMap<QDate, double> dailyCaffeine;
////};

////#endif // MONTHLYSTATISTICS_H

//#ifndef MONTHLYSTATISTICS_H
//#define MONTHLYSTATISTICS_H

//#include <QMainWindow>
//#include <QPushButton>
//#include <QMap>
//#include <QPair>
//#include <QDate>

//class QCalendarWidget;
//class DayInputDialog;

//class MonthlyStatistics : public QMainWindow {
//    Q_OBJECT
//public:
//    explicit MonthlyStatistics(QWidget *parent = nullptr);
//    ~MonthlyStatistics();
//    QMap<QString, double> getDrinkTypes() const { return drinkCaffeine; }

//    void updateCalendarColors();
//    void showAdvice();

//private slots:
//    void onBackButtonClicked();
//    void onDayClicked(const QDate &date);
//    void onRecordsUpdated(const QDate &date, const QList<QPair<QString, int>>& records);
//    void onAdviceButtonClicked();

//signals:
//    void windowClosed();

//private:
//    QCalendarWidget *calendar;
//    QPushButton *adviceButton;
//    QMap<QDate, QList<QPair<QString, int>>> dailyRecords;
//    QMap<QString, double> drinkCaffeine; // 饮品咖啡因含量
//    QString currentUser;
//    void loadUserData();
//    void saveUserData();

//    double calculateDayCaffeine(const QDate &date);
//    double calculateMonthCaffeine();
//};

//#endif // MONTHLYSTATISTICS_H

#ifndef MONTHLYSTATISTICS_H
#define MONTHLYSTATISTICS_H

#include <QMainWindow>
#include <QMap>
#include <QPair>
#include <QDate>
#include <QCalendarWidget>
#include <QPushButton>

class DayInputDialog;

struct Drink
{
    QString name;
    int count;
};
struct JsonItem
{
    QString time;
    QList<Drink> drinks;
};

struct JsonInfo
{
    QString userName;
    QList<JsonItem> items;
};

class MonthlyStatistics : public QMainWindow {
    Q_OBJECT
public:
    explicit MonthlyStatistics(QWidget *parent = nullptr);

    // 用户管理
    void setCurrentUser(const QString &username);

    // 数据获取
    QMap<QString, double> getDrinkTypes() const { return drinkCaffeine; }

    // 计算功能
    double calculateDayCaffeine(const QDate &date);
    double calculateMonthCaffeine();

    // 界面更新
    void updateCalendarColors();
    void showAdvice();

    QMap<QString,JsonInfo> getDatas() const {return m_userData;}
    void setDatas(JsonInfo info);
    // 数据持久化
    void loadUserData();

signals:
    void windowClosed();

public slots:
    void onBackButtonClicked();
    void onDayClicked(const QDate &date);
    void onRecordsUpdated(const QDate &date, const QList<QPair<QString, int>>& records);
    void onAdviceButtonClicked();
    void loadDrinksFromFile();

private:

    void saveUserData();

    // UI组件
    QCalendarWidget *calendar;
    QPushButton *adviceButton;

    QMap<QString,JsonInfo> m_userData;
    // 数据存储
    QMap<QDate, QList<QPair<QString, int>>> dailyRecords; // 每日记录 <日期, <饮品名称, 数量>>
    QMap<QString, double> drinkCaffeine;                  // 饮品咖啡因含量 <饮品名称, 含量(mg)>
    QString currentUser;                                  // 当前用户名
};

#endif // MONTHLYSTATISTICS_H
