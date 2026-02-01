// Function: shouki__10CGPartyObjFv
// Entry: 80121ba4
// Size: 924 bytes

/* WARNING: Removing unreachable block (ram,0x80121f18) */
/* WARNING: Removing unreachable block (ram,0x80121bb4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void shouki__10CGPartyObjFv(CGPartyObj *gPartyObj)

{
  int iVar1;
  void **ppvVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  
  if ((*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) == 0) ||
     (((-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x18) &&
       (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1b | (uint)((byte)CFlat._4836_1_ >> 5)))) ||
      (-1 < (int)((uint)*(byte *)((int)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags + 1)
                 << 0x18))))) {
    if (*(int *)&(gPartyObj->gCharaObj).field_0x688 != 0) {
      deletePSlotBit__10CGCharaObjFi(gPartyObj,0x200);
      *(undefined4 *)&(gPartyObj->gCharaObj).field_0x688 = 0;
    }
  }
  else {
    dVar5 = (double)PSVECDistance(&(gPartyObj->gCharaObj).gPrgObj.object.m_worldPosition,
                                  (Vec *)(Game.game.unk_flat3_0xc7d0 + 0x15c));
    if (((double)(FLOAT_80331b00 * Game.game.unkFloat_0xca10) < dVar5) ||
       ((int)((uint)(byte)CFlat._4836_1_ << 0x1b | (uint)((byte)CFlat._4836_1_ >> 5)) < 0)) {
      if (*(int *)&(gPartyObj->gCharaObj).field_0x688 != 2) {
        deletePSlotBit__10CGCharaObjFi(gPartyObj,0x200);
        ResetParticleWork__13CFlatRuntime2Fii
                  ((CFlatRuntime2 *)&CFlat,1,*(undefined4 *)&(gPartyObj->gCharaObj).field_0x588);
        SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                  ((CFlatRuntime2 *)&CFlat,Game.game.unk_flat3_0xc7d0);
        SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                  ((CFlatRuntime2 *)&CFlat,gPartyObj);
        PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      }
      *(undefined4 *)&(gPartyObj->gCharaObj).field_0x688 = 2;
    }
    else {
      deletePSlotBit__10CGCharaObjFi(gPartyObj,0x200);
      if (dVar5 < (double)(FLOAT_80331a74 * Game.game.unkFloat_0xca10)) {
        *(undefined4 *)&(gPartyObj->gCharaObj).field_0x688 = 0;
      }
      else {
        iVar1 = *(int *)&(gPartyObj->gCharaObj).gPrgObj.m_flags;
        uVar4 = iVar1 >> 0x1f;
        if ((uVar4 * 4 | iVar1 * 0x40000000 + uVar4 >> 0x1e) == uVar4) {
          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gPartyObj,0x1e,0x32,0x96,0,0);
          ResetParticleWork__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,2,0);
          SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                    ((double)(gPartyObj->gCharaObj).gPrgObj.object.m_rotBaseY,
                     (CFlatRuntime2 *)&CFlat,&(gPartyObj->gCharaObj).gPrgObj.object.m_worldPosition)
          ;
          SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                    ((CFlatRuntime2 *)&CFlat,Game.game.unk_flat3_0xc7d0);
          SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                    ((CFlatRuntime2 *)&CFlat,gPartyObj);
          PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        }
        *(undefined4 *)&(gPartyObj->gCharaObj).field_0x688 = 1;
      }
    }
    iVar1 = *(int *)&(gPartyObj->gCharaObj).field_0x688;
    if ((iVar1 == 0) &&
       (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1b | (uint)((byte)CFlat._4836_1_ >> 5)))) {
      iVar1 = 0;
      if (*(uint32_t *)&gPartyObj->field_0x6f0 == Game.game.unk_flat3_0xc7d0) {
        iVar3 = *(int *)&(gPartyObj->gCharaObj).gPrgObj.m_flags;
        if (iVar3 == (iVar3 / (int)(uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 4)) *
                     (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 4)) {
          iVar1 = 1;
        }
      }
      else {
        iVar3 = *(int *)&(gPartyObj->gCharaObj).gPrgObj.m_flags;
        if (iVar3 == (iVar3 / (int)(uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 6)) *
                     (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 6)) {
          iVar1 = 1;
        }
      }
      uVar4 = (uint)*(byte *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0x2f7);
      if ((uVar4 != 0) &&
         (iVar3 = *(int *)&(gPartyObj->gCharaObj).gPrgObj.m_flags,
         iVar3 == (iVar3 / (int)uVar4) * uVar4)) {
        iVar1 = iVar1 + 1;
      }
      if (iVar1 != 0) {
        addHp__10CGCharaObjFiP8CGPrgObj(&gPartyObj->gCharaObj,iVar1,(CGPrgObj *)0x0);
      }
    }
    else if (iVar1 == 2) {
      ppvVar2 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
      uVar4 = (uint)*(ushort *)((int)ppvVar2[9] + 0xf4);
      if (((uint)ppvVar2[0xec] & 0x2000) != 0) {
        uVar4 = uVar4 + *(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 8);
      }
      iVar1 = *(int *)&(gPartyObj->gCharaObj).gPrgObj.m_flags;
      if ((iVar1 == (iVar1 / (int)uVar4) * uVar4) &&
         (playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gPartyObj,0x19,0x32,0x96,0,0),
         -1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1a | (uint)((byte)CFlat._4836_1_ >> 6)))) {
        addHp__10CGCharaObjFiP8CGPrgObj(&gPartyObj->gCharaObj,0xffffffff,(CGPrgObj *)0x0);
      }
    }
  }
  return;
}

