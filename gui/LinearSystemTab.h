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
    void changeNumber(int value);
    void reset();
    void setRandom();
    void takeFromFile();
    void solve();

private:
    QLineEdit *matrixA[20][20];
    QLineEdit *matrixB[20];
    QDoubleValidator *doubleValidator;
    QGroupBox *gridGroupBox, *filtGroupBox, *buttonsGroupBox;
    QTextEdit *answerField;
    QLineEdit *precisionField;
    QSlider *numberSlider;
    QLabel *numberLabel;
    QPushButton *randButton, *fileButton, *solveButton, *resetButton;

    void setSlider();
    void setAMatrix(QGridLayout *aCells);
    void setBMatrix(QGridLayout *bCells);
    void setButtons();
    double randomDouble(double lower, double upper);
};

#endif //COMPMATH_LINEARSYSTEMTAB_H
