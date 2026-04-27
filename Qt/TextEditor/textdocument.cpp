#include "textdocument.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

void TextDocument::doRead(const QString& path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        content = in.readAll();
        filePath = path;
        isModified = false;
        qDebug() << "Текст загружен из" << path;
    }
}

void TextDocument::doWrite(const QString& path)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << content;
        qDebug() << "Текст сохранен в" << path;
    }
}