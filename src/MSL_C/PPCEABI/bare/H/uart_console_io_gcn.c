

/*
 * --INFO--
 * JP Address: 
 * JP Size: 
 * PAL Address: 801b9140
 * PAL Size: 208b
 * EN Address: 
 * EN Size: 
 */

// External function declarations
extern unsigned int OSGetConsoleType(void);
extern int InitializeUART(unsigned int);
extern int WriteUARTN(unsigned int, unsigned int);
extern int __TRK_write_console(unsigned int, unsigned int, unsigned int *, unsigned int);

// Static variable for UART initialization state  
static int DAT_8032f398 = 0;

int __write_console(unsigned int param_1, unsigned int param_2, unsigned int *param_3, unsigned int param_4)
{
	unsigned int uVar1;
	int iVar2;

	uVar1 = OSGetConsoleType();
	if ((uVar1 & 0x20000000) == 0) {
		iVar2 = 0;
		if ((DAT_8032f398 == 0) && (iVar2 = InitializeUART(0xe100), iVar2 == 0)) {
			DAT_8032f398 = 1;
		}
		if (iVar2 != 0) {
			return 1;
		}
		iVar2 = WriteUARTN(param_2, *param_3);
		if (iVar2 != 0) {
			*param_3 = 0;
			return 1;
		}
	}
	__TRK_write_console(param_1, param_2, param_3, param_4);
	return 0;
}