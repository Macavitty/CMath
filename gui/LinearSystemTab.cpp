#include <QTabWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDir>
#include "LinearSystemTab.h"

LinearSystemTab::LinearSystemTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;
// TODO make consts for number
    // MATRIX
    gridGroupBox = new QGroupBox(tr(""));
    auto *matrixLayout = new QGridLayout;
    answerField = new QTextEdit();
    answerField->setPlainText(tr("--- ANSWER ---"));
    answerField->setFixedWidth(400);
    //task
    doubleValidator = new QDoubleValidator;
    doubleValidator->setNotation(QDoubleValidator::ScientificNotation);
    auto *aCells = new QGridLayout;
    auto *bCells = new QGridLayout;
    setAMatrix(aCells);
    setBMatrix(bCells);

    matrixLayout->addWidget(answerField, 0, 2);
    matrixLayout->addLayout(aCells, 0, 0);
    matrixLayout->addLayout(bCells, 0, 1);
    gridGroupBox->setLayout(matrixLayout);

    // FILT
    filtGroupBox = new QGroupBox(tr(""));
    auto *filtLayout = new QFormLayout;
    setSlider();
    filtLayout->addRow(new QLabel(tr("Число неизвестных:")), numberLabel);
    filtLayout->addRow(new QLabel(tr("")), numberSlider);
    precisionField = new QLineEdit;
    precisionField->setValidator(doubleValidator);
    precisionField->setMaxLength(20);
    precisionField->setMaximumSize(200, 15);
    filtLayout->addRow(new QLabel(tr("Точность:")), precisionField); // Точность ли?
    filtGroupBox->setLayout(filtLayout);

    setButtons();

    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(filtGroupBox);
    mainLayout->addWidget(buttonsGroupBox);
    setLayout(mainLayout);
}

void LinearSystemTab::setButtons() {
    buttonsGroupBox = new QGroupBox;
    auto *buttonsLayout = new QHBoxLayout;

    randButton = new QPushButton("Сгенерировать рандомно");
    fileButton = new QPushButton("Заполнить из файла");
    solveButton = new QPushButton("Решить");
    resetButton = new QPushButton("Сбросить");

    randButton->setMaximumWidth(180);
    fileButton->setMaximumWidth(180);
    resetButton->setMaximumWidth(180);
    solveButton->setMaximumWidth(180);
    randButton->setMinimumHeight(40);
    fileButton->setMinimumHeight(40);
    resetButton->setMinimumHeight(40);
    solveButton->setMinimumHeight(40);
    // TODO make stylesheet file
    randButton->setStyleSheet("color : black; background : #C3A8A8");
    fileButton->setStyleSheet("color : black; background : #C3A8A8");
    resetButton->setStyleSheet("color : #710C02; background : #C3A8A8");
    solveButton->setStyleSheet("color : #115404; background : #C3A8A8");

    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(randButton, SIGNAL(clicked()), this, SLOT(setRandom()));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(takeFromFile()));
    connect(solveButton, SIGNAL(clicked()), this, SLOT(solve()));

    buttonsLayout->addWidget(randButton);
    buttonsLayout->addWidget(fileButton);
    buttonsLayout->addWidget(resetButton);
    buttonsLayout->addWidget(solveButton);

    buttonsGroupBox->setLayout(buttonsLayout);
}

void LinearSystemTab::solve() {
    int n = numberSlider->value();
    double e = precisionField->text().replace(",", ".").toDouble();
    auto **A = new long double*[n], *B = new long double[n];
    for (int i = 0 ; i <n ; i++) A[i] = new long double[n];
   for (auto i = 0; i < n; i++){
        B[i] = matrixB[i]->text().replace(",", ".").toDouble();
        for (auto j = 0; j < n; j++){
            A[i][j] = matrixA[i][j]->text().replace(",", ".").toDouble();
        }
    }
    compute(A, B, n, e);
}

