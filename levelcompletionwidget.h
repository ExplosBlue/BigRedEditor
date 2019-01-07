#ifndef LEVELCOMPLETIONWIDGET_H
#define LEVELCOMPLETIONWIDGET_H

#include <QWidget>
#include <QCheckBox>

class LevelCompletionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LevelCompletionWidget(QWidget *parent = nullptr);
    void loadLevel(quint8 level);

signals:
    void valueChanged(quint8 level);

public slots:
    void normalExitToggled(bool toggle);
    void secretExitToggled(bool toggle);
    void assistUsedToggled(bool toggle);
    void unknownFlagToggled(bool toggle);


private:
    quint8 level;

    QCheckBox* normalExit;
    QCheckBox* secretExit;

    QCheckBox* assistUsed;

    QCheckBox* unknownFlag;

    void blockAllSignals(bool block);
};

#endif // LEVELCOMPLETIONWIDGET_H
