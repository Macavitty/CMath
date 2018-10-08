#include "IntegrationTab.h"

IntegrationTab::IntegrationTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;
    auto *label= new QLabel("Sorry, this tab is under development");
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);
    setLayout(mainLayout);
}