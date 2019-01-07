#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bigredsave.h"
#include "maineditorwidget.h"

#include <QMainWindow>
#include <QSettings>
#include <QFile>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow* ui;
    QSettings* settings;

    MainEditorWidget* editor;

    BigRedSave* saveFile;
};

#endif // MAINWINDOW_H
