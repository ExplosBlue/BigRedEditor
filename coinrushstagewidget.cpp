#include "coinrushstagewidget.h"

#include <QHBoxLayout>
#include <QLabel>

CoinRushStageWidget::CoinRushStageWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout();

    // World
    worldSpinbox = new QSpinBox(this);
    worldSpinbox->setRange(1, 256);
    connect(worldSpinbox, SIGNAL(valueChanged(int)), this, SLOT(worldChanged(int)));
    mainLayout->addWidget(worldSpinbox);

    mainLayout->addWidget(new QLabel("  -"), Qt::AlignRight);

    // Level
    levelSpinbox = new QSpinBox(this);
    levelSpinbox->setRange(1, 256);
    connect(levelSpinbox, SIGNAL(valueChanged(int)), this, SLOT(levelChanged(int)));
    mainLayout->addWidget(levelSpinbox);

    this->setLayout(mainLayout);

}

void CoinRushStageWidget::loadStage(quint8 world, quint8 level)
{
    this->world = world;
    this->level = level;

    blockAllSignals(true);

    worldSpinbox->setValue(world + 1);
    levelSpinbox->setValue(level + 1);

    blockAllSignals(false);
}

void CoinRushStageWidget::blockAllSignals(bool block)
{
    worldSpinbox->blockSignals(block);
    levelSpinbox->blockSignals(block);
}

// SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void CoinRushStageWidget::worldChanged(int value)
{
    world = static_cast<quint8>(value - 1);
    emit stageChanged(world, level);
}

void CoinRushStageWidget::levelChanged(int value)
{
    level = static_cast<quint8>(value - 1);
    emit stageChanged(world, level);
}
