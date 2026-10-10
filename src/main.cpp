#include "ffcc/main.h"
#include "ffcc/game.h"
#include "ffcc/pad.h"
#include "ffcc/system.h"

#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

static void game(int, char**);

static const char kDefaultScriptName[] = "ffcc_0";
#ifndef VERSION_GCCJGC
static const char kLanguageArgUs[] = "us";
static const char kLanguageArgUk[] = "uk";
static const char kLanguageArgGr[] = "gr";
static const char kLanguageArgIt[] = "it";
static const char kLanguageArgFr[] = "fr";
static const char kLanguageArgSp[] = "sp";
#endif

#ifdef VERSION_GCCJGC
/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void game(int argc, char** argv)
{
    int copyScriptName;
    int i;

    Game.Init();
    strcpy(Game.m_startScriptName, kDefaultScriptName);

    if (argc != 0) {
        copyScriptName = 0;
        for (i = 1; i < argc; i++) {
            if (copyScriptName) {
                strcpy(Game.m_startScriptName, argv[i]);
                copyScriptName = 0;
            } else {
                char c = (argv[i])[0];
                if ((c == '-') || (c == '/')) {
                    c = (argv[i])[1];
                    switch (c) {
                    case 'f':
                        copyScriptName = 1;
                        break;
                    }
                }
            }
        }
    }

    Game.Exec();
    Game.Quit();
}
#else
static void game(int argc, char** argv);
#endif

/*
 * --INFO--
 * PAL Address: 0x80019f88
 * PAL Size: 204b
 * EN Address: 0x80019D7C
 * EN Size: 204b
 * JP Address: 0x80019964
 * JP Size: 388b
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
                Pad.m_replayPlayback = 1;
                break;
            case 'w':
                Pad.m_replayWrite = 1;
                break;
            }
        }
    }

    System.Init();
    game(argc, argv);
    System.Quit();
}

#ifndef VERSION_GCCJGC
/*
 * --INFO--
 * PAL Address: 0x8001a054
 * PAL Size: 476b
 * EN Address: 0x80019E48
 * EN Size: 476b
 * JP Address: TODO
 * JP Size: TODO
 */
void game(int argc, char** argv)
{
    int copyScriptName;
    int parseLanguage;
    int i;

    Game.Init();
    strcpy(Game.m_startScriptName, kDefaultScriptName);

    if (argc != 0) {
        copyScriptName = 0;
        parseLanguage = 0;
        for (i = 1; i < argc; i++) {
            if (copyScriptName) {
                strcpy(Game.m_startScriptName, argv[i]);
                copyScriptName = 0;
            } else if (parseLanguage) {
                int cmp = strcmp(argv[i], kLanguageArgUs);
                if (cmp == 0) {
                    Game.m_gameWork.m_languageId = 1;
                } else {
                    cmp = strcmp(argv[i], kLanguageArgUk);
                    if (cmp == 0) {
                        Game.m_gameWork.m_languageId = 1;
                    } else {
                        cmp = strcmp(argv[i], kLanguageArgGr);
                        if (cmp == 0) {
                            Game.m_gameWork.m_languageId = 2;
                        } else {
                            cmp = strcmp(argv[i], kLanguageArgIt);
                            if (cmp == 0) {
                                Game.m_gameWork.m_languageId = 3;
                            } else {
                                cmp = strcmp(argv[i], kLanguageArgFr);
                                if (cmp == 0) {
                                    Game.m_gameWork.m_languageId = 4;
                                } else {
                                    cmp = strcmp(argv[i], kLanguageArgSp);
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
                parseLanguage = 0;
            } else {
                char c = (argv[i])[0];
                if ((c == '-') || (c == '/')) {
                    c = (argv[i])[1];
                    switch (c) {
                    case 'f':
                        copyScriptName = 1;
                        break;
                    case 'l':
                        parseLanguage = 1;
                        break;
                    }
                }
            }
        }
    }

    Game.Exec();
    Game.Quit();
}
#endif
