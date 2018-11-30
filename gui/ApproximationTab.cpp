#include "ApproximationTab.h"

ApproximationTab::ApproximationTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QHBoxLayout;
    auto *leftLayout = new QVBoxLayout;
    auto *paramLayout = new QHBoxLayout;
    auto *btnArea = new QGridLayout;
    auto *btnGroupBox = new QGroupBox;
    btnGroupBox->setLayout(btnArea);

    // vars for plot
    QChart *m_chart = new QChart();
    QChartView *chartView = new QChartView(m_chart);
    QLineSeries *m_serBefore = new QLineSeries();
    QLineSeries *m_serAfter = new QLineSeries();
    QValueAxis *axisY = new QValueAxis;
    QValueAxis *axisX = new QValueAxis;
    setPlotArea(m_chart,chartView, m_serBefore, m_serAfter, axisX, axisY);

    // vars for appr func
    QButtonGroup *btnGroup = new QButtonGroup;
    QVBoxLayout *funcLayout = new QVBoxLayout;
    setFuncArea(btnGroup, funcLayout);

    // vars for table
    QTableWidget *table = new  QTableWidget(9, 2);
    setTableArea(table);

    // buttons
    QPushButton *addDotBtn = new QPushButton("Добавить точку");
    QPushButton *rmDotBtn = new QPushButton("Удалить точку");
    QPushButton *solveBtn = new QPushButton("ВЖУХ");
    prettyBtn(solveBtn, 250, 30, "#115404", "#C3A8A8");
    prettyBtn(rmDotBtn, 202, 30, "#C3A8A8");
    prettyBtn(addDotBtn, 202, 30, "#C3A8A8");

    // coefficients
    QTextEdit *coeffField = new QTextEdit;
    prettyCoeff(coeffField, 450, 280);

    // building
    leftLayout->setContentsMargins(0,0,0,0);

    btnArea->addWidget(rmDotBtn, 0, 0);
    btnArea->addWidget(addDotBtn, 1, 0);

    paramLayout->addLayout(funcLayout);
    paramLayout->addWidget(table, 0, Qt::AlignTop);

    leftLayout->addWidget(new QLabel("Выберите аппроксимирующую функцию и задайте минимум 3 точки:"), 0, Qt::AlignCenter);
    leftLayout->addLayout(paramLayout);
    leftLayout->addWidget(btnGroupBox, 0, Qt::AlignRight);
    leftLayout->addWidget(solveBtn, 0, Qt::AlignCenter);
    leftLayout->addWidget(new QLabel("Значения аппроксимирующих коэффициентов:"), 0, Qt::AlignCenter);
    leftLayout->addWidget(coeffField, 0, Qt::AlignTop);

    mainLayout->addWidget(chartView);
    mainLayout->addLayout(leftLayout);

    setLayout(mainLayout);
}

void ApproximationTab::setPlotArea(QChart *chart, QChartView *view, QLineSeries *sBefore, QLineSeries *sAfter, QValueAxis *x, QValueAxis *y){
    chart->setTitle("Very nise plot");

    sBefore->setName("func");
    sAfter->setName("another func");
    // add series to chart
    chart->addSeries(sBefore);
    chart->addSeries(sAfter);

    // legend settings
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeCircle);

    // x axis
    x->setLabelFormat("%.2f");
    x->setTitleText("X");
    chart->addAxis(x, Qt::AlignBottom);
    sBefore->attachAxis(x);
    sAfter->attachAxis(x);

    // y axis
    y->setLabelFormat("%.2f");
    y->setTitleText("Y");
    chart->addAxis(y, Qt::AlignLeft);
    sBefore->attachAxis(y);
    sAfter->attachAxis(y);

    view->setFixedHeight(1000);
    view->setFixedWidth(1000);
    view->setRenderHint(QPainter::Antialiasing);
}

