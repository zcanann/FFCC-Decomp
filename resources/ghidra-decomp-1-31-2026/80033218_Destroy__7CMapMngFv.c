// Function: Destroy__7CMapMngFv
// Entry: 80033218
// Size: 60 bytes

void Destroy__7CMapMngFv(CMapMng *mapMng)

{
  DestroyMap__7CMapMngFv(mapMng);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)mapMng);
  return;
}

