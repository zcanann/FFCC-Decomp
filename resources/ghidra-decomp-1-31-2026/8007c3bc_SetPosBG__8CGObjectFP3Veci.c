// Function: SetPosBG__8CGObjectFP3Veci
// Entry: 8007c3bc
// Size: 672 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetPosBG__8CGObjectFP3Veci(CGObject *gObject,float *param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  CVector CStack_b8;
  CVector CStack_ac;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  
  (gObject->m_worldPosition).x = *param_2;
  (gObject->m_worldPosition).y = param_2[1];
  (gObject->m_worldPosition).z = param_2[2];
  if (((int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1b |
            (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 5)) < 0) &&
     (Game.game.m_currentMapId != 0x21)) {
    local_94 = (gObject->m_worldPosition).x;
    local_8c = (gObject->m_worldPosition).z;
    local_90 = FLOAT_80330354;
    if (param_3 != 0) {
      local_90 = gObject->m_capsuleHalfHeight;
    }
    local_90 = (gObject->m_worldPosition).y + local_90;
    local_a0 = FLOAT_80330350;
    local_98 = FLOAT_80330350;
    local_9c = FLOAT_80330358;
    local_18 = FLOAT_8033033c;
    local_1c = FLOAT_8033033c;
    local_20 = FLOAT_8033033c;
    local_c = FLOAT_80330340;
    local_10 = FLOAT_80330340;
    local_14 = FLOAT_80330340;
    local_30 = FLOAT_80330350;
    local_2c = FLOAT_80330358;
    local_28 = FLOAT_80330350;
    local_24 = FLOAT_80330350;
    local_48 = local_94;
    local_44 = local_90;
    local_40 = local_8c;
    iVar2 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                      (&MapMng,&local_48,&local_a0,(gObject->m_moveVec).x);
    if (iVar2 != 0) {
      CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&gObject->m_worldPosition);
    }
    bVar1 = false;
    if ((gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) &&
       (gObject->m_charaModelHandle->m_model != (CModel *)0x0)) {
      bVar1 = true;
    }
    if (bVar1) {
      puVar3 = (undefined4 *)
               __ct__7CVectorFfff(FLOAT_80330350,FLOAT_8033035c,FLOAT_80330350,&CStack_ac);
      puVar4 = (undefined4 *)
               __ct__7CVectorFfff((gObject->m_worldPosition).x,
                                  FLOAT_80330360 + (gObject->m_worldPosition).y,
                                  (gObject->m_worldPosition).z,&CStack_b8);
      local_58 = FLOAT_8033033c;
      local_5c = FLOAT_8033033c;
      local_60 = FLOAT_8033033c;
      local_4c = FLOAT_80330340;
      local_50 = FLOAT_80330340;
      local_54 = FLOAT_80330340;
      local_88 = *puVar4;
      local_84 = puVar4[1];
      local_80 = puVar4[2];
      local_70 = *puVar3;
      local_6c = puVar3[1];
      local_68 = puVar3[2];
      local_64 = FLOAT_80330350;
      iVar2 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                        (&MapMng,&local_88,puVar3,0x78000000);
      if (iVar2 == 0) {
        gObject->m_bgAttrValue = FLOAT_80330338;
      }
      else {
        iVar2 = *(byte *)(DAT_8032ec90 + 0x47) - 0x28;
        if (iVar2 == 2) {
          gObject->m_bgAttrValue = FLOAT_8033036c;
        }
        else if (iVar2 < 2) {
          if (*(byte *)(DAT_8032ec90 + 0x47) == 0x28) {
            gObject->m_bgAttrValue = FLOAT_80330364;
          }
          else if (-1 < iVar2) {
            gObject->m_bgAttrValue = FLOAT_80330368;
          }
        }
        else if (iVar2 < 4) {
          gObject->m_bgAttrValue = FLOAT_80330350;
        }
      }
    }
    gObject->m_animBlend = gObject->m_bgAttrValue;
  }
  return;
}

