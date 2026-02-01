// Function: InitFurTexBuffer__6CCharaFv
// Entry: 800e1148
// Size: 292 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitFurTexBuffer__6CCharaFv(CChara *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = 0;
  iVar1 = 0;
  do {
    iVar4 = iVar1 << 1;
    iVar3 = 0;
    iVar6 = 8;
    do {
      iVar5 = iVar3 + iVar1;
      *(undefined2 *)((int)&Chara.field0_0x0.object.base_object.object.m_freeListNode + iVar4) =
           0x7fff;
      iVar4 = iVar4 + 0x10;
      *(undefined2 *)
       ((int)&Chara.field0_0x0.object.base_object.object.m_freeListNode + iVar5 * 2 + 2) = 0x7fff;
      iVar3 = iVar3 + 8;
      *(undefined2 *)((int)&Chara.field0_0x0.object.base_object.object.m_stackPointer + iVar5 * 2) =
           0x7fff;
      *(undefined2 *)
       ((int)&Chara.field0_0x0.object.base_object.object.m_stackPointer + iVar5 * 2 + 2) = 0x7fff;
      *(undefined2 *)((int)&Chara.field0_0x0.object.base_object.object.m_localBase + iVar5 * 2) =
           0x7fff;
      *(undefined2 *)((int)&Chara.field0_0x0.object.base_object.object.m_localBase + iVar5 * 2 + 2)
           = 0x7fff;
      *(undefined2 *)((int)&Chara.field0_0x0.object.base_object.object.m_thisBase + iVar5 * 2) =
           0x7fff;
      *(undefined2 *)((int)&Chara.field0_0x0.object.base_object.object.m_thisBase + iVar5 * 2 + 2) =
           0x7fff;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + 0x40;
  } while (iVar2 < 0x40);
  *(undefined4 *)&param_1->field_0x2004 = 0;
  Chara._8212_4_ = System.m_frameCounter;
  memset(&param_1->field_0x2018,0,0x40);
  CalcMogScore__6CCharaFv(param_1);
  return;
}

