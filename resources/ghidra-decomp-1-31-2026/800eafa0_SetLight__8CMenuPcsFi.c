// Function: SetLight__8CMenuPcsFi
// Entry: 800eafa0
// Size: 232 bytes

void SetLight__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int local_28;
  undefined4 local_24 [4];
  
  SetFog__8CGraphicFii(&Graphic,1,0);
  local_24[0] = (&DAT_80210830)[param_2 * 0xe];
  SetAmbient__9CLightPcsF8_GXColor(&LightPcs,local_24);
  piVar2 = &DAT_8021082c + param_2 * 0xe;
  SetNumDiffuse__9CLightPcsFUl(&LightPcs,*piVar2);
  piVar3 = piVar2;
  piVar4 = piVar2;
  for (iVar1 = 0; iVar1 < *piVar2; iVar1 = iVar1 + 1) {
    local_28 = piVar4[2];
    SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(&LightPcs,iVar1,&local_28,piVar3 + 5,0);
    piVar4 = piVar4 + 1;
    piVar3 = piVar3 + 3;
  }
  SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs,0,0,0xffffffff);
  return;
}

