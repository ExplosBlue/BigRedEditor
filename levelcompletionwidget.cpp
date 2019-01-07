#include "levelcompletionwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

LevelCompletionWidget::LevelCompletionWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout();

    QVBoxLayout* compFlagsLayout = new QVBoxLayout();

    // Completion Flags
    normalExit = new QCheckBox("Normal Exit", this);
    connect(normalExit, SIGNAL(toggled(bool)), this, SLOT(normalExitToggled(bool)));
    compFlagsLayout->addWidget(normalExit);

    secretExit = new QCheckBox("Secret Exit", this);
    connect(secretExit, SIGNAL(toggled(bool)), this, SLOT(secretExitToggled(bool)));
    compFlagsLayout->addWidget(secretExit);

    mainLayout->addLayout(compFlagsLayout);

    QVBoxLayout* otherFlags = new QVBoxLayout();

    // Assist Flag
    assistUsed = new QCheckBox("Assist Used", this);
    connect(assistUsed, SIGNAL(toggled(bool)), this, SLOT(assistUsedToggled(bool)));
    otherFlags->addWidget(assistUsed);

    // Unknown Flag
    unknownFlag = new QCheckBox("Unknown Flag", this);
    connect(unknownFlag, SIGNAL(toggled(bool)), this, SLOT(unknownFlagToggled(bool)));
    otherFlags->addWidget(unknownFlag);

    mainLayout->addLayout(otherFlags);

    this->setLayout(mainLayout);
}

void LevelCompletionWidget::loadLevel(quint8 level)
{
    this->level = level;

    blockAllSignals(true);

    normalExit->setChecked((level >> 0x00) & 1);
    secretExit->setChecked((level >> 0x01) & 1);
    assistUsed->setChecked((level >> 0x02) & 1);
    unknownFlag->setChecked((level >> 0x04) & 1);

    blockAllSignals(false);
}

void LevelCompletionWidget::blockAllSignals(bool block)
{
    normalExit->blockSignals(block);
    secretExit->blockSignals(block);
    assistUsed->blockSignals(block);
    unknownFlag->blockSignals(block);
}

// SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LevelCompletionWidget::normalExitToggled(bool toggle)
{
    level ^= (-static_cast<int>(toggle) ^ level) & (1 << 0x00);
    emit valueChanged(level);
}

void LevelCompletionWidget::secretExitToggled(bool toggle)
{
    level ^= (-static_cast<int>(toggle) ^ level) & (1 << 0x01);
    emit valueChanged(level);
}

void LevelCompletionWidget::assistUsedToggled(bool toggle)
{
    level ^= (-static_cast<int>(toggle) ^ level) & (1 << 0x02);
    emit valueChanged(level);
}

void LevelCompletionWidget::unknownFlagToggled(bool toggle)
{
    level ^= (-static_cast<int>(toggle) ^ level) & (1 << 0x04);
    emit valueChanged(level);
}
