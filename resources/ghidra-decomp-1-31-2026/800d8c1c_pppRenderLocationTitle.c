// Function: pppRenderLocationTitle
// Entry: 800d8c1c
// Size: 400 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderLocationTitle(pppLocationTitle *pppLocationTitle,UnkB *param_2,UnkC *param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  Vec *source;
  int iVar5;
  undefined4 *puVar6;
  float local_60;
  Vec local_5c;
  Mtx local_50;
  
  iVar4 = *param_3->m_serializedDataOffsets;
  if (param_2->m_dataValIndex != 0xffff) {
    uVar2 = (pppLocationTitle->field0_0x0).m_graphId;
    iVar5 = -1;
    iVar3 = ((int)uVar2 >> 0xc) + (uint)((int)uVar2 < 0 && (uVar2 & 0xfff) != 0);
    source = *(Vec **)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar4);
    puVar6 = *(undefined4 **)
              (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA + param_2->m_dataValIndex * 4);
    if ((int)(uint)*(ushort *)(param_2->m_payload + 10) <= iVar3) {
      iVar5 = (uint)*(ushort *)(param_2->m_payload + 0xc) +
              (iVar3 - (uint)*(ushort *)(param_2->m_payload + 10));
    }
    for (iVar3 = 0;
        iVar3 < (int)(uint)*(ushort *)
                            ((undefined4 *)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar4) + 1);
        iVar3 = iVar3 + 1) {
      PSMTXIdentity(&local_50);
      local_50.value[2][2] = source[1].y;
      local_50.value[0][0] = (pppMngStPtr->m_scale).x * local_50.value[2][2];
      local_50.value[1][1] = (pppMngStPtr->m_scale).y * local_50.value[2][2];
      local_50.value[2][2] = (pppMngStPtr->m_scale).z * local_50.value[2][2];
      PSMTXMultVec(&ppvCameraMatrix0,source,&local_5c);
      local_50.value[0][3] = local_5c.x;
      local_50.value[1][3] = local_5c.y;
      local_50.value[2][3] = local_5c.z;
      pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
                (FLOAT_80330ee0,(pppCVector *)(source + 1),(pppFMATRIX *)0x0,0,0,0,0,0,1,0);
      if (-1 < iVar5) {
        bVar1 = *(byte *)((int)&source[1].x + 3);
        *(byte *)((int)&source[1].x + 3) = bVar1 - (char)((int)(uint)bVar1 / iVar5);
      }
      local_60 = source[1].x;
      GXSetChanMatColor(4,&local_60);
      GXLoadPosMtxImm(&local_50,0);
      pppSetBlendMode__FUc(*(undefined *)((int)&param_2->m_stepValue + 1));
      pppDrawShp__FPlsP12CMaterialSetUc
                (*puVar6,(int)*(short *)&source[2].x,pppEnvStPtr->m_materialSetPtr,
                 *(undefined *)((int)&param_2->m_stepValue + 1));
      source = (Vec *)&source[2].y;
    }
  }
  return;
}

