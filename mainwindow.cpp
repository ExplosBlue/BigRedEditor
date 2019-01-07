#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "BigRedEditor", "Settings");

    ui->setupUi(this);
    setWindowTitle("BigRedEditor");

    editor = new MainEditorWidget();
    setCentralWidget(editor);

    ui->actionSave->setDisabled(true);
    ui->actionSaveAs->setDisabled(true);
    editor->setDisabled(true);

    QString iconPath = QCoreApplication::applicationDirPath() + "/data/icons/";

    ui->actionOpen->setIcon(QIcon(iconPath + "open.png"));
    ui->actionSave->setIcon(QIcon(iconPath + "save.png"));
    ui->actionSaveAs->setIcon(QIcon(iconPath + "saveAs.png"));
}

MainWindow::~MainWindow()
{
    delete editor;
    delete settings;
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString previousPath = settings->value("LastOpenPath").value<QString>();

    if (previousPath == "")
        previousPath = QCoreApplication::applicationDirPath();

    QString openPath = QFileDialog::getOpenFileName(this, "BigRedEditor - Open", previousPath, "NSMB2 Savefile (*.dat);;All Files (*.*)");

    if (openPath.isEmpty() || openPath.isNull())
        return;

    settings->setValue("LastOpenPath", openPath);

    QFile file(openPath);
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::information(this, "BigRedEditor", "Could not open " + openPath + "!", QMessageBox::Ok);
        return;
    }

    if (file.size() != 0x2838)
    {
        QMessageBox::information(this, "BigRedEditor", "Incorrect filesize!", QMessageBox::Ok);
        return;
    }

    saveFile = new BigRedSave();

    QDataStream inStream(&file);
    inStream.setByteOrder(QDataStream::LittleEndian);
    inStream.readRawData(reinterpret_cast<char*>(saveFile), sizeof(BigRedSave));
    file.close();

    if (saveFile->magic != 0x00000020)
    {
        QMessageBox::information(this, "BigRedEditor", "Invalid File!", QMessageBox::Ok);
        delete saveFile;
        return;
    }

    editor->loadFile(saveFile);
    ui->statusBar->showMessage("Opened Successfully", 4000);
    setWindowTitle("NSMB2SaveEdit - " + openPath);
    ui->actionSave->setDisabled(false);
    ui->actionSaveAs->setDisabled(false);
    editor->setDisabled(false);
}

void MainWindow::on_actionSave_triggered()
{
    QString currentFile = settings->value("LastOpenPath").value<QString>();

    QFile file(currentFile);
    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox::information(this, "BigRedEditor", "Could not save " + currentFile + "!", QMessageBox::Ok);
        return;
    }

    QDataStream outStream(&file);
    outStream.setByteOrder(QDataStream::LittleEndian);
    outStream.writeRawData(reinterpret_cast<char*>(saveFile), sizeof(BigRedSave));
    file.close();

    ui->statusBar->showMessage("Saved Successfully", 4000);
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString previousPath = settings->value("LastSavePath").value<QString>();

    if (previousPath == "")
        previousPath = QCoreApplication::applicationDirPath();

    QString savePath = QFileDialog::getSaveFileName(this, "BigRedEditor - Save", previousPath, "NSMB2 Savefile (*.dat);;All Files (*.*)");

    if (savePath.isEmpty() || savePath.isNull())
        return;

    settings->setValue("LastSavePath", savePath);

    QFile file(savePath);
    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox::information(this, "BigRedEditor", "Could not save " + savePath + "!", QMessageBox::Ok);
        return;
    }

    QDataStream outStream(&file);
    outStream.setByteOrder(QDataStream::LittleEndian);
    outStream.writeRawData(reinterpret_cast<char*>(saveFile), sizeof(BigRedSave));
    file.close();

    ui->statusBar->showMessage("Saved Successfully", 4000);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "BigRedEditor - About", "BigRedEditor v1.0 by Explos\n"
                                                                "This software is freeware", QMessageBox::Ok);

}
