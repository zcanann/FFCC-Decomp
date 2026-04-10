#include "ffcc/main.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/system.h"

#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

static const char kDefaultScriptName[] = "ffcc_0";
static const char kLanguageArgUs[] = "us";
static const char kLanguageArgUk[] = "uk";
static const char kLanguageArgGr[] = "gr";
static const char kLanguageArgIt[] = "it";
static const char kLanguageArgFr[] = "fr";
static const char kLanguageArgSp[] = "sp";

void game(int argc, char** argv);

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
    bool copyScriptName;
    bool parseLanguage;
    int cmp;
    char** argument;
    int i;

    Game.Init();
    strcpy(Game.m_startScriptName, kDefaultScriptName);

    if (argc != 0) {
        copyScriptName = false;
        parseLanguage = false;
        for (i = 1, argument = argv + 1; i < argc; i++, argument++) {
            if (copyScriptName) {
                strcpy(Game.m_startScriptName, *argument);
                copyScriptName = false;
            } else if (parseLanguage) {
                cmp = strcmp(*argument, kLanguageArgUs);
                if (cmp == 0) {
                    Game.m_gameWork.m_languageId = 1;
                } else {
                    cmp = strcmp(*argument, kLanguageArgUk);
                    if (cmp == 0) {
                        Game.m_gameWork.m_languageId = 1;
                    } else {
                        cmp = strcmp(*argument, kLanguageArgGr);
                        if (cmp == 0) {
                            Game.m_gameWork.m_languageId = 2;
                        } else {
                            cmp = strcmp(*argument, kLanguageArgFr);
                            if (cmp == 0) {
                                Game.m_gameWork.m_languageId = 3;
                            } else {
                                cmp = strcmp(*argument, kLanguageArgSp);
                                if (cmp == 0) {
                                    Game.m_gameWork.m_languageId = 4;
                                } else {
                                    cmp = strcmp(*argument, kLanguageArgIt);
                                    if (cmp == 0) {
                                        Game.m_gameWork.m_languageId = 5;
                                    } else {
                                        Game.m_gameWork.m_languageId = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                parseLanguage = false;
            } else {
                c = (*argument)[0];
                if ((c == '-') || (c == '/')) {
                    c = (*argument)[1];
                    switch (c) {
                    case 'f':
                        copyScriptName = true;
                        break;
                    case 'l':
                        parseLanguage = true;
                        break;
                    }
                }
            }
        }
    }

    Game.Exec();
    Game.Quit();
}
