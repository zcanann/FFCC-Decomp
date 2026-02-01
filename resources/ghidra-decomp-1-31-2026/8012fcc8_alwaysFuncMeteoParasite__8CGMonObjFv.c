// Function: alwaysFuncMeteoParasite__8CGMonObjFv
// Entry: 8012fcc8
// Size: 796 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void alwaysFuncMeteoParasite__8CGMonObjFv(CGMonObj *gMonObj)

{
  int *piVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  void *pvVar14;
  int iVar15;
  
  pvVar14 = (gMonObj->gObject).m_scriptHandle[4];
  if ((pvVar14 == (void *)0x85) &&
     (-1 < (int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x19 |
                (uint)((byte)m_boss__8CGMonObj._92_1_ >> 7)))) {
    if (DAT_8032eea4 == '\0') {
      DAT_8032eea4 = '\x01';
      FLOAT_8032eea0 = FLOAT_80331cf8;
    }
    PSMTXRotRad(FLOAT_8032eea0,SoundBuffer._1260_4_ + 0x14,0x78);
    PSMTXRotRad(-FLOAT_8032eea0,SoundBuffer._1264_4_ + 0x14,0x78);
    fVar5 = FLOAT_80331d5c;
    fVar4 = FLOAT_80331d58;
    dVar3 = DOUBLE_80331d38;
    fVar2 = FLOAT_80331d2c;
    iVar12 = -0x7fcffeb4;
    iVar13 = 0;
    iVar15 = 2;
    do {
      uVar6 = iVar13 + 3;
      uVar10 = iVar13 + 4;
      uVar7 = iVar13 + 5;
      uVar11 = iVar13 + 7;
      uVar8 = iVar13 + 6;
      uVar9 = iVar13 + 8;
      iVar13 = iVar13 + 6;
      *(float *)(*(int *)(iVar12 + 0x38) + 0x1b4) =
           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - dVar3)) /
           fVar5 + FLOAT_8032eea0;
      *(float *)(*(int *)(iVar12 + 0x3c) + 0x1b4) =
           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - dVar3)) /
           fVar5 + FLOAT_8032eea0;
      *(float *)(*(int *)(iVar12 + 0x40) + 0x1b4) =
           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar7 ^ 0x80000000) - dVar3)) /
           fVar5 + FLOAT_8032eea0;
      *(float *)(*(int *)(iVar12 + 0x44) + 0x1b4) =
           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar8 ^ 0x80000000) - dVar3)) /
           fVar5 + FLOAT_8032eea0;
      *(float *)(*(int *)(iVar12 + 0x48) + 0x1b4) =
           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar11 ^ 0x80000000) - dVar3)) /
           fVar5 + FLOAT_8032eea0;
      piVar1 = (int *)(iVar12 + 0x4c);
      iVar12 = iVar12 + 0x18;
      *(float *)(*piVar1 + 0x1b4) =
           (fVar4 * fVar2 * (float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - dVar3)) /
           fVar5 + FLOAT_8032eea0;
      iVar15 = iVar15 + -1;
    } while (iVar15 != 0);
    FLOAT_8032eea0 = FLOAT_8032eea0 + FLOAT_80331d60;
  }
  if (((((int)pvVar14 < 0x88) && (0x84 < (int)pvVar14)) &&
      (m_boss__8CGMonObj._88_4_ == (int)pvVar14 + -0x85)) &&
     (((int)((uint)(byte)m_boss__8CGMonObj._92_1_ << 0x18) < 0 &&
      (iVar12 = _getItemPdt__10CGCharaObjFiiRiRiRi(gMonObj), iVar12 != 0)))) {
    if (m_boss__8CGMonObj._96_4_ == 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,100,0,0);
      gMonObj->_bossBranchRelated = 0;
    }
    if (m_boss__8CGMonObj._96_4_ == 2) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x65,0,0);
      gMonObj->_bossBranchRelated = 2;
    }
    if (m_boss__8CGMonObj._96_4_ == 1) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x66,0,0);
      gMonObj->_bossBranchRelated = 1;
    }
    m_boss__8CGMonObj._92_1_ = m_boss__8CGMonObj._92_1_ & 0x7f;
  }
  return;
}

