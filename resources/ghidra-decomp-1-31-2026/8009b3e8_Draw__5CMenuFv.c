// Function: Draw__5CMenuFv
// Entry: 8009b3e8
// Size: 44 bytes

void Draw__5CMenuFv(CMenuPcs *menuPcs)

{
  (**(code **)((int)(menuPcs->process).manager.vtable + 0x18))();
  return;
}

