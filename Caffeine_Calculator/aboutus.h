
#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QWidget>
#include <QMap>
#include <QDate>
#include <QMainWindow>
#include <QWidget>
#include "drinkselectiondialog.h"
#include "cafresultwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutUs;
}
QT_END_NAMESPACE

class AboutUs : public QMainWindow
{
    Q_OBJECT

public:
    explicit AboutUs(QWidget *parent = nullptr);
    ~AboutUs();

signals:
    void windowClosed();
    void handleAboutUsWindowClosed();


private slots:
    void onBackButtonClicked();


private:
    Ui::AboutUs *ui;
};

#endif // NEWORDERWINDOW_H
