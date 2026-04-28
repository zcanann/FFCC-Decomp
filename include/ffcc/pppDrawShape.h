#ifndef _FFCC_PPPDRAWSHAPE_H_
#define _FFCC_PPPDRAWSHAPE_H_


struct ShapeControlData;
#ifdef __cplusplus
extern "C" {
#endif

void pppDrawShapeConstruct(void* pppShape, void* data);
void pppCalcShape(void* pppShape, struct ShapeControlData* data, void* additionalData);
void pppDrawShape(void* pppShape, struct ShapeControlData* data, void* additionalData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWSHAPE_H_
