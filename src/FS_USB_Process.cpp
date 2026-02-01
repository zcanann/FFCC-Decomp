#include "ffcc/FS_USB_Process.h"
#include "ffcc/p_FunnyShape.h"
#include "ffcc/p_usb.h"

/*
 * --INFO--
 * PAL Address: 80052bc0
 * PAL Size: 3524b
 */
void CFunnyShape::SetUSBData()
{
	// TODO: Complex USB data processing function
	// Handles packet codes 4,5,6,10,11,12,15,16 for different data types
}

/*
 * --INFO--
 * PAL Address: UNUSED  
 * PAL Size: 52b
 */
void CFunnyShape::USBDataCallback(CDataHeader* dataHeader)
{
	// TODO: USB data callback processing
	// Small 52-byte function
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShape::SetDisplay(FS_DISPLAY_STATUS)
{
	// TODO
}
