#ifndef _FFCC_P_MATERIALEDITOR_H_
#define _FFCC_P_MATERIALEDITOR_H_

struct Vec;

class CMaterialEditorPcs
{
public:
    CMaterialEditorPcs();
    ~CMaterialEditorPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);

    void createViewer();
    void destroyViewer();

    void ClearTextureData();

    void calcViewer();
    void drawViewer();

    void CreateBoundaryBox(Vec&, Vec&, long, const Vec*);
};

#endif // _FFCC_P_MATERIALEDITOR_H_
