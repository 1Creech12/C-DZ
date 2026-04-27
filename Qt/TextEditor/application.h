#ifndef APPLICATION_H
#define APPLICATION_H

#include <QList>
#include <QObject>
#include "document.h"

class Application : public QObject
{
    Q_OBJECT

protected:
    QList<document*> docs;

public:
    virtual ~Application();

    void newDocument();
    void openDocument(const QString& path);
    void saveDocument(int index);
    void closeDocument(int index);

    document* getDocument(int index) const;
    int documentCount() const { return docs.size(); }

protected:
    virtual document* createDocument() = 0;
};

#endif