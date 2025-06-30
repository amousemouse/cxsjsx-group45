#include "neworderwindow.h"
#include "ui_neworderwindow.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "ui_monthlystatistics.h"
#include "monthlystatistics.h"
#include <QFile>
#include <QMessageBox>

NewOrderWindow::NewOrderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewOrderWindow)
{
    ui->setupUi(this);
    connect(ui->saveButton, &QPushButton::clicked, this, &NewOrderWindow::onBackButtonClicked);
    //ui->backButton = new QPushButton("checkout", this);
    //connect(ui->backButton, &QPushButton::clicked, this, &NewOrderWindow::onCheckoutClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &NewOrderWindow::onSaveButtonClicked);

//    qDebug() << "enter neworder window";
//    setWindowTitle("新的订单");
//    resize(1000, 1000);  // 设置窗口初始大小

//    // 设置主布局边距和间距
//    ui->verticalLayout->setContentsMargins(20, 20, 20, 20);
//    ui->verticalLayout->setSpacing(15);

//    // 设置标题标签样式
//    ui->label->setAlignment(Qt::AlignCenter);
//    ui->label->setStyleSheet("font-weight: bold; font-size: 14px;");

//    setupDrinkData();

    // 创建滚动区域内容
    QWidget *scrollWidget = new QWidget;
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(10);  // 设置饮品按钮间距

    for(const QString &drink : drinkPrices.keys()) {
        QPushButton *drinkBtn = new QPushButton(drink + " - ¥" + QString::number(drinkPrices[drink]));
        drinkBtn->setMinimumHeight(40);  // 统一按钮高度
        drinkBtn->setStyleSheet(
            "QPushButton {"
            "  background-color: #f0f0f0;"
            "  border: 1px solid #ccc;"
            "  border-radius: 5px;"
            "  padding: 5px;"
            "}"
            "QPushButton:hover {"
            "  background-color: #e0e0e0;"
            "}"
        );
        connect(drinkBtn, &QPushButton::clicked, [this, drink]() { onDrinkSelected(drink); });
        scrollLayout->addWidget(drinkBtn);
    }

//    // 添加弹簧使按钮顶部对齐
//    scrollLayout->addStretch();

//    QScrollArea *scrollArea = new QScrollArea;
//    scrollArea->setWidget(scrollWidget);
//    scrollArea->setWidgetResizable(true);
//    scrollArea->setStyleSheet("QScrollArea { border: none; }");
//    ui->verticalLayout->insertWidget(1, scrollArea);

//    // 连接返回按钮信号
//    connect(ui->backButton, &QPushButton::clicked, this, &NewOrderWindow::onBackButtonClicked);
}

NewOrderWindow::~NewOrderWindow()
{
    delete ui;
}

void NewOrderWindow::setupDrinkData()
{
    // Drink prices
    drinkPrices["美式咖啡"] = 25.0;
    drinkPrices["拿铁"] = 30.0;
    drinkPrices["卡布奇诺"] = 32.0;
    drinkPrices["摩卡"] = 35.0;
    drinkPrices["浓缩咖啡"] = 28.0;

    // Caffeine content (mg per standard serving)
    drinkCaffeine["美式咖啡"] = 150.0;
    drinkCaffeine["拿铁"] = 120.0;
    drinkCaffeine["卡布奇诺"] = 100.0;
    drinkCaffeine["摩卡"] = 110.0;
    drinkCaffeine["浓缩咖啡"] = 200.0;
}

void NewOrderWindow::onDrinkSelected(const QString &drinkName)
{
    if(!selectionDialog) {
        selectionDialog = new DrinkSelectionDialog(this);
        connect(selectionDialog, &DrinkSelectionDialog::drinkConfigured,
                this, &NewOrderWindow::handleDrinkSelection);
    }

    selectionDialog->setDrinkName(drinkName);
    selectionDialog->show();
}

void NewOrderWindow::handleDrinkSelection(const QString &drinkName, const QString &size,
                                        const QString &beanType, const QString &temp, int count)
{
    double caffeineMultiplier = 1.0;
    if(size == "大杯") caffeineMultiplier = 1.5;
    else if(size == "中杯") caffeineMultiplier = 1.0;
    else if(size == "小杯") caffeineMultiplier = 0.7;

    double totalCaffeine = drinkCaffeine[drinkName] * caffeineMultiplier * count;
    currentOrder.append(qMakePair(drinkName, qMakePair(count, totalCaffeine)));

    qDebug() << "Added to order:" << drinkName << size << count << "caffeine:" << totalCaffeine;
}

void NewOrderWindow::onBackButtonClicked()
{
    if (parentWidget()) {
        parentWidget()->show();
    }
    emit windowClosed();
    this->hide();
}

void NewOrderWindow::onCheckoutClicked()
{
    if(currentOrder.isEmpty()) {
        qDebug() << "No items in order";
        return;
    }
}

void NewOrderWindow::onSaveButtonClicked()
{
    qDebug() << "in the function";

    // 获取nameEdit的输入内容
    QString name = ui->nameEdit->text();  // 确保ui中有nameEdit这个QLineEdit
    QString num = ui->numEdit->text();

    if(name.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入饮品名称!");
        return;
    }
    if(num.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入饮品咖啡因含量!");
        return;
    }

    // 保存到文件
    QFile file("saved_names.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << name << " " << num << "\n";  // 每行保存一个名字
        file.close();
        QMessageBox::information(this, "成功", "名称已保存!");

        // 清空输入框
        ui->nameEdit->clear();
        ui->numEdit->clear();
    } else {
        QMessageBox::critical(this, "错误", "无法保存文件!");
    }
}
