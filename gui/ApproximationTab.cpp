#include "ApproximationTab.h"

ApproximationTab::ApproximationTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QHBoxLayout;
    auto *leftLayout = new QVBoxLayout;
    auto *paramLayout = new QHBoxLayout;
    auto *btnArea = new QGridLayout;
    auto *btnGroupBox = new QGroupBox;
    btnGroupBox->setLayout(btnArea);

    doubleValidator = new QDoubleValidator;
    doubleValidator->setNotation(QDoubleValidator::ScientificNotation);

    columnX = new QList<QLineEdit*>;
    columnY = new QList<QLineEdit*>;
    for (int i = 0 ; i < 20; i++){
        QLineEdit *x = new QLineEdit;
        QLineEdit *y = new QLineEdit;
        columnX->append(x);
        columnY->append(y);
        x->setMaxLength(MAX_EDIT_CHARS);
        y->setMaxLength(MAX_EDIT_CHARS);
        x->setValidator(doubleValidator);
        y->setValidator(doubleValidator);
    }

    //QSignalMapper *mapper = new QSignalMapper(this);

    // vars for plot
    chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    serBefore = new QLineSeries();
    serAfter = new QLineSeries();
    serInput = new QScatterSeries();
    QValueAxis *axisY = new QValueAxis;
    QValueAxis *axisX = new QValueAxis;
    setPlotArea(chart, chartView, axisX, axisY);

    // vars for appr func
    QButtonGroup *btnGroup = new QButtonGroup;
    QVBoxLayout *funcLayout = new QVBoxLayout;
    setFuncArea(btnGroup, funcLayout);

    // vars for table
    table = new  QTableWidget();
    setTableArea();

    // buttons
    QPushButton *addDotBtn = new QPushButton("Добавить точку");
    QPushButton *rmDotBtn = new QPushButton("Удалить точку");
    QPushButton *solveBtn = new QPushButton("ВЖУХ");


    connect(solveBtn, SIGNAL(clicked()), this, SLOT(solve()));
    connect(rmDotBtn, SIGNAL(clicked()), this, SLOT(rmDot()));
    connect(addDotBtn, SIGNAL(clicked()), this, SLOT(addDot()));
    //connect(addDotBtn, SIGNAL(clicked()), mapper, SLOT(map()));
    //connect(mapper, SLOT(mapped(QWidget *)), this, SLOT(addDot(QWidget*)));

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

void ApproximationTab::setPlotArea(QChart *chart, QChartView *view, QValueAxis *x, QValueAxis *y){
    chart->setTitle("Very nise plot");

    serBefore->setName("func");
    serAfter->setName("another func");
    serInput->setName("набор заданных изначально точек");
    serInput->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    serInput->setMarkerSize(11.0);
    // add series to chart
    chart->addSeries(serBefore);
    chart->addSeries(serAfter);
    chart->addSeries(serInput);

    // legend settings
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeCircle);

    // x axis
    x->setLabelFormat("%.2f");
    x->setTitleText("X");
    chart->addAxis(x, Qt::AlignBottom);
    serBefore->attachAxis(x);
    serAfter->attachAxis(x);
    serInput->attachAxis(x);

    // y axis
    y->setLabelFormat("%.2f");
    y->setTitleText("Y");
    chart->addAxis(y, Qt::AlignLeft);
    serBefore->attachAxis(y);
    serAfter->attachAxis(y);
    serInput->attachAxis(y);

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

void ApproximationTab::setTableArea(){
    table->setColumnCount(2);

    table->setMaximumWidth(210);
    table->setMinimumWidth(210);
    table->setMaximumHeight(300);
    table->setMinimumHeight(300);

    QTableWidgetItem *headerX = new QTableWidgetItem("X");
    QTableWidgetItem *headerY = new QTableWidgetItem("Y");
    table->setHorizontalHeaderItem(0, headerX);
    table->setHorizontalHeaderItem(1, headerY);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    addDot(7);
    //table->horizontalHeader()->setDefaultSectionSize(94);
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

void ApproximationTab::rmDot(){
    QModelIndexList rows = table->selectionModel()->selectedRows();
    int total = table->rowCount();
    int selected = rows.size();
    if (selected == 0){
        showErr("Выделите хотя бы одну строку", table);
    }
    else if (total - selected < 3){
        showErr("Для аппроксимации необходимо\n хотя бы три точки", table);
    }
    else {
        while (!rows.empty()){
            table->removeRow(rows[0].row());
            rows = table->selectionModel()->selectedRows();
        }
    }
}

void ApproximationTab::addDot(){
    if (table->rowCount() == 20){
        showErr("Пожалуй хватит", table);
    }
    else {
        int rowIndx = table->rowCount();
        table->insertRow(rowIndx);
        QLineEdit *x = columnX->takeAt(rowIndx);
        QLineEdit *y = columnY->takeAt(rowIndx);
        x->setText("");
        y->setText("");
        table->setCellWidget(rowIndx, 0, x);
        table->setCellWidget(rowIndx, 1, y);
    }
}

void ApproximationTab::addDot(int num){
   for (auto i = 0; i < num; i++) addDot();
}

void ApproximationTab::solve(){
    if (!hasEmptyCells()){
        // check if have same dots!
        showErr("Заполните все ячейки", table);
    }
    else {
        redrawPlot();
    }
}

void ApproximationTab::showErr(QString msg, QWidget *w) {
    QToolTip::showText(w->pos()*60/7, msg, w);
}

bool ApproximationTab::hasEmptyCells(){
    for (auto i = 0; i < table->rowCount(); i++){
        /* BEWARE somehow columnX->takeAt(i) doesn`t work */
        if (((QLineEdit*)table
             ->cellWidget(i, 0))
                ->text()
                .replace(" ", "") == "" ||
                ((QLineEdit*)table
                             ->cellWidget(i, 1))
                                ->text()
                                .replace(" ", "") == "") {
           return false;
        }
    }

    return true;
}

void ApproximationTab::redrawPlot(){

    serInput->clear();
    serBefore->clear();
    serAfter->clear();

    double maxX = pow(10, MAX_EDIT_CHARS + 1) * (-1),
           maxY = pow(10, MAX_EDIT_CHARS + 1) * (-1),
           minX = pow(10, MAX_EDIT_CHARS + 1),
           minY = pow(10, MAX_EDIT_CHARS + 1);
    for (auto i = 0; i < table->rowCount(); i++){
        double x = ((QLineEdit*)table->cellWidget(i, 0))->text().toDouble();
        double y = ((QLineEdit*)table->cellWidget(i, 1))->text().toDouble();
        maxX = max(x, maxX);
        maxY = max(y, maxY);
        minX = min(x, minX);
        minY = min(y, minY);
        serInput->append(x, y);
    }
    int step = (int)(maxX - minX)/2 <= 18 ? (int)(maxX - minX) : (int)(maxX - minX)/2;
    scaleAxes(chart->axisX(), minX-1, maxX+1, step);
    step = (int)(maxY - minY) <= 18 ? (int)(maxY - minY) : (int)(maxY - minY)/2;
    scaleAxes(chart->axisY(), minY-1, maxY+1, step);

}
void ApproximationTab::scaleAxes(QAbstractAxis* a, double min, double max, int step){
    a->setMin(min);
    a->setMax(max);
    ((QValueAxis*)a)->setTickCount(step);
}








