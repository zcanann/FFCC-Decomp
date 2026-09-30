#include "global.h"
#include "text.h"

extern u8 gItemIcons[];
extern s8 gItemDescIds[][2];
extern const char sPlusText[];
extern const char sTenText[];
extern char *gTribeNames_En[];
extern char *gTribeNames_De[];
extern char *gTribeNames_Fr[];
extern char *gTribeNames_Es[];
extern char *gTribeNames_It[];
extern char *gSystemText_En[];
extern char *gSystemText_De[];
extern char *gSystemText_Fr[];
extern char *gSystemText_Es[];
extern char *gSystemText_It[];
extern char *gJobNames_En[];
extern char *gJobNames_De[];
extern char *gJobNames_Fr[];
extern char *gJobNames_Es[];
extern char *gJobNames_It[];
extern char *gStatNames_En[];
extern char *gStatNames_De[];
extern char *gStatNames_Fr[];
extern char *gStatNames_Es[];
extern char *gStatNames_It[];
extern char *gNoticeText_En[];
extern char *gNoticeText_De[];
extern char *gNoticeText_Fr[];
extern char *gNoticeText_Es[];
extern char *gNoticeText_It[];
extern char *gTraitNames_En[];
extern char *gTraitNames_De[];
extern char *gTraitNames_Fr[];
extern char *gTraitNames_Es[];
extern char *gTraitNames_It[];
extern char *gLookNames_En[];
extern char *gLookNames_De[];
extern char *gLookNames_Fr[];
extern char *gLookNames_Es[];
extern char *gLookNames_It[];
extern char *gCMakeText_En[];
extern char *gCMakeText_De[];
extern char *gCMakeText_Fr[];
extern char *gCMakeText_Es[];
extern char *gCMakeText_It[];
extern char *gLetterText_En[];
extern char *gLetterText_De[];
extern char *gLetterText_Fr[];
extern char *gLetterText_Es[];
extern char *gLetterText_It[];
extern char *gItemNames_En[];
extern char *gItemNames_De[];
extern char *gItemNames_Fr[];
extern char *gItemNames_Es[];
extern char *gItemNames_It[];
extern char *gMonsterNames_En[];
extern char *gMonsterNames_De[];
extern char *gMonsterNames_Fr[];
extern char *gMonsterNames_Es[];
extern char *gMonsterNames_It[];
extern char *gItemDescs_En[];
extern char *gItemDescs_De[];
extern char *gItemDescs_Fr[];
extern char *gItemDescs_Es[];
extern char *gItemDescs_It[];

char *Msg_GetTribe(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gTribeNames_De;
        break;
    case 2:
        tbl = gTribeNames_Fr;
        break;
    case 3:
        tbl = gTribeNames_Es;
        break;
    case 4:
        tbl = gTribeNames_It;
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
        tbl = gSystemText_Fr;
        break;
    case 3:
        tbl = gSystemText_Es;
        break;
    case 4:
        tbl = gSystemText_It;
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
        tbl = gJobNames_Fr;
        break;
    case 3:
        tbl = gJobNames_Es;
        break;
    case 4:
        tbl = gJobNames_It;
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
        tbl = gStatNames_Fr;
        break;
    case 3:
        tbl = gStatNames_Es;
        break;
    case 4:
        tbl = gStatNames_It;
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
        tbl = gNoticeText_Fr;
        break;
    case 3:
        tbl = gNoticeText_Es;
        break;
    case 4:
        tbl = gNoticeText_It;
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
        tbl = gTraitNames_Fr;
        break;
    case 3:
        tbl = gTraitNames_Es;
        break;
    case 4:
        tbl = gTraitNames_It;
        break;
    case 0:
    default:
        tbl = gTraitNames_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetLook(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gLookNames_De;
        break;
    case 2:
        tbl = gLookNames_Fr;
        break;
    case 3:
        tbl = gLookNames_Es;
        break;
    case 4:
        tbl = gLookNames_It;
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
        tbl = gCMakeText_Fr;
        break;
    case 3:
        tbl = gCMakeText_Es;
        break;
    case 4:
        tbl = gCMakeText_It;
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
        tbl = gLetterText_Fr;
        break;
    case 3:
        tbl = gLetterText_Es;
        break;
    case 4:
        tbl = gLetterText_It;
        break;
    case 0:
    default:
        tbl = gLetterText_En;
        break;
    }
    return tbl[idx];
}

char *Msg_GetItemName(s32 idx)
{
    char **tbl;

    switch (gLanguage & 0xF) {
    case 1:
        tbl = gItemNames_De;
        break;
    case 2:
        tbl = gItemNames_Fr;
        break;
    case 3:
        tbl = gItemNames_Es;
        break;
    case 4:
        tbl = gItemNames_It;
        break;
    case 0:
    default:
        tbl = gItemNames_En;
        break;
    }
    return tbl[idx];
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
        tbl = gMonsterNames_Fr;
        break;
    case 3:
        tbl = gMonsterNames_Es;
        break;
    case 4:
        tbl = gMonsterNames_It;
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
        tbl = gItemDescs_Fr;
        break;
    case 3:
        tbl = gItemDescs_Es;
        break;
    case 4:
        tbl = gItemDescs_It;
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
