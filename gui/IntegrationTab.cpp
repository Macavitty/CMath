#include "IntegrationTab.h"

IntegrationTab::IntegrationTab(QWidget *parent) : QWidget(parent) {
    auto mainLayout = new QVBoxLayout;
    contentLayout = new QGridLayout();
    filtLayout = new QGridLayout();

    groupBox = new QGroupBox;
    groupBox->setLayout(contentLayout);

    doubleValidator = new QDoubleValidator;
    doubleValidator->setNotation(QDoubleValidator::ScientificNotation);

    solveBtn = new QPushButton("Решить");
    solveBtn->setStyleSheet("color : #115404; background : #C3A8A8");
    solveBtn->setMaximumWidth(180);
    solveBtn->setMinimumHeight(40);

    setFiltLayout();

    auto answerLayout = new QVBoxLayout;
    answerLayout->setContentsMargins(100,10,50,10);
    answerField = new QLabel("--- ОТВЕТ ---\n\n");
    tuneAswField();
    answerLayout->addWidget(answerField);

    contentLayout->addLayout(answerLayout, 0, 0);
    contentLayout->addLayout(filtLayout, 0, 2); // yes, there should be 2, not 1
    //contentLayout->addWidget(solveBtn, 1,2);

    // don`t try to set Qt::AlignCenter - doesn`t work
    //contentLayout->setColumnStretch(1, 1);
    groupBox->setContentsMargins(10, 10, 10, 10);
    mainLayout->addWidget(groupBox);

    setLayout(mainLayout);
}

void IntegrationTab::setBtnGroup() {
    // create and set functions
    func_1 = new QRadioButton("f(x) = x\u2075 + 6\u00b7x + 7");
    func_2 = new QRadioButton("y = 2x");
    func_3 = new QRadioButton("y = 3x");
    func_4 = new QRadioButton("y = 4x");

    func_1->setStyleSheet("font: 20px; color: #181322");
    func_2->setStyleSheet("font: 20px; color: #181322");
    func_3->setStyleSheet("font: 20px; color: #181322");
    func_4->setStyleSheet("font: 20px; color: #181322");

    btnGroup->addButton(func_1, 1);
    btnGroup->addButton(func_2, 2);
    btnGroup->addButton(func_3, 3);
    btnGroup->addButton(func_4, 4);

    func_1->setChecked(true);
}

void IntegrationTab::tuneAswField() {
    answerField->setStyleSheet("background : white; "
                               "border: 1px solid #C3A8A8; "
                               "border-radius: 8px; "
                               "font: 16px; "
                               "color: #181322");
    answerField->setFixedSize(600, 500);
    answerField->setMinimumSize(600, 500);
    answerField->setAlignment(Qt::AlignHCenter);
}

void IntegrationTab::setFiltLayout() {

    btnGroup = new QButtonGroup;
    setBtnGroup();

    auto *forms = new QFormLayout;

    precisionField = new QLineEdit;
    hBoundField = new QLineEdit;
    lBoundField = new QLineEdit;
    setLineEdit(precisionField);
    setLineEdit(hBoundField);
    setLineEdit(lBoundField);
    auto l1 = new QLabel("Нижний предел:");
    auto l2 = new QLabel("Верхний предел:");
    auto l3 = new QLabel("Точность:");
    l1->setStyleSheet("font: 18px");
    l2->setStyleSheet("font: 18px");
    l3->setStyleSheet("font: 18px");
    forms->addRow(l1, lBoundField);
    forms->addRow(l2, hBoundField);
    forms->addRow(l3, precisionField);
    forms->setAlignment(Qt::AlignRight);

    filtLayout->addWidget(func_1, 0, 0);
    filtLayout->addWidget(func_2, 1, 0);
    filtLayout->addWidget(func_3, 2, 0);
    filtLayout->addWidget(func_4, 3, 0);
    filtLayout->addLayout(forms, 4, 0);
    filtLayout->addWidget(solveBtn, 5,0);

    filtLayout->setContentsMargins(10,10,100,10);
}

void IntegrationTab::setLineEdit(QLineEdit *l) {
    l->setValidator(doubleValidator);
    l->setMaxLength(20);
    l->setMaximumSize(200, 25);
    l->setMinimumWidth(100);
}