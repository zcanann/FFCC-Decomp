#ifndef _FFCC_FUNNYSHAPE_H_
#define _FFCC_FUNNYSHAPE_H_

class FS_tagOAN3_SHAPE;
class Vec2d;

void GXEnd(void);
void GXSetTexCoordGen(void);

class CFunnyShape
{
public:
	CFunnyShape();
	~CFunnyShape();

	void InitAnmWork();
	void Update();
	void Render();
	void RenderTexture();
	void RenderShape();
	void ClearAnmData();
	void ClearTextureData();
	void RenderShape(FS_tagOAN3_SHAPE*, Vec2d&, float);
	void SetDefaultStage();
};

#endif // _FFCC_FUNNYSHAPE_H_
