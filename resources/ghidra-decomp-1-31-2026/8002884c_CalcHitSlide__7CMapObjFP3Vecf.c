// Function: CalcHitSlide__7CMapObjFP3Vecf
// Entry: 8002884c
// Size: 92 bytes

undefined4 CalcHitSlide__7CMapObjFP3Vecf(CMapObj *mapObj,Vec *param_2)

{
  undefined4 uVar1;
  undefined8 in_f1;
  
  uVar1 = CalcHitSlide__7CMapHitFP3Vecf(in_f1,mapObj->field12_0xc,param_2);
  PSMTXMultVecSR((Mtx *)&mapObj->field_0xb8,param_2,param_2);
  return uVar1;
}

