#ifndef COMPMATH_APPROXIMATIONTAB_H
#define COMPMATH_APPROXIMATIONTAB_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <memory>

using namespace QtCharts;
using namespace std;


class ApproximationTab : public QWidget {
Q_OBJECT
public:
    explicit ApproximationTab(QWidget *parent = nullptr);
private:
    unique_ptr<QGridLayout> _contentLayout;
    void setPlotArea(QChart*, QChartView*, QLineSeries*, QLineSeries*, QValueAxis*, QValueAxis*);
    void setFuncArea(QButtonGroup*, QVBoxLayout*);
    void setTableArea(QTableWidget*);
    void prettyBtn(QPushButton*, int w, int h, QString color, QString back);
    void prettyBtn(QPushButton*, int w, int h,QString back);
    void prettyCoeff(QTextEdit*, int w, int h);
};


#endif //COMPMATH_APPROXIMATIONTAB_H
