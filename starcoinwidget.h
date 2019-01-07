#ifndef STARCOINWIDGET_H
#define STARCOINWIDGET_H

#include <QWidget>
#include <QCheckBox>

class StarCoinWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StarCoinWidget(QWidget *parent = nullptr);
    void loadFlag(quint8 flag);

signals:
    void valueChanged(quint8 value);

public slots:
    void coin1Toggled(bool toggle);
    void coin2Toggled(bool toggle);
    void coin3Toggled(bool toggle);


private:
    quint8 starCoinFlag;

    QCheckBox* coin1;
    QCheckBox* coin2;
    QCheckBox* coin3;

    void blockAllSignals(bool block);
};

#endif // STARCOINWIDGET_H
