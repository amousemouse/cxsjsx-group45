#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class ProfileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileWindow(const QString &username, QWidget *parent = nullptr);
    void setUsername(const QString &username);


signals:
    void windowClosed();

private:
    QLabel *usernameLabel;
};

#endif // PROFILEWINDOW_H
