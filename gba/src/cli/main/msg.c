#include "global.h"
#include "text.h"

extern const u8 gItemIcons[];
extern char *gTribeNames_En[];
extern char *gTribeNames_De[];
extern char *gTribeNames_It[];
extern char *gTribeNames_Fr[];
extern char *gTribeNames_Es[];
extern char *gSystemText_En[];
extern char *gSystemText_De[];
extern char *gSystemText_It[];
extern char *gSystemText_Fr[];
extern char *gSystemText_Es[];
extern char *gJobNames_En[];
extern char *gJobNames_De[];
extern char *gJobNames_It[];
extern char *gJobNames_Fr[];
extern char *gJobNames_Es[];
extern char *gStatNames_En[];
extern char *gStatNames_De[];
extern char *gStatNames_It[];
extern char *gStatNames_Fr[];
extern char *gStatNames_Es[];
extern char *gNoticeText_En[];
extern char *gNoticeText_De[];
extern char *gNoticeText_It[];
extern char *gNoticeText_Fr[];
extern char *gNoticeText_Es[];
extern char *gTraitNames_En[];
extern char *gTraitNames_De[];
extern char *gTraitNames_It[];
extern char *gTraitNames_Fr[];
extern char *gTraitNames_Es[];
extern char *gLookNames_En[];
extern char *gLookNames_De[];
extern char *gLookNames_It[];
extern char *gLookNames_Fr[];
extern char *gLookNames_Es[];
extern char *gCMakeText_En[];
extern char *gCMakeText_De[];
extern char *gCMakeText_It[];
extern char *gCMakeText_Fr[];
extern char *gCMakeText_Es[];
extern char *gLetterText_En[];
extern char *gLetterText_De[];
extern char *gLetterText_It[];
extern char *gLetterText_Fr[];
extern char *gLetterText_Es[];
extern char *gItemNames_En[];
extern char *gItemNames_De[];
extern char *gItemNames_It[];
extern char *gItemNames_Fr[];
extern char *gItemNames_Es[];
extern char *gMonsterNames_En[];
extern char *gMonsterNames_De[];
extern char *gMonsterNames_It[];
extern char *gMonsterNames_Fr[];
extern char *gMonsterNames_Es[];

#if defined(VERSION_GCCE01)
#include "msg_desc_us.inc"
#else
char *gItemDescs_En[] = {
    "???",
    "Weapon for Clavats",
    "Weapon for Lilties",
    "Weapon for Yukes",
    "Weapon for Selkies",
    "Armour for anyone",
    "Armour for Clavats",
    "Shield for Clavats",
    "Gauntlets for Lilties",
    "Helmet for Yukes",
    "Belt for Selkies",
    "Accessory for Clavats",
    "Accessory for Lilties",
    "Accessory for Yukes",
    "Accessory for Selkies",
    "Accessory for men",
    "Accessory for women",
    "Accessory for anyone",
    "Strength ",
    "Defence ",
    "Magic ",
    "Gain another command slot",
    "Cast Fire at any time",
    "Cast Blizzard at any time",
    "Cast Thunder at any time",
    "Cast Cure at any time",
    "Cast Life at any time",
    "Gain another heart",
    "Magicite of Fire",
    "Magicite of Blizzard",
    "Magicite of Thunder",
    "Magicite of Cure",
    "Magicite of Clear",
    "Magicite of Life",
    "Revives the fallen",
    "Material for equipment",
    "Figurine of a goddess",
    "Terrifying mask",
    "Flower seed",
    "Strangely shaped seed",
    "Fruit seed",
    "Vegetable seed",
    "Wheat seed",
    "Bandana you found",
    "Allows entry into Shella",
    "Sulphur from Mt. Kilanda",
    "Cactus flower",
    "Restores HP",
    "Wheat",
    "Flour",
    "Design for Clavats",
    "Design for Lilties",
    "Design for Yukes",
    "Design for Selkies",
    "Design for men",
    "Design for women",
    "Design for anyone",
    "Armour for anyone",
    "Armour for Clavats",
    "Bandana you found",
    "Sulphur from Mt. Kilanda",
};

