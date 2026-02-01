// Function: Add3DLine__6CSoundFiP3Vec
// Entry: 800c5508
// Size: 132 bytes

void Add3DLine__6CSoundFiP3Vec(CSound *sound,int param_2,Vec *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = param_2 * 0x1cc;
  uVar2 = *(uint *)(&sound->field_0x1444 + iVar3);
  if (uVar2 < 10) {
    *(uint *)(&sound->field_0x1444 + iVar3) = uVar2 + 1;
    iVar1 = uVar2 * 0xc + iVar3;
    *(float *)(&sound->field_0x145c + iVar1) = param_3->x;
    *(float *)(&sound->field_0x1460 + iVar1) = param_3->y;
    *(float *)(&sound->field_0x1464 + iVar1) = param_3->z;
    CalcBound__9CLine(&sound->field_0x142c + iVar3);
  }
  else {
    Printf__7CSystemFPce(&System,s_CSound__C___B_801db14c);
  }
  return;
}

