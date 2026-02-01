// Function: pppFrameLensFlare
// Entry: 800de8c4
// Size: 844 bytes

/* WARNING: Removing unreachable block (ram,0x800debf4) */
/* WARNING: Removing unreachable block (ram,0x800debec) */
/* WARNING: Removing unreachable block (ram,0x800debe4) */
/* WARNING: Removing unreachable block (ram,0x800debdc) */
/* WARNING: Removing unreachable block (ram,0x800de8ec) */
/* WARNING: Removing unreachable block (ram,0x800de8e4) */
/* WARNING: Removing unreachable block (ram,0x800de8dc) */
/* WARNING: Removing unreachable block (ram,0x800de8d4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameLensFlare(pppLensFlare *pppLensFlare,UnkB *param_2,UnkC *param_3)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  uint local_128;
  Vec VStack_124;
  Vec local_118;
  Vec VStack_10c;
  Vec local_100;
  Vec local_f4;
  undefined auStack_e8 [24];
  undefined auStack_d0 [28];
  Mtx MStack_b4;
  undefined4 local_80;
  uint uStack_7c;
  longlong local_78;
  undefined8 local_70;
  
  if (DAT_8032ed70 == 0) {
    iVar9 = param_3->m_serializedDataOffsets[2];
    local_80 = 0x43300000;
    uStack_7c = (uint)(byte)(&pppLensFlare->field_0x8b)[param_3->m_serializedDataOffsets[1]];
    dVar15 = (double)(pppMngStPtr->m_matrix).value[0][3];
    dVar14 = (double)(pppMngStPtr->m_matrix).value[1][3];
    dVar13 = (double)(pppMngStPtr->m_matrix).value[2][3];
    dVar16 = (double)((float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80331070) *
                     FLOAT_80331064);
    GXGetViewportv(auStack_e8);
    GXGetProjectionv(auStack_d0);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_b4);
    GXProject(dVar15,dVar14,dVar13,&MStack_b4,auStack_d0,auStack_e8,
              &pppLensFlare->field_0x90 + iVar9,&pppLensFlare->field_0x94 + iVar9,
              &pppLensFlare->field_0x98 + iVar9);
    (&pppLensFlare->field_0xb2)[iVar9] = 0;
    local_f4.x = (float)CameraPcs._224_4_;
    local_f4.y = (float)CameraPcs._228_4_;
    local_f4.z = (float)CameraPcs._232_4_;
    local_100.x = (float)CameraPcs._212_4_;
    local_100.y = (float)CameraPcs._216_4_;
    local_100.z = (float)CameraPcs._220_4_;
    PSVECSubtract(&local_100,&local_f4,&VStack_10c);
    local_118.x = (pppMngStPtr->m_matrix).value[0][3];
    local_118.y = (pppMngStPtr->m_matrix).value[1][3];
    local_118.z = (pppMngStPtr->m_matrix).value[2][3];
    PSVECSubtract(&local_f4,&local_118,&VStack_124);
    PSVECScale(FLOAT_80331068,&VStack_124,&VStack_124);
    PSVECNormalize(&VStack_10c,&VStack_10c);
    PSVECNormalize(&VStack_124,&VStack_124);
    dVar13 = (double)PSVECDotProduct(&VStack_124,&VStack_10c);
    *(float *)(&pppLensFlare->field_0xb4 + iVar9) = (float)dVar13;
    fVar2 = *(float *)(&pppLensFlare->field_0x90 + iVar9);
    fVar3 = *(float *)(&pppLensFlare->field_0x94 + iVar9);
    local_78 = (longlong)(int)fVar2;
    local_128 = 0;
    local_70 = (double)(longlong)(int)fVar3;
    bVar1 = *(byte *)&param_2->m_arg3;
    uVar6 = (uint)(bVar1 >> 1);
    uVar7 = __cvt_fp2unsigned((double)(FLOAT_8033106c *
                                      *(float *)(&pppLensFlare->field_0x98 + iVar9)));
    uVar4 = (int)fVar3 & 0xffff;
    uVar5 = (int)fVar2 & 0xffff;
    iVar12 = (int)(short)((ushort)bVar1 / (ushort)*(byte *)((int)&param_2->m_arg3 + 1));
    for (uVar10 = uVar4 - uVar6; (int)uVar10 <= (int)(uVar4 + uVar6); uVar10 = uVar10 + iVar12) {
      for (uVar11 = uVar5 - uVar6; (int)uVar11 <= (int)(uVar5 + uVar6); uVar11 = uVar11 + iVar12) {
        if ((((-1 < (short)uVar11) && (-1 < (short)uVar10)) && ((short)uVar11 < 0x281)) &&
           (((short)uVar10 < 0x1c1 &&
            (GXPeekZ(uVar11 & 0xffff,uVar10 & 0xffff,&local_128), uVar7 <= local_128)))) {
          (&pppLensFlare->field_0xb2)[iVar9] = (&pppLensFlare->field_0xb2)[iVar9] + '\x01';
        }
      }
    }
    iVar12 = *(byte *)((int)&param_2->m_arg3 + 1) + 1;
    uVar6 = iVar12 * iVar12;
    if ((byte)(&pppLensFlare->field_0xb2)[iVar9] == uVar6) {
      (&pppLensFlare->field_0xb2)[iVar9] = 0xff;
    }
    else {
      uVar6 = (uint)(byte)(&pppLensFlare->field_0xb2)[iVar9] * (0xff / uVar6);
      uVar8 = (undefined)uVar6;
      (&pppLensFlare->field_0xb2)[iVar9] = uVar8;
      if ((uVar6 & 0xff) < 0x100) {
        (&pppLensFlare->field_0xb2)[iVar9] = uVar8;
      }
      else {
        (&pppLensFlare->field_0xb2)[iVar9] = 0xff;
      }
    }
    local_70 = (double)CONCAT44(0x43300000,(uint)(byte)(&pppLensFlare->field_0xb2)[iVar9]);
    iVar12 = (int)((double)(float)(local_70 - DOUBLE_80331070) * dVar16);
    local_78 = (longlong)iVar12;
    (&pppLensFlare->field_0xb2)[iVar9] = (char)iVar12;
    if (param_2->m_dataValIndex != 0xffff) {
      pppCalcFrameShape__FPlRsRsRss
                (**(undefined4 **)
                   (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                   param_2->m_dataValIndex * 4),&pppLensFlare->field_0xac + iVar9,
                 &pppLensFlare->field_0xae + iVar9,&pppLensFlare->field_0xb0 + iVar9,
                 (int)*(short *)&param_2->m_initWOrk);
    }
  }
  return;
}

