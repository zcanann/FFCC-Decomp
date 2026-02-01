// Function: onChangeStat__8CGMonObjFi
// Entry: 80119528
// Size: 324 bytes

/* WARNING: Removing unreachable block (ram,0x801195fc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onChangeStat__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  
  __ptmf_scall(gMonObj,param_2,*(undefined4 *)&gMonObj->field_0x708);
  if (((2 < param_2) || (-5 < param_2)) || (param_2 < -0xe)) goto LAB_80119650;
  iVar3 = (param_2 + 0xe) * 2;
  *(uint *)&gMonObj->field_0x560 =
       (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle + iVar3 + 0xd0);
  *(uint *)&gMonObj->field_0x550 =
       (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle + iVar3 + 0xf0);
  *(int *)&gMonObj->field_0x554 = *(int *)&gMonObj->field_0x550 + 1;
  *(int *)&gMonObj->field_0x558 = *(int *)&gMonObj->field_0x554 + 1;
  *(int *)&gMonObj->field_0x55c = *(int *)&gMonObj->field_0x558 + 1;
  iVar3 = *(int *)&gMonObj->field_0x560 * 0x48;
  uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar3 + 0xe);
  if (uVar1 != 3) {
    if (2 < uVar1) goto LAB_80119650;
    if (1 < uVar1) {
      uVar2 = calcCastTime__10CGCharaObjFi(gMonObj);
      *(undefined4 *)&gMonObj->field_0x68c = uVar2;
      goto LAB_80119650;
    }
  }
  *(uint *)&gMonObj->field_0x630 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar3 + 0x20);
  *(uint *)&gMonObj->field_0x634 =
       (uint)*(ushort *)(Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 0x22);
  *(uint *)&gMonObj->field_0x638 =
       (uint)*(ushort *)(Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 0x22);
LAB_80119650:
  onChangeStat__10CGCharaObjFi(gMonObj,param_2);
  return;
}

