#include "worldeditorwidget.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>

WorldEditorWidget::WorldEditorWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout* mainLayout = new QGridLayout();

    // World Selector
    mainLayout->addWidget(new QLabel("Editing World:"), 0, 0, 1, 1, Qt::AlignRight);
    worldSelector = new QComboBox(this);
    worldSelector->addItem("World 1");
    worldSelector->addItem("World 2");
    worldSelector->addItem("World 3");
    worldSelector->addItem("World 4");
    worldSelector->addItem("World 5");
    worldSelector->addItem("World 6");
    worldSelector->addItem("World Mushroom");
    worldSelector->addItem("World Flower");
    worldSelector->addItem("World Star");
    connect(worldSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(worldChanged(int)));
    mainLayout->addWidget(worldSelector, 0, 1, 1, 3);

    // Levels
    levels = new QTableWidget(31, 3);
    QList<QString> tableHeaders = { "Completion", "Star Coins", "Coin Highscore" };
    levels->setHorizontalHeaderLabels(QStringList(tableHeaders));
    levels->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    levels->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    levels->verticalHeader()->setDefaultSectionSize(60);
    levels->setFocusPolicy(Qt::NoFocus);
    levels->setSelectionMode(QAbstractItemView::NoSelection);
    levels->setEditTriggers(QAbstractItemView::NoEditTriggers);
    levels->setAlternatingRowColors(true);

    setLevelNames();
    mainLayout->addWidget(levels, 1, 0, 1, 4);

    for (int i = 0; i < 31; i++)
    {
        // Level Completion
        LevelCompletionWidget* levelCompletion = new LevelCompletionWidget();
        levelCompletion->setProperty("Row", i);
        connect(levelCompletion, SIGNAL(valueChanged(quint8)), this, SLOT(levelCompletionFlagChanged(quint8)));
        levels->setCellWidget(i, 0, levelCompletion);


        // Star Coins
        StarCoinWidget* starCoinFlags = new StarCoinWidget();
        starCoinFlags->setProperty("Row", i);
        connect(starCoinFlags, SIGNAL(valueChanged(quint8)), this, SLOT(starCoinFlagsChanged(quint8)));
        levels->setCellWidget(i, 1, starCoinFlags);


        // Coin Scores
        CoinScoreWidget* coinScore = new CoinScoreWidget();
        coinScore->setProperty("Row", i);
        connect(coinScore, SIGNAL(valueChanged(quint16)), this, SLOT(coinScoreChanged(quint16)));
        levels->setCellWidget(i, 2, coinScore);
    }

    // Rainbow Level
    mainLayout->addWidget(new QLabel("Rainbow Level:"), 2, 2, 1, 1, Qt::AlignRight);
    rainbowLevel = new QComboBox(this);
    rainbowLevel->addItem("Rainbow 1");
    rainbowLevel->addItem("Rainbow 2");
    rainbowLevel->addItem("Rainbow 3");
    rainbowLevel->addItem("Rainbow 4");
    rainbowLevel->addItem("Rainbow 5");
    rainbowLevel->addItem("Rainbow 6");
    rainbowLevel->addItem("Rainbow Mushroom");
    rainbowLevel->addItem("Rainbow Flower");
    rainbowLevel->addItem("Rainbow Star");
    rainbowLevel->addItem("None");
    connect(rainbowLevel, SIGNAL(currentIndexChanged(int)), this, SLOT(rainbowLevelChanged(int)));
    mainLayout->addWidget(rainbowLevel, 2, 3, 1, 1);

    // Star Coin Gates
    QGroupBox* scGroupBox = new QGroupBox("StarCoin Gates");
    QHBoxLayout* scGatesLayout = new QHBoxLayout();

    starCoinGate1 = new QCheckBox("Gate 1 Open", this);
    connect(starCoinGate1, SIGNAL(toggled(bool)), this, SLOT(starCoinGate1Toggled(bool)));
    scGatesLayout->addWidget(starCoinGate1);

    starCoinGate2 = new QCheckBox("Gate 2 Open", this);
    connect(starCoinGate2, SIGNAL(toggled(bool)), this, SLOT(starCoinGate2Toggled(bool)));
    scGatesLayout->addWidget(starCoinGate2);

    starCoinGate3 = new QCheckBox("Gate 3 Open", this);
    connect(starCoinGate3, SIGNAL(toggled(bool)), this, SLOT(starCoinGate3Toggled(bool)));
    scGatesLayout->addWidget(starCoinGate3);

    scGroupBox->setLayout(scGatesLayout);

    mainLayout->addWidget(scGroupBox, 3, 0, 1, 4);

    this->setLayout(mainLayout);
}

void WorldEditorWidget::loadFile(Save *file)
{
    this->file = file;

    blockAllSignals(true);

    worldChanged(worldSelector->currentIndex());

    blockAllSignals(false);
}

