
#ifndef COMPMATH_LABSTABS_H
#define COMPMATH_LABSTABS_H
#include <QDialog>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>

class QTabWidget;
class QMenu;
class QMenuBar;

// Tabs
class LinerSystemTab : public QWidget{
Q_OBJECT
public:
    explicit LinerSystemTab(QWidget *parent = nullptr);

private slots:
    void changeNumber(int value);

private:
    QLineEdit *matrixA[20][20];
    QGroupBox *gridGroupBox, *filtGroupBox ;
    QTextEdit *answerField;
    QLineEdit *taskField;
    QSlider *numberSlider;
    QLabel *numberLabel;

    void setSlider();

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
