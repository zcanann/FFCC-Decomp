// Function: bgAttribCollision__8CGObjectFv
// Entry: 800801c4
// Size: 736 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void bgAttribCollision__8CGObjectFv(CGObject *gObject)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  CVector CStack_c8;
  CVector CStack_bc;
  CVector CStack_b0;
  CVector CStack_a4;
  undefined auStack_98 [4];
  float local_94;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  bVar1 = false;
  if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
     (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (bVar1) {
    *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xdf;
    if ((gObject->m_displayFlags & 4) != 0) {
      puVar2 = (undefined4 *)
               __ct__7CVectorFfff(FLOAT_80330350,FLOAT_8033035c,FLOAT_80330350,&CStack_b0);
      puVar3 = (undefined4 *)
               __ct__7CVectorFfff((gObject->m_worldPosition).x,
                                  FLOAT_80330410 + (gObject->m_worldPosition).y,
                                  (gObject->m_worldPosition).z,&CStack_a4);
      local_1c = FLOAT_8033033c;
      local_20 = FLOAT_8033033c;
      local_24 = FLOAT_8033033c;
      local_10 = FLOAT_80330340;
      local_14 = FLOAT_80330340;
      local_18 = FLOAT_80330340;
      local_4c = *puVar3;
      local_48 = puVar3[1];
      local_44 = puVar3[2];
      local_34 = *puVar2;
      local_30 = puVar2[1];
      local_2c = puVar2[2];
      local_28 = FLOAT_80330350;
      iVar4 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                        (&MapMng,&local_4c,puVar2,0x80000000);
      if (iVar4 != 0) {
        CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,auStack_98);
        gObject->m_bgCharmFactor = (gObject->m_worldPosition).y - local_94;
        *(byte *)&gObject->m_shieldNodeFlags = *(byte *)&gObject->m_shieldNodeFlags & 0xdf | 0x20;
      }
    }
    if ((*(byte *)&gObject->m_weaponNodeFlags & 1) == 0) {
      if ((FLOAT_80330350 != (gObject->m_groundHitOffset).x) ||
         (FLOAT_80330350 != (gObject->m_groundHitOffset).z)) {
        bVar1 = false;
        if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
           (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
          bVar1 = true;
        }
        if (bVar1) {
          puVar2 = (undefined4 *)
                   __ct__7CVectorFfff(FLOAT_80330350,FLOAT_8033035c,FLOAT_80330350,&CStack_bc);
          puVar3 = (undefined4 *)
                   __ct__7CVectorFfff((gObject->m_worldPosition).x,
                                      FLOAT_80330360 + (gObject->m_worldPosition).y,
                                      (gObject->m_worldPosition).z,&CStack_c8);
          local_5c = FLOAT_8033033c;
          local_60 = FLOAT_8033033c;
          local_64 = FLOAT_8033033c;
          local_50 = FLOAT_80330340;
          local_54 = FLOAT_80330340;
          local_58 = FLOAT_80330340;
          local_8c = *puVar3;
          local_88 = puVar3[1];
          local_84 = puVar3[2];
          local_74 = *puVar2;
          local_70 = puVar2[1];
          local_6c = puVar2[2];
          local_68 = FLOAT_80330350;
          iVar4 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                            (&MapMng,&local_8c,puVar2,0x78000000);
          if (iVar4 == 0) {
            gObject->m_bgAttrValue = FLOAT_80330338;
          }
          else {
            iVar4 = *(byte *)(DAT_8032ec90 + 0x47) - 0x28;
            if (iVar4 == 2) {
              gObject->m_bgAttrValue = FLOAT_8033036c;
            }
            else if (iVar4 < 2) {
              if (*(byte *)(DAT_8032ec90 + 0x47) == 0x28) {
                gObject->m_bgAttrValue = FLOAT_80330364;
              }
              else if (-1 < iVar4) {
                gObject->m_bgAttrValue = FLOAT_80330368;
              }
            }
            else if (iVar4 < 4) {
              gObject->m_bgAttrValue = FLOAT_80330350;
            }
          }
        }
      }
    }
    else {
      gObject->m_bgAttrValue = gObject->m_attachOwner->m_bgAttrValue;
    }
  }
  return;
}

