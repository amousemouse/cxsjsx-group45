#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "usermanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class NewOrderWindow;
class MonthlyStatistics;
class AboutUs;
class My;
class ProfileWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setCurrentUser(const QString& username);
    explicit MainWindow(UserManager *parent = nullptr, QWidget *qparent = nullptr);
    ~MainWindow();

private slots:
    void onNewOrderClicked();
    void onMonthlyStatsClicked();
    void handleNewOrderWindowClosed();
    void onAboutUsClicked();
    void handleAboutUsWindowClosed();
    void onMyClicked();
    void handleMyWindowClosed();
    void showUserProfile();
    void updateProfileDisplay();
    void handleMonthlyStatsWindowClosed();
    void slotOk();
    void slotRead();

private:
    Ui::MainWindow *ui;
    NewOrderWindow *newOrderWindow;
    MonthlyStatistics *monthlyStatsWindow;
    AboutUs *aboutUsWindow;
    My *myWindow;
    QString currentUser;
    UserManager* userManager;
    MonthlyStatistics* monthlyStatistics = nullptr;
    QWidget *profileWindow = nullptr;
    QLabel *userLabel = nullptr;
};
#endif // MAINWINDOW_H
