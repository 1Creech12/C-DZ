#include "mainwindow.h"
#include "catalogwindow.h"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Интернет магазин");
    setFixedSize(400, 300);

    catalogButton = new QPushButton("Каталог товаров", this);
    catalogButton->setGeometry(100, 120, 200, 50);

    connect(catalogButton, &QPushButton::clicked, this, &MainWindow::openCatalog);
}

void MainWindow::openCatalog()
{
    CatalogWindow *catalog = new CatalogWindow(this);
    catalog->setAttribute(Qt::WA_DeleteOnClose);
    catalog->show();
}

MainWindow::~MainWindow() {}