// Function: onFrameAlways__8CGMonObjFv
// Entry: 801143d0
// Size: 512 bytes

/* WARNING: Removing unreachable block (ram,0x801145a8) */
/* WARNING: Removing unreachable block (ram,0x801143e0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrameAlways__8CGMonObjFv(CGMonObj *gMonObj)

{
  ushort uVar1;
  void **ppvVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  
  ppvVar2 = (gMonObj->gObject).m_scriptHandle;
  if (ppvVar2 != (void **)0x0) {
    if ((*(ushort *)((int)ppvVar2[9] + 0xfe) & 4) != 0) {
      cVar6 = '\0';
      if (gMonObj->field_0x6b9 == '\0') {
        dVar9 = (double)FLOAT_803319f8;
        iVar7 = -0x7fde1140;
        iVar5 = 0;
        do {
          iVar3 = *(int *)(iVar7 + 0xc5b0);
          if (((iVar3 != 0) && (*(int *)(iVar3 + 0x668) != 0)) &&
             (dVar8 = (double)PSVECDistance((Vec *)(iVar3 + 0x66c),
                                            &(gMonObj->gObject).m_worldPosition),
             dVar8 < (double)(float)(dVar9 + (double)(gMonObj->gObject).m_bodyEllipsoidRadius))) {
            cVar6 = '\x01';
            break;
          }
          iVar5 = iVar5 + 1;
          iVar7 = iVar7 + 4;
        } while (iVar5 < 4);
      }
      if (cVar6 != gMonObj->field_0x6c3) {
        if (((*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfe) & 4) != 0) &&
           (endPSlotBit__10CGCharaObjFi(gMonObj,0x200000), cVar6 != '\0')) {
          putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                    ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,0x146,*(int *)&gMonObj->field_0x5b8,
                     &gMonObj->gObject,0);
        }
        gMonObj->field_0x6c3 = cVar6;
      }
    }
    CalcStatus__8CMonWorkFv((CMonWork *)(gMonObj->gObject).m_scriptHandle);
    __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
    uVar1 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1be);
    if (uVar1 == 0xffff) {
      iVar5 = 0;
    }
    else {
      iVar5 = (uVar1 & 0xff) + (uint)(uVar1 >> 8) * 1000;
    }
    if (iVar5 != 0) {
      if ((gMonObj->gObject).m_currentAnimSlot == *(char *)&(gMonObj->gObject).m_animStartFrame) {
        if (*(int *)&gMonObj->field_0x704 == 0) {
          uVar4 = playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,iVar5,0x32,0x96,0,0);
          *(undefined4 *)&gMonObj->field_0x704 = uVar4;
        }
        else {
          ChangeSe3DPos__6CSoundFiP3Vec
                    (&Sound,*(int *)&gMonObj->field_0x704,&(gMonObj->gObject).m_worldPosition);
        }
      }
      else if (*(int *)&gMonObj->field_0x704 != 0) {
        FadeOutSe3D__6CSoundFii(&Sound,*(int *)&gMonObj->field_0x704,0x32);
        *(undefined4 *)&gMonObj->field_0x704 = 0;
      }
    }
  }
  return;
}

