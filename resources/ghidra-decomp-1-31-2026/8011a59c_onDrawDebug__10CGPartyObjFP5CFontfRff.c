// Function: onDrawDebug__10CGPartyObjFP5CFontfRff
// Entry: 8011a59c
// Size: 892 bytes

/* WARNING: Removing unreachable block (ram,0x8011a8fc) */
/* WARNING: Removing unreachable block (ram,0x8011a8f4) */
/* WARNING: Removing unreachable block (ram,0x8011a8ec) */
/* WARNING: Removing unreachable block (ram,0x8011a8e4) */
/* WARNING: Removing unreachable block (ram,0x8011a5c4) */
/* WARNING: Removing unreachable block (ram,0x8011a5bc) */
/* WARNING: Removing unreachable block (ram,0x8011a5b4) */
/* WARNING: Removing unreachable block (ram,0x8011a5ac) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDrawDebug__10CGPartyObjFP5CFontfRff
               (double param_1,double param_2,CGPartyObj *gPartyObj,CFont *font,float *param_5)

{
  float fVar1;
  uint uVar2;
  void **ppvVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  undefined auStack_168 [256];
  undefined4 local_68;
  uint uStack_64;
  undefined8 local_60;
  
  onDrawDebug__10CGCharaObjFP5CFontfRff(param_1,param_2,&gPartyObj->gCharaObj,font,param_5);
  if ((((int)((uint)*(byte *)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags << 0x18) < 0)
      && (CFlat._4780_4_ == 0)) && ((MiniGamePcs._25732_4_ & 0x80) != 0)) {
    if (((Game.game.m_gameWork.m_menuStageMode == '\0') ||
        (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
       ((uVar2 = (**(code **)((int)(gPartyObj->gCharaObj).gPrgObj.object.base_object.object.m_vtable
                             + 0xc))(gPartyObj), (uVar2 & 0x6d) != 0x6d ||
        ((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0)))) {
      ppvVar3 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
      sprintf(auStack_168,s__d__d__d__d__d__d_801dcb08,*(undefined *)(ppvVar3 + 0x2e9),
              *(undefined2 *)(ppvVar3 + 0x2f1),*(undefined2 *)((int)ppvVar3 + 0xbc6),
              *(undefined2 *)(ppvVar3 + 0x2f2),*(undefined2 *)((int)ppvVar3 + 0xbca),
              *(undefined2 *)(ppvVar3 + 0x2f3));
      dVar4 = (double)*param_5;
      dVar6 = (double)GetWidth__5CFontFPc(font,auStack_168);
      SetPosX__5CFontFf(-(float)((double)FLOAT_80331a58 * dVar6 - param_1),font);
      SetPosY__5CFontFf((float)dVar4,font);
      SetPosZ__5CFontFf((float)param_2,font);
      Draw__5CFontFPc(font,auStack_168);
    }
    else {
      switch(Game.game.m_gameWork.m_bossArtifactStageIndex) {
      default:
        uVar2 = 0;
        break;
      case 4:
      case 8:
      case 9:
      case 0xb:
      case 0xc:
      case 0xd:
        uVar2 = 2;
        break;
      case 6:
      case 10:
        uVar2 = 1;
      }
      local_68 = 0x43300000;
      uStack_64 = Chara._8276_4_ ^ 0x80000000;
      fVar1 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331a60) / FLOAT_80331a50;
      if (uVar2 == 2) {
        dVar6 = (double)(FLOAT_80331a58 * fVar1 + FLOAT_80331a58);
      }
      else if ((uVar2 < 2) && (uVar2 != 0)) {
        dVar6 = (double)(FLOAT_80331a58 * (FLOAT_80331a54 - fVar1) + FLOAT_80331a58);
      }
      else {
        dVar6 = (double)FLOAT_80331a54;
      }
      sprintf(auStack_168,s__d__d__d__d__d__d_801dcae8,m_ghostWork__10CGPartyObj._4_4_,
              Chara._8264_4_,m_ghostWork__10CGPartyObj._8_4_,Chara._8268_4_,
              m_ghostWork__10CGPartyObj._12_4_,Chara._8272_4_);
      dVar5 = (double)*param_5;
      dVar4 = (double)GetWidth__5CFontFPc(font,auStack_168);
      SetPosX__5CFontFf(-(float)((double)FLOAT_80331a58 * dVar4 - param_1),font);
      SetPosY__5CFontFf((float)dVar5,font);
      SetPosZ__5CFontFf((float)param_2,font);
      Draw__5CFontFPc(font,auStack_168);
      uStack_64 = (uint)*(ushort *)&font->field_0xa;
      dVar4 = (double)FLOAT_80331a5c;
      local_68 = 0x43300000;
      local_60 = (double)(longlong)(int)(dVar4 * dVar6);
      *param_5 = *param_5 -
                 (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_80331a68) * font->scaleY;
      sprintf(auStack_168,s__d__d_a__d_801dcafc,m_ghostWork__10CGPartyObj._24_4_,
              (int)(dVar4 * dVar6),Chara._8276_4_);
      dVar4 = (double)*param_5;
      dVar6 = (double)GetWidth__5CFontFPc(font,auStack_168);
      SetPosX__5CFontFf(-(float)((double)FLOAT_80331a58 * dVar6 - param_1),font);
      SetPosY__5CFontFf((float)dVar4,font);
      SetPosZ__5CFontFf((float)param_2,font);
      Draw__5CFontFPc(font,auStack_168);
    }
    local_60 = (double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa);
    *param_5 = *param_5 - (float)(local_60 - DOUBLE_80331a68) * font->scaleY;
  }
  return;
}

