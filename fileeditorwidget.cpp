#include "fileeditorwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>

FileEditorWidget::FileEditorWidget(QWidget* parent) : QWidget(parent)
{
    QGridLayout* mainLayout = new QGridLayout();

    // Score
    mainLayout->addWidget(new QLabel("Score:"), 0, 0, 1, 1, Qt::AlignRight);
    score = new QSpinBox(this);
    score->setRange(0, 999999999);
    connect(score, SIGNAL(valueChanged(int)), this, SLOT(scoreChanged(int)));
    mainLayout->addWidget(score, 0, 1, 1, 1);

    // Powerup
    mainLayout->addWidget(new QLabel("Player State:"), 0, 2, 1, 1, Qt::AlignRight);
    powerup = new QComboBox(this);
    powerup->addItem("Small");
    powerup->addItem("Super");
    powerup->addItem("Fire");
    powerup->addItem("Mini");
    powerup->addItem("Tanooki");
    powerup->addItem("Gold");
    powerup->addItem("White Tanooki");
    connect(powerup, SIGNAL(currentIndexChanged(int)), this, SLOT(powerupChanged(int)));
    mainLayout->addWidget(powerup, 0, 3, 1, 1);

    // Lives
    mainLayout->addWidget(new QLabel("Lives:"), 1, 0, 1, 1, Qt::AlignRight);
    lives = new QSpinBox(this);
    lives->setRange(0, 1110);
    connect(lives, SIGNAL(valueChanged(int)), this, SLOT(livesChanged(int)));
    mainLayout->addWidget(lives, 1, 1, 1, 1);

    // Inventory
    mainLayout->addWidget(new QLabel("Inventory Item:"), 1, 2, 1, 1, Qt::AlignRight);
    inventory = new QComboBox(this);
    inventory->addItem("Mushroom");
    inventory->addItem("Fire Flower");
    inventory->addItem("Star");
    inventory->addItem("Mini Mushroom");
    inventory->addItem("Super Leaf");
    inventory->addItem("Gold Flower");
    inventory->addItem("Nothing");
    connect(inventory, SIGNAL(currentIndexChanged(int)), this, SLOT(inventoryChanged(int)));
    mainLayout->addWidget(inventory, 1, 3, 1, 1);

    // Coin Count
    mainLayout->addWidget(new QLabel("Coin Count:"), 2, 0, 1, 1, Qt::AlignRight);
    coinCount = new QSpinBox(this);
    coinCount->setRange(0, 99);
    connect(coinCount, SIGNAL(valueChanged(int)), this, SLOT(coinCountChanged(int)));
    mainLayout->addWidget(coinCount, 2, 1, 1, 1);

    // Star Coin Count
    mainLayout->addWidget(new QLabel("StarCoin Count:"), 2, 2, 1, 1, Qt::AlignRight);
    starCoinCount = new QSpinBox(this);
    starCoinCount->setRange(0, 219);
    connect(starCoinCount, SIGNAL(valueChanged(int)), this, SLOT(starCoinCountChanged(int)));
    mainLayout->addWidget(starCoinCount, 2, 3, 1, 1);

    // World
    mainLayout->addWidget(new QLabel("Curent World:"), 3, 0, 1, 1, Qt::AlignRight);
    world = new QComboBox(this);
    world->addItem("World 1");
    world->addItem("World 2");
    world->addItem("World 3");
    world->addItem("World 4");
    world->addItem("World 5");
    world->addItem("World 6");
    world->addItem("World Mushroom");
    world->addItem("World Flower");
    world->addItem("World Star");
    connect(world, SIGNAL(currentIndexChanged(int)), this, SLOT(worldChanged(int)));
    mainLayout->addWidget(world, 3, 1, 1, 1);

    // Map Position
    mainLayout->addWidget(new QLabel("Curent Map Position:"), 3, 2, 1, 1, Qt::AlignRight);
    mapPosition = new QSpinBox(this);
    mapPosition->setRange(0, 255);
    connect(mapPosition, SIGNAL(valueChanged(int)), this, SLOT(mapPositionChanged(int)));
    mainLayout->addWidget(mapPosition, 3, 3, 1, 1);

    mainLayout->addWidget(new HorLine(), 4, 0, 1, 4);

    // Opening Cutscene Flag
    openingCutsceneFlag = new QCheckBox("Play Opening Cutscene", this);
    connect(openingCutsceneFlag, SIGNAL(toggled(bool)), this, SLOT(openingCutsceneFlagToggled(bool)));
    mainLayout->addWidget(openingCutsceneFlag, 5, 1, 1, 1);

    // Gold Block Flag
    goldBlockFlag = new QCheckBox("Gold Block Active", this);
    connect(goldBlockFlag, SIGNAL(toggled(bool)), this, SLOT(goldBlockFlagToggled(bool)));
    mainLayout->addWidget(goldBlockFlag, 5, 3, 1, 1);

    // World Editor
    QGroupBox* worldEditorGroupBox = new QGroupBox("World");
    QHBoxLayout* worldEditorLayout = new QHBoxLayout();

    worldEditor = new WorldEditorWidget();
    worldEditorLayout->addWidget(worldEditor);
    worldEditorGroupBox->setLayout(worldEditorLayout);

    mainLayout->addWidget(worldEditorGroupBox, 6, 0, 1, 4);


    this->setLayout(mainLayout);
}

