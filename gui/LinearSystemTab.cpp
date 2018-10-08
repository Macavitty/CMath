#include <QTabWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QFile>
#include <QtWidgets/QMessageBox>
#include <QtCore/QDir>
#include <QFileDialog>
#include <QTextStream>
#include "LinearSystemTab.h"

LinearSystemTab::LinearSystemTab(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout;
// TODO make consts for number
    // MATRIX
    gridGroupBox = new QGroupBox(tr(""));
    auto *matrixLayout = new QGridLayout;
    answerField = new QTextEdit();
    answerField->setMinimumWidth(400);
    clearAnswerField();
    //task
    doubleValidator = new QDoubleValidator;
    doubleValidator->setNotation(QDoubleValidator::ScientificNotation);
    cellsLayout = new QGridLayout;
    setAMatrix(cellsLayout);

    matrixLayout->addWidget(answerField, 0, 2);
    matrixLayout->addLayout(cellsLayout, 0, 0);
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
        B[i] = matrix[i][n + 1]->text().replace(",", ".").toDouble();
        for (auto j = 0; j < n; j++) {
            A[i][j] = matrix[i][j]->text().replace(",", ".").toDouble();
        }
    }
    clearAnswerField();
    if (compute(A, B, n, e)) {
        auto *X = getAnswer();
        auto *Precisions = getPrecisions();
        answerField->append("Число итераций : " +  QString::number(getIterationsNumber()) + "\n");
        char endLineChar;
        for (auto i = 0; i < n; i++) {
            if (i == n-1) endLineChar = '.';
            else endLineChar = ';';
            int prec = e;
            answerField->append("x" + QString::number(i+1) + " = " + QString::number(X[i], 'g', 7) +
            ";  погрешность: " + QString::number(Precisions[i], 'g', 2) + endLineChar);

        }
    }
    else answerField->append("Данная матрица не обладает свойством диагонального преобладания");
}

void LinearSystemTab::clearAnswerField(){
    answerField->setPlainText(tr("--- ОТВЕТ --- \n\n"));
    answerField->setAlignment(Qt::AlignCenter);
}

void LinearSystemTab::takeFromFile() {
    int n = numberSlider->value();
    QString file = QFileDialog::getOpenFileName(this, "ВЫБЕРИТЕ ФАЙЛ", "");
    if (file != nullptr) {
        QFile
                taskFile(file);
        if (taskFile.exists()) {
            try {
                taskFile.open(QIODevice::ReadOnly);
                clearAnswerField();
                // clear matrix
                for (int i = 0; i < n; i++) {
                    matrix[i][n + 1]->setText("0");
                    for (int j = 0; j < n; j++) {
                        matrix[j][i]->setText("0");
                    }
                }
                int j = -1;
                QString
                        cell;
                        foreach(QString
                                        s,
                                QString(taskFile.readAll()).split(QRegExp("[\r\n]"), QString::SkipEmptyParts)) {
                        j++;
                        if (j == n) break;
                        cell = s.section(" ", n, n).replace(",", ".");
                        cell = cell == "" ? "0" : QString::number(cell.toDouble(), 'g', 5);
                        matrix[j][n + 1]->setText(cell);
                        for (int i = 0; i < n; i++) {
                            cell = s.section(" ", i, i).replace(",", ".");
                            cell = cell == "" ? "0" : QString::number(cell.toDouble(), 'g', 5);
                            matrix[j][i]->setText(cell);
                        }
                    }
                taskFile.close();
            } catch (QFile::FileError &e) {
                QMessageBox
                        readExcMsg;
                readExcMsg.setText("Ошибка во время чтения файла \n ");
                readExcMsg.exec();
            }
        } else {
            QMessageBox
                    fileNotfoundMsg;
            fileNotfoundMsg.setText("Сорян, файл не найден");
            fileNotfoundMsg.exec();
        }
    }
}

void LinearSystemTab::reset() {
    clearAnswerField();
    int n = numberSlider->value();
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n + 2; j++) {
            if (j != n) matrix[i][j]->setText("0");
        }
    }
}

