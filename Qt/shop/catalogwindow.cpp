#include "catalogwindow.h"
#include "orderwindow.h"
#include <QPixmap>

CatalogWindow::CatalogWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Каталог товаров");
    setFixedSize(500, 400);

    descriptionLabel = new QLabel(this);
    descriptionLabel->setText("Ноутбук Apple MacBook Air 13\"\n"
                              "M1, 8GB RAM, 256GB SSD\n"
                              "Серебристый");
    descriptionLabel->setGeometry(30, 30, 300, 80);
    descriptionLabel->setWordWrap(true);

    priceLabel = new QLabel(this);
    priceLabel->setText("Цена: 44 990 ₽");
    priceLabel->setGeometry(30, 120, 200, 30);

    QLabel *photoLabel = new QLabel(this);
    photoLabel->setGeometry(320, 30, 140, 140);
    photoLabel->setFrameStyle(QFrame::Box);
    photoLabel->setAlignment(Qt::AlignCenter);

    QPixmap pixmap(":/images/mac.jpg");

    if (!pixmap.isNull()) {
        QPixmap scaled = pixmap.scaled(140, 140,
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);
        photoLabel->setPixmap(scaled);
    } else {
        photoLabel->setText("Ошибка");
    }

    orderButton = new QPushButton("Заказать", this);
    orderButton->setGeometry(200, 300, 100, 40);

    connect(orderButton, &QPushButton::clicked, this, &CatalogWindow::orderProduct);
}

void CatalogWindow::orderProduct()
{
    OrderWindow *order = new OrderWindow(
        descriptionLabel->text(),
        priceLabel->text(),
        this
        );
    order->setAttribute(Qt::WA_DeleteOnClose);
    order->show();
}