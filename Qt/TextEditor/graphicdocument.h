#ifndef GRAPHICDOCUMENT_H
#define GRAPHICDOCUMENT_H

#include "document.h"
#include "imageformat.h"
#include <QByteArray>

class GraphicDocument : public document
{
private:
    QByteArray imageData;
    ImageFormat* format = nullptr;

protected:
    void doRead(const QString& path) override;
    void doWrite(const QString& path) override;

public:
    ~GraphicDocument();

    void setFormat(ImageFormat* fmt);
    ImageFormat* getFormat() const { return format; }
    void setImageData(const QByteArray& data) { imageData = data; isModified = true; }
    QByteArray getImageData() const { return imageData; }
    QString getTypeName() const override { return "Графический документ"; }
};

#endif