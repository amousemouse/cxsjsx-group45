//#include "My.h"
//#include "ui_My.h"
//#include <QDebug>  // 用于调试输出

//My::My(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::My)
//{
//    ui->setupUi(this);
//    ui->goback->setText("返回主界面");
//    // 连接返回按钮的点击信号到槽函数
//    connect(ui->goback, &QPushButton::clicked,
//                this, &My::onBackButtonClicked);
//    connect(ui->lineEdit, &QLineEdit::textChanged, [=](const QString &text){
//        qDebug() << "实时输入变化:" << text;
//    });

//    qDebug() << "AboutUs界面初始化完成";  // 调试输出
//}

//My::~My() {
//    delete ui;
//}

//void My::onBackButtonClicked()
//{
//    qDebug() << "返回主界面按钮被点击";
//    // 方案1：直接关闭窗口，由主窗口处理显示逻辑
//    emit windowClosed();
//    this->hide();
//}

#include "My.h"
#include "ui_My.h"
#include <QDebug>  // 用于调试输出
#include <QMessageBox>
#include <QPixmap>
//My::My(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::My),
//    m_storedText("")  // 初始化成员变量
//{
//    ui->setupUi(this);
//    ui->goback->setText("返回主界面");
//    // 连接返回按钮的点击信号到槽函数
//    connect(ui->goback, &QPushButton::clicked,
//                this, &My::onBackButtonClicked);
//    connect(ui->lineEdit, &QLineEdit::textChanged, [=](const QString &text){
//        qDebug() << "实时输入变化:" << text;
//        m_storedText = text;  // 更新存储的文本
//    });

//    qDebug() << "AboutUs界面初始化完成";  // 调试输出
//}
const double CAFFEINE_THRESHOLD = 6000; // 可根据需要调整
// 添加一个带参数的构造函数
My::My(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::My)
{
    ui->setupUi(this);
    m_monthlyGoal = CAFFEINE_THRESHOLD;
    ui->goback->setText("返回主界面");
    ui->lineEdit->setText(m_storedText);  // 设置lineEdit的初始值
    qDebug()<<"初始化";

    // 连接返回按钮的点击信号到槽函数
    connect(ui->goback, &QPushButton::clicked,
                this, &My::onBackButtonClicked);
    connect(ui->lineEdit, &QLineEdit::textChanged, [=](const QString &text){
        qDebug() << "实时输入变化:" << text;
        m_storedText = text;  // 更新存储的文本
    });
    //connect(ui->adviceButton, &QPushButton::clicked, this, &My::onAdviceButtonClicked);
    qDebug() << "AboutUs界面初始化完成，初始文本:" << m_storedText;
    updateAdviceImage();

}

My::~My() {
    delete ui;
}

// 添加获取存储文本的方法
QString My::getStoredText() const
{
    return m_storedText;
}

//User* currentUser = userManager->currentUser();
//double caffeine = currentUser->calculateMonthCaffeine(
//    QDate::currentDate().year(),
//    QDate::currentDate().month(),
//    drinkCaffeineMap // 全局饮品咖啡因数据
//);

void My::onBackButtonClicked()
{
    qDebug() << "返回主界面按钮被点击，当前存储文本:" << m_storedText;
    // 方案1：直接关闭窗口，由主窗口处理显示逻辑
    emit windowClosed();
    this->hide();
}
void My::setCaffeineData(double currentCaffeine, double monthlyGoal) {
    m_currentCaffeine = currentCaffeine;
    m_monthlyGoal = monthlyGoal;
    updateAdviceImage(); // 立即更新UI
}

void My::setData(JsonInfo data)
{
    ui->plainTextEdit->clear();
    m_data = data;
    updateProgress();
    updateAdviceImage();

    for(int i=0;i<data.items.size();i++)
    {
        JsonItem item = data.items.at(i);
        QString time = item.time;
        ui->plainTextEdit->appendPlainText(time);
        for(int j = 0;j<item.drinks.size();j++)
        {
           Drink drink = item.drinks.at(j);
           QString show = QString("  %1:%2").arg(drink.name).arg(drink.count);
           ui->plainTextEdit->appendPlainText(show);
        }
    }
}

