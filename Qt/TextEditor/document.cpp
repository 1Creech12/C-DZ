#include "document.h"
#include <QFile>
#include <QDebug>


void document::open(const QString& path)
{
    doRead(path);
    qDebug() << "Документ открыт" << path;
}

void document::save()
{
    if (filePath.isEmpty()) {
        qDebug() << "Нет пути к файлу";
        return;
    }
    doWrite(filePath);
    isModified = false;
    qDebug() << "Документ сохранен в" << filePath;
}

void document::saveAs(const QString& path)
{
    filePath = path;
    doWrite(path);
    isModified = false;
    qDebug() << "Документ сохранен в" << path;
}