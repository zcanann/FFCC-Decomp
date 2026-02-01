// Function: onDrawDebug__8CGMonObjFP5CFontfRff
// Entry: 8011740c
// Size: 644 bytes

/* WARNING: Removing unreachable block (ram,0x80117668) */
/* WARNING: Removing unreachable block (ram,0x80117660) */
/* WARNING: Removing unreachable block (ram,0x80117658) */
/* WARNING: Removing unreachable block (ram,0x8011742c) */
/* WARNING: Removing unreachable block (ram,0x80117424) */
/* WARNING: Removing unreachable block (ram,0x8011741c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDrawDebug__8CGMonObjFP5CFontfRff
               (double param_1,CGMonObj *gMonObj,CGCharaObj *param_3,CFont *font,float *param_5)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  double dVar5;
  undefined4 in_register_00004010;
  double dVar6;
  double dVar7;
  undefined auStack_178 [256];
  undefined4 local_78;
  uint uStack_74;
  longlong local_70;
  undefined4 local_68;
  uint uStack_64;
  longlong local_60;
  longlong local_58;
  
  dVar6 = (double)CONCAT44(in_register_00004010,gMonObj);
  onDrawDebug__10CGCharaObjFP5CFontfRff(param_1,dVar6,param_3,font,param_5);
  if ((((int)((uint)*(byte *)&(param_3->gPrgObj).object.m_weaponNodeFlags << 0x18) < 0) &&
      (CFlat._4780_4_ == 0)) && ((MiniGamePcs._25732_4_ & 0x80) != 0)) {
    iVar4 = 0x2d;
    uVar2 = *(ushort *)&param_3[1].gPrgObj.object.base_object.object.m_id;
    if (-1 < *(int *)&param_3->field_0x6c4) {
      iVar4 = *(int *)&param_3->field_0x6c4 + 0x30;
    }
    sVar3 = 0x2d;
    if ((uVar2 & 0x7fff) != 0) {
      sVar3 = (uVar2 & 0x7fff) + 0x40;
    }
    sprintf(auStack_178,s__d__c__d__c_801dca2c,(param_3->gPrgObj).object.m_scriptHandle[2],sVar3,
            param_3[1].gPrgObj.object.base_object.object.m_freeListNode,iVar4);
    dVar7 = (double)*param_5;
    dVar5 = (double)GetWidth__5CFontFPc(font,auStack_178);
    SetPosX__5CFontFf(-(float)((double)FLOAT_80331a34 * dVar5 - param_1),font);
    SetPosY__5CFontFf((float)dVar7,font);
    SetPosZ__5CFontFf((float)dVar6,font);
    Draw__5CFontFPc(font,auStack_178);
    uStack_74 = (uint)*(ushort *)&font->field_0xa;
    local_78 = 0x43300000;
    *param_5 = *param_5 -
               (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_803319e0) * font->scaleY;
    if (*(int *)&param_3->field_0x6c4 < 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = (int)*(float *)(&param_3->field_0x5d0 + *(int *)&param_3->field_0x6c4 * 4);
      local_70 = (longlong)iVar4;
    }
    local_68 = 0x43300000;
    uStack_64 = (uint)*(ushort *)((int)(param_3->gPrgObj).object.m_scriptHandle[9] + 0xcc);
    iVar1 = (int)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_803319e0);
    local_60 = (longlong)iVar1;
    dVar5 = (double)PSVECDistance((Vec *)&param_3[1].gPrgObj.object.base_object.object.m_next,
                                  &(param_3->gPrgObj).object.m_worldPosition);
    local_58 = (longlong)(int)dVar5;
    sprintf(auStack_178,s__d__d__d_801dca38,iVar4,(int)dVar5,iVar1);
    dVar7 = (double)*param_5;
    dVar5 = (double)GetWidth__5CFontFPc(font,auStack_178);
    SetPosX__5CFontFf(-(float)((double)FLOAT_80331a34 * dVar5 - param_1),font);
    SetPosY__5CFontFf((float)dVar7,font);
    SetPosZ__5CFontFf((float)dVar6,font);
    Draw__5CFontFPc(font,auStack_178);
    *param_5 = *param_5 -
               (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa) -
                      DOUBLE_803319e0) * font->scaleY;
  }
  return;
}

