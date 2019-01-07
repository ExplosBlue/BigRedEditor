#ifndef WORLDEDITORWIDGET_H
#define WORLDEDITORWIDGET_H

#include "bigredsave.h"
#include "levelcompletionwidget.h"
#include "starcoinwidget.h"
#include "coinscorewidget.h"

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>


class WorldEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorldEditorWidget(QWidget *parent = nullptr);
    void loadFile(Save* file);

signals:

public slots:
    void worldChanged(int index);
    void rainbowLevelChanged(int index);

    void levelCompletionFlagChanged(quint8 value);
    void starCoinFlagsChanged(quint8 value);
    void coinScoreChanged(quint16 value);

    void starCoinGate1Toggled(bool toggle);
    void starCoinGate2Toggled(bool toggle);
    void starCoinGate3Toggled(bool toggle);

private:
    class HorLine : public QFrame { public: HorLine() { setFrameStyle(QFrame::HLine | QFrame::Sunken); } };

    Save* file;

    QComboBox* worldSelector;

    QComboBox* rainbowLevel;

    // Levels
    QTableWidget* levels;

    // Star Coin Gates
    QCheckBox* starCoinGate1;
    QCheckBox* starCoinGate2;
    QCheckBox* starCoinGate3;

    int currentWorld;

    void blockAllSignals(bool block);

    void setLevelNames();
    quint8* getStarCoins(int worldNum);
    void setStarCoin(int worldNum, int levelNum, quint8 value);
};

#endif // WORLDEDITORWIDGET_H
