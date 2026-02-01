// Function: onChangeStat__10CGPartyObjFi
// Entry: 80124540
// Size: 768 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onChangeStat__10CGPartyObjFi(int param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  uVar3 = 0;
  *(byte *)(param_1 + 0x9b) = *(byte *)(param_1 + 0x9b) & 0xbf;
  switch(param_2) {
  case 0:
    *(byte *)(param_1 + 0x9b) = *(byte *)(param_1 + 0x9b) & 0xbf | 0x40;
    break;
  case 1:
    iVar5 = *(int *)(param_1 + 0x6c8);
    if (iVar5 == 0) {
      iVar2 = 5;
    }
    else {
      iVar2 = ((int)~(iVar5 - 1U | 1U - iVar5) >> 0x1f) + 8;
    }
    *(int *)(param_1 + 0x550) = iVar2;
    iVar5 = iVar5 * 0x12;
    *(uint *)(param_1 + 0x630) =
         (uint)*(ushort *)
                (Game.game.unk_flat3_field_30_0xc7e0 +
                ((uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e2) +
                (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e0) * 2) * 0x1ca + iVar5);
    *(uint *)(param_1 + 0x634) =
         (uint)*(ushort *)
                (Game.game.unk_flat3_field_30_0xc7e0 +
                 ((uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e2) +
                 (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e0) * 2) * 0x1ca + iVar5 + 2);
    *(uint *)(param_1 + 0x638) =
         (uint)*(ushort *)
                (Game.game.unk_flat3_field_30_0xc7e0 +
                 ((uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e2) +
                 (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e0) * 2) * 0x1ca + iVar5 + 10);
    break;
  case 2:
    *(undefined4 *)(param_1 + 0x550) = 0xf;
    *(undefined4 *)(param_1 + 0x554) = 0x10;
    *(undefined4 *)(param_1 + 0x558) = 0x11;
    if (*(int *)(param_1 + 0x560) != 0x103) {
      uVar3 = calcCastTime__10CGCharaObjFi();
    }
    *(undefined4 *)(param_1 + 0x68c) = uVar3;
    break;
  case 6:
    Printf__7CSystemFPce(&System,&DAT_801dcdb8,*(undefined4 *)(param_1 + 0x560));
    *(uint *)(param_1 + 0x560) =
         (uint)*(ushort *)(Game.game.unkCFlatData0[2] + *(int *)(param_1 + 0x560) * 0x48 + 10);
    Printf__7CSystemFPce(&System,&DAT_80331b0c,*(undefined4 *)(param_1 + 0x560));
    *(undefined4 *)(param_1 + 0x550) = 0x12;
    *(undefined4 *)(param_1 + 0x554) = 0x13;
    uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + *(int *)(param_1 + 0x560) * 0x48 + 10);
    iVar5 = (int)(uint)uVar1 >> 8;
    uVar4 = uVar1 & 0xff;
    Printf__7CSystemFPce(&System,&DAT_801dcdd8,iVar5);
    Printf__7CSystemFPce(&System,&DAT_801dcdf4,uVar4);
    *(int *)(param_1 + 0x558) = iVar5 + 0x2a;
    iVar5 = uVar4 * 0x42;
    *(uint *)(param_1 + 0x630) =
         (uint)*(ushort *)
                (Game.game.unk_flat3_field_30_0xc7e0 +
                 ((uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e2) +
                 (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e0) * 2) * 0x1ca + iVar5 + 0x38);
    *(uint *)(param_1 + 0x634) =
         (uint)*(ushort *)
                (Game.game.unk_flat3_field_30_0xc7e0 +
                 ((uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e2) +
                 (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3e0) * 2) * 0x1ca + iVar5 + 0x3a);
    uVar3 = calcCastTime__10CGCharaObjFi(param_1,*(undefined4 *)(param_1 + 0x560));
    *(undefined4 *)(param_1 + 0x68c) = uVar3;
    if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
       (iVar5 = _GetCmdListItem__12CCaravanWorkFi
                          (*(CCaravanWork **)(param_1 + 0x58),*(int *)(param_1 + 0x6dc)), -1 < iVar5
       )) {
      *(int *)(param_1 + 0x684) = iVar5;
    }
    break;
  case 8:
    *(undefined4 *)(param_1 + 0x550) = 0x15;
    *(undefined4 *)(param_1 + 0x554) = 0x16;
    *(undefined4 *)(param_1 + 0x558) = 0x17;
    *(undefined4 *)(param_1 + 0x55c) = 0x18;
  }
  onChangeStat__10CGCharaObjFi(param_1,param_2);
  return;
}

