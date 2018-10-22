#ifndef COMPMATH_LINEARSYSTEMTAB_H
#define COMPMATH_LINEARSYSTEMTAB_H

#include <QDialog>
#include <QTabWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QDoubleValidator>
#include <math.h>
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
    QLineEdit *matrix[MAX_N][MAX_N + 2];
    QDoubleValidator *doubleValidator;
    QGroupBox *gridGroupBox, *filtGroupBox, *buttonsGroupBox;
    QGridLayout *cellsLayout;
    QTextEdit *answerField;
    QLineEdit *precisionField;
    QSlider *numberSlider;
    QLabel *numberLabel;
    QPushButton *randBtn, *fileBtn, *solveBtn, *resetBtn;

    void setSlider();

    void clearAnswerField();

    void setAMatrix(QGridLayout *aCells);

    QLineEdit *createCell(QString text);

    void setButtons();

    double randomDouble(double lower, double upper);
};

#endif //COMPMATH_LINEARSYSTEMTAB_H
