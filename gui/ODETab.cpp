#include "ODETab.h"

#define MAX_EDIT_CHARS 9

static void tuneLineEdit(QLineEdit *l){
    l->setMaxLength(MAX_EDIT_CHARS);
    l->setMaximumSize(150, 30);
    l->setMinimumWidth(100);
}

static void tuneLineEdit(QLineEdit *l, QValidator *v) {
    l->setValidator(v);
    tuneLineEdit(l);
}

static void setBtnGroup(QButtonGroup *btnGroup, QRadioButton *f0, QRadioButton *f1) {

    f0->setStyleSheet("font: 20px; color: #181322;");
    f1->setStyleSheet("font: 20px; color: #181322");

    f0->setIcon(QIcon("gui/img/ode_linear.png"));
    f1->setIcon(QIcon("gui/img/ode_quadr.png"));

    f0->setIconSize(QSize(300, 55));
    f1->setIconSize(QSize(300, 55));

    btnGroup->addButton(f0, 0);
    btnGroup->addButton(f1, 1);

    f0->setChecked(true);
}

static void prettyAnsField(QTextEdit* field, int w, int h){
    field->setStyleSheet("background : white; "
                               "border: 1px solid #C3A8A8; "
                               "border-radius: 7px; "
                               "font: 12px; "
                               "color: #181322");
    field->setFixedSize(w, h);
    field->setMinimumSize(w, h);
    field->setAlignment(Qt::AlignCenter);
}

static void unsetErr(QLineEdit *field) {
    field->setStyleSheet("border: none");
    field->setStyleSheet("border: 1px solid #C3A8A8");
}

static void setErr(QString msg, QLineEdit *field) {
    QToolTip::showText(field->pos(), msg, field);
    field->setStyleSheet("border: 1px solid red;");
}


ODETab::ODETab(QWidget *parent) : QWidget(parent) {

    auto *mainLayout = new QHBoxLayout;
    auto *paramLayout = new QVBoxLayout;
    QWidget *stab = new QWidget;

    QDoubleValidator *doubleValidator = new QDoubleValidator;

    precisionField  = new QLineEdit;
    x0Field  = new QLineEdit;
    y0Field  = new QLineEdit;
    endXField  = new QLineEdit;
    btnGroup = new QButtonGroup;

    QTextEdit *hField = new QTextEdit;

    chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    series = new QLineSeries();
    serInput  = new QScatterSeries();
    QValueAxis *axisY = new QValueAxis;
    QValueAxis *axisX = new QValueAxis;

    QLabel *l0 = new QLabel("Начальные условия:"),
            *l1 = new QLabel("x0:"),
            *l2 = new QLabel("y0:"),
            *l3 = new QLabel("Конец отрезка :"),
            *l4 = new QLabel("Точность:");
    auto *forms_1 = new QFormLayout;

    QPushButton *solveBtn = new QPushButton("Расчитать");
    QRadioButton *funcBtn_0 = new QRadioButton,
               *funcBtn_1 = new QRadioButton;

    doubleValidator->setNotation(QDoubleValidator::ScientificNotation);
    
    // build view

    setPlotArea(chart, chartView, axisX, axisY);
    setBtnGroup(btnGroup, funcBtn_0, funcBtn_1);

    tuneLineEdit(x0Field, doubleValidator);
    tuneLineEdit(y0Field, doubleValidator);
    tuneLineEdit(endXField, doubleValidator);
    tuneLineEdit(precisionField, doubleValidator);
    prettyAnsField(hField, 400, 200);
    /*
        connect(precisionField, SIGNAL(editingFinished()), this, SLOT(unsetErrPres()));
        connect(lBoundField, SIGNAL(editingFinished()), this, SLOT(unsetErrLow()));
        connect(uBoundField, SIGNAL(editingFinished()), this, SLOT(unsetErrUpp()));
    */


    l0->setStyleSheet("font: 16px");
    l1->setStyleSheet("font: 16px");
    l2->setStyleSheet("font: 16px");
    l3->setStyleSheet("font: 16px");
    l4->setStyleSheet("font: 16px");

    forms_1->addRow(l1, x0Field);
    forms_1->addRow(l2, y0Field);
    forms_1->addRow(l3, endXField);
    forms_1->addRow(l4, precisionField);
    forms_1->setAlignment(Qt::AlignLeft);

    stab->setLayout(forms_1);
    paramLayout->addWidget(funcBtn_0, 0, Qt::AlignTop);
    paramLayout->addWidget(funcBtn_1, 0, Qt::AlignTop);
    paramLayout->addWidget(stab, 1, Qt::AlignLeft);
    paramLayout->addWidget(solveBtn, 10, Qt::AlignTop);
    //paramLayout->addWidget(hField, 10, Qt::AlignTop);

    mainLayout->addWidget(chartView, 0, Qt::AlignLeft);
    mainLayout->addLayout(paramLayout);

    setLayout(mainLayout);

    // button(s)
    connect(solveBtn, SIGNAL(clicked()), this, SLOT(solve()));
    prettyBtn(solveBtn, 250, 40, "#115404", "#C3A8A8");
}

