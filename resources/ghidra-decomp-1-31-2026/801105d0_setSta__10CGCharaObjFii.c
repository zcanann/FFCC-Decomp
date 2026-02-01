// Function: setSta__10CGCharaObjFii
// Entry: 801105d0
// Size: 3452 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void setSta__10CGCharaObjFii(CGMonObj *param_1,int param_2,uint param_3)

{
  short sVar1;
  float fVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  CRef *pCVar6;
  void **ppvVar7;
  CGMonObj *pCVar8;
  int iVar9;
  
  bVar3 = false;
  bVar4 = false;
  uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))();
  if (((uVar5 & 0xad) == 0xad) &&
     (bVar4 = true, *(short *)((int)(param_1->gObject).m_scriptHandle[9] + 0xfc) == 0xb)) {
    bVar3 = true;
  }
  sVar1 = *(short *)((int)(param_1->gObject).m_scriptHandle + param_2 * 2 + 0x3e);
  param_3 = param_3 & ~((int)param_3 >> 0x1f);
  if ((sVar1 == 0) || (param_3 != 0)) {
    if ((sVar1 == 0) && (param_3 != 0)) {
      if (param_2 == 8) {
        iVar9 = 0;
        pCVar8 = param_1;
        do {
          if ((1 << iVar9 & 0x2000U) != 0) {
            EndParticleSlot__13CFlatRuntime2Fii
                      ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
          }
          iVar9 = iVar9 + 1;
          pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
        } while (iVar9 < 0x16);
        uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
        uVar5 = countLeadingZeros(0xad - (uVar5 & 0xad));
        fVar2 = FLOAT_80331964;
        if ((uVar5 >> 5 & 0xff) != 0) {
          fVar2 = FLOAT_80331984 *
                  (float)((double)CONCAT44(0x43300000,
                                           (uint)*(ushort *)
                                                  ((int)(param_1->gObject).m_scriptHandle[9] + 0x1b4
                                                  )) - DOUBLE_80331978);
        }
        uVar5 = 0x12;
        if (bVar4) {
          uVar5 = 0x6e;
        }
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius * fVar2),
                   (CGPrgObj *)param_1,uVar5 | 0x100,*(int *)&param_1->field_0x598,&param_1->gObject
                   ,0);
      }
      else if (param_2 < 8) {
        if (param_2 == 3) {
          iVar9 = 0;
          pCVar8 = param_1;
          do {
            if ((1 << iVar9 & 0x40000U) != 0) {
              EndParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
            }
            iVar9 = iVar9 + 1;
            pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
          } while (iVar9 < 0x16);
          putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                    ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                     (CGPrgObj *)param_1,0x10d,*(int *)&param_1->field_0x5ac,&param_1->gObject,0);
        }
        else if (param_2 < 3) {
          if (param_2 == 1) {
            iVar9 = 0;
            pCVar8 = param_1;
            do {
              if ((1 << iVar9 & 0x40U) != 0) {
                EndParticleSlot__13CFlatRuntime2Fii
                          ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
              }
              iVar9 = iVar9 + 1;
              pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
            } while (iVar9 < 0x16);
            if (bVar3) {
              pCVar6 = ((param_1->gObject).m_charaModelHandle)->m_pdtLoadRef;
              if (pCVar6 == (CRef *)0x0) {
                iVar9 = -1;
              }
              else {
                iVar9 = pCVar6[2].refCount;
              }
              putParticle__8CGPrgObjFiiP8CGObjectfi
                        ((double)FLOAT_80331964,(CGPrgObj *)param_1,iVar9 << 8 | 0x14,
                         *(int *)&param_1->field_0x57c,&param_1->gObject,0);
            }
            else {
              putParticle__8CGPrgObjFiiP8CGObjectfi
                        ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                         (CGPrgObj *)param_1,0x12a,*(int *)&param_1->field_0x57c,&param_1->gObject,0
                        );
            }
          }
          else if (param_2 < 1) {
            if (-1 < param_2) {
              iVar9 = 0;
              pCVar8 = param_1;
              do {
                if ((1 << iVar9 & 4U) != 0) {
                  EndParticleSlot__13CFlatRuntime2Fii
                            ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
                }
                iVar9 = iVar9 + 1;
                pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
              } while (iVar9 < 0x16);
              if (bVar3) {
                pCVar6 = ((param_1->gObject).m_charaModelHandle)->m_pdtLoadRef;
                if (pCVar6 == (CRef *)0x0) {
                  iVar9 = -1;
                }
                else {
                  iVar9 = pCVar6[2].refCount;
                }
                putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                          ((double)FLOAT_80331964,(CGPrgObj *)param_1,iVar9 << 8 | 0x15,
                           *(int *)&param_1->field_0x56c,&param_1->gObject,0);
              }
              else {
                putParticle__8CGPrgObjFiiP8CGObjectfi
                          ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                           (CGPrgObj *)param_1,0x10a,*(int *)&param_1->field_0x56c,&param_1->gObject
                           ,0);
              }
              uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))
                                (param_1);
              if ((uVar5 & 0xad) == 0xad) {
                setIceJEffect__8CGMonObjFi(param_1,0);
              }
            }
          }
          else {
            iVar9 = 0;
            *(undefined4 *)&param_1->field_0x6a0 = 0;
            pCVar8 = param_1;
            do {
              if ((1 << iVar9 & 0x80000U) != 0) {
                EndParticleSlot__13CFlatRuntime2Fii
                          ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
              }
              iVar9 = iVar9 + 1;
              pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
            } while (iVar9 < 0x16);
            putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                      ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                       (CGPrgObj *)param_1,0x10c,*(int *)&param_1->field_0x5b0,&param_1->gObject,0);
          }
        }
        else if (param_2 == 6) {
          iVar9 = 0;
          pCVar8 = param_1;
          do {
            if ((1 << iVar9 & 0x100000U) != 0) {
              EndParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
            }
            iVar9 = iVar9 + 1;
            pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
          } while (iVar9 < 0x16);
          putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                    ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                     (CGPrgObj *)param_1,0x107,*(int *)&param_1->field_0x5b4,&param_1->gObject,0);
        }
        else if (param_2 < 6) {
          if (param_2 < 5) {
            iVar9 = 0;
            pCVar8 = param_1;
            do {
              if ((1 << iVar9 & 0x80U) != 0) {
                EndParticleSlot__13CFlatRuntime2Fii
                          ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
              }
              iVar9 = iVar9 + 1;
              pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
            } while (iVar9 < 0x16);
            if (bVar3) {
              pCVar6 = ((param_1->gObject).m_charaModelHandle)->m_pdtLoadRef;
              if (pCVar6 == (CRef *)0x0) {
                iVar9 = -1;
              }
              else {
                iVar9 = pCVar6[2].refCount;
              }
              putParticle__8CGPrgObjFiiP8CGObjectfi
                        ((double)FLOAT_80331964,(CGPrgObj *)param_1,iVar9 << 8 | 0x17,
                         *(int *)&param_1->field_0x580,&param_1->gObject,0);
            }
            else {
              putParticle__8CGPrgObjFiiP8CGObjectfi
                        ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                         (CGPrgObj *)param_1,0x130,*(int *)&param_1->field_0x580,&param_1->gObject,0
                        );
            }
          }
        }
        else {
          iVar9 = 0;
          pCVar8 = param_1;
          do {
            if ((1 << iVar9 & 0x8000U) != 0) {
              EndParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
            }
            iVar9 = iVar9 + 1;
            pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
          } while (iVar9 < 0x16);
          uVar5 = 0x14;
          if (bVar4) {
            uVar5 = 0x70;
          }
          putParticle__8CGPrgObjFiiP8CGObjectfi
                    ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                     (CGPrgObj *)param_1,uVar5 | 0x100,*(int *)&param_1->field_0x5a0,
                     &param_1->gObject,0);
        }
      }
      else if (param_2 == 0x1c) {
        uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
        if (((uVar5 & 0xad) == 0xad) &&
           ((*(ushort *)((int)(param_1->gObject).m_scriptHandle[9] + 0xfe) & 1) != 0)) {
          undeadOff__8CGMonObjFv(param_1);
        }
      }
      else if (param_2 < 0x1c) {
        if (param_2 == 10) {
          uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
          if (((uVar5 & 0xad) == 0xad) &&
             ((*(ushort *)((int)(param_1->gObject).m_scriptHandle[9] + 0xfe) & 4) != 0)) {
            flyDown__8CGMonObjFv(param_1);
          }
        }
        else if (param_2 < 10) {
          iVar9 = 0;
          pCVar8 = param_1;
          do {
            if ((1 << iVar9 & 0x4000U) != 0) {
              EndParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
            }
            iVar9 = iVar9 + 1;
            pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
          } while (iVar9 < 0x16);
          uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
          uVar5 = countLeadingZeros(0xad - (uVar5 & 0xad));
          fVar2 = FLOAT_80331964;
          if ((uVar5 >> 5 & 0xff) != 0) {
            fVar2 = FLOAT_80331984 *
                    (float)((double)CONCAT44(0x43300000,
                                             (uint)*(ushort *)
                                                    ((int)(param_1->gObject).m_scriptHandle[9] +
                                                    0x1b4)) - DOUBLE_80331978);
          }
          uVar5 = 0x10;
          if (bVar4) {
            uVar5 = 0x6c;
          }
          putParticle__8CGPrgObjFiiP8CGObjectfi
                    ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius * fVar2),
                     (CGPrgObj *)param_1,uVar5 | 0x100,*(int *)&param_1->field_0x59c,
                     &param_1->gObject,0);
        }
        else if (0x1a < param_2) {
          iVar9 = 0;
          pCVar8 = param_1;
          do {
            if ((1 << iVar9 & 0x400U) != 0) {
              EndParticleSlot__13CFlatRuntime2Fii
                        ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
            }
            iVar9 = iVar9 + 1;
            pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
          } while (iVar9 < 0x16);
          putParticle__8CGPrgObjFiiP8CGObjectfi
                    ((double)FLOAT_80331964,(CGPrgObj *)param_1,0x11c,*(int *)&param_1->field_0x58c,
                     &param_1->gObject,0x1290d);
        }
      }
    }
  }
  else {
    switch(param_2) {
    case 0:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 4U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      if (bVar3) {
        pCVar6 = ((param_1->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar6 == (CRef *)0x0) {
          iVar9 = -1;
        }
        else {
          iVar9 = pCVar6[2].refCount;
        }
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331964,(CGPrgObj *)param_1,iVar9 << 8 | 0x16,0,&param_1->gObject,
                   0);
      }
      else {
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),
                   (CGPrgObj *)param_1,0x10b,0,&param_1->gObject,0);
      }
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)param_1,0x16,0x32,0x96,0,0);
      uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
      if ((uVar5 & 0xad) == 0xad) {
        setIceJEffect__8CGMonObjFi(param_1,1);
      }
      break;
    case 1:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x40U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      break;
    case 2:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x80000U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      break;
    case 3:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x40000U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),(CGPrgObj *)param_1
                 ,0x10e,0,&param_1->gObject,0);
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)param_1,0x3a,0x32,0x96,0,0);
      break;
    case 4:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x80U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      break;
    case 6:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x100000U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      break;
    case 7:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x8000U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      uVar5 = 0x15;
      if (bVar4) {
        uVar5 = 0x71;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius),(CGPrgObj *)param_1
                 ,uVar5 | 0x100,0,&param_1->gObject,0);
      break;
    case 8:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x2000U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
      uVar5 = countLeadingZeros(0xad - (uVar5 & 0xad));
      fVar2 = FLOAT_80331964;
      if ((uVar5 >> 5 & 0xff) != 0) {
        fVar2 = FLOAT_80331984 *
                (float)((double)CONCAT44(0x43300000,
                                         (uint)*(ushort *)
                                                ((int)(param_1->gObject).m_scriptHandle[9] + 0x1b4))
                       - DOUBLE_80331978);
      }
      uVar5 = 0x13;
      if (bVar4) {
        uVar5 = 0x6f;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius * fVar2),
                 (CGPrgObj *)param_1,uVar5 | 0x100,0,&param_1->gObject,0);
      break;
    case 9:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x4000U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
      uVar5 = countLeadingZeros(0xad - (uVar5 & 0xad));
      fVar2 = FLOAT_80331964;
      if ((uVar5 >> 5 & 0xff) != 0) {
        fVar2 = FLOAT_80331984 *
                (float)((double)CONCAT44(0x43300000,
                                         (uint)*(ushort *)
                                                ((int)(param_1->gObject).m_scriptHandle[9] + 0x1b4))
                       - DOUBLE_80331978);
      }
      uVar5 = 0x11;
      if (bVar4) {
        uVar5 = 0x6d;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)(FLOAT_803319ac * (param_1->gObject).m_attackColRadius * fVar2),
                 (CGPrgObj *)param_1,uVar5 | 0x100,0,&param_1->gObject,0);
      break;
    case 10:
      uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
      if ((((uVar5 & 0xad) == 0xad) &&
          (ppvVar7 = (param_1->gObject).m_scriptHandle,
          (*(ushort *)((int)ppvVar7[9] + 0xfe) & 4) != 0)) && (*(short *)(ppvVar7 + 7) != 0)) {
        flyUp__8CGMonObjFv(param_1);
      }
      break;
    case 0x1b:
      iVar9 = 0;
      pCVar8 = param_1;
      do {
        if ((1 << iVar9 & 0x400U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&pCVar8->field_0x564);
        }
        iVar9 = iVar9 + 1;
        pCVar8 = (CGMonObj *)&(pCVar8->gObject).base_object.object.m_freeListNode;
      } while (iVar9 < 0x16);
      break;
    case 0x1c:
      uVar5 = (**(code **)((int)(param_1->gObject).base_object.object.m_vtable + 0xc))(param_1);
      if (((uVar5 & 0xad) == 0xad) &&
         ((*(ushort *)((int)(param_1->gObject).m_scriptHandle[9] + 0xfe) & 1) != 0)) {
        undeadOn__8CGMonObjFv(param_1);
      }
    }
  }
  *(short *)((int)(param_1->gObject).m_scriptHandle + param_2 * 2 + 0x3e) = (short)param_3;
  return;
}

