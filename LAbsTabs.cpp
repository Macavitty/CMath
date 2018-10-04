#include <QtWidgets/QVBoxLayout>
#include <QTabWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QLineEdit>
#include <QDoubleValidator>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include "LAbsTabs.h"

LAbsTabs::LAbsTabs(QWidget *parent) : QDialog(parent) {
    tabWidget = new QTabWidget;
    tabWidget->addTab(new LinerSystemTab, tr("СЛАУ"));
    tabWidget->addTab(new IntegrationTab(), tr("Интегрирование"));
    tabWidget->addTab(new Interpolation(), tr("Интерполирование"));
    tabWidget->addTab(new ODETab(), tr("ОДУ"));

    auto *mainLayout = new QVBoxLayout;

    // set menu
    menuBar = new QMenuBar;
    simpleMenu = new QMenu(tr("МЕНЮ"), this);
    exitAction = simpleMenu->addAction(tr("Выйти"));
    menuBar->addMenu(simpleMenu);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitProgramm()));
    // hot key
    keyCtrlW = new QShortcut(this);
    keyCtrlW->setKey(Qt::CTRL + Qt::Key_W);
    connect(keyCtrlW, SIGNAL(activated()), this, SLOT(exitProgramm()));

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    setWindowTitle(tr("Tab Dialog"));
}

void LAbsTabs::exitProgramm() {
    this->close();
}


// Tabs
LinerSystemTab::LinerSystemTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;

    gridGroupBox = new QGroupBox(tr(""));
    auto *matrixLayout = new QGridLayout;
    answerField = new QTextEdit();
    answerField->setPlainText(tr("--- ANSWER ---"));
    //task
    auto *cells = new QGridLayout;
    auto *validator = new QDoubleValidator;
    validator->setNotation(QDoubleValidator::ScientificNotation);
    for (auto i = 0; i < 20; i++) {
        for (auto j = 0; j < 20; j++) {
            taskField = new QLineEdit();
            taskField->setText("0");
            taskField->setValidator(new QDoubleValidator);
            taskField->setMaximumSize(30, 15);
            cells->addWidget(taskField, i, j);
            matrixA[i][j] = taskField;
        }
    }
    matrixLayout->addWidget(answerField, 0, 1);
    matrixLayout->addLayout(cells, 0, 0);
    gridGroupBox->setLayout(matrixLayout);

    filtGroupBox = new QGroupBox(tr(""));
    auto *filtLayout = new QFormLayout;
    setSlider();
    filtLayout->addRow(new QLabel(tr("Число неизвестных:")));
    filtLayout->addRow(numberSlider, numberLabel);
    filtGroupBox->setLayout(filtLayout);

    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(filtGroupBox);
    setLayout(mainLayout);
}

void LinerSystemTab::setSlider() {
    numberSlider = new QSlider;
    numberSlider->setOrientation(Qt::Horizontal);
    numberSlider->setFixedWidth(300);
    numberSlider->setMaximum(20);
    numberSlider->setMinimum(1);
    numberSlider->setValue(20);
    numberSlider->setSingleStep(1);
    numberLabel = new QLabel;
    numberLabel->setText("20");
    connect(numberSlider, SIGNAL(valueChanged(int)), this, SLOT(changeNumber(int)));
}

void LinerSystemTab::changeNumber(int value) {
    numberLabel->setText(QString::fromStdString(std::to_string(value)));
    for (auto i = value; i < 20; i++) {
        for (auto j = 0; j < 20; j++) {
            matrixA[i][j]->setText("0");
            matrixA[i][j]->setEnabled(false);
            matrixA[j][i]->setText("0");
            matrixA[j][i]->setEnabled(false);
        }
    }
    for (auto i = 0; i < value; i++) {
        for (auto j = 0; j < value; j++) {
            matrixA[i][j]->setEnabled(true);
        }
    }
}

IntegrationTab::IntegrationTab(QWidget *parent) : QWidget(parent) {

}

Interpolation::Interpolation(QWidget *parent) : QWidget(parent) {

}

ODETab::ODETab(QWidget *parent) : QWidget(parent) {

}
