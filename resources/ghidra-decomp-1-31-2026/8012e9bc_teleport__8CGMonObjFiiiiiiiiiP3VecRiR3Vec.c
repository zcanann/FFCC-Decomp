// Function: teleport__8CGMonObjFiiiiiiiiiP3VecRiR3Vec
// Entry: 8012e9bc
// Size: 1360 bytes

/* WARNING: Removing unreachable block (ram,0x8012eef0) */
/* WARNING: Removing unreachable block (ram,0x8012e9cc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void teleport__8CGMonObjFiiiiiiiiiP3VecRiR3Vec
               (CGMonObj *gMonObj,int param_2,undefined4 param_3,int param_4,int param_5,
               undefined4 param_6,undefined4 param_7,uint param_8,uint param_9,uint param_10,
               int param_11,int *param_12,float *param_13)

{
  float fVar1;
  int iVar2;
  CRef *pCVar3;
  Vec *pVVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  Vec local_c8;
  Vec local_bc;
  Vec local_b0;
  CVector CStack_a4;
  Vec local_98;
  CVector CStack_8c;
  Vec local_80;
  float local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  
  fVar1 = FLOAT_80331cf8;
  iVar5 = param_4 + 8;
  if (*(int *)&gMonObj->field_0x528 == 0) {
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff3fffc;
    *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
         *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xef;
    (gMonObj->gObject).m_groundHitOffset.z = fVar1;
    (gMonObj->gObject).m_groundHitOffset.y = fVar1;
    (gMonObj->gObject).m_groundHitOffset.x = fVar1;
    reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,param_3,0,0);
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,param_6,0x32,0x1c2,0,0);
    pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
    if (pCVar3 == (CRef *)0x0) {
      iVar2 = -1;
    }
    else {
      iVar2 = pCVar3[2].refCount;
    }
    putParticle__8CGPrgObjFiiP8CGObjectfi
              ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,param_8 | iVar2 << 8,
               *(int *)&gMonObj->field_0x58c,&gMonObj->gObject,0);
    if (param_2 == 0) {
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticle__8CGPrgObjFiiP3Vecfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,param_9 | iVar2 << 8,
                 *(undefined4 *)&gMonObj->field_0x58c,&(gMonObj->gObject).m_worldPosition,0);
    }
    else {
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,param_9 | iVar2 << 8,
                 *(int *)&gMonObj->field_0x58c,&gMonObj->gObject,0);
    }
  }
  iVar2 = *(int *)&gMonObj->field_0x528;
  if (iVar5 < iVar2) {
    if (param_5 < iVar2) {
      if (iVar2 <= param_5 + 8) {
        if (iVar2 == param_5 + 1) {
          if (param_2 == 0) {
            pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
            if (pCVar3 == (CRef *)0x0) {
              iVar5 = -1;
            }
            else {
              iVar5 = pCVar3[2].refCount;
            }
            putParticle__8CGPrgObjFiiP3Vecfi
                      ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,param_10 | iVar5 << 8,
                       *(undefined4 *)&gMonObj->field_0x58c,&(gMonObj->gObject).m_worldPosition,0);
            playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,param_7,0x32,0x1c2,0,0);
          }
          fVar1 = FLOAT_80331cf8;
          (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 3;
          *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
               *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xef | 0x10;
          (gMonObj->gObject).m_groundHitOffset.z = fVar1;
          (gMonObj->gObject).m_groundHitOffset.y = fVar1;
          (gMonObj->gObject).m_groundHitOffset.x = fVar1;
          if (param_2 == 1) {
            (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags | 1;
          }
        }
        local_60 = 0x43300000;
        uStack_5c = *(int *)&gMonObj->field_0x528 - param_5 ^ 0x80000000;
        dVar7 = (double)(FLOAT_80331d24 *
                        -((float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331d38) *
                          FLOAT_80331d28 - FLOAT_80331d18));
        dVar6 = (double)cos(dVar7);
        (gMonObj->gObject).m_rotationZ = (float)dVar6;
        (gMonObj->gObject).m_rotationX = (float)dVar6;
        dVar6 = (double)sin(dVar7);
        (gMonObj->gObject).m_rotationY = FLOAT_80331d18 + (float)dVar6;
        if (*(int *)&gMonObj->field_0x528 == param_5 + 8) {
          (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0xc0000;
          setAttackAfter__8CGMonObjFi(gMonObj,*(undefined4 *)&gMonObj->field_0x560);
        }
      }
    }
    else {
      if (iVar2 == param_4 + 9) {
        do {
          iVar2 = Rand__5CMathFUl(&Math,4);
        } while (iVar2 == *param_12);
        *param_12 = iVar2;
        *param_13 = (gMonObj->gObject).m_worldPosition.x;
        param_13[1] = (gMonObj->gObject).m_worldPosition.y;
        param_13[2] = (gMonObj->gObject).m_worldPosition.z;
        if (param_2 == 1) {
          (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags & 0xfffffffe;
        }
      }
      uStack_5c = param_5 - iVar5 ^ 0x80000000;
      local_68 = 0x43300000;
      uStack_64 = *(int *)&gMonObj->field_0x528 - iVar5 ^ 0x80000000;
      local_60 = 0x43300000;
      dVar6 = (double)cos((double)(FLOAT_80331d2c *
                                  ((float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331d38)
                                  / (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331d38
                                           ))));
      dVar6 = (double)(FLOAT_80331d30 * (FLOAT_80331d18 + (float)dVar6));
      pVVar4 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_a4,(Vec *)(param_11 + *param_12 * 0xc));
      __ct__7CVectorFv(&local_bc);
      PSVECScale((float)((double)FLOAT_80331d18 - dVar6),pVVar4,&local_bc);
      local_98.x = local_bc.x;
      local_98.y = local_bc.y;
      local_98.z = local_bc.z;
      pVVar4 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_8c,&(gMonObj->gObject).m_worldPosition);
      __ct__7CVectorFv(&local_b0);
      PSVECScale((float)dVar6,pVVar4,&local_b0);
      local_80.x = local_b0.x;
      local_80.y = local_b0.y;
      local_80.z = local_b0.z;
      __ct__7CVectorFv(&local_c8);
      PSVECAdd(&local_80,&local_98,&local_c8);
      local_74 = local_c8.x;
      (gMonObj->gObject).m_worldPosition.x = local_c8.x;
      (gMonObj->gObject).m_worldPosition.y = local_c8.y;
      local_70 = local_c8.y;
      local_6c = local_c8.z;
      (gMonObj->gObject).m_worldPosition.z = local_c8.z;
      if ((param_2 == 1) && (*(int *)&gMonObj->field_0x528 == param_5 + -0x2a)) {
        pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar3 == (CRef *)0x0) {
          iVar5 = -1;
        }
        else {
          iVar5 = pCVar3[2].refCount;
        }
        putParticle__8CGPrgObjFiiP3Vecfi
                  ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,param_10 | iVar5 << 8,
                   *(undefined4 *)&gMonObj->field_0x58c,param_11 + *param_12 * 0xc,0);
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,param_7,0x32,0x1c2,0,0);
      }
    }
  }
  else if (param_4 <= iVar2) {
    uStack_64 = iVar2 - param_4 ^ 0x80000000;
    local_68 = 0x43300000;
    dVar7 = (double)(FLOAT_80331d24 *
                    (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331d38) *
                    FLOAT_80331d28);
    dVar6 = (double)cos(dVar7);
    (gMonObj->gObject).m_rotationZ = (float)dVar6;
    (gMonObj->gObject).m_rotationX = (float)dVar6;
    dVar6 = (double)sin(dVar7);
    (gMonObj->gObject).m_rotationY = FLOAT_80331d18 + (float)dVar6;
  }
  return;
}

