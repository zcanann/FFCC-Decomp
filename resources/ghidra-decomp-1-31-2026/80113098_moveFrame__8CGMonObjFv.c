// Function: moveFrame__8CGMonObjFv
// Entry: 80113098
// Size: 1508 bytes

/* WARNING: Removing unreachable block (ram,0x8011365c) */
/* WARNING: Removing unreachable block (ram,0x80113654) */
/* WARNING: Removing unreachable block (ram,0x8011364c) */
/* WARNING: Removing unreachable block (ram,0x80113644) */
/* WARNING: Removing unreachable block (ram,0x801130c0) */
/* WARNING: Removing unreachable block (ram,0x801130b8) */
/* WARNING: Removing unreachable block (ram,0x801130b0) */
/* WARNING: Removing unreachable block (ram,0x801130a8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void moveFrame__8CGMonObjFv(CGMonObj *gMonObj)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  Vec *pVVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double in_f29;
  Vec local_f8;
  Vec local_ec;
  Vec local_e0;
  CVector local_d4;
  CVector local_c8;
  CVector CStack_bc;
  CVector CStack_b0;
  CVector CStack_a4;
  CVector local_98;
  CVector local_8c;
  Vec local_80;
  CVector local_74;
  Vec local_68;
  undefined4 local_58;
  uint uStack_54;
  
  __ct__7CVectorFv(&local_68);
  __ct__7CVectorFv(&local_74);
  if ((*(uint *)&gMonObj->field_0x710 & 1) == 0) {
    __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
    uVar2 = *(uint *)&gMonObj->field_0x70c;
    if ((uVar2 & 1) == 0) {
      if ((uVar2 & 2) == 0) {
        if ((uVar2 & 0x2000) != 0) {
          __ct__7CVectorFRC3Vec(&CStack_b0,(Vec *)&gMonObj->field_0x718);
          pVVar4 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_a4,&(gMonObj->gObject).m_worldPosition);
          __ct__7CVectorFv(&local_e0);
          PSVECAdd(pVVar4,(Vec *)&CStack_b0,&local_e0);
          local_68.x = local_e0.x;
          local_68.y = local_e0.y;
          local_68.z = local_e0.z;
          in_f29 = (double)PSVECDistance(&local_68,&(gMonObj->gObject).m_worldPosition);
        }
      }
      else {
        __ct__7CVectorFRC3Vec(&local_98,(Vec *)&gMonObj->field_0x718);
        local_68.x = local_98.x;
        local_68.y = local_98.y;
        local_68.z = local_98.z;
        in_f29 = (double)PSVECDistance(&local_68,&(gMonObj->gObject).m_worldPosition);
        if (((*(uint *)&gMonObj->field_0x70c & 0x30000) != 0) && (ARRAY_8030918c._0_4_ != 0)) {
          uVar3 = calcPolygonGroup__6CAStarFP3Veci
                            ((CAStar *)&DbgMenuPcs.field_0x2a5c,&local_68,
                             (gMonObj->gObject).m_moveVec.x);
          moveAStar__8CGMonObjFiiR3Vec(gMonObj,(int)*(short *)&gMonObj->field_0x6a4,uVar3,&local_68)
          ;
        }
      }
    }
    else {
      __ct__7CVectorFRC3Vec(&local_8c,(Vec *)(*(int *)&gMonObj->field_0x714 + 0x15c));
      local_68.x = local_8c.x;
      local_68.y = local_8c.y;
      local_68.z = local_8c.z;
      in_f29 = (double)PSVECDistance(&local_68,&(gMonObj->gObject).m_worldPosition);
      if (((*(uint *)&gMonObj->field_0x70c & 0x30000) != 0) && (ARRAY_8030918c._0_4_ != 0)) {
        moveAStar__8CGMonObjFiiR3Vec
                  (gMonObj,(int)*(short *)&gMonObj->field_0x6a4,
                   (int)*(short *)(*(int *)&gMonObj->field_0x714 + 0x6a4),&local_68);
      }
    }
    __ct__7CVectorFRC3Vec(&CStack_bc,&(gMonObj->gObject).m_worldPosition);
    __ct__7CVectorFv(&local_ec);
    PSVECSubtract(&local_68,(Vec *)&CStack_bc,&local_ec);
    local_74.x = local_ec.x;
    local_74.y = local_ec.y;
    local_74.z = local_ec.z;
    if ((*(uint *)&gMonObj->field_0x70c & 0x40) != 0) {
      __ct__7CVectorFfff(-local_ec.x,-local_ec.y,-local_ec.z,&local_c8);
      local_74.x = local_c8.x;
      local_74.y = local_c8.y;
      local_74.z = local_c8.z;
    }
    dVar5 = (double)GetRotateY__7CVectorFv(&local_74);
    dVar6 = (double)PSVECMag((Vec *)&local_74);
    uVar2 = *(uint *)&gMonObj->field_0x70c;
    if ((((uVar2 & 0x20) == 0) || ((double)*(float *)&gMonObj->field_0x728 <= in_f29)) &&
       (((uVar2 & 0x40) == 0 || (in_f29 < (double)*(float *)&gMonObj->field_0x728)))) {
      if ((uVar2 & 4) != 0) {
        dVar6 = (double)(gMonObj->gObject).m_rotBaseY;
        if ((uVar2 & 0x8000) != 0) {
          dVar6 = (double)(float)(dVar6 + (double)FLOAT_803319c4);
        }
        dVar6 = (double)DstRot__5CMathFff(dVar5,dVar6,&Math);
        dVar7 = (double)(gMonObj->gObject).m_hitNormal.x;
        dVar5 = (double)(float)(dVar5 - (double)(float)(dVar6 * (double)(float)((double)
                                                  FLOAT_803319c0 - dVar7)));
        (gMonObj->gObject).m_rotBaseY = (gMonObj->gObject).m_rotBaseY + (float)(dVar6 * dVar7);
        (gMonObj->gObject).m_rotTargetY = (gMonObj->gObject).m_rotBaseY;
        dVar7 = (double)sin();
        dVar8 = (double)(float)dVar7;
        dVar6 = (double)cos(dVar6);
        dVar7 = (double)local_74.x;
        local_74.x = (float)((double)(float)dVar6 * dVar7 -
                            (double)(float)(dVar8 * (double)local_74.z));
        local_74.z = (float)(dVar8 * dVar7 +
                            (double)(float)((double)(float)dVar6 * (double)local_74.z));
        dVar6 = (double)PSVECMag((Vec *)&local_74);
      }
      uVar2 = *(uint *)&gMonObj->field_0x70c;
      if (((uVar2 & 0x80) == 0) ||
         (bVar1 = (gMonObj->gObject).m_stateFlags0,
         -1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) {
        if ((uVar2 & 0x200) == 0) {
          if ((uVar2 & 0x800) == 0) {
            dVar7 = (double)*(float *)&gMonObj->field_0x724;
          }
          else {
            local_58 = 0x43300000;
            uStack_54 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xd4);
            dVar7 = (double)(*(float *)&gMonObj->field_0x690 *
                            (FLOAT_803319cc *
                             (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_803319e0) +
                            FLOAT_803319c8));
          }
        }
        else {
          local_58 = 0x43300000;
          uStack_54 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xd4);
          dVar7 = (double)(*(float *)&gMonObj->field_0x690 *
                          (FLOAT_803319cc *
                           (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_803319e0) +
                          FLOAT_803319c8));
        }
        __ct__7CVectorFv(&local_80);
        if ((*(uint *)&gMonObj->field_0x70c & 0x1000) == 0) {
          if (DOUBLE_803319d0 <= ABS(dVar6)) {
            __ct__7CVectorFv(&local_f8);
            PSVECScale((float)((double)(float)((double)FLOAT_803319c0 / dVar6) * dVar7),
                       (Vec *)&local_74,&local_f8);
            local_80.x = local_f8.x;
            local_80.y = local_f8.y;
            local_80.z = local_f8.z;
          }
          else {
            __ct__7CVectorFfff(FLOAT_803319d8,FLOAT_803319d8,FLOAT_803319d8,&local_d4);
            local_80.x = local_d4.x;
            local_80.y = local_d4.y;
            local_80.z = local_d4.z;
          }
        }
        else {
          local_80.x = local_74.x;
          local_80.y = local_74.y;
          local_80.z = local_74.z;
        }
        if ((*(uint *)&gMonObj->field_0x70c & 0x4000) == 0) {
          (gMonObj->gObject).m_groundHitOffset.x =
               (gMonObj->gObject).m_groundHitOffset.x + local_80.x;
          (gMonObj->gObject).m_groundHitOffset.z =
               (gMonObj->gObject).m_groundHitOffset.z + local_80.z;
        }
        else {
          pVVar4 = &(gMonObj->gObject).m_groundHitOffset;
          PSVECAdd(pVVar4,&local_80,pVVar4);
        }
        if ((*(uint *)&gMonObj->field_0x70c & 0x8000) == 0) {
          (gMonObj->gObject).m_rotTargetY = (float)dVar5;
        }
        else {
          (gMonObj->gObject).m_rotTargetY = (float)((double)FLOAT_803319c4 + dVar5);
        }
        uVar2 = *(uint *)&gMonObj->field_0x70c;
        if ((((uVar2 & 0x20) == 0) || (*(float *)&gMonObj->field_0x728 <= (float)(in_f29 - dVar7)))
           && (((uVar2 & 0x40) == 0 || ((float)(in_f29 - dVar7) < *(float *)&gMonObj->field_0x728)))
           ) {
          if ((*(int *)&gMonObj->field_0x730 == 0) && ((uVar2 & 0x400) == 0)) {
            reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,1,1,0);
          }
          *(int *)&gMonObj->field_0x730 = *(int *)&gMonObj->field_0x730 + 1;
          if ((*(uint *)&gMonObj->field_0x70c & 0x10) == 0) {
            return;
          }
          if (*(int *)&gMonObj->field_0x730 < *(int *)&gMonObj->field_0x72c) {
            return;
          }
        }
      }
    }
    *(uint *)&gMonObj->field_0x710 = *(uint *)&gMonObj->field_0x710 | 1;
    __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
    *(uint *)&gMonObj->field_0x710 = *(uint *)&gMonObj->field_0x710 | 2;
    if ((*(uint *)&gMonObj->field_0x70c & 0x100) != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,*(undefined4 *)&gMonObj->field_0x738,0,0);
    }
  }
  return;
}

