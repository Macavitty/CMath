
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
#include "LinearSystemTab.h"
#include "IntegrationTab.h"

class QTabWidget;
class QMenu;
class QMenuBar;

// Tabs
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
    LinearSystemTab *linearSystemTab;
    IntegrationTab *integrationTab;
    QTabWidget *tabWidget;
    QMenu *simpleMenu;
    QMenuBar *menuBar;
    QAction *exitAction, *aboutAction;
    QShortcut *keyCtrlW;
};

#endif //COMPMATH_LABSTABS_H
