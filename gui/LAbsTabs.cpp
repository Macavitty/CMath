#include <QtWidgets/QVBoxLayout>
#include <QTabWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QLineEdit>
#include <QDoubleValidator>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDir>
#include "LAbsTabs.h"

LAbsTabs::LAbsTabs(QWidget *parent) : QDialog(parent) {
    tabWidget = new QTabWidget;
    linearSystemTab = new LinearSystemTab;
    integrationTab = new IntegrationTab;
    tabWidget->addTab(linearSystemTab, tr("СЛАУ"));
    tabWidget->addTab(integrationTab, tr("Интегрирование"));
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

    setWindowTitle(tr("COMPUTATIONAL MATH"));
}

void LAbsTabs::exitProgramm() {
    this->close();
}

Interpolation::Interpolation(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;
    auto *label= new QLabel("Sorry, this tab is under development");
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);
    setLayout(mainLayout);
}

ODETab::ODETab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;
    auto *label= new QLabel("Sorry, this tab is under development");
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);
    setLayout(mainLayout);
}