void ApproximationTab::setFuncArea(QButtonGroup *btnGroup, QVBoxLayout *funcLayout){
     QRadioButton *funcBtn_0,
                *funcBtn_1,
                *funcBtn_2,
                *funcBtn_3,
                *funcBtn_4;
     funcBtn_0 = new QRadioButton();
     funcBtn_1 = new QRadioButton();
     funcBtn_2 = new QRadioButton();
     funcBtn_3 = new QRadioButton();
     funcBtn_4 = new QRadioButton();

     funcBtn_0->setStyleSheet("color: #181322;");
     funcBtn_1->setStyleSheet("color: #181322");
     funcBtn_2->setStyleSheet("color: #181322");
     funcBtn_3->setStyleSheet("color: #181322");
     funcBtn_4->setStyleSheet("color: #181322");

     funcBtn_0->setIcon(QIcon("gui/img/linear.png"));
     funcBtn_1->setIcon(QIcon("gui/img/quadr.png"));
     funcBtn_2->setIcon(QIcon("gui/img/expon.png"));
     funcBtn_3->setIcon(QIcon("gui/img/expon_exp.png"));
     funcBtn_4->setIcon(QIcon("gui/img/ln.png"));

     funcBtn_0->setIconSize(QSize(200, 60));
     funcBtn_1->setIconSize(QSize(200, 60));
     funcBtn_2->setIconSize(QSize(200, 60));
     funcBtn_3->setIconSize(QSize(200, 60));
     funcBtn_4->setIconSize(QSize(200, 60));

     funcBtn_0->setMaximumSize(200, 30);
     funcBtn_1->setMaximumSize(200, 30);
     funcBtn_2->setMaximumSize(200, 30);
     funcBtn_3->setMaximumSize(200, 30);
     funcBtn_4->setMaximumSize(200, 30);

     btnGroup->addButton(funcBtn_0, 0);
     btnGroup->addButton(funcBtn_1, 1);
     btnGroup->addButton(funcBtn_2, 2);
     btnGroup->addButton(funcBtn_3, 3);
     btnGroup->addButton(funcBtn_4, 4);

     funcBtn_0->setChecked(true);

     funcLayout->addWidget(funcBtn_0, 0, Qt::AlignTop);
     funcLayout->addWidget(funcBtn_1, 0, Qt::AlignTop);
     funcLayout->addWidget(funcBtn_2, 0, Qt::AlignTop);
     funcLayout->addWidget(funcBtn_3, 0, Qt::AlignTop);
     funcLayout->addWidget(funcBtn_4, 0, Qt::AlignTop);
     funcLayout->addWidget(funcBtn_2, 0, Qt::AlignTop);
}

void ApproximationTab::setTableArea(QTableWidget *table){
    table->verticalHeader()->hide();
    table->setMaximumWidth(202);
    table->setMinimumWidth(202);
    table->setMaximumHeight(300);
    table->setMinimumHeight(300);

    QTableWidgetItem *headerX = new QTableWidgetItem("X");
    QTableWidgetItem *headerY = new QTableWidgetItem("Y");
    table->setHorizontalHeaderItem(0, headerX);
    table->setHorizontalHeaderItem(1, headerY);
    table->horizontalHeader()->setDefaultSectionSize(100);
}

void ApproximationTab::prettyBtn(QPushButton* btn, int w, int h, QString color, QString back){
    btn->setStyleSheet("color : " + color + "; background :" + back);
    btn->setMaximumWidth(w);
    btn->setMinimumWidth(w);
    btn->setMinimumHeight(h);
}

void ApproximationTab::prettyBtn(QPushButton* btn, int w, int h, QString back){
    prettyBtn(btn, w, h, "black", back);
}

void ApproximationTab::prettyCoeff(QTextEdit* field, int w, int h){
    field->setStyleSheet("background : white; "
                               "border: 1px solid #C3A8A8; "
                               "border-radius: 7px; "
                               "font: 15px; "
                               "color: #181322");
    field->setFixedSize(w, h);
    field->setMinimumSize(w, h);
}





















