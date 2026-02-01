// Function: EndParticle__13CFlatRuntime2FPQ29CCharaPcs7CHandle
// Entry: 8006a118
// Size: 48 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CFlatRuntime2 *
EndParticle__13CFlatRuntime2FPQ29CCharaPcs7CHandle
          (CFlatRuntime2 *flatRuntime2,CCharaPcsCHandle *handle)

{
  if (handle != (CCharaPcsCHandle *)0x0) {
    flatRuntime2 = (CFlatRuntime2 *)pppEndCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,handle);
  }
  return flatRuntime2;
}

