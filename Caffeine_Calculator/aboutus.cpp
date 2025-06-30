#include "aboutus.h"
#include "ui_aboutus.h"
#include <QDebug>  // 用于调试输出
#include <QPixmap>

AboutUs::AboutUs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutUs)
{
    ui->setupUi(this);
    ui->pushButton->setText("返回主界面");
    // 连接返回按钮的点击信号到槽函数
    connect(ui->pushButton, &QPushButton::clicked,
                this, &AboutUs::onBackButtonClicked);

    qDebug() << "AboutUs界面初始化完成";  // 调试输出

    QString pic= ":/icons/coffee.png";
    QPixmap pixmap(pic);
    if(!pixmap.isNull()) {
            ui->onelabel->setPixmap(pixmap.scaled(
                ui->onelabel->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
        }
    qDebug() << "图片尺寸：" << pixmap.size();
    qDebug() << "QLabel尺寸：" << ui->onelabel->size();
}

AboutUs::~AboutUs() {
    delete ui;
}

void AboutUs::onBackButtonClicked()
{
    qDebug() << "返回主界面按钮被点击";
    // 方案1：直接关闭窗口，由主窗口处理显示逻辑
    emit windowClosed();
    this->hide();
}


