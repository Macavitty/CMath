#ifndef COMPMATH_LINEARSYSTEMTAB_H
#define COMPMATH_LINEARSYSTEMTAB_H

#include <QDialog>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QDoubleValidator>
#include "algos/LinearSystemSolver.h"


class LinearSystemTab : public QWidget {
Q_OBJECT
public:
    explicit LinearSystemTab(QWidget *parent = nullptr);

private slots:

    void changeNumber(int newN);

    void reset();

    void setRandom();

    void takeFromFile();

    void solve();

private:
    int currN;
    static const int MAX_N = 20;
    int matrixBColomn = MAX_N + 1;
    int equalityColomn = MAX_N;
    QLineEdit *matrixA[MAX_N][MAX_N + 2];
    QLineEdit *matrixB[MAX_N];
    QLineEdit *equalitySigns[MAX_N];
    QDoubleValidator *doubleValidator;
    QGroupBox *gridGroupBox, *filtGroupBox, *buttonsGroupBox;
    QGridLayout *aCells, *bCells;
    QTextEdit *answerField;
    QLineEdit *precisionField;
    QSlider *numberSlider;
    QLabel *numberLabel;
    QPushButton *randButton, *fileButton, *solveButton, *resetButton;

    void setSlider();

    void setAMatrix(QGridLayout *aCells);

    void setBMatrix(QGridLayout *bCells);

    QLineEdit *createCell(QString text);

    void setButtons();

    double randomDouble(double lower, double upper);
};

#endif //COMPMATH_LINEARSYSTEMTAB_H
