// Function: SetUSBData__14CFunnyShapePcsFv
// Entry: 8004eb4c
// Size: 3524 bytes

void SetUSBData__14CFunnyShapePcsFv(CFunnyShapePcs *funnyShapePcs)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  uint uVar4;
  uint *puVar5;
  undefined4 uVar6;
  void *pvVar7;
  int iVar8;
  ushort *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined local_198;
  undefined uStack_197;
  undefined local_196;
  undefined uStack_195;
  undefined local_194;
  undefined uStack_193;
  undefined local_192;
  undefined uStack_191;
  undefined local_190;
  undefined uStack_18f;
  undefined local_18e;
  undefined uStack_18d;
  undefined local_18c;
  undefined uStack_18b;
  undefined local_18a;
  undefined uStack_189;
  undefined local_188;
  undefined uStack_187;
  undefined local_186;
  undefined uStack_185;
  undefined local_184;
  undefined uStack_183;
  undefined local_182;
  undefined uStack_181;
  undefined local_180;
  undefined uStack_17f;
  undefined local_17e;
  undefined uStack_17d;
  undefined local_17c;
  undefined uStack_17b;
  undefined local_17a;
  undefined uStack_179;
  undefined local_178;
  undefined uStack_177;
  undefined local_176;
  undefined uStack_175;
  undefined local_174;
  undefined uStack_173;
  undefined local_172;
  undefined uStack_171;
  undefined local_170;
  undefined uStack_16f;
  undefined local_16e;
  undefined uStack_16d;
  undefined local_16c;
  undefined uStack_16b;
  undefined local_16a;
  undefined uStack_169;
  undefined local_168;
  undefined uStack_167;
  undefined local_166;
  undefined uStack_165;
  undefined local_164;
  undefined uStack_163;
  undefined local_162;
  undefined uStack_161;
  undefined local_160;
  undefined uStack_15f;
  undefined local_15e;
  undefined uStack_15d;
  undefined local_15c;
  undefined uStack_15b;
  undefined local_15a;
  undefined uStack_159;
  undefined local_158;
  undefined uStack_157;
  undefined local_156;
  undefined uStack_155;
  undefined local_154;
  undefined uStack_153;
  undefined local_152;
  undefined uStack_151;
  undefined local_150;
  undefined uStack_14f;
  undefined local_14e;
  undefined uStack_14d;
  undefined local_14c;
  undefined uStack_14b;
  undefined local_14a;
  undefined uStack_149;
  undefined local_148;
  undefined uStack_147;
  undefined local_146;
  undefined uStack_145;
  undefined local_144;
  undefined uStack_143;
  undefined local_142;
  undefined uStack_141;
  undefined local_140;
  undefined uStack_13f;
  undefined local_13e;
  undefined uStack_13d;
  undefined local_13c;
  undefined uStack_13b;
  undefined local_13a;
  undefined uStack_139;
  undefined local_138;
  undefined uStack_137;
  undefined local_136;
  undefined uStack_135;
  undefined local_134;
  undefined uStack_133;
  undefined local_132;
  undefined uStack_131;
  undefined local_130;
  undefined uStack_12f;
  undefined local_12e;
  undefined uStack_12d;
  undefined local_12c;
  undefined uStack_12b;
  undefined local_12a;
  undefined uStack_129;
  undefined local_128;
  undefined uStack_127;
  undefined local_126;
  undefined uStack_125;
  undefined local_124;
  undefined uStack_123;
  undefined local_122;
  undefined uStack_121;
  undefined local_120;
  undefined uStack_11f;
  undefined local_11e;
  undefined uStack_11d;
  undefined local_11c;
  undefined uStack_11b;
  undefined local_11a;
  undefined uStack_119;
  undefined local_118;
  undefined uStack_117;
  undefined local_116;
  undefined uStack_115;
  undefined local_114;
  undefined uStack_113;
  undefined local_112;
  undefined uStack_111;
  undefined local_110;
  undefined uStack_10f;
  undefined local_10e;
  undefined uStack_10d;
  undefined local_10c;
  undefined uStack_10b;
  undefined local_10a;
  undefined uStack_109;
  undefined local_108;
  undefined uStack_107;
  undefined4 local_8c;
  undefined4 local_88;
  undefined local_84 [4];
  undefined4 local_80;
  undefined2 local_7c;
  undefined4 local_7a;
  undefined2 local_76;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  
  switch((funnyShapePcs->m_usbStreamData).m_packetCode) {
  case 4:
    *(undefined4 *)&funnyShapePcs->field_0x61b8 = 1;
    ClearTextureData__11CFunnyShapeFv
              ((CFunnyShape *)&(funnyShapePcs->m_usbStreamData).m_stageDefault);
    break;
  case 5:
    puVar3 = (undefined2 *)
             __nwa__FUlPQ27CMemory6CStagePci
                       ((funnyShapePcs->m_usbStreamData).m_sizeBytes,FunnyShapePcs._4_4_,
                        s_FS_USB_Process_cpp_801d7e80,0x55);
    uVar2 = __nw__FUlPQ27CMemory6CStagePci
                      (0x30,FunnyShapePcs._4_4_,s_FS_USB_Process_cpp_801d7e80,0x57);
    *(undefined4 *)(&funnyShapePcs->field_0x60a4 + (char)funnyShapePcs->field_0x6124 * 4) = uVar2;
    memcpy(puVar3,(funnyShapePcs->m_usbStreamData).m_data,
           (funnyShapePcs->m_usbStreamData).m_sizeBytes);
    uStack_10b = (undefined)*puVar3;
    local_10c = (undefined)((ushort)*puVar3 >> 8);
    *puVar3 = CONCAT11(uStack_10b,local_10c);
    uStack_10d = (undefined)puVar3[1];
    local_10e = (undefined)((ushort)puVar3[1] >> 8);
    puVar3[1] = CONCAT11(uStack_10d,local_10e);
    uStack_10f = (undefined)puVar3[2];
    local_110 = (undefined)((ushort)puVar3[2] >> 8);
    puVar3[2] = CONCAT11(uStack_10f,local_110);
    uStack_111 = (undefined)puVar3[3];
    local_112 = (undefined)((ushort)puVar3[3] >> 8);
    puVar3[3] = CONCAT11(uStack_111,local_112);
    uStack_113 = (undefined)puVar3[4];
    local_114 = (undefined)((ushort)puVar3[4] >> 8);
    puVar3[4] = CONCAT11(uStack_113,local_114);
    uStack_115 = (undefined)puVar3[5];
    local_116 = (undefined)((ushort)puVar3[5] >> 8);
    puVar3[5] = CONCAT11(uStack_115,local_116);
    uStack_117 = (undefined)puVar3[6];
    local_118 = (undefined)((ushort)puVar3[6] >> 8);
    puVar3[6] = CONCAT11(uStack_117,local_118);
    uStack_119 = (undefined)puVar3[7];
    local_11a = (undefined)((ushort)puVar3[7] >> 8);
    puVar3[7] = CONCAT11(uStack_119,local_11a);
    uStack_11b = (undefined)puVar3[0x10];
    local_11c = (undefined)((ushort)puVar3[0x10] >> 8);
    puVar3[0x10] = CONCAT11(uStack_11b,local_11c);
    uStack_11d = (undefined)puVar3[0x11];
    local_11e = (undefined)((ushort)puVar3[0x11] >> 8);
    puVar3[0x11] = CONCAT11(uStack_11d,local_11e);
    DCFlushRange(puVar3,0x30);
    memcpy(*(void **)(&funnyShapePcs->field_0x60a4 + (char)funnyShapePcs->field_0x6124 * 4),puVar3,
           0x30);
    uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                      ((funnyShapePcs->m_usbStreamData).m_sizeBytes - 0x30,FunnyShapePcs._4_4_,
                       s_FS_USB_Process_cpp_801d7e80,0x6c);
    *(undefined4 *)(&funnyShapePcs->field_0x60e4 + (char)funnyShapePcs->field_0x6124 * 4) = uVar2;
    memcpy(*(void **)(&funnyShapePcs->field_0x60e4 + (char)funnyShapePcs->field_0x6124 * 4),
           puVar3 + 0x18,(funnyShapePcs->m_usbStreamData).m_sizeBytes - 0x30);
    DCFlushRange(*(undefined4 *)
                  (&funnyShapePcs->field_0x60e4 + (char)funnyShapePcs->field_0x6124 * 4),
                 (funnyShapePcs->m_usbStreamData).m_sizeBytes - 0x30);
    uVar2 = __nw__FUlPQ27CMemory6CStagePci
                      (0x20,FunnyShapePcs._4_4_,s_FS_USB_Process_cpp_801d7e80,0x73);
    *(undefined4 *)(&funnyShapePcs->field_0x6064 + (char)funnyShapePcs->field_0x6124 * 4) = uVar2;
    GXInitTexObj(*(undefined4 *)
                  (&funnyShapePcs->field_0x6064 + (char)funnyShapePcs->field_0x6124 * 4),
                 *(undefined4 *)
                  (&funnyShapePcs->field_0x60e4 + (char)funnyShapePcs->field_0x6124 * 4),puVar3[2],
                 puVar3[3],6,0,0,0);
    funnyShapePcs->field_0x6124 = funnyShapePcs->field_0x6124 + '\x01';
    if (puVar3 != (undefined2 *)0x0) {
      __dla__FPv(puVar3);
    }
    break;
  case 6:
    *(undefined4 *)&funnyShapePcs->field_0x61b8 = 0;
    break;
  case 10:
    ClearAnmData__11CFunnyShapeFv((CFunnyShape *)&(funnyShapePcs->m_usbStreamData).m_stageDefault);
    if (*(void **)&funnyShapePcs->field_0x6134 != (void *)0x0) {
      __dla__FPv(*(void **)&funnyShapePcs->field_0x6134);
      *(undefined4 *)&funnyShapePcs->field_0x6134 = 0;
    }
    memset(&(funnyShapePcs->m_usbStreamData).m_stageDefault,0,0x30);
    memcpy(&funnyShapePcs->field_0x6128,(funnyShapePcs->m_usbStreamData).m_data,0x10);
    uVar4 = *(uint *)&funnyShapePcs->field_0x6128;
    *(uint *)&funnyShapePcs->field_0x6128 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uStack_11f = (undefined)*(undefined2 *)&funnyShapePcs->field_0x612c;
    local_120 = (undefined)((ushort)*(undefined2 *)&funnyShapePcs->field_0x612c >> 8);
    *(ushort *)&funnyShapePcs->field_0x612c = CONCAT11(uStack_11f,local_120);
    uStack_121 = (undefined)*(undefined2 *)&funnyShapePcs->field_0x612e;
    local_122 = (undefined)((ushort)*(undefined2 *)&funnyShapePcs->field_0x612e >> 8);
    *(ushort *)&funnyShapePcs->field_0x612e = CONCAT11(uStack_121,local_122);
    uStack_123 = (undefined)*(undefined2 *)&funnyShapePcs->field_0x6130;
    local_124 = (undefined)((ushort)*(undefined2 *)&funnyShapePcs->field_0x6130 >> 8);
    *(ushort *)&funnyShapePcs->field_0x6130 = CONCAT11(uStack_123,local_124);
    uStack_125 = (undefined)*(undefined2 *)&funnyShapePcs->field_0x6132;
    local_126 = (undefined)((ushort)*(undefined2 *)&funnyShapePcs->field_0x6132 >> 8);
    *(ushort *)&funnyShapePcs->field_0x6132 = CONCAT11(uStack_125,local_126);
    *(undefined4 *)&funnyShapePcs->field_0x6134 = 0;
    DCStoreRange(&funnyShapePcs->field_0x6128,(funnyShapePcs->m_usbStreamData).m_sizeBytes);
    break;
  case 0xb:
    uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                      ((funnyShapePcs->m_usbStreamData).m_sizeBytes,FunnyShapePcs._4_4_,
                       s_FS_USB_Process_cpp_801d7e80,0x9c);
    *(undefined4 *)&funnyShapePcs->field_0x6134 = uVar2;
    memcpy(*(void **)&funnyShapePcs->field_0x6134,(funnyShapePcs->m_usbStreamData).m_data,
           (funnyShapePcs->m_usbStreamData).m_sizeBytes);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 2);
    uStack_127 = (undefined)uVar1;
    local_128 = (undefined)((ushort)uVar1 >> 8);
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 2) = CONCAT11(uStack_127,local_128);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 4);
    uStack_129 = (undefined)uVar1;
    local_12a = (undefined)((ushort)uVar1 >> 8);
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 4) = CONCAT11(uStack_129,local_12a);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 6);
    uStack_12b = (undefined)uVar1;
    local_12c = (undefined)((ushort)uVar1 >> 8);
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 6) = CONCAT11(uStack_12b,local_12c);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 8);
    uStack_12d = (undefined)uVar1;
    local_12e = (undefined)((ushort)uVar1 >> 8);
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 8) = CONCAT11(uStack_12d,local_12e);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 10);
    uStack_12f = (undefined)uVar1;
    local_130 = (undefined)((ushort)uVar1 >> 8);
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 10) = CONCAT11(uStack_12f,local_130);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 0xe);
    uStack_131 = (undefined)uVar1;
    local_132 = (undefined)((ushort)uVar1 >> 8);
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 0xe) = CONCAT11(uStack_131,local_132);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 0x10);
    uStack_133 = (undefined)uVar1;
    local_134 = (undefined)((ushort)uVar1 >> 8);
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 0x10) = CONCAT11(uStack_133,local_134);
    uVar1 = *(undefined2 *)(*(int *)&funnyShapePcs->field_0x6134 + 0x12);
    uStack_135 = (undefined)uVar1;
    local_136 = (undefined)((ushort)uVar1 >> 8);
    iVar10 = 0;
    *(ushort *)(*(int *)&funnyShapePcs->field_0x6134 + 0x12) = CONCAT11(uStack_135,local_136);
    for (iVar8 = 0; iVar11 = *(int *)&funnyShapePcs->field_0x6134, iVar8 < *(short *)(iVar11 + 6);
        iVar8 = iVar8 + 1) {
      iVar11 = iVar11 + iVar10;
      if (iVar8 != 0) {
        uStack_137 = (undefined)*(undefined2 *)(iVar11 + 0x10);
        local_138 = (undefined)((ushort)*(undefined2 *)(iVar11 + 0x10) >> 8);
        *(ushort *)(iVar11 + 0x10) = CONCAT11(uStack_137,local_138);
        uStack_139 = (undefined)*(undefined2 *)(iVar11 + 0x12);
        local_13a = (undefined)((ushort)*(undefined2 *)(iVar11 + 0x12) >> 8);
        *(ushort *)(iVar11 + 0x12) = CONCAT11(uStack_139,local_13a);
      }
      puVar9 = (ushort *)(*(int *)&funnyShapePcs->field_0x6134 + (int)*(short *)(iVar11 + 0x10));
      uStack_13b = (undefined)*puVar9;
      local_13c = (undefined)(*puVar9 >> 8);
      *puVar9 = CONCAT11(uStack_13b,local_13c);
      uStack_13d = (undefined)puVar9[1];
      local_13e = (undefined)(puVar9[1] >> 8);
      iVar11 = 0;
      iVar15 = 0;
      puVar9[1] = CONCAT11(uStack_13d,local_13e);
      iVar13 = 0;
      iVar12 = 0;
      for (iVar14 = 0; iVar14 < (short)puVar9[1]; iVar14 = iVar14 + 1) {
        if ((*puVar9 & 8) == 0) {
          puVar5 = (uint *)((int)puVar9 + iVar13 + 0x10);
          uVar4 = *puVar5;
          *puVar5 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                    uVar4 >> 0x18;
          uVar4 = puVar5[1];
          puVar5[1] = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                      uVar4 >> 0x18;
          uStack_157 = (undefined)*(undefined2 *)(puVar5 + 4);
          local_158 = (undefined)((ushort)*(undefined2 *)(puVar5 + 4) >> 8);
          *(ushort *)(puVar5 + 4) = CONCAT11(uStack_157,local_158);
          uStack_159 = (undefined)*(undefined2 *)((int)puVar5 + 0x12);
          local_15a = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x12) >> 8);
          *(ushort *)((int)puVar5 + 0x12) = CONCAT11(uStack_159,local_15a);
          uStack_15b = (undefined)*(undefined2 *)(puVar5 + 5);
          local_15c = (undefined)((ushort)*(undefined2 *)(puVar5 + 5) >> 8);
          *(ushort *)(puVar5 + 5) = CONCAT11(uStack_15b,local_15c);
          uStack_15d = (undefined)*(undefined2 *)((int)puVar5 + 0x16);
          local_15e = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x16) >> 8);
          *(ushort *)((int)puVar5 + 0x16) = CONCAT11(uStack_15d,local_15e);
          uStack_15f = (undefined)*(undefined2 *)(puVar5 + 6);
          local_160 = (undefined)((ushort)*(undefined2 *)(puVar5 + 6) >> 8);
          *(ushort *)(puVar5 + 6) = CONCAT11(uStack_15f,local_160);
          uStack_161 = (undefined)*(undefined2 *)((int)puVar5 + 0x1a);
          local_162 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1a) >> 8);
          *(ushort *)((int)puVar5 + 0x1a) = CONCAT11(uStack_161,local_162);
          uStack_163 = (undefined)*(undefined2 *)(puVar5 + 7);
          local_164 = (undefined)((ushort)*(undefined2 *)(puVar5 + 7) >> 8);
          *(ushort *)(puVar5 + 7) = CONCAT11(uStack_163,local_164);
          uStack_165 = (undefined)*(undefined2 *)((int)puVar5 + 0x1e);
          local_166 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1e) >> 8);
          pvVar7 = (void *)((int)puVar9 + iVar12 + 0x10);
          *(ushort *)((int)puVar5 + 0x1e) = CONCAT11(uStack_165,local_166);
          memcpy(pvVar7,puVar5,0x24);
          DCStoreRange(pvVar7,0x24);
        }
        else {
          puVar5 = (uint *)((int)puVar9 + iVar15 + 0x10);
          uVar4 = *puVar5;
          *puVar5 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                    uVar4 >> 0x18;
          uVar4 = puVar5[1];
          puVar5[1] = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                      uVar4 >> 0x18;
          uStack_13f = (undefined)*(undefined2 *)(puVar5 + 4);
          local_140 = (undefined)((ushort)*(undefined2 *)(puVar5 + 4) >> 8);
          *(ushort *)(puVar5 + 4) = CONCAT11(uStack_13f,local_140);
          uStack_141 = (undefined)*(undefined2 *)((int)puVar5 + 0x12);
          local_142 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x12) >> 8);
          *(ushort *)((int)puVar5 + 0x12) = CONCAT11(uStack_141,local_142);
          uStack_143 = (undefined)*(undefined2 *)(puVar5 + 5);
          local_144 = (undefined)((ushort)*(undefined2 *)(puVar5 + 5) >> 8);
          *(ushort *)(puVar5 + 5) = CONCAT11(uStack_143,local_144);
          uStack_145 = (undefined)*(undefined2 *)((int)puVar5 + 0x16);
          local_146 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x16) >> 8);
          *(ushort *)((int)puVar5 + 0x16) = CONCAT11(uStack_145,local_146);
          uStack_147 = (undefined)*(undefined2 *)(puVar5 + 6);
          local_148 = (undefined)((ushort)*(undefined2 *)(puVar5 + 6) >> 8);
          *(ushort *)(puVar5 + 6) = CONCAT11(uStack_147,local_148);
          uStack_149 = (undefined)*(undefined2 *)((int)puVar5 + 0x1a);
          local_14a = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1a) >> 8);
          *(ushort *)((int)puVar5 + 0x1a) = CONCAT11(uStack_149,local_14a);
          uStack_14b = (undefined)*(undefined2 *)(puVar5 + 7);
          local_14c = (undefined)((ushort)*(undefined2 *)(puVar5 + 7) >> 8);
          *(ushort *)(puVar5 + 7) = CONCAT11(uStack_14b,local_14c);
          uStack_14d = (undefined)*(undefined2 *)((int)puVar5 + 0x1e);
          local_14e = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1e) >> 8);
          *(ushort *)((int)puVar5 + 0x1e) = CONCAT11(uStack_14d,local_14e);
          uStack_14f = (undefined)*(undefined2 *)(puVar5 + 8);
          local_150 = (undefined)((ushort)*(undefined2 *)(puVar5 + 8) >> 8);
          *(ushort *)(puVar5 + 8) = CONCAT11(uStack_14f,local_150);
          uStack_151 = (undefined)*(undefined2 *)((int)puVar5 + 0x22);
          local_152 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x22) >> 8);
          *(ushort *)((int)puVar5 + 0x22) = CONCAT11(uStack_151,local_152);
          uStack_153 = (undefined)*(undefined2 *)(puVar5 + 9);
          local_154 = (undefined)((ushort)*(undefined2 *)(puVar5 + 9) >> 8);
          *(ushort *)(puVar5 + 9) = CONCAT11(uStack_153,local_154);
          uStack_155 = (undefined)*(undefined2 *)((int)puVar5 + 0x26);
          local_156 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x26) >> 8);
          pvVar7 = (void *)((int)puVar9 + iVar11 + 0x10);
          *(ushort *)((int)puVar5 + 0x26) = CONCAT11(uStack_155,local_156);
          memcpy(pvVar7,puVar5,0x2c);
          DCStoreRange(pvVar7,0x2c);
        }
        iVar15 = iVar15 + 0x2c;
        iVar13 = iVar13 + 0x24;
        iVar12 = iVar12 + 0x24;
        iVar11 = iVar11 + 0x2c;
      }
      iVar10 = iVar10 + 8;
    }
    DCStoreRange(iVar11,(funnyShapePcs->m_usbStreamData).m_sizeBytes);
    InitAnmWork__11CFunnyShapeFv((CFunnyShape *)&(funnyShapePcs->m_usbStreamData).m_stageDefault);
    break;
  case 0xc:
    memcpy(&funnyShapePcs->field_0x6178,(funnyShapePcs->m_usbStreamData).m_data,0x40);
    uVar4 = *(uint *)&funnyShapePcs->field_0x6178;
    *(uint *)&funnyShapePcs->field_0x6178 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x6180;
    *(uint *)&funnyShapePcs->field_0x6180 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x6184;
    *(uint *)&funnyShapePcs->field_0x6184 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x6188;
    *(uint *)&funnyShapePcs->field_0x6188 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x618c;
    *(uint *)&funnyShapePcs->field_0x618c =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x6190;
    *(uint *)&funnyShapePcs->field_0x6190 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x6194;
    *(uint *)&funnyShapePcs->field_0x6194 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x6198;
    *(uint *)&funnyShapePcs->field_0x6198 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x619c;
    *(uint *)&funnyShapePcs->field_0x619c =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uStack_107 = (undefined)*(undefined2 *)&funnyShapePcs->field_0x61a0;
    local_108 = (undefined)((ushort)*(undefined2 *)&funnyShapePcs->field_0x61a0 >> 8);
    *(ushort *)&funnyShapePcs->field_0x61a0 = CONCAT11(uStack_107,local_108);
    uStack_109 = (undefined)*(undefined2 *)&funnyShapePcs->field_0x61a2;
    local_10a = (undefined)((ushort)*(undefined2 *)&funnyShapePcs->field_0x61a2 >> 8);
    *(ushort *)&funnyShapePcs->field_0x61a2 = CONCAT11(uStack_109,local_10a);
    uVar4 = *(uint *)&funnyShapePcs->field_0x61a4;
    *(uint *)&funnyShapePcs->field_0x61a4 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    uVar4 = *(uint *)&funnyShapePcs->field_0x61a8;
    *(uint *)&funnyShapePcs->field_0x61a8 =
         uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18;
    DCStoreRange(&funnyShapePcs->field_0x6178,0x40);
    local_8c = *(undefined4 *)&funnyShapePcs->field_0x617c;
    local_88 = local_8c;
    GXSetCopyClear(&local_8c,0xffffff);
    local_74 = *(undefined4 *)&funnyShapePcs->field_0x6178;
    uVar2 = *(undefined4 *)&funnyShapePcs->field_0x617c;
    local_6c = *(undefined4 *)&funnyShapePcs->field_0x6180;
    local_68 = *(undefined4 *)&funnyShapePcs->field_0x6184;
    local_64 = *(undefined4 *)&funnyShapePcs->field_0x6188;
    local_60 = *(undefined4 *)&funnyShapePcs->field_0x618c;
    local_5c = *(undefined4 *)&funnyShapePcs->field_0x6190;
    local_58 = *(undefined4 *)&funnyShapePcs->field_0x6194;
    local_54 = *(undefined4 *)&funnyShapePcs->field_0x6198;
    local_50 = *(undefined4 *)&funnyShapePcs->field_0x619c;
    uVar6 = *(undefined4 *)&funnyShapePcs->field_0x61a0;
    local_48 = *(undefined4 *)&funnyShapePcs->field_0x61a4;
    local_44 = *(undefined4 *)&funnyShapePcs->field_0x61a8;
    local_3c = *(undefined4 *)&funnyShapePcs->field_0x61b0;
    local_38 = *(undefined4 *)&funnyShapePcs->field_0x61b4;
    *(undefined4 *)&funnyShapePcs->field_0x6138 = local_74;
    local_70._0_1_ = (undefined)((uint)uVar2 >> 0x18);
    funnyShapePcs->field_0x613c = local_70._0_1_;
    local_70._1_1_ = (undefined)((uint)uVar2 >> 0x10);
    funnyShapePcs->field_0x613d = local_70._1_1_;
    local_70._2_1_ = (undefined)((uint)uVar2 >> 8);
    funnyShapePcs->field_0x613e = local_70._2_1_;
    local_70._3_1_ = (undefined)uVar2;
    funnyShapePcs->field_0x613f = (undefined)local_70;
    *(undefined4 *)&funnyShapePcs->field_0x6140 = local_6c;
    *(undefined4 *)&funnyShapePcs->field_0x6144 = local_68;
    *(undefined4 *)&funnyShapePcs->field_0x6148 = local_64;
    *(undefined4 *)&funnyShapePcs->field_0x614c = local_60;
    *(undefined4 *)&funnyShapePcs->field_0x6150 = local_5c;
    *(undefined4 *)&funnyShapePcs->field_0x6154 = local_58;
    *(undefined4 *)&funnyShapePcs->field_0x6158 = local_54;
    *(undefined4 *)&funnyShapePcs->field_0x615c = local_50;
    local_4c._0_2_ = (undefined2)((uint)uVar6 >> 0x10);
    *(undefined2 *)&funnyShapePcs->field_0x6160 = local_4c._0_2_;
    local_4c._2_2_ = (undefined2)uVar6;
    *(undefined2 *)&funnyShapePcs->field_0x6162 = local_4c._2_2_;
    *(undefined4 *)&funnyShapePcs->field_0x6164 = local_48;
    *(undefined4 *)&funnyShapePcs->field_0x6168 = local_44;
    local_40._0_1_ = (undefined)((uint)*(undefined4 *)&funnyShapePcs->field_0x61ac >> 0x18);
    funnyShapePcs->field_0x616c = local_40._0_1_;
    local_70 = uVar2;
    local_4c = uVar6;
    local_40 = *(undefined4 *)&funnyShapePcs->field_0x61ac;
    __copy(&funnyShapePcs->field_0x616d,(int)&local_40 + 1,0xb);
    break;
  case 0xf:
    memcpy(local_84,(funnyShapePcs->m_usbStreamData).m_data,0x10);
    uStack_167 = (undefined)local_84._0_2_;
    local_168 = SUB21(local_84._0_2_,1);
    uStack_169 = (undefined)local_84._2_2_;
    local_16a = SUB21(local_84._2_2_,1);
    uStack_16b = (undefined)local_7c;
    local_16c = (undefined)((ushort)local_7c >> 8);
    *(ushort *)&funnyShapePcs->field_0x6050 = CONCAT11(uStack_167,local_168);
    *(ushort *)&funnyShapePcs->field_0x6052 = CONCAT11(uStack_169,local_16a);
    *(undefined4 *)&funnyShapePcs->field_0x6054 = local_80;
    *(ushort *)&funnyShapePcs->field_0x6058 = CONCAT11(uStack_16b,local_16c);
    *(undefined4 *)&funnyShapePcs->field_0x605a = local_7a;
    *(undefined2 *)&funnyShapePcs->field_0x605e = local_76;
    break;
  case 0x10:
    if (*(void **)&funnyShapePcs->field_0x6060 != (void *)0x0) {
      __dla__FPv(*(void **)&funnyShapePcs->field_0x6060);
      *(undefined4 *)&funnyShapePcs->field_0x6060 = 0;
    }
    puVar3 = (undefined2 *)
             __nwa__FUlPQ27CMemory6CStagePci
                       ((funnyShapePcs->m_usbStreamData).m_sizeBytes,FunnyShapePcs._4_4_,
                        s_FS_USB_Process_cpp_801d7e80,0x106);
    memcpy(puVar3,(funnyShapePcs->m_usbStreamData).m_data,
           (funnyShapePcs->m_usbStreamData).m_sizeBytes);
    uStack_16d = (undefined)*puVar3;
    local_16e = (undefined)((ushort)*puVar3 >> 8);
    *puVar3 = CONCAT11(uStack_16d,local_16e);
    uStack_16f = (undefined)puVar3[1];
    local_170 = (undefined)((ushort)puVar3[1] >> 8);
    iVar12 = 0;
    iVar14 = 0;
    puVar3[1] = CONCAT11(uStack_16f,local_170);
    iVar10 = 0;
    iVar11 = 0;
    for (iVar8 = 0; iVar8 < *(short *)&funnyShapePcs->field_0x6052; iVar8 = iVar8 + 1) {
      if ((*(ushort *)&funnyShapePcs->field_0x6050 & 8) == 0) {
        puVar5 = (uint *)((int)puVar3 + iVar14 + 0x10);
        uVar4 = *puVar5;
        *puVar5 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                  uVar4 >> 0x18;
        uVar4 = puVar5[1];
        puVar5[1] = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                    uVar4 >> 0x18;
        uStack_189 = (undefined)*(undefined2 *)(puVar5 + 4);
        local_18a = (undefined)((ushort)*(undefined2 *)(puVar5 + 4) >> 8);
        *(ushort *)(puVar5 + 4) = CONCAT11(uStack_189,local_18a);
        uStack_18b = (undefined)*(undefined2 *)((int)puVar5 + 0x12);
        local_18c = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x12) >> 8);
        *(ushort *)((int)puVar5 + 0x12) = CONCAT11(uStack_18b,local_18c);
        uStack_18d = (undefined)*(undefined2 *)(puVar5 + 5);
        local_18e = (undefined)((ushort)*(undefined2 *)(puVar5 + 5) >> 8);
        *(ushort *)(puVar5 + 5) = CONCAT11(uStack_18d,local_18e);
        uStack_18f = (undefined)*(undefined2 *)((int)puVar5 + 0x16);
        local_190 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x16) >> 8);
        *(ushort *)((int)puVar5 + 0x16) = CONCAT11(uStack_18f,local_190);
        uStack_191 = (undefined)*(undefined2 *)(puVar5 + 6);
        local_192 = (undefined)((ushort)*(undefined2 *)(puVar5 + 6) >> 8);
        *(ushort *)(puVar5 + 6) = CONCAT11(uStack_191,local_192);
        uStack_193 = (undefined)*(undefined2 *)((int)puVar5 + 0x1a);
        local_194 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1a) >> 8);
        *(ushort *)((int)puVar5 + 0x1a) = CONCAT11(uStack_193,local_194);
        uStack_195 = (undefined)*(undefined2 *)(puVar5 + 7);
        local_196 = (undefined)((ushort)*(undefined2 *)(puVar5 + 7) >> 8);
        *(ushort *)(puVar5 + 7) = CONCAT11(uStack_195,local_196);
        uStack_197 = (undefined)*(undefined2 *)((int)puVar5 + 0x1e);
        local_198 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1e) >> 8);
        pvVar7 = (void *)((int)puVar3 + iVar10 + 0x10);
        *(ushort *)((int)puVar5 + 0x1e) = CONCAT11(uStack_197,local_198);
        memcpy(pvVar7,puVar5,0x24);
        DCStoreRange(pvVar7,0x24);
      }
      else {
        puVar5 = (uint *)((int)puVar3 + iVar12 + 0x10);
        uVar4 = *puVar5;
        *puVar5 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                  uVar4 >> 0x18;
        uVar4 = puVar5[1];
        puVar5[1] = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                    uVar4 >> 0x18;
        uStack_171 = (undefined)*(undefined2 *)(puVar5 + 4);
        local_172 = (undefined)((ushort)*(undefined2 *)(puVar5 + 4) >> 8);
        *(ushort *)(puVar5 + 4) = CONCAT11(uStack_171,local_172);
        uStack_173 = (undefined)*(undefined2 *)((int)puVar5 + 0x12);
        local_174 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x12) >> 8);
        *(ushort *)((int)puVar5 + 0x12) = CONCAT11(uStack_173,local_174);
        uStack_175 = (undefined)*(undefined2 *)(puVar5 + 5);
        local_176 = (undefined)((ushort)*(undefined2 *)(puVar5 + 5) >> 8);
        *(ushort *)(puVar5 + 5) = CONCAT11(uStack_175,local_176);
        uStack_177 = (undefined)*(undefined2 *)((int)puVar5 + 0x16);
        local_178 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x16) >> 8);
        *(ushort *)((int)puVar5 + 0x16) = CONCAT11(uStack_177,local_178);
        uStack_179 = (undefined)*(undefined2 *)(puVar5 + 6);
        local_17a = (undefined)((ushort)*(undefined2 *)(puVar5 + 6) >> 8);
        *(ushort *)(puVar5 + 6) = CONCAT11(uStack_179,local_17a);
        uStack_17b = (undefined)*(undefined2 *)((int)puVar5 + 0x1a);
        local_17c = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1a) >> 8);
        *(ushort *)((int)puVar5 + 0x1a) = CONCAT11(uStack_17b,local_17c);
        uStack_17d = (undefined)*(undefined2 *)(puVar5 + 7);
        local_17e = (undefined)((ushort)*(undefined2 *)(puVar5 + 7) >> 8);
        *(ushort *)(puVar5 + 7) = CONCAT11(uStack_17d,local_17e);
        uStack_17f = (undefined)*(undefined2 *)((int)puVar5 + 0x1e);
        local_180 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x1e) >> 8);
        *(ushort *)((int)puVar5 + 0x1e) = CONCAT11(uStack_17f,local_180);
        uStack_181 = (undefined)*(undefined2 *)(puVar5 + 8);
        local_182 = (undefined)((ushort)*(undefined2 *)(puVar5 + 8) >> 8);
        *(ushort *)(puVar5 + 8) = CONCAT11(uStack_181,local_182);
        uStack_183 = (undefined)*(undefined2 *)((int)puVar5 + 0x22);
        local_184 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x22) >> 8);
        *(ushort *)((int)puVar5 + 0x22) = CONCAT11(uStack_183,local_184);
        uStack_185 = (undefined)*(undefined2 *)(puVar5 + 9);
        local_186 = (undefined)((ushort)*(undefined2 *)(puVar5 + 9) >> 8);
        *(ushort *)(puVar5 + 9) = CONCAT11(uStack_185,local_186);
        uStack_187 = (undefined)*(undefined2 *)((int)puVar5 + 0x26);
        local_188 = (undefined)((ushort)*(undefined2 *)((int)puVar5 + 0x26) >> 8);
        pvVar7 = (void *)((int)puVar3 + iVar11 + 0x10);
        *(ushort *)((int)puVar5 + 0x26) = CONCAT11(uStack_187,local_188);
        memcpy(pvVar7,puVar5,0x2c);
        DCStoreRange(pvVar7,0x2c);
      }
      iVar12 = iVar12 + 0x2c;
      iVar14 = iVar14 + 0x24;
      iVar10 = iVar10 + 0x24;
      iVar11 = iVar11 + 0x2c;
    }
    *(undefined2 **)&funnyShapePcs->field_0x6060 = puVar3;
    DCStoreRange(*(undefined4 *)&funnyShapePcs->field_0x6060,
                 (funnyShapePcs->m_usbStreamData).m_sizeBytes);
  }
  return;
}

