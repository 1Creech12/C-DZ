#include "graphicwindow.h"
#include "ui_graphicwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>

GraphicWindow::GraphicWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GraphicWindow)
{
    ui->setupUi(this);

    QLabel* labelFormat = new QLabel("Формат: ");

    formatCombo = new QComboBox();
    formatCombo->addItem("PNG");
    formatCombo->addItem("JPEG");
    formatCombo->addItem("BMP");
    formatCombo->setMinimumWidth(100);

    ui->toolBar->addWidget(labelFormat);
    ui->toolBar->addWidget(formatCombo);

    connect(formatCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &GraphicWindow::on_formatCombo_currentIndexChanged);

    ui->statusBar->showMessage("Готов к работе");
}

GraphicWindow::~GraphicWindow()
{
    delete ui;
}

void GraphicWindow::on_actionNew_triggered()
{
    app.newDocument();
    ui->docList->addItem("Новое изображение");
    ui->docList->setCurrentRow(app.documentCount() - 1);
    ui->statusBar->showMessage("Создано новое изображение");
}

void GraphicWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "Открыть изображение", "",
                                                "Изображения (*.png *.jpg *.jpeg *.bmp);;Все файлы (*)");
    if (path.isEmpty()) return;

    app.newDocument();
    GraphicDocument* doc = dynamic_cast<GraphicDocument*>(app.getDocument(app.documentCount() - 1));
    if (doc) {
        doc->open(path);
    }

    QFileInfo fi(path);
    ui->docList->addItem(fi.fileName());
    ui->docList->setCurrentRow(app.documentCount() - 1);
    ui->statusBar->showMessage(QString("Открыт файл: %1").arg(path));
}

void GraphicWindow::on_actionSave_triggered()
{
    if (currentIndex < 0) {
        ui->statusBar->showMessage("Нет открытого документа");
        return;
    }

    GraphicDocument* doc = dynamic_cast<GraphicDocument*>(app.getDocument(currentIndex));
    if (!doc) return;

    QString path = doc->getFilePath();
    if (path.isEmpty()) {
        ImageFormat* fmt = doc->getFormat();
        QString ext = fmt ? fmt->extension() : "png";
        path = QFileDialog::getSaveFileName(this, "Сохранить", "/Users/creech12/test", QString("Изображение (*.%1)").arg(ext));
        if (path.isEmpty()) return;
    }
    doc->saveAs(path);
    QFileInfo fi(path);
    ui->docList->item(currentIndex)->setText(fi.fileName());
    ui->statusBar->showMessage("Изображение сохранено");
}

void GraphicWindow::on_formatCombo_currentIndexChanged(int idx)
{
    if (currentIndex < 0) return;

    GraphicDocument* doc = dynamic_cast<GraphicDocument*>(app.getDocument(currentIndex));
    if (!doc) return;

    ImageFormat* fmt = nullptr;
    switch (idx) {
    case 0: fmt = new PngFormat(); break;
    case 1: fmt = new JpegFormat(); break;
    case 2: fmt = new BmpFormat(); break;
    }
    if (fmt) {
        doc->setFormat(fmt);
        ui->statusBar->showMessage(QString("Выбран формат: %1").arg(fmt->name()));
    }
}

void GraphicWindow::on_docList_currentRowChanged(int index)
{
    if (index < 0) return;

    currentIndex = index;
    GraphicDocument* doc = dynamic_cast<GraphicDocument*>(app.getDocument(index));
    if (!doc) return;

    QPixmap pix;
    bool loaded = pix.loadFromData(doc->getImageData());

    if (loaded && !pix.isNull()) {
        ui->imageLabel->setPixmap(pix.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        ui->imageLabel->setText("Не удалось загрузить изображение");
    }

    ImageFormat* fmt = doc->getFormat();
    if (fmt) {
        if (fmt->name() == "PNG") formatCombo->setCurrentIndex(0);
        else if (fmt->name() == "JPEG") formatCombo->setCurrentIndex(1);
        else if (fmt->name() == "BMP") formatCombo->setCurrentIndex(2);
    }
}