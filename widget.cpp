#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "MathExpr.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), display(new QLineEdit(this))
{
    ui->setupUi(this);

    // Displaybox
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    // Main layout
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(display, 0, 0, 1, 4);

    // Digit Buttons
    for (int i = 0; i < 10; i++)
    {
        digitButtons[i] = new QPushButton();
        digitButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        digitButtons[i]->resize(qMax(digitButtons[i]->size().width(), digitButtons[i]->size().height()), qMax(digitButtons[i]->size().width(), digitButtons[i]->size().height()));
        digitButtons[i]->setText(QString::number((i + 1) % 10));
        connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(inputBtnClicked()));

        mainLayout->addWidget(digitButtons[i], i / 3 + 1, i % 3, 1, 1);
    }

    // Parenthese Buttons
    parentheseButtons[0] = new QPushButton();
    parentheseButtons[0]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    parentheseButtons[0]->resize(qMax(parentheseButtons[0]->size().width(), parentheseButtons[0]->size().height()), qMax(parentheseButtons[0]->size().width(), parentheseButtons[0]->size().height()));
    parentheseButtons[0]->setText(tr("("));
    connect(parentheseButtons[0], SIGNAL(clicked()), this, SLOT(inputBtnClicked()));
    mainLayout->addWidget(parentheseButtons[0], 4, 1, 1, 1);

    parentheseButtons[1] = new QPushButton();
    parentheseButtons[1]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    parentheseButtons[1]->resize(qMax(parentheseButtons[1]->size().width(), parentheseButtons[1]->size().height()), qMax(parentheseButtons[1]->size().width(), parentheseButtons[1]->size().height()));
    parentheseButtons[1]->setText(tr(")"));
    connect(parentheseButtons[1], SIGNAL(clicked()), this, SLOT(inputBtnClicked()));
    mainLayout->addWidget(parentheseButtons[1], 4, 2, 1, 1);

    // Operator buttons
    QList<QString> operatorList = {"+", "-", "*", "/"};

    for (int i = 0; i < 4; i++)
    {
        operatorButtons[i] = new QPushButton();
        operatorButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        operatorButtons[i]->resize(qMax(operatorButtons[i]->size().width(), operatorButtons[i]->size().height()), qMax(operatorButtons[i]->size().width(), operatorButtons[i]->size().height()));
        operatorButtons[i]->setText(operatorList.at(i));
        connect(operatorButtons[i], SIGNAL(clicked()), this, SLOT(inputBtnClicked()));

        mainLayout->addWidget(operatorButtons[i], i % 4 + 1, 3, 1, 1);
    }

    // Manipulation buttons
    QList<QString> manList = {"BS", "CE", "="};
    for (int i = 0; i < 3; i++)
    {
        manButtons[i] = new QPushButton();
        manButtons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        manButtons[i]->resize(qMax(manButtons[i]->size().width(), manButtons[i]->size().height()), qMax(manButtons[i]->size().width(), manButtons[i]->size().height()));
        manButtons[i]->setText(manList.at(i));
        connect(manButtons[i], SIGNAL(clicked()), this, SLOT(manBtnClicked()));

        mainLayout->addWidget(manButtons[i], 5, i % 3, 1, 1);
    }

    setLayout(mainLayout);
    resize(300, 300);
}

void Widget::inputBtnClicked()
{
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());

    QString displayText = display->text();
    displayText.append(senderButton->text());
    display->setText(displayText);
}

void Widget::manBtnClicked()
{
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());

    QString btnText = senderButton->text();
    if (btnText == "BS") {
        QString displayText = display->text();
        displayText = displayText.left(displayText.size() - 1);
        display->setText(displayText);
    } else if (btnText == "CE") {
        display->setText(tr(""));
    } else if (btnText == "=") {
        MathExpr expr(display->text());
        display->setText(QString::number(expr.evaluate()));
    }
}

Widget::~Widget()
{
    delete ui;
}

