// Function: FUN_80115c00
// Entry: 80115c00
// Size: 1716 bytes

/* WARNING: Removing unreachable block (ram,0x80116290) */
/* WARNING: Removing unreachable block (ram,0x80115c10) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void FUN_80115c00(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  CGPartyObj *pCVar6;
  double dVar7;
  double dVar8;
  int local_38 [2];
  undefined4 local_30;
  uint uStack_2c;
  
  if (-1 < *(int *)(param_1 + 0x6c4)) {
    local_30 = 0x43300000;
    uStack_2c = (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xcc);
    dVar8 = (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0);
    dVar7 = (double)PSVECDistance((Vec *)(param_1 + 0x6f8),(Vec *)(param_1 + 0x15c));
    if (dVar7 < dVar8) {
      if (*(char *)(param_1 + 0x6bd) != '\0') {
        local_30 = 0x43300000;
        uStack_2c = (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 200);
        FUN_80116870((double)*(float *)(param_1 + 0x1a8),
                     (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0),
                     param_1,6,0,local_38);
        if (-1 < local_38[0]) {
          *(int *)(param_1 + 0x6c4) = local_38[0];
          *(undefined *)(param_1 + 0x6bd) = 0;
        }
      }
      iVar3 = FUN_8011548c(param_1,*(undefined4 *)(param_1 + 0x6c4));
      if (iVar3 == -2) {
        SoundBuffer._1252_4_ = 0;
        memset(param_1 + 0x70c,0,0x34);
        *(undefined4 *)(param_1 + 0x6d8) = 0;
        *(undefined4 *)(param_1 + 0x6dc) = 0;
        *(undefined *)(param_1 + 0x6bb) = 1;
        return;
      }
      if (iVar3 != -1) {
        iVar4 = *(int *)(param_1 + 0x58);
        iVar5 = *(int *)(iVar4 + 0x24);
        if (*(short *)(iVar5 + 0x10c) == 1) {
          SoundBuffer._1252_4_ = iVar3;
          if (iVar3 < 100) {
            sVar1 = *(short *)(param_1 + 0x6e4);
            iVar2 = (int)sVar1;
            if (sVar1 != 0) {
              iVar5 = Game.game.unkCFlatData0[1] +
                      (iVar2 + (uint)*(ushort *)(iVar5 + 0x100)) * 0x1d0 + 0x10;
            }
            iVar3 = iVar3 * 0x10;
            if ((*(ushort *)(iVar5 + iVar3 + 0x110) & 0x20) != 0) {
              SoundBuffer._1252_4_ = 0x21;
              pCVar6 = Game.game.m_partyObjArr[*(int *)(param_1 + 0x6c4)];
              if (*(int *)(param_1 + 0x734) != 4) {
                memset(param_1 + 0x70c,0,0x34);
                *(undefined4 *)(param_1 + 0x70c) = 0x855;
                if ((*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xfe) & 4) != 0) {
                  *(uint *)(param_1 + 0x70c) = *(uint *)(param_1 + 0x70c) | 0x400;
                }
                if (*(short *)(param_1 + 0x6e4) == 0) {
                  iVar3 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
                }
                else {
                  iVar3 = Game.game.unkCFlatData0[1] +
                          ((int)*(short *)(param_1 + 0x6e4) +
                          (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) *
                          0x1d0 + 0x10;
                }
                if ((*(ushort *)(iVar3 + 0x102) & 0x80) != 0) {
                  *(uint *)(param_1 + 0x70c) = *(uint *)(param_1 + 0x70c) | 0x20000;
                }
                dVar7 = DOUBLE_803319e0;
                *(undefined4 *)(param_1 + 0x70c) = *(undefined4 *)(param_1 + 0x70c);
                *(undefined4 *)(param_1 + 0x734) = 4;
                *(float *)(param_1 + 0x728) =
                     (float)((double)CONCAT44(0x43300000,
                                              (uint)*(ushort *)
                                                     (*(int *)(*(int *)(param_1 + 0x58) + 0x24) +
                                                     0xd6)) - dVar7);
                *(uint *)(param_1 + 0x72c) =
                     (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x1b6);
              }
              *(CGPartyObj **)(param_1 + 0x714) = pCVar6;
              *(undefined4 *)(param_1 + 0x6d8) = 5;
              *(undefined4 *)(param_1 + 0x6dc) = 0;
              *(undefined *)(param_1 + 0x6bb) = 1;
              return;
            }
            if (sVar1 == 0) {
              iVar5 = *(int *)(iVar4 + 0x24);
            }
            else {
              iVar5 = Game.game.unkCFlatData0[1] +
                      (iVar2 + (uint)*(ushort *)(*(int *)(iVar4 + 0x24) + 0x100)) * 0x1d0 + 0x10;
            }
            uStack_2c = (uint)*(ushort *)(iVar5 + iVar3 + 0x11c);
            local_30 = 0x43300000;
            dVar7 = (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0);
            if (sVar1 == 0) {
              iVar4 = *(int *)(iVar4 + 0x24);
            }
            else {
              iVar4 = Game.game.unkCFlatData0[1] +
                      (iVar2 + (uint)*(ushort *)(*(int *)(iVar4 + 0x24) + 0x100)) * 0x1d0 + 0x10;
            }
            sVar1 = *(short *)(iVar4 + iVar3 + 0x11e);
            SoundBuffer._1252_4_ = 0x21;
            pCVar6 = Game.game.m_partyObjArr[*(int *)(param_1 + 0x6c4)];
            if (*(int *)(param_1 + 0x734) != 2) {
              memset(param_1 + 0x70c,0,0x34);
              *(undefined4 *)(param_1 + 0x70c) = 0x325;
              if (*(short *)(param_1 + 0x6e4) == 0) {
                iVar3 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
              }
              else {
                iVar3 = Game.game.unkCFlatData0[1] +
                        ((int)*(short *)(param_1 + 0x6e4) +
                        (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) *
                        0x1d0 + 0x10;
              }
              if ((*(ushort *)(iVar3 + 0x102) & 0x40) != 0) {
                *(uint *)(param_1 + 0x70c) = *(uint *)(param_1 + 0x70c) | 0x10000;
              }
              *(undefined4 *)(param_1 + 0x70c) = *(undefined4 *)(param_1 + 0x70c);
              *(undefined4 *)(param_1 + 0x734) = 2;
            }
            *(CGPartyObj **)(param_1 + 0x714) = pCVar6;
            *(float *)(param_1 + 0x728) = (float)dVar7;
            *(int *)(param_1 + 0x738) = (int)sVar1;
          }
        }
        else {
          SoundBuffer._1252_4_ = iVar3 + -0xe;
        }
        *(undefined4 *)(param_1 + 0x6d8) = 1;
        *(undefined4 *)(param_1 + 0x6dc) = 0;
        *(undefined *)(param_1 + 0x6bb) = 1;
        return;
      }
      iVar3 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
      if (*(short *)(iVar3 + 0x10c) != 1) {
        if ((int)(uint)*(ushort *)(iVar3 + 0x1ba) <= *(int *)(param_1 + 0x6dc)) {
          *(undefined4 *)(param_1 + 0x6d8) = 3;
          *(undefined4 *)(param_1 + 0x6dc) = 0;
          *(undefined *)(param_1 + 0x6bb) = 1;
          return;
        }
        SoundBuffer._1252_4_ = 3;
        return;
      }
      if (*(short *)(param_1 + 0x6e4) != 0) {
        iVar3 = Game.game.unkCFlatData0[1] +
                ((int)*(short *)(param_1 + 0x6e4) + (uint)*(ushort *)(iVar3 + 0x100)) * 0x1d0 + 0x10
        ;
      }
      if (((*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xfe) & 8) == 0) &&
         ((*(ushort *)(iVar3 + 0x102) & 0x100) == 0)) {
        SoundBuffer._1252_4_ = 0x21;
        pCVar6 = Game.game.m_partyObjArr[*(int *)(param_1 + 0x6c4)];
        if (*(int *)(param_1 + 0x734) != 1) {
          memset(param_1 + 0x70c,0,0x34);
          *(undefined4 *)(param_1 + 0x70c) = 0x205;
          if (*(short *)(param_1 + 0x6e4) == 0) {
            iVar3 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
          }
          else {
            iVar3 = Game.game.unkCFlatData0[1] +
                    ((int)*(short *)(param_1 + 0x6e4) +
                    (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) * 0x1d0 +
                    0x10;
          }
          if ((*(ushort *)(iVar3 + 0x102) & 0x40) != 0) {
            *(uint *)(param_1 + 0x70c) = *(uint *)(param_1 + 0x70c) | 0x10000;
          }
          *(undefined4 *)(param_1 + 0x734) = 1;
        }
        *(CGPartyObj **)(param_1 + 0x714) = pCVar6;
        if (((*(uint *)(param_1 + 0x710) & 1) == 0) &&
           (*(int *)(param_1 + 0x730) <
            (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x1ba))) {
          return;
        }
        SoundBuffer._1252_4_ = 0;
        memset(param_1 + 0x70c,0,0x34);
        *(undefined4 *)(param_1 + 0x6d8) = 3;
        *(undefined4 *)(param_1 + 0x6dc) = 0;
        *(undefined *)(param_1 + 0x6bb) = 1;
        return;
      }
      SoundBuffer._1252_4_ = 0;
      memset(param_1 + 0x70c,0,0x34);
      *(undefined4 *)(param_1 + 0x6d8) = 2;
      *(undefined4 *)(param_1 + 0x6dc) = 0;
      *(undefined *)(param_1 + 0x6bb) = 1;
      return;
    }
  }
  *(undefined4 *)(param_1 + 0x6c4) = 0xffffffff;
  SoundBuffer._1252_4_ = 0;
  memset(param_1 + 0x70c,0,0x34);
  *(undefined4 *)(param_1 + 0x6d8) = 3;
  *(undefined4 *)(param_1 + 0x6dc) = 0;
  *(undefined *)(param_1 + 0x6bb) = 1;
  return;
}