void WorldEditorWidget::blockAllSignals(bool block)
{
    rainbowLevel->blockSignals(block);

    // Levels
    levels->blockSignals(block);

    // Star Coin Gates
    starCoinGate1->blockSignals(block);
    starCoinGate2->blockSignals(block);
    starCoinGate3->blockSignals(block);
}

void WorldEditorWidget::setLevelNames()
{
    QString world = worldSelector->currentText();
    QList<QString> tableHeaders =
    {
        world + " - 1", world + " - 2", world + " - 3", world + " - 4",
        world + " - 5", world + " - 6", world + " - 7", world + " - A",
        world + " - B", world + " - C", world + " - 11", world + " - Ghost House",
        world + " - 13", world + " - Tower", world + " - 15", world + " - Castle",
        world + " - 17", world + " - Toadhouse 1", world + " - Toadhouse 2", world + " - Toadhouse 3",
        world + " - Toadhouse 4", world + " - Toadhouse 5", world + " - Toadhouse 6", world + " - Cannon 1",
        world + " - Cannon 2", world + " - 26", world + " - 27", world + " - Pipe 1",
        world + " - Rainbow", world + " - Pipe 2", world + " - 31"
    };

    levels->setVerticalHeaderLabels(QStringList(tableHeaders));
}

quint8* WorldEditorWidget::getStarCoins(int worldNum)
{
    int startpos = worldNum * 31;

    static quint8 result[31];

    for (int i = 0; i < 31; i++)
    {
        if ((i + startpos) % 2 == 0)
            result[i] = file->starCoinFlags[(startpos + i)/2] & 0xF;
        else
            result[i] = file->starCoinFlags[(startpos + i)/2] >> 4;
    }
    return  result;
}

void WorldEditorWidget::setStarCoin(int worldNum, int levelNum, quint8 value)
{
    int index = (worldNum * 31) + levelNum;

        if (index % 2 == 0)
            file->starCoinFlags[index/2] = ((file->starCoinFlags[index/2] & 0xF0) | value);
        else
            file->starCoinFlags[index/2] = static_cast<quint8>(((file->starCoinFlags[index/2]) & 0x0F) | value << 4);
}

// SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void WorldEditorWidget::worldChanged(int index)
{
    currentWorld = index;

    rainbowLevel->setCurrentIndex(file->rainbowFlags[currentWorld]);

    // Levels
    setLevelNames();

    quint8* starCoins = getStarCoins(currentWorld);

    for (int i = 0; i < 31; i++)
    {
        // Level Completion
        static_cast<LevelCompletionWidget*>(levels->cellWidget(i, 0))->loadLevel(file->levelFlags[currentWorld][i]);

        // Star Coins
        static_cast<StarCoinWidget*>(levels->cellWidget(i, 1))->loadFlag(starCoins[i]);

        // Coin Scores
        static_cast<CoinScoreWidget*>(levels->cellWidget(i, 2))->loadScore(file->coinScores[currentWorld][i]);
    }

    // Star Coin Gates
    starCoinGate1->setChecked((file->starCoinGates[currentWorld] >> 0x00) & 1);
    starCoinGate2->setChecked((file->starCoinGates[currentWorld] >> 0x01) & 1);
    starCoinGate3->setChecked((file->starCoinGates[currentWorld] >> 0x02) & 1);
}

void WorldEditorWidget::rainbowLevelChanged(int index)
{
    file->rainbowFlags[currentWorld] = static_cast<quint8>(index);
}

// Coin Scores
void WorldEditorWidget::coinScoreChanged(quint16 value)
{
    CoinScoreWidget* coinScore = qobject_cast<CoinScoreWidget*>(sender());

    int row = coinScore->property("Row").toInt();
    file->coinScores[currentWorld][row] = value;
}

// Level Completion Flags
void WorldEditorWidget::levelCompletionFlagChanged(quint8 value)
{
    LevelCompletionWidget* levelWidget = qobject_cast<LevelCompletionWidget*>(sender());

    int row = levelWidget->property("Row").toInt();
    file->levelFlags[currentWorld][row] = value;
}

// Star Coin Flags
void WorldEditorWidget::starCoinFlagsChanged(quint8 value)
{
    StarCoinWidget* starCoinEditor = qobject_cast<StarCoinWidget*>(sender());

    int row = starCoinEditor->property("Row").toInt();
    setStarCoin(currentWorld, row, value);
}

// Star Coin Gates
void WorldEditorWidget::starCoinGate1Toggled(bool toggle)
{
    file->starCoinGates[currentWorld] ^= (-static_cast<int>(toggle) ^ file->starCoinGates[currentWorld]) & (1 << 0x00);
}

void WorldEditorWidget::starCoinGate2Toggled(bool toggle)
{
    file->starCoinGates[currentWorld] ^= (-static_cast<int>(toggle) ^ file->starCoinGates[currentWorld]) & (1 << 0x01);
}

void WorldEditorWidget::starCoinGate3Toggled(bool toggle)
{
    file->starCoinGates[currentWorld] ^= (-static_cast<int>(toggle) ^ file->starCoinGates[currentWorld]) & (1 << 0x02);
}


