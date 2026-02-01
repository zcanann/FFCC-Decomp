// Function: onDrawDebug__10CGCharaObjFP5CFontfRff
// Entry: 8010c1a8
// Size: 328 bytes

/* WARNING: Removing unreachable block (ram,0x8010c2d0) */
/* WARNING: Removing unreachable block (ram,0x8010c2c8) */
/* WARNING: Removing unreachable block (ram,0x8010c2c0) */
/* WARNING: Removing unreachable block (ram,0x8010c1c8) */
/* WARNING: Removing unreachable block (ram,0x8010c1c0) */
/* WARNING: Removing unreachable block (ram,0x8010c1b8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDrawDebug__10CGCharaObjFP5CFontfRff
               (double param_1,double param_2,CGCharaObj *gCharaObj,CFont *font,float *param_5)

{
  void **ppvVar1;
  double dVar2;
  double dVar3;
  undefined auStack_148 [272];
  
  if ((((int)((uint)*(byte *)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags << 0x18) < 0) &&
      (CFlat._4780_4_ == 0)) && ((MiniGamePcs._25732_4_ & 0x80) != 0)) {
    ppvVar1 = (gCharaObj->gPrgObj).object.m_scriptHandle;
    sprintf(auStack_148,s__d__d__d__d__d_801dc5ac,*(undefined2 *)(ppvVar1 + 7),
            *(undefined2 *)((int)ppvVar1 + 0x1a),*(undefined2 *)((int)ppvVar1 + 0x1e),
            *(undefined2 *)(ppvVar1 + 8),*(undefined2 *)((int)ppvVar1 + 0x22));
    dVar3 = (double)*param_5;
    dVar2 = (double)GetWidth__5CFontFPc(font,auStack_148);
    SetPosX__5CFontFf(-(float)((double)FLOAT_80331970 * dVar2 - param_1),font);
    SetPosY__5CFontFf((float)dVar3,font);
    SetPosZ__5CFontFf((float)param_2,font);
    Draw__5CFontFPc(font,auStack_148);
    *param_5 = *param_5 -
               (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa) -
                      DOUBLE_80331978) * font->scaleY;
  }
  return;
}

