#ifndef BIGREDSAVE_H
#define BIGREDSAVE_H

#include <QFile>

struct Save                                 // Block Length = 0x528
{
    quint32 score;                          // 0x00 - 0x03
    quint16 lifeCount;                      // 0x04 - 0x05
    quint8 currentPowerup;                  // 0x06
    quint8 currentInvItem;                  // 0x07
    quint8 CoinCount;                       // 0x08
    quint8 world;                           // 0x09
    quint8 mapPos;                          // 0x0A
    quint8 goldBlockFlag;                   // 0x0B
    quint32 starCoinCount;                  // 0x0C - 0x0F

    quint8 starCoinFlags[140];              // 0x10 - 0x9B
    quint8 padding0[4];                     // 0x9C - 0x9F (check this?)
    quint8 levelFlags[9][31];               // 0xA0 - 0x1B6
    quint8 padding1[9];                     // 0x1B7 - 0x1BF (Check this?)
    quint16 coinScores[9][31];              // 0x1C0 - 0x3ED
    quint16 starCoinGates[9];               // 0x3EE - 0x3FF
    quint8 rainbowFlags[9];                 // 0x400 - 0x408

    quint8 openingCutsceneFlag;             // 0x409

    quint8 unknownStuff[286];               // 0x40A - 0x527
};

struct GameFile                             // Block Length = 0xA54
{
    Save normalSave;                        // 0x00 - 0x527
    Save quickSave;                         // 0x528 - 0xA4F
    quint32 padding;                        // 0xA50 - 0xA53
};

struct Mii                                  // Block Length = 0x5C
{
    quint32 miiID;                          // 0x00 - 0x03
    quint8 systemID[8];                     // 0x04 - 0x0B
    quint32 creationDate;                   // 0x0C - 0x0F
    quint8 MACAddress[6];                   // 0x10 - 0x15
    quint16 padding;                        // 0x16 - 0x17
    quint16 miiBirthday;                    // 0x18 - 0x19
    QChar miiName[10];                      // 0x1A - 0x2D
    quint16 miiHeightWidth;                 // 0x2E - 0x2F
    quint32 miiSettings1;                   // 0x30 - 0x33
    quint32 unk1;                           // 0x34 - 0x37
    quint32 miiSettings2;                   // 0x38 - 0x3B
    quint32 unk2;                           // 0x3C - 0x3F
    quint8 copyableFlag;                    // 0x40
    quint8 unk3[7];                         // 0x41 - 0x47
    QChar creatorName[10];                  // 0x48 - 0x5B
};

struct StreetpassChallenger                 // Block Length = 0x80
{
    Mii challengerMii;                      // 0x00 - 0x5B
    quint8 unk[12];                         // 0x5C - 0x57
    quint8 packFlag;                        // 0x58 (0 - mushroom, 1 - flower, 2 - star, 3 - dlc)
    quint8 unk2[3];                         // 0x59 - 0x6B
    quint16 challengerScore;                // 0x6C - 0x6D
    quint16 playerScore;                    // 0x6E - 0x6F
    quint8 stage1World;                     // 0x70
    quint8 stage1Level;                     // 0x71
    quint8 stage2World;                     // 0x72
    quint8 stage2Level;                     // 0x73
    quint8 stage3World;                     // 0x74
    quint8 stage3Level;                     // 0x75
    quint8 favoriteFlag;                    // 0x76
    quint8 newChallengerFlag;               // 0x77
    quint8 challengerRacoonFlag;            // 0x78
    quint8 playerRacoonFlag;                // 0x79
    quint8 unk3[6];                         // 0x7A - 0x7F
};

struct BigRedSave                           // Block Length = 0x2838
{
    quint32 magic;                          // 0x00 - 0x03 (0x20000000)
    quint32 unk2;                           // 0x04 - 0x07
    quint32 unk3;                           // 0x08 - 0x0B (Related to spotpass?)
    quint32 unk4;                           // 0x0C - 0x0F
    quint32 unk5;                           // 0x10 - 0x13
    quint32 unk6;                           // 0x14 - 0x17

    GameFile file1;                         // 0x18 - 0xA6B
    GameFile file2;                         // 0xA6C - 0x14BF
    GameFile file3;                         // 0x14C0 - 0x1F13

    quint32 padding;                        // 0x1F14 - 0x1F17 (Maybe not actualy padding?)
    quint32 globalCoinCount;                // 0x1F18 - 0x1F1B

    Mii playerMii;                          // 0x1F1C - 0x1F77
    quint8 unk7[4];                         // 0x1F78 - 0x1F7B
    quint8 coinRushHighScorePackFlag;       // 0x1F7C
    quint8 unk8[3];                         // 0x1F7D - 0x1F7F
    quint16 coinRushHighScore;              // 0x1F80 - 0x1F81
    quint8 coinRushHighScoreStage[3][2];    // 0x1F82 - 0x1F87
    quint8 coinRushHighScoreRacoonFlag;     // 0x1F88
    quint8 unk9[7];                         // 0x1F89 - 0x1F8F

    StreetpassChallenger challengers[15];   // 0x1F90 - 0x270F

    quint8 controlScheme;                   // 0x2710 (May actually be quint16)
    quint8 unk10;                           // 0x2711
    quint8 spotpassSetting;                 // 0x2712 (May actually be quint16)
    quint8 unk11;                           // 0x2713
    quint16 streetpassCount;                // 0x2714 - 0x2715
    quint16 coinRushVictories;              // 0x2716 - 0x2717

    quint8 globalLevelFlags[9][31];         // 0x2718 - 0x282E

    quint8 coinDialogFlag;                  // 0x282F
    quint8 firstBootFlag;                   // 0x2830
    quint8 unk12[2];                        // 0x2831 - 0x2832
    quint8 eshopButtonFlag;                 // 0x2833
    quint8 coinRushFirstLoadFlag;           // 0x2834
    quint8 newStreetpassFlag;               // 0x2835
    quint8 unk13;                           // 0x2836
    quint8 lastFileSavedFlag;               // 0x2837
};

#endif // BIGREDSAVE_H
