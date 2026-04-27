#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>

class document
{
protected:
    QString filePath;
    bool isModified = false;

public:
    virtual ~document() = default;

    void open(const QString& path);
    void save();
    void saveAs(const QString& path);

    QString getFilePath() const { return filePath; }
    bool getIsModified() const { return isModified; }
    virtual QString getTypeName() const = 0;

protected:
    virtual void doRead(const QString& path) = 0;
    virtual void doWrite(const QString& path) = 0;
};

#endif