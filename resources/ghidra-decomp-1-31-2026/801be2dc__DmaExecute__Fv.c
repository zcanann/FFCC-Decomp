// Function: _DmaExecute__Fv
// Entry: 801be2dc
// Size: 496 bytes

void _DmaExecute__Fv(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  
  do {
    do {
      if ((DAT_8032f3e0 == DAT_8032f3e8) && (iRam8032f3e4 == iRam8032f3ec)) {
        DAT_8032f488 = 0;
        return;
      }
      if (DAT_8032f3e0 == DAT_8032f3e8) {
        puVar5 = (undefined4 *)0x8032f3ec;
        piVar4 = (int *)&DAT_8032c660;
      }
      else {
        puVar5 = &DAT_8032f3e8;
        piVar4 = &DAT_8032b860;
      }
      piVar7 = (int *)*puVar5;
      DAT_8032f488 = 2;
      piVar6 = (int *)0x0;
      if (*piVar7 != 0) {
        DAT_8032f468 = 1;
        if (piVar7[1] == 0) {
          DCFlushRange(piVar7[2],piVar7[4]);
          iVar3 = piVar7[2];
          iVar2 = piVar7[3];
        }
        else {
          DCInvalidateRange(piVar7[2],piVar7[4]);
          iVar3 = piVar7[3];
          iVar2 = piVar7[2];
        }
        DAT_8032f488 = 3;
        ARQSetChunkSize(piVar7[4]);
        ARQPostRequest(&DAT_8032dde4,0x469,piVar7[1],1,iVar3,iVar2,piVar7[4],_DmaCallback__FUl);
        piVar6 = piVar7;
      }
      piVar8 = piVar7 + 7;
      if (piVar4 + 0x380 <= piVar7 + 7) {
        piVar8 = piVar4;
      }
      *puVar5 = piVar8;
    } while (piVar6 == (int *)0x0);
    while (piVar6 != (int *)0x0) {
      DAT_8032f488 = 7;
      if (DAT_8032f468 == 0) {
        DAT_8032f488 = 8;
        if (piVar6[5] != 0) {
          uVar1 = OSDisableInterrupts();
          (*(code *)piVar6[5])(piVar6[6]);
          OSRestoreInterrupts(uVar1);
        }
        DAT_8032f488 = 9;
        if (piVar6[1] == 1) {
          DCFlushRange(piVar6[2],piVar6[4]);
        }
        *piVar6 = 0;
        break;
      }
      RedSleep__Fi(0);
    }
  } while( true );
}

