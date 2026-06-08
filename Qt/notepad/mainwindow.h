#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Меню "Файл"
    void on_action_New_triggered();
    void on_action_Open_triggered();
    void on_action_Save_triggered();
    void on_action_SaveAs_triggered();
    void on_action_Print_triggered();
    void on_action_Exit_triggered();

    // Меню "Правка"
    void on_action_Undo_triggered();
    void on_action_Redo_triggered();
    void on_action_Copy_triggered();
    void on_action_Cut_triggered();
    void on_action_Paste_triggered();
    void on_action_Delete_triggered();
    void on_action_Date_triggered();

    // Меню "Вид" — Шрифт
    void on_action_Font_triggered();

    // Меню "Вид" — Выравнивание
    void on_action_Left_triggered();
    void on_action_Center_triggered();
    void on_action_Right_triggered();

    // Меню "Найти"
    void on_action_Search_triggered();
    void on_action_Replace_triggered();
    void on_action_GoToLine_triggered();

    // Меню "Справка"
    void on_action_About_triggered();

private:
    Ui::MainWindow *ui;
    QString _copytext;
    QString _filename;
};
#endif // MAINWINDOW_H