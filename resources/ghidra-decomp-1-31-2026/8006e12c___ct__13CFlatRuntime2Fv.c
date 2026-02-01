// Function: __ct__13CFlatRuntime2Fv
// Entry: 8006e12c
// Size: 1516 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CFlatRuntime2 * __ct__13CFlatRuntime2Fv(CFlatRuntime2 *flatRuntime2)

{
  float fVar1;
  short sVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  short sVar10;
  CGQuadObj *pCVar7;
  CGObject *pCVar8;
  CGItemObj *pCVar9;
  short sVar11;
  short sVar12;
  ushort uVar13;
  short sVar14;
  ushort uVar15;
  short sVar16;
  short sVar17;
  CGBaseObj *pCVar18;
  short sVar19;
  int iVar20;
  int iVar21;
  
  __ct__12CFlatRuntimeFv(&flatRuntime2->flatRuntimeBase);
  (flatRuntime2->flatRuntimeBase).vtable = &PTR_PTR_s_CFlatRuntime2_801fcc14;
  *(undefined4 *)&flatRuntime2->field_0x170c = 0xffffffff;
  fVar1 = FLOAT_80330140;
  *(undefined4 *)&flatRuntime2->field_0x16fc = 0xffffffff;
  flatRuntime2->field_0x1700 = 0;
  flatRuntime2->field_0x1701 = 1;
  *(undefined4 *)&flatRuntime2->field_0x1704 = 0;
  flatRuntime2->field_0x1702 = 0;
  *(undefined4 *)&flatRuntime2->field_0x1708 = 0x1e;
  *(undefined4 *)&flatRuntime2->field_0x1710 = 0;
  *(undefined2 *)&flatRuntime2->field_0x1714 = 0;
  flatRuntime2->field_0x1716 = 0;
  flatRuntime2->field_0x1717 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16cc = 0;
  *(undefined4 *)&flatRuntime2->field_0x16d0 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16d4 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16d8 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16dc = 0;
  *(undefined4 *)&flatRuntime2->field_0x16e0 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16e4 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16e8 = 0;
  *(undefined4 *)&flatRuntime2->field_0x16ec = 0;
  *(float *)&flatRuntime2->field_0x16f0 = fVar1;
  *(float *)&flatRuntime2->field_0x16f4 = fVar1;
  flatRuntime2->field_0x16f8 = 0;
  __construct_array(&flatRuntime2->field_0x1bdc,__ct__9CLine<64>Fv,0,0xb14,0x10);
  __ct__9CFlatDataFv((CFlatData *)&flatRuntime2->field_0xcf20);
  *(undefined4 *)&flatRuntime2->field_0x10418 = 0;
  *(undefined4 *)&flatRuntime2->field_0x129c = 0;
  *(undefined4 *)&flatRuntime2->field_0x12a0 = 0;
  *(undefined4 *)&flatRuntime2->field_0x12a4 = 0xffffffff;
  flatRuntime2->field_0x12e4 = flatRuntime2->field_0x12e4 & 0xfb | 4;
  *(undefined4 *)&flatRuntime2->field_0x10400 = 0;
  *(undefined4 *)&flatRuntime2->field_0x10408 = 0;
  memset(&flatRuntime2->field_0x15cc,0,0x100);
  memset(&flatRuntime2->field_0x1770,0,0x60);
  resetChangeScript__13CFlatRuntime2Fv(flatRuntime2);
  memset(&flatRuntime2->field_0x12f0,0,0x48);
  pCVar18 = m_gBaseObjArr;
  sVar19 = 0;
  iVar20 = 5;
  do {
    pCVar18->m_isActive = pCVar18->m_isActive & 0x7f;
    sVar17 = sVar19 + 2;
    sVar16 = sVar19 + 3;
    sVar14 = sVar19 + 4;
    (pCVar18->object).m_particleId = sVar19 + 1;
    sVar12 = sVar19 + 5;
    sVar11 = sVar19 + 6;
    sVar10 = sVar19 + 7;
    sVar2 = sVar19 + 8;
    sVar19 = sVar19 + 8;
    pCVar18[1].m_isActive = pCVar18[1].m_isActive & 0x7f;
    pCVar18[1].object.m_particleId = sVar17;
    pCVar18[2].m_isActive = pCVar18[2].m_isActive & 0x7f;
    pCVar18[2].object.m_particleId = sVar16;
    pCVar18[3].m_isActive = pCVar18[3].m_isActive & 0x7f;
    pCVar18[3].object.m_particleId = sVar14;
    pCVar18[4].m_isActive = pCVar18[4].m_isActive & 0x7f;
    pCVar18[4].object.m_particleId = sVar12;
    pCVar18[5].m_isActive = pCVar18[5].m_isActive & 0x7f;
    pCVar18[5].object.m_particleId = sVar11;
    pCVar18[6].m_isActive = pCVar18[6].m_isActive & 0x7f;
    pCVar18[6].object.m_particleId = sVar10;
    pCVar18[7].m_isActive = pCVar18[7].m_isActive & 0x7f;
    pCVar18[7].object.m_particleId = sVar2;
    pCVar18 = pCVar18 + 8;
    iVar20 = iVar20 + -1;
  } while (iVar20 != 0);
  pCVar7 = m_gObjQuadArr;
  sVar19 = 0;
  iVar20 = 3;
  do {
    (pCVar7->field0_0x0).m_isActive = (pCVar7->field0_0x0).m_isActive & 0x7f;
    uVar3 = sVar19 + 3;
    (pCVar7->field0_0x0).object.m_particleId = sVar19 + 1U | 0x100;
    uVar4 = sVar19 + 4;
    uVar5 = sVar19 + 5;
    pCVar7[1].field0_0x0.m_isActive = pCVar7[1].field0_0x0.m_isActive & 0x7f;
    uVar15 = sVar19 + 6;
    uVar13 = sVar19 + 7;
    pCVar7[1].field0_0x0.object.m_particleId = sVar19 + 2U | 0x100;
    uVar6 = sVar19 + 8;
    sVar19 = sVar19 + 8;
    pCVar7[2].field0_0x0.m_isActive = pCVar7[2].field0_0x0.m_isActive & 0x7f;
    pCVar7[2].field0_0x0.object.m_particleId = uVar3 | 0x100;
    pCVar7[3].field0_0x0.m_isActive = pCVar7[3].field0_0x0.m_isActive & 0x7f;
    pCVar7[3].field0_0x0.object.m_particleId = uVar4 | 0x100;
    pCVar7[4].field0_0x0.m_isActive = pCVar7[4].field0_0x0.m_isActive & 0x7f;
    pCVar7[4].field0_0x0.object.m_particleId = uVar5 | 0x100;
    pCVar7[5].field0_0x0.m_isActive = pCVar7[5].field0_0x0.m_isActive & 0x7f;
    pCVar7[5].field0_0x0.object.m_particleId = uVar15 | 0x100;
    pCVar7[6].field0_0x0.m_isActive = pCVar7[6].field0_0x0.m_isActive & 0x7f;
    pCVar7[6].field0_0x0.object.m_particleId = uVar13 | 0x100;
    pCVar7[7].field0_0x0.m_isActive = pCVar7[7].field0_0x0.m_isActive & 0x7f;
    pCVar7[7].field0_0x0.object.m_particleId = uVar6 | 0x100;
    pCVar7 = pCVar7 + 8;
    iVar20 = iVar20 + -1;
  } while (iVar20 != 0);
  pCVar8 = m_gObjArr;
  sVar19 = 0;
  iVar20 = 7;
  do {
    (pCVar8->base_object).m_isActive = (pCVar8->base_object).m_isActive & 0x7f;
    uVar3 = sVar19 + 3;
    (pCVar8->base_object).object.m_particleId = sVar19 + 1U | 0x200;
    uVar4 = sVar19 + 4;
    uVar5 = sVar19 + 5;
    pCVar8[1].base_object.m_isActive = pCVar8[1].base_object.m_isActive & 0x7f;
    uVar15 = sVar19 + 6;
    uVar13 = sVar19 + 7;
    pCVar8[1].base_object.object.m_particleId = sVar19 + 2U | 0x200;
    uVar6 = sVar19 + 8;
    sVar19 = sVar19 + 8;
    pCVar8[2].base_object.m_isActive = pCVar8[2].base_object.m_isActive & 0x7f;
    pCVar8[2].base_object.object.m_particleId = uVar3 | 0x200;
    pCVar8[3].base_object.m_isActive = pCVar8[3].base_object.m_isActive & 0x7f;
    pCVar8[3].base_object.object.m_particleId = uVar4 | 0x200;
    pCVar8[4].base_object.m_isActive = pCVar8[4].base_object.m_isActive & 0x7f;
    pCVar8[4].base_object.object.m_particleId = uVar5 | 0x200;
    pCVar8[5].base_object.m_isActive = pCVar8[5].base_object.m_isActive & 0x7f;
    pCVar8[5].base_object.object.m_particleId = uVar15 | 0x200;
    pCVar8[6].base_object.m_isActive = pCVar8[6].base_object.m_isActive & 0x7f;
    pCVar8[6].base_object.object.m_particleId = uVar13 | 0x200;
    pCVar8[7].base_object.m_isActive = pCVar8[7].base_object.m_isActive & 0x7f;
    pCVar8[7].base_object.object.m_particleId = uVar6 | 0x200;
    pCVar8 = pCVar8 + 8;
    iVar20 = iVar20 + -1;
  } while (iVar20 != 0);
  m_objParty[0].gCharaObj.gPrgObj.object.base_object.m_isActive =
       m_objParty[0].gCharaObj.gPrgObj.object.base_object.m_isActive & 0x7f;
  m_objParty[1].gCharaObj.gPrgObj.object.base_object.object.m_0x44._0_1_ =
       m_objParty[1].gCharaObj.gPrgObj.object.base_object.object.m_0x44._0_1_ & 0x7f;
  m_objParty[2].gCharaObj.gPrgObj.object.base_object.object.m_0x3C._0_1_ =
       m_objParty[2].gCharaObj.gPrgObj.object.base_object.object.m_0x3C._0_1_ & 0x7f;
  m_objParty[3].gCharaObj.gPrgObj.object.base_object.object.m_scriptPriority._0_1_ =
       m_objParty[3].gCharaObj.gPrgObj.object.base_object.object.m_scriptPriority._0_1_ & 0x7f;
  iVar20 = -0x7fd35720;
  sVar19 = 0;
  m_objParty[0].gCharaObj.gPrgObj.object.base_object.object.m_particleId = 0x301;
  m_objParty[1].gCharaObj.gPrgObj.object.base_object.object.m_waitCounter._0_2_ = 0x302;
  m_objParty[2].gCharaObj.gPrgObj.object.base_object.object.m_previous._0_2_ = 0x303;
  m_objParty[3].gCharaObj.gPrgObj.object.base_object.object.m_engineObject._0_2_ = 0x304;
  iVar21 = 8;
  do {
    *(byte *)(iVar20 + 0x4c) = *(byte *)(iVar20 + 0x4c) & 0x7f;
    uVar3 = sVar19 + 3;
    *(ushort *)(iVar20 + 0x30) = sVar19 + 1U | 0x400;
    uVar4 = sVar19 + 4;
    uVar5 = sVar19 + 5;
    *(byte *)(iVar20 + 0x78c) = *(byte *)(iVar20 + 0x78c) & 0x7f;
    uVar15 = sVar19 + 6;
    uVar13 = sVar19 + 7;
    *(ushort *)(iVar20 + 0x770) = sVar19 + 2U | 0x400;
    uVar6 = sVar19 + 8;
    sVar19 = sVar19 + 8;
    *(byte *)(iVar20 + 0xecc) = *(byte *)(iVar20 + 0xecc) & 0x7f;
    *(ushort *)(iVar20 + 0xeb0) = uVar3 | 0x400;
    *(byte *)(iVar20 + 0x160c) = *(byte *)(iVar20 + 0x160c) & 0x7f;
    *(ushort *)(iVar20 + 0x15f0) = uVar4 | 0x400;
    *(byte *)(iVar20 + 0x1d4c) = *(byte *)(iVar20 + 0x1d4c) & 0x7f;
    *(ushort *)(iVar20 + 0x1d30) = uVar5 | 0x400;
    *(byte *)(iVar20 + 0x248c) = *(byte *)(iVar20 + 0x248c) & 0x7f;
    *(ushort *)(iVar20 + 0x2470) = uVar15 | 0x400;
    *(byte *)(iVar20 + 0x2bcc) = *(byte *)(iVar20 + 0x2bcc) & 0x7f;
    *(ushort *)(iVar20 + 0x2bb0) = uVar13 | 0x400;
    *(byte *)(iVar20 + 0x330c) = *(byte *)(iVar20 + 0x330c) & 0x7f;
    *(ushort *)(iVar20 + 0x32f0) = uVar6 | 0x400;
    iVar20 = iVar20 + 0x3a00;
    iVar21 = iVar21 + -1;
  } while (iVar21 != 0);
  pCVar9 = m_objItem;
  sVar19 = 0;
  iVar20 = 4;
  do {
    (pCVar9->prgObj).object.base_object.m_isActive =
         (pCVar9->prgObj).object.base_object.m_isActive & 0x7f;
    uVar3 = sVar19 + 3;
    (pCVar9->prgObj).object.base_object.object.m_particleId = sVar19 + 1U | 0x500;
    uVar4 = sVar19 + 4;
    uVar5 = sVar19 + 5;
    pCVar9[1].prgObj.object.base_object.m_isActive =
         pCVar9[1].prgObj.object.base_object.m_isActive & 0x7f;
    uVar15 = sVar19 + 6;
    uVar13 = sVar19 + 7;
    pCVar9[1].prgObj.object.base_object.object.m_particleId = sVar19 + 2U | 0x500;
    uVar6 = sVar19 + 8;
    sVar19 = sVar19 + 8;
    pCVar9[2].prgObj.object.base_object.m_isActive =
         pCVar9[2].prgObj.object.base_object.m_isActive & 0x7f;
    pCVar9[2].prgObj.object.base_object.object.m_particleId = uVar3 | 0x500;
    pCVar9[3].prgObj.object.base_object.m_isActive =
         pCVar9[3].prgObj.object.base_object.m_isActive & 0x7f;
    pCVar9[3].prgObj.object.base_object.object.m_particleId = uVar4 | 0x500;
    pCVar9[4].prgObj.object.base_object.m_isActive =
         pCVar9[4].prgObj.object.base_object.m_isActive & 0x7f;
    pCVar9[4].prgObj.object.base_object.object.m_particleId = uVar5 | 0x500;
    pCVar9[5].prgObj.object.base_object.m_isActive =
         pCVar9[5].prgObj.object.base_object.m_isActive & 0x7f;
    pCVar9[5].prgObj.object.base_object.object.m_particleId = uVar15 | 0x500;
    pCVar9[6].prgObj.object.base_object.m_isActive =
         pCVar9[6].prgObj.object.base_object.m_isActive & 0x7f;
    pCVar9[6].prgObj.object.base_object.object.m_particleId = uVar13 | 0x500;
    pCVar9[7].prgObj.object.base_object.m_isActive =
         pCVar9[7].prgObj.object.base_object.m_isActive & 0x7f;
    pCVar9[7].prgObj.object.base_object.object.m_particleId = uVar6 | 0x500;
    pCVar9 = pCVar9 + 8;
    iVar20 = iVar20 + -1;
  } while (iVar20 != 0);
  return flatRuntime2;
}

