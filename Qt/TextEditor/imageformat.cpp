#include "imageformat.h"
#include <QImage>
#include <QBuffer>
#include <QDebug>

QByteArray PngFormat::saveImage(const QByteArray& data)
{
    QImage image;
    image.loadFromData(data);
    QByteArray result;
    QBuffer buffer(&result);
    image.save(&buffer, "PNG");
    qDebug() << "Сохранен в PNG";
    return result;
}

QByteArray JpegFormat::saveImage(const QByteArray& data)
{
    QImage image;
    image.loadFromData(data);
    QByteArray result;
    QBuffer buffer(&result);
    image.save(&buffer, "JPEG");
    qDebug() << "Сохранен в JPEG";
    return result;
}

QByteArray BmpFormat::saveImage(const QByteArray& data)
{
    QImage image;
    image.loadFromData(data);
    QByteArray result;
    QBuffer buffer(&result);
    image.save(&buffer, "BMP");
    qDebug() << "Сохранен в BMP";
    return result;
}