void FileEditorWidget::loadFile(Save* file)
{
    this->file = file;

    blockAllSignals(true);

    score->setValue(static_cast<int>(file->score));
    setPowerupIndex();
    lives->setValue(static_cast<int>(file->lifeCount));
    setInventoryIndex();
    coinCount->setValue(static_cast<int>(file->CoinCount));
    starCoinCount->setValue(static_cast<int>(file->starCoinCount));
    world->setCurrentIndex(file->world);
    mapPosition->setValue(static_cast<int>(file->mapPos));
    openingCutsceneFlag->setChecked(!file->openingCutsceneFlag);
    goldBlockFlag->setChecked(file->goldBlockFlag);
    worldEditor->loadFile(file);

    blockAllSignals(false);
}

void FileEditorWidget::blockAllSignals(bool block)
{
    score->blockSignals(block);
    powerup->blockSignals(block);
    lives->blockSignals(block);
    inventory->blockSignals(block);
    coinCount->blockSignals(block);
    starCoinCount->blockSignals(block);
    world->blockSignals(block);
    mapPosition->blockSignals(block);
    openingCutsceneFlag->blockSignals(block);
    goldBlockFlag->blockSignals(block);
}

void FileEditorWidget::setPowerupIndex()
{
    switch (file->currentPowerup)
    {
        case 6:
            powerup->setCurrentIndex(5);
            break;
        case 7:
            powerup->setCurrentIndex(6);
            break;
        default:
            powerup->setCurrentIndex(file->currentPowerup);
    }
}

void FileEditorWidget::setInventoryIndex()
{
    switch (file->currentInvItem)
    {
        case 4:
            inventory->setCurrentIndex(3);
            break;
        case 6:
            inventory->setCurrentIndex(4);
            break;
        case 7:
            inventory->setCurrentIndex(5);
            break;
        case 9:
            inventory->setCurrentIndex(6);
            break;
        default:
            inventory->setCurrentIndex(file->currentInvItem);
            break;
    }
}

// SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void FileEditorWidget::scoreChanged(int value)
{
    file->score = static_cast<quint32>(value);
}

void FileEditorWidget::powerupChanged(int value)
{
    switch (value)
    {
        case 5:
            file->currentPowerup = static_cast<quint8>(6);
            break;
        case 6:
            file->currentPowerup = static_cast<quint8>(7);
            break;
        default:
            file->currentPowerup = static_cast<quint8>(value);
            break;
    }
}

void FileEditorWidget::livesChanged(int value)
{
    file->lifeCount = static_cast<quint16>(value);
}

void FileEditorWidget::inventoryChanged(int value)
{
    switch (value)
    {
        case 3:
            file->currentInvItem = static_cast<quint8>(4);
            break;
        case 4:
            file->currentInvItem = static_cast<quint8>(6);
            break;
        case 5:
            file->currentInvItem = static_cast<quint8>(7);
            break;
        case 6:
            file->currentInvItem = static_cast<quint8>(9);
            break;
        default:
            file->currentInvItem = static_cast<quint8>(value);
            break;
    }
}

void FileEditorWidget::coinCountChanged(int value)
{
    file->CoinCount = static_cast<quint8>(value);
}

void FileEditorWidget::starCoinCountChanged(int value)
{
    file->starCoinCount = static_cast<quint32>(value);
}

void FileEditorWidget::worldChanged(int value)
{
    file->world = static_cast<quint8>(value);
}

void FileEditorWidget::mapPositionChanged(int value)
{
    file->mapPos = static_cast<quint8>(value);
}

void FileEditorWidget::openingCutsceneFlagToggled(bool toggle)
{
    file->openingCutsceneFlag = static_cast<quint8>(!toggle);
}

void FileEditorWidget::goldBlockFlagToggled(bool toggle)
{
    file->goldBlockFlag = static_cast<quint8>(toggle);
}

// File Container Widget

FileContainerWidget::FileContainerWidget(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout();

    normal = new FileEditorWidget();
    quick = new FileEditorWidget();

    QTabWidget* tabWidget = new QTabWidget();
    tabWidget->setTabPosition(QTabWidget::West);
    tabWidget->addTab(normal, "Normal Save");
    tabWidget->addTab(quick, "Quick Save");

    mainLayout->addWidget(tabWidget);

    this->setLayout(mainLayout);
}

void FileContainerWidget::LoadFile(GameFile* file)
{
    normal->loadFile(&file->normalSave);
    quick->loadFile(&file->quickSave);
}