void LinearSystemTab::takeFromFile() {
    int n = numberSlider->value();
    QFile taskFile("linear_sys_task.txt");
    if (taskFile.exists()) {
        taskFile.open(QIODevice::ReadOnly);
        int j = -1;
        QString cell;
                foreach (QString s, QString(taskFile.readAll()).split(QRegExp("[\r\n]"), QString::SkipEmptyParts)) {
                j++;
                cell = s.section(" ", n, n).replace(",", ".");
                cell = cell == "" ? "0" : QString::number(cell.toDouble(), 'g', 5);
                matrixB[j]->setText(cell);
                for (int i = 0; i < n; i++) {
                    cell = s.section(" ", i, i).replace(",", ".");
                    cell = cell == "" ? "0" : QString::number(cell.toDouble(), 'g', 5);
                    matrixA[j][i]->setText(cell);
                }
            }
        taskFile.close();
    } else {
        QMessageBox fileNotfoundMsg;
        fileNotfoundMsg.setText("Сорян, файл не найден");
        fileNotfoundMsg.exec();
    }
}

void LinearSystemTab::reset() {
    int n = numberSlider->value();
    for (auto i = 0; i < n; i++) {
        matrixB[i]->setText("0");
        for (auto j = 0; j < n; j++) {
            matrixA[i][j]->setText("0");
        }
    }
}

void LinearSystemTab::setRandom() {
    int n = numberSlider->value();
    QString cell;
    for (auto i = 0; i < n; i++) {
        double x = randomDouble(-100, 100);
        cell = QString::number(x == 0 ? 42 : x, 'g', 4).replace(",", ".");
        matrixA[i][i]->setText(cell);
        cell = QString::number(x + randomDouble(-70, 70), 'g', 4).replace(",", ".");
        matrixB[i]->setText(cell);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double negBound = matrixA[i][i]->text().toDouble();
                negBound = negBound < 0 ? negBound : negBound * (-1);
                double x = randomDouble(negBound, negBound * (-1));
                cell = QLocale().toString(x / n, 'g', 4).replace(",", ".");
                matrixA[i][j]->setText(cell);
            }
        }
    }
}

double LinearSystemTab::randomDouble(double lower, double upper) {
    return (int) (upper - lower) * ((double) random() / (double) RAND_MAX) + lower;
}

void LinearSystemTab::setSlider() {
    numberSlider = new QSlider;
    numberSlider->setOrientation(Qt::Horizontal);
    numberSlider->setFixedWidth(200);
    numberSlider->setMaximum(20);
    numberSlider->setMinimum(1);
    numberSlider->setValue(20);
    numberSlider->setSingleStep(1);
    numberLabel = new QLabel;
    numberLabel->setText("20");
    connect(numberSlider, SIGNAL(valueChanged(int)), this, SLOT(changeNumber(int)));
}

void LinearSystemTab::setAMatrix(QGridLayout *aCells) {
    for (auto i = 0; i < 20; i++) {
        for (auto j = 0; j < 20; j++) {
            auto aCell = new QLineEdit();
            aCell->setText("0");
            aCell->setValidator(new QDoubleValidator);
            aCell->setMaximumSize(50, 15);
            aCell->setMaxLength(20);
            aCells->addWidget(aCell, i, j);
            matrixA[i][j] = aCell;
        }
    }
}

void LinearSystemTab::setBMatrix(QGridLayout *bCells) {
    bCells->setColumnStretch(2, 1);
    for (auto i = 0; i < 20; i++) {
        auto bCell = new QLineEdit();
        bCell->setText("0");
        bCell->setValidator(new QDoubleValidator);
        bCell->setMaximumSize(50, 15);
        bCell->setMaxLength(20);
        bCells->addWidget(new QLabel(tr(" = ")), i, 0);
        bCells->addWidget(bCell, i, 1);
        matrixB[i] = bCell;
    }
}

void LinearSystemTab::changeNumber(int value) {
    numberLabel->setText(QString::fromStdString(std::to_string(value)));
    for (auto i = value; i < 20; i++) {
        //matrixB[i]->setText("0");
        matrixB[i]->setEnabled(false);
        for (auto j = 0; j < 20; j++) {
            //matrixA[i][j]->setText("0");
            matrixA[i][j]->setEnabled(false);
            //matrixA[j][i]->setText("0");
            matrixA[j][i]->setEnabled(false);
        }
    }
    for (auto i = 0; i < value; i++) {
        matrixB[i]->setEnabled(true);
        for (auto j = 0; j < value; j++) {
            matrixA[i][j]->setEnabled(true);
        }
    }
}

/*
 * выбор файла
 * удаление лишних
 * точна/запятая
 * nan - система не решается методом гаусса
 * */
