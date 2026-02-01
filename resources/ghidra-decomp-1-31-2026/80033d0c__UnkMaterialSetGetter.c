// Function: ?UnkMaterialSetGetter
// Entry: 80033d0c
// Size: 8 bytes

undefined4 _UnkMaterialSetGetter(CMaterial *material)

{
  return *(undefined4 *)&material->field_0x4;
}

