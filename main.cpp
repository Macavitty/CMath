#include <QtWidgets/QApplication>
#include <QMainWindow>
#include "gui/LAbsTabs.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    LAbsTabs labs;
    labs.setMinimumSize(1200, 900);
    labs.setMaximumSize(1500, 900);
    labs.resize(1700, 1000);

    /*QFile File("styles.scss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);*/
    app.setWindowIcon(QIcon("gui/ico/zomb.png")); // maze icon is available
    labs.show();
    return QApplication::exec();
}
