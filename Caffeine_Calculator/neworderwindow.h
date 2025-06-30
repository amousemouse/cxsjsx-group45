#ifndef NEWORDERWINDOW_H
#define NEWORDERWINDOW_H

#include <QWidget>
#include <QMap>
#include <QDate>
#include <QMainWindow>
#include "drinkselectiondialog.h"
#include "cafresultwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class NewOrderWindow;
}
QT_END_NAMESPACE

class NewOrderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewOrderWindow(QWidget *parent = nullptr);
    ~NewOrderWindow();

signals:
    void windowClosed();

private slots:
    void onBackButtonClicked();
    void onDrinkSelected(const QString &drinkName);
    void onCheckoutClicked();
    void handleDrinkSelection(const QString &drinkName, const QString &size, const QString &beanType, const QString &temp, int count);
    void onSaveButtonClicked();

private:
    Ui::NewOrderWindow *ui;
    DrinkSelectionDialog *selectionDialog;
    CafResultWindow *resultWindow;
    QMap<QString, double> drinkPrices;
    QMap<QString, double> drinkCaffeine;
    QList<QPair<QString, QPair<int, double>>> currentOrder;

    void setupDrinkData();
    double calculateTotalCaffeine();
};

#endif // NEWORDERWINDOW_H

