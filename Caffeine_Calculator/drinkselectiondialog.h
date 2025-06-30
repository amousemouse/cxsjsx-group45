#ifndef DRINKSELECTIONDIALOG_H
#define DRINKSELECTIONDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class DrinkSelectionDialog;
}
QT_END_NAMESPACE

class DrinkSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrinkSelectionDialog(QWidget *parent = nullptr);
    ~DrinkSelectionDialog();

    void setDrinkName(const QString &name);

signals:
    void drinkConfigured(const QString &drinkName, const QString &size,
                            const QString &beanType, const QString &temp, int count);

private slots:
    void onConfirmClicked();
private:
    Ui::DrinkSelectionDialog *ui;
    QString currentDrinkName;
};

#endif // DRINKSELECTIONDIALOG_H
