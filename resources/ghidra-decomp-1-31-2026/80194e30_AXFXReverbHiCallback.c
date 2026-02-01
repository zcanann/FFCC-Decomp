// Function: AXFXReverbHiCallback
// Entry: 80194e30
// Size: 260 bytes

/* WARNING: Removing unreachable block (ram,0x80194e9c) */

void AXFXReverbHiCallback(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  byte bVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  if (*(char *)(param_2 + 0x1c4) == '\0') {
    uVar1 = param_1[2];
    uVar2 = param_1[1];
    uVar3 = *param_1;
    dVar7 = (double)FLOAT_80333794;
    dVar8 = (double)FLOAT_80333754;
    dVar6 = (double)FLOAT_80333750;
    for (bVar4 = 0; bVar4 < 3; bVar4 = bVar4 + 1) {
      if (bVar4 == 1) {
        HandleReverb(uVar2,param_2,1);
      }
      else if (bVar4 == 0) {
        if (dVar6 != (double)*(float *)(param_2 + 0x1a8)) {
          dVar5 = (double)(float)(dVar7 * (double)*(float *)(param_2 + 0x1a8));
          DoCrossTalk(dVar5,(double)(float)(dVar8 - dVar5),uVar3,uVar2);
        }
        HandleReverb(uVar3,param_2,0);
      }
      else if (bVar4 < 3) {
        HandleReverb(uVar1,param_2,2);
      }
    }
  }
  return;
}

