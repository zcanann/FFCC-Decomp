// Function: pppFrameScreenBreak
// Entry: 8012d500
// Size: 880 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameScreenBreak(pppScreenBreak *pppScreenBreak,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  CCharaPcsCHandle *handle;
  int iVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  uint uVar8;
  float *value;
  
  if (DAT_8032ed70 == 0) {
    if (DAT_802381a0 != 0) {
      SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs(&GraphicsPcs,0,0,0,0,0,0,0);
    }
    iVar7 = *param_3->m_serializedDataOffsets;
    value = (float *)((int)(&pppScreenBreak->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    handle = (CCharaPcsCHandle *)
             GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
    iVar4 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(float **)(iVar4 + 0xe4) = value;
    *(UnkB **)(iVar4 + 0xe8) = param_2;
    GXSetZMode(1,3,0);
    *(undefined *)(value + 10) = (&pppScreenBreak->field_0x88)[iVar7];
    *(undefined *)((int)value + 0x29) = (&pppScreenBreak->field_0x89)[iVar7];
    *(undefined *)((int)value + 0x2a) = (&pppScreenBreak->field_0x8a)[iVar7];
    *(undefined *)((int)value + 0x2b) = (&pppScreenBreak->field_0x8b)[iVar7];
    DCFlushRange(value + 10,4);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (param_2->m_stepValue,&pppScreenBreak->field0_0x0,param_2->m_graphId,value,value + 1,
               value + 2,&param_2->m_arg3,param_2->m_payload);
    if (value[3] == 0.0) {
      fVar5 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               (*(int *)(*(int *)(iVar4 + 0xa4) + 0xc) * 0x3c,
                                pppEnvStPtr->m_stagePtr,s_pppScreenBreak_cpp_801dd4d4,0x25e);
      value[3] = fVar5;
      fVar5 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                               (0x20,pppEnvStPtr->m_stagePtr,s_pppScreenBreak_cpp_801dd4d4,0x25f);
      value[4] = fVar5;
      InitPieceData__FPQ26CChara6CModelP12PScreenBreakP12VScreenBreak(iVar4,param_2,value);
      PSVECNormalize((Vec *)(param_2->m_payload + 0xc),(Vec *)(param_2->m_payload + 0xc));
    }
    fVar5 = FLOAT_80331cc0 * value[6];
    fVar6 = value[3];
    fVar1 = FLOAT_80331cc0 * value[7];
    for (uVar8 = 0; uVar8 < *(uint *)(*(int *)(iVar4 + 0xa4) + 0xc); uVar8 = uVar8 + 1) {
      switch(*(undefined *)&param_2->m_initWOrk) {
      case 0:
        *(undefined *)((int)fVar6 + 0x38) = 1;
        break;
      case 1:
        if (-*(float *)((int)fVar6 + 0x28) < *value * fVar1 - value[7]) {
          *(undefined *)((int)fVar6 + 0x38) = 1;
        }
        break;
      case 2:
        if (-(*value * fVar1 - value[7]) < -*(float *)((int)fVar6 + 0x28)) {
          *(undefined *)((int)fVar6 + 0x38) = 1;
        }
        break;
      case 3:
        if (-*(float *)((int)fVar6 + 0x24) < *value * fVar5 + -value[6]) {
          *(undefined *)((int)fVar6 + 0x38) = 1;
        }
        break;
      case 4:
        if (-(*value * fVar5 - value[6]) < -*(float *)((int)fVar6 + 0x24)) {
          *(undefined *)((int)fVar6 + 0x38) = 1;
        }
        break;
      case 5:
        fVar5 = value[6];
        fVar1 = value[7];
        fVar2 = *value * fVar5;
        fVar3 = *value * fVar1;
        if (((*(float *)((int)fVar6 + 0x24) <= fVar2) && (-*(float *)((int)fVar6 + 0x24) <= fVar2))
           && ((*(float *)((int)fVar6 + 0x28) <= fVar3 && (-*(float *)((int)fVar6 + 0x28) <= fVar3))
              )) {
          *(undefined *)((int)fVar6 + 0x38) = 1;
        }
        break;
      case 6:
        fVar5 = value[6];
        fVar3 = *value * fVar5;
        fVar1 = value[7];
        fVar2 = *value * fVar1;
        if ((((fVar5 - fVar3 <= -*(float *)((int)fVar6 + 0x24)) ||
             (-*(float *)((int)fVar6 + 0x24) <= -fVar5 + fVar3)) ||
            (fVar1 - fVar2 <= -*(float *)((int)fVar6 + 0x28))) ||
           (-*(float *)((int)fVar6 + 0x28) <= -fVar1 + fVar2)) {
          *(undefined *)((int)fVar6 + 0x38) = 1;
        }
      }
      fVar6 = (float)((int)fVar6 + 0x3c);
    }
    pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
  }
  return;
}

