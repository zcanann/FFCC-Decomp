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
    char c;
    int cmp;
    int i;
    int copyScriptName;
    int parseLanguage;
    char** argument;

    Game.game.Init();
    strcpy(Game.game.m_currentScriptName, lbl_801d6a40);

    if (argc != 0) {
        argument = argv + 1;
        copyScriptName = 0;
        parseLanguage = 0;
        for (i = 1; i < argc; i++) {
            if (copyScriptName) {
                strcpy(Game.game.m_currentScriptName, *argument);
                copyScriptName = 0;
            } else if (parseLanguage) {
                cmp = strcmp(*argument, lbl_801d6a48);
                if (cmp == 0) {
                    Game.game.m_gameWork.m_languageId = 1;
                } else {
                    cmp = strcmp(*argument, lbl_801d6a4c);
                    if (cmp == 0) {
                        Game.game.m_gameWork.m_languageId = 1;
                    } else {
                        cmp = strcmp(*argument, lbl_801d6a50);
                        if (cmp == 0) {
                            Game.game.m_gameWork.m_languageId = 2;
                        } else {
                            cmp = strcmp(*argument, lbl_801d6a58);
                            if (cmp == 0) {
                                Game.game.m_gameWork.m_languageId = 3;
                            } else {
                                cmp = strcmp(*argument, lbl_801d6a5c);
                                if (cmp == 0) {
                                    Game.game.m_gameWork.m_languageId = 4;
                                } else {
                                    cmp = strcmp(*argument, lbl_801d6a54);
                                    if (cmp == 0) {
                                        Game.game.m_gameWork.m_languageId = 5;
                                    } else {
                                        Game.game.m_gameWork.m_languageId = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                parseLanguage = 0;
            } else {
                c = (*argument)[0];
                if ((c == '-') || (c == '/')) {
                    c = (*argument)[1];
                    switch (c) {
                    case 'l':
                        parseLanguage = 1;
                        break;
                    case 'f':
                        copyScriptName = 1;
                        break;
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

            if ((argument[0] != '-') && (argument[0] != '/')) {
                continue;
            }

            switch (argument[1]) {
            case 'r':
                Pad._1b4_4_ = 1;
                break;
            case 'w':
                Pad._1b8_4_ = 1;
                break;
            }
        }
    }

    System.Init();
    game(argc, argv);
    System.Quit();
}
