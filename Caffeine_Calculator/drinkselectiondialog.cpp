#include "drinkselectiondialog.h"
#include "ui_drinkselectiondialog.h"
#include "ui_monthlystatistics.h"

DrinkSelectionDialog::DrinkSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrinkSelectionDialog)
{
    ui->setupUi(this);
    setWindowTitle("饮品选项");

    connect(ui->confirmButton, &QPushButton::clicked, this, &DrinkSelectionDialog::onConfirmClicked);
}

DrinkSelectionDialog::~DrinkSelectionDialog()
{
    delete ui;
}

void DrinkSelectionDialog::setDrinkName(const QString &name)
{
    currentDrinkName = name;
    ui->drinkNameLabel->setText(name);
}

void DrinkSelectionDialog::onConfirmClicked()
{
    QString size = "中杯";
    if(ui->largeRadio->isChecked()) size = "大杯";
    else if(ui->smallRadio->isChecked()) size = "小杯";

    QString beanType = "阿拉比卡";
    if(ui->robustaRadio->isChecked()) beanType = "罗布斯塔";
    else if(ui->blendRadio->isChecked()) beanType = "混合";

    QString temp = "热";
    if(ui->coldRadio->isChecked()) temp = "冷";
    else if(ui->warmRadio->isChecked()) temp = "温";

    int count = ui->countSpinBox->value();

    emit drinkConfigured(currentDrinkName, size, beanType, temp, count);
    this->close();
}

