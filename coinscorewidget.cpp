#include "coinscorewidget.h"

#include <QHBoxLayout>

CoinScoreWidget::CoinScoreWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout();

    coinScore = new QSpinBox(this);
    coinScore->setRange(0, 9999);
    connect(coinScore, SIGNAL(valueChanged(int)), this, SLOT(coinScoreChanged(int)));
    mainLayout->addWidget(coinScore);

    this->setLayout(mainLayout);

}

void CoinScoreWidget::loadScore(quint16 score)
{
    this->score = score;

    coinScore->blockSignals(true);

    coinScore->setValue(score);

    coinScore->blockSignals(false);
}

// SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void CoinScoreWidget::coinScoreChanged(int value)
{
    score = static_cast<quint16>(value);
    emit valueChanged(score);
}
