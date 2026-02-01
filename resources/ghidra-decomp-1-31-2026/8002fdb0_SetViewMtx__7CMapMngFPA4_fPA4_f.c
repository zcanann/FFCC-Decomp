// Function: SetViewMtx__7CMapMngFPA4_fPA4_f
// Entry: 8002fdb0
// Size: 188 bytes

/* WARNING: Removing unreachable block (ram,0x8002fe4c) */
/* WARNING: Removing unreachable block (ram,0x8002fe44) */
/* WARNING: Removing unreachable block (ram,0x8002fdc8) */
/* WARNING: Removing unreachable block (ram,0x8002fdc0) */

void SetViewMtx__7CMapMngFPA4_fPA4_f(CMapMng *mapMng,Mtx *viewMtx,float *param_3)

{
  double dVar1;
  double dVar2;
  
  PSMTXCopy(viewMtx,(Mtx *)&mapMng->field_0x228f8);
  dVar1 = (double)*param_3;
  dVar2 = (double)(FLOAT_8032f994 * param_3[5]);
  PSMTXScaleApply((float)((double)FLOAT_8032f990 * dVar1),FLOAT_8032f994 * param_3[5],FLOAT_8032f998
                  ,(Mtx *)&mapMng->field_0x228f8,(Mtx *)&mapMng->field_0x22928);
  PSMTXScaleApply((float)((double)FLOAT_8032f99c * dVar1),(float)dVar2,FLOAT_8032f998,
                  (Mtx *)&mapMng->field_0x228f8,(Mtx *)&mapMng->field_0x22958);
  return;
}