bool ODETab::validateInput(){
    QString eS = precisionField->text().replace(",", "."),
            x0S = x0Field->text().replace(",", "."),
            y0S = y0Field->text().replace(",", "."),
            endxS = endXField->text().replace(",", ".");

    if (eS == "" || x0S == "" || y0S == "" || endxS == ""){
        if (eS == "") setErr("", precisionField);
        if (x0S == "") setErr("", x0Field);
        if (y0S == "") setErr("", y0Field);
        if (endxS == "") setErr("", endXField);
        return false;
    }

    double x0 = x0S.toDouble();
    double endx = endxS.toDouble();
    if (endx < x0){
        setErr("", x0Field);
        setErr("", endXField);
        return false;
    }
    if (eS.toDouble() <= 0) precisionField->setText("0,0001");
    else if (eS.toDouble() >= 1) precisionField->setText("0,1");

    return true;

}

void ODETab::prettyBtn(QPushButton* btn,
                                 int w, int h, QString color,
                                 QString back){
    btn->setStyleSheet("color : " + color + "; background :" + back);
    btn->setMaximumWidth(w);
    btn->setMinimumWidth(w);
    btn->setMinimumHeight(h);
}

void ODETab::prettyBtn(QPushButton* btn, int w, int h, QString back){
    prettyBtn(btn, w, h, "black", back);
}

void ODETab::prettyCoeff(QTextEdit* field, int w, int h){
    field->setStyleSheet("background : white; "
                               "border: 1px solid #C3A8A8; "
                               "border-radius: 7px; "
                               "font: 12px; "
                               "color: #181322");
    field->setFixedSize(w, h);
    field->setMinimumSize(w, h);
    field->setAlignment(Qt::AlignCenter);
}

void ODETab::solve(){
    unsetErr(precisionField);
    unsetErr(x0Field);
    unsetErr(y0Field);
    unsetErr(endXField);
    if (validateInput()){
        double e = precisionField->text().replace(",", ".").toDouble(),
                x0 = x0Field->text().replace(",", ".").toDouble(),
                y0 = y0Field->text().replace(",", ".").toDouble(),
                endx = endXField->text().replace(",", ".").toDouble();
        redrawPlot(odeSolve(btnGroup->checkedId(), x0, endx + 1, y0, e));
    }

}

void ODETab::redrawPlot(QList<QPair<double, double>> *dots){

    series->clear();

    double maxX = endXField->text().replace(",", ".").toDouble(),
           maxY = pow(10, MAX_EDIT_CHARS + 1) * (-1),
           minX = x0Field->text().replace(",", ".").toDouble(),
           minY = pow(10, MAX_EDIT_CHARS + 1);

    // fill appr function series
    for (auto i = 0; i < dots->size(); i++){
        double y = dots->at(i).second;
        series->append(dots->at(i).first, y);
        maxY = max(y, maxY);
        minY = min(y, minY);
    }

    int steps = 420;
    double step = (maxX - minX)/steps;
    double delta = maxX - minX;
    if (delta > 100) delta = 10;
    else if (delta < 3) delta = 0.2;
    else delta = 1;
    minX -= step*10;
    maxX += step*10;
    minY -= step*10;
    maxY += step*10;

    int tick = 20;

    scaleAxes(chart->axisX(), minX-delta, maxX+delta, tick);
    scaleAxes(chart->axisY(), minY-delta, maxY+delta, tick);

}

void ODETab::showErr(QString msg, QWidget *w) {
    QToolTip::showText(w->pos()*60/7, msg, w);
}

void ODETab::scaleAxes(QAbstractAxis* a, double min, double max, int step){
    a->setMin(min);
    a->setMax(max);
    ((QValueAxis*)a)->setTickCount(step);
}

void ODETab::setPlotArea(QChart *chart, QChartView *view, QValueAxis *x, QValueAxis *y){

    series->setName("искомая функция");

    // add series to chart
    chart->addSeries(series);

    // legend settings
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeCircle);

    // x axis
    x->setLabelFormat("%.2f");
    x->setTitleText("X");
    chart->addAxis(x, Qt::AlignBottom);
    series->attachAxis(x);

    // y axis
    y->setLabelFormat("%.2f");
    y->setTitleText("Y");
    chart->addAxis(y, Qt::AlignLeft);
    series->attachAxis(y);

    view->setFixedHeight(1000);
    view->setFixedWidth(1000);
    view->setRenderHint(QPainter::Antialiasing);
}


