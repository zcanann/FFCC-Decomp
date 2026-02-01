// Function: __dt__Q29CCharaPcs8CLoadPdtFv
// Entry: 80073af4
// Size: 132 bytes

CCharaPcs * __dt__Q29CCharaPcs8CLoadPdtFv(CCharaPcs *charaPcs,CLoadPdt *loadPdt)

{
  if (charaPcs != (CCharaPcs *)0x0) {
    (charaPcs->process).manager.vtable = &PTR_PTR_s_CCharaPcs_CLoadPdt_801fd278;
    if (-1 < *(int *)&charaPcs->field_0x14) {
      ReleasePdt__8CPartPcsFi(&PartPcs,*(int *)&charaPcs->field_0x14);
      *(undefined4 *)&charaPcs->field_0x14 = 0xffffffff;
    }
    __dt__4CRefFv((CRef *)charaPcs,0);
    if (0 < (short)loadPdt) {
      __dl__FPv(charaPcs);
    }
  }
  return charaPcs;
}

