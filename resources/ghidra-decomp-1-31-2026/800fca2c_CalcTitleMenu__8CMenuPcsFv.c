// Function: CalcTitleMenu__8CMenuPcsFv
// Entry: 800fca2c
// Size: 1416 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcTitleMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar4;
  undefined4 uVar3;
  int iVar5;
  CGBaseObj *pCVar6;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  CGBaseObj *local_e8;
  CGBaseObj *local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  float local_d8;
  float local_d4;
  undefined local_d0;
  undefined4 local_cc;
  undefined local_c8;
  undefined local_c7;
  undefined local_c6;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined2 local_b4;
  undefined local_b2;
  undefined local_b1;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  CGBaseObj *local_7c;
  CGBaseObj *local_78;
  undefined4 local_74;
  undefined4 local_70;
  float local_6c;
  float local_68;
  undefined local_64;
  undefined4 local_60;
  undefined local_5c;
  undefined local_5b;
  undefined local_5a;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined2 local_48;
  undefined local_46;
  undefined local_45;
  
  if (DAT_8032ee38 == '\0') {
    DAT_8032ee38 = '\x01';
    DAT_8032ee34 = s_dvd_movie_ffcc_op_thp_801dc448;
  }
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar2 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar2 = Pad._8_2_;
  }
  uVar4 = GetButtonRepeat__8CMenuPcsFi(menuPcs,0);
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 8) == '\0') {
    if (DAT_8032ee1c == '\x01') {
      local_50 = 0xffffffff;
      local_60 = 0xffffffff;
      local_5c = 0;
      local_5b = 1;
      local_58 = 0;
      local_5a = 0;
      local_54 = 0x1e;
      local_4c = 0;
      local_48 = 0;
      local_46 = 0;
      local_45 = 0;
      local_90 = 0;
      local_8c = 0;
      local_88 = 0;
      local_84 = 0;
      local_80 = 0;
      local_7c = (CGBaseObj *)0x0;
      local_78 = (CGBaseObj *)0x0;
      local_74 = 0;
      local_70 = 0;
      local_6c = FLOAT_803313e8;
      local_68 = FLOAT_803313e8;
      local_64 = 0;
      iVar5 = *(int *)&menuPcs->field_0x840;
      *(undefined4 *)(iVar5 + 0x763c) = 0x1f;
      pCVar6 = (CGBaseObj *)(iVar5 + 0x7648);
      *(undefined4 *)(iVar5 + 0x7644) = 0x17;
      Create__9CGBaseObjFv(pCVar6);
      *(undefined4 *)(iVar5 + 0x7740) = *(undefined4 *)&menuPcs->field_0x7d0;
      local_7c = pCVar6;
      local_78 = pCVar6;
      uVar3 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(&PartMng,0,0x1f,&local_90,1);
      *(undefined4 *)(iVar5 + 0x7640) = uVar3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
      menuPcs->field_0x858 = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0xffff;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
      local_108 = 9;
      local_104 = 0;
      local_100 = 0;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,0,1,4,3,&local_108,(CStack *)0x0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
      DAT_8032ee1c = 0;
      return;
    }
    DAT_8032e8ac = 0;
    THPSimpleInit(1);
    THPSimpleOpen(DAT_8032ee34);
    uVar3 = THPSimpleCalcNeedMemory();
    uVar3 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                      (&Memory,uVar3,CharaPcs._212_4_,s_wm_menu_cpp_801dc418,0xaba,0);
    *(undefined4 *)&menuPcs->field_0x854 = uVar3;
    THPSimpleSetBuffer(*(undefined4 *)&menuPcs->field_0x854);
    THPSimplePreLoad(0);
    THPSimpleAudioStart();
    local_bc = 0xffffffff;
    local_cc = 0xffffffff;
    local_c8 = 0;
    local_c7 = 1;
    local_c4 = 0;
    local_c6 = 0;
    local_c0 = 0x1e;
    local_b8 = 0;
    local_b4 = 0;
    local_b2 = 0;
    local_b1 = 0;
    local_fc = 0;
    local_f8 = 0;
    local_f4 = 0;
    local_f0 = 0;
    local_ec = 0;
    local_e8 = (CGBaseObj *)0x0;
    local_e4 = (CGBaseObj *)0x0;
    local_e0 = 0;
    local_dc = 0;
    local_d8 = FLOAT_803313e8;
    local_d4 = FLOAT_803313e8;
    local_d0 = 0;
    iVar5 = *(int *)&menuPcs->field_0x840;
    *(undefined4 *)(iVar5 + 0x763c) = 0x1f;
    pCVar6 = (CGBaseObj *)(iVar5 + 0x7648);
    *(undefined4 *)(iVar5 + 0x7644) = 0x17;
    Create__9CGBaseObjFv(pCVar6);
    *(undefined4 *)(iVar5 + 0x7740) = *(undefined4 *)&menuPcs->field_0x7d0;
    local_e8 = pCVar6;
    local_e4 = pCVar6;
    uVar3 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(&PartMng,0,0x1f,&local_fc,1);
    *(undefined4 *)(iVar5 + 0x7640) = uVar3;
    menuPcs->field_0x858 = 1;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
  }
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0) {
    if ((uVar2 & 0x1000) == 0) {
      iVar5 = THPSimpleDecode(0);
      if (iVar5 == 0) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
      }
    }
    else {
      THPSimpleAudioStop();
      THPSimpleLoadStop();
      THPSimpleClose();
      THPSimpleQuit();
      if (*(int *)&menuPcs->field_0x854 != 0) {
        Free__7CMemoryFPv(&Memory);
        *(undefined4 *)&menuPcs->field_0x854 = 0;
      }
      menuPcs->field_0x858 = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0xffff;
    }
  }
  iVar5 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar5 + 0x10) == 2) {
    if (*(short *)(iVar5 + 0x18) == 0) {
      if ((uVar4 & 0xc) == 0) {
        if ((uVar2 & 0x100) == 0) {
          if ((uVar2 & 0x200) != 0) {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
        }
        else {
          if (*(short *)(iVar5 + 0x26) == 0) {
            DAT_8032ee2c = 0xffffffff;
            DAT_8032ee28 = 0xffffffff;
            DAT_8032ee20 = 0xff;
            uRam8032ee21 = 0xff;
            InitNewGame__5CGameFv(0x8021eec0);
          }
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0x14;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
          PlaySe__6CSoundFiiii(&Sound,0xb,0x40,0x7f,0);
        }
      }
      else {
        *(ushort *)(iVar5 + 0x26) = *(ushort *)(iVar5 + 0x26) ^ 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x24) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 0;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if (uVar4 == 0) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
      }
      else {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      }
    }
  }
  else if (*(short *)(iVar5 + 0x10) < 2) {
    iVar5 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,0);
    if (iVar5 == 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 1;
    }
    else {
      iVar5 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,1);
      if (iVar5 == 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 1;
      }
      else {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
      }
    }
  }
  return;
}

