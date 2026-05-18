#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Заголовок таблицы
    ui->resultTable->setColumnCount(3);
    ui->resultTable->setHorizontalHeaderLabels({"Имя", "Статус", "Описание"});
    ui->resultTable->horizontalHeader()->setStretchLastSection(true);

    // Состояние кнопок
    ui->analyzeButton->setEnabled(false);

    classGirls["5А"] = QSet<QString>() << "Анна" << "Мария" << "Елена" << "Ольга";
    classGirls["5Б"] = QSet<QString>() << "Мария" << "Ольга" << "Татьяна" << "Наталья";
    classGirls["5В"] = QSet<QString>() << "Мария" << "Ольга" << "Анна" << "Светлана";

    updateClassList();
    ui->analyzeButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addClassButton_clicked()
{
    bool ok;
    QString className = QInputDialog::getText(this, "Добавить класс", "Введите название класса (например, 5А):", QLineEdit::Normal, "", &ok);

    if (ok && !className.isEmpty()) {
        if (classGirls.contains(className)) {
            QMessageBox::warning(this, "Ошибка", "Такой класс уже существует!");
            return;
        }

        QString girlsInput = QInputDialog::getText(this, "Добавить девочек", "Введите имена девочек через запятую (например: Анна,Мария,Елена):", QLineEdit::Normal, "", &ok);

        if (ok && !girlsInput.isEmpty()) {
            QSet<QString> girls;
            QStringList namesList = girlsInput.split(",");

            for (const QString &name : namesList) {
                QString trimmedName = name.trimmed();
                if (!trimmedName.isEmpty()) {
                    girls.insert(trimmedName);
                    allGirlNames.insert(trimmedName);
                }
            }

            classGirls[className] = girls;
            updateClassList();
            ui->analyzeButton->setEnabled(true);
        }
    }
}

void MainWindow::on_analyzeButton_clicked()
{
    analyzeNames();
}

void MainWindow::on_clearButton_clicked()
{
    clearAll();
}

void MainWindow::updateClassList()
{
    ui->classListText->clear();
    QString text;

    for (auto it = classGirls.begin(); it != classGirls.end(); ++it) {
        text += "Класс " + it.key() + ":\n";
        QStringList namesList = it.value().values();
        namesList.sort();
        text += namesList.join(", ") + "\n\n";
    }

    ui->classListText->setText(text);
}

void MainWindow::analyzeNames()
{
    if (classGirls.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет данных для анализа!");
        return;
    }

    // Все классы
    QList<QString> classes = classGirls.keys();
    int totalClasses = classes.size();

    // Все имена из всех классов
    QSet<QString> allNames;
    for (const QSet<QString> &girls : classGirls.values()) {
        allNames.unite(girls);
    }

    // Категории
    QSet<QString> inAllClasses;     // Имена во всех классах
    QSet<QString> inSomeClasses;    // Имена только в некоторых классах

    // Анализ
    for (const QString &name : allNames) {
        int count = 0;

        for (const QSet<QString> &girls : classGirls.values()) {
            if (girls.contains(name)) {
                count++;
            }
        }

        if (count == totalClasses) {
            inAllClasses.insert(name);
        } else {
            inSomeClasses.insert(name);
        }
    }

    ui->resultTable->setRowCount(0);
    int row = 0;

    // Имена которые есть во всех классах
    QStringList sortedAll = inAllClasses.values();
    sortedAll.sort();
    for (const QString &name : sortedAll) {
        ui->resultTable->insertRow(row);
        ui->resultTable->setItem(row, 0, new QTableWidgetItem(name));
        ui->resultTable->setItem(row, 1, new QTableWidgetItem("Во всех классах"));
        ui->resultTable->setItem(row, 2, new QTableWidgetItem("Имя встречается во всех " + QString::number(totalClasses) + " классах"));
        row++;
    }

    // Имена которые есть только в некоторых классах
    QStringList sortedSome = inSomeClasses.values();
    sortedSome.sort();
    for (const QString &name : sortedSome) {
        ui->resultTable->insertRow(row);
        ui->resultTable->setItem(row, 0, new QTableWidgetItem(name));
        ui->resultTable->setItem(row, 1, new QTableWidgetItem("В некоторых классах"));
        ui->resultTable->setItem(row, 2, new QTableWidgetItem("Имя встречается не во всех классах"));
        row++;
    }

    ui->resultTable->resizeColumnsToContents();

    QString stats = QString("Всего классов: %1\n"
                            "Уникальных имен: %2\n"
                            "Во всех классах: %3\n"
                            "Только в некоторых: %4\n")
                        .arg(totalClasses)
                        .arg(allNames.size())
                        .arg(inAllClasses.size())
                        .arg(inSomeClasses.size());

    ui->statsLabel->setText(stats);
}

void MainWindow::clearAll()
{
    classGirls.clear();
    allGirlNames.clear();
    ui->classListText->clear();
    ui->resultTable->setRowCount(0);
    ui->statsLabel->clear();
    ui->analyzeButton->setEnabled(false);

    QMessageBox::information(this, "Очистка", "Все данные очищены");
}