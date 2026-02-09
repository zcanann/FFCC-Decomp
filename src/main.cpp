#include "ffcc/main.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/system.h"

#include <string.h>

static const char lbl_801d6a40[] = "ffcc_0";
static const char lbl_801d6a48[] = "us";
static const char lbl_801d6a4c[] = "uk";
static const char lbl_801d6a50[] = "gr";
static const char lbl_801d6a54[] = "it";
static const char lbl_801d6a58[] = "fr";
static const char lbl_801d6a5c[] = "sp";

/*
 * --INFO--
 * PAL Address: 0x8001a054
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void game(int argc, char** argv)
{
    bool copyScriptName;
    bool parseLanguage;
    int i;
    char** argument;

    Game.game.Init();
    strcpy(reinterpret_cast<char*>(0x8022b7b4), lbl_801d6a40);

    if (argc != 0) {
        argument = argv + 1;
        copyScriptName = false;
        parseLanguage = false;
        for (i = 1; i < argc; i++) {
            char c;

            if (copyScriptName) {
                strcpy(reinterpret_cast<char*>(0x8022b7b4), *argument);
                copyScriptName = false;
            } else if (parseLanguage) {
                if ((strcmp(*argument, lbl_801d6a48) == 0) || (strcmp(*argument, lbl_801d6a4c) == 0)) {
                    Game.game.m_gameWork.m_languageId = 1;
                } else if (strcmp(*argument, lbl_801d6a50) == 0) {
                    Game.game.m_gameWork.m_languageId = 2;
                } else if (strcmp(*argument, lbl_801d6a58) == 0) {
                    Game.game.m_gameWork.m_languageId = 3;
                } else if (strcmp(*argument, lbl_801d6a5c) == 0) {
                    Game.game.m_gameWork.m_languageId = 4;
                } else if (strcmp(*argument, lbl_801d6a54) == 0) {
                    Game.game.m_gameWork.m_languageId = 5;
                } else {
                    Game.game.m_gameWork.m_languageId = 0;
                }
                parseLanguage = false;
            } else {
                c = (*argument)[0];
                if ((c == '-') || (c == '/')) {
                    c = (*argument)[1];
                    if (c == 'l') {
                        parseLanguage = true;
                    } else if ((c < 'l') && (c == 'f')) {
                        copyScriptName = true;
                    }
                }
            }

            argument++;
        }
    }

    Game.game.Exec();
    Game.game.Quit();
}

/*
 * --INFO--
 * PAL Address: 0x80019f88
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void main(int argc, char** argv)
{
    if (argc != 0) {
        for (int i = 1; i < argc; i++) {
            const char* argument = argv[i];
            char command;

            if ((argument[0] != '-') && (argument[0] != '/')) {
                continue;
            }

            command = argument[1];
            if (command == 'w') {
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1B8) = 1;
            } else if (command == 'r') {
                *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Pad) + 0x1B4) = 1;
            }
        }
    }

    System.Init();
    game(argc, argv);
    System.Quit();
}
