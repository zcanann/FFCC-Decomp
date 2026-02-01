// Function: BindMcObj__8CMenuPcsFv
// Entry: 800e9c8c
// Size: 896 bytes

/* WARNING: Removing unreachable block (ram,0x800e9ff0) */
/* WARNING: Removing unreachable block (ram,0x800e9c9c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void BindMcObj__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint32_t *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  CGBaseObj *pCVar7;
  uint *puVar8;
  double dVar9;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  CGBaseObj *local_104;
  CGBaseObj *local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  float local_f4;
  float local_f0;
  undefined local_ec;
  undefined4 local_e8;
  undefined local_e4;
  undefined local_e3;
  undefined local_e2;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined2 local_d0;
  undefined local_ce;
  undefined local_cd;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  CGBaseObj *local_98;
  CGBaseObj *local_94;
  undefined4 local_90;
  undefined4 local_8c;
  float local_88;
  float local_84;
  undefined local_80;
  undefined4 local_7c;
  undefined local_78;
  undefined local_77;
  undefined local_76;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined2 local_64;
  undefined local_62;
  undefined local_61;
  
  iVar3 = 0;
  do {
    puVar4 = (undefined4 *)(*(int *)&menuPcs->field_0x840 + (iVar3 + 0x11) * 0x524);
    if (-1 < (int)puVar4[1]) {
      pppDeletePart__8CPartMngFi(&PartMng,puVar4[1]);
      puVar4[1] = 0xffffffff;
      puVar4[2] = 0xffffffff;
      *puVar4 = 0xffffffff;
    }
    if (-1 < (int)puVar4[0x525]) {
      pppDeletePart__8CPartMngFi(&PartMng,puVar4[0x525]);
      puVar4[0x525] = 0xffffffff;
      puVar4[0x526] = 0xffffffff;
      puVar4[0x524] = 0xffffffff;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  iVar3 = 0;
  dVar9 = (double)FLOAT_803313e8;
  iVar6 = 0;
  do {
    puVar1 = menuPcs->m_unk0x838;
    iVar5 = *(int *)((int)puVar1 + iVar6 + 0xc);
    if (iVar5 != 0) {
      local_6c = 0xffffffff;
      local_7c = 0xffffffff;
      local_78 = 0;
      local_77 = 1;
      local_74 = 0;
      local_76 = 0;
      local_70 = 0x1e;
      local_68 = 0;
      local_64 = 0;
      local_62 = 0;
      local_61 = 0;
      local_ac = 0;
      local_a8 = 0;
      local_a4 = 0;
      local_a0 = 0;
      local_9c = 0;
      local_98 = (CGBaseObj *)0x0;
      local_94 = (CGBaseObj *)0x0;
      local_90 = 0;
      local_8c = 0;
      local_88 = FLOAT_803313e8;
      local_84 = FLOAT_803313e8;
      local_80 = 0;
      puVar8 = (uint *)(*(int *)&menuPcs->field_0x840 + (iVar3 + 0x11) * 0x524);
      if ((iVar3 + 0x11 == 5) && (iVar5 + 0x16 < 0x13)) {
        puVar8 = puVar8 + 0x149;
      }
      else if ((0x10 < iVar3 + 0x11) && ((iVar3 + 0x11 < 0x15 && (0x19 < iVar5 + 0x16)))) {
        puVar8 = puVar8 + 0x524;
      }
      uVar2 = iVar5 + 0x16;
      *puVar8 = uVar2;
      pCVar7 = (CGBaseObj *)(puVar8 + 3);
      puVar8[2] = iVar3 + 0x11;
      Create__9CGBaseObjFv(pCVar7);
      puVar8[0x41] = *(uint *)((int)(&menuPcs->m_cameraMatrix + 2) + iVar3 * 4 + 0x14);
      local_98 = pCVar7;
      local_94 = pCVar7;
      uVar2 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
                        (&PartMng,((int)(uVar2 ^ 100) >> 1) - ((uVar2 ^ 100) & uVar2) >> 0x1f,
                         iVar5 + 0x16,&local_ac,1);
      puVar8[1] = uVar2;
    }
    uVar2 = *(uint *)((int)puVar1 + iVar6 + 0x28);
    if ((uVar2 & 1) == 0) {
      if ((uVar2 & 2) == 0) {
        if ((uVar2 & 4) == 0) {
          if ((uVar2 & 8) == 0) {
            if ((uVar2 & 0x10) != 0) {
              iVar5 = 4;
            }
          }
          else {
            iVar5 = 3;
          }
        }
        else {
          iVar5 = 2;
        }
      }
      else {
        iVar5 = 1;
      }
    }
    else {
      iVar5 = 0;
    }
    local_d8 = 0xffffffff;
    local_e8 = 0xffffffff;
    local_e4 = 0;
    local_e3 = 1;
    local_e0 = 0;
    local_e2 = 0;
    local_dc = 0x1e;
    local_d4 = 0;
    local_d0 = 0;
    local_ce = 0;
    local_cd = 0;
    local_118 = 0;
    local_114 = 0;
    local_110 = 0;
    local_10c = 0;
    local_108 = 0;
    local_104 = (CGBaseObj *)0x0;
    local_100 = (CGBaseObj *)0x0;
    local_fc = 0;
    local_f8 = 0;
    local_f4 = (float)dVar9;
    local_f0 = (float)dVar9;
    local_ec = 0;
    puVar8 = (uint *)(*(int *)&menuPcs->field_0x840 + (iVar3 + 0x11) * 0x524);
    if ((iVar3 + 0x11 == 5) && (iVar5 + 0x1a < 0x13)) {
      puVar8 = puVar8 + 0x149;
    }
    else if ((0x10 < iVar3 + 0x11) && ((iVar3 + 0x11 < 0x15 && (0x19 < iVar5 + 0x1a)))) {
      puVar8 = puVar8 + 0x524;
    }
    uVar2 = iVar5 + 0x1a;
    *puVar8 = uVar2;
    pCVar7 = (CGBaseObj *)(puVar8 + 3);
    puVar8[2] = iVar3 + 0x11;
    Create__9CGBaseObjFv(pCVar7);
    puVar8[0x41] = *(uint *)((int)(&menuPcs->m_cameraMatrix + 2) + iVar3 * 4 + 0x14);
    local_104 = pCVar7;
    local_100 = pCVar7;
    uVar2 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
                      (&PartMng,((int)(uVar2 ^ 100) >> 1) - ((uVar2 ^ 100) & uVar2) >> 0x1f,
                       iVar5 + 0x1a,&local_118,1);
    iVar3 = iVar3 + 1;
    puVar8[1] = uVar2;
    iVar6 = iVar6 + 0x48;
  } while (iVar3 < 4);
  return;
}

