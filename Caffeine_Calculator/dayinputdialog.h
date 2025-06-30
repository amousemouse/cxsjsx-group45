//#ifndef DAYINPUTDIALOG_H
//#define DAYINPUTDIALOG_H

//#include <QDialog>
//#include <QDate>

//QT_BEGIN_NAMESPACE
//namespace Ui {
//class DayInputDialog;
//}
//QT_END_NAMESPACE

//class DayInputDialog : public QDialog
//{
//    Q_OBJECT

//public:
//    explicit DayInputDialog(QWidget *parent = nullptr);
//    ~DayInputDialog();

//    void setDate(const QDate &date);

//signals:
//    void caffeineEntered(double amount);

//private slots:
//    void onConfirmClicked();

//private:
//    Ui::DayInputDialog *ui;
//    QDate currentDate;
//};

//#endif // DAYINPUTDIALOG_H

#ifndef DAYINPUTDIALOG_H
#define DAYINPUTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QDate>

namespace Ui {
class DayInputDialog;
}

class DayInputDialog : public QDialog {
    Q_OBJECT
public:
    explicit DayInputDialog(QWidget *parent = nullptr);
    ~DayInputDialog();

    void setDate(const QDate &date);
    void setDrinkRecords(const QList<QPair<QString, int>>& records);
    QList<QPair<QString, int>> getDrinkRecords() const;

signals:
    void recordsUpdated(const QDate &date, const QList<QPair<QString, int>>& records);

private slots:
    void onAddDrinkClicked();
    void onRemoveDrinkClicked();
    void onSaveClicked();
    void updateCurrentDrink(const QString &newDrink);
    void initDrinkComboBox();

private:
    Ui::DayInputDialog *ui;
    QDate currentDate;
    QString currentDrink;
};

#endif // DAYINPUTDIALOG_H
