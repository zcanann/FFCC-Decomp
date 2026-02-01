// Function: SetUSBData__18CMaterialEditorPcsFv
// Entry: 8004ca08
// Size: 4784 bytes

void SetUSBData__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  undefined uVar1;
  float fVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  undefined4 *puVar6;
  CStage *pCVar7;
  uint uVar8;
  undefined *dstBuffer;
  int *piVar9;
  undefined2 *dstBuffer_00;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  uint32_t *puVar13;
  uint32_t uVar14;
  undefined4 uVar15;
  undefined *puVar16;
  int iVar17;
  int iVar18;
  undefined local_220;
  undefined uStack_21f;
  undefined local_21e;
  undefined uStack_21d;
  undefined local_21c;
  undefined uStack_21b;
  undefined local_21a;
  undefined uStack_219;
  undefined local_218;
  undefined uStack_217;
  undefined local_216;
  undefined uStack_215;
  undefined local_214;
  undefined uStack_213;
  undefined local_212;
  undefined uStack_211;
  undefined local_210;
  undefined uStack_20f;
  undefined local_20e;
  undefined uStack_20d;
  undefined local_20c;
  undefined uStack_20b;
  undefined local_20a;
  undefined uStack_209;
  undefined local_208;
  undefined uStack_207;
  undefined local_206;
  undefined uStack_205;
  undefined local_204;
  undefined uStack_203;
  undefined local_202;
  undefined uStack_201;
  undefined local_200;
  undefined uStack_1ff;
  undefined local_1fe;
  undefined uStack_1fd;
  undefined local_1fc;
  undefined uStack_1fb;
  undefined local_1fa;
  undefined uStack_1f9;
  undefined local_1f8;
  undefined uStack_1f7;
  undefined local_1f6;
  undefined uStack_1f5;
  undefined local_1f4;
  undefined uStack_1f3;
  undefined local_1f2;
  undefined uStack_1f1;
  undefined local_1f0;
  undefined uStack_1ef;
  undefined local_1ee;
  undefined uStack_1ed;
  undefined local_1ec;
  undefined uStack_1eb;
  undefined local_1ea;
  undefined uStack_1e9;
  undefined auStack_ac [4];
  float local_a8;
  float local_a4;
  undefined auStack_a0 [4];
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  longlong local_70;
  undefined4 local_68;
  uint uStack_64;
  longlong local_60;
  undefined4 local_58;
  uint uStack_54;
  
  switch((materialEditorPcs->m_usbStream).m_packetCode) {
  case 1:
    memcpy(&materialEditorPcs->field_0xec,(materialEditorPcs->m_usbStream).m_data,0x120);
    uVar8 = *(uint *)&materialEditorPcs->field_0xec;
    *(uint *)&materialEditorPcs->field_0xec =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0xf0;
    *(uint *)&materialEditorPcs->field_0xf0 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0xf4;
    *(uint *)&materialEditorPcs->field_0xf4 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0xf8;
    *(uint *)&materialEditorPcs->field_0xf8 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0xfc;
    *(uint *)&materialEditorPcs->field_0xfc =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x100;
    *(uint *)&materialEditorPcs->field_0x100 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x104;
    *(uint *)&materialEditorPcs->field_0x104 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x108;
    *(uint *)&materialEditorPcs->field_0x108 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x10c;
    *(uint *)&materialEditorPcs->field_0x10c =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x110;
    *(uint *)&materialEditorPcs->field_0x110 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x114;
    *(uint *)&materialEditorPcs->field_0x114 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x118;
    *(uint *)&materialEditorPcs->field_0x118 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x11c;
    *(uint *)&materialEditorPcs->field_0x11c =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x120;
    *(uint *)&materialEditorPcs->field_0x120 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x124;
    *(uint *)&materialEditorPcs->field_0x124 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x128;
    *(uint *)&materialEditorPcs->field_0x128 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x12c;
    *(uint *)&materialEditorPcs->field_0x12c =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x130;
    *(uint *)&materialEditorPcs->field_0x130 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x134;
    *(uint *)&materialEditorPcs->field_0x134 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x138;
    *(uint *)&materialEditorPcs->field_0x138 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x13c;
    *(uint *)&materialEditorPcs->field_0x13c =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x140;
    *(uint *)&materialEditorPcs->field_0x140 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x144;
    *(uint *)&materialEditorPcs->field_0x144 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x148;
    *(uint *)&materialEditorPcs->field_0x148 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x14c;
    *(uint *)&materialEditorPcs->field_0x14c =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x150;
    *(uint *)&materialEditorPcs->field_0x150 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x154;
    *(uint *)&materialEditorPcs->field_0x154 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    uVar8 = *(uint *)&materialEditorPcs->field_0x158;
    *(uint *)&materialEditorPcs->field_0x158 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    fVar2 = (materialEditorPcs->field268_0x15c).x;
    (materialEditorPcs->field268_0x15c).x =
         (float)((int)fVar2 << 0x18 | ((uint)fVar2 >> 8 & 0xff) << 0x10 |
                 ((uint)fVar2 >> 0x10 & 0xff) << 8 | (uint)fVar2 >> 0x18);
    fVar2 = (materialEditorPcs->field268_0x15c).y;
    (materialEditorPcs->field268_0x15c).y =
         (float)((int)fVar2 << 0x18 | ((uint)fVar2 >> 8 & 0xff) << 0x10 |
                 ((uint)fVar2 >> 0x10 & 0xff) << 8 | (uint)fVar2 >> 0x18);
    fVar2 = (materialEditorPcs->field268_0x15c).z;
    (materialEditorPcs->field268_0x15c).z =
         (float)((int)fVar2 << 0x18 | ((uint)fVar2 >> 8 & 0xff) << 0x10 |
                 ((uint)fVar2 >> 0x10 & 0xff) << 8 | (uint)fVar2 >> 0x18);
    uVar8 = *(uint *)&materialEditorPcs->field_0x168;
    *(uint *)&materialEditorPcs->field_0x168 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    memcpy(&materialEditorPcs->m_unkMatrix,&materialEditorPcs->field_0xec,0x30);
    DCStoreRange(&materialEditorPcs->field_0xec,0x120);
    break;
  case 3:
    (materialEditorPcs->m_usbStream).m_stageDefault = (CStage *)0x1;
    break;
  case 4:
    (materialEditorPcs->m_usbStream).m_stageDefault = (CStage *)0x0;
    break;
  case 0x10:
    puVar6 = (undefined4 *)GetRsdItem__18CMaterialEditorPcsFv(materialEditorPcs);
    puVar13 = (uint32_t *)*puVar6;
    if ((void *)puVar13[4] != (void *)0x0) {
      __dla__FPv((void *)puVar13[4]);
      puVar13[4] = 0;
    }
    *puVar13 = (materialEditorPcs->m_usbStream).m_sizeBytes;
    iVar11 = (materialEditorPcs->m_usbStream).m_sizeBytes * 0xc;
    uVar14 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,iVar11,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0)
    ;
    if (uVar14 == 0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,iVar11);
    }
    puVar13[4] = uVar14;
    memcpy((void *)puVar13[4],(materialEditorPcs->m_usbStream).m_data,
           (materialEditorPcs->m_usbStream).m_sizeBytes * 0xc);
    iVar11 = 0;
    for (uVar8 = 0; uVar10 = (materialEditorPcs->m_usbStream).m_sizeBytes, uVar8 < uVar10;
        uVar8 = uVar8 + 1) {
      uVar10 = *(uint *)(puVar13[4] + iVar11);
      *(uint *)(puVar13[4] + iVar11) =
           uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
           uVar10 >> 0x18;
      uVar10 = *(uint *)(puVar13[4] + iVar11 + 4);
      iVar17 = iVar11 + 8;
      *(float *)(puVar13[4] + iVar11 + 4) =
           -(float)(uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                   uVar10 >> 0x18);
      uVar10 = *(uint *)(puVar13[4] + iVar17);
      iVar11 = iVar11 + 0xc;
      *(float *)(puVar13[4] + iVar17) =
           -(float)(uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                   uVar10 >> 0x18);
    }
    DCStoreRange(puVar13[4],uVar10 * 0xc);
    CreateBoundaryBox__18CMaterialEditorPcsFR3VecR3VeclPC3Vec
              (materialEditorPcs,auStack_a0,auStack_ac,*puVar13,puVar13[4]);
    iVar11 = (int)(local_a8 - local_9c);
    local_70 = (longlong)iVar11;
    local_68 = 0x43300000;
    local_60 = (longlong)(int)(local_a4 - local_98);
    local_58 = 0x43300000;
    uStack_64 = -iVar11 / 2 ^ 0x80000000;
    iVar11 = iVar11 / 0x14 + (iVar11 >> 0x1f);
    local_80 = FLOAT_8032fd00;
    local_90 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8032fd08);
    local_84 = FLOAT_8032fd00;
    local_88 = FLOAT_8032fd00;
    local_74 = FLOAT_8032fd04;
    uStack_54 = -(int)(local_a4 - local_98) * (iVar11 - (iVar11 >> 0x1f)) - 10U ^ 0x80000000;
    local_78 = FLOAT_8032fd04;
    local_7c = FLOAT_8032fd04;
    local_8c = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8032fd08);
    local_94 = FLOAT_8032fd00;
    SetViewerSRT__10CCameraPcsFPC3SRT(&CameraPcs,&local_94);
    break;
  case 0x12:
    piVar9 = (int *)GetRsdItem__18CMaterialEditorPcsFv(materialEditorPcs);
    iVar11 = *piVar9;
    if (*(void **)(iVar11 + 0x14) != (void *)0x0) {
      __dla__FPv(*(void **)(iVar11 + 0x14));
      *(undefined4 *)(iVar11 + 0x14) = 0;
    }
    *(uint32_t *)(iVar11 + 4) = (materialEditorPcs->m_usbStream).m_sizeBytes;
    iVar5 = (materialEditorPcs->m_usbStream).m_sizeBytes * 0xc;
    iVar17 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,iVar5,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0);
    if (iVar17 == 0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,iVar5);
    }
    *(int *)(iVar11 + 0x14) = iVar17;
    memcpy(*(void **)(iVar11 + 0x14),(materialEditorPcs->m_usbStream).m_data,
           (materialEditorPcs->m_usbStream).m_sizeBytes * 0xc);
    iVar17 = 0;
    for (uVar8 = 0; uVar10 = (materialEditorPcs->m_usbStream).m_sizeBytes, uVar8 < uVar10;
        uVar8 = uVar8 + 1) {
      uVar10 = *(uint *)(*(int *)(iVar11 + 0x14) + iVar17);
      *(uint *)(*(int *)(iVar11 + 0x14) + iVar17) =
           uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
           uVar10 >> 0x18;
      uVar10 = *(uint *)(*(int *)(iVar11 + 0x14) + iVar17 + 4);
      iVar5 = iVar17 + 8;
      *(float *)(*(int *)(iVar11 + 0x14) + iVar17 + 4) =
           -(float)(uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                   uVar10 >> 0x18);
      uVar10 = *(uint *)(*(int *)(iVar11 + 0x14) + iVar5);
      iVar17 = iVar17 + 0xc;
      *(float *)(*(int *)(iVar11 + 0x14) + iVar5) =
           -(float)(uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                   uVar10 >> 0x18);
    }
    DCStoreRange(*(undefined4 *)(iVar11 + 0x14),uVar10 * 0xc);
    break;
  case 0x13:
    piVar9 = (int *)GetRsdItem__18CMaterialEditorPcsFv(materialEditorPcs);
    iVar11 = *piVar9;
    if (*(void **)(iVar11 + 0x18) != (void *)0x0) {
      __dla__FPv(*(void **)(iVar11 + 0x18));
      *(undefined4 *)(iVar11 + 0x18) = 0;
    }
    *(uint32_t *)(iVar11 + 8) = (materialEditorPcs->m_usbStream).m_sizeBytes;
    iVar5 = (materialEditorPcs->m_usbStream).m_sizeBytes * 0x70;
    iVar17 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,iVar5,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0);
    if (iVar17 == 0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,iVar5);
    }
    *(int *)(iVar11 + 0x18) = iVar17;
    memset(*(undefined4 *)(iVar11 + 0x18),0,(materialEditorPcs->m_usbStream).m_sizeBytes * 0x70);
    memcpy(*(void **)(iVar11 + 0x18),(materialEditorPcs->m_usbStream).m_data,
           (materialEditorPcs->m_usbStream).m_sizeBytes * 0x70);
    iVar17 = 0;
    for (uVar8 = 0; uVar10 = (materialEditorPcs->m_usbStream).m_sizeBytes, uVar8 < uVar10;
        uVar8 = uVar8 + 1) {
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17);
      uStack_1e9 = (undefined)uVar4;
      local_1ea = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17) = CONCAT11(uStack_1e9,local_1ea);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 2);
      uStack_1eb = (undefined)uVar4;
      local_1ec = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 2) = CONCAT11(uStack_1eb,local_1ec);
      uVar10 = *(uint *)(*(int *)(iVar11 + 0x18) + iVar17 + 4);
      *(uint *)(*(int *)(iVar11 + 0x18) + iVar17 + 4) =
           uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
           uVar10 >> 0x18;
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 8);
      uStack_1ed = (undefined)uVar4;
      local_1ee = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 8) = CONCAT11(uStack_1ed,local_1ee);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 10);
      uStack_1ef = (undefined)uVar4;
      local_1f0 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 10) = CONCAT11(uStack_1ef,local_1f0);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0xc);
      uStack_1f1 = (undefined)uVar4;
      local_1f2 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0xc) = CONCAT11(uStack_1f1,local_1f2);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0xe);
      uStack_1f3 = (undefined)uVar4;
      local_1f4 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0xe) = CONCAT11(uStack_1f3,local_1f4);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x10);
      uStack_1f5 = (undefined)uVar4;
      local_1f6 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x10) = CONCAT11(uStack_1f5,local_1f6);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x12);
      uStack_1f7 = (undefined)uVar4;
      local_1f8 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x12) = CONCAT11(uStack_1f7,local_1f8);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x14);
      uStack_1f9 = (undefined)uVar4;
      local_1fa = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x14) = CONCAT11(uStack_1f9,local_1fa);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x16);
      uStack_1fb = (undefined)uVar4;
      local_1fc = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x16) = CONCAT11(uStack_1fb,local_1fc);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x1c);
      uStack_1fd = (undefined)uVar4;
      local_1fe = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x1c) = CONCAT11(uStack_1fd,local_1fe);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x1e);
      uStack_1ff = (undefined)uVar4;
      local_200 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x1e) = CONCAT11(uStack_1ff,local_200);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x20);
      uStack_201 = (undefined)uVar4;
      local_202 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x20) = CONCAT11(uStack_201,local_202);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x22);
      uStack_203 = (undefined)uVar4;
      local_204 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x22) = CONCAT11(uStack_203,local_204);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x24);
      uStack_205 = (undefined)uVar4;
      local_206 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x24) = CONCAT11(uStack_205,local_206);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x26);
      uStack_207 = (undefined)uVar4;
      local_208 = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x26) = CONCAT11(uStack_207,local_208);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x28);
      uStack_209 = (undefined)uVar4;
      local_20a = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x28) = CONCAT11(uStack_209,local_20a);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x2a);
      uStack_20b = (undefined)uVar4;
      local_20c = (undefined)((ushort)uVar4 >> 8);
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x2a) = CONCAT11(uStack_20b,local_20c);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x2c);
      uStack_20d = (undefined)uVar4;
      local_20e = (undefined)((ushort)uVar4 >> 8);
      iVar5 = iVar17 + 0x2e;
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar17 + 0x2c) = CONCAT11(uStack_20d,local_20e);
      uVar4 = *(undefined2 *)(*(int *)(iVar11 + 0x18) + iVar5);
      uStack_20f = (undefined)uVar4;
      local_210 = (undefined)((ushort)uVar4 >> 8);
      iVar17 = iVar17 + 0x70;
      *(ushort *)(*(int *)(iVar11 + 0x18) + iVar5) = CONCAT11(uStack_20f,local_210);
    }
    DCStoreRange(*(undefined4 *)(iVar11 + 0x18),uVar10 * 0x70);
    break;
  case 0x20:
    uVar14 = (materialEditorPcs->m_usbStream).m_sizeBytes;
    dstBuffer_00 = (undefined2 *)
                   _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                             (&Memory,uVar14,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,
                              0x31,0);
    if (dstBuffer_00 == (undefined2 *)0x0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,uVar14);
    }
    iVar11 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,0x10,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0);
    if (iVar11 == 0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,0x10);
    }
    *(int *)((int)(&materialEditorPcs->m_unkMatrix + 2) +
            (char)materialEditorPcs->field_0x3bc * 4 + 0x10) = iVar11;
    memcpy(dstBuffer_00,(materialEditorPcs->m_usbStream).m_data,
           (materialEditorPcs->m_usbStream).m_sizeBytes);
    uStack_211 = (undefined)*dstBuffer_00;
    local_212 = (undefined)((ushort)*dstBuffer_00 >> 8);
    *dstBuffer_00 = CONCAT11(uStack_211,local_212);
    uStack_213 = (undefined)dstBuffer_00[1];
    local_214 = (undefined)((ushort)dstBuffer_00[1] >> 8);
    dstBuffer_00[1] = CONCAT11(uStack_213,local_214);
    uStack_215 = (undefined)dstBuffer_00[2];
    local_216 = (undefined)((ushort)dstBuffer_00[2] >> 8);
    dstBuffer_00[2] = CONCAT11(uStack_215,local_216);
    uStack_217 = (undefined)dstBuffer_00[3];
    local_218 = (undefined)((ushort)dstBuffer_00[3] >> 8);
    dstBuffer_00[3] = CONCAT11(uStack_217,local_218);
    uStack_219 = (undefined)dstBuffer_00[4];
    local_21a = (undefined)((ushort)dstBuffer_00[4] >> 8);
    dstBuffer_00[4] = CONCAT11(uStack_219,local_21a);
    uStack_21b = (undefined)dstBuffer_00[5];
    local_21c = (undefined)((ushort)dstBuffer_00[5] >> 8);
    dstBuffer_00[5] = CONCAT11(uStack_21b,local_21c);
    uStack_21d = (undefined)dstBuffer_00[6];
    local_21e = (undefined)((ushort)dstBuffer_00[6] >> 8);
    dstBuffer_00[6] = CONCAT11(uStack_21d,local_21e);
    uStack_21f = (undefined)dstBuffer_00[7];
    local_220 = (undefined)((ushort)dstBuffer_00[7] >> 8);
    dstBuffer_00[7] = CONCAT11(uStack_21f,local_220);
    DCFlushRange(dstBuffer_00,0x10);
    memcpy(*(void **)((int)(&materialEditorPcs->m_unkMatrix + 2) +
                     (char)materialEditorPcs->field_0x3bc * 4 + 0x10),dstBuffer_00,0x10);
    sVar3 = dstBuffer_00[1];
    if (sVar3 == 0x20) {
      uVar14 = (materialEditorPcs->m_usbStream).m_sizeBytes;
      iVar11 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                         (&Memory,uVar14 - 0x10,MaterialEditorPcs._4_4_,
                          s_ME_USB_process_cpp_801d7d78,0x31,0);
      if (iVar11 == 0) {
        Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,uVar14 - 0x10);
      }
      *(int *)(&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4) = iVar11;
      memcpy(*(void **)(&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4),
             dstBuffer_00 + 8,(materialEditorPcs->m_usbStream).m_sizeBytes - 0x10);
      DCFlushRange(*(undefined4 *)
                    (&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4),
                   (materialEditorPcs->m_usbStream).m_sizeBytes - 0x10);
    }
    else if ((sVar3 == 4) || (sVar3 == 8)) {
      iVar11 = 0x100;
      if (sVar3 == 4) {
        iVar11 = 0x10;
      }
      iVar17 = iVar11 * 4;
      iVar18 = ((materialEditorPcs->m_usbStream).m_sizeBytes - 0x10) + iVar11 * -4;
      iVar5 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                        (&Memory,iVar18,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0
                        );
      if (iVar5 == 0) {
        Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,iVar18);
      }
      *(int *)(&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4) = iVar5;
      memcpy(*(void **)(&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4),
             dstBuffer_00 + 8,((materialEditorPcs->m_usbStream).m_sizeBytes - 0x10) + iVar11 * -4);
      DCFlushRange(*(undefined4 *)
                    (&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4),
                   ((materialEditorPcs->m_usbStream).m_sizeBytes - 0x10) + iVar11 * -4);
      iVar11 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                         (&Memory,iVar17,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,
                          0);
      if (iVar11 == 0) {
        Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,iVar17);
      }
      *(int *)(&materialEditorPcs->field_0x2fc + (char)materialEditorPcs->field_0x3bc * 4) = iVar11;
      if (dstBuffer_00[1] == 4) {
        iVar11 = ((int)(short)dstBuffer_00[2] * (int)(short)dstBuffer_00[3]) / 2;
      }
      else {
        iVar11 = (int)(short)dstBuffer_00[2] * (int)(short)dstBuffer_00[3];
      }
      memcpy(*(void **)(&materialEditorPcs->field_0x2fc + (char)materialEditorPcs->field_0x3bc * 4),
             (int)dstBuffer_00 + iVar11 + 0x10,iVar17);
      DCFlushRange(*(undefined4 *)
                    (&materialEditorPcs->field_0x2fc + (char)materialEditorPcs->field_0x3bc * 4),
                   iVar17);
    }
    iVar11 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,0x20,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0);
    if (iVar11 == 0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,0x20);
    }
    *(int *)((int)(&materialEditorPcs->m_unkMatrix + 1) + (char)materialEditorPcs->field_0x3bc * 4)
         = iVar11;
    iVar11 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,0xc,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0);
    if (iVar11 == 0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,0xc);
    }
    *(int *)(&materialEditorPcs->field_0x33c + (char)materialEditorPcs->field_0x3bc * 4) = iVar11;
    iVar11 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                       (&Memory,0xc,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31,0);
    if (iVar11 == 0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,0xc);
    }
    uVar15 = 1;
    *(int *)(&materialEditorPcs->field_0x37c + (char)materialEditorPcs->field_0x3bc * 4) = iVar11;
    uVar10 = (uint)(short)dstBuffer_00[3];
    for (uVar8 = (uint)(short)dstBuffer_00[2]; (uVar8 & 1) == 0; uVar8 = uVar8 >> 1) {
    }
    for (; (uVar10 & 1) == 0; uVar10 = uVar10 >> 1) {
    }
    if ((uVar10 != 1) || (uVar10 != 1)) {
      uVar15 = 0;
    }
    sVar3 = dstBuffer_00[1];
    if (sVar3 == 0x20) {
      GXInitTexObj(*(undefined4 *)
                    ((int)(&materialEditorPcs->m_unkMatrix + 1) +
                    (char)materialEditorPcs->field_0x3bc * 4),
                   *(undefined4 *)
                    (&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4),
                   dstBuffer_00[2],dstBuffer_00[3],6,uVar15,uVar15,0);
    }
    else if ((sVar3 == 4) || (sVar3 == 8)) {
      iVar11 = 0x100;
      if (sVar3 == 4) {
        iVar11 = 0x10;
      }
      GXInitTlutObj(*(undefined4 *)
                     (&materialEditorPcs->field_0x33c + (char)materialEditorPcs->field_0x3bc * 4),
                    *(undefined4 *)
                     (&materialEditorPcs->field_0x2fc + (char)materialEditorPcs->field_0x3bc * 4),0,
                    iVar11);
      GXInitTlutObj(*(undefined4 *)
                     (&materialEditorPcs->field_0x37c + (char)materialEditorPcs->field_0x3bc * 4),
                    *(int *)(&materialEditorPcs->field_0x2fc +
                            (char)materialEditorPcs->field_0x3bc * 4) + iVar11 * 2,0,iVar11);
      GXLoadTlut(*(undefined4 *)
                  (&materialEditorPcs->field_0x33c + (char)materialEditorPcs->field_0x3bc * 4),0);
      GXLoadTlut(*(undefined4 *)
                  (&materialEditorPcs->field_0x37c + (char)materialEditorPcs->field_0x3bc * 4),1);
      uVar12 = 9;
      if (dstBuffer_00[1] == 4) {
        uVar12 = 8;
      }
      GXInitTexObjCI(*(undefined4 *)
                      ((int)(&materialEditorPcs->m_unkMatrix + 1) +
                      (char)materialEditorPcs->field_0x3bc * 4),
                     *(undefined4 *)
                      (&materialEditorPcs->field_0x2bc + (char)materialEditorPcs->field_0x3bc * 4),
                     dstBuffer_00[2],dstBuffer_00[3],uVar12,uVar15,uVar15,0,0);
    }
    if (dstBuffer_00 != (undefined2 *)0x0) {
      __dla__FPv(dstBuffer_00);
    }
    materialEditorPcs->field_0x3bc = materialEditorPcs->field_0x3bc + '\x01';
    break;
  case 0x21:
    *(undefined4 *)&materialEditorPcs->field_0xe8 = 1;
    ClearTextureData__18CMaterialEditorPcsFv(materialEditorPcs);
    break;
  case 0x22:
    *(undefined4 *)&materialEditorPcs->field_0xe8 = 0;
    break;
  case 0x31:
    uVar14 = (materialEditorPcs->m_usbStream).m_sizeBytes;
    dstBuffer = (undefined *)
                _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                          (&Memory,uVar14,MaterialEditorPcs._4_4_,s_ME_USB_process_cpp_801d7d78,0x31
                           ,0);
    if (dstBuffer == (undefined *)0x0) {
      Printf__7CSystemFPce(&System,s_MemAlloc_Error____size__d_801d7d8c,uVar14);
    }
    piVar9 = (int *)GetRsdItem__18CMaterialEditorPcsFv(materialEditorPcs);
    iVar17 = *piVar9;
    memcpy(dstBuffer,(materialEditorPcs->m_usbStream).m_data,
           (materialEditorPcs->m_usbStream).m_sizeBytes);
    iVar11 = 0;
    puVar16 = dstBuffer;
    for (uVar8 = 0; uVar8 < (materialEditorPcs->m_usbStream).m_sizeBytes; uVar8 = uVar8 + 1) {
      uVar1 = *puVar16;
      iVar5 = iVar11 + 0x1a;
      iVar11 = iVar11 + 0x70;
      puVar16 = puVar16 + 1;
      *(undefined *)(*(int *)(iVar17 + 0x18) + iVar5) = uVar1;
    }
    if (dstBuffer != (undefined *)0x0) {
      __dla__FPv(dstBuffer);
    }
    break;
  case 0x40:
    ResetRsdList__18CMaterialEditorPcsFP5ZLIST(materialEditorPcs,&materialEditorPcs->zlistA);
    break;
  case 0x41:
    AddRsdList__18CMaterialEditorPcsFP5ZLIST(materialEditorPcs,&materialEditorPcs->zlistA);
    break;
  case 0x42:
    memcpy(&(materialEditorPcs->m_usbStream).m_stageLoad,(materialEditorPcs->m_usbStream).m_data,4);
    pCVar7 = (materialEditorPcs->m_usbStream).m_stageLoad;
    (materialEditorPcs->m_usbStream).m_stageLoad =
         (CStage *)
         ((int)pCVar7 << 0x18 | ((uint)pCVar7 >> 8 & 0xff) << 0x10 |
          ((uint)pCVar7 >> 0x10 & 0xff) << 8 | (uint)pCVar7 >> 0x18);
    DCStoreRange(&(materialEditorPcs->m_usbStream).m_stageLoad,4);
    SetRsdIndex__18CMaterialEditorPcsFv(materialEditorPcs);
    break;
  case 0x43:
    memcpy(&materialEditorPcs->field_0xc0,(materialEditorPcs->m_usbStream).m_data,4);
    uVar8 = *(uint *)&materialEditorPcs->field_0xc0;
    *(uint *)&materialEditorPcs->field_0xc0 =
         uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
    SetRsdFlag__18CMaterialEditorPcsFv(materialEditorPcs);
    DCStoreRange(&materialEditorPcs->field_0xc0,4);
  }
  return;
}

