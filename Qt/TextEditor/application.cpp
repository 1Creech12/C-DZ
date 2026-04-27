#include "application.h"

Application::~Application()
{
    for (document* doc : docs) {
        delete doc;
    }
}

void Application::newDocument()
{
    document* doc = createDocument();
    docs.append(doc);
}

void Application::openDocument(const QString& path)
{
    document* doc = createDocument();
    doc->saveAs(path);
    docs.append(doc);
}

void Application::saveDocument(int index)
{
    if (index >= 0 && index < docs.size()) {
        docs[index]->save();
    }
}

void Application::closeDocument(int index)
{
    if (index >= 0 && index < docs.size()) {
        delete docs[index];
        docs.removeAt(index);
    }
}

document* Application::getDocument(int index) const
{
    return (index >= 0 && index < docs.size()) ? docs[index] : nullptr;
}