// Function: cb
// Entry: 8018b624
// Size: 196 bytes

/* WARNING: Possible PIC construction at 0x8018b658: Changing call to branch */
/* WARNING: Possible PIC construction at 0x8018b680: Changing call to branch */
/* WARNING: Possible PIC construction at 0x8018b6b4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x8018b680) */
/* WARNING: Removing unreachable block (ram,0x8018b658) */
/* WARNING: Removing unreachable block (ram,0x8018b6b4) */

void cb(int param_1,undefined4 param_2)

{
  if (param_1 < 1) {
    if ((param_1 != -1) && (param_1 == -4)) {
      DAT_8032f0d0 = 0;
      DVDReset();
      DVDReadDiskID(param_2,DAT_8032f0d8,cb);
    }
  }
  else if (DAT_8032f0d0 == 1) {
    DAT_8032f0d0 = 2;
    DVDReadAbsAsyncForBS
              (param_2,*(undefined4 *)(DAT_8032f0d4 + 0x10),
               *(int *)(DAT_8032f0d4 + 8) + 0x1fU & 0xffffffe0,*(undefined4 *)(DAT_8032f0d4 + 4),cb)
    ;
  }
  else if ((DAT_8032f0d0 < 1) && (-1 < DAT_8032f0d0)) {
    DAT_8032f0d0 = 1;
    DVDReadAbsAsyncForBS(param_2,DAT_8032f0d4,0x20,0x420,cb);
  }
  return;
}

