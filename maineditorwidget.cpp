#include "maineditorwidget.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>

MainEditorWidget::MainEditorWidget(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout();

    QGridLayout* leftLayout = new QGridLayout();

    // Global Coin Count
    leftLayout->addWidget(new QLabel("Coin Count:"), 0, 0, 1, 1, Qt::AlignRight);
    globalCoinCount = new QSpinBox(this);
    globalCoinCount->setRange(0, 9999999);
    connect(globalCoinCount, SIGNAL(valueChanged(int)), this, SLOT(globalCoinCountChanged(int)));
    leftLayout->addWidget(globalCoinCount, 0, 1, 1, 1);

    // Last File Saved
    leftLayout->addWidget(new QLabel("Last File Saved:"), 0, 2, 1, 1, Qt::AlignRight);
    lastFileSaved = new QComboBox(this);
    lastFileSaved->addItem("File 1");
    lastFileSaved->addItem("File 2");
    lastFileSaved->addItem("File 3");
    connect(lastFileSaved, SIGNAL(currentIndexChanged(int)), this, SLOT(lastFileSavedChanged(int)));
    leftLayout->addWidget(lastFileSaved, 0, 3, 1, 1);

    // Coin Milestones
    leftLayout->addWidget(new QLabel("Last Milestone:"), 1, 0, 1, 1, Qt::AlignRight);
    coinMilestones = new QComboBox(this);
    coinMilestones->addItem("None");
    coinMilestones->addItem("100,000 Coins");
    coinMilestones->addItem("200,000 Coins");
    coinMilestones->addItem("300,000 Coins");
    coinMilestones->addItem("400,000 Coins");
    coinMilestones->addItem("500,000 Coins");
    coinMilestones->addItem("600,000 Coins");
    coinMilestones->addItem("700,000 Coins");
    coinMilestones->addItem("800,000 Coins");
    coinMilestones->addItem("900,000 Coins");
    coinMilestones->addItem("1,000,000 Coins");
    coinMilestones->addItem("9,999,999 Coins");
    connect(coinMilestones, SIGNAL(currentIndexChanged(int)), this, SLOT(coinMilestonesChanged(int)));
    leftLayout->addWidget(coinMilestones, 1, 1, 1, 1);

    // Coin Rush
    QGroupBox* coinRushGroupBox = new QGroupBox("Coin Rush");
    QGridLayout* coinRushLayout = new QGridLayout();

    // Streetpass Count
    coinRushLayout->addWidget(new QLabel("Streetpass Count:"), 0, 0, 1, 1, Qt::AlignRight);
    streetpassCount = new QSpinBox(this);
    streetpassCount->setRange(0, 65535);
    connect(streetpassCount, SIGNAL(valueChanged(int)), this, SLOT(streetpassCountChanged(int)));
    coinRushLayout->addWidget(streetpassCount, 0, 1, 1, 1);

    // CoinRush Victories
    coinRushLayout->addWidget(new QLabel("Victory Count:"), 0, 2, 1, 1, Qt::AlignRight);
    coinRushVictories = new QSpinBox(this);
    coinRushVictories->setRange(0, 65535);
    connect(coinRushVictories, SIGNAL(valueChanged(int)), this, SLOT(coinRushVictoriesChanged(int)));
    coinRushLayout->addWidget(coinRushVictories, 0, 3, 1, 1);

    // New Streetpass Flag
    newStreetpassFlag = new QCheckBox("Show New Streetpass Notification", this);
    connect(newStreetpassFlag, SIGNAL(toggled(bool)), this, SLOT(newStreetpassFlagToggled(bool)));
    coinRushLayout->addWidget(newStreetpassFlag, 1, 3, 1, 1);

    QGroupBox* highscoreGroupBox = new QGroupBox("Highscore");
    QGridLayout* highscoreLayout = new QGridLayout();

    // Coin Rush Highscore
    highscoreLayout->addWidget(new QLabel("Highscore:"), 0, 0, 1, 1, Qt::AlignRight);
    coinRushHighscore = new QSpinBox(this);
    coinRushHighscore->setRange(0, 30000);
    connect(coinRushHighscore, SIGNAL(valueChanged(int)), this, SLOT(coinRushHighscoreChanged(int)));
    highscoreLayout->addWidget(coinRushHighscore, 0, 1, 1, 1);

    // Coin Rush Pack Type
    highscoreLayout->addWidget(new QLabel("Pack:"), 0, 2, 1, 1, Qt::AlignRight);
    coinRushPackType = new QComboBox(this);
    coinRushPackType->addItem("Mushroom");
    coinRushPackType->addItem("Flower");
    coinRushPackType->addItem("Star");
    coinRushPackType->addItem("Invalid");
    coinRushPackType->addItem("DLC");
    connect(coinRushPackType, SIGNAL(currentIndexChanged(int)), this, SLOT(coinRushPackTypeChanged(int)));
    highscoreLayout->addWidget(coinRushPackType, 0, 3, 1, 1);

    coinRushLevels = new QTableWidget(1, 3);
    QList<QString> tableHeaders = { "Stage 1", "Stage 2", "Stage 3" };
    coinRushLevels->setHorizontalHeaderLabels(QStringList(tableHeaders));
    coinRushLevels->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    coinRushLevels->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    coinRushLevels->verticalHeader()->setDefaultSectionSize(60);
    coinRushLevels->verticalHeader()->setHidden(true);
    coinRushLevels->setFocusPolicy(Qt::NoFocus);
    coinRushLevels->setSelectionMode(QAbstractItemView::NoSelection);
    coinRushLevels->setEditTriggers(QAbstractItemView::NoEditTriggers);
    coinRushLevels->setMaximumHeight(80);
    coinRushLevels->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    highscoreLayout->addWidget(coinRushLevels, 1, 0, 1, 4);

    for (int i = 0; i < 3; i++)
    {
        // Stage
        CoinRushStageWidget* coinRushStage = new CoinRushStageWidget();
        coinRushStage->setProperty("Stage", i);
        connect(coinRushStage, SIGNAL(stageChanged(quint8, quint8)), this, SLOT(coinRushStageChanged(quint8, quint8)));
        coinRushLevels->setCellWidget(0, i, coinRushStage);
    }

    coinRushRacoonFlag = new QCheckBox("White Raccon Mario Used", this);
    connect(coinRushRacoonFlag, SIGNAL(toggled(bool)), this, SLOT(coinRushRacoonFlagToggled(bool)));
    highscoreLayout->addWidget(coinRushRacoonFlag, 2, 3, 1, 1);

    highscoreGroupBox->setLayout(highscoreLayout);
    coinRushLayout->addWidget(highscoreGroupBox, 2, 0, 1, 4);

    coinRushGroupBox->setLayout(coinRushLayout);
    leftLayout->addWidget(coinRushGroupBox, 2, 0, 1, 4);

    // Global Level Completion
    QGroupBox* levelCompletion = new QGroupBox("Global Level Completion");
    QGridLayout* levelCompletionLayout = new QGridLayout();

    // World Selector
    levelCompletionLayout->addWidget(new QLabel("Editing World:"), 0, 0, 1, 1, Qt::AlignRight);
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
    levelCompletionLayout->addWidget(worldSelector, 0, 1, 1, 3);

    // Levels
    globalLevels = new QTableWidget(31, 1);
    QList<QString> levelCompletionTableHeaders = { "Completion" };
    globalLevels->setHorizontalHeaderLabels(QStringList(levelCompletionTableHeaders));
    globalLevels->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    globalLevels->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    globalLevels->verticalHeader()->setDefaultSectionSize(60);
    globalLevels->setFocusPolicy(Qt::NoFocus);
    globalLevels->setSelectionMode(QAbstractItemView::NoSelection);
    globalLevels->setEditTriggers(QAbstractItemView::NoEditTriggers);
    globalLevels->setAlternatingRowColors(true);

    setLevelNames();
    levelCompletionLayout->addWidget(globalLevels, 1, 0, 1, 4);

    for (int i = 0; i < 31; i++)
    {
        // Level Completion
        LevelCompletionWidget* levelCompletion = new LevelCompletionWidget();
        levelCompletion->setProperty("Row", i);
        connect(levelCompletion, SIGNAL(valueChanged(quint8)), this, SLOT(levelCompletionFlagChanged(quint8)));
        globalLevels->setCellWidget(i, 0, levelCompletion);
    }

    levelCompletion->setLayout(levelCompletionLayout);
    leftLayout->addWidget(levelCompletion, 3, 0, 1, 4);

    // Settings
    QGroupBox* settingsGroupBox = new QGroupBox("Settings");
    QGridLayout* settingsLayout = new QGridLayout();

    // Control Scheme Settings
    settingsLayout->addWidget(new QLabel("Control Scheme:"), 0, 0, 1, 1, Qt::AlignRight);
    controlScheme = new QComboBox(this);
    controlScheme->addItem("Type 1");
    controlScheme->addItem("Type 2");
    connect(controlScheme, SIGNAL(currentIndexChanged(int)), this, SLOT(controlSchemeChanged(int)));
    settingsLayout->addWidget(controlScheme, 0, 1, 1, 3);

    // Spotpass Settings
    spotpassSetting = new QCheckBox("Spotpass Enabled", this);
    connect(spotpassSetting, SIGNAL(toggled(bool)), this, SLOT(spotpassSettingToggled(bool)));
    settingsLayout->addWidget(spotpassSetting, 1, 1, 1, 1);

    // First Boot Flag
    firstBootFlag = new QCheckBox("Show First Boot Message", this);
    connect(firstBootFlag, SIGNAL(toggled(bool)), this, SLOT(firstBootFlagToggled(bool)));
    settingsLayout->addWidget(firstBootFlag, 1, 3, 1, 1);

    // CoinRush First Boot Flag
    coinRushFirstLoad = new QCheckBox("Show Coin Rush First Boot Message", this);
    connect(coinRushFirstLoad, SIGNAL(toggled(bool)), this, SLOT(coinRushFirstLoadToggled(bool)));
    settingsLayout->addWidget(coinRushFirstLoad, 2, 1, 1, 1);

    // Show Eshop Button
    showEshopButton = new QCheckBox("Show eShop Button", this);
    connect(showEshopButton, SIGNAL(toggled(bool)), this, SLOT(showEshopButtonToggled(bool)));
    settingsLayout->addWidget(showEshopButton, 2, 3, 1, 1);

    settingsGroupBox->setLayout(settingsLayout);
    leftLayout->addWidget(settingsGroupBox, 4, 0, 1, 4);

    mainLayout->addLayout(leftLayout);

    // Files
    filesTabWidget = new QTabWidget();

    file1 = new FileContainerWidget();
    file2 = new FileContainerWidget();
    file3 = new FileContainerWidget();

    filesTabWidget->addTab(file1, "File 1");
    filesTabWidget->addTab(file2, "File 2");
    filesTabWidget->addTab(file3, "File 3");

    mainLayout->addWidget(filesTabWidget);

    this->setLayout(mainLayout);
}

