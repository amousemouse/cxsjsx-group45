#include "cafresultwindow.h"
#include "ui_cafresultwindow.h"
#include "ui_monthlystatistics.h"

CafResultWindow::CafResultWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CafResultWindow)
{
    ui->setupUi(this);
    setWindowTitle("咖啡因含量");

    connect(ui->backButton, &QPushButton::clicked, this, &CafResultWindow::onBackButtonClicked);
}

CafResultWindow::~CafResultWindow()
{
    delete ui;
}

void CafResultWindow::setCaffeineAmount(double amount)
{
    ui->caffeineLabel->setText(QString("本次摄入咖啡因: %1 mg").arg(amount));
}

void CafResultWindow::onBackButtonClicked()
{
    parentWidget()->show();
    this->close();
}
