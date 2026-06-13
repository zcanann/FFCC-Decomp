#include "ffcc/cflat_runtime.h"
#include "ffcc/chunkfile.h"
#include "ffcc/memory.h"
#include "ffcc/stopwatch.h"
#include "ffcc/system.h"
#include <math.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

extern "C" {
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    CFlatRuntime*, CFlatRuntime::CObject*, int, int, int, CFlatRuntime::CStack*, CFlatRuntime::CStack*);
}

static const char s_cflat_runtime_newline[] = "\n";
extern const char lbl_8033011C[8] = "no name";
extern const char s_CFlatRuntime_801D8EE8[] = "CFlatRuntime";
static const char s_cflat_runtime_cpp[] = "cflat_runtime.cpp";


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onNewObject(CFlatRuntime::CObject*)
{
    return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onDeleteObject(CFlatRuntime::CObject*)
{
    return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFlatRuntime::onSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
	return 0;
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CFlatRuntime::onClassSystemFunc(CFlatRuntime::CObject*, int, int, int&)
{
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CVal* CFlatRuntime::onSystemVal(CFlatRuntime::CObject*, int)
{
	return reinterpret_cast<CVal*>(reinterpret_cast<u8*>(this) + 0x96C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CVal* CFlatRuntime::onClassSystemVal(CFlatRuntime::CObject*, int)
{
	return reinterpret_cast<CVal*>(reinterpret_cast<u8*>(this) + 0x96C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onSetSystemVal(int, CFlatRuntime::CStack*, int)
{
    return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::onSetClassSystemVal(int, CFlatRuntime::CObject*, CFlatRuntime::CStack*, int)
{
    return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CObject* CFlatRuntime::getFreeObject(int)
{
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* CFlatRuntime::intToClass(int)
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::reqFinished(int, CFlatRuntime::CObject*)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80065cf0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::ResetPerformance()
{
	memset(&m_performanceTotalTime, 0, sizeof(m_performanceTotalTime) + sizeof(m_performanceBlock));
}

/*
 * --INFO--
 * PAL Address: 0x80065d1c
 * PAL Size: 1760b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::systemFunc(CFlatRuntime::CObject* object, int systemKind, int systemIndex, int& result)
{
	int ret = 1;
	result = 1;

	if (systemKind == 1) {
		switch (systemIndex) {
		case -1:
			if (static_cast<int>(*object->m_localBase) <= object->m_waitCounter) {
				*object->m_sp = 0;
				object->m_sp++;
				result = 0;
			}
			break;
		case -2:
			if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x1298) != 0) {
				char* format = m_strBlob + m_strOffsets[*object->m_localBase];

				if (object->m_argCount == 1) {
					System.Printf(format);
					System.Printf(const_cast<char*>(s_cflat_runtime_newline));
				} else {
					char spec[256];
					char rendered[256];
					char line[264];
					line[0] = '\0';

					for (int i = 0; i < object->m_argCount - 1; i++) {
						while (true) {
							char specChar;
							int specLen = 0;
							while (((specChar = *format) != '\0') && ((specLen == 0) || (specChar != '%'))) {
								format++;
								spec[specLen] = specChar;
								specLen++;
							}
							spec[specLen] = '\0';

							if (spec[0] == '%') {
								break;
							}
							strcat(line, spec);
						}

						const int argIndex = i + 1;
						unsigned int* const arg = object->m_localBase + argIndex;
						if (spec[0] == '%') {
							char* scan = spec + 1;
							int fmtIndex = 1;
							int width = 0;
							s32 started = static_cast<u32>(__cntlzw(static_cast<u32>(0x30 - spec[1]))) >> 5 & 0xFF;
							for (; (*scan >= '0') && (*scan <= '9'); scan++) {
								fmtIndex++;
								width = width * 10 + (*scan - '0');
							}

							if (spec[fmtIndex] == 'b') {
								char* out = rendered;
								int value = *arg;
								int outLen = 0;

								for (int bit = 0; bit < width; bit++) {
									const int cur = (value >> ((width - bit) - 1)) & 1;
									if ((started == 0) && (cur != 0)) {
										started = 1;
									}
									if (started != 0) {
										*out++ = static_cast<char>(cur + '0');
										outLen++;
									}
								}
								rendered[outLen] = '\0';
								strcat(rendered, spec + 1 + fmtIndex);
							} else {
								scan = spec + 1;
								while (*scan != '\0') {
									switch (*scan) {
									case 'd':
									case 'x':
										sprintf(rendered, spec, *arg);
										goto renderedDone;
									case 'f':
										sprintf(rendered, spec, static_cast<double>(*reinterpret_cast<float*>(arg)));
										goto renderedDone;
									case 's':
										sprintf(rendered, spec, m_strBlob + m_strOffsets[*arg]);
										goto renderedDone;
									default:
										scan++;
										break;
									}
								}
							renderedDone:;
							}
						}

						strcat(line, rendered);
					}

					System.Printf(line);
					System.Printf(const_cast<char*>(s_cflat_runtime_newline));
				}
			}

			*object->m_sp = 0;
			object->m_sp++;
			result = 0;
			break;
		default: {
			CStopWatch watch(const_cast<char*>(lbl_8033011C));
			watch.Reset();
			watch.Start();
			ret = onClassSystemFunc(object, systemKind, systemIndex, result);
			watch.Stop();
			*reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + ((-systemIndex) * 4) + 0x4C) += watch.Get();
			*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + ((-systemIndex) * 4) + 0x44C) += 1;
			break;
		}
		}
	} else {
		switch (systemIndex) {
		case -1: {
			const int reqFlags = *reinterpret_cast<int*>(&object->m_reqFlag0);
			if (reqFlags != 0) {
				*object->m_sp = 0;
				object->m_sp++;
				result = 0;
				goto done;
			}

			const u32 requestIndex = object->m_localBase[0];
			const int noPush = object->m_localBase[1];
			object->m_waitCounter = 1;
			*reinterpret_cast<int*>(&object->m_reqFlag0) = 1;

			if (request(object, 2, requestIndex, object->m_argCount - 2,
			            reinterpret_cast<CStack*>(object->m_localBase + 2)) != 0) {
				if (object == reinterpret_cast<CObject*>(object->m_engineObject)) {
					result = 2;
					goto done;
				}

				*object->m_sp = 0;
				object->m_sp++;
				result = 0;
				goto done;
			}

			*reinterpret_cast<int*>(&object->m_reqFlag0) = 0;

			if (noPush != 0) {
				goto done;
			}

			*object->m_sp = 0;
			object->m_sp++;
			result = 0;
			goto done;
		}
		case -2: {
			CObject* const engineObject = reinterpret_cast<CObject*>(object->m_engineObject);
			const u32 scriptGroup = *object->m_localBase;

			engineObject->m_next->m_previous = engineObject->m_previous;
			engineObject->m_previous->m_next = engineObject->m_next;

			CObject* const root = &m_objectSentinel;
			CObject* begin = root->m_next;
			CObject* it = begin;
			do {
				if (static_cast<int>(scriptGroup) < it->m_0x32) {
					break;
				}
				it = it->m_next;
			} while (it != begin);

			it = it->m_previous;
			engineObject->m_next = it;
			engineObject->m_previous = it->m_previous;
			it->m_previous->m_next = engineObject;
			it->m_previous = engineObject;
			engineObject->m_0x32 = static_cast<s16>(scriptGroup);

			*object->m_sp = 0;
			object->m_sp++;
			result = 0;
			goto done;
		}
		case -3: {
			CObject* const engineObject = reinterpret_cast<CObject*>(object->m_engineObject);
			if ((static_cast<u32>(__cntlzw(static_cast<u32>(reinterpret_cast<u8*>(engineObject) - reinterpret_cast<u8*>(object)))) >> 5) == 0) {
				engineObject->m_previous->m_next = engineObject->m_next;
				engineObject->m_next->m_previous = engineObject->m_previous;

				*reinterpret_cast<void**>(reinterpret_cast<u8*>(*engineObject->m_freeListNode) + 0x04) =
				    engineObject->m_freeListNode[1];
				*reinterpret_cast<void**>(engineObject->m_freeListNode[1]) = *engineObject->m_freeListNode;

				engineObject->m_freeListNode[1] = m_objectFreeListHead;
				m_objectFreeListHead = engineObject->m_freeListNode;
				engineObject->m_flagBits.m_constructFlag = 0;

				onDeleteObject(engineObject);
			} else {
				object->m_flagBits.m_deleteFlag = 1;
			}

			*object->m_sp = 0;
			object->m_sp++;
			result = 0;
			goto done;
		}
		case -4:
			SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
			    this, object, 2, *object->m_localBase, object->m_argCount - 1,
			    reinterpret_cast<CStack*>(object->m_localBase + 1), 0);
			*object->m_sp = 0;
			object->m_sp++;
			result = 0;
			goto done;
		}

		CStopWatch watch(const_cast<char*>(lbl_8033011C));
		watch.Reset();
		watch.Start();
		ret = onSystemFunc(object, systemKind, systemIndex, result);
		watch.Stop();
		*reinterpret_cast<float*>(reinterpret_cast<u8*>(this) + ((-systemIndex) * 4) + 0x24C) += watch.Get();
		*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + ((-systemIndex) * 4) + 0x64C) += 1;
	}

done:
	return ret;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CFlatRuntime::CFunc* CFlatRuntime::searchFunc(int classIndex, int systemKind, int systemIndex)
{
	if ((classIndex >= 0)
	    && (((systemKind == 2) || (systemKind == 3)) && (systemIndex >= 0))) {
		u8* const classes = reinterpret_cast<u8*>(m_classes) + (classIndex * 0x22C) + 0x24;
		const int funcIndex = *reinterpret_cast<int*>(classes + (systemIndex * 4));
		if (funcIndex >= 0) {
			return reinterpret_cast<CFunc*>(m_funcs) + funcIndex;
		}
	} else {
		const int funcCount = m_funcCount;
		CFunc* func = reinterpret_cast<CFunc*>(m_funcs);

		for (int i = 0; i < funcCount; i++, func++) {
			if (func->m_systemKind != systemKind) {
				continue;
			}
			if (func->m_systemIndex != systemIndex) {
				continue;
			}
			return func;
		}
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CFlatRuntime::pop(CFlatRuntime::CObject* object)
{
	union {
		u32 u;
		s32 s;
	} value;

	object->m_sp--;
	value.u = *object->m_sp;
	return value.s;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CFlatRuntime::callSetup(CFlatRuntime::CObject* object, CFlatRuntime::CFunc* func, int callFlag)
{
	const u32 prevCodePos = object->m_codePos;
	const int prevCallFlag = object->m_flagBits.m_callFlag;
	unsigned int* const prevLocalBase = object->m_localBase;
	const int prevWaitCounter = object->m_waitCounter;
	const int prevReqFlag0 = *reinterpret_cast<int*>(&object->m_reqFlag0);
	const int prevArgCount = object->m_argCount;

	if (func->m_useCallerArgs != 0) {
		object->m_argCount = static_cast<s16>(pop(object));
		object->m_localBase = object->m_sp - object->m_argCount;
		object->m_sp = object->m_localBase + object->m_argCount;
	} else {
		object->m_localBase = object->m_sp - func->m_argCount;
		object->m_sp = object->m_localBase + func->m_localCount;
	}

	object->m_codeIndex.m_codeFunc = static_cast<s16>(func->m_index);
	object->m_codeIndex.m_codeOffset = 0;

	object->m_flagBits.m_callFlag = callFlag;
	object->m_waitCounter = 0;
	*reinterpret_cast<int*>(&object->m_reqFlag0) = 0;

	*object->m_sp = reinterpret_cast<u32>(prevLocalBase);
	object->m_sp++;
	*object->m_sp = prevCodePos;
	object->m_sp++;
	*object->m_sp = static_cast<u32>(prevCallFlag);
	object->m_sp++;
	*object->m_sp =
	    static_cast<u32>(prevArgCount | ((prevWaitCounter << 16) | (prevReqFlag0 << 15)));
	object->m_sp++;

	int clearCount = func->m_localCount - func->m_argCount;
	if (clearCount != 0) {
		unsigned int* clearPtr = object->m_localBase + func->m_argCount;
		while (clearCount > 0) {
			*clearPtr++ = 0;
			clearCount--;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CFlatRuntime::getTopBit(unsigned int value)
{
	int bit = 0x1F;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if ((value & 0x80000000) != 0) {
				return bit;
			}
			value <<= 1;
			bit--;
		}
	}

	return -1;
}
/*
 * --INFO--
 * PAL Address: 0x800663fc
 * PAL Size: 5600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::objectFrame(CFlatRuntime::CObject* object)
{
	union CodeWord {
		u32 u;
		s32 s;
	};
	struct CodeIndexView {
		short m_codeFunc : 12;
		int m_codeOffset : 20;
	};

	CStopWatch watch(const_cast<char*>(lbl_8033011C));
	watch.Reset();
	watch.Start();

	int watchdog = 100000;
	u8* code;
	u8* const self = reinterpret_cast<u8*>(this);
	int systemResult;

	if (object->m_waitCounter != 0) {
		goto callSystemFunction;
	}

	code = *reinterpret_cast<u8**>(
	    *reinterpret_cast<u8**>(self + 0x20) + (object->m_codeIndex.m_codeFunc * 0x50) + 0x34)
	    + object->m_codeIndex.m_codeOffset;

	while (true) {
		*reinterpret_cast<u32*>(self + 0x968) = *reinterpret_cast<u32*>(self + 0x964);
		*reinterpret_cast<u32*>(self + 0x964) = object->m_codePos;

		switch (code[0]) {
		case 0: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			const int index = static_cast<int>(arg) >> 8;
			unsigned int* value = 0;
			if ((arg & 1) != 0) {
				if (index < 0) {
					value = reinterpret_cast<unsigned int*>(
					    (arg & 0x10) != 0 ? onSystemVal(object, index) : onClassSystemVal(object, index));
				} else if ((arg & 8) != 0) {
					if ((arg & 0x10) != 0) {
						value = object->m_thisBase + index;
					} else {
						value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x0C) + (index * 4));
					}
				} else {
					value = object->m_localBase + index;
				}
				*object->m_sp = *value;
				object->m_sp++;
			} else if ((arg & 2) != 0) {
				if (index < 0) {
					CodeWord offset;
					object->m_sp--;
					offset.u = *object->m_sp;
					value = reinterpret_cast<unsigned int*>((arg & 0x10) != 0
					                                            ? onSystemVal(object, index + offset.s)
					                                            : onClassSystemVal(object, index + offset.s));
				} else if ((arg & 8) != 0) {
					if ((arg & 0x10) != 0) {
						CodeWord offset;
						object->m_sp--;
						offset.u = *object->m_sp;
						value = object->m_thisBase + (index + offset.s);
					} else {
						CodeWord offset;
						object->m_sp--;
						offset.u = *object->m_sp;
						value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x0C) + ((index + offset.s) * 4));
					}
				} else {
					CodeWord offset;
					object->m_sp--;
					offset.u = *object->m_sp;
					value = object->m_localBase + (index + offset.s);
				}
				*object->m_sp = *value;
				object->m_sp++;
			} else if ((arg & 4) != 0) {
				CodeWord offset;
				if (index < 0) {
					value = reinterpret_cast<unsigned int*>(
					    (arg & 0x10) != 0 ? onSystemVal(object, index) : onClassSystemVal(object, index));
				} else if ((arg & 8) != 0) {
					if ((arg & 0x10) != 0) {
						value = object->m_thisBase + index;
					} else {
						value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x0C) + (index * 4));
					}
				} else {
					value = object->m_localBase + index;
				}
				object->m_sp--;
				offset.u = *object->m_sp;
				*object->m_sp = *reinterpret_cast<unsigned int*>(*value + (offset.s * 4));
				object->m_sp++;
			}
			break;
		}
		case 1: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			const int index = static_cast<int>(arg) >> 8;
			unsigned int* value = 0;
			if ((arg & 1) != 0) {
				if (index < 0) {
					value = reinterpret_cast<unsigned int*>(
					    (arg & 0x10) != 0 ? onSystemVal(object, index) : onClassSystemVal(object, index));
				} else if ((arg & 8) != 0) {
					if ((arg & 0x10) != 0) {
						value = object->m_thisBase + index;
					} else {
						value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x0C) + (index * 4));
					}
				} else {
					value = object->m_localBase + index;
				}
				*object->m_sp = reinterpret_cast<u32>(value);
				object->m_sp++;
			} else if ((arg & 2) != 0) {
				if (index < 0) {
					CodeWord offset;
					object->m_sp--;
					offset.u = *object->m_sp;
					value = reinterpret_cast<unsigned int*>((arg & 0x10) != 0
					                                            ? onSystemVal(object, index + offset.s)
					                                            : onClassSystemVal(object, index + offset.s));
				} else if ((arg & 8) != 0) {
					if ((arg & 0x10) != 0) {
						CodeWord offset;
						object->m_sp--;
						offset.u = *object->m_sp;
						value = object->m_thisBase + (index + offset.s);
					} else {
						CodeWord offset;
						object->m_sp--;
						offset.u = *object->m_sp;
						value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x0C) + ((index + offset.s) * 4));
					}
				} else {
					CodeWord offset;
					object->m_sp--;
					offset.u = *object->m_sp;
					value = object->m_localBase + (index + offset.s);
				}
				*object->m_sp = reinterpret_cast<u32>(value);
				object->m_sp++;
			} else if ((arg & 4) != 0) {
				CodeWord offset;
				if (index < 0) {
					value = reinterpret_cast<unsigned int*>(
					    (arg & 0x10) != 0 ? onSystemVal(object, index) : onClassSystemVal(object, index));
				} else if ((arg & 8) != 0) {
					if ((arg & 0x10) != 0) {
						value = object->m_thisBase + index;
					} else {
						value = reinterpret_cast<unsigned int*>(*reinterpret_cast<u8**>(self + 0x0C) + (index * 4));
					}
				} else {
					value = object->m_localBase + index;
				}
				object->m_sp--;
				offset.u = *object->m_sp;
				*object->m_sp = *value + (offset.s * 4);
				object->m_sp++;
			}
			break;
		}
		case 2: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			const int index = static_cast<int>(arg) >> 8;
			const u32 classId = object->m_engineObject != 0 ? static_cast<u32>(*reinterpret_cast<s16*>(reinterpret_cast<u8*>(object->m_engineObject) + 0x30)) : 1U;
			if ((arg & 1) != 0) {
				*object->m_sp = ((static_cast<u32>(index) << 13) | (classId & 0xFFF))
				              | ((arg >> 4 & 1) != 0 ? 0x1000 : 0);
				object->m_sp++;
			} else if ((arg & 2) != 0) {
				CodeWord offset;
				const u32 sign = (arg >> 4 & 1) != 0 ? 0x1000 : 0;
				object->m_sp--;
				offset.u = *object->m_sp;
				*object->m_sp = sign | ((classId & 0xFFF) | (index + offset.s) * 0x2000);
				object->m_sp++;
			}
			break;
		}
		case 0x3F:
			*object->m_sp = 0;
			object->m_sp++;
			break;
		case 3:
			*object->m_sp = *reinterpret_cast<unsigned int*>(code + 1);
			object->m_sp++;
			break;
		case 4:
			*object->m_sp = *reinterpret_cast<unsigned int*>(code + 1);
			object->m_sp++;
			break;
		case 5:
			*object->m_sp = *reinterpret_cast<unsigned int*>(code + 1);
			object->m_sp++;
			break;
		case 6: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			if ((static_cast<int>(arg) >> 16) == 0) {
				object->m_sp += 2;
			} else {
				unsigned int* frameBase = object->m_sp + (-3 - static_cast<int>(arg & 0xFFFF));
				u8* classData = reinterpret_cast<u8*>(intToClass(static_cast<int>(*frameBase)));
				frameBase[1] = reinterpret_cast<u32>(object->m_thisBase);
				u32 classIndex = 0xFFFF;
				if (object->m_classIndex >= 0) {
					classIndex = static_cast<u32>(object->m_classIndex);
				}
				frameBase[2] = (static_cast<u32>(*reinterpret_cast<s16*>(reinterpret_cast<u8*>(object->m_engineObject) + 0x30)) << 16)
				               | classIndex;
				object->m_thisBase = reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(classData));
				object->m_classIndex = *reinterpret_cast<s16*>(classData + 0x14);
				object->m_engineObject = classData;
			}
			break;
		}
		case 7: {
			CodeIndexView* const view = reinterpret_cast<CodeIndexView*>(&object->m_codePos);
			const int delta = static_cast<int>(*reinterpret_cast<u32*>(code + 1) & 0x00FFFFFF) - view->m_codeOffset;
			code += delta;
			object->m_codeIndex.m_codeOffset = object->m_codeIndex.m_codeOffset + delta;
			continue;
		}
		case 9: {
			CodeWord cond;
			cond.u = pop(object);
			if (cond.s != 0) {
				const u32 jumpArg = *reinterpret_cast<u32*>(code + 1);
				if ((static_cast<int>(jumpArg) >> 24) != 0) {
					*object->m_sp = 1;
					object->m_sp++;
				}
				const int delta = static_cast<int>(jumpArg & 0x00FFFFFF)
				    - reinterpret_cast<CodeIndexView*>(&object->m_codePos)->m_codeOffset;
				code += delta;
				object->m_codeIndex.m_codeOffset = object->m_codeIndex.m_codeOffset + delta;
				continue;
			}
			break;
		}
		case 8: {
			CodeWord cond;
			cond.u = pop(object);
			if (cond.s == 0) {
				const u32 jumpArg = *reinterpret_cast<u32*>(code + 1);
				if ((static_cast<int>(jumpArg) >> 24) != 0) {
					*object->m_sp = 0;
					object->m_sp++;
				}
				const int delta = static_cast<int>(jumpArg & 0x00FFFFFF)
				    - reinterpret_cast<CodeIndexView*>(&object->m_codePos)->m_codeOffset;
				code += delta;
				object->m_codeIndex.m_codeOffset = object->m_codeIndex.m_codeOffset + delta;
				continue;
			}
			break;
		}
		case 0x0A: {
			const u32 arg = *reinterpret_cast<u32*>(code + 1);
			CFunc* func = reinterpret_cast<CFunc*>(*reinterpret_cast<u8**>(self + 0x20)) + (arg & 0xFFFF);

			if ((static_cast<int>(arg) >> 16) >= 0) {
				const int funcIndex = *reinterpret_cast<int*>(*reinterpret_cast<u8**>(self + 0x18) + (object->m_classIndex * 0x22C) + 0x24 + (func->m_systemIndex * 4));
				if (funcIndex < 0) {
					continue;
				}
				func = reinterpret_cast<CFunc*>(*reinterpret_cast<u8**>(self + 0x20)) + funcIndex;
			}

			callSetup(object, func, 0);

			if (((func->m_systemKind != 1) && (func->m_systemKind != 2)) || (func->m_systemIndex >= 0)) {
				goto recomputeCode;
			}
		}
		callSystemFunction: {
			const int funcIndex = object->m_codeIndex.m_codeFunc;
			CFunc* func = reinterpret_cast<CFunc*>(*reinterpret_cast<u8**>(self + 0x20)) + funcIndex;
			const int ret = systemFunc(object, func->m_systemKind, func->m_systemIndex, systemResult);

			if (ret != 0) {
				if (systemResult == 0) {
					goto returnFromCall;
				}
				if (systemResult == 2) {
					goto suspend;
				}
				goto addWait;
			} else {
				*object->m_sp = 0;
				object->m_sp++;
			}
			goto returnFromCall;
		}
		recomputeCode:
			code = *reinterpret_cast<u8**>(
			    *reinterpret_cast<u8**>(self + 0x20) + (object->m_codeIndex.m_codeFunc * 0x50) + 0x34)
			    + object->m_codeIndex.m_codeOffset;
			continue;
		case 0x0B: {
			CObject* newObject = createObject(*reinterpret_cast<int*>(code + 1));
			CFunc* func = reinterpret_cast<CFunc*>(*reinterpret_cast<u8**>(self + 0x20))
			              + *reinterpret_cast<int*>(*reinterpret_cast<u8**>(self + 0x18) + (newObject->m_activeClassIndex * 0x22C) + 0x24);

			for (int i = 0; i < func->m_argCount; i++) {
				newObject->m_sp[i] = object->m_sp[i - func->m_argCount];
			}
			newObject->m_sp += func->m_argCount;

			CodeWord argCount;
			CodeWord prevCodePos;
			prevCodePos.u = newObject->m_codePos;
			unsigned int* const prevLocalBase = newObject->m_localBase;
			const int prevWaitCounter = newObject->m_waitCounter;
			const int prevActive = newObject->m_flagBits.m_callFlag;
			const int prevReqFlags = *reinterpret_cast<int*>(&newObject->m_reqFlag0);
			const int prevArgCount = newObject->m_argCount;

			if (func->m_useCallerArgs != 0) {
				newObject->m_sp--;
				argCount.u = *newObject->m_sp;
				newObject->m_argCount = static_cast<s16>(argCount.s);
				newObject->m_localBase = newObject->m_sp - newObject->m_argCount;
				newObject->m_sp = newObject->m_localBase + newObject->m_argCount;
			} else {
				newObject->m_localBase = newObject->m_sp - func->m_argCount;
				newObject->m_sp = newObject->m_localBase + func->m_localCount;
			}

			newObject->m_codeIndex.m_codeFunc = static_cast<s16>(func->m_index);
			newObject->m_codeIndex.m_codeOffset = 0;
			newObject->m_flagBits.m_callFlag = 1;
			newObject->m_waitCounter = 0;
			*reinterpret_cast<int*>(&newObject->m_reqFlag0) = 0;

			*newObject->m_sp = reinterpret_cast<unsigned int>(prevLocalBase);
			newObject->m_sp++;
			*newObject->m_sp = static_cast<u32>(prevCodePos.s);
			newObject->m_sp++;
			*newObject->m_sp = prevActive;
			newObject->m_sp++;
			*newObject->m_sp =
			    static_cast<u32>(prevArgCount | ((prevWaitCounter << 16) | (prevReqFlags << 15)));
			newObject->m_sp++;

			int clearCount = func->m_localCount - func->m_argCount;
			if (clearCount != 0) {
				unsigned int* clear = newObject->m_localBase + func->m_argCount;
				while (clearCount > 0) {
					*clear++ = 0;
					clearCount--;
				}
			}

			objectFrame(newObject);
			--newObject->m_sp;
			object->m_sp -= func->m_argCount;
			*object->m_sp = static_cast<int>(newObject->m_particleId);
			object->m_sp++;
			request(newObject, 2, 3, 0, 0);
			request(newObject, 2, 2, 0, 0);
			newObject->onNewFinished();
			break;
		}
		case 0x0C:
			--object->m_sp;
			break;
		case 0x0D: {
			unsigned int* sp = --object->m_sp;
			unsigned int* value = reinterpret_cast<unsigned int*>(sp[-1]);
			sp[-1] = *value;
			*value = sp[0];
			break;
		}
		case 0x0E: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			unsigned int* value = reinterpret_cast<unsigned int*>(sp[-2]);
			sp[-2] = *value;
			*value = *value + *top;
			break;
		}
		case 0x0F: {
			unsigned int* sp = --object->m_sp;
			unsigned int* value = reinterpret_cast<unsigned int*>(sp[-1]);
			sp[-1] = *value;
			*value = *value - sp[0];
			break;
		}
		case 0x10: {
			unsigned int* sp = --object->m_sp;
			float* value = reinterpret_cast<float*>(sp[-1]);
			*reinterpret_cast<float*>(sp - 1) = *value;
			*value = *reinterpret_cast<float*>(sp);
			break;
		}
		case 0x11: {
			unsigned int* sp = --object->m_sp;
			float* value = reinterpret_cast<float*>(sp[-1]);
			*reinterpret_cast<float*>(sp - 1) = *value;
			*value = *value + *reinterpret_cast<float*>(sp);
			break;
		}
		case 0x12: {
			unsigned int* sp = --object->m_sp;
			float* value = reinterpret_cast<float*>(sp[-1]);
			*reinterpret_cast<float*>(sp - 1) = *value;
			*value = *value - *reinterpret_cast<float*>(sp);
			break;
		}
		case 0x13:
		case 0x16: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			const u32 systemValue = sp[-2];
			const int valIndex = static_cast<int>(systemValue) >> 13;
			if (((systemValue >> 12) & 1) != 0) {
				CObject* target = reinterpret_cast<CObject*>(intToClass(systemValue & 0xFFF));
				onSetClassSystemVal(valIndex, target, reinterpret_cast<CStack*>(top), 0);
			} else {
				onSetSystemVal(valIndex, reinterpret_cast<CStack*>(top), 0);
			}
			break;
		}
		case 0x14:
		case 0x17: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			const u32 systemValue = sp[-2];
			const int valIndex = static_cast<int>(systemValue) >> 13;
			if (((systemValue >> 12) & 1) != 0) {
				CObject* target = reinterpret_cast<CObject*>(intToClass(systemValue & 0xFFF));
				onSetClassSystemVal(valIndex, target, reinterpret_cast<CStack*>(top), 1);
			} else {
				onSetSystemVal(valIndex, reinterpret_cast<CStack*>(top), 1);
			}
			break;
		}
		case 0x15:
		case 0x18: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			const u32 systemValue = sp[-2];
			const int valIndex = static_cast<int>(systemValue) >> 13;
			if (((systemValue >> 12) & 1) != 0) {
				CObject* target = reinterpret_cast<CObject*>(intToClass(systemValue & 0xFFF));
				onSetClassSystemVal(valIndex, target, reinterpret_cast<CStack*>(top), -1);
			} else {
				onSetSystemVal(valIndex, reinterpret_cast<CStack*>(top), -1);
			}
			break;
		}
		case 0x19:
		case 0x1A:
		case 0x1B:
		case 0x1C:
		case 0x1D:
		case 0x1E:
		case 0x1F:
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x27:
		case 0x28:
		case 0x29:
		case 0x2A:
		case 0x2B:
			GetCodeInfo(reinterpret_cast<char*>(object));
			break;
		case 0x2C: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			top[-1] = (__cntlzw(*top - sp[-2]) >> 5) & 0xFF;
			break;
		}
		case 0x2D: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			top[-1] = ((sp[-1] - sp[-2]) | (sp[-2] - sp[-1])) >> 31;
			break;
		}
		case 0x2E: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			const u32 value = sp[-1] ^ sp[-2];
			top[-1] = static_cast<u32>((static_cast<int>(value) >> 1) - static_cast<int>(value & sp[-1])) >> 31;
			break;
		}
		case 0x2F: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			top[-1] = (static_cast<int>(sp[-1]) >> 31) + (sp[-2] >> 31) + (sp[-2] <= sp[-1]) & 0xFF;
			break;
		}
		case 0x30: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			const u32 value = sp[-2] ^ sp[-1];
			top[-1] = static_cast<u32>((static_cast<int>(value) >> 1) - static_cast<int>(value & sp[-2])) >> 31;
			break;
		}
		case 0x31: {
			unsigned int* sp = object->m_sp;
			unsigned int* top = --object->m_sp;
			top[-1] = (static_cast<int>(sp[-2]) >> 31) + (sp[-1] >> 31) + (sp[-1] <= sp[-2]) & 0xFF;
			break;
		}
		case 0x32: {
			float* sp = reinterpret_cast<float*>(object->m_sp);
			--object->m_sp;
			sp[-2] = static_cast<float>(static_cast<unsigned int>(sp[-2] == sp[-1]));
			break;
		}
		case 0x33: {
			float* sp = reinterpret_cast<float*>(object->m_sp);
			--object->m_sp;
			sp[-2] = static_cast<float>(static_cast<unsigned int>(sp[-2] != sp[-1]));
			break;
		}
		case 0x34: {
			float* sp = reinterpret_cast<float*>(object->m_sp);
			--object->m_sp;
			sp[-2] = static_cast<float>(static_cast<unsigned int>(sp[-2] < sp[-1]));
			break;
		}
		case 0x35: {
			float* sp = reinterpret_cast<float*>(object->m_sp);
			--object->m_sp;
			sp[-2] = static_cast<float>(static_cast<unsigned int>(sp[-2] <= sp[-1]));
			break;
		}
		case 0x36: {
			float* sp = reinterpret_cast<float*>(object->m_sp);
			--object->m_sp;
			sp[-2] = static_cast<float>(static_cast<unsigned int>(sp[-2] > sp[-1]));
			break;
		}
		case 0x37: {
			float* sp = reinterpret_cast<float*>(object->m_sp);
			--object->m_sp;
			sp[-2] = static_cast<float>(static_cast<unsigned int>(sp[-2] >= sp[-1]));
			break;
		}
		case 0x39: {
			--object->m_sp;
			const u32 returnValue = *object->m_sp;
			--object->m_sp;
			const u32 classWord = *object->m_sp;
			CObject* target = reinterpret_cast<CObject*>(intToClass(classWord >> 16));
			object->m_engineObject = target;
			object->m_classIndex = static_cast<s16>(classWord);
			--object->m_sp;
			object->m_thisBase = reinterpret_cast<unsigned int*>(*object->m_sp);
			--object->m_sp;
			*object->m_sp++ = returnValue;
			break;
		}
		case 0x3A:
			*object->m_sp = object->m_sp[-1];
			object->m_sp++;
			break;
		case 0x3C:
		returnFromCall: {
			CodeWord previousLocalBase;
			CodeWord previousCodePos;
			CodeWord previousActive;
			CodeWord packedFlags;
			CodeWord returnValue;
			CodeWord codePosTemp;
			CodeWord returnTemp;
			const int oldCallFlag = object->m_flagBits.m_callFlag;

			object->m_sp--;
			returnValue.u = *object->m_sp;
			returnTemp.s = returnValue.s;
			object->m_sp--;
			packedFlags.u = *object->m_sp;
			object->m_sp--;
			previousActive.u = *object->m_sp;
			object->m_sp--;
			previousCodePos.u = *object->m_sp;
			codePosTemp.s = previousCodePos.s;
			object->m_sp--;
			previousLocalBase.u = *object->m_sp;

			object->m_sp = object->m_localBase;
			*object->m_sp = returnTemp.u;
			object->m_sp++;
			object->m_localBase = reinterpret_cast<unsigned int*>(previousLocalBase.s);
			object->m_codePos = codePosTemp.u;
			object->m_flagBits.m_callFlag = static_cast<s8>(previousActive.s);
			object->m_waitCounter = packedFlags.s >> 16;
			*reinterpret_cast<int*>(&object->m_reqFlag0) = (packedFlags.u >> 15) & 1;
			object->m_argCount = static_cast<s16>(packedFlags.u);

			if (object->m_flagBits.m_deleteFlag != 0) {
				return 0;
			}
			if (oldCallFlag != 0) {
				return 1;
			}

			code = *reinterpret_cast<u8**>(
			    *reinterpret_cast<u8**>(self + 0x20) + (object->m_codeIndex.m_codeFunc * 0x50) + 0x34)
			    + object->m_codeIndex.m_codeOffset;
			break;
		}
		case 0x3D:
			object->m_sp[-1] = static_cast<int>(*reinterpret_cast<float*>(object->m_sp - 1));
			break;
		case 0x3E:
			*reinterpret_cast<float*>(object->m_sp - 1) = static_cast<float>(*reinterpret_cast<int*>(object->m_sp - 1));
			break;
		default:
			break;
		}

		const int step = (code[0] < 0x0C) ? 5 : 1;
		code += step;
		--watchdog;
		object->m_codeIndex.m_codeOffset += step;
	}

addWait:
	if (object->m_waitCounter < 0x708) {
		object->m_waitCounter++;
	}
suspend:
	watch.Stop();
	*reinterpret_cast<float*>(self + 0x48) += watch.Get();
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800679DC
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::GetCodeInfo(char* codeInfo)
{
	union CodeWord {
		u32 u;
		s32 s;
		float f;
	};

	CObject* object = reinterpret_cast<CObject*>(codeInfo);
	register int op;
	CodeWord lhsFloat;
	CodeWord rhsFloat;
	CodeWord result;
	CodeWord rhs;
	CodeWord lhs;

#ifdef __MWERKS__
	asm { mr op, r5 };
#else
	op = 0;
#endif

	object->m_sp--;
	rhs.u = *object->m_sp;
	rhsFloat.u = rhs.u;

	if ((op == 0x20) || (op == 0x23) || (op == 0x25) || (op == 0x2B)) {
		switch (op) {
		case 0x20:
			result.s = -rhsFloat.s;
			break;
		case 0x23:
			result.u = static_cast<u32>((__cntlzw(rhsFloat.u) >> 5) & 0xFF);
			break;
		case 0x25:
			result.u = ~rhsFloat.u;
			break;
		case 0x2B:
			result.f = -rhsFloat.f;
			break;
		}
	} else {
		object->m_sp--;
		lhs.u = *object->m_sp;
		lhsFloat.u = lhs.u;

		switch (op) {
		case 0x19:
			result.s = lhs.s + rhs.s;
			break;
		case 0x1A:
			result.s = lhs.s - rhs.s;
			break;
		case 0x1B:
			result.s = lhs.s * rhs.s;
			break;
		case 0x1C:
			result.s = lhs.s / rhs.s;
			break;
		case 0x1D:
		{
			int quotient = lhs.s / rhs.s;
			result.s = lhs.s - (quotient * rhs.s);
			break;
		}
		case 0x1E:
			result.u = lhs.u | rhs.u;
			break;
		case 0x1F:
			result.u = lhs.u & rhs.u;
			break;
		case 0x21:
			result.s = lhs.s >> rhs.u;
			break;
		case 0x22:
			result.s = lhs.s << rhs.s;
			break;
		case 0x24:
			result.u = lhs.u ^ rhs.u;
			break;
		case 0x26:
			result.f = lhsFloat.f + rhsFloat.f;
			break;
		case 0x27:
			result.f = lhsFloat.f - rhsFloat.f;
			break;
		case 0x28:
			result.f = lhsFloat.f * rhsFloat.f;
			break;
		case 0x29:
			result.f = lhsFloat.f / rhsFloat.f;
			break;
		case 0x2A:
			result.f = static_cast<float>(fmod(static_cast<double>(lhsFloat.f), static_cast<double>(rhsFloat.f)));
			break;
		}
	}

	*object->m_sp = result.u;
	object->m_sp++;
}

/*
 * --INFO--
 * PAL Address: 0x80067be0
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::push(CFlatRuntime::CObject* object, int value)
{
	*object->m_sp = static_cast<u32>(value);
	object->m_sp++;
}

/*
 * --INFO--
 * PAL Address: 0x80067bf8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::ClearParmanent()
{
	int varIndex = 0;

	while (varIndex < m_permanentVarCount) {
		int valueOffset = varIndex * 4;
		if ((m_permanentVarDefs[valueOffset + 1] & 0x20) != 0) {
			*reinterpret_cast<u32*>(m_permanentVarValues + valueOffset) = 0;
		}
		varIndex += 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80067c3c
 * PAL Size: 1144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::request(CFlatRuntime::CObject* object, int systemKind, int systemIndex, int argCount,
                          CFlatRuntime::CStack* args)
{
	CObject* const engineObject = reinterpret_cast<CObject*>(object->m_engineObject);

	if (engineObject->m_flagBits.m_deleteFlag != 0) {
		return 1;
	}

	CFunc* const func = searchFunc(engineObject->m_activeClassIndex, systemKind, systemIndex);

	if (func == 0) {
		return 0;
	}

	const int reqFlagIndex = func->m_reqFlagIndex;
	if (reqFlagIndex >= 0) {
		if (reqFlagIndex <= getTopBit(engineObject->m_0x34)) {
			return 0;
		}
		engineObject->m_0x34 |= 1 << reqFlagIndex;
	}

	int copiedArgs;
	for (copiedArgs = 0; copiedArgs < argCount; copiedArgs++) {
		engineObject->m_sp[copiedArgs] = args[copiedArgs].m_word;
	}
	engineObject->m_sp += copiedArgs;

	const u32 prevCodePos = engineObject->m_codePos;
	const int prevCallFlag = engineObject->m_flagBits.m_callFlag;
	unsigned int* const prevLocalBase = engineObject->m_localBase;
	const int prevWaitCounter = engineObject->m_waitCounter;
	const int prevReqFlag0 = *reinterpret_cast<int*>(&engineObject->m_reqFlag0);
	const s16 prevArgCount = engineObject->m_argCount;

	if (func->m_useCallerArgs != 0) {
		engineObject->m_argCount = static_cast<s16>(pop(engineObject));
		engineObject->m_localBase = engineObject->m_sp - engineObject->m_argCount;
		engineObject->m_sp = engineObject->m_localBase + engineObject->m_argCount;
	} else {
		engineObject->m_localBase = engineObject->m_sp - func->m_argCount;
		engineObject->m_sp = engineObject->m_localBase + func->m_localCount;
	}

	engineObject->m_codeIndex.m_codeFunc = static_cast<s16>(func->m_index);
	engineObject->m_codeIndex.m_codeOffset = 0;

	engineObject->m_flagBits.m_callFlag = 1;
	engineObject->m_waitCounter = 0;
	*reinterpret_cast<int*>(&engineObject->m_reqFlag0) = 0;

	*engineObject->m_sp = reinterpret_cast<u32>(prevLocalBase);
	engineObject->m_sp++;
	*engineObject->m_sp = prevCodePos;
	engineObject->m_sp++;
	*engineObject->m_sp = static_cast<u32>(prevCallFlag);
	engineObject->m_sp++;
	*engineObject->m_sp =
	    static_cast<u32>(prevArgCount | ((prevWaitCounter << 16) | (prevReqFlag0 << 15)));
	engineObject->m_sp++;

	int clearCount = func->m_localCount - func->m_argCount;
	if (clearCount != 0) {
		unsigned int* clearPtr = engineObject->m_localBase + func->m_argCount;
		while (clearCount > 0) {
			*clearPtr++ = 0;
			clearCount--;
		}
	}

	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800680b4
 * PAL Size: 1044b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::SystemCall(CFlatRuntime::CObject* objectParam, int systemKind, int systemIndex, int argCount,
                              CFlatRuntime::CStack* args, CFlatRuntime::CStack* outArg)
{
	if (objectParam == 0) {
		objectParam = reinterpret_cast<CObject*>(intToClass(1));
	}

	CObject* const object = reinterpret_cast<CObject*>(objectParam->m_engineObject);
	CFunc* func;

	if (object->m_flagBits.m_deleteFlag != 0) {
		return 1;
	}

	const int classIndex = object->m_activeClassIndex;
	if ((classIndex >= 0)
	    && (((systemKind == 2) || (systemKind == 3)) && (systemIndex >= 0))) {
		u8* const classes = reinterpret_cast<u8*>(m_classes) + (classIndex * 0x22C) + 0x24;
		const int funcIndex = *reinterpret_cast<int*>(classes + (systemIndex * 4));
		if (funcIndex >= 0) {
			func = reinterpret_cast<CFunc*>(m_funcs) + funcIndex;
			goto haveFunc;
		}
	} else {
		const int funcCount = m_funcCount;
		func = reinterpret_cast<CFunc*>(m_funcs);

		for (int i = 0; i < funcCount; i++, func++) {
			if (func->m_systemKind != systemKind) {
				continue;
			}
			if (func->m_systemIndex != systemIndex) {
				continue;
			}
			goto haveFunc;
		}
	}
	func = 0;
haveFunc:

	if ((func == 0) || (func->m_codeSize == 0)) {
		return 0;
	}

	int copiedArgs;
	for (copiedArgs = 0; copiedArgs < argCount; copiedArgs++) {
		object->m_sp[copiedArgs] = args[copiedArgs].m_word;
	}
	object->m_sp += copiedArgs;

	const u32 prevCodePos = object->m_codePos;
	const int prevCallFlag = object->m_flagBits.m_callFlag;
	unsigned int* const prevLocalBase = object->m_localBase;
	const int prevWaitCounter = object->m_waitCounter;
	const int prevReqFlag0 = *reinterpret_cast<int*>(&object->m_reqFlag0);
	const s16 prevArgCount = object->m_argCount;

	if (func->m_useCallerArgs != 0) {
		object->m_argCount = static_cast<s16>(pop(object));
		object->m_localBase = object->m_sp - object->m_argCount;
		object->m_sp = object->m_localBase + object->m_argCount;
	} else {
		object->m_localBase = object->m_sp - func->m_argCount;
		object->m_sp = object->m_localBase + func->m_localCount;
	}

	object->m_codeIndex.m_codeFunc = static_cast<s16>(func->m_index);
	object->m_codeIndex.m_codeOffset = 0;

	object->m_flagBits.m_callFlag = 1;
	object->m_waitCounter = 0;
	*reinterpret_cast<int*>(&object->m_reqFlag0) = 0;

	*object->m_sp = reinterpret_cast<u32>(prevLocalBase);
	object->m_sp++;
	*object->m_sp = prevCodePos;
	object->m_sp++;
	*object->m_sp = static_cast<u32>(prevCallFlag);
	object->m_sp++;
	*object->m_sp =
	    static_cast<u32>(prevArgCount | ((prevWaitCounter << 16) | (prevReqFlag0 << 15)));
	object->m_sp++;

	int clearCount = func->m_localCount - func->m_argCount;
	if (clearCount != 0) {
		unsigned int* clearPtr = object->m_localBase + func->m_argCount;
		while (clearCount > 0) {
			*clearPtr++ = 0;
			clearCount--;
		}
	}

	objectFrame(object);

	const int result = pop(object);
	if (outArg != 0) {
		outArg->m_word = result;
	}
	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800684c8
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::CObject* CFlatRuntime::createObject(int classIndex)
{
	u8* const self = reinterpret_cast<u8*>(this);
	CClass* classBase;
	if (classIndex == -1) {
		classBase = 0;
	} else {
		classBase = &m_classes[classIndex];
	}

	const int varCount = (classBase != 0) ? classBase->m_variableCount : 0;

	CObject* object = getFreeObject(varCount);

	object->m_previous = m_objectSentinel.m_previous;
	object->m_next = &m_objectSentinel;
	m_objectSentinel.m_previous->m_next = object;
	m_objectSentinel.m_previous = object;

	const u32 clearBit = 0;
	const u32 setBit = 1;

	object->m_flagBits.m_deleteFlag = clearBit;
	object->m_flagBits.m_callFlag = clearBit;
	object->m_flagBits.m_constructFlag = setBit;
	object->m_0x34 = 0;
	object->m_0x32 = 0xF;
	object->m_waitCounter = 0;
	*reinterpret_cast<int*>(&object->m_reqFlag0) = 0;
	object->m_classIndex = static_cast<s16>(classIndex);
	object->m_activeClassIndex = object->m_classIndex;
	object->m_flagBits.m_activeFlag = setBit;

	const int classLocalCount = (classIndex == -1) ? 0 : classBase->m_localCount;

	const int requiredWords = classLocalCount + 0x60;
	u8* scanNode = reinterpret_cast<u8*>(m_freeListNext);
	const int noScan = static_cast<u8>(scanNode == self + 0x978);
	u8* selectedNode;
	do {
		selectedNode = scanNode;
		if (noScan != 0) {
			break;
		}
		scanNode = *reinterpret_cast<u8**>(selectedNode + 4);
	} while ((*reinterpret_cast<int*>(selectedNode + 8) + requiredWords) +
	             *reinterpret_cast<int*>(selectedNode + 0xC) >
	         *reinterpret_cast<int*>(scanNode + 8));

	void** const freeNode = m_objectFreeListHead;
	m_objectFreeListHead = reinterpret_cast<void**>(freeNode[1]);
	freeNode[0] = selectedNode;
	freeNode[1] = *reinterpret_cast<void**>(selectedNode + 4);
	*reinterpret_cast<void***>(freeNode[1]) = freeNode;
	*reinterpret_cast<void**>(selectedNode + 4) = freeNode;

	const int scanOffset = *reinterpret_cast<int*>(selectedNode + 0xC);
	const int baseWords = (noScan != 0) ? 0 : *reinterpret_cast<int*>(selectedNode + 8);
	freeNode[2] = reinterpret_cast<void*>(static_cast<int>(scanOffset + baseWords));
	freeNode[3] = reinterpret_cast<void*>(requiredWords);

	object->m_freeListNode = freeNode;
	object->m_id = reinterpret_cast<u32>(*reinterpret_cast<u8**>(self + 0x10) + (reinterpret_cast<s32>(freeNode[2]) * 4));

	unsigned int* varBase = 0;
	if (classIndex == -1) {
		varBase = *reinterpret_cast<unsigned int**>(self + 0x0C);
	} else {
		varBase = reinterpret_cast<unsigned int*>(object->m_id);
	}
	object->m_thisBase = varBase;

	if (classIndex == -1) {
		varBase = reinterpret_cast<unsigned int*>(object->m_id);
	} else {
		varBase = object->m_thisBase + classBase->m_localCount;
	}
	object->m_sp = varBase;
	object->m_localBase = 0;
	object->m_engineObject = object;
	object->m_codeIndex.m_codeFunc = -1;
	object->m_argCount = 0;

	const int allowKeep = (classIndex == -1) ? static_cast<u8>(m_0x970 == 0) : 1;

	unsigned int* write = object->m_thisBase;
	u8* defs = (classIndex == -1) ? m_permanentVarDefs : 0;
	int clearCount = (classIndex == -1) ? m_permanentVarCount : classBase->m_localCount;
	while (clearCount > 0) {
		if ((allowKeep != 0) || ((defs[1] & 0x20) == 0)) {
			*write = 0;
		}
		defs += 4;
		write++;
		clearCount--;
	}

	if (classIndex == -1) {
		request(object, 1, 0, 0, 0);
	}

	onNewObject(object);

	return object;
}


/*
 * --INFO--
 * PAL Address: 0x8006879c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::deleteObject(CFlatRuntime::CObject* object)
{
	object->m_previous->m_next = object->m_next;
	object->m_next->m_previous = object->m_previous;

	*(void**)((char*)*object->m_freeListNode + 4) = object->m_freeListNode[1];
	*(void**)object->m_freeListNode[1] = *object->m_freeListNode;

	object->m_freeListNode[1] = m_objectFreeListHead;
	m_objectFreeListHead = object->m_freeListNode;

	object->m_flagBits.m_constructFlag = 0;

	onDeleteObject(object);
}

/*
 * --INFO--
 * PAL Address: 0x80068824
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::AfterFrame(int mode)
{
	CObject* object = m_objectSentinel.m_next;

	while (object != &m_objectSentinel) {
		CObject* const next = object->m_next;

		if ((mode != 0) || (object->m_flagBits.m_deleteFlag != 0)) {
			object->m_previous->m_next = object->m_next;
			object->m_next->m_previous = object->m_previous;

			*reinterpret_cast<void**>(reinterpret_cast<u8*>(*object->m_freeListNode) + 4) = object->m_freeListNode[1];
			*reinterpret_cast<void**>(object->m_freeListNode[1]) = *object->m_freeListNode;

			object->m_freeListNode[1] = m_objectFreeListHead;
			m_objectFreeListHead = object->m_freeListNode;

			object->m_flagBits.m_constructFlag = 0;

			onDeleteObject(object);
		}

		object = next;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80068910
 * PAL Size: 756b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::Frame(int mode, int unused)
{
	int hasParticle = 0;
	CObject* object = m_objectSentinel.m_next;

	while (object != &m_objectSentinel) {
processObject:
		if ((object->m_flagBits.m_deleteFlag == 0) && (mode != 0)) {
			object->m_flagBits.m_activeFlag = 0;
			if (objectFrame(object) != 0) {
				if (object->m_0x34 != 0) {
					object->m_sp--;
					const int scriptIndex = getTopBit(object->m_0x34);

					reqFinished(scriptIndex, object);

					object->m_0x34 = static_cast<s16>(object->m_0x34 & ~(1U << scriptIndex));

					if (getTopBit(object->m_0x34) >= 0) {
						goto processObject;
					}
				}

				object->m_flagBits.m_deleteFlag = 1;
				if (object->m_particleId == 1) {
					hasParticle = 1;
				}
			}
		}

		CObject* const next = object->m_next;

		if (object->m_flagBits.m_deleteFlag != 0) {
			object->m_previous->m_next = object->m_next;
			object->m_next->m_previous = object->m_previous;

			*reinterpret_cast<void**>(reinterpret_cast<u8*>(*object->m_freeListNode) + 4) = object->m_freeListNode[1];
			*reinterpret_cast<void**>(object->m_freeListNode[1]) = *object->m_freeListNode;

			object->m_freeListNode[1] = m_objectFreeListHead;
			m_objectFreeListHead = object->m_freeListNode;

			object->m_flagBits.m_constructFlag = 0;

			onDeleteObject(object);
		}

		object = next;
	}

	return hasParticle;
}

/*
 * --INFO--
 * PAL Address: 0x80068c04
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CFlatRuntime::CreateDebug(void* filePtr, int debugChunkIndex)
{
	CChunkFile chunkFile(filePtr);
	CChunkFile::CChunk chunk;
	int debugOffset = debugChunkIndex * 0x50;

	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != 'CFLT') {
			continue;
		}

		chunkFile.PushChunk();
		int funcOffset = debugOffset;

		while (chunkFile.GetNextChunk(chunk)) {
			switch (chunk.m_id) {
			case 'NAME':
				break;

			case 'FUNC': {
				chunkFile.PushChunk();
				int blockOffset = funcOffset;

				while (chunkFile.GetNextChunk(chunk)) {
					CFunc* funcBase = reinterpret_cast<CFunc*>(m_funcs + blockOffset);
					switch (chunk.m_id) {
					case 'BLCK':
						chunkFile.PushChunk();

						while (chunkFile.GetNextChunk(chunk)) {
							switch (chunk.m_id) {
							case 'NAME':
								break;

							case 'CODE':
								if (funcBase->m_codeSize != 0) {
									funcBase->m_debugCodeSize = chunk.m_size >> 3;
									funcBase->m_debugCode =
									    new (getDebugStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x181)
									        u8[funcBase->m_debugCodeSize << 3];
									memcpy(funcBase->m_debugCode, chunkFile.GetAddress(), chunk.m_size);
								} else {
									funcBase->m_debugCode = 0;
									funcBase->m_debugCodeSize = 0;
								}
								break;
							}
						}

						chunkFile.PopChunk();
						blockOffset += 0x50;
						funcOffset += 0x50;
						debugOffset += 0x50;
						debugChunkIndex++;
						break;
					}
				}

				chunkFile.PopChunk();
				break;
			}
			}
		}

		chunkFile.PopChunk();
	}

	int result = -1;
	if (debugChunkIndex < m_funcCount) {
		result = debugChunkIndex;
	}
	return result;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::Create(void* filePtr)
{
	CChunkFile::CChunk chunk;

	Destroy();

	CChunkFile chunkFile(filePtr);
	while (chunkFile.GetNextChunk(chunk)) {
		if (chunk.m_id != 'CFLT') {
			continue;
		}

		chunkFile.PushChunk();
		while (chunkFile.GetNextChunk(chunk)) {
			switch (chunk.m_id) {
			case 'NAME':
				strcpy(m_name, chunkFile.GetString());
				break;

			case 'VAL ': {
				m_permanentVarCount = chunk.m_arg0;
				m_permanentVarDefs =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x96)
				        u8[m_permanentVarCount << 2];

				int i = 0;
				u8* variableDef = m_permanentVarDefs;
				const int variableCount = m_permanentVarCount;
				for (; i < variableCount; i++, variableDef += 4) {
					variableDef[0] = chunkFile.Get1();
					variableDef[1] = chunkFile.Get1();
					*reinterpret_cast<u16*>(variableDef + 2) = chunkFile.Get2();
				}
				break;
			}

			case 'CLAS': {
				m_classCount = chunk.m_arg0;

				m_classes =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x9E)
				        CClass[m_classCount];

				int classOffset = 0;
				int classIndex = 0;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					CClass* classBase = reinterpret_cast<CClass*>(reinterpret_cast<u8*>(m_classes) + classOffset);
					classBase->m_index = classIndex;
					switch (chunk.m_id) {
					case 'BLCK': {
						chunkFile.PushChunk();
						while (chunkFile.GetNextChunk(chunk)) {
							switch (chunk.m_id) {
							case 'NAME':
								strcpy(classBase->m_name, chunkFile.GetString());
								break;
							case 'INFO':
								classBase->m_variableCount = chunkFile.Get4();
								break;
							case 'VTBL':
								for (int i = 0; i < 0x80; i++) {
									classBase->m_functionTable[i] = chunkFile.Get4();
								}
								break;
							case 'VAL ':
								classBase->m_localCount = chunk.m_arg0;
								break;
							default:
								break;
							}
						}
						chunkFile.PopChunk();

						classOffset += 0x22C;
						classIndex++;
						break;
					}
					}
				}
				chunkFile.PopChunk();
				break;
			}

			case 'FUNC': {
				m_funcCount = chunk.m_arg0;
				m_funcs =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0xD9)
				        u8[m_funcCount * 0x50];

				int funcIndex = 0;
				int funcOffset = 0;
				chunkFile.PushChunk();
				while (chunkFile.GetNextChunk(chunk)) {
					CFunc* funcBase = reinterpret_cast<CFunc*>(m_funcs + funcOffset);
					funcBase->m_index = funcIndex;
					switch (chunk.m_id) {
					case 'BLCK': {
						chunkFile.PushChunk();
						while (chunkFile.GetNextChunk(chunk)) {
							switch (chunk.m_id) {
							case 'NAME':
								strcpy(funcBase->m_name, chunkFile.GetString());
								break;
							case 'INFO':
								funcBase->m_argCount = chunkFile.Get4();
								funcBase->m_systemKind = chunkFile.Get4();
								funcBase->m_systemIndex = chunkFile.Get4();
								funcBase->m_reqFlagIndex = chunkFile.Get4();
								funcBase->m_useCallerArgs = chunkFile.Get4();
								break;
							case 'VAL ':
								funcBase->m_localCount = chunk.m_arg0;
								break;
							case 'RET ':
								funcBase->m_returnType = chunkFile.Get1();
								funcBase->m_returnFlags = chunkFile.Get1();
								funcBase->m_returnValue = chunkFile.Get2();
								break;
							case 'CODE':
								funcBase->m_codeSize = chunk.m_size;
								funcBase->m_debugCode = 0;
								funcBase->m_debugCodeSize = 0;
								if (funcBase->m_codeSize != 0) {
									funcBase->m_code = reinterpret_cast<u8*>(
									    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x109)
									        u8[chunk.m_size]);
									memcpy(funcBase->m_code, chunkFile.GetAddress(), chunk.m_size);
								} else {
									funcBase->m_code = 0;
								}
								break;
							default:
								break;
							}
						}
						chunkFile.PopChunk();

						funcOffset += 0x50;
						funcIndex++;
						break;
					}
					}
				}
				chunkFile.PopChunk();
				break;
			}

			case 'STR ': {
				m_strCount = chunk.m_arg0;
				m_strOffsets =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x121)
				        u16[m_strCount];
				m_strBlob =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x122)
				        char[chunk.m_size];

				memcpy(m_strBlob, chunkFile.GetAddress(), chunk.m_size);
				u8* const base = chunkFile.GetAddress();
				int i = 0;
				int offset = 0;
				for (; i < m_strCount; i++) {
					*reinterpret_cast<short*>(reinterpret_cast<u8*>(m_strOffsets) + offset) =
					    chunkFile.GetAddress() - base;
					chunkFile.GetString();
					offset += 2;
				}
				break;
			}

			case 'FSTR': {
				m_fstrCount = chunk.m_arg0;
				m_fstrOffsets =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x12F)
				        u16[m_fstrCount];
				m_fstrBlob =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x130)
				        char[chunk.m_size];

				memcpy(m_fstrBlob, chunkFile.GetAddress(), chunk.m_size);
				u8* const base = chunkFile.GetAddress();
				int i = 0;
				int offset = 0;
				for (; i < m_fstrCount; i++) {
					*reinterpret_cast<short*>(reinterpret_cast<u8*>(m_fstrOffsets) + offset) =
					    chunkFile.GetAddress() - base;
					chunkFile.GetString();
					offset += 2;
				}
				break;
			}

			case 'VSTR': {
				m_vstrCount = chunk.m_arg0;
				m_vstrOffsets =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x13D)
				        u16[m_vstrCount];
				m_vstrBlob =
				    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x13E)
				        char[chunk.m_size];

				memcpy(m_vstrBlob, chunkFile.GetAddress(), chunk.m_size);
				u8* const base = chunkFile.GetAddress();
				int i = 0;
				int offset = 0;
				for (; i < m_vstrCount; i++) {
					*reinterpret_cast<short*>(reinterpret_cast<u8*>(m_vstrOffsets) + offset) =
					    chunkFile.GetAddress() - base;
					chunkFile.GetString();
					offset += 2;
				}
				break;
			}

			default:
				break;
			}
		}
		chunkFile.PopChunk();
	}

	createObject(-1);
	m_0x970 = 1;
	m_0x974 = 1;
}

/*
 * --INFO--
 * PAL Address: 0x800695fc
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::CClass::CClass()
{
	m_variableCount = 2;
}

/*
 * --INFO--
 * PAL Address: 0x80069608
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::clear()
{
	u8* const self = reinterpret_cast<u8*>(this);

	*reinterpret_cast<void**>(self + 0x08) = 0;
	m_funcs = 0;
	m_funcCount = 0;
	m_classes = 0;
	m_classCount = 0;
	m_strOffsets = 0;
	m_strBlob = 0;
	m_strCount = 0;
	m_fstrOffsets = 0;
	m_fstrBlob = 0;
	m_fstrCount = 0;
	m_vstrOffsets = 0;
	m_vstrBlob = 0;
	m_vstrCount = 0;

	m_currentCodeIndex.m_codeFunc = -1;
	m_previousCodeIndex.m_codeFunc = -1;

	m_objectSentinel.m_previous = &m_objectSentinel;
	m_objectSentinel.m_next = &m_objectSentinel;
	m_objectSentinel.m_0x32 = 0x10;

	m_freeListPrev = reinterpret_cast<void**>(self + 0x978);
	m_freeListNext = reinterpret_cast<void**>(self + 0x978);
	m_freeListCount = 0x5220;
	m_0x984 = 0;
	m_objectFreeListHead = reinterpret_cast<void**>(self + 0x998);
	m_objectPoolBase = self + 0x1288;

	u8* node = self;
	for (int idx = 0; idx < 0x90; idx++) {
		*reinterpret_cast<void**>(node + 0x998) =
		    (idx == 0) ? (self + 0x988) : (self + ((idx - 1) * 0x10) + 0x998);
		*reinterpret_cast<void**>(node + 0x99C) =
		    (idx == 0x8F) ? (self + 0x988) : (self + ((idx + 1) * 0x10) + 0x998);
		node += 0x10;
	}

	memset(&m_performanceTotalTime, 0, sizeof(m_performanceTotalTime) + sizeof(m_performanceBlock));
}

/*
 * --INFO--
 * PAL Address: 0x800697CC
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::Destroy()
{
	u8* const self = reinterpret_cast<u8*>(this);
	CObject* object = m_objectSentinel.m_next;

	while (object != &m_objectSentinel) {
		CObject* const next = object->m_next;

		object->m_previous->m_next = next;
		object->m_next->m_previous = object->m_previous;

		*reinterpret_cast<void**>(reinterpret_cast<u8*>(*object->m_freeListNode) + 4) = object->m_freeListNode[1];
		*reinterpret_cast<void**>(object->m_freeListNode[1]) = *object->m_freeListNode;

		object->m_freeListNode[1] = m_objectFreeListHead;
		m_objectFreeListHead = object->m_freeListNode;

		object->m_flagBits.m_constructFlag = 0;

		onDeleteObject(object);

		object = next;
	}

	void* ptr = *reinterpret_cast<void**>(self + 0x08);
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	for (int i = 0, off = 0; i < m_funcCount; off += 0x50, i++) {
		delete[] *reinterpret_cast<u8**>(m_funcs + off + 0x34);
		delete[] *reinterpret_cast<u8**>(m_funcs + off + 0x3C);
	}

	ptr = m_funcs;
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	if (m_classes != 0) {
		delete[] m_classes;
	}

	ptr = m_strBlob;
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	ptr = m_strOffsets;
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	ptr = m_fstrBlob;
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	ptr = m_fstrOffsets;
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	ptr = m_vstrBlob;
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	ptr = m_vstrOffsets;
	if (ptr != 0) {
		delete[] reinterpret_cast<u8*>(ptr);
	}

	clear();
}

/*
 * --INFO--
 * PAL Address: 0x8006996c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::Quit()
{
	delete[] (char*)m_permanentVarValues;
	delete[] (char*)m_initScratchA;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::Init()
{
	m_permanentVarValues =
	    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x2A) u8[0x3000];
	m_initScratchA =
	    new (getStage(), const_cast<char*>(s_cflat_runtime_cpp), 0x2B) u8[0x14880];
}

/*
 * --INFO--
 * PAL Address: 0x80069a2c
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CFlatRuntime::~CFlatRuntime()
{
	Destroy();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CFlatRuntime::CFlatRuntime()
{
	const u32 clearBit = 0;

	m_0x970 = clearBit;
	m_0x1298 = 1;

	clear();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::createVal(CChunkFile&, int, CFlatRuntime::CVal*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::CStack::operator= (const CFlatRuntime::CStack&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::callCleanup(CFlatRuntime::CObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::CCodeIndex::operator= (const CFlatRuntime::CCodeIndex&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::initVal(int, CFlatRuntime::CVal*, CFlatRuntime::CStack*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::push(CFlatRuntime::CObject*, CFlatRuntime::CStack*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::pushAddress(CFlatRuntime::CObject*, CFlatRuntime::CStack*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::PrintCodeInfo()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::checkWB(void*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::calc(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::systemVal(CFlatRuntime::CObject*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::setSystemVal(CFlatRuntime::CObject*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::toFunc(CFlatRuntime::CCodeIndex&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::toCode(CFlatRuntime::CCodeIndex&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFlatRuntime::PrintPerformance()
{
	// TODO
}
