#ifndef COINSCOREWIDGET_H
#define COINSCOREWIDGET_H

#include <QWidget>
#include <QSpinBox>

class CoinScoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CoinScoreWidget(QWidget *parent = nullptr);
    void loadScore(quint16 score);

signals:
    void valueChanged(quint16 score);

public slots:
    void coinScoreChanged(int value);

private:
    quint16 score;

    QSpinBox* coinScore;
};

#endif // COINSCOREWIDGET_H
