#include "MathExpr.h"
#include <QStack>
#include <QDebug>
#include <QString>

int MathExpr::precedence(QString opr)
{
    if (opr == "+" || opr == "-") {
        return 1;
    } else if (opr == "*" || opr == "/") {
        return 2;
    }
}

double MathExpr::evaluate()
{
    QStack<int> varStack;
    QStack<QString> oprStack;

    if (!mathExpr.isEmpty()) {
        int index = 0;

        while (index < mathExpr.size())
        {
            QString str(mathExpr.at(index));

            bool isNumber = true;

            int value = str.toInt(&isNumber);

            if (isNumber) {
                // If number, add value to the value stack
                bool flag = true;

                while (index + 1 < mathExpr.size() && flag) {
                    index++;

                    QString nextStr(mathExpr.at(index));
                    int nextValue = nextStr.toInt(&isNumber);

                    if (isNumber) {
                        value = value * 10 + nextValue;
                    } else {
                        index--;
                        flag = false;
                    }
                }

                varStack.push_back(value);
                qDebug() << "Value: " << varStack.toList();
            } else {
               if (str == "+" || str == "-" || str == "*" || str == "/") {
                   if (oprStack.size() > 0 && (precedence(oprStack.top()) >= precedence(str))) {
                       QString topOpr = oprStack.pop();

                       int val2 = varStack.pop();
                       int val1 = varStack.pop();
                       if (topOpr == "+") {
                           varStack.push_back(val1 + val2);
                       } else if (topOpr == "-") {
                           varStack.push_back(val1 - val2);
                       } else if (topOpr == "*") {
                           varStack.push_back(val1 * val2);
                       } else if (topOpr == "/") {
                           varStack.push_back(val1 / val2);
                       }
                   }

                   // Add operator to oprStack
                   oprStack.push_back(str);
                   qDebug() << "Operator: " << oprStack.toList();
               } else if (str == "(") {
                   // Add left parenthese to oprStack
                   oprStack.push_back(str);
                   qDebug() << "Operator: " << oprStack.toList();
               } else if (str == ")") {
                   // Calculate until left parenthese is popped from operator stack
                   bool flag = true;
                   QString topOpr = oprStack.pop();

                   while (topOpr != "(" && flag) {
                       int val2 = varStack.pop();
                       int val1 = varStack.pop();
                       if (topOpr == "+") {
                           varStack.push_back(val1 + val2);
                       } else if (topOpr == "-") {
                           varStack.push_back(val1 - val2);
                       } else if (topOpr == "*") {
                           varStack.push_back(val1 * val2);
                       } else if (topOpr == "/") {
                           varStack.push_back(val1 / val2);
                       }

                       if (oprStack.size() > 0) {
                           topOpr = oprStack.pop();
                       } else {
                           flag = false;
                       }
                   }
               }
            }

            index++;
        }

        while (oprStack.size() > 0) {
            QString topOpr = oprStack.pop();

            int val2 = varStack.pop();
            int val1 = varStack.pop();
            if (topOpr == "+") {
                varStack.push_back(val1 + val2);
            } else if (topOpr == "-") {
                varStack.push_back(val1 - val2);
            } else if (topOpr == "*") {
                varStack.push_back(val1 * val2);
            } else if (topOpr == "/") {
                varStack.push_back(val1 / val2);
            }
        }

        return varStack.pop();
    } else {
        return 0;
    }
}
