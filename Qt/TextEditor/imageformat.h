#ifndef IMAGEFORMAT_H
#define IMAGEFORMAT_H

#include <QByteArray>
#include <QString>

class ImageFormat
{
public:
    virtual ~ImageFormat() = default;
    virtual QByteArray saveImage(const QByteArray& data) = 0;
    virtual QString extension() const = 0;
    virtual QString name() const = 0;
};

class PngFormat : public ImageFormat
{
public:
    QByteArray saveImage(const QByteArray& data) override;
    QString extension() const override { return "png"; }
    QString name() const override { return "PNG"; }
};

class JpegFormat : public ImageFormat
{
public:
    QByteArray saveImage(const QByteArray& data) override;
    QString extension() const override { return "jpg"; }
    QString name() const override { return "JPEG"; }
};

class BmpFormat : public ImageFormat
{
public:
    QByteArray saveImage(const QByteArray& data) override;
    QString extension() const override { return "bmp"; }
    QString name() const override { return "BMP"; }
};

#endif