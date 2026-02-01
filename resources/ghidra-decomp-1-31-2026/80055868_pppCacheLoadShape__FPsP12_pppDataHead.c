// Function: pppCacheLoadShape__FPsP12_pppDataHead
// Entry: 80055868
// Size: 108 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppCacheLoadShape__FPsP12_pppDataHead(short *param_1,_pppDataHead *pppDataHead)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  short sVar4;
  
  psVar3 = param_1 + 1;
  sVar1 = *param_1;
  for (sVar4 = 0; sVar4 < sVar1; sVar4 = sVar4 + 1) {
    sVar2 = *psVar3;
    psVar3 = psVar3 + 1;
    pppCacheLoadShapeTexture__FP10pppShapeStP12CMaterialSet
              (*(pppShapeSt **)(pppDataHead->m_shapeNames + sVar2 * 4),PartMng.m_materialSet);
  }
  return;
}

