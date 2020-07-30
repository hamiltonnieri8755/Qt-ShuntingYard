#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QPushButton *manButtons[3];
    QPushButton *digitButtons[10];
    QPushButton *operatorButtons[4];
    QPushButton *parentheseButtons[2];
    QLineEdit *display;

private slots:
    void inputBtnClicked();
    void manBtnClicked();
};
#endif // WIDGET_H
