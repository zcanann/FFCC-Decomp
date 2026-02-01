// Function: CalcMtx__7CMapObjFPA4_fUc
// Entry: 8002a258
// Size: 856 bytes

void CalcMtx__7CMapObjFPA4_fUc(CMapObj *mapObj,Mtx *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  Mtx MStack_b8;
  Mtx MStack_88;
  Mtx MStack_58;
  
  do {
    uVar4 = param_3;
    if (mapObj->field_0x1b != '\0') {
      mapObj->field_0x1b = 0;
      if (mapObj->field_0x1c != '\0') {
        PSMTXScale(*(float *)&mapObj->field_0x7c,*(float *)&mapObj->field_0x80,
                   *(float *)&mapObj->field_0x84,&mapObj->localMtx);
        PSMTXRotRad(FLOAT_8032f950 * *(float *)&mapObj->field_0x70,&MStack_58,0x78);
        PSMTXConcat(&MStack_58,&mapObj->localMtx,&mapObj->localMtx);
        PSMTXRotRad(FLOAT_8032f950 * *(float *)&mapObj->field_0x74,&MStack_58,0x79);
        PSMTXConcat(&MStack_58,&mapObj->localMtx,&mapObj->localMtx);
        PSMTXRotRad(FLOAT_8032f950 * *(float *)&mapObj->field_0x78,&MStack_58,0x7a);
        PSMTXConcat(&MStack_58,&mapObj->localMtx,&mapObj->localMtx);
        PSMTXTrans(mapObj->drawRange,*(float *)&mapObj->field_0x68,*(float *)&mapObj->field_0x6c,
                   &MStack_58);
        PSMTXConcat(&MStack_58,&mapObj->localMtx,&mapObj->localMtx);
      }
      uVar4 = 1;
    }
    if ((uVar4 & 0xff) != 0) {
      PSMTXConcat(param_2,&mapObj->localMtx,(Mtx *)&mapObj->field_0xb8);
    }
    for (iVar5 = *(int *)&mapObj->field_0x4; iVar5 != 0; iVar5 = *(int *)(iVar5 + 8)) {
      uVar3 = uVar4;
      if (*(char *)(iVar5 + 0x1b) != '\0') {
        *(undefined *)(iVar5 + 0x1b) = 0;
        if (*(char *)(iVar5 + 0x1c) != '\0') {
          PSMTXScale(*(float *)(iVar5 + 0x7c),*(float *)(iVar5 + 0x80),*(float *)(iVar5 + 0x84),
                     (Mtx *)(iVar5 + 0x88));
          PSMTXRotRad(FLOAT_8032f950 * *(float *)(iVar5 + 0x70),&MStack_88,0x78);
          PSMTXConcat(&MStack_88,(Mtx *)(iVar5 + 0x88),(Mtx *)(iVar5 + 0x88));
          PSMTXRotRad(FLOAT_8032f950 * *(float *)(iVar5 + 0x74),&MStack_88,0x79);
          PSMTXConcat(&MStack_88,(Mtx *)(iVar5 + 0x88),(Mtx *)(iVar5 + 0x88));
          PSMTXRotRad(FLOAT_8032f950 * *(float *)(iVar5 + 0x78),&MStack_88,0x7a);
          PSMTXConcat(&MStack_88,(Mtx *)(iVar5 + 0x88),(Mtx *)(iVar5 + 0x88));
          PSMTXTrans(*(float *)(iVar5 + 100),*(float *)(iVar5 + 0x68),*(float *)(iVar5 + 0x6c),
                     &MStack_88);
          PSMTXConcat(&MStack_88,(Mtx *)(iVar5 + 0x88),(Mtx *)(iVar5 + 0x88));
        }
        uVar3 = 1;
      }
      if ((uVar3 & 0xff) != 0) {
        PSMTXConcat((Mtx *)&mapObj->field_0xb8,(Mtx *)(iVar5 + 0x88),(Mtx *)(iVar5 + 0xb8));
      }
      iVar1 = *(int *)(iVar5 + 4);
      if (iVar1 != 0) {
        do {
          uVar2 = uVar3;
          if (*(char *)(iVar1 + 0x1b) != '\0') {
            *(undefined *)(iVar1 + 0x1b) = 0;
            if (*(char *)(iVar1 + 0x1c) != '\0') {
              PSMTXScale(*(float *)(iVar1 + 0x7c),*(float *)(iVar1 + 0x80),*(float *)(iVar1 + 0x84),
                         (Mtx *)(iVar1 + 0x88));
              PSMTXRotRad(FLOAT_8032f950 * *(float *)(iVar1 + 0x70),&MStack_b8,0x78);
              PSMTXConcat(&MStack_b8,(Mtx *)(iVar1 + 0x88),(Mtx *)(iVar1 + 0x88));
              PSMTXRotRad(FLOAT_8032f950 * *(float *)(iVar1 + 0x74),&MStack_b8,0x79);
              PSMTXConcat(&MStack_b8,(Mtx *)(iVar1 + 0x88),(Mtx *)(iVar1 + 0x88));
              PSMTXRotRad(FLOAT_8032f950 * *(float *)(iVar1 + 0x78),&MStack_b8,0x7a);
              PSMTXConcat(&MStack_b8,(Mtx *)(iVar1 + 0x88),(Mtx *)(iVar1 + 0x88));
              PSMTXTrans(*(float *)(iVar1 + 100),*(float *)(iVar1 + 0x68),*(float *)(iVar1 + 0x6c),
                         &MStack_b8);
              PSMTXConcat(&MStack_b8,(Mtx *)(iVar1 + 0x88),(Mtx *)(iVar1 + 0x88));
            }
            uVar2 = 1;
          }
          if ((uVar2 & 0xff) != 0) {
            PSMTXConcat((Mtx *)(iVar5 + 0xb8),(Mtx *)(iVar1 + 0x88),(Mtx *)(iVar1 + 0xb8));
          }
          if (*(CMapObj **)(iVar1 + 4) != (CMapObj *)0x0) {
            CalcMtx__7CMapObjFPA4_fUc(*(CMapObj **)(iVar1 + 4),(Mtx *)(iVar1 + 0xb8),uVar2);
          }
          iVar1 = *(int *)(iVar1 + 8);
        } while (iVar1 != 0);
      }
    }
    mapObj = *(CMapObj **)&mapObj->field_0x8;
  } while (mapObj != (CMapObj *)0x0);
  return;
}

