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

class IntegrationTab : public QWidget {

public:
    explicit IntegrationTab(QWidget *parent = nullptr);

private:
    QGridLayout *contentLayout;
    QTableWidget *funcTable;
    QRadioButton *func_1, *func_2, *func_3, *func_4;
    QLabel *answerField;
    QTextBlock *textBlock;
    QGridLayout *filtLayout;
    QLineEdit *precisionField, *hBoundField, *lBoundField;
    QDoubleValidator *doubleValidator;
    QGroupBox *groupBox;
    QButtonGroup *btnGroup;
    QPushButton *solveBtn;
    void setFiltLayout();
    void setBtnGroup();
    void tuneAswField();
    void setLineEdit(QLineEdit *l);
};

#endif //COMPMATH_INTEGRATIONTAB_H

