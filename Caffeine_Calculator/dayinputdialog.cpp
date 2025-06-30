

#include "dayinputdialog.h"
#include "ui_dayinputdialog.h"
#include <QMessageBox>
#include "monthlystatistics.h"
#include "ui_monthlystatistics.h"
#include <QDebug>
#include <QFile>

DayInputDialog::DayInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DayInputDialog)
{
    ui->setupUi(this);
    qDebug()<<"out";
     //获取父窗口(MonthlyStatistics)的咖啡类型
//        if (MonthlyStatistics* stats = qobject_cast<MonthlyStatistics*>(parent)) {
//            QMap<QString, double> drinks = stats->getDrinkTypes();
//            qDebug()<<"drinks"<<drinks.keys()[1];
//            ui->drinkComboBox->clear();
//            ui->drinkComboBox->addItems(drinks.keys());
//        }

    // ============= UI优化部分 =============
    // 设置窗口标题
    setWindowTitle("每日饮品记录");

    // 设置固定窗口大小（比原来更大）
    resize(700, 700);  // 宽度600，高度600

    // 设置日期标签样式（居中+大字体）
//    ui->dateLabel->setAlignment(Qt::AlignCenter);
//    QFont dateFont = ui->dateLabel->font();
//    dateFont.setPointSize(8);  // 字体更大
//    dateFont.setBold(true);
//    ui->dateLabel->setFont(dateFont);
//    ui->dateLabel->setMinimumWidth(800);
//    ui->dateLabel->setMinimumHeight(800);  // 增加标签高度

    // 设置饮品下拉框选项和样式
//    ui->drinkComboBox->clear();
//    ui->drinkComboBox->addItems({"coffee", "tea", "water", "juice", "milk"});
//    ui->drinkComboBox->addItem("coffee", 100);
//    ui->drinkComboBox->addItem("tea", 0);
//    ui->drinkComboBox->setMinimumWidth(80);  // 增加宽度
//    ui->drinkComboBox->setMinimumHeight(60);
//    ui->drinkComboBox->setStyleSheet("padding: 5px;");
//    qDebug() << "Combo box items:" << ui->drinkComboBox->count();
//    ui->drinkComboBox->setEditable(true);
//    QString selectedText = ui->drinkComboBox->currentText();
//    QVariant selectedData = ui->drinkComboBox->currentData();

//    qDebug() << "选中的文本:" << selectedText;
//    qDebug() << "选中的数据:" << selectedData.toInt();

//        QComboBox *comboBox = new QComboBox();
//        comboBox->addItem("苹果", 100);   // 绑定整数数据
//        comboBox->addItem("香蕉", "yellow"); // 绑定字符串数据
//        comboBox->addItem("橙子");        // 仅添加文本，不绑定数据

//        // 获取选中项的文本和数据
//        QString selectedText = comboBox->currentText();
//        QVariant selectedData = comboBox->currentData();

//        qDebug() << "选中的文本:" << selectedText;
//        qDebug() << "选中的数据:" << selectedData.toInt();





    // 设置杯数选择器样式
//    ui->cupsSpinBox->setRange(1, 20);
//    ui->cupsSpinBox->setValue(1);
//    ui->cupsSpinBox->setMinimumWidth(80);
//    ui->cupsSpinBox->setMinimumHeight(60);
//    ui->cupsSpinBox->setStyleSheet("padding: 5px;");
//    connect(ui->cupsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
//            this, [](int cups) {  // 移除了this
//        qDebug() << "当前杯数:" << cups;
//    });

    // 设置按钮文本和样式
//    ui->addButton->setMinimumWidth(80);
//    ui->removeButton->setMinimumWidth(80);
//    ui->saveButton->setMinimumWidth(80);
//    ui->addButton->setText("添加饮品");
//    ui->removeButton->setText("删除选中");
//    ui->saveButton->setText("保存记录");

//    // 增加按钮大小
//    ui->addButton->setMinimumSize(100, 30);
//    ui->removeButton->setMinimumSize(100, 30);
//    ui->saveButton->setMinimumSize(120, 35);

    // 按钮样式
//    QString buttonStyle = "QPushButton {"
//                         "   padding: 5px 10px;"
//                         "   border-radius: 4px;"
//                         "   font-weight: bold;"
//                         "}";
//    ui->addButton->setStyleSheet(buttonStyle + "background-color: #e7f5ff; color: #1864ab;");
//    ui->removeButton->setStyleSheet(buttonStyle + "background-color: #fff3bf; color: #e67700;");
//    ui->saveButton->setStyleSheet(buttonStyle + "background-color: #d3f9d8; color: #2b8a3e;");

    // 设置列表控件样式和大小
/*    ui->listWidget->setStyleSheet(
        "QListWidget {"
        "   border: 1px solid #ddd;"
        "   border-radius: 6px;"
        "   padding: 8px;"
        "   font-size: 14px;"
        "}"
        "QListWidget::item {"
        "   padding: 6px;"
        "   border-bottom: 1px solid #eee;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #f8f9fa;"
        "}"
    );
    ui->listWidget->setMinimumHeight(300); */ // 增加列表高度

    initDrinkComboBox();

    // 清除列表默认项
    ui->listWidget->clear();
    // ============= UI优化结束 =============

    // 连接信号槽（保持不变）
    connect(ui->addButton, &QPushButton::clicked, this, &DayInputDialog::onAddDrinkClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &DayInputDialog::onRemoveDrinkClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &DayInputDialog::onSaveClicked);
    connect(ui->drinkBox, &QComboBox::currentTextChanged,
                this, &DayInputDialog::updateCurrentDrink);

}

