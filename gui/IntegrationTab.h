#ifndef COMPMATH_INTEGRATIONTAB_H
#define COMPMATH_INTEGRATIONTAB_H
#include <QDialog>
#include <QtWidgets/QShortcut>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QDoubleValidator>

class IntegrationTab : public QWidget {

public:
    explicit IntegrationTab(QWidget *parent = nullptr);
};

#endif //COMPMATH_INTEGRATIONTAB_H

