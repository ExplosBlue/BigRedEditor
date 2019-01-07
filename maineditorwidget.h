#ifndef MAINEDITORWIDGET_H
#define MAINEDITORWIDGET_H

#include "bigredsave.h"
#include "fileeditorwidget.h"
#include "coinrushstagewidget.h"

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QTableWidget>


class MainEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainEditorWidget(QWidget* parent = nullptr);
    void loadFile(BigRedSave* saveFile);

signals:

public slots:
    // General
    void coinMilestonesChanged(int index);
    void lastFileSavedChanged(int index);
    void globalCoinCountChanged(int value);

    // Coin Rush
    void streetpassCountChanged(int value);
    void coinRushVictoriesChanged(int value);
    void newStreetpassFlagToggled(bool toggle);
    void coinRushHighscoreChanged(int value);
    void coinRushPackTypeChanged(int value);
    void coinRushStageChanged(quint8 world, quint8 level);
    void coinRushRacoonFlagToggled(bool toggle);

    // Global Level Completion
    void worldChanged(int world);
    void levelCompletionFlagChanged(quint8 value);

    // Settings
    void controlSchemeChanged(int index);
    void spotpassSettingToggled(bool toggle);
    void firstBootFlagToggled(bool toggle);
    void coinRushFirstLoadToggled(bool toggle);
    void showEshopButtonToggled(bool toggle);

private:
     class HorLine : public QFrame { public: HorLine() { setFrameStyle(QFrame::HLine | QFrame::Sunken); } };

    BigRedSave* saveFile;

    // General
    QComboBox* coinMilestones;
    QComboBox* lastFileSaved;
    QSpinBox* globalCoinCount;

    // Coin Rush
    QSpinBox* streetpassCount;
    QSpinBox* coinRushVictories;
    QCheckBox* newStreetpassFlag;

    QSpinBox* coinRushHighscore;
    QComboBox* coinRushPackType;
    QTableWidget* coinRushLevels;

    QCheckBox* coinRushRacoonFlag;

    // TODO: - Mii editing
    // TODO: - Challenger editing

    // Global Level Completion
    QComboBox* worldSelector;
    QTableWidget* globalLevels;

    // Settings
    QComboBox* controlScheme;
    QCheckBox* spotpassSetting;
    QCheckBox* firstBootFlag;
    QCheckBox* coinRushFirstLoad;
    QCheckBox* showEshopButton;

    // Streetpass

    // Files
    QTabWidget* filesTabWidget;
    FileContainerWidget* file1;
    FileContainerWidget* file2;
    FileContainerWidget* file3;

    void blockAllSignals(bool block);
    void setLevelNames();
};

#endif // MAINEDITORWIDGET_H
