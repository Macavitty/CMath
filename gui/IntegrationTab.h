#ifndef COMPMATH_INTEGRATIONTAB_H
#define COMPMATH_INTEGRATIONTAB_H

#include <QDialog>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QDoubleValidator>
#include <QTableView>
#include <QtWidgets/QTableWidget>
#include <QHeaderView>
#include <QSizePolicy>
#include <QFormLayout>
#include <QtWidgets/QButtonGroup>
#include <QAbstractButton>
#include <QtWidgets/QRadioButton>
#include <QRadioButton>
#include <QTextBlock>
#include <QPushButton>
#include <QtGui/QVector2D>
#include <QtWidgets/QToolTip>
#include "algos/IntegrationSolver.h"
#include "helpers/Function.h"

class IntegrationTab : public QWidget {
Q_OBJECT
public:
    explicit IntegrationTab(QWidget *parent = nullptr);

private slots:
    void unsetErrPres(); // no better solution was found , so TODO
    void unsetErrLow();
    void unsetErrUpp();
    void solve();
private:
    QGridLayout *contentLayout;
    QRadioButton *funcBtn_0, *funcBtn_1, *funcBtn_2, *funcBtn_3;
    QLabel *answerField;
    QGridLayout *filtLayout;
    QLineEdit *precisionField, *uBoundField, *lBoundField;
    QDoubleValidator *doubleValidator;
    QGroupBox *groupBox;
    QButtonGroup *btnGroup;
    QPushButton *solveBtn;
    void setFiltLayout();
    void setBtnGroup();
    void tuneAswField();
    void setLineEdit(QLineEdit *l);
    void setUpStruct();
    bool checkInput();
    void setErr(QString msg, QLineEdit *field);
    void unsetErr(QLineEdit *field);
    struct functionStr{
        QVector<QString> funcStr;
        QVector<double (Function::*)(double)> funcs; // the vector of pointers to functions
    };
    functionStr f;
};

#endif //COMPMATH_INTEGRATIONTAB_H

