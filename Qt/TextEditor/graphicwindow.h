#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "application.h"
#include "graphicdocument.h"
#include "imageformat.h"

namespace Ui {
class GraphicWindow;
}

class GraphicApplication : public Application
{
    Q_OBJECT

protected:
    document* createDocument() override { return new GraphicDocument(); }
};

class GraphicWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::GraphicWindow* ui;
    GraphicApplication app;
    QComboBox* formatCombo;

    PngFormat png;
    JpegFormat jpeg;
    BmpFormat bmp;

    int currentIndex = -1;

public:
    explicit GraphicWindow(QWidget *parent = nullptr);
    ~GraphicWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_formatCombo_currentIndexChanged(int idx);
    void on_docList_currentRowChanged(int index);
};

#endif