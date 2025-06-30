
#ifndef MY_H
#define MY_H

#include <QWidget>
#include <QMap>
#include <QDate>
#include <QMainWindow>
#include <QWidget>
#include "drinkselectiondialog.h"
#include "cafresultwindow.h"
#include "usermanager.h"
#include "user.h"
#include "monthlystatistics.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class My;
}
QT_END_NAMESPACE

class My : public QMainWindow
{
    Q_OBJECT

public:
    explicit My(QWidget *parent = nullptr);
    ~My();
    explicit My(const QString &text = "", QWidget *parent = nullptr);  // 修改构造函数
        QString getStoredText() const;  // 添加获取文本的方法
    void setMonthlyGoal(int goalMg);
    void setCaffeineData(double currentCaffeine, double monthlyGoal = 6000.0);

    void setData(JsonInfo info);
    JsonInfo getData() {return m_data;}
    void updateProgress();

signals:
    void windowClosed();
    void handleAboutUsWindowClosed();
    void sigOk();
    void sigRead();

private slots:
    void onBackButtonClicked();
    void onAdviceButtonClicked();

    void on_btnSet_clicked();

    void on_btnRead_clicked();

private:
    UserManager* m_userManager;
    Ui::My *ui;
    QString m_storedText;
    double m_currentCaffeine;  // 当前咖啡因量
    double m_monthlyGoal;      // 月度目标阈值

    void updateAdviceImage();

    JsonInfo m_data;
};

#endif // NEWORDERWINDOW_H
