// Function: GetCharaModelPtr__FPQ29CCharaPcs7CHandle
// Entry: 800e5858
// Size: 24 bytes

CModel * GetCharaModelPtr__FPQ29CCharaPcs7CHandle(CCharaPcsCHandle *handle)

{
  if (handle != (CCharaPcsCHandle *)0x0) {
    return handle->m_model;
  }
  return (CModel *)0x0;
}

