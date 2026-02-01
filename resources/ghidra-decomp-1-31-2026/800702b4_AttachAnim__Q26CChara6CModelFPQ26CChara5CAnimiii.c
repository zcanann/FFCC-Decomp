// Function: AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
// Entry: 800702b4
// Size: 848 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
               (CModel *model,CChara *chara,uint param_3,uint param_4,uint param_5)

{
  float fVar1;
  double dVar2;
  uint uVar3;
  void **ppvVar4;
  CAnim *pCVar5;
  CChara *pCVar6;
  int iVar7;
  ushort *puVar8;
  int iVar9;
  uint uVar10;
  ushort *puVar11;
  uint uVar12;
  void *pvVar13;
  int iVar14;
  uint uVar15;
  CNode *pCVar16;
  double local_48;
  
  if (param_5 == 0xffffffff) {
    pCVar5 = model->m_anim;
    if (((pCVar5 == (CAnim *)0x0) || (uVar12 = (uint)(byte)pCVar5[9], uVar12 == 0)) ||
       (*(int *)(pCVar5 + 0x20) == 0)) {
      if (pCVar5 == (CAnim *)0x0) {
        param_5 = 0;
      }
      else {
        param_5 = 4;
      }
    }
    else {
      param_5 = 4;
      iVar9 = 0;
      puVar8 = (ushort *)(*(int *)(pCVar5 + 0x18) + *(int *)(pCVar5 + 0x20));
      puVar11 = puVar8;
      for (uVar15 = uVar12; uVar15 != 0; uVar15 = uVar15 - 1) {
        if (iVar9 == 0) {
          uVar10 = 0;
        }
        else {
          uVar10 = (uint)*puVar11;
        }
        if (iVar9 + 1 < (int)uVar12) {
          uVar3 = (uint)puVar11[2];
        }
        else {
          uVar3 = 10000000;
        }
        if (((int)uVar10 <= (int)model->m_curFrame) && ((int)model->m_curFrame < (int)uVar3)) {
          param_5 = (uint)puVar8[iVar9 * 2 + 1];
          break;
        }
        puVar11 = puVar11 + 2;
        iVar9 = iVar9 + 1;
      }
    }
  }
  pCVar6 = (CChara *)model->m_anim;
  if (chara != pCVar6) {
    if (pCVar6 != (CChara *)0x0) {
      ppvVar4 = (void **)((int)(pCVar6->field0_0x0).object.base_object.object.m_freeListNode + -1);
      (pCVar6->field0_0x0).object.base_object.object.m_freeListNode = ppvVar4;
      if ((ppvVar4 == (void **)0x0) && (pCVar6 != (CChara *)0x0)) {
        (**(code **)((pCVar6->field0_0x0).object.base_object.object.m_id + 8))(pCVar6,1);
      }
      model->m_anim = (CAnim *)0x0;
    }
    model->m_anim = (CAnim *)chara;
    pCVar5 = model->m_anim;
    if (pCVar5 != (CAnim *)0x0) {
      *(int *)(pCVar5 + 4) = *(int *)(pCVar5 + 4) + 1;
    }
  }
  pCVar16 = model->m_nodes;
  uVar12 = 0;
  do {
    fVar1 = FLOAT_803301b0;
    if (model->m_data->m_nodeCount <= uVar12) {
      if (model->m_anim == (CAnim *)0x0) {
        model->m_curFrame = FLOAT_803301b0;
        model->m_time = fVar1;
        model->m_animEnd = fVar1;
        model->m_animStart = fVar1;
      }
      else {
        if (model->m_attachMode == '\0') {
          model->m_blendCur =
               (ushort)param_5 & (ushort)((int)-(uint)((byte)model->m_anim[8] >> 7) >> 0x1f);
        }
        else if (model->m_attachMode == '\x01') {
          model->m_blendCur = (ushort)param_5;
        }
        else {
          model->m_blendCur = 0;
        }
        dVar2 = DOUBLE_803301c0;
        local_48 = (double)(CONCAT44(0x43300000,
                                     param_3 & ~((int)~(param_3 + 1 | -param_3 - 1) >> 0x1f)) ^
                           0x80000000);
        model->m_blendMax = model->m_blendCur;
        model->m_animStart = (float)(local_48 - dVar2);
        model->m_curFrame = model->m_animStart;
        model->m_time = model->m_animStart;
        if (param_4 == 0xffffffff) {
          param_4 = *(ushort *)(model->m_anim + 0x10) - 1;
        }
        model->m_animEnd =
             (float)((double)CONCAT44(0x43300000,param_4 ^ 0x80000000) - DOUBLE_803301c0);
      }
      return;
    }
    pCVar16->m_animNode0 = (void *)0x0;
    pCVar16->m_animNode1 = (void *)0x0;
    C_QUATMtx(&pCVar16->m_previousQuat,(Mtx *)(pCVar16->unk_0x8_0x43 + 0xc));
    (pCVar16->m_previousPosition).x = *(float *)(pCVar16->unk_0x8_0x43 + 0x18);
    (pCVar16->m_previousPosition).y = *(float *)(pCVar16->unk_0x8_0x43 + 0x28);
    (pCVar16->m_previousPosition).z = *(float *)(pCVar16->unk_0x8_0x43 + 0x38);
    MTXGetScale__5CMathFPA4_fP3Vec
              (&Math,(Mtx *)(pCVar16->unk_0x8_0x43 + 0xc),&pCVar16->m_previousScale);
    if (model->m_anim != (CAnim *)0x0) {
      iVar9 = 0;
      for (uVar15 = 0; uVar15 < *(ushort *)(model->m_anim + 0xe); uVar15 = uVar15 + 1) {
        uVar10 = 0;
        iVar14 = 0;
        pvVar13 = (void *)(*(int *)(model->m_anim + 0x14) + iVar9);
        do {
          if ((pCVar16->m_refData->m_name[iVar14] != '\0') && (iVar7 = strcmp(pvVar13), iVar7 == 0))
          {
            *(void **)((int)(&pCVar16->m_mtx + 1) + uVar10 * 4) = pvVar13;
            break;
          }
          uVar10 = uVar10 + 1;
          iVar14 = iVar14 + 0x10;
        } while (uVar10 < 2);
        iVar9 = iVar9 + 0x18;
      }
    }
    uVar12 = uVar12 + 1;
    pCVar16 = pCVar16 + 1;
  } while( true );
}

