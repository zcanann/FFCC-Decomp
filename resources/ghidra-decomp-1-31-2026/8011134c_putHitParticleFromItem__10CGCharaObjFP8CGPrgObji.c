// Function: putHitParticleFromItem__10CGCharaObjFP8CGPrgObji
// Entry: 8011134c
// Size: 436 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void putHitParticleFromItem__10CGCharaObjFP8CGPrgObji(CGPrgObj *gPrgObj,int param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if ((param_3 == 0x1fa) || (iVar4 = 0, param_3 == 0x237)) {
    iVar4 = DAT_8032ee64;
  }
  param_3 = param_3 * 0x48;
  uVar3 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + param_3 + 0x12);
  if ((uVar3 != 0xffff) && (uVar3 != 0xff)) {
    if (uVar3 == 0xfe) {
      iVar2 = *(int *)(*(int *)(param_2 + 0xf8) + 0x178);
      if (iVar2 == 0) {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = *(uint *)(iVar2 + 0x14);
      }
    }
    if (uVar3 == 0xfd) {
      uVar3 = 0xffffffff;
    }
    uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + param_3 + 0x1c);
    if (uVar1 != 0xffff) {
      if ((uVar1 & 0x1000) == 0) {
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) != 0) {
            uVar3 = 3;
          }
        }
        else {
          uVar3 = 2;
        }
      }
      else {
        uVar3 = 1;
      }
      ResetParticleWork__13CFlatRuntime2Fii
                ((CFlatRuntime2 *)&CFlat,uVar3 << 8 | (uVar1 & 0xff) + iVar4,0);
      if ((*(ushort *)(Game.game.unkCFlatData0[2] + param_3 + 0xc) & 0x200) == 0) {
        SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                  ((double)FLOAT_80331988,(CFlatRuntime2 *)&CFlat,DAT_8032ee60);
      }
      else {
        SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                  ((CFlatRuntime2 *)&CFlat,gPrgObj);
      }
      PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
    }
  }
  uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + param_3 + 0x42);
  if (uVar1 == 0xffff) {
    iVar2 = 0;
  }
  else {
    iVar2 = (uVar1 & 0xff) + (uint)(uVar1 >> 8) * 1000;
  }
  if (iVar2 != 0) {
    playSe3D__8CGPrgObjFiiiiP3Vec(gPrgObj,iVar2 + iVar4,0x32,0x96,0,0);
  }
  return;
}