void MainEditorWidget::loadFile(BigRedSave* saveFile)
{
    this->saveFile = saveFile;

    blockAllSignals(true);

    // General
    coinMilestones->setCurrentIndex(saveFile->coinDialogFlag);
    lastFileSaved->setCurrentIndex(saveFile->lastFileSavedFlag);
    globalCoinCount->setValue(static_cast<int>(saveFile->globalCoinCount));

    // Coin Rush
    streetpassCount->setValue(static_cast<int>(saveFile->streetpassCount));
    coinRushVictories->setValue(static_cast<int>(saveFile->coinRushVictories));
    newStreetpassFlag->setChecked(saveFile->newStreetpassFlag);
    coinRushHighscore->setValue(static_cast<int>(saveFile->coinRushHighScore));
    coinRushPackType->setCurrentIndex(saveFile->coinRushHighScorePackFlag);

    for (int i = 0; i < 3; i++)
        static_cast<CoinRushStageWidget*>(coinRushLevels->cellWidget(0, i))->loadStage(saveFile->coinRushHighScoreStage[i][0], saveFile->coinRushHighScoreStage[i][1]);

    coinRushRacoonFlag->setChecked(saveFile->coinRushHighScoreRacoonFlag);

    // Global Level Completion
    worldChanged(worldSelector->currentIndex());

    // Settings
    controlScheme->setCurrentIndex(saveFile->controlScheme);
    spotpassSetting->setChecked(saveFile->spotpassSetting);
    firstBootFlag->setChecked(saveFile->firstBootFlag);
    coinRushFirstLoad->setChecked(saveFile->coinRushFirstLoadFlag);
    showEshopButton->setChecked(saveFile->eshopButtonFlag);

    // Files
    file1->LoadFile(&saveFile->file1);
    file2->LoadFile(&saveFile->file2);
    file3->LoadFile(&saveFile->file3);

    blockAllSignals(false);
}

