//#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "loginwindow.h"
//#include "ui_loginwindow.h"
//#include "user.h"
//#include "neworderwindow.h"
//#include "monthlystatistics.h"
//#include "ui_monthlystatistics.h"
//#include "monthlystatistics.h"
//#include "ui_monthlystatistics.h"
//#include "aboutus.h"
//#include "ui_aboutus.h"
//#include "My.h"
//#include "ui_My.h"
//#include <QDebug>
//#include <QVBoxLayout>
//#include <QLabel>



//MainWindow::MainWindow(UserManager *parent, QWidget *qparent)
//    : QMainWindow(qparent)
//    , ui(new Ui::MainWindow)
//    , newOrderWindow(nullptr)
//    , monthlyStatsWindow(nullptr)
//    , aboutUsWindow(nullptr)
//    , myWindow(nullptr)
//    , userManager(parent)
//{
//    ui->setupUi(this);
//    setWindowTitle("咖啡因计算器");
//    monthlyStatistics = new MonthlyStatistics(this);

//    connect(ui->newOrderButton, &QPushButton::clicked, this, &MainWindow::onNewOrderClicked);
//    connect(ui->monthlyStatsButton, &QPushButton::clicked, this, &MainWindow::onMonthlyStatsClicked);
//    connect(ui->mybutton, &QPushButton::clicked, this, &MainWindow::onMyClicked);
//    connect(ui->monthlyStatsButton_3, &QPushButton::clicked, this, &MainWindow::onAboutUsClicked);
//    connect(ui->profileButton, &QPushButton::clicked, this, &MainWindow::showUserProfile);
//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//    if(newOrderWindow) delete newOrderWindow;
//    if(monthlyStatsWindow) delete monthlyStatsWindow;
//}


//void MainWindow::onNewOrderClicked()
//{
//    if(!newOrderWindow) {
//        newOrderWindow = new NewOrderWindow(this);
//    }
//    this->hide();
//    newOrderWindow->show();

//}

//void MainWindow::onMonthlyStatsClicked()
//{
//    if(!monthlyStatsWindow) {
//        monthlyStatsWindow = new MonthlyStatistics(this);
//    }
//    this->hide();
//    monthlyStatsWindow->show();
//}

//void MainWindow::handleNewOrderWindowClosed()
//{
//    this->show();
//    newOrderWindow = nullptr; // 重置指针
//}

//void MainWindow::onAboutUsClicked()
//{
//    if(!aboutUsWindow) {  // 如果窗口不存在则创建
//        aboutUsWindow = new AboutUs(this);
//        // 连接关闭信号到处理函数（可选）
//        connect(aboutUsWindow, &AboutUs::windowClosed, this, &MainWindow::handleAboutUsWindowClosed);
//    }
//    this->hide();        // 隐藏主窗口
//    aboutUsWindow->show(); // 显示关于我们窗口
//}

//// 添加对应的关闭处理函数（与handleNewOrderWindowClosed类似）
//void MainWindow::handleAboutUsWindowClosed()
//{
//    this->show();         // 重新显示主窗口
//    aboutUsWindow = nullptr; // 重置指针
//}

//void MainWindow::onMyClicked()
//{
//    qDebug() << "=== 开始执行onMyClicked ===";
//    qDebug() << "myWindow指针:" << myWindow;

//    if(!myWindow) {
//        qDebug() << "创建新My窗口";
//        myWindow = new My(this);
//        if(!connect(myWindow, &My::windowClosed, this, &MainWindow::handleMyWindowClosed)) {
//            qDebug() << "信号连接失败!";
//        }
//    }

//    qDebug() << "隐藏主窗口";
//    this->hide();

//    qDebug() << "显示My窗口";
//    myWindow->show();

//    qDebug() << "=== onMyClicked执行完成 ===";
//}

//// 添加对应的关闭处理函数（与handleNewOrderWindowClosed类似）
//void MainWindow::handleMyWindowClosed()
//{
//    this->show();         // 重新显示主窗口
//    myWindow = nullptr; // 重置指针
//}

