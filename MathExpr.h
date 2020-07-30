#ifndef MATHEXPR_H
#define MATHEXPR_H

#include <QString>

class MathExpr
{
public:
    MathExpr() { mathExpr = ""; }
    MathExpr(QString str) { mathExpr = str; }
    ~MathExpr() {}
    double evaluate();

private:
    QString mathExpr;

    int precedence(QString opr);
};

#endif // MATHEXPR_H