void MainEditorWidget::blockAllSignals(bool block)
{
    // General
    coinMilestones->blockSignals(block);
    lastFileSaved->blockSignals(block);
    globalCoinCount->blockSignals(block);

    // Coin Rush
    streetpassCount->blockSignals(block);
    coinRushVictories->blockSignals(block);
    newStreetpassFlag->blockSignals(block);
    coinRushHighscore->blockSignals(block);
    coinRushPackType->blockSignals(block);

    for (int i = 0; i < 3; i++)
        static_cast<CoinRushStageWidget*>(coinRushLevels->cellWidget(0, i))->blockSignals(block);

    coinRushRacoonFlag->blockSignals(block);

    // Settings
    controlScheme->blockSignals(block);
    spotpassSetting->blockSignals(block);
    firstBootFlag->blockSignals(block);
    coinRushFirstLoad->blockSignals(block);
    showEshopButton->blockSignals(block);

    // Global Level Completion
    globalLevels->blockSignals(block);

    // Files
    filesTabWidget->blockSignals(block);
    file1->blockSignals(block);
    file2->blockSignals(block);
    file3->blockSignals(block);
}

void MainEditorWidget::setLevelNames()
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

    globalLevels->setVerticalHeaderLabels(QStringList(tableHeaders));
}

// SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// General
void MainEditorWidget::coinMilestonesChanged(int index)
{
    saveFile->coinDialogFlag = static_cast<quint8>(index);
}

