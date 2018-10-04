#include <QtWidgets/QApplication>
#include <QMainWindow>
#include "LAbsTabs.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QString title = "COMPUTATIONAL MATH";
    LAbsTabs labs;
    labs.setMinimumSize(900, 900);
    labs.resize(1200, 1000);
    labs.show();

    return app.exec();
}
