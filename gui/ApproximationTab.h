#ifndef COMPMATH_APPROXIMATIONTAB_H
#define COMPMATH_APPROXIMATIONTAB_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <memory>
#include "algos/ApproximationSolver.h"
#include <iostream>


using namespace QtCharts;
using namespace std;


class ApproximationTab : public QWidget {
Q_OBJECT
public:
    explicit ApproximationTab(QWidget *parent = nullptr);

private slots:
    void addDot();
    void rmDot();
    void solve();

private:
    int MAX_EDIT_CHARS = 9;
    QDoubleValidator *doubleValidator;
    QChart *chart;
    QTableWidget *table;
    QLineSeries *serBefore;
    QLineSeries *serAfter;
    QScatterSeries *serInput;
    QList<QLineEdit*> *columnX;
    QList<QLineEdit*> *columnY;
    unique_ptr<QGridLayout> _contentLayout;
    void setPlotArea(QChart*, QChartView*, QValueAxis*, QValueAxis*);
    void setFuncArea(QButtonGroup*, QVBoxLayout*);
    void setTableArea();
    void prettyBtn(QPushButton*, int w, int h, QString color, QString back);
    void prettyBtn(QPushButton*, int w, int h,QString back);
    void prettyCoeff(QTextEdit*, int w, int h);
    void showErr(QString, QWidget*);
    void addDot(int);
    bool hasEmptyCells();
    void redrawPlot();
    void scaleAxes(QAbstractAxis*, double min, double max, int step);
    void tuneCell(QLineEdit*);
};


#endif //COMPMATH_APPROXIMATIONTAB_H
