// Function: SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj
// Entry: 800330cc
// Size: 80 bytes

int * SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(CMapMng *mapMng,int *param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = (uint)((int)(mapMng->mapObjArr + mapMng->field10_0xc) + (0xef - (int)param_2)) / 0xf0;
  if (param_2 < mapMng->mapObjArr + mapMng->field10_0xc) {
    do {
      if (*param_2 == param_3) {
        return param_2;
      }
      param_2 = param_2 + 0x3c;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  return (int *)0x0;
}