char *gItemDescs_De[] = {
    "???",
    "Waffe f\xFCr Clavats",
    "Waffe f\xFCr Liltys",
    "Waffe f\xFCr Yukes",
    "Waffe f\xFCr Selkies",
    "Eine R\xFCstung",
    "R\xFCstung f\xFCr Clavats",
    "Schild f\xFCr Clavats",
    "Handschuhe f\xFCr Liltys",
    "Helm f\xFCr Yukes",
    "G\xFCrtel f\xFCr Selkies",
    "Accessoire f\xFCr Clavats",
    "Accessoire f\xFCr Liltys",
    "Accessoire f\xFCr Yukes",
    "Accessoire f\xFCr Selkies",
    "Accessoire f\xFCr M\xE4nner",
    "Accessoire f\xFCr Frauen",
    "Ein Accessoire",
    "St\xE4rke ",
    "Abwehr ",
    "Magie ",
    "Neue Kommandospalte",
    "Zur Ausf\xFChrung von Feuer",
    "Zur Ausf\xFChrung von Eis",
    "Zur Ausf\xFChrung von Blitz",
    "Zur Ausf\xFChrung von Vita",
    "Zur Ausf\xFChrung von Engel",
    "Zus\xE4tzliches Herz",
    "Zauberstein f\xFCr Feuer",
    "Zauberstein f\xFCr Eis",
    "Zauberstein f\xFCr Blitz",
    "Zauberstein f\xFCr Vita",
    "Zauberstein f\xFCr Sanitas",
    "Zauberstein f\xFCr Engel",
    "Hebt Kampfunf\xE4higkeit auf",
    "Herstellungsmaterial",
    "B\xFCste einer G\xF6ttin",
    "Maske eines D\xE4mons",
    "Samen einer Pflanze",
    "Seltsamer Samen",
    "Ein Obstkern",
    "Ein Gem\xFCsesamen",
    "Ein Weizenkorn",
    "Ein Kopftuch",
    "Passierschein f\xFCr Shella",
    "Ein Stein von Kilanda",
    "Eine Kaktusbl\xFCte",
    "Heilt die HP",
    "Wird zu Mehl verarbeitet",
    "Mehl",
    "Skizze f\xFCr Clavats",
    "Skizze f\xFCr Liltys",
    "Skizze f\xFCr Yukes",
    "Skizze f\xFCr Selkies",
    "Skizze f\xFCr M\xE4nner",
    "Skizze f\xFCr Frauen",
    "Eine Skizze",
};

char *gItemDescs_It[] = {
    "???",
    "Arma per Clavat",
    "Arma per Lility",
    "Arma per Yuke",
    "Arma per Seliky",
    "Armatura per tutti",
    "Armatura per Clavat",
    "Scudo per Clavat",
    "Manopole per Lility",
    "Elmo per Yuke",
    "Cinta per Seliky",
    "Accessorio per Clavat",
    "Accessorio per Lility",
    "Accessorio per Yuke",
    "Accessorio per Seliky",
    "Accessorio da uomo",
    "Accessorio da donna",
    "Accessorio per tutti",
    "Forza ",
    "Difesa ",
    "Magia ",
    "Comando aggiuntivo in lista",
    "Puoi lanciare Fire in ogni momento",
    "Puoi lanciare Blizzard in ogni momento",
    "Puoi lanciare Thunder in ogni momento",
    "Puoi lanciare Energia in ogni momento",
    "Puoi lanciare Reiz in ogni momento",
    "Ottieni un altro cuore",
    "Magicite di Fire",
    "Magicite di Blizzard",
    "Magicite di Thunder",
    "Magicite di Energia",
    "Magicite di Esuna",
    "Magicite di Reiz",
    "Rianima i caduti",
    "Materiale per equipaggiamento",
    "Statuetta di una dea",
    "Maschera terrificante",
    "Semi di fiore",
    "Semi dalla forma bizzarra",
    "Semi di frutto",
    "Semi di verdura",
    "Semi di grano",
    "Una bandana che hai trovato",
    "Permesso di accesso a Shella",
    "Zolfo del Monte Kilanda",
    "Fiore di cactus",
    "Ripristina PV",
    "Grano",
    "Farina",
    "Progetto per Clavat",
    "Progetto per Lility",
    "Progetto per Yuke",
    "Progetto per Seliky",
    "Progetto per uomini",
    "Progetto per donne",
    "Progetto per tutti",
};

