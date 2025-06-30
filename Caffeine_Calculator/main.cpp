//#include "mainwindow.h"
//#include "cafresultwindow.h"
//#include "dayinputdialog.h"
//#include "drinkselectiondialog.h"
//#include "monthlystatistics.h"
//#include "neworderwindow.h"
//#include "ui_monthlystatistics.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

//#include "loginwindow.h"
//#include "mainwindow.h"
//#include <QApplication>
//#include <QMessageBox>

//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);

//    // 只创建登录窗口
//    Loginwindow loginWindow;

//    // 连接登录成功信号
//    QObject::connect(&loginWindow, &Loginwindow::loginSuccess,
//        [&](const QString& username) {
//            // 登录成功后才创建主窗口
//            MainWindow *mainWindow = new MainWindow();
//            mainWindow->setCurrentUser(username);
//            mainWindow->show();

//            // 关闭登录窗口
//            loginWindow.close();
//        });


//    loginWindow.show();
//    return a.exec();
//}

#include "loginwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "usermanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserManager userManager;
    LoginWindow loginWindow(&userManager);
    MainWindow mainWindow(&userManager);

    QObject::connect(&loginWindow, &LoginWindow::loginSuccess,
                     &mainWindow, &MainWindow::show);

    loginWindow.show();
    return a.exec();
}
