#ifndef COINRUSHSTAGEWIDGET_H
#define COINRUSHSTAGEWIDGET_H

#include <QWidget>
#include <QSpinBox>

class CoinRushStageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CoinRushStageWidget(QWidget *parent = nullptr);
    void loadStage(quint8 world, quint8 level);

signals:
    void stageChanged(quint8 world, quint8 level);

public slots:
    void worldChanged(int value);
    void levelChanged(int value);

private:
    quint8 world;
    quint8 level;

    QSpinBox* worldSpinbox;
    QSpinBox* levelSpinbox;

    void blockAllSignals(bool block);
};

#endif // COINRUSHSTAGEWIDGET_H