//void MainWindow::setCurrentUser(const QString& username) {
//    currentUser = username;

//    // 通知 monthlyStatistics 加载该用户的数据
//    if (monthlyStatistics) {
//        monthlyStatistics->setCurrentUser(username);
//    }

//    updateProfileDisplay();
//}

//void MainWindow::showUserProfile()
//{
//    if (!profileWindow) {
//        profileWindow = new QWidget(this);
//        profileWindow->setWindowTitle("我的档案");

//        QVBoxLayout *layout = new QVBoxLayout(profileWindow);

//        QLabel *titleLabel = new QLabel("用户信息", profileWindow);
//        titleLabel->setAlignment(Qt::AlignCenter);
//        titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

//        QLabel *userLabel = new QLabel(profileWindow);
//        userLabel->setAlignment(Qt::AlignCenter);
//        userLabel->setStyleSheet("font-size: 16px;");

//        QPushButton *closeButton = new QPushButton("关闭", profileWindow);

//        layout->addWidget(titleLabel);
//        layout->addWidget(userLabel);
//        layout->addWidget(closeButton);

//        connect(closeButton, &QPushButton::clicked, profileWindow, &QWidget::close);
//        connect(profileWindow, &QWidget::destroyed, this, [this]() {
//            profileWindow = nullptr;
//            this->show();
//        });

//        updateProfileDisplay(); // 更新显示
//    }

//    this->hide();
//    profileWindow->show();
//}

//// 更新档案显示
//void MainWindow::updateProfileDisplay()
//{
//    if (profileWindow) {
//        QLabel *userLabel = profileWindow->findChild<QLabel*>(Qt::FindDirectChildrenOnly);
//        if (userLabel) {
//            userLabel->setText("用户名: " + currentUser);
//        }
//    }
//}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "user.h"
#include "neworderwindow.h"
#include "monthlystatistics.h"
#include "ui_monthlystatistics.h"
#include "aboutus.h"
#include "ui_aboutus.h"
#include "My.h"
#include "ui_My.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

extern QString g_curUsername;

