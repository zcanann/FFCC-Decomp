// Function: getEscapePos__6CAStarFR3VecR3Vecii
// Entry: 80141820
// Size: 584 bytes

/* WARNING: Removing unreachable block (ram,0x80141a4c) */
/* WARNING: Removing unreachable block (ram,0x80141a44) */
/* WARNING: Removing unreachable block (ram,0x80141a3c) */
/* WARNING: Removing unreachable block (ram,0x80141840) */
/* WARNING: Removing unreachable block (ram,0x80141838) */
/* WARNING: Removing unreachable block (ram,0x80141830) */

CAPos * getEscapePos__6CAStarFR3VecR3Vecii
                  (CAStar *aStar,Vec *param_2,Vec *param_3,uint param_4,uint param_5)

{
  bool bVar1;
  Vec *pVVar2;
  uint uVar3;
  int iVar4;
  CAPos *pCVar5;
  CAPos *pCVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  Vec local_d8;
  Vec local_cc;
  Vec local_c0;
  CVector CStack_b4;
  CVector CStack_a8;
  CVector CStack_9c;
  CVector CStack_90;
  CVector CStack_84;
  CVector CStack_78;
  CVector local_6c;
  CVector local_60;
  
  __ct__7CVectorFRC3Vec(&CStack_84,param_3);
  pVVar2 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_78,param_2);
  __ct__7CVectorFv(&local_c0);
  PSVECSubtract(pVVar2,(Vec *)&CStack_84,&local_c0);
  local_60.x = local_c0.x;
  local_60.y = local_c0.y;
  local_60.z = local_c0.z;
  Normalize__7CVectorFv(&local_60);
  dVar9 = (double)FLOAT_8033209c;
  pCVar6 = (CAPos *)0x0;
  pCVar5 = (CAPos *)0x0;
  iVar4 = 0;
  dVar10 = dVar9;
  do {
    uVar3 = (uint)aStar->m_portals[0].m_groupA;
    bVar1 = false;
    if ((uVar3 != 0) && (aStar->m_portals[0].m_groupB != '\0')) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = false;
      if ((uVar3 == param_4) || (aStar->m_portals[0].m_groupB == param_4)) {
        bVar1 = true;
      }
      if (bVar1) {
        if (uVar3 == param_4) {
          uVar3 = (uint)aStar->m_portals[0].m_groupB;
        }
        if (param_5 != uVar3) {
          __ct__7CVectorFRC3Vec(&CStack_9c,param_3);
          pVVar2 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_90,&aStar->m_portals[0].m_position);
          __ct__7CVectorFv(&local_cc);
          PSVECSubtract(pVVar2,(Vec *)&CStack_9c,&local_cc);
          local_6c.x = local_cc.x;
          local_6c.y = local_cc.y;
          local_6c.z = local_cc.z;
          Normalize__7CVectorFv(&local_6c);
          dVar7 = (double)PSVECDotProduct((Vec *)&local_60,(Vec *)&local_6c);
          __ct__7CVectorFRC3Vec(&CStack_b4,param_3);
          pVVar2 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_a8,&aStar->m_portals[0].m_position);
          __ct__7CVectorFv(&local_d8);
          PSVECSubtract(pVVar2,(Vec *)&CStack_b4,&local_d8);
          local_6c.x = local_d8.x;
          local_6c.y = local_d8.y;
          local_6c.z = local_d8.z;
          dVar8 = (double)PSVECMag((Vec *)&local_6c);
          if (dVar7 < (double)FLOAT_80332088) {
            if (dVar9 < dVar8) {
              pCVar5 = aStar->m_portals;
              dVar9 = dVar8;
            }
          }
          else if (dVar10 < dVar8) {
            pCVar6 = aStar->m_portals;
            dVar10 = dVar8;
          }
        }
      }
    }
    iVar4 = iVar4 + 1;
    aStar = (CAStar *)&aStar->m_portals[0].m_position.y;
  } while (iVar4 < 0x40);
  if (pCVar6 != (CAPos *)0x0) {
    pCVar5 = pCVar6;
  }
  return pCVar5;
}

