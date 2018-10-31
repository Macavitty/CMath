//
// Created by tania on 27.10.18.
//

#include "InterpolationTab.h"

InterpolationTab::InterpolationTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;
    auto *label = new QLabel("Sorry, this tab is under development");
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);
    setLayout(mainLayout);
}