char *gItemDescs_Fr[] = {
    "???",
    "Arme pour Clavat",
    "Arme pour Lilty",
    "Arme pour Yuke",
    "Arme pour Selkie",
    "Armure pour tous",
    "Armure pour Clavat",
    "Bouclier pour Clavat",
    "Gantelets pour Lilty",
    "Casque pour Yuke",
    "Ceinture pour Selkie",
    "Accessoire pour Clavat",
    "Accessoire pour Lilty",
    "Accessoire pour Yuke",
    "Accessoire pour Selkie",
    "Accessoire pour homme",
    "Accessoire pour femme",
    "Accessoire pour tous",
    "Force ",
    "R\xE9sistance ",
    "Magie ",
    "Fait gagner un champ de commande",
    "Permet de lancer Brasier",
    "Permet de lancer Glacier",
    "Permet de lancer Foudre",
    "Permet de lancer Soin",
    "Permet de lancer Vie",
    "Fait gagner un c\x9Cur",
    "Magilithe de Brasier",
    "Magilithe de Glacier",
    "Magilithe de Foudre",
    "Magilithe de Soin",
    "Magilithe de Esuna",
    "Magilithe de Vie",
    "Ressuscite les morts",
    "Mat\xE9riau pour \xE9quipement",
    "Figurine d'une d\xE9" "esse",
    "Masque terrifiant",
    "Graine de fleur",
    "Graine de forme \xE9trange",
    "Graine de fruit",
    "Graine de l\xE9gume",
    "Graine de bl\xE9",
    "Bandana trouv\xE9",
    "Pour acc\xE9" "der \xE0 Shella",
    "Soufre du mont Kilanda",
    "Fleur de cactus",
    "R\xE9g\xE9n\xE8re les PV",
    "Bl\xE9",
    "Farine",
    "Sch\xE9ma pour Clavat",
    "Sch\xE9ma pour Lilty",
    "Sch\xE9ma pour Yuke",
    "Sch\xE9ma pour Selkie",
    "Sch\xE9ma pour homme",
    "Sch\xE9ma pour femme",
    "Sch\xE9ma pour tous",
};

char *gItemDescs_Es[] = {
    "\xBF\xBF??",
    "Arma para Clavates",
    "Arma para Liltis",
    "Arma para Yukos",
    "Arma para Selkis",
    "Armadura para todos",
    "Armadura para Clavates",
    "Escudo para Clavates",
    "Guanteletes para Liltis",
    "Cascos para Yukos",
    "Cintur\xF3n para Selkis",
    "Accesorio para Clavates",
    "Accesorio para Liltis",
    "Accesorio para Yukos",
    "Accesorio para Selkis",
    "Accesorio de hombre",
    "Accesorio de mujer",
    "Accesorio para todos",
    "Fuerza ",
    "Defensa ",
    "Magia ",
    "Obtienes otra ranura de comando",
    "Permite lanzar Piro",
    "Permite lanzar Hielo",
    "Permite lanzar Electro",
    "Permite lanzar Cura",
    "Permite lanzar L\xE1zaro",
    "Permite obtener otro coraz\xF3n",
    "Magicita de Fuego",
    "Magicita de Hielo",
    "Magicita de Electro",
    "Magicita de Cura",
    "Magicita de Esuna",
    "Magicita de L\xE1zaro",
    "Revive a los ca\xED" "dos",
    "Material de equipamiento",
    "Estatuilla de una diosa",
    "M\xE1scara espantosa",
    "Semilla de flor",
    "Semilla de forma extra\xF1" "a",
    "Semilla de fruta",
    "Semilla de legumbre",
    "Semilla de trigo",
    "Bandana encontrada",
    "Acceso a Sulena",
    "Sulfuro de Mte. Kilandia",
    "Flor de cactus",
    "Restituye la VIT",
    "Trigo",
    "Harina",
    "Dise\xF1o para Clavates",
    "Dise\xF1o para Liltis",
    "Dise\xF1o para Yukos",
    "Dise\xF1o para Selkis",
    "Dise\xF1o para hombre",
    "Dise\xF1o para mujer",
    "Dise\xF1o para todos",
};

