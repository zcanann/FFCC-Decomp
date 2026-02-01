// Function: ReWriteDisplayList__5CUtilFPvUlUl
// Entry: 80022b80
// Size: 292 bytes

void ReWriteDisplayList__5CUtilFPvUlUl(CUtil *util,byte *param_2,int param_3,uint param_4)

{
  byte bVar1;
  undefined2 uVar2;
  bool bVar3;
  byte bVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  
  pbVar5 = param_2;
  while (pbVar5 < param_2 + param_3) {
    bVar1 = *pbVar5;
    uVar7 = (uint)*(ushort *)(pbVar5 + 1);
    pbVar5 = pbVar5 + 3;
    bVar4 = bVar1 & 0xf8;
    if (bVar4 == 0xa0) {
LAB_80022c08:
      bVar3 = true;
    }
    else {
      if (0x9f < bVar4) {
        if (bVar4 != 0xb0) {
          if (bVar4 < 0xb0) {
            if (bVar4 == 0xa8) goto LAB_80022c08;
          }
          else if (bVar4 == 0xb8) goto LAB_80022c08;
          goto LAB_80022c10;
        }
        goto LAB_80022c08;
      }
      if (bVar4 == 0x90) goto LAB_80022c08;
      if (bVar4 < 0x90) {
        if (bVar4 == 0x80) goto LAB_80022c08;
      }
      else if (bVar4 == 0x98) goto LAB_80022c08;
LAB_80022c10:
      bVar3 = false;
    }
    if (!bVar3) break;
    for (; uVar7 != 0; uVar7 = uVar7 - 1) {
      uVar2 = *(undefined2 *)pbVar5;
      if ((param_4 & 1) != 0) {
        *(undefined2 *)(pbVar5 + 4) = uVar2;
      }
      if ((param_4 & 2) != 0) {
        *(undefined2 *)(pbVar5 + 6) = uVar2;
      }
      pbVar6 = pbVar5 + 8;
      if ((bVar1 & 7) == 2) {
        if ((param_4 & 2) == 0) {
          pbVar6 = pbVar5 + 10;
        }
        else {
          *(undefined2 *)pbVar6 = uVar2;
          pbVar6 = pbVar5 + 10;
        }
      }
      pbVar5 = pbVar6;
    }
  }
  DCFlushRange(param_2,param_3);
  return;
}