void DayInputDialog::initDrinkComboBox()
{
    // 清空现有选项
    ui->drinkBox->clear();

    // 从文件读取饮品列表
    QFile file("saved_names.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                // 分割行，只取饮品名称部分
                QString drinkName = line.split(" ").first();  // 取第一个空格前的部分
                qDebug()<<">>>>>>>>>>>>>>>>>>"<<drinkName;
                if (!drinkName.isEmpty()) {
                    ui->drinkBox->addItem(drinkName);
                }
            }
        }
        file.close();
    } else {
        qDebug() << "无法打开饮品列表文件，使用默认选项";
        // 添加一些默认选项
        ui->drinkBox->addItems({"美式咖啡", "拿铁", "卡布奇诺", "摩卡", "浓缩咖啡"});
    }

    // 设置下拉框样式和属性
    ui->drinkBox->setEditable(true);  // 允许用户输入新饮品
    ui->drinkBox->setStyleSheet("QComboBox { padding: 5px; min-width: 100px; }");
}



// 以下原有函数保持不变
void DayInputDialog::setDate(const QDate &date) {
    currentDate = date;
//    ui->dateLabel->setText(date.toString("yyyy年MM月dd日"));
}

void DayInputDialog::setDrinkRecords(const QList<QPair<QString, int>>& records) {
    ui->listWidget->clear();
    for (const auto& record : records) {
        ui->listWidget->addItem(QString("%1 × %2杯").arg(record.first).arg(record.second));
    }
}

QList<QPair<QString, int>> DayInputDialog::getDrinkRecords() const {
    QList<QPair<QString, int>> records;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QString text = ui->listWidget->item(i)->text();
        QStringList parts = text.split(" × ");
        if (parts.size() == 2) {
            records.append({parts[0], parts[1].replace("杯", "").toInt()});
        }
    }
    qDebug()<<"pass getdrinkrecord";
    return records;
}

void DayInputDialog::onAddDrinkClicked()
{
    QString drink = ui->drinkBox->currentText();
    int cups = ui->cupsSpinBox->value();

    if (!drink.isEmpty() && cups > 0) {
        // 直接添加，不做重复检查
        ui->listWidget->addItem(QString("%1 × %2杯").arg(drink).arg(cups));

        // 可选：添加后清空输入（根据需求）
        // ui->drinkComboBox->setCurrentText("");
        // ui->cupsSpinBox->setValue(1);
    }
}

void DayInputDialog::onRemoveDrinkClicked() {
    delete ui->listWidget->currentItem();
}

void DayInputDialog::onSaveClicked() {
    emit recordsUpdated(currentDate, getDrinkRecords());
    accept();
}

void DayInputDialog::updateCurrentDrink(const QString &newDrink)
{
    if (!newDrink.isEmpty()) {
        // 直接更新当前饮品（不自动添加到列表）
        currentDrink = newDrink;

        // 可选：如果希望立即添加到列表，取消下面注释
        // onAddDrinkClicked();
    }
}
