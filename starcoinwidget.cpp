#include "starcoinwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

StarCoinWidget::StarCoinWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout();

    // StarCoin 1
    coin1 = new QCheckBox("Coin 1", this);
    connect(coin1, SIGNAL(toggled(bool)), this, SLOT(coin1Toggled(bool)));
    mainLayout->addWidget(coin1);

    // StarCoin 2
    coin2 = new QCheckBox("Coin 2", this);
    connect(coin2, SIGNAL(toggled(bool)), this, SLOT(coin2Toggled(bool)));
    mainLayout->addWidget(coin2);

    // StarCoin 3
    coin3 = new QCheckBox("Coin 3", this);
    connect(coin3, SIGNAL(toggled(bool)), this, SLOT(coin3Toggled(bool)));
    mainLayout->addWidget(coin3);

    this->setLayout(mainLayout);
}

void StarCoinWidget::loadFlag(quint8 flag)
{
    this->starCoinFlag = flag;

    blockAllSignals(true);

    coin1->setChecked((starCoinFlag >> 0x00) & 1);
    coin2->setChecked((starCoinFlag >> 0x01) & 1);
    coin3->setChecked((starCoinFlag >> 0x02) & 1);

    blockAllSignals(false);
}

void StarCoinWidget::blockAllSignals(bool block)
{
    coin1->blockSignals(block);
    coin2->blockSignals(block);
    coin3->blockSignals(block);
}

// SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void StarCoinWidget::coin1Toggled(bool toggle)
{
    starCoinFlag ^= (-static_cast<int>(toggle) ^ starCoinFlag) & (1 << 0x00);
    emit valueChanged(starCoinFlag);
}

void StarCoinWidget::coin2Toggled(bool toggle)
{
    starCoinFlag ^= (-static_cast<int>(toggle) ^ starCoinFlag) & (1 << 0x01);
    emit valueChanged(starCoinFlag);
}

void StarCoinWidget::coin3Toggled(bool toggle)
{
    starCoinFlag ^= (-static_cast<int>(toggle) ^ starCoinFlag) & (1 << 0x02);
    emit valueChanged(starCoinFlag);
}
