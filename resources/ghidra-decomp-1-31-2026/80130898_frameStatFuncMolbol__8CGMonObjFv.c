// Function: frameStatFuncMolbol__8CGMonObjFv
// Entry: 80130898
// Size: 336 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncMolbol__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  CVector local_28;
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  iVar1 = *(int *)&gMonObj->field_0x520;
  if (iVar1 == 0x65) {
    iVar1 = *(int *)&gMonObj->field_0x528;
    if (((iVar1 == 0) || (iVar1 == 5)) || (iVar1 == 10)) {
      __ct__7CVectorFRC3Vec
                (&local_28,
                 &(Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]->gCharaObj).gPrgObj.object
                  .m_worldPosition);
      local_18 = 0x43300000;
      uVar2 = countLeadingZeros(*(undefined4 *)&gMonObj->field_0x528);
      uStack_14 = ~-(uVar2 >> 5 & 1) & 0x28 ^ 0x80000000;
      dVar3 = (double)RandFPM__5CMathFf((double)(float)((double)CONCAT44(0x43300000,uStack_14) -
                                                       DOUBLE_80331d38),&Math);
      local_10 = 0x43300000;
      local_28.x = (float)((double)local_28.x + dVar3);
      uVar2 = countLeadingZeros(*(undefined4 *)&gMonObj->field_0x528);
      uStack_c = ~-(uVar2 >> 5 & 1) & 0x28 ^ 0x80000000;
      dVar3 = (double)RandFPM__5CMathFf((double)(float)((double)CONCAT44(0x43300000,uStack_c) -
                                                       DOUBLE_80331d38),&Math);
      local_28.z = (float)((double)local_28.z + dVar3);
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (gMonObj,*(undefined4 *)&gMonObj->field_0x560,3,*(undefined4 *)&gMonObj->field_0x564
                 ,&local_28);
    }
    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
  }
  else if ((iVar1 < 0x65) && (99 < iVar1)) {
    suikomi__8CGMonObjFif((double)FLOAT_80331cf8,gMonObj,0x53);
  }
  return;
}

