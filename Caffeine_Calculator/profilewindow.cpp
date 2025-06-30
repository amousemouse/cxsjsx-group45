#include "profilewindow.h"
#include "mainwindow.h"

void ProfileWindow::setUsername(const QString &username)
{
    usernameLabel->setText("用户名: " + username);
}

ProfileWindow::ProfileWindow(const QString &username, QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口属性
    setWindowTitle("我的档案");
    setFixedSize(300, 200);

    // 创建布局和控件
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("用户档案", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    usernameLabel = new QLabel(this);
    usernameLabel->setAlignment(Qt::AlignCenter);
    usernameLabel->setStyleSheet("font-size: 16px;");
    setUsername(username);  // 设置用户名

    QPushButton *closeButton = new QPushButton("关闭", this);

    // 添加到布局
    layout->addWidget(titleLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(closeButton);

    // 连接信号槽
    connect(closeButton, &QPushButton::clicked, this, [this]() {
        emit windowClosed();
        close();
    });
}