#endif

const s8 gItemDescIds[][2] = {
    { 0, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 },
    { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 0, 0 }, { 0, 0 }, { 1, 0 },
    { 0, 0 }, { 0, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 },
    { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 }, { 2, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 },
    { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 }, { 3, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 4, 0 }, { 4, 0 }, { 4, 0 }, { 4, 0 },
    { 4, 0 }, { 4, 0 }, { 4, 0 }, { 4, 0 }, { 4, 0 }, { 4, 0 }, { 4, 0 }, { 4, 0 },
    { 4, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 },
    { 5, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 },
    { 5, 0 }, { 5, 0 }, { 5, 0 }, { 6, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 }, { 5, 0 },
    { 7, 0 }, { 7, 0 }, { 7, 0 }, { 7, 0 }, { 7, 0 }, { 7, 0 }, { 7, 0 }, { 7, 0 },
    { 7, 0 }, { 7, 0 }, { 8, 0 }, { 8, 0 }, { 8, 0 }, { 8, 0 }, { 8, 0 }, { 8, 0 },
    { 8, 0 }, { 8, 0 }, { 8, 0 }, { 9, 0 }, { 9, 0 }, { 9, 0 }, { 9, 0 }, { 9, 0 },
    { 9, 0 }, { 9, 0 }, { 9, 0 }, { 9, 0 }, { 9, 0 }, { 10, 0 }, { 10, 0 }, { 10, 0 },
    { 10, 0 }, { 10, 0 }, { 10, 0 }, { 10, 0 }, { 10, 0 }, { 10, 0 }, { 10, 0 }, { 17, 0 },
    { 17, 0 }, { 17, 0 }, { 17, 0 }, { 17, 0 }, { 17, 0 }, { 17, 0 }, { 17, 0 }, { 13, 0 },
    { 11, 0 }, { 16, 0 }, { 14, 0 }, { 14, 0 }, { 14, 0 }, { 15, 0 }, { 13, 0 }, { 11, 0 },
    { 12, 0 }, { 14, 0 }, { 17, 0 }, { 13, 0 }, { 11, 0 }, { 15, 0 }, { 16, 0 }, { 12, 0 },
    { 14, 0 }, { 12, 0 }, { 12, 0 }, { 13, 0 }, { 13, 0 }, { 13, 0 }, { 17, 0 }, { 18, 1 },
    { 18, 1 }, { 18, 1 }, { 18, 1 }, { 18, 1 }, { 18, 2 }, { 18, 2 }, { 18, 2 }, { 18, 2 },
    { 18, 2 }, { 18, 3 }, { 18, 3 }, { 18, 3 }, { 18, 4 }, { 18, 5 }, { 18, 5 }, { 18, 1 },
    { 18, 1 }, { 18, 1 }, { 18, 1 }, { 18, 2 }, { 18, 3 }, { 18, 3 }, { 20, 1 }, { 20, 1 },
    { 20, 1 }, { 20, 1 }, { 20, 3 }, { 20, 3 }, { 20, 3 }, { 20, 5 }, { 20, 5 }, { 20, 7 },
    { 20, 10 }, { 20, 1 }, { 20, 1 }, { 20, 1 }, { 20, 1 }, { 20, 1 }, { 20, 3 }, { 20, 3 },
    { 20, 5 }, { 20, 5 }, { 20, 7 }, { 20, 9 }, { 19, 2 }, { 19, 3 }, { 19, 4 }, { 19, 1 },
    { 19, 1 }, { 19, 1 }, { 19, 1 }, { 19, 2 }, { 19, 2 }, { 19, 2 }, { 19, 3 }, { 19, 4 },
    { 19, 5 }, { 19, 2 }, { 19, 2 }, { 21, 0 }, { 21, 0 }, { 21, 0 }, { 21, 0 }, { 22, 0 },
    { 23, 0 }, { 24, 0 }, { 25, 0 }, { 26, 0 }, { 27, 0 }, { 27, 0 }, { 27, 0 }, { 27, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 28, 0 }, { 29, 0 }, { 30, 0 }, { 0, 0 }, { 0, 0 }, { 31, 0 }, { 32, 0 }, { 33, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 34, 0 }, { 35, 0 }, { 35, 0 },
    { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 },
    { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 },
    { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 },
    { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 },
    { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 },
    { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 },
    { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 }, { 35, 0 },
    { 36, 0 }, { 37, 0 }, { 0, 0 }, { 38, 0 }, { 39, 0 }, { 40, 0 }, { 40, 0 }, { 40, 0 },
    { 41, 0 }, { 41, 0 }, { 41, 0 }, { 42, 0 }, { 43, 0 }, { 44, 0 }, { 45, 0 }, { 46, 0 },
    { 0, 0 }, { 35, 0 }, { 35, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 47, 0 }, { 47, 0 }, { 47, 0 },
    { 47, 0 }, { 47, 0 }, { 47, 0 }, { 47, 0 }, { 47, 0 }, { 47, 0 }, { 47, 0 }, { 47, 0 },
    { 47, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 48, 0 }, { 49, 0 }, { 0, 0 },
    { 0, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 },
    { 51, 0 }, { 51, 0 }, { 50, 0 }, { 53, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 },
    { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 },
    { 56, 0 }, { 50, 0 }, { 50, 0 }, { 50, 0 }, { 50, 0 }, { 50, 0 }, { 50, 0 }, { 50, 0 },
    { 50, 0 }, { 50, 0 }, { 50, 0 }, { 51, 0 }, { 51, 0 }, { 51, 0 }, { 51, 0 }, { 51, 0 },
    { 51, 0 }, { 51, 0 }, { 51, 0 }, { 52, 0 }, { 52, 0 }, { 52, 0 }, { 52, 0 }, { 52, 0 },
    { 52, 0 }, { 52, 0 }, { 52, 0 }, { 52, 0 }, { 53, 0 }, { 53, 0 }, { 53, 0 }, { 53, 0 },
    { 53, 0 }, { 53, 0 }, { 53, 0 }, { 53, 0 }, { 53, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 },
    { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 56, 0 }, { 52, 0 }, { 50, 0 }, { 55, 0 },
    { 53, 0 }, { 53, 0 }, { 53, 0 }, { 54, 0 }, { 52, 0 }, { 50, 0 }, { 51, 0 }, { 53, 0 },
    { 56, 0 }, { 52, 0 }, { 50, 0 }, { 54, 0 }, { 55, 0 }, { 51, 0 }, { 53, 0 }, { 51, 0 },
    { 51, 0 }, { 52, 0 }, { 52, 0 }, { 52, 0 }, { 56, 0 }, { 56, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

const char sPlusText[] = "+";
const char sTenText[] = "10";

#if !defined(VERSION_GCCJGC)
/*
 * --INFO--
 * PAL Address: 0x0201A6D4
 * PAL Size: 104b
 * EN Address: 0x0201A4F8
 * EN Size: 104b
 * JP Address: N/A (table lookup is inlined)
 * JP Size: 0b
 */
char *Msg_GetTribe(s32 idx)
{
    char **tbl;

#if defined(VERSION_GCCE01)
    switch ((s8)gLanguage) {
#else
    switch (gLanguage & 0xF) {
#endif
    case 1:
        tbl = gTribeNames_De;
        break;
    case 2:
        tbl = gTribeNames_It;
        break;
    case 3:
        tbl = gTribeNames_Fr;
        break;
    case 4:
        tbl = gTribeNames_Es;
        break;
    case 0:
    default:
        tbl = gTribeNames_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetSystem(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gSystemText_De;
        break;
    case 2:
        tbl = gSystemText_It;
        break;
    case 3:
        tbl = gSystemText_Fr;
        break;
    case 4:
        tbl = gSystemText_Es;
        break;
    case 0:
    default:
        if (gLanguage & 0x10) {
            if (idx == 51)
                return gSystemText_En[64];
            if (idx == 63)
                return gSystemText_En[65];
        }
        tbl = gSystemText_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetJob(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gJobNames_De;
        break;
    case 2:
        tbl = gJobNames_It;
        break;
    case 3:
        tbl = gJobNames_Fr;
        break;
    case 4:
        tbl = gJobNames_Es;
        break;
    case 0:
    default:
        tbl = gJobNames_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetStat(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gStatNames_De;
        break;
    case 2:
        tbl = gStatNames_It;
        break;
    case 3:
        tbl = gStatNames_Fr;
        break;
    case 4:
        tbl = gStatNames_Es;
        break;
    case 0:
    default:
        tbl = gStatNames_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetNotice(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gNoticeText_De;
        break;
    case 2:
        tbl = gNoticeText_It;
        break;
    case 3:
        tbl = gNoticeText_Fr;
        break;
    case 4:
        tbl = gNoticeText_Es;
        break;
    case 0:
    default:
        tbl = gNoticeText_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetTrait(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gTraitNames_De;
        break;
    case 2:
        tbl = gTraitNames_It;
        break;
    case 3:
        tbl = gTraitNames_Fr;
        break;
    case 4:
        tbl = gTraitNames_Es;
        break;
    case 0:
    default:
        tbl = gTraitNames_En;
        break;
    }
    return tbl[idx];
}

#endif

char *Msg_GetLook(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gLookNames_De;
        break;
    case 2:
        tbl = gLookNames_It;
        break;
    case 3:
        tbl = gLookNames_Fr;
        break;
    case 4:
        tbl = gLookNames_Es;
        break;
    case 0:
    default:
        tbl = gLookNames_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetCMake(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gCMakeText_De;
        break;
    case 2:
        tbl = gCMakeText_It;
        break;
    case 3:
        tbl = gCMakeText_Fr;
        break;
    case 4:
        tbl = gCMakeText_Es;
        break;
    case 0:
    default:
        tbl = gCMakeText_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetLetter(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gLetterText_De;
        break;
    case 2:
        tbl = gLetterText_It;
        break;
    case 3:
        tbl = gLetterText_Fr;
        break;
    case 4:
        tbl = gLetterText_Es;
        break;
    case 0:
    default:
        tbl = gLetterText_En;
        break;
    }
    return tbl[idx];
}

/*
 * --INFO--
 * PAL Address: 0x0201AAAC
 * PAL Size: 104b
 * EN Address: 0x0201A8D0
 * EN Size: 16b
 * JP Address: TODO
 * JP Size: TODO
 */
char *Msg_GetItemName(s32 idx)
{
#if defined(VERSION_GCCE01)
    return gItemNames_En[idx];
#else
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gItemNames_De;
        break;
    case 2:
        tbl = gItemNames_It;
        break;
    case 3:
        tbl = gItemNames_Fr;
        break;
    case 4:
        tbl = gItemNames_Es;
        break;
    case 0:
    default:
        tbl = gItemNames_En;
        break;
    }
    return tbl[idx];
#endif
}

s32 Item_GetIcon(s32 idx)
{
    return gItemIcons[idx];
}

char *Msg_GetMonsterName(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gMonsterNames_De;
        break;
    case 2:
        tbl = gMonsterNames_It;
        break;
    case 3:
        tbl = gMonsterNames_Fr;
        break;
    case 4:
        tbl = gMonsterNames_Es;
        break;
    case 0:
    default:
        tbl = gMonsterNames_En;
        break;
    }
    return tbl[idx];
}

void Msg_GetItemDesc(s32 idx, char *buf)
{
    char **tbl;
    char *str;
    s32 id = gItemDescIds[idx][0];
    s32 num;
    char digit[2];

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gItemDescs_De;
        break;
    case 2:
        tbl = gItemDescs_It;
        break;
    case 3:
        tbl = gItemDescs_Fr;
        break;
    case 4:
        tbl = gItemDescs_Es;
        break;
    case 0:
    default:
        if (gLanguage & 0x10) {
            if (id == 5 || id == 6) {
                str = gItemDescs_En[id + 52];
                goto copy;
            }
            if (id == 43) {
                str = gItemDescs_En[59];
                goto copy;
            }
            if (id == 45) {
                str = gItemDescs_En[60];
                goto copy;
            }
        }
        tbl = gItemDescs_En;
        break;
    }
    str = tbl[id];
copy:
    strcpy(buf, str);
    num = gItemDescIds[idx][1];
    if (num > 0) {
        strcat(buf, sPlusText);
        if (num > 9) {
            strcat(buf, sTenText);
        } else {
            digit[0] = num + '0';
            digit[1] = 0;
            strcat(buf, digit);
        }
    }
}
