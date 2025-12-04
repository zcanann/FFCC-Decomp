#ifndef _FFCC_FS_USB_PROCESS_H_
#define _FFCC_FS_USB_PROCESS_H_

class OSFS_SHAPE_ST
{
public:
	OSFS_SHAPE_ST& operator=(const OSFS_SHAPE_ST &);
};

class FS_DISPLAY_STATUS
{
public:
	FS_DISPLAY_STATUS& operator=(const FS_DISPLAY_STATUS &);
};

class CFunnyShape
{
public:
	void SetDisplay(FS_DISPLAY_STATUS);
};

#endif // _FFCC_FS_USB_PROCESS_H_
