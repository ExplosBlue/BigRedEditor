#ifndef FILEEDITORWIDGET_H
#define FILEEDITORWIDGET_H

#include "bigredsave.h"
#include "worldeditorwidget.h"

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

class FileEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileEditorWidget(QWidget* parent = nullptr);
    void loadFile(Save* file);

signals:

public slots:
    void scoreChanged(int value);
    void powerupChanged(int value);
    void livesChanged(int value);
    void inventoryChanged(int value);
    void coinCountChanged(int value);
    void starCoinCountChanged(int value);
    void worldChanged(int value);
    void mapPositionChanged(int value);
    void openingCutsceneFlagToggled(bool toggle);
    void goldBlockFlagToggled(bool toggle);

private:
    class HorLine : public QFrame { public: HorLine() { setFrameStyle(QFrame::HLine | QFrame::Sunken); } };

    Save* file;

    QSpinBox* score;
    QComboBox* powerup;
    QSpinBox* lives;
    QComboBox* inventory;
    QSpinBox* coinCount;
    QSpinBox* starCoinCount;
    QComboBox* world;
    QSpinBox* mapPosition;
    QCheckBox* openingCutsceneFlag;
    QCheckBox* goldBlockFlag;

    // TODO: Other Stuff
    WorldEditorWidget* worldEditor;

    void setPowerupIndex();
    void setInventoryIndex();

    void blockAllSignals(bool block);
};

class FileContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileContainerWidget(QWidget* parent = nullptr);
    void LoadFile(GameFile* file);

private:
    GameFile* file;

    FileEditorWidget* normal;
    FileEditorWidget* quick;
};

#endif // FILEEDITORWIDGET_H
