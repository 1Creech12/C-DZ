#include "graphicdocument.h"
#include <QFile>
#include <QDebug>

GraphicDocument::~GraphicDocument()
{
    delete format;
}

void GraphicDocument::setFormat(ImageFormat* fmt)
{
    delete format;
    format = fmt;
}

void GraphicDocument::doRead(const QString& path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        imageData = file.readAll();
        filePath = path;
        isModified = false;
        qDebug() << "Изображение азгружено из" << path;
    }
}

void GraphicDocument::doWrite(const QString& path)
{
    if (!format) {
        format = new PngFormat();
    }

    QByteArray saved = format->saveImage(imageData);
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(saved);
        qDebug() << "Изображение сохранено в" << path;
    }
}