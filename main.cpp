#include <QtWidgets/QApplication>
#include <QMainWindow>
#include "LAbsTabs.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QString title = "COMPUTATIONAL MATH";
    LAbsTabs labs;
    labs.setMinimumSize(1000, 900);
    labs.setMaximumSize(1700, 1000);
    labs.resize(1700, 1000);
    labs.show();
    return app.exec();
}
