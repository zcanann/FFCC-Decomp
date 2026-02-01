// Function: calc__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
// Entry: 8008b824
// Size: 772 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR
               (_pppPObject *pppPObject,VYmMegaBirthShpTail2 *vYmMegaBirthShpTail2,
               PYmMegaBirthShpTail2 *pYmMegaBirthShpTail2,VColor *vColor,
               _PARTICLE_COLOR *particleColor)

{
  short sVar1;
  ushort uVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  float local_70;
  float local_6c;
  float local_68;
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
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  uVar7 = (uint)*(byte *)((int)particleColor->m_color + 0xb);
  *(float *)(vColor[3].m_unknown + 4) =
       *(float *)(vColor[3].m_unknown + 4) + pYmMegaBirthShpTail2->m_colorDeltaAdd[2];
  *(float *)(vColor[3].m_unknown + 8) =
       *(float *)(vColor[3].m_unknown + 8) + pYmMegaBirthShpTail2->m_sizeVal;
  local_4c = *(undefined4 *)(vColor[1].m_unknown + 4);
  local_48 = *(undefined4 *)(vColor[1].m_unknown + 8);
  local_44 = *(undefined4 *)vColor[2].m_unknown;
  pppScaleVectorXYZ__FR3Vec3Vecf(*(float *)(vColor[3].m_unknown + 4),&local_40,&local_4c);
  local_64 = local_40;
  local_60 = local_3c;
  local_5c = local_38;
  local_58 = *(undefined4 *)vColor->m_unknown;
  local_54 = *(undefined4 *)(vColor->m_unknown + 4);
  local_50 = *(undefined4 *)(vColor->m_unknown + 8);
  pppAddVector__FR3Vec3Vec3Vec(vColor,&local_58,&local_64);
  local_70 = (vYmMegaBirthShpTail2->m_tailScaleDirection).x;
  local_6c = (vYmMegaBirthShpTail2->m_tailScaleDirection).y;
  local_68 = (vYmMegaBirthShpTail2->m_tailScaleDirection).z;
  pppScaleVectorXYZ__FR3Vec3Vecf(*(float *)(vColor[3].m_unknown + 8),&local_40,&local_70);
  local_88 = local_40;
  local_84 = local_3c;
  local_80 = local_38;
  local_7c = *(undefined4 *)vColor->m_unknown;
  local_78 = *(undefined4 *)(vColor->m_unknown + 4);
  local_74 = *(undefined4 *)(vColor->m_unknown + 8);
  pppAddVector__FR3Vec3Vec3Vec(vColor,&local_7c,&local_88);
  if (*(short *)((pYmMegaBirthShpTail2->m_matrix).value[1] + 1) != 0) {
    *(short *)(vColor[2].m_unknown + 10) = *(short *)(vColor[2].m_unknown + 10) + -1;
  }
  vColor[4].m_unknown[4] = vColor[4].m_unknown[4] + '\x01';
  fVar3 = FLOAT_80330560;
  uVar4 = (uint)vColor[4].m_unknown[5];
  if ((uVar4 != 0) && (vColor[4].m_unknown[4] <= uVar4)) {
    uStack_2c = uVar7 ^ 0x80000000;
    local_30 = 0x43300000;
    local_28 = 0x43300000;
    *(float *)vColor[4].m_unknown =
         *(float *)vColor[4].m_unknown -
         (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80330578) /
         (float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80330580);
    uStack_24 = uVar4;
    if (*(float *)vColor[4].m_unknown < fVar3) {
      *(float *)vColor[4].m_unknown = fVar3;
    }
  }
  fVar3 = FLOAT_80330570;
  if ((vColor[4].m_unknown[6] != 0) &&
     (*(ushort *)(vColor[2].m_unknown + 10) <= (ushort)vColor[4].m_unknown[6])) {
    uStack_2c = (uint)*(byte *)((int)(pYmMegaBirthShpTail2->m_matrix).value[1] + 7);
    uStack_24 = uVar7 ^ 0x80000000;
    local_28 = 0x43300000;
    local_30 = 0x43300000;
    *(float *)vColor[4].m_unknown =
         *(float *)vColor[4].m_unknown +
         (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80330578) /
         (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80330580);
    if (fVar3 < *(float *)vColor[4].m_unknown) {
      *(float *)vColor[4].m_unknown = fVar3;
    }
  }
  if (vColor[4].m_unknown[8] == '\0') {
    vColor[4].m_unknown[8] = vColor[4].m_unknown[7];
  }
  vColor[4].m_unknown[8] = vColor[4].m_unknown[8] + 0xff;
  PSMTXMultVec(&pppPObject->m_localMatrix,(Vec *)vColor,
               (Vec *)(vColor[vColor[4].m_unknown[8] + 5].m_unknown + 4));
  uVar2 = *(ushort *)(vColor[2].m_unknown + 6);
  iVar5 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                    (int)(pYmMegaBirthShpTail2->m_matrix).value[0][1] * 4);
  *(ushort *)(vColor[2].m_unknown + 8) = uVar2;
  iVar6 = iVar5 + (uint)uVar2 * 8 + 0x10;
  *(short *)(vColor[2].m_unknown + 4) =
       *(short *)(vColor[2].m_unknown + 4) + SUB42((pYmMegaBirthShpTail2->m_matrix).value[0][2],0);
  sVar1 = *(short *)(iVar6 + 2);
  if ((int)sVar1 <= (int)(uint)*(ushort *)(vColor[2].m_unknown + 4)) {
    *(ushort *)(vColor[2].m_unknown + 4) = *(ushort *)(vColor[2].m_unknown + 4) - sVar1;
    *(short *)(vColor[2].m_unknown + 6) = *(short *)(vColor[2].m_unknown + 6) + 1;
    if ((int)*(short *)(iVar5 + 6) <= (int)(uint)*(ushort *)(vColor[2].m_unknown + 6)) {
      if ((*(byte *)(iVar6 + 4) & 0x80) == 0) {
        vColor[2].m_unknown[4] = '\0';
        vColor[2].m_unknown[5] = '\0';
        *(short *)(vColor[2].m_unknown + 6) = *(short *)(vColor[2].m_unknown + 6) + -1;
      }
      else {
        vColor[2].m_unknown[6] = '\0';
        vColor[2].m_unknown[7] = '\0';
        vColor[2].m_unknown[4] = '\0';
        vColor[2].m_unknown[5] = '\0';
      }
    }
  }
  return;
}