void LinearSystemTab::setRandom() {
    clearAnswerField();
    int n = numberSlider->value();
    QString cell;
    for (auto i = 0; i < n; i++) {
        double x = randomDouble(-100, 100);
        cell = QString::number(x == 0 ? 42 : x, 'g', 4).replace(",", ".");
        matrix[i][i]->setText(cell);
        cell = QString::number(x + randomDouble(-70, 70), 'g', 4).replace(",", ".");
        matrix[i][n + 1]->setText(cell);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double negBound = matrix[i][i]->text().toDouble();
                negBound = negBound < 0 ? negBound : negBound * (-1);
                double x = randomDouble(negBound, negBound * (-1));
                cell = QLocale().toString(x / n, 'g', 4).replace(",", ".");
                matrix[i][j]->setText(cell);
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
    numberSlider->setTickInterval(10);
    numberLabel = new QLabel;
    numberLabel->setText("20");
    connect(numberSlider, SIGNAL(valueChanged(int)), this, SLOT(changeNumber(int)));
}

void LinearSystemTab::setAMatrix(QGridLayout *aCells) {
    for (auto i = 0; i < MAX_N; i++) {
        for (auto j = 0; j < MAX_N; j++) {
            matrix[i][j] = createCell("0");
            aCells->addWidget(matrix[i][j], i, j);
        }
    }
    // set = and b
    for (int i = 0; i < MAX_N; i++) {
        matrix[i][equalityColomn] = createCell("=");
        matrix[i][matrixBColomn] = createCell("0");
        aCells->addWidget(matrix[i][equalityColomn], i, equalityColomn);
        aCells->addWidget(matrix[i][matrixBColomn], i, matrixBColomn);
    }
}

QLineEdit *LinearSystemTab::createCell(QString text) {
    cellsLayout->setColumnStretch(MAX_N, 1);
    auto *aCell = new QLineEdit();
    aCell->setText(text);
    aCell->setValidator(doubleValidator);
    aCell->setMaxLength(20);
    aCell->setMaximumSize(10, 15);
    aCell->setFrame(false);
    aCell->setEnabled(false);
    aCell->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); color: black;}");
    if (text != "=") {
        aCell->setFrame(true);
        aCell->setEnabled(true);
        aCell->setStyleSheet("* { background-color: white; color: black;}");
        aCell->setMaximumSize(50, 15);
    }

    return aCell;
}

void LinearSystemTab::changeNumber(int newN) {
    numberLabel->setText(QString::fromStdString(std::to_string(newN)));
    numberSlider->setEnabled(false);
    clearAnswerField();
    if (newN > currN) {
        int step = newN - currN;
        // move b and "="
        for (int i = 0; i < newN; i++) {
            matrix[i][matrixBColomn + step]->setFrame(true);
            matrix[i][matrixBColomn + step]->setEnabled(true);
            matrix[i][matrixBColomn + step]->setStyleSheet("* { background-color: white; color: black;}");
            matrix[i][matrixBColomn + step]->setMaximumSize(50, 15);
            if (i >= currN) matrix[i][matrixBColomn + step]->setText("0");
            else matrix[i][matrixBColomn + step]->setText(matrix[i][matrixBColomn]->text());

            matrix[i][equalityColomn + step]->setText("=");
            matrix[i][equalityColomn + step]->setMaximumSize(10, 15);
            matrix[i][equalityColomn + step]->setFrame(false);
            matrix[i][equalityColomn + step]->setEnabled(false);
            matrix[i][equalityColomn + step]->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); color: black;}");
        }
        // set new cells
        for (int i = 0; i < newN; i++) {
            for (int j = currN; j < newN; j++) {
                matrix[j][i]->setFrame(true);
                matrix[j][i]->setEnabled(true);
                matrix[j][i]->setStyleSheet("* { background-color: white; color: black;}");
                matrix[j][i]->setMaximumSize(50, 15);
                matrix[j][i]->setText("0");

                matrix[i][j]->setFrame(true);
                matrix[i][j]->setEnabled(true);
                matrix[i][j]->setStyleSheet("* { background-color: white; color: black;}");
                matrix[i][j]->setMaximumSize(50, 15);
                matrix[i][j]->setText("0");
            }
        }
        equalityColomn += step;
        matrixBColomn += step;

    } else if (newN < currN) {
        int step = currN - newN;
        // set "=" and b to new place
        for (int i = 0; i < newN; i++) {
            matrix[i][matrixBColomn - step]->setFrame(true);
            matrix[i][matrixBColomn - step]->setEnabled(true);
            matrix[i][matrixBColomn - step]->setStyleSheet("* { background-color: white; color: black;}");
            matrix[i][matrixBColomn - step]->setMaximumSize(50, 15);
            matrix[i][matrixBColomn - step]->setText(matrix[i][matrixBColomn]->text());

            matrix[i][equalityColomn - step]->setText("=");
            matrix[i][equalityColomn - step]->setMaximumSize(10, 15);
            matrix[i][equalityColomn - step]->setFrame(false);
            matrix[i][equalityColomn - step]->setEnabled(false);
            matrix[i][equalityColomn - step]->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); color: black;}");
        }

        // set size 0 to others
        for (int i = matrixBColomn; i < MAX_N + 2; i++) {
            for (int j = 0; j < MAX_N; j++) {
                //matrix[j][i] = createCell("0");
                matrix[j][i]->setMaximumSize(0, 0);
            }
        }
        for (int i = newN; i < MAX_N; i++) {
            for (int j = 0; j < MAX_N; j++) {
                //matrix[j][i] = createCell("0");
                matrix[i][j]->setMaximumSize(0, 0);
            }
        }
        matrix[19][20]->setMaximumSize(0, 0); // ОСТОРОЖНО, костыль! не трогать
        equalityColomn = newN;
        matrixBColomn = newN + 1;
    }
    currN = newN;
    numberSlider->setEnabled(true);

}

/*
 * точна/запятая
 * nan - система не решается методом гаусса
 * */