void MainEditorWidget::lastFileSavedChanged(int index)
{
    saveFile->lastFileSavedFlag = static_cast<quint8>(index);
}

void MainEditorWidget::globalCoinCountChanged(int value)
{
    saveFile->globalCoinCount = static_cast<quint32>(value);
}

// Coin Rush
void MainEditorWidget::streetpassCountChanged(int index)
{
    saveFile->streetpassCount = static_cast<quint16>(index);
}

void MainEditorWidget::coinRushVictoriesChanged(int index)
{
    saveFile->coinRushVictories = static_cast<quint16>(index);
}

void MainEditorWidget::newStreetpassFlagToggled(bool toggle)
{
    saveFile->newStreetpassFlag = toggle;
}

void MainEditorWidget::coinRushHighscoreChanged(int value)
{
    saveFile->coinRushHighScore = static_cast<quint16>(value);
}

void MainEditorWidget::coinRushPackTypeChanged(int index)
{
    saveFile->coinRushHighScorePackFlag = static_cast<quint8>(index);
}

void MainEditorWidget::coinRushStageChanged(quint8 world, quint8 level)
{
    CoinRushStageWidget* coinRushStage = qobject_cast<CoinRushStageWidget*>(sender());

    int stage = coinRushStage->property("Stage").toInt();

    saveFile->coinRushHighScoreStage[stage][0] = world;
    saveFile->coinRushHighScoreStage[stage][1] = level;
}

void MainEditorWidget::coinRushRacoonFlagToggled(bool toggle)
{
    saveFile->coinRushHighScoreRacoonFlag = static_cast<quint8>(toggle);
}

// Global Level Completion
void MainEditorWidget::worldChanged(int world)
{
    setLevelNames();

    for (int i = 0; i< 31; i++)
        static_cast<LevelCompletionWidget*>(globalLevels->cellWidget(i, 0))->loadLevel(saveFile->globalLevelFlags[world][i]);
}

void MainEditorWidget::levelCompletionFlagChanged(quint8 value)
{
    LevelCompletionWidget* levelWidget = qobject_cast<LevelCompletionWidget*>(sender());

    int row = levelWidget->property("Row").toInt();
    saveFile->globalLevelFlags[worldSelector->currentIndex()][row] = value;
}

// Settings
void MainEditorWidget::controlSchemeChanged(int index)
{
    saveFile->controlScheme = static_cast<quint8>(index);
}

void MainEditorWidget::spotpassSettingToggled(bool toggle)
{
    saveFile->spotpassSetting = static_cast<quint8>(toggle);
}

void MainEditorWidget::firstBootFlagToggled(bool toggle)
{
    saveFile->firstBootFlag = static_cast<quint8>(toggle);
}

void MainEditorWidget::coinRushFirstLoadToggled(bool toggle)
{
    saveFile->coinRushFirstLoadFlag = static_cast<quint8>(toggle);
}

void MainEditorWidget::showEshopButtonToggled(bool toggle)
{
    saveFile->eshopButtonFlag = static_cast<quint8>(toggle);
}

