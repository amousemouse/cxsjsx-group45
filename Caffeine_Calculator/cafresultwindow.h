#ifndef CAFRESULTWINDOW_H
#define CAFRESULTWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CafResultWindow;
}
QT_END_NAMESPACE

class CafResultWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CafResultWindow(QWidget *parent = nullptr);
    ~CafResultWindow();

    void setCaffeineAmount(double amount);

private slots:
    void onBackButtonClicked();

private:
    Ui::CafResultWindow *ui;
};

#endif // CAFRESULTWINDOW_H
