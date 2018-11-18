//
// Created by tania on 27.10.18.
//

#include "InterpolationTab.h"

InterpolationTab::InterpolationTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(label);
    scene = new QGraphicsScene;
    scene->setBackgroundBrush(Qt::red);
    
    graphicsView = new QGraphicsView(scene);
    graphicsView->setFixedSize(1000, 800);
    mainLayout->addWidget(graphicsView);
    setLayout(mainLayout);
}