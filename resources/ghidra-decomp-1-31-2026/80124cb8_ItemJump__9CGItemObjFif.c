// Function: ItemJump__9CGItemObjFif
// Entry: 80124cb8
// Size: 332 bytes

/* WARNING: Removing unreachable block (ram,0x80124de0) */
/* WARNING: Removing unreachable block (ram,0x80124cc8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ItemJump__9CGItemObjFif(double param_1,uint param_2)

{
  CGItemObj *gItemObj;
  int iVar1;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  
  for (gItemObj = (CGItemObj *)FindGItemObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      gItemObj != (CGItemObj *)0x0;
      gItemObj = (CGItemObj *)
                 FindGItemObjNext__13CFlatRuntime2FP9CGItemObj((CFlatRuntime2 *)&CFlat,gItemObj)) {
    if (((gItemObj->prgObj).object.m_objectFlags & 0x10) == 0) {
      local_6c = (gItemObj->prgObj).object.m_worldPosition.x;
      local_64 = (gItemObj->prgObj).object.m_worldPosition.z;
      local_68 = (gItemObj->prgObj).object.m_worldPosition.y + FLOAT_80331b1c;
      local_78 = FLOAT_80331b20;
      local_70 = FLOAT_80331b20;
      local_74 = FLOAT_80331b24;
      local_30 = FLOAT_80331b28;
      local_34 = FLOAT_80331b28;
      local_38 = FLOAT_80331b28;
      local_24 = FLOAT_80331b2c;
      local_28 = FLOAT_80331b2c;
      local_2c = FLOAT_80331b2c;
      local_48 = FLOAT_80331b20;
      local_44 = FLOAT_80331b24;
      local_40 = FLOAT_80331b20;
      local_3c = FLOAT_80331b20;
      local_60 = local_6c;
      local_5c = local_68;
      local_58 = local_64;
      iVar1 = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl
                        (&MapMng,&local_60,&local_78,(gItemObj->prgObj).object.m_moveVec.x);
      if ((iVar1 != 0) && (*(byte *)(DAT_8032ec90 + 0x47) == param_2)) {
        (gItemObj->prgObj).object.m_groundHitOffset.y =
             (float)((double)(gItemObj->prgObj).object.m_groundHitOffset.y + param_1);
      }
    }
  }
  return;
}

