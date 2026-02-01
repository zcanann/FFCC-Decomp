// Function: DrawOmoideName__9CGItemObjFP5CFont
// Entry: 80124e04
// Size: 424 bytes

/* WARNING: Removing unreachable block (ram,0x80124f88) */
/* WARNING: Removing unreachable block (ram,0x80124f80) */
/* WARNING: Removing unreachable block (ram,0x80124e1c) */
/* WARNING: Removing unreachable block (ram,0x80124e14) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawOmoideName__9CGItemObjFP5CFont(CGItemObj *gItemObj,CFont *font)

{
  int iVar1;
  byte bVar2;
  float fVar3;
  bool bVar4;
  undefined4 *puVar5;
  CCharaPcsCHandle *pCVar6;
  int32_t iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  undefined auStack_48 [4];
  undefined4 local_44;
  longlong local_40;
  
  bVar2 = *(byte *)&(gItemObj->prgObj).object.m_weaponNodeFlags;
  if ((int)((uint)bVar2 << 0x1a | (uint)(bVar2 >> 6)) < 0) {
    pCVar6 = (gItemObj->prgObj).object.m_charaModelHandle;
    bVar4 = false;
    if ((pCVar6 != (CCharaPcsCHandle *)0x0) && (pCVar6->m_model != (CModel *)0x0)) {
      bVar4 = true;
    }
    if ((((bVar4) && ((gItemObj->prgObj).object.m_worldParamA == 2.84464e-43)) &&
        (FLOAT_80331b20 < (gItemObj->prgObj).object.m_screenDepth)) &&
       (FLOAT_80331b20 != (gItemObj->prgObj).object.m_lookAtTimer)) {
      SetTlut__5CFontFi(font,7);
      iVar1 = (int)(FLOAT_80331b30 * (gItemObj->prgObj).object.m_lookAtTimer);
      local_40 = (longlong)iVar1;
      puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_48,0xff,0xff,0xff,iVar1);
      local_44 = *puVar5;
      SetColor__5CFontF8_GXColor(font,&local_44);
      iVar7 = Game.game.m_cFlatDataArr[1].m_table[2].index[*(int *)&gItemObj->field_0x570];
      dVar8 = (double)GetWidth__5CFontFPc(font,iVar7);
      fVar3 = FLOAT_80331b18 / ((gItemObj->prgObj).object.m_screenDepth - FLOAT_80331b1c);
      dVar9 = (double)((gItemObj->prgObj).object.m_projection.w * fVar3);
      dVar10 = -(double)(FLOAT_80331b34 * (gItemObj->prgObj).object.m_projection.z * fVar3 -
                        FLOAT_80331b34);
      SetPosX__5CFontFf(-(float)((double)FLOAT_80331b3c * dVar8 -
                                (double)(FLOAT_80331b38 * (gItemObj->prgObj).object.m_projection.y *
                                         fVar3 + FLOAT_80331b38)),font);
      SetPosY__5CFontFf((float)(dVar10 - (double)FLOAT_80331b40),font);
      SetPosZ__5CFontFf((float)dVar9,font);
      Draw__5CFontFPc(font,iVar7);
    }
  }
  return;
}

