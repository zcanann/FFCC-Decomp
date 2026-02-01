// Function: pppKeShpTail3X
// Entry: 80089da0
// Size: 1516 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppKeShpTail3X(pppKeShpTail3X *pppKeShpTail3X,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  Vec *dest;
  short *psVar2;
  Vec local_168;
  Vec local_15c;
  Vec local_150;
  float local_140;
  float local_13c;
  float local_138;
  float local_130;
  float local_12c;
  float local_128;
  Vec local_120;
  pppFMATRIX local_110;
  pppFMATRIX local_e0;
  pppFMATRIX local_b0;
  pppFMATRIX local_80;
  pppFMATRIX pStack_50;
  
  if (DAT_8032ed70 == 0) {
    psVar2 = (short *)((int)(&pppKeShpTail3X->pppPObject + 2) + *param_3->m_serializedDataOffsets);
    if (((pppKeShpTail3X->pppPObject).m_graphId == 0) && (pppKeShpTail3X->field_0x7d != '\0')) {
      *(undefined *)((int)psVar2 + 0x1c3) = 1;
      if (param_2->m_payload[0x3f] == '\0') {
        local_130 = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][3];
        local_12c = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][3];
        local_128 = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][3];
      }
      else if (param_2->m_payload[0x3f] == '\x01') {
        local_b0.value[0][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][0];
        local_b0.value[0][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][1];
        local_b0.value[0][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][2];
        local_b0.value[0][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][3];
        local_b0.value[1][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][0];
        local_b0.value[1][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][1];
        local_b0.value[1][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][2];
        local_b0.value[1][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][3];
        local_b0.value[2][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][0];
        local_b0.value[2][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][1];
        local_b0.value[2][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][2];
        local_b0.value[2][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][3];
        local_80.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
        local_80.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
        local_80.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
        local_80.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
        local_80.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
        local_80.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
        local_80.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
        local_80.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
        local_80.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
        local_80.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
        local_80.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
        local_80.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
        pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&pStack_50,&local_80,&local_b0);
        local_130 = pStack_50.value[0][3];
        local_12c = pStack_50.value[1][3];
        local_128 = pStack_50.value[2][3];
      }
      local_150.x = local_130;
      local_150.y = local_12c;
      local_150.z = local_128;
      pppCopyVector__FR3Vec3Vec(&local_120,&local_150);
      dest = (Vec *)(psVar2 + 0x18);
      iVar1 = 0x1c;
      do {
        local_15c.x = local_120.x;
        local_15c.y = local_120.y;
        local_15c.z = local_120.z;
        pppCopyVector__FR3Vec3Vec(dest,&local_15c);
        iVar1 = iVar1 + -1;
        dest = dest + 1;
      } while (0 < iVar1);
    }
    if (*(char *)(psVar2 + 0xe1) == '\0') {
      *(undefined *)(psVar2 + 0xe1) = 0x1c;
    }
    *(char *)(psVar2 + 0xe1) = *(char *)(psVar2 + 0xe1) + -1;
    if (param_2->m_payload[0x3f] == '\0') {
      local_140 = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][3];
      local_13c = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][3];
      local_138 = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][3];
    }
    else if (param_2->m_payload[0x3f] == '\x01') {
      local_110.value[0][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][0];
      local_110.value[0][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][1];
      local_110.value[0][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][2];
      local_110.value[0][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[0][3];
      local_110.value[1][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][0];
      local_110.value[1][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][1];
      local_110.value[1][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][2];
      local_110.value[1][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[1][3];
      local_110.value[2][0] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][0];
      local_110.value[2][1] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][1];
      local_110.value[2][2] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][2];
      local_110.value[2][3] = (pppKeShpTail3X->pppPObject).m_localMatrix.value[2][3];
      local_e0.value[0][0] = (pppMngStPtr->m_matrix).value[0][0];
      local_e0.value[0][1] = (pppMngStPtr->m_matrix).value[0][1];
      local_e0.value[0][2] = (pppMngStPtr->m_matrix).value[0][2];
      local_e0.value[0][3] = (pppMngStPtr->m_matrix).value[0][3];
      local_e0.value[1][0] = (pppMngStPtr->m_matrix).value[1][0];
      local_e0.value[1][1] = (pppMngStPtr->m_matrix).value[1][1];
      local_e0.value[1][2] = (pppMngStPtr->m_matrix).value[1][2];
      local_e0.value[1][3] = (pppMngStPtr->m_matrix).value[1][3];
      local_e0.value[2][0] = (pppMngStPtr->m_matrix).value[2][0];
      local_e0.value[2][1] = (pppMngStPtr->m_matrix).value[2][1];
      local_e0.value[2][2] = (pppMngStPtr->m_matrix).value[2][2];
      local_e0.value[2][3] = (pppMngStPtr->m_matrix).value[2][3];
      pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&pStack_50,&local_e0,&local_110);
      local_140 = pStack_50.value[0][3];
      local_13c = pStack_50.value[1][3];
      local_138 = pStack_50.value[2][3];
    }
    local_168.x = local_140;
    local_168.y = local_13c;
    local_168.z = local_138;
    pppCopyVector__FR3Vec3Vec
              ((Vec *)(psVar2 + (uint)*(byte *)(psVar2 + 0xe1) * 6 + 0x18),&local_168);
    psVar2[8] = psVar2[8] + psVar2[0xc];
    *psVar2 = *psVar2 + psVar2[8];
    psVar2[9] = psVar2[9] + psVar2[0xd];
    psVar2[1] = psVar2[1] + psVar2[9];
    psVar2[10] = psVar2[10] + psVar2[0xe];
    psVar2[2] = psVar2[2] + psVar2[10];
    psVar2[0xb] = psVar2[0xb] + psVar2[0xf];
    psVar2[3] = psVar2[3] + psVar2[0xb];
    psVar2[0x10] = psVar2[0x10] + psVar2[0x14];
    psVar2[4] = psVar2[4] + psVar2[0x10];
    psVar2[0x11] = psVar2[0x11] + psVar2[0x15];
    psVar2[5] = psVar2[5] + psVar2[0x11];
    psVar2[0x12] = psVar2[0x12] + psVar2[0x16];
    psVar2[6] = psVar2[6] + psVar2[0x12];
    psVar2[0x13] = psVar2[0x13] + psVar2[0x17];
    psVar2[7] = psVar2[7] + psVar2[0x13];
    if ((pppKeShpTail3X->pppPObject).m_graphId == param_2->m_graphId) {
      *psVar2 = *psVar2 + *(short *)(param_2->m_payload + 0xc);
      psVar2[1] = psVar2[1] + *(short *)(param_2->m_payload + 0xe);
      psVar2[2] = psVar2[2] + *(short *)(param_2->m_payload + 0x10);
      psVar2[3] = psVar2[3] + *(short *)(param_2->m_payload + 0x12);
      psVar2[8] = psVar2[8] + *(short *)(param_2->m_payload + 0x1c);
      psVar2[9] = psVar2[9] + *(short *)(param_2->m_payload + 0x1e);
      psVar2[10] = psVar2[10] + *(short *)(param_2->m_payload + 0x20);
      psVar2[0xb] = psVar2[0xb] + *(short *)(param_2->m_payload + 0x22);
      psVar2[0xc] = psVar2[0xc] + *(short *)(param_2->m_payload + 0x24);
      psVar2[0xd] = psVar2[0xd] + *(short *)(param_2->m_payload + 0x26);
      psVar2[0xe] = psVar2[0xe] + *(short *)(param_2->m_payload + 0x28);
      psVar2[0xf] = psVar2[0xf] + *(short *)(param_2->m_payload + 0x2a);
      psVar2[4] = psVar2[4] + *(short *)(param_2->m_payload + 0x14);
      psVar2[5] = psVar2[5] + *(short *)(param_2->m_payload + 0x16);
      psVar2[6] = psVar2[6] + *(short *)(param_2->m_payload + 0x18);
      psVar2[7] = psVar2[7] + *(short *)(param_2->m_payload + 0x1a);
      psVar2[0x10] = psVar2[0x10] + *(short *)(param_2->m_payload + 0x2c);
      psVar2[0x11] = psVar2[0x11] + *(short *)(param_2->m_payload + 0x2e);
      psVar2[0x12] = psVar2[0x12] + *(short *)(param_2->m_payload + 0x30);
      psVar2[0x13] = psVar2[0x13] + *(short *)(param_2->m_payload + 0x32);
      psVar2[0x14] = psVar2[0x14] + *(short *)(param_2->m_payload + 0x34);
      psVar2[0x15] = psVar2[0x15] + *(short *)(param_2->m_payload + 0x36);
      psVar2[0x16] = psVar2[0x16] + *(short *)(param_2->m_payload + 0x38);
      psVar2[0x17] = psVar2[0x17] + *(short *)(param_2->m_payload + 0x3a);
    }
    *(uint32_t *)(psVar2 + 0xdc) = *(int *)(psVar2 + 0xdc) + param_2->m_initWOrk;
  }
  return;
}

