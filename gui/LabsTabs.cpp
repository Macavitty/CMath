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
#include <QQuickWidget>
#include "LabsTabs.h"

LAbsTabs::LAbsTabs(QWidget *parent) : QDialog(parent) {
    tabWidget = new QTabWidget;
    linearSystemTab = new LinearSystemTab;
    integrationTab = new IntegrationTab;
    approximationTab = new ApproximationTab;

    /*QQuickWidget *odeTab = new QQuickWidget;
    odeTab->setSource(QUrl::fromLocalFile("last_tab.qml"));
    */
    odeTab = new ODETab;

    tabWidget->addTab(linearSystemTab, tr("СЛАУ"));
    tabWidget->addTab(integrationTab, tr("Интегрирование"));
    tabWidget->addTab(approximationTab, tr("Аппроксимация"));
    tabWidget->addTab(odeTab, tr("ОДУ"));
    tabWidget->setCurrentWidget(odeTab);

    auto *mainLayout = new QVBoxLayout;

    // set menu
    menuBar = new QMenuBar;
    simpleMenu = new QMenu(tr("МЕНЮ"), this);
    // about
    QDialog *aboutDialog = new QDialog;
    aboutDialog->setWindowTitle("О ПРОГРАММЕ");
    auto *aboutLayout = new QGridLayout();
    QLabel *header = new QLabel("\u2a33 \u2a33 \u2a33\n"),
            *content = new QLabel("\n\tПриветствую!\n\n\tДанная программа пилится в рамках "
                                  "лабораторных работ\n\tпо дисциплине \u00abВычислительная математика\u00bb "
                                  "\n\t( ИТМО, (уже не)кафедра ВТ, 2 курс ).\n\tДелает ст. Прилуцкая Таня.\n\n\t"
                                  "Что реализовано и будет реализованно:\n\n\t"
                                  "\u16dc  Решение СЛАУ методом Гаусса-Зейделя\n\t"
                                  "\u16dc  Интергирование методом трапеций\n\t"
                                  "\u16dc  Аппроксимация функций мнк\n\t"
                                  "\u16dc  Решение ОДУ методом Адамса (ждём)\n"),
                    *trueFooter = new QLabel("\tEnjoy, так сказать\n");
    header->setAlignment(Qt::AlignCenter);
    aboutLayout->addWidget(header);
    aboutLayout->addWidget(content);
    aboutLayout->addWidget(trueFooter);
    aboutLayout->addWidget(header);
    aboutDialog->setLayout(aboutLayout);
    //aboutDialog->setFixedWidth(content->geometry().width());
    aboutAction = simpleMenu->addAction(tr("О программе"));
    connect(aboutAction, SIGNAL(triggered()), aboutDialog, SLOT(show()));
    // exit
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

    setWindowTitle(tr("ЧИСЛЕННЫЕ МЕТОДЫ"));
}

void LAbsTabs::exitProgramm() {
    this->close();
}
