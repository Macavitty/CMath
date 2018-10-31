#include "IntegrationTab.h"

IntegrationTab::IntegrationTab(QWidget *parent) : QWidget(parent) {
    //structure
    setUpFunctions();

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
    connect(solveBtn, SIGNAL(clicked()), this, SLOT(solve()));

    setFiltLayout();

    auto answerLayout = new QVBoxLayout;
    answerLayout->setContentsMargins(100, 10, 50, 10);
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
    funcBtn_0 = new QRadioButton;
    funcBtn_1 = new QRadioButton();
    funcBtn_2 = new QRadioButton();
    funcBtn_3 = new QRadioButton();

    funcBtn_0->setStyleSheet("font: 20px; color: #181322;");
    funcBtn_1->setStyleSheet("font: 20px; color: #181322");
    funcBtn_2->setStyleSheet("font: 20px; color: #181322");
    funcBtn_3->setStyleSheet("font: 20px; color: #181322");

    /*
     * WARNING
     * don`t forget to set up working directory correctly
     * e. g. "/home/macavitty/CLionProjects/CMath"
     * */
    funcBtn_0->setIcon(QIcon("gui/images/func_0.png"));
    funcBtn_1->setIcon(QIcon("gui/images/func_1.png"));
    funcBtn_2->setIcon(QIcon("gui/images/func_2.png"));
    funcBtn_3->setIcon(QIcon("gui/images/func_3.png"));

    funcBtn_0->setIconSize(QSize(500, 60));
    funcBtn_1->setIconSize(QSize(400, 60));
    funcBtn_2->setIconSize(QSize(500, 60));
    funcBtn_3->setIconSize(QSize(500, 60));

    btnGroup->addButton(funcBtn_0, 0);
    btnGroup->addButton(funcBtn_1, 1);
    btnGroup->addButton(funcBtn_2, 2);
    btnGroup->addButton(funcBtn_3, 3);

    funcBtn_0->setChecked(true);
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
    uBoundField = new QLineEdit;
    lBoundField = new QLineEdit;
    setLineEdit(precisionField);
    setLineEdit(uBoundField);
    setLineEdit(lBoundField);
    connect(precisionField, SIGNAL(editingFinished()), this, SLOT(unsetErrPres()));
    connect(lBoundField, SIGNAL(editingFinished()), this, SLOT(unsetErrLow()));
    connect(uBoundField, SIGNAL(editingFinished()), this, SLOT(unsetErrUpp()));
    auto l1 = new QLabel("Нижний предел:");
    auto l2 = new QLabel("Верхний предел:");
    auto l3 = new QLabel("Точность:");
    l1->setStyleSheet("font: 18px");
    l2->setStyleSheet("font: 18px");
    l3->setStyleSheet("font: 18px");
    forms->addRow(l2, uBoundField);
    forms->addRow(l1, lBoundField);
    forms->addRow(l3, precisionField);
    forms->setAlignment(Qt::AlignRight);

    filtLayout->addWidget(funcBtn_0, 0, 0);
    filtLayout->addWidget(funcBtn_1, 1, 0);
    filtLayout->addWidget(funcBtn_2, 2, 0);
    filtLayout->addWidget(funcBtn_3, 3, 0);
    filtLayout->addLayout(forms, 4, 0);
    filtLayout->addWidget(solveBtn, 5, 0);

    filtLayout->setContentsMargins(10, 10, 100, 10);
}

void IntegrationTab::setLineEdit(QLineEdit *l) {
    l->setValidator(doubleValidator);
    l->setMaxLength(20);
    l->setMaximumSize(200, 25);
    l->setMinimumWidth(100);
}

void IntegrationTab::solve() {
    if (checkInput()) {
        Function fObj;
        compute(uBoundField->text().toDouble(),
                lBoundField->text().toDouble(),
                precisionField->text().replace(",", ".").toDouble(),
                funcsVector.at(btnGroup->checkedId()),
                fObj);
        answerField->setText("---ОТВЕТ---\n\n\n\n\n\n\n\n Значение интеграла: "
                             + QString::number(getAnswIntegr(), 'g', 8)
                             + "\n\nКоличество разбиений: "
                             + QString::number(getPartsNumber())
                             + "\n\nПолученная порешность: "
                             + QString::number(getPrecision(), 'g', 2));
    }
}

bool IntegrationTab::checkInput() { // TODO it`s too ugly - change
    QString empty = "ну и где чиселка?";
    if (precisionField->text().replace(" ", "") == "" ||
        lBoundField->text().replace(" ", "") == "" ||
        uBoundField->text().replace(" ", "") == "") {
        if (precisionField->text().replace(" ", "") == "")
            setErr(empty, precisionField);

        if (lBoundField->text().replace(" ", "") == "")
            setErr(empty, lBoundField);

        if (uBoundField->text().replace(" ", "") == "")
            setErr(empty, uBoundField);
        return false;
    }

    double a = uBoundField->text().replace(",", ".").toDouble();
    double b = lBoundField->text().replace(",", ".").toDouble();
    double eps = precisionField->text().replace(" ", "").toDouble();
    if (a < b) {
        uBoundField->setText(QString::number(b));
        lBoundField->setText(QString::number(a));
    }
    if (eps < 0 )
        precisionField->setText(QString::number(eps*(-1)));
    return true;
}

void IntegrationTab::setErr(QString msg, QLineEdit *field) {
    QToolTip::showText(field->pos() + field->pos() / 4, msg, field);
    field->setStyleSheet("border: 1px solid red;");
}

void IntegrationTab::unsetErrPres() {
    unsetErr(precisionField);
}

void IntegrationTab::unsetErrLow() {
    unsetErr(lBoundField);
}

void IntegrationTab::unsetErrUpp() {
    unsetErr(uBoundField);
}

void IntegrationTab::unsetErr(QLineEdit *field) {
    field->setStyleSheet("border: none");
    field->setStyleSheet("border: 1px solid #C3A8A8");
}

void IntegrationTab::setUpFunctions() {

    funcsVector.push_back(&Function::function_0);

    funcsVector.push_back(&Function::function_1);

    funcsVector.push_back(&Function::function_2);

    funcsVector.push_back(&Function::function_3);
}