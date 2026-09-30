#include "gba_types.h"

struct Work {
    u8 unk0[0x3A];
    vu8 unk3A;
};

extern s32 lbl_03005C70;
extern s32 lbl_03005C74;
extern u8 lbl_0202BB94[];
extern char lbl_0200ECD4[];
extern char lbl_0200ECDC[];
extern char lbl_0200ECE4[];
extern char lbl_0200ECEC[];
extern struct Work lbl_03000000;

void fn_02007148();
void fn_0200720C(void *);
void fn_020091C4(void);

void fn_020001A0(s32 arg0, s32 arg1)
{
    s32 i;

    lbl_03005C70 = arg0;
    lbl_03005C74 = arg1;
    fn_02007148(lbl_0202BB94, 0, 5, lbl_0200ECD4);
    fn_02007148(lbl_0202BB94, 0, 6, lbl_0200ECDC, arg0 + 16);
    fn_02007148(lbl_0202BB94, 0, 7, lbl_0200ECE4, arg1);
    lbl_03000000.unk3A = 1;
    for (i = 0;; i++) {
        fn_02007148(lbl_0202BB94, 0, 8, lbl_0200ECEC, i % 10);
        fn_0200720C(lbl_0202BB94);
        fn_020091C4();
    }
}
