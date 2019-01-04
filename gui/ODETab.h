#ifndef COMPMATH_ODETAB_H
#define COMPMATH_ODETAB_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <memory>
#include <istream>
#include "algos/ODESolver.h"
#include "algos/ApproximationSolver.h"

using namespace QtCharts;
using namespace std;

class ODETab : public QWidget {
Q_OBJECT
public:
    explicit ODETab(QWidget *parent = nullptr);

private slots:
    void solve();


private:
    QLineEdit *precisionField,
            *x0Field,
            *y0Field,
            *endXField;
    QGroupBox *groupBox;
    QButtonGroup *btnGroup;
    QLineSeries *series;
    QScatterSeries *serInput;
    QChart *chart;
    void setPlotArea(QChart*, QChartView*, QValueAxis* x, QValueAxis* y);
    void prettyBtn(QPushButton*, int w, int h, QString color, QString back);
    void prettyBtn(QPushButton*, int w, int h,QString back);
    void prettyCoeff(QTextEdit*, int w, int h);
    void showErr(QString, QWidget*);
    void redrawPlot(QList<double>* before, QList<double>* after, int);
    void scaleAxes(QAbstractAxis*, double min, double max, int step);
    QList<QPair<double, double>>* getInputDots();
    void fillCoeffArea(int, QList<double>* before, QList<double>* after);
    //void tuneLineEdit(QLineEdit *, QValidator *);
    double function(int f, double a, double b, double x);
    double function(int f, double a, double b, double c, double x);
    bool validateInput();
    void setErr(QString msg, QLineEdit*);
    void unsetErr(QLineEdit*);
    //void setBtnGroup();
    void redrawPlot(QList<QPair<double, double>> *dots, QList<double>* coeffs, int func);
};


#endif //COMPMATH_ODETAB_H