void My::updateProgress()
{
    double sum = 0;
    for(int i=0;i<m_data.items.size();i++)
    {
        JsonItem item = m_data.items.at(i);
        for(int j = 0;j<item.drinks.size();j++)
        {
            Drink drink = item.drinks.at(j);
            if(drink.name == "卡布奇诺")    //假设一杯含有70mg咖啡因
            {
                sum += 70*drink.count;
            }
            else if(drink.name == "拿铁") //假设一杯含有50mg咖啡因
            {
                sum += 50*drink.count;
            }
            else if(drink.name == "摩卡") //假设一杯含有60mg咖啡因
            {
                sum += 60*drink.count;
            }
            else if(drink.name == "浓缩咖啡") //假设一杯含有80mg咖啡因
            {
                sum += 80*drink.count;
            }
        }
    }
    m_currentCaffeine = sum;
    ui->progressBar->setValue(sum/m_monthlyGoal * 100);
}
void My::updateAdviceImage() {
    QString imagePath;
    QString advice;
    if (m_currentCaffeine >= m_monthlyGoal) {
        imagePath = ":/icons/IMG_0673.png";
        advice = "爆表啦！不要再喝了";// 超过阈值
    } else if (m_currentCaffeine >= m_monthlyGoal/2) {
        imagePath = ":/icons/IMG_0627.png"; // 超过一半
        advice = "接近目标，少喝一点哦";
    } else {
        imagePath = ":/icons/IMG_0674.png";    // 安全范围
        advice = "安全范围，继续保持！";
    }
    ui->AdviceLabel->setText(advice);
    QPixmap pixmap(imagePath);
    if(!pixmap.isNull()) {
        ui->ImageLabel->setPixmap(pixmap.scaled(
            ui->ImageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
    }
}

void My::onAdviceButtonClicked() {
    QString status;
    if (m_currentCaffeine >= m_monthlyGoal) {
        status = "⚠️ 超过月度目标";
    } else {
        status = QString("剩余 %1mg").arg(m_monthlyGoal - m_currentCaffeine);
    }

    QMessageBox::information(this, "咖啡因状态",
        QString("当前摄入: %1mg\n月度目标: %2mg\n%3")
            .arg(m_currentCaffeine)
            .arg(m_monthlyGoal)
            .arg(status));
}
//void My::setMonthlyGoal(int goalMg) {
//    bool ok;
//    int newGoal = QInputDialog::getInt(
//        nullptr,
//        "设置月度目标",
//        "请输入月度咖啡因目标（mg）:",
//        goalMg,
//        1,
//        15000,
//        1,
//        &ok
//    );
//    if (ok) {
//        m_userManager->setUserMonthlyCaffeineGoal(currentUser, newGoal);
//        QMessageBox::information(nullptr, "成功", QString("目标已设置为: %1 mg").arg(newGoal));
//    }
//}


void My::on_btnSet_clicked()
{
    QList<JsonItem> items = m_data.items;
    int index = -1;
    for(int i = 0;i<items.size();i++)
    {
        JsonItem item = items.at(i);
        if(item.time == QDate::currentDate().toString("yyyy-MM-dd"))
        {
            index = i;
            break;
        }
    }

    if(index > 0)
    {
        JsonItem item = items.at(index);
        bool isExist = false;
        int flag = -1;

        for(int k = 0;k<item.drinks.size();k++)
        {
            QString name = item.drinks.at(k).name;
            if(ui->comboBox->currentText() == name)
            {
                isExist = true;
                flag = k;
                break;
            }
        }


        if(!isExist)
        {
            Drink drink;
            drink.name = ui->comboBox->currentText();
            drink.count = ui->leCount->text().toInt();
            item.drinks.append(drink);
        }
        else
        {
            Drink drink;
            drink.name = ui->comboBox->currentText();
            drink.count = ui->leCount->text().toInt();
            item.drinks.replace(flag,drink);
        }

        m_data.items.replace(index,item);
    }
    else
    {
        JsonItem item;
        item.time = QDate::currentDate().toString("yyyy-MM-dd");

        bool isExist = false;
        int flag = -1;
        JsonItem tmpjitem;
        for(int j = 0;j<items.size();j++)
        {
            int flag = -1;
            JsonItem jitem = items.at(j);
            for(int k = 0;k<jitem.drinks.size();k++)
            {
                QString name = jitem.drinks.at(k).name;
                if(ui->comboBox->currentText() == name &&
                        item.time == jitem.time)
                {
                    isExist == true;
                    flag = k;
                    tmpjitem = jitem;
                    break;
                }
            }
        }

        if(!isExist)
        {
            Drink drink;
            drink.name = ui->comboBox->currentText();
            drink.count = ui->leCount->text().toInt();
            item.drinks.append(drink);
        }
        else
        {
            QList<Drink> drinks = tmpjitem.drinks;
            Drink drink;
            drink.name = ui->comboBox->currentText();
            drink.count = ui->leCount->text().toInt();
            drinks.replace(flag,drink);
            item.drinks = drinks;
        }


        m_data.items.append(item);
    }
    emit sigOk();
}

void My::on_btnRead_clicked()
{
    emit sigRead();
}
