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
    answerField->setMinimumWidth(400);
    //task
    doubleValidator = new QDoubleValidator;
    doubleValidator->setNotation(QDoubleValidator::ScientificNotation);
    aCells = new QGridLayout;
    bCells = new QGridLayout;
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
    currN = MAX_N;
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
    auto **A = new long double *[n], *B = new long double[n];
    for (int i = 0; i < n; i++) A[i] = new long double[n];
    for (auto i = 0; i < n; i++) {
        B[i] = matrixB[i]->text().replace(",", ".").toDouble();
        for (auto j = 0; j < n; j++) {
            A[i][j] = matrixA[i][j]->text().replace(",", ".").toDouble();
        }
    }
    compute(A, B, n, e);
}

void LinearSystemTab::takeFromFile() {
    int n = numberSlider->value();
    QFile
    taskFile("linear_sys_task.txt");
    if (taskFile.exists()) {
        taskFile.open(QIODevice::ReadOnly);
        int j = -1;
        QString
        cell;
        foreach(QString
        s, QString(taskFile.readAll()).split(QRegExp("[\r\n]"), QString::SkipEmptyParts)) {
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
        QMessageBox
        fileNotfoundMsg;
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
    QString
    cell;
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

void LinearSystemTab::setAMatrix(QGridLayout * aCells) {
    //aCells->setRowStretch(MAX_N, 1);
   // bCells->setColumnStretch(MAX_N, 1);
    for (auto i = 0; i < MAX_N; i++) {
        equalitySigns[i] = new QLabel(tr(" = "));
        aCells->addWidget(equalitySigns[i], i, MAX_N);
        for (auto j = 0; j < MAX_N; j++) {
            matrixA[i][j] = createCell("0");
            aCells->addWidget(matrixA[i][j], i, j);
        }
    }
}

void LinearSystemTab::setBMatrix(QGridLayout * bCells) {
    for (auto i = 0; i < MAX_N; i++) {
        matrixB[i] = createCell("0");
        bCells->addWidget(matrixB[i], i, 1);
    }
}

QLineEdit *LinearSystemTab::createCell(QString text) {
    auto *aCell = new QLineEdit();
    aCell->setText(text);
    aCell->setValidator(doubleValidator);
    aCell->setMaximumSize(50, 15);
    aCell->setMaxLength(20);
    return aCell;
}

void LinearSystemTab::changeNumber(int newN) {
    numberLabel->setText(QString::fromStdString(std::to_string(newN)));
    if (newN > currN) {
        for (auto i = currN; i < newN; i++) {
            matrixB[i]->setMaximumSize(50, 15);
            for (auto j = 0; j < newN; j++) {
                matrixA[i][j]->setMaximumSize(50, 15);
                matrixA[j][i]->setMaximumSize(50, 15);
            }
        }
    } else if (newN < currN) {
        for (auto i = newN; i < currN; i++) {
            //delete(matrixB[i]);
            matrixB[i]->setMaximumSize(0, 0);
            equalitySigns[i]->setMaximumSize(0, 0);
            //delete(equalitySigns[i]);
            for (auto j = 0; j < currN; j++) {
                matrixA[i][j]->setMaximumSize(0, 0);
                matrixA[j][i]->setMaximumSize(0, 0);
            }
        }
    }
    currN = newN;

}

/*
 * выбор файла
 * удаление лишних
 * точна/запятая
 * nan - система не решается методом гаусса
 * */
