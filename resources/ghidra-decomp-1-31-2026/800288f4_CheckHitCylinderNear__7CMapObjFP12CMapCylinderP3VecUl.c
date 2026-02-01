// Function: CheckHitCylinderNear__7CMapObjFP12CMapCylinderP3VecUl
// Entry: 800288f4
// Size: 716 bytes

void CheckHitCylinderNear__7CMapObjFP12CMapCylinderP3VecUl
               (int param_1,Vec *param_2,Vec *param_3,undefined4 param_4)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  Vec VStack_98;
  undefined local_8c [36];
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  Mtx MStack_4c;
  
  if (((*(char *)(param_1 + 0x1d) == '\x02') && (*(int *)(param_1 + 0xc) != 0)) &&
     (*(char *)(param_1 + 0x1f) == -1)) {
    PSMTXInverse((Mtx *)(param_1 + 0xb8),&MStack_4c);
    local_5c = FLOAT_8032f938;
    local_60 = FLOAT_8032f938;
    local_64 = FLOAT_8032f938;
    local_50 = FLOAT_8032f93c;
    local_54 = FLOAT_8032f93c;
    local_58 = FLOAT_8032f93c;
    PSMTXMultVec(&MStack_4c,param_2,(Vec *)local_8c);
    PSMTXMultVec(&MStack_4c,param_2 + 1,(Vec *)(local_8c + 0xc));
    local_68 = param_2[3].x;
    local_64 = (float)local_8c._12_4_;
    if ((float)local_8c._0_4_ < (float)local_8c._12_4_) {
      local_64 = (float)local_8c._0_4_;
      local_8c._0_4_ = local_8c._12_4_;
    }
    local_58 = (float)local_8c._0_4_ + FLOAT_8032f940 + local_68;
    local_64 = local_64 - (FLOAT_8032f940 + local_68);
    local_60 = (float)local_8c._16_4_;
    if ((float)local_8c._4_4_ < (float)local_8c._16_4_) {
      local_60 = (float)local_8c._4_4_;
      local_8c._4_4_ = local_8c._16_4_;
    }
    local_54 = (float)local_8c._4_4_ + FLOAT_8032f940 + local_68;
    local_60 = local_60 - (FLOAT_8032f940 + local_68);
    local_5c = (float)local_8c._20_4_;
    if ((float)local_8c._8_4_ < (float)local_8c._20_4_) {
      local_5c = (float)local_8c._8_4_;
      local_8c._8_4_ = local_8c._20_4_;
    }
    local_50 = (float)local_8c._8_4_ + FLOAT_8032f940 + local_68;
    local_5c = local_5c - (FLOAT_8032f940 + local_68);
    iVar5 = *(int *)(param_1 + 0xc);
    bVar2 = false;
    bVar4 = false;
    fVar1 = *(float *)(iVar5 + 4);
    if (local_64 <= fVar1) {
      if (fVar1 <= local_64) {
        bVar3 = true;
      }
      else {
        bVar3 = fVar1 <= local_58;
      }
    }
    else {
      bVar3 = local_64 <= *(float *)(iVar5 + 0x10);
    }
    if (bVar3) {
      fVar1 = *(float *)(iVar5 + 8);
      if (local_60 <= fVar1) {
        if (fVar1 <= local_60) {
          bVar3 = true;
        }
        else {
          bVar3 = fVar1 <= local_54;
        }
      }
      else {
        bVar3 = local_60 <= *(float *)(iVar5 + 0x14);
      }
      if (bVar3) {
        bVar4 = true;
      }
    }
    if (bVar4) {
      fVar1 = *(float *)(iVar5 + 0xc);
      if (local_5c <= fVar1) {
        if (fVar1 <= local_5c) {
          bVar4 = true;
        }
        else {
          bVar4 = fVar1 <= local_50;
        }
      }
      else {
        bVar4 = local_5c <= *(float *)(iVar5 + 0x18);
      }
      if (bVar4) {
        bVar2 = true;
      }
    }
    if (bVar2) {
      PSMTXMultVecSR(&MStack_4c,param_2 + 2,(Vec *)(local_8c + 0x18));
      PSMTXMultVecSR(&MStack_4c,param_3,&VStack_98);
      CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUl
                (*(undefined4 *)(param_1 + 0xc),(CMapCylinder *)local_8c,&VStack_98,param_4);
    }
  }
  return;
}