MainWindow::MainWindow(UserManager *parent, QWidget *qparent)
    : QMainWindow(qparent)
    , ui(new Ui::MainWindow)
    , newOrderWindow(nullptr)
    , monthlyStatsWindow(nullptr)
    , aboutUsWindow(nullptr)
    , myWindow(nullptr)
    , userManager(parent)
    , profileWindow(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("咖啡因计算器");
    monthlyStatistics = new MonthlyStatistics(this);

    // 连接按钮信号
    connect(ui->newOrderButton, &QPushButton::clicked, this, &MainWindow::onNewOrderClicked);
    connect(ui->monthlyStatsButton, &QPushButton::clicked, this, &MainWindow::onMonthlyStatsClicked);
    connect(ui->mybutton, &QPushButton::clicked, this, &MainWindow::onMyClicked);
    connect(ui->monthlyStatsButton_3, &QPushButton::clicked, this, &MainWindow::onAboutUsClicked);
    //connect(ui->pButton, &QPushButton::clicked, this, &MainWindow::showUserProfile);

    if(!monthlyStatsWindow) {
        monthlyStatsWindow = new MonthlyStatistics(this);
        monthlyStatsWindow->hide();
        connect(monthlyStatsWindow, &MonthlyStatistics::windowClosed, this, &MainWindow::handleMonthlyStatsWindowClosed);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if(newOrderWindow) delete newOrderWindow;
    if(monthlyStatsWindow) delete monthlyStatsWindow;
    if(aboutUsWindow) delete aboutUsWindow;
    if(myWindow) delete myWindow;
    if(profileWindow) delete profileWindow;
}

void MainWindow::onNewOrderClicked()
{
    if(!newOrderWindow) {
        newOrderWindow = new NewOrderWindow(this);
        connect(newOrderWindow, &NewOrderWindow::windowClosed, this, &MainWindow::handleNewOrderWindowClosed);
    }
    this->hide();
    newOrderWindow->show();
}

void MainWindow::handleNewOrderWindowClosed()
{
    this->show();
    newOrderWindow = nullptr;
}

void MainWindow::onMonthlyStatsClicked()
{
    this->hide();
    monthlyStatsWindow->show();
}

void MainWindow::handleMonthlyStatsWindowClosed()
{
    this->show();
    monthlyStatsWindow = nullptr;
}

void MainWindow::slotOk()
{
   JsonInfo data = myWindow->getData();
   monthlyStatsWindow->setDatas(data);
}

void MainWindow::slotRead()
{
    monthlyStatistics->loadUserData();
    QMap<QString,JsonInfo> infos = monthlyStatistics->getDatas();
    myWindow->setData(infos.value(g_curUsername));
}

void MainWindow::onAboutUsClicked()
{
    if(!aboutUsWindow) {
        aboutUsWindow = new AboutUs(this);
        connect(aboutUsWindow, &AboutUs::windowClosed, this, &MainWindow::handleAboutUsWindowClosed);
    }
    this->hide();
    aboutUsWindow->show();
}

void MainWindow::handleAboutUsWindowClosed()
{
    this->show();
    aboutUsWindow = nullptr;
}

void MainWindow::onMyClicked()
{
    qDebug() << "=== 开始执行onMyClicked ===";
    qDebug() << "myWindow指针:" << myWindow;

    if(!myWindow) {
        qDebug() << "创建新My窗口";
        myWindow = new My(this);
        if(!connect(myWindow, &My::windowClosed, this, &MainWindow::handleMyWindowClosed)) {
            qDebug() << "信号连接失败!";
        }

        connect(myWindow,&My::sigOk,this,&MainWindow::slotOk);
        connect(myWindow,&My::sigRead,this,&MainWindow::slotRead);
    }

    qDebug() << "隐藏主窗口";
    this->hide();

    qDebug() << "显示My窗口";
    //setCurrentUser(g_curUsername);
    QMap<QString,JsonInfo> infos = monthlyStatistics->getDatas();
    myWindow->setData(infos.value(g_curUsername));
    myWindow->show();

    qDebug() << "=== onMyClicked执行完成 ===";
}

void MainWindow::handleMyWindowClosed()
{
    this->show();
    myWindow = nullptr;
}

void MainWindow::setCurrentUser(const QString& username)
{
    currentUser = username;

    // 更新monthlyStatistics
    if (monthlyStatistics) {
        monthlyStatistics->setCurrentUser(username);
    }

    // 更新档案显示
    updateProfileDisplay();
}

void MainWindow::showUserProfile()
{
    if (!profileWindow) {
        profileWindow = new QWidget(this);
        profileWindow->setWindowTitle("我的档案");
        profileWindow->setFixedSize(300, 200);

        QVBoxLayout *layout = new QVBoxLayout(profileWindow);

        QLabel *titleLabel = new QLabel("用户信息", profileWindow);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

        userLabel = new QLabel(profileWindow); // 改为成员变量
        userLabel->setAlignment(Qt::AlignCenter);
        userLabel->setStyleSheet("font-size: 16px;");

        QPushButton *closeButton = new QPushButton("关闭", profileWindow);

        layout->addWidget(titleLabel);
        layout->addWidget(userLabel);
        layout->addWidget(closeButton);

        connect(closeButton, &QPushButton::clicked, profileWindow, &QWidget::close);
        connect(profileWindow, &QWidget::destroyed, this, [this]() {
            profileWindow = nullptr;
            this->show();
        });

        updateProfileDisplay();
    }

    this->hide();
    profileWindow->show();
}

void MainWindow::updateProfileDisplay()
{
    if (profileWindow && userLabel) {
        userLabel->setText("用户名: " + currentUser);
    }
}
