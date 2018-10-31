
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
#include "InterpolationTab.h"
#include "ODETab.h"

class QTabWidget;
class QMenu;
class QMenuBar;

class LAbsTabs : public QDialog{
Q_OBJECT
public:
    explicit LAbsTabs(QWidget *parent = nullptr);
private slots:
    void exitProgramm();
private:
    LinearSystemTab *linearSystemTab;
    IntegrationTab *integrationTab;
    InterpolationTab *interpolationTab;
    ODETab *odeTab;
    QTabWidget *tabWidget;
    QMenu *simpleMenu;
    QMenuBar *menuBar;
    QAction *exitAction, *aboutAction;
    QShortcut *keyCtrlW;
};

#endif //COMPMATH_LABSTABS_H
