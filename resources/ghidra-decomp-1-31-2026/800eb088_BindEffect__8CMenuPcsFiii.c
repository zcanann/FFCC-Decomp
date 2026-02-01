// Function: BindEffect__8CMenuPcsFiii
// Entry: 800eb088
// Size: 336 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint BindEffect__8CMenuPcsFiii(CMenuPcs *menuPcs,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint *puVar2;
  CGBaseObj *gBaseObj;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  CGBaseObj *local_74;
  CGBaseObj *local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_64;
  float local_60;
  undefined local_5c;
  undefined4 local_58;
  undefined local_54;
  undefined local_53;
  undefined local_52;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined2 local_40;
  undefined local_3e;
  undefined local_3d;
  
  local_48 = 0xffffffff;
  local_58 = 0xffffffff;
  local_54 = 0;
  local_53 = 1;
  local_50 = 0;
  local_52 = 0;
  local_4c = 0x1e;
  local_44 = 0;
  local_40 = 0;
  local_3e = 0;
  local_3d = 0;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = (CGBaseObj *)0x0;
  local_70 = (CGBaseObj *)0x0;
  local_6c = 0;
  local_68 = 0;
  local_64 = FLOAT_803313e8;
  local_60 = FLOAT_803313e8;
  local_5c = 0;
  if ((int)param_4 < 0) {
    param_4 = param_2;
  }
  puVar2 = (uint *)(*(int *)&menuPcs->field_0x840 + param_2 * 0x524);
  if ((param_2 == 5) && ((int)param_3 < 0x13)) {
    puVar2 = puVar2 + 0x149;
  }
  else if ((0x10 < (int)param_2) && (((int)param_2 < 0x15 && (0x19 < (int)param_3)))) {
    puVar2 = puVar2 + 0x524;
  }
  *puVar2 = param_3;
  gBaseObj = (CGBaseObj *)(puVar2 + 3);
  puVar2[2] = param_2;
  Create__9CGBaseObjFv(gBaseObj);
  puVar2[0x41] = *(uint *)((int)(&menuPcs->m_cameraMatrix + 1) + param_4 * 4);
  local_74 = gBaseObj;
  local_70 = gBaseObj;
  uVar1 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
                    (&PartMng,((int)(param_3 ^ 100) >> 1) - ((param_3 ^ 100) & param_3) >> 0x1f,
                     param_3,&local_88,1);
  puVar2[1] = uVar1;
  return puVar2[1];
}

