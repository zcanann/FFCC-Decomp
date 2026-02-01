// Function: pppEditBeforeCalc__8CPartMngFv
// Entry: 8005bbc0
// Size: 1648 bytes

/* WARNING: Removing unreachable block (ram,0x8005c210) */
/* WARNING: Removing unreachable block (ram,0x8005c208) */
/* WARNING: Removing unreachable block (ram,0x8005bbd8) */
/* WARNING: Removing unreachable block (ram,0x8005bbd0) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEditBeforeCalc__8CPartMngFv(CPartMng *partMng)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  double dVar2;
  double dVar3;
  int local_58;
  int local_54 [4];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  switch((partMng->m_pppEnvSt).m_lastEnvCmd) {
  case 1:
    (partMng->m_editCameraMatrix).value[2][0] = -(partMng->m_editCameraMatrix).value[2][0];
    (partMng->m_editCameraMatrix).value[2][2] = -(partMng->m_editCameraMatrix).value[2][2];
    (partMng->m_editCameraMatrix).value[0][1] = -(partMng->m_editCameraMatrix).value[0][1];
    (partMng->m_editCameraMatrix).value[1][1] = -(partMng->m_editCameraMatrix).value[1][1];
    (partMng->m_editCameraMatrix).value[2][3] = -(partMng->m_editCameraMatrix).value[2][3];
    (partMng->m_editCameraMatrix).value[2][3] =
         (partMng->m_editCameraMatrix).value[2][3] * *(float *)partMng->m_editCameraExtra;
    PSMTXCopy(&partMng->m_editCameraMatrix,&ppvCameraMatrix0);
    C_MTXPerspective(FLOAT_8032fe4c,FLOAT_8032fe50,FLOAT_8032fe54,FLOAT_8032fe58,
                     (Mtx *)&ppvScreenMatrix);
    FLOAT_8032ed58 = ppvScreenMatrix.value[2][0];
    FLOAT_8032ed5c = ppvScreenMatrix.value[2][1];
    FLOAT_8032ed60 = ppvScreenMatrix.value[2][3];
    PSMTXCopy(&ppvCameraMatrix0,&ppvCameraMatrix0);
    PSMTX44Copy(&ppvScreenMatrix,&ppvScreenMatrix0);
    local_34 = CONCAT31(*(undefined3 *)partMng->m_rgbaA,0xff);
    local_3c = local_34;
    GXSetCopyClear(&local_3c,0xffffff);
    dVar2 = (double)(float)partMng->m_fogFarRaw;
    dVar3 = (double)(float)partMng->m_fogNearRaw;
    if (partMng->m_rgbaB[0] == '\0') {
      local_54[2] = 0;
      local_44 = 0;
      SetFogColor__8CGraphicF8_GXColor(&Graphic,&local_44);
      SetFogParam__8CGraphicFff(FLOAT_8032fe5c,FLOAT_8032fe5c,&Graphic);
    }
    else {
      local_54[2] = (uint)*(uint3 *)(partMng->m_rgbaB + 1) << 8;
      local_54[3] = local_54[2];
      SetFogColor__8CGraphicF8_GXColor(&Graphic,local_54 + 3);
      SetFogParam__8CGraphicFff((float)dVar3,(float)dVar2,&Graphic);
    }
    DAT_8032ed6c = 1;
    break;
  case 2:
    (partMng->m_editCameraMatrix).value[2][0] = -(partMng->m_editCameraMatrix).value[2][0];
    (partMng->m_editCameraMatrix).value[2][2] = -(partMng->m_editCameraMatrix).value[2][2];
    (partMng->m_editCameraMatrix).value[0][1] = -(partMng->m_editCameraMatrix).value[0][1];
    (partMng->m_editCameraMatrix).value[1][1] = -(partMng->m_editCameraMatrix).value[1][1];
    (partMng->m_editCameraMatrix).value[2][3] = -(partMng->m_editCameraMatrix).value[2][3];
    (partMng->m_editCameraMatrix).value[2][3] =
         (partMng->m_editCameraMatrix).value[2][3] * *(float *)partMng->m_editCameraExtra;
    PSMTXCopy(&partMng->m_editCameraMatrix,&ppvCameraMatrix0);
    C_MTXPerspective(FLOAT_8032fe4c,FLOAT_8032fe50,FLOAT_8032fe54,FLOAT_8032fe58,
                     (Mtx *)&ppvScreenMatrix);
    FLOAT_8032ed58 = ppvScreenMatrix.value[2][0];
    FLOAT_8032ed5c = ppvScreenMatrix.value[2][1];
    FLOAT_8032ed60 = ppvScreenMatrix.value[2][3];
    PSMTXCopy(&ppvCameraMatrix0,&ppvCameraMatrix0);
    PSMTX44Copy(&ppvScreenMatrix,&ppvScreenMatrix0);
    local_38 = CONCAT31(*(undefined3 *)partMng->m_rgbaA,0xff);
    local_40 = local_38;
    GXSetCopyClear(&local_40,0xffffff);
    dVar3 = (double)(float)partMng->m_fogFarRaw;
    dVar2 = (double)(float)partMng->m_fogNearRaw;
    if (partMng->m_rgbaB[0] == '\0') {
      local_54[1] = 0;
      SetFogColor__8CGraphicF8_GXColor(&Graphic,local_54 + 1);
      SetFogParam__8CGraphicFff(FLOAT_8032fe5c,FLOAT_8032fe5c,&Graphic);
    }
    else {
      local_58 = (uint)*(uint3 *)(partMng->m_rgbaB + 1) << 8;
      local_54[0] = local_58;
      SetFogColor__8CGraphicF8_GXColor(&Graphic,local_54);
      SetFogParam__8CGraphicFff((float)dVar2,(float)dVar3,&Graphic);
    }
    DAT_8032ed6c = 1;
    break;
  case 0x18:
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x7a4);
    LoadMap__7CMapPcsFiiPvUlUc
              (&MapPcs,*(undefined4 *)partMng->m_loadMapArgs,
               *(undefined4 *)(partMng->m_loadMapArgs + 4),0,0,0);
    MapPcs._384_4_ = 1;
    break;
  case 0x19:
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x7ad);
    if (*(int *)(partMng->m_usbEdit + 0x1c) != 0) {
      iVar1 = *(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8);
      if (iVar1 != 0) {
        __dt__Q29CCharaPcs7CHandleFv(iVar1,1);
        *(undefined4 *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) = 0;
      }
      if (*(int *)(partMng->m_usbEdit + 0x1c) != 0) {
        __dl__FPv();
        partMng->m_usbEdit[0x1c] = '\0';
        partMng->m_usbEdit[0x1d] = '\0';
        partMng->m_usbEdit[0x1e] = '\0';
        partMng->m_usbEdit[0x1f] = '\0';
      }
    }
    iVar1 = __nw__FUlPQ27CMemory6CStagePci
                      (0x518,PartPcs.m_usbStreamData.m_stageLoad,s_partMng_cpp_801d8230,0x7b5);
    if (iVar1 != 0) {
      *(undefined ***)(iVar1 + 0x48) = &PTR_PTR_s_CFlatRuntime_CObject_801eae88;
      *(byte *)(iVar1 + 0x38) = *(byte *)(iVar1 + 0x38) & 0xef;
      *(undefined ***)(iVar1 + 0x48) = &PTR_PTR_s_CGBaseObj_802112f4;
      *(undefined ***)(iVar1 + 0x48) = &PTR_PTR_s_CGObject_801fd360;
    }
    *(int *)(partMng->m_usbEdit + 0x1c) = iVar1;
    Create__9CGBaseObjFv(*(CGBaseObj **)(partMng->m_usbEdit + 0x1c));
    handle = (CCharaPcsCHandle *)
             __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                       (0x194,(CCharaPcsCHandle *)PartPcs.m_usbStreamData.m_stageLoad,
                        s_partMng_cpp_801d8230,0x7b7);
    if (handle != (CCharaPcsCHandle *)0x0) {
      handle = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(handle);
    }
    *(CCharaPcsCHandle **)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) = handle;
    Add__Q29CCharaPcs7CHandleFv(*(CCharaPcsCHandle **)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8));
    *(undefined4 *)(*(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) + 8) = 3;
    iVar1 = LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
                      (*(undefined4 *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8),
                       *(undefined4 *)partMng->m_loadModelArgs,
                       *(undefined4 *)(partMng->m_loadModelArgs + 4),
                       *(undefined4 *)(partMng->m_loadModelArgs + 8),0,0xffffffff,0,0);
    if ((iVar1 == 0) && (iVar1 = *(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8), iVar1 != 0))
    {
      __dt__Q29CCharaPcs7CHandleFv(iVar1,1);
      *(undefined4 *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) = 0;
    }
    break;
  case 0x1a:
    if (*(int *)(partMng->m_usbEdit + 0x1c) != 0) {
      _WaitDrawDone__8CGraphicFPci(&Graphic,s_partMng_cpp_801d8230,0x7ce);
      if (DAT_8032ed91 == '\0') {
        DAT_8032ed90 = 0;
        DAT_8032ed91 = '\x01';
      }
      LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                (*(CCharaPcsCHandle **)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8),
                 partMng->m_loadAnimName,(uint)DAT_8032ed90,0,0xffffffff,0xffffffff,0xffffffff,0);
      SetAnim__Q29CCharaPcs7CHandleFiiiii
                (*(CCharaPcsCHandle **)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8),
                 (uint)DAT_8032ed90,0xffffffff,0xffffffff,0xffffffff,0);
      DAT_8032ed90 = DAT_8032ed90 + 1;
    }
    break;
  case 0x1b:
    MapPcs._384_4_ = partMng->m_mapPcsFlag;
    break;
  case 0x1c:
    iVar1 = *(int *)(partMng->m_usbEdit + 0x1c);
    if (iVar1 != 0) {
      if (partMng->m_charaVisToggle == 0) {
        *(uint *)(*(int *)(iVar1 + 0xf8) + 8) = *(uint *)(*(int *)(iVar1 + 0xf8) + 8) & 0xfffffffe;
      }
      else {
        *(uint *)(*(int *)(iVar1 + 0xf8) + 8) = *(uint *)(*(int *)(iVar1 + 0xf8) + 8) | 1;
      }
    }
  }
  (partMng->m_pppEnvSt).m_lastEnvCmd = 0;
  return;
}

