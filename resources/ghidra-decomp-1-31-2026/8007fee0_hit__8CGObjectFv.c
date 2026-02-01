// Function: hit__8CGObjectFv
// Entry: 8007fee0
// Size: 740 bytes

/* WARNING: Removing unreachable block (ram,0x800801a8) */
/* WARNING: Removing unreachable block (ram,0x8007fef0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void hit__8CGObjectFv(CGObject *gObject)

{
  float fVar1;
  bool bVar2;
  CGObject *pCVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  double dVar10;
  CStack CStack_78;
  Vec VStack_74;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  Vec VStack_5c;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  void *local_38;
  
  bVar2 = false;
  if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
     (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
    bVar2 = true;
  }
  if (bVar2) {
    iVar6 = 0;
    pCVar3 = gObject;
    do {
      PSMTXMultVec(&gObject->m_charaModelHandle->m_model->m_nodes
                    [(int)pCVar3->m_attackColliders[0].m_radius2].m_mtx,
                   (Vec *)&pCVar3->m_attackColliders[0].m_localStart.y,
                   (Vec *)&pCVar3->m_attackColliders[0].m_worldPosition.y);
      pfVar9 = &pCVar3->m_attackColliders[0].m_worldPosition.y;
      PSVECAdd((Vec *)pfVar9,&gObject->m_worldPosition,(Vec *)pfVar9);
      iVar6 = iVar6 + 1;
      pCVar3 = (CGObject *)&(pCVar3->base_object).object.m_particleId;
    } while (iVar6 < 8);
    iVar6 = 0;
    pCVar3 = gObject;
    do {
      PSMTXMultVec(&gObject->m_charaModelHandle->m_model->m_nodes
                    [(int)pCVar3->m_damageColliders[0].m_outerRadius].m_mtx,
                   (Vec *)&pCVar3->m_damageColliders[0].m_localPosition.y,
                   (Vec *)&pCVar3->m_damageColliders[0].m_worldPosition.y);
      pfVar9 = &pCVar3->m_damageColliders[0].m_worldPosition.y;
      PSVECAdd((Vec *)pfVar9,&gObject->m_worldPosition,(Vec *)pfVar9);
      iVar6 = iVar6 + 1;
      pCVar3 = (CGObject *)&(pCVar3->base_object).object.m_waitCounter;
    } while (iVar6 < 8);
    if ((gObject->m_bgColMask & 0x40000) != 0) {
      for (pCVar3 = (CGObject *)FindGObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
          pCVar3 != (CGObject *)0x0;
          pCVar3 = (CGObject *)
                   FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,pCVar3)) {
        if (((pCVar3->m_bgColMask & 0x80000) != 0) && (gObject != pCVar3)) {
          PSVECSubtract(&gObject->m_worldPosition,&pCVar3->m_worldPosition,&VStack_5c);
          dVar10 = (double)PSVECDotProduct(&VStack_5c,&VStack_5c);
          fVar1 = gObject->m_nearColRadius + pCVar3->m_nearColRadius;
          if (dVar10 <= (double)(fVar1 * fVar1)) {
            dVar10 = (double)FLOAT_80330350;
            pfVar9 = &gObject->m_attackColliders[0].m_localStart.y;
            iVar6 = 0;
            do {
              if (dVar10 != (double)pfVar9[10]) {
                pfVar8 = &pCVar3->m_damageColliders[0].m_localPosition.y;
                iVar7 = 0;
                do {
                  if (((((uint)pfVar9[0xb] & (uint)pfVar8[9]) != 0) && (FLOAT_80330350 != pfVar8[7])
                      ) && (FLOAT_80330350 != pfVar8[8])) {
                    PSVECSubtract((Vec *)(pfVar9 + 6),(Vec *)(pfVar9 + 3),&VStack_74);
                    iVar4 = CrossCheckSphereVector__5CMathFP3VecPfP3VecP3VecP3Vecf
                                      ((double)pfVar9[10],(double)pfVar8[7],(double)pfVar8[8],&Math,
                                       &local_68,0,pfVar9 + 3,&VStack_74,pfVar8 + 3);
                    if ((iVar4 != 0) &&
                       (uVar5 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0xc))
                                          (gObject), (uVar5 & 0x2d) == 0x2d)) {
                      local_4c = (int)(pCVar3->base_object).object.m_particleId;
                      local_44 = local_68;
                      local_40 = local_64;
                      local_3c = local_60;
                      local_38 = gObject[1].base_object.object.m_vtable;
                      local_50 = iVar6;
                      local_48 = iVar7;
                      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                                (&CFlat,gObject,2,0x13,7,&local_50,&CStack_78);
                      iVar4 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0x38))
                                        (gObject,iVar6,pCVar3,iVar7,&local_68);
                      if (iVar4 == 1) goto LAB_80080190;
                      if (iVar4 == 2) {
                        return;
                      }
                    }
                  }
                  iVar7 = iVar7 + 1;
                  pfVar8 = pfVar8 + 10;
                } while (iVar7 < 8);
              }
              iVar6 = iVar6 + 1;
              pfVar9 = pfVar9 + 0xc;
            } while (iVar6 < 8);
          }
        }
LAB_80080190:
      }
    }
  }
  return;
}

