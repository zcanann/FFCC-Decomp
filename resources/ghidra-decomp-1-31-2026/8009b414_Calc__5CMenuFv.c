// Function: Calc__5CMenuFv
// Entry: 8009b414
// Size: 44 bytes

void Calc__5CMenuFv(CMenu *menu)

{
  (**(code **)((int)(menu->ref).vtable + 0x14))();
  return;
}

