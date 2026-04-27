#ifndef TEXTDOCUMENT_H
#define TEXTDOCUMENT_H

#include "document.h"

class TextDocument : public document
{
private:
    QString content;

protected:
    void doRead(const QString& path) override;
    void doWrite(const QString& path) override;

public:
    void setContent(const QString& text) { content = text; isModified = true; }
    QString getContent() const { return content; }
    QString getTypeName() const override { return "Текстовый документ"; }
};

#endif