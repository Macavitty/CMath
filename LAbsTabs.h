
#ifndef COMPMATH_LABSTABS_H
#define COMPMATH_LABSTABS_H
#include <QDialog>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QDoubleValidator>

class QTabWidget;
class QMenu;
class QMenuBar;

// Tabs
class LinearSystemTab : public QWidget{
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
class IntegrationTab : public QWidget {

public:
    explicit IntegrationTab(QWidget *parent = nullptr);
};
class Interpolation : public QWidget {

public:
    explicit Interpolation(QWidget *parent = nullptr);
};
class ODETab : public QWidget {
public:
    explicit ODETab(QWidget *parent = nullptr);
};

class LAbsTabs : public QDialog{
Q_OBJECT
public:
    explicit LAbsTabs(QWidget *parent = nullptr);
private slots:
    void exitProgramm();
private:
    QTabWidget *tabWidget;
    QMenu *simpleMenu;
    QMenuBar *menuBar;

    QAction *exitAction;
    QShortcut *keyCtrlW;
};

#endif //COMPMATH_LABSTABS_H
