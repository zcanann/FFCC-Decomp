// Function: addString__4CMesFPPci
// Entry: 80099460
// Size: 6900 bytes

/* WARNING: Removing unreachable block (ram,0x8009af38) */
/* WARNING: Removing unreachable block (ram,0x80099470) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void addString__4CMesFPPci(int *param_1,undefined4 *param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint8_t uVar4;
  float fVar5;
  bool bVar6;
  uint uVar7;
  float fVar8;
  int iVar9;
  byte bVar11;
  ushort uVar10;
  byte bVar12;
  byte *pbVar13;
  char cVar15;
  undefined *puVar14;
  uint uVar16;
  byte *pbVar17;
  byte *pbVar18;
  char *pcVar19;
  CFont *unaff_r18;
  CFont *font;
  int iVar20;
  int *piVar21;
  CFont *unaff_r24;
  int iVar22;
  double dVar23;
  undefined *local_248;
  undefined *local_244;
  undefined4 local_240;
  int32_t local_23c;
  char *local_238;
  char *local_234;
  char *local_230;
  char *local_22c;
  char *local_228;
  int local_224;
  undefined local_220;
  undefined4 local_21e;
  undefined local_218;
  undefined4 local_216;
  undefined local_210;
  undefined4 local_20e;
  char local_208 [32];
  char local_1e8 [32];
  char local_1c8 [32];
  char local_1a8 [32];
  char local_188 [32];
  undefined auStack_168 [256];
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  
  iVar9 = param_1[0xf50];
  font = (CFont *)MenuPcs._256_4_;
  if (iVar9 != 2) {
    if (iVar9 < 2) {
      font = (CFont *)MenuPcs._248_4_;
      if (iVar9 != 0) {
        font = unaff_r18;
      }
    }
    else {
      font = unaff_r18;
      if (iVar9 < 4) {
        font = (CFont *)MenuPcs._256_4_;
      }
    }
  }
  SetShadow__5CFontFi(font,(char)param_1[0xf4e]);
  SetMargin__5CFontFf(FLOAT_8033089c,font);
  dVar23 = (double)(float)param_1[0xf52];
  SetScaleX__5CFontFf((float)param_1[0xf51],font);
  SetScaleY__5CFontFf((float)dVar23,font);
  bVar6 = true;
  iVar9 = 0;
  iVar22 = 0;
  do {
    if (!bVar6) {
      return;
    }
    pbVar13 = (byte *)*param_2;
    *param_2 = pbVar13 + 1;
    bVar12 = *pbVar13;
    uVar16 = (uint)bVar12;
    if (bVar12 == 0) {
      bVar6 = false;
      goto switchD_8009959c_caseD_23;
    }
    if (bVar12 != 0xff) {
LAB_8009ad0c:
      if (iVar22 != 2) {
        piVar21 = param_1 + param_1[2] * 5 + 3;
        *(char *)((int)piVar21 + 0x12) = (char)param_1[0xf4a];
        *(char *)(piVar21 + 4) = (char)uVar16;
        *piVar21 = param_1[0xf21];
        local_60 = (double)(longlong)(int)(float)param_1[0xf22];
        *(short *)(piVar21 + 2) = (short)(int)(float)param_1[0xf22];
        font->renderFlags = font->renderFlags & 0xf7 | 8;
        if (uVar16 < 0x20) {
          dVar23 = (double)FLOAT_80330894;
        }
        else {
          dVar23 = (double)GetWidth__5CFontFUs(font,uVar16);
        }
        piVar21[1] = (int)(float)dVar23;
        fVar5 = FLOAT_803308ac;
        font->renderFlags = font->renderFlags & 0xf7;
        *(short *)(piVar21 + 3) = (short)param_1[0xf1f];
        *(byte *)((int)piVar21 + 0xf) =
             (byte)(param_1[0xf2d] << 4) | *(byte *)((int)piVar21 + 0xf) & 0xf;
        *(byte *)((int)piVar21 + 0xf) = *(byte *)((int)piVar21 + 0xf) & 0xf0;
        *(char *)((int)piVar21 + 0x13) = (char)param_1[0xf03];
        *(byte *)((int)piVar21 + 0xe) =
             (byte)(param_1[0xf4b] << 4) | *(byte *)((int)piVar21 + 0xe) & 0xf;
        *(byte *)((int)piVar21 + 0xe) =
             (byte)param_1[0xf50] & 0xf | *(byte *)((int)piVar21 + 0xe) & 0xf0;
        iVar20 = (int)(fVar5 * (float)param_1[0xf51]);
        local_68 = (double)(longlong)iVar20;
        *(char *)((int)piVar21 + 10) = (char)iVar20;
        iVar20 = (int)(fVar5 * (float)param_1[0xf52]);
        local_58 = (double)(longlong)iVar20;
        *(char *)((int)piVar21 + 0x11) = (char)iVar20;
        param_1[0xf21] = (int)((float)param_1[0xf21] + (float)piVar21[1] + (float)param_1[0xf4f]);
        if (param_1[0xf53] == 0) {
          param_1[0xf1f] = param_1[0xf1f] + param_1[0xf2c];
        }
        else {
          local_58 = (double)(CONCAT44(0x43300000,param_1[0xf2c] >> 1) ^ 0x80000000);
          dVar23 = local_58 - DOUBLE_80330878;
          if ((param_1[2] & 1U) == 0) {
            local_58 = (double)(CONCAT44(0x43300000,param_1[0xf1f]) ^ 0x80000000);
            iVar20 = (int)((float)(local_58 - DOUBLE_80330878) + (float)dVar23);
            local_60 = (double)(longlong)iVar20;
            param_1[0xf1f] = iVar20;
          }
          else {
            local_60 = (double)CONCAT44(0x43300000,param_1[0xf2c] ^ 0x80000000);
            local_58 = (double)CONCAT44(0x43300000,param_1[0xf1f] ^ 0x80000000);
            iVar20 = (int)((float)(local_58 - DOUBLE_80330878) +
                          ((float)(local_60 - DOUBLE_80330878) - (float)dVar23));
            local_68 = (double)(longlong)iVar20;
            param_1[0xf1f] = iVar20;
          }
        }
        param_1[2] = param_1[2] + 1;
      }
      goto switchD_8009959c_caseD_23;
    }
    pbVar13 = (byte *)*param_2;
    *param_2 = pbVar13 + 1;
    dVar23 = DOUBLE_80330878;
    uVar16 = *pbVar13 - 0xa0 & 0xffff;
    switch(uVar16) {
    case 0:
      goto switchD_8009959c_caseD_0;
    case 1:
      iVar20 = 2;
      if (param_1[0xf44] != 0) {
        iVar20 = 3;
      }
      param_1[0xf1e] = iVar20;
      bVar6 = false;
      param_1[0xf1d] = 1;
      goto switchD_8009959c_caseD_0;
    case 2:
      param_1[0xf1e] = 4;
      bVar6 = false;
      param_1[0xf1d] = 1;
      goto switchD_8009959c_caseD_0;
    case 3:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      param_1[0xf1f] = param_1[0xf1f] + (int)(char)(cVar15 << 4 | *pbVar13 & 0xf);
      break;
    case 4:
      param_1[0xf4b] = 0;
      break;
    case 5:
      param_1[0xf4b] = 2;
      break;
    case 6:
      param_1[0xf4b] = 1;
      break;
    case 7:
      param_1[0xf44] = 1;
      dVar23 = DOUBLE_80330880;
      param_1[0xf45] = 0;
      fVar8 = FLOAT_803308a8;
      fVar5 = FLOAT_803308a4;
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      param_1[0xf46] = (int)(char)(cVar15 << 4 | *pbVar13 & 0xf);
      local_68 = (double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa);
      param_1[0xf49] = (int)(fVar5 + (float)(local_68 - dVar23) * font->scaleY);
      param_1[0xf48] = param_1[0xf22];
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      param_1[0xf47] = (int)(char)(cVar15 << 4 | *pbVar13 & 0xf);
      param_1[0xf21] = (int)((float)param_1[0xf21] + fVar8 + (float)param_1[0xf4f]);
      break;
    case 8:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      iVar20 = param_1[0xf4a];
      if ((bVar12 & 0xf) != 0 || (*pbVar13 & 0xf) != 0) {
        param_1[0xf4a] = 6;
      }
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      local_224 = (param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffffU) * 0xc30 +
                  -0x7fddf986;
      addString__4CMesFPPci(param_1,&local_224,param_3);
      param_1[0xf4a] = iVar20;
      break;
    case 9:
    case 0x19:
    case 0x1d:
    case 0x37:
    case 0x39:
    case 0x3b:
    case 0x3d:
    case 0x3f:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      iVar20 = param_1[0xf4a];
      if ((bVar12 & 0xf) != 0 || (*pbVar13 & 0xf) != 0) {
        param_1[0xf4a] = 5;
      }
      pcVar19 = (char *)*param_2;
      local_228 = local_188;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      uVar7 = param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff;
      switch(uVar16) {
      case 9:
      case 0x37:
        strcpy(local_228,Game.game.m_cFlatDataArr[1].m_table[0].index[uVar7 * 5 + 1]);
        break;
      case 0x19:
        MakeArtsItemNames__5CGameFPci(&Game.game,local_228,uVar7);
        break;
      case 0x1d:
        strcpy(local_228,Game.game.m_cFlatDataArr[1].m_table[0].index[uVar7 * 5]);
        break;
      case 0x39:
        strcpy(local_228,Game.game.m_cFlatDataArr[1].m_table[0].index[uVar7 * 5 + 3]);
        break;
      case 0x3b:
        MakeArtItemName__5CGameFPcii(&Game.game,local_228,uVar7,1);
        break;
      case 0x3d:
        pcVar19 = (char *)*param_2;
        *param_2 = pcVar19 + 1;
        pbVar13 = (byte *)*param_2;
        cVar15 = *pcVar19;
        *param_2 = pbVar13 + 1;
        MakeArtItemName__5CGameFPcii
                  (&Game.game,local_228,uVar7,
                   param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff);
        break;
      case 0x3f:
        pcVar19 = (char *)*param_2;
        *param_2 = pcVar19 + 1;
        pbVar13 = (byte *)*param_2;
        cVar15 = *pcVar19;
        *param_2 = pbVar13 + 1;
        MakeNumItemName__5CGameFPcii
                  (&Game.game,local_228,uVar7,
                   param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff);
      }
      pcVar19 = local_228;
      if (iVar9 != 0) {
        if (iVar9 == 1) {
          if (*local_228 != '\0') {
            toupper();
          }
        }
        else if (iVar9 == 2) {
          if (*local_228 != '\0') {
            cVar15 = _toupperLatin1();
            *pcVar19 = cVar15;
          }
        }
        else if (*local_228 != '\0') {
          tolower();
        }
        iVar9 = 0;
      }
      addString__4CMesFPPci(param_1,&local_228,param_3);
      param_1[0xf4a] = iVar20;
      break;
    case 10:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar17 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      bVar11 = cVar15 << 4 | bVar12 & 0xf;
      pbVar17 = (byte *)*param_2;
      bVar12 = *pbVar13;
      *param_2 = pbVar17 + 1;
      pbVar18 = (byte *)*param_2;
      bVar2 = *pbVar17;
      *param_2 = pbVar18 + 1;
      pbVar13 = (byte *)*param_2;
      bVar3 = *pbVar18;
      *param_2 = pbVar13 + 1;
      uVar10 = (ushort)((int)(short)((ushort)((int)(short)((bVar12 & 0xf) << 4 | bVar2 & 0xf) << 4)
                                    | bVar3 & 0xf) << 4) | *pbVar13 & 0xf;
      param_1[bVar11 + 0xf30] = (int)(short)uVar10;
      if (param_3 == 0) {
        iVar20 = param_1[0xf03];
        local_20e = CONCAT13(bVar11,local_20e._1_3_);
        local_20e = CONCAT22(local_20e._0_2_,uVar10);
        param_1[0xf03] = iVar20 + 1;
        puVar14 = (undefined *)((int)param_1 + iVar20 * 6 + 0x3c14);
        *puVar14 = 2;
        local_210 = 2;
        *(undefined4 *)(puVar14 + 2) = local_20e;
      }
      break;
    case 0xb:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      bVar12 = cVar15 << 4 | *pbVar13 & 0xf;
      param_1[bVar12 + 0xf30] = param_1[bVar12 + 0xf30] + 1;
      if (param_3 == 0) {
        iVar20 = param_1[0xf03];
        local_216 = CONCAT13(bVar12,local_216._1_3_);
        param_1[0xf03] = iVar20 + 1;
        local_218 = 1;
        puVar14 = (undefined *)((int)param_1 + iVar20 * 6 + 0x3c14);
        *puVar14 = 1;
        *(undefined4 *)(puVar14 + 2) = local_216;
      }
      break;
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
      param_1[0xf4a] = uVar16 - 0xc;
      break;
    case 0x1a:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      fVar5 = FLOAT_803308a0;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      pbVar17 = (byte *)*param_2;
      bVar2 = *pbVar13;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar3 = *pbVar17;
      *param_2 = pbVar13 + 1;
      local_60 = (double)(CONCAT44(0x43300000,
                                   (int)(short)((ushort)((int)(short)((ushort)((int)(short)((bVar12 
                                                  & 0xf) << 4 | bVar2 & 0xf) << 4) | bVar3 & 0xf) <<
                                                  4) | *pbVar13 & 0xf)) ^ 0x80000000);
      param_1[0xf51] = (int)(fVar5 * (float)(local_60 - dVar23));
      dVar23 = (double)(float)param_1[0xf52];
      SetScaleX__5CFontFf((float)param_1[0xf51],font);
      SetScaleY__5CFontFf((float)dVar23,font);
      break;
    case 0x1b:
      pcVar19 = (char *)*param_2;
      iVar22 = 2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      if ((param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 1U) == 0) {
        iVar22 = 1;
      }
      break;
    case 0x1c:
      pcVar19 = (char *)*param_2;
      iVar22 = 2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      if ((param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 1U) == 1) {
        iVar22 = 1;
      }
      break;
    case 0x1e:
    case 0x1f:
    case 0x2a:
    case 0x38:
    case 0x3a:
    case 0x3c:
    case 0x3e:
    case 0x40:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      iVar20 = param_1[0xf4a];
      if ((bVar12 & 0xf) != 0 || (*pbVar13 & 0xf) != 0) {
        param_1[0xf4a] = 0;
      }
      pcVar19 = (char *)*param_2;
      local_22c = local_1a8;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      uVar7 = param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff;
      switch(uVar16) {
      case 0x1e:
        strcpy(local_22c,Game.game.m_cFlatDataArr[1].m_table[1].index[uVar7 * 5]);
        break;
      case 0x1f:
        MakeArtsMonNames__5CGameFPci(&Game.game,local_22c,uVar7);
        break;
      case 0x2a:
      case 0x38:
        strcpy(local_22c,Game.game.m_cFlatDataArr[1].m_table[1].index[uVar7 * 5 + 1]);
        break;
      case 0x3a:
        strcpy(local_22c,Game.game.m_cFlatDataArr[1].m_table[1].index[uVar7 * 5 + 3]);
        break;
      case 0x3c:
        MakeArtMonName__5CGameFPcii(&Game.game,local_22c,uVar7,1);
        break;
      case 0x3e:
        pcVar19 = (char *)*param_2;
        *param_2 = pcVar19 + 1;
        pbVar13 = (byte *)*param_2;
        cVar15 = *pcVar19;
        *param_2 = pbVar13 + 1;
        MakeArtMonName__5CGameFPcii
                  (&Game.game,local_22c,uVar7,
                   param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff);
        break;
      case 0x40:
        pcVar19 = (char *)*param_2;
        *param_2 = pcVar19 + 1;
        pbVar13 = (byte *)*param_2;
        cVar15 = *pcVar19;
        *param_2 = pbVar13 + 1;
        MakeNumMonName__5CGameFPcii
                  (&Game.game,local_22c,uVar7,
                   param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff);
      }
      pcVar19 = local_22c;
      if (iVar9 != 0) {
        if (iVar9 == 1) {
          if (*local_22c != '\0') {
            toupper();
          }
        }
        else if (iVar9 == 2) {
          if (*local_22c != '\0') {
            cVar15 = _toupperLatin1();
            *pcVar19 = cVar15;
          }
        }
        else if (*local_22c != '\0') {
          tolower();
        }
        iVar9 = 0;
      }
      addString__4CMesFPPci(param_1,&local_22c,param_3);
      param_1[0xf4a] = iVar20;
      break;
    case 0x20:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      uVar4 = Game.game.m_caravanWorkArr[param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30]].
              unk_0x3ca_0x3dd[0];
      if (((uVar4 == 'A') || (uVar4 == 'I')) ||
         ((uVar4 == 'U' || (((uVar4 == 'E' || (uVar4 == 'O')) || (uVar4 == 'Y')))))) {
        iVar22 = 1;
      }
      else {
        iVar22 = 2;
      }
      break;
    case 0x21:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      cVar15 = *(char *)Game.game.m_cFlatDataArr[1].m_table[2].index
                        [param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30]];
      if ((((cVar15 == 'A') || (cVar15 == 'I')) || (cVar15 == 'U')) ||
         (((cVar15 == 'E' || (cVar15 == 'O')) || (cVar15 == 'Y')))) {
        iVar22 = 1;
      }
      else {
        iVar22 = 2;
      }
      break;
    case 0x22:
      pbVar13 = (byte *)*param_2;
      *param_2 = pbVar13 + 1;
      pbVar18 = (byte *)*param_2;
      bVar12 = *pbVar13;
      *param_2 = pbVar18 + 1;
      pbVar17 = (byte *)*param_2;
      bVar2 = *pbVar18;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar3 = *pbVar17;
      *param_2 = pbVar13 + 1;
      bVar11 = *pbVar13;
      pbVar13 = (byte *)*param_2;
      *param_2 = pbVar13 + 1;
      bVar1 = *pbVar13;
      pbVar13 = (byte *)*param_2;
      local_60 = (double)(CONCAT44(0x43300000,
                                   (int)(short)((ushort)((int)(short)((ushort)((int)(short)((bVar12 
                                                  & 0xf) << 4 | bVar2 & 0xf) << 4) | bVar3 & 0xf) <<
                                                  4) | bVar11 & 0xf)) ^ 0x80000000);
      *param_2 = pbVar13 + 1;
      pbVar17 = (byte *)*param_2;
      bVar12 = *pbVar13;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar2 = *pbVar17;
      *param_2 = pbVar13 + 1;
      local_68 = (double)(CONCAT44(0x43300000,
                                   (int)(short)((ushort)((int)(short)((ushort)((int)(short)((bVar1 &
                                                                                            0xf) << 
                                                  4 | bVar12 & 0xf) << 4) | bVar2 & 0xf) << 4) |
                                               *pbVar13 & 0xf)) ^ 0x80000000);
      SetPos__8CMesMenuFff
                ((double)(float)(local_60 - dVar23),(double)(float)(local_68 - dVar23),
                 *(undefined4 *)(&MenuPcs.field_0x10c + *param_1 * 4));
      break;
    case 0x24:
      bVar6 = false;
      param_1[0xf1e] = 2;
      goto switchD_8009959c_caseD_0;
    case 0x25:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      iVar20 = (int)(char)(cVar15 << 4 | *pbVar13 & 0xf);
      if (param_1[0xf4c] == 0) {
        if (iVar20 == 0x7f) {
          param_1[0xf53] = 0;
        }
        else {
          param_1[0xf2c] = iVar20;
        }
      }
      else if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801d9e58);
      }
      break;
    case 0x26:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      param_1[0xf2d] = (int)(char)(cVar15 << 4 | *pbVar13 & 0xf);
      break;
    case 0x27:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      param_1[0xf2e] = (int)(char)(cVar15 << 4 | *pbVar13 & 0xf);
      break;
    case 0x28:
      bVar6 = false;
      param_1[0xf1e] = 1;
      goto switchD_8009959c_caseD_0;
    case 0x29:
      param_1[0xf1e] = 5;
      bVar6 = false;
      param_1[0xf1d] = 1;
switchD_8009959c_caseD_0:
      dVar23 = DOUBLE_80330880;
      param_1[0xf21] = (int)FLOAT_8033089c;
      local_68 = (double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa);
      param_1[0xf22] =
           (int)((float)param_1[0xf22] + FLOAT_803308a4 + (float)(local_68 - dVar23) * font->scaleY)
      ;
      fVar5 = FLOAT_803308a8;
      if (param_1[0xf44] != 0) {
        param_1[0xf45] = param_1[0xf45] + 1;
        param_1[0xf21] = (int)((float)param_1[0xf21] + fVar5 + (float)param_1[0xf4f]);
      }
      break;
    case 0x2b:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      iVar20 = param_1[0xf4a];
      if ((bVar12 & 0xf) != 0 || (*pbVar13 & 0xf) != 0) {
        param_1[0xf4a] = 6;
      }
      pcVar19 = (char *)*param_2;
      local_230 = local_1c8;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      strcpy(local_230,
             Game.game.m_cFlatDataArr[1].m_table[2].index
             [param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff]);
      pcVar19 = local_230;
      if (iVar9 != 0) {
        if (iVar9 == 1) {
          if (*local_230 != '\0') {
            toupper();
          }
        }
        else if (iVar9 == 2) {
          if (*local_230 != '\0') {
            cVar15 = _toupperLatin1();
            *pcVar19 = cVar15;
          }
        }
        else if (*local_230 != '\0') {
          tolower();
        }
        iVar9 = 0;
      }
      addString__4CMesFPPci(param_1,&local_230,param_3);
      param_1[0xf4a] = iVar20;
      break;
    case 0x2c:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      iVar20 = param_1[0xf4a];
      if ((bVar12 & 0xf) != 0 || (*pbVar13 & 0xf) != 0) {
        param_1[0xf4a] = 4;
      }
      pcVar19 = (char *)*param_2;
      local_234 = local_1e8;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      strcpy(local_234,
             Game.game.m_cFlatDataArr[1].m_table[3].index
             [param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff]);
      pcVar19 = local_234;
      if (iVar9 != 0) {
        if (iVar9 == 1) {
          if (*local_234 != '\0') {
            toupper();
          }
        }
        else if (iVar9 == 2) {
          if (*local_234 != '\0') {
            cVar15 = _toupperLatin1();
            *pcVar19 = cVar15;
          }
        }
        else if (*local_234 != '\0') {
          tolower();
        }
        iVar9 = 0;
      }
      addString__4CMesFPPci(param_1,&local_234,param_3);
      param_1[0xf4a] = iVar20;
      break;
    case 0x2d:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      iVar20 = param_1[0xf4a];
      if ((bVar12 & 0xf) != 0 || (*pbVar13 & 0xf) != 0) {
        param_1[0xf4a] = 3;
      }
      pcVar19 = (char *)*param_2;
      local_238 = local_208;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      strcpy(local_238,
             Game.game.m_cFlatDataArr[1].m_table[3].index
             [(param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffffU) + 0x3c]);
      pcVar19 = local_238;
      if (iVar9 != 0) {
        if (iVar9 == 1) {
          if (*local_238 != '\0') {
            toupper();
          }
        }
        else if (iVar9 == 2) {
          if (*local_238 != '\0') {
            cVar15 = _toupperLatin1();
            *pcVar19 = cVar15;
          }
        }
        else if (*local_238 != '\0') {
          tolower();
        }
        iVar9 = 0;
      }
      addString__4CMesFPPci(param_1,&local_238,param_3);
      param_1[0xf4a] = iVar20;
      break;
    case 0x2e:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      local_23c = Game.game.m_cFlatDataArr[1].m_table[5].index
                  [param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] & 0xffff];
      addString__4CMesFPPci(param_1,&local_23c,param_3);
      break;
    case 0x2f:
      local_240 = 0x8021ff68;
      addString__4CMesFPPci(param_1,&local_240,param_3);
      break;
    case 0x30:
      pcVar19 = (char *)*param_2;
      local_244 = auStack_168;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      sprintf(local_244,&DAT_8033088c,param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30]);
      addString__4CMesFPPci(param_1,&local_244,param_3);
      break;
    case 0x31:
      pbVar13 = (byte *)*param_2;
      *param_2 = pbVar13 + 1;
      pbVar18 = (byte *)*param_2;
      bVar12 = *pbVar13;
      *param_2 = pbVar18 + 1;
      pbVar17 = (byte *)*param_2;
      bVar2 = *pbVar18;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar3 = *pbVar17;
      *param_2 = pbVar13 + 1;
      local_68 = (double)(CONCAT44(0x43300000,
                                   (int)(short)((ushort)((int)(short)((ushort)((int)(short)((bVar12 
                                                  & 0xf) << 4 | bVar2 & 0xf) << 4) | bVar3 & 0xf) <<
                                                  4) | *pbVar13 & 0xf)) ^ 0x80000000);
      param_1[0xf21] = (int)(float)(local_68 - dVar23);
      pbVar13 = (byte *)*param_2;
      *param_2 = pbVar13 + 1;
      bVar12 = *pbVar13;
      pbVar13 = (byte *)*param_2;
      *param_2 = pbVar13 + 1;
      pbVar17 = (byte *)*param_2;
      bVar2 = *pbVar13;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar3 = *pbVar17;
      *param_2 = pbVar13 + 1;
      local_60 = (double)(CONCAT44(0x43300000,
                                   (int)(short)((ushort)((int)(short)((ushort)((int)(short)((bVar12 
                                                  & 0xf) << 4 | bVar2 & 0xf) << 4) | bVar3 & 0xf) <<
                                                  4) | *pbVar13 & 0xf)) ^ 0x80000000);
      param_1[0xf22] = (int)(float)(local_60 - dVar23);
      break;
    case 0x32:
      param_1[0xf4a] = 9;
      break;
    case 0x33:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      local_60 = (double)(CONCAT44(0x43300000,(int)(char)(cVar15 << 4 | *pbVar13 & 0xf)) ^
                         0x80000000);
      param_1[0xf4f] = (int)(float)(local_60 - dVar23);
      break;
    case 0x34:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      param_1[0xf50] = (int)(char)(cVar15 << 4 | *pbVar13 & 0xf);
      iVar20 = param_1[0xf50];
      font = (CFont *)MenuPcs._256_4_;
      if (iVar20 != 2) {
        if (iVar20 < 2) {
          font = (CFont *)MenuPcs._248_4_;
          if (iVar20 != 0) {
            font = unaff_r24;
          }
        }
        else {
          font = unaff_r24;
          if (iVar20 < 4) {
            font = (CFont *)MenuPcs._256_4_;
          }
        }
      }
      SetShadow__5CFontFi(font,(char)param_1[0xf4e]);
      SetMargin__5CFontFf(FLOAT_8033089c,font);
      dVar23 = (double)(float)param_1[0xf52];
      SetScaleX__5CFontFf((float)param_1[0xf51],font);
      SetScaleY__5CFontFf((float)dVar23,font);
      unaff_r24 = font;
      break;
    case 0x35:
      pbVar17 = (byte *)*param_2;
      *param_2 = pbVar17 + 1;
      fVar5 = FLOAT_803308a0;
      pbVar13 = (byte *)*param_2;
      bVar12 = *pbVar17;
      *param_2 = pbVar13 + 1;
      pbVar17 = (byte *)*param_2;
      bVar2 = *pbVar13;
      *param_2 = pbVar17 + 1;
      pbVar13 = (byte *)*param_2;
      bVar3 = *pbVar17;
      *param_2 = pbVar13 + 1;
      local_60 = (double)(CONCAT44(0x43300000,
                                   (int)(short)((ushort)((int)(short)((ushort)((int)(short)((bVar12 
                                                  & 0xf) << 4 | bVar2 & 0xf) << 4) | bVar3 & 0xf) <<
                                                  4) | *pbVar13 & 0xf)) ^ 0x80000000);
      fVar5 = fVar5 * (float)(local_60 - dVar23);
      param_1[0xf52] = (int)fVar5;
      param_1[0xf51] = (int)fVar5;
      dVar23 = (double)(float)param_1[0xf52];
      SetScaleX__5CFontFf((float)param_1[0xf51],font);
      SetScaleY__5CFontFf((float)dVar23,font);
      break;
    case 0x36:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      if (param_3 == 0) {
        iVar20 = param_1[0xf03];
        local_21e = CONCAT13(cVar15 << 4 | *pbVar13 & 0xf,local_21e._1_3_);
        param_1[0xf03] = iVar20 + 1;
        local_220 = 4;
        puVar14 = (undefined *)((int)param_1 + iVar20 * 6 + 0x3c14);
        *puVar14 = 4;
        *(undefined4 *)(puVar14 + 2) = local_21e;
      }
      break;
    case 0x41:
      pcVar19 = (char *)*param_2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      bVar12 = cVar15 << 4 | *pbVar13 & 0xf;
      if (bVar12 == 1) {
        iVar9 = 1;
      }
      else {
        iVar9 = 2;
        if (bVar12 == 0) {
          iVar9 = 3;
        }
      }
      break;
    case 0x42:
      pcVar19 = (char *)*param_2;
      iVar22 = 2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      if (param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30] == 1) {
        iVar22 = 1;
      }
      break;
    case 0x43:
      iVar22 = 2;
      if (Game.game.m_gameWork.m_menuStageMode != '\0') {
        iVar22 = 1;
      }
      break;
    case 0x44:
      iVar22 = 2;
      if (Game.game.m_caravanWorkArr[param_1[0xf43]].m_genderFlag == 0) {
        iVar22 = 1;
      }
      break;
    case 0x45:
      pcVar19 = (char *)*param_2;
      iVar22 = 2;
      *param_2 = pcVar19 + 1;
      pbVar13 = (byte *)*param_2;
      cVar15 = *pcVar19;
      *param_2 = pbVar13 + 1;
      if (Game.game.m_caravanWorkArr[param_1[(char)(cVar15 << 4 | *pbVar13 & 0xf) + 0xf30]].
          m_genderFlag == 0) {
        iVar22 = 1;
      }
      break;
    case 0x46:
      if (iVar22 == 1) {
        iVar22 = 2;
      }
      else if (iVar22 == 2) {
        iVar22 = 1;
      }
      break;
    case 0x47:
      iVar22 = 0;
      break;
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
    case 0x50:
    case 0x52:
    case 0x53:
      uVar16 = uVar16 - 0x48 & 0xffff;
      goto LAB_8009ad0c;
    case 0x54:
      local_248 = &DAT_80330888;
      addString__4CMesFPPci(param_1,&local_248,param_3);
    }
switchD_8009959c_caseD_23:
    fVar5 = (float)param_1[0xf21];
    if (fVar5 < (float)param_1[0xf23]) {
      fVar5 = (float)param_1[0xf23];
    }
    param_1[0xf23] = (int)fVar5;
    fVar5 = (float)param_1[0xf22];
    if (fVar5 < (float)param_1[0xf24]) {
      fVar5 = (float)param_1[0xf24];
    }
    param_1[0xf24] = (int)fVar5;
  } while( true );
}

