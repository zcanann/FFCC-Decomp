// Function: SetLink__7CMapObjFv
// Entry: 80029d18
// Size: 672 bytes

void SetLink__7CMapObjFv(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int local_94;
  int local_90;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  
  local_94 = 0;
  local_90 = -0x7fdb9f48;
  local_88 = -0x7fdb9f48;
  local_84 = -0x7fdb9f48;
  local_80 = -0x7fdb9f48;
  local_7c = -0x7fdb9f48;
  local_78 = -0x7fdb9f48;
  while( true ) {
    iVar9 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,local_90,param_1);
    if (iVar9 == 0) break;
    *(int *)(iVar9 + 8) = local_94;
    local_70 = -0x7fdb9f48;
    local_6c = 0;
    while( true ) {
      iVar8 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,local_70,iVar9);
      if (iVar8 == 0) break;
      *(int *)(iVar8 + 8) = local_6c;
      local_74 = 0;
      iVar11 = local_88;
      while( true ) {
        iVar7 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,iVar11,iVar8);
        if (iVar7 == 0) break;
        *(int *)(iVar7 + 8) = local_74;
        iVar11 = local_84;
        iVar10 = 0;
        while( true ) {
          iVar6 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,iVar11,iVar7);
          if (iVar6 == 0) break;
          *(int *)(iVar6 + 8) = iVar10;
          iVar11 = local_80;
          iVar10 = 0;
          while( true ) {
            iVar5 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,iVar11,iVar6);
            if (iVar5 == 0) break;
            *(int *)(iVar5 + 8) = iVar10;
            iVar11 = local_7c;
            iVar10 = 0;
            while( true ) {
              iVar4 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,iVar11,iVar5);
              if (iVar4 == 0) break;
              *(int *)(iVar4 + 8) = iVar10;
              iVar11 = local_78;
              iVar10 = 0;
              while( true ) {
                iVar3 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,iVar11,iVar4);
                if (iVar3 == 0) break;
                *(int *)(iVar3 + 8) = iVar10;
                iVar11 = -0x7fdb9f48;
                iVar10 = 0;
                while( true ) {
                  iVar2 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,iVar11,iVar3);
                  if (iVar2 == 0) break;
                  *(int *)(iVar2 + 8) = iVar10;
                  iVar11 = -0x7fdb9f48;
                  iVar10 = 0;
                  while( true ) {
                    iVar1 = SearchChildMapObj__7CMapMngFP7CMapObjP7CMapObj(&MapMng,iVar11,iVar2);
                    if (iVar1 == 0) break;
                    *(int *)(iVar1 + 8) = iVar10;
                    SetLink__7CMapObjFv(iVar1);
                    iVar11 = iVar1 + 0xf0;
                    iVar10 = iVar1;
                  }
                  *(int *)(iVar2 + 4) = iVar10;
                  iVar11 = iVar2 + 0xf0;
                  iVar10 = iVar2;
                }
                *(int *)(iVar3 + 4) = iVar10;
                iVar11 = iVar3 + 0xf0;
                iVar10 = iVar3;
              }
              *(int *)(iVar4 + 4) = iVar10;
              iVar11 = iVar4 + 0xf0;
              iVar10 = iVar4;
            }
            *(int *)(iVar5 + 4) = iVar10;
            iVar11 = iVar5 + 0xf0;
            iVar10 = iVar5;
          }
          *(int *)(iVar6 + 4) = iVar10;
          iVar11 = iVar6 + 0xf0;
          iVar10 = iVar6;
        }
        *(int *)(iVar7 + 4) = iVar10;
        iVar11 = iVar7 + 0xf0;
        local_74 = iVar7;
      }
      *(int *)(iVar8 + 4) = local_74;
      local_70 = iVar8 + 0xf0;
      local_6c = iVar8;
    }
    *(int *)(iVar9 + 4) = local_6c;
    local_90 = iVar9 + 0xf0;
    local_94 = iVar9;
  }
  *(int *)(param_1 + 4) = local_94;
  return;
}

