#ifndef _FFCC_CHUNKFILE_H_
#define _FFCC_CHUNKFILE_H_

class CChunkFile
{
public:
	class CChunk
	{
	public:
		CChunk();
		~CChunk();

		unsigned int m_id;      // 0x00 - FourCC tag, e.g. 'TANM', 'NAME', 'IMAG', 'SIZE'.
		unsigned int m_arg0;    // 0x04 - chunk-specific argument; often a count or flags.
		unsigned int m_version; // 0x08 - chunk-specific argument; often version/variant.
		unsigned int m_size;    // 0x0C - payload size in bytes.
	};
	
	CChunkFile();
	CChunkFile(void* filePtr);

	void SetBuf(void* filePtr);
	void PushChunk();
	void PopChunk();
	bool GetNextChunk(CChunkFile::CChunk& outChunk);
	unsigned char* GetAddress();
	void Get(void*, long);
	unsigned char Get1();
	unsigned short Get2();
	unsigned int Get4();
	float GetF4();
	char* GetString();
	void Align(unsigned long);

private:
	struct ChunkScope {
		unsigned int m_scopeSize;
		int m_lastChunkSize;
		int m_scopeOffset;
		unsigned char* m_base;
		unsigned char* m_headerPtr;
	};

    unsigned int m_scopeSize;    // 0x00
    int m_lastChunkSize;         // 0x04
    int m_scopeOffset;           // 0x08
    unsigned char *m_base;       // 0x0C
    unsigned char *m_headerPtr;  // 0x10
    unsigned char *m_cursor;     // 0x14
    int m_stackDepth;            // 0x18
    ChunkScope m_chunkScopes[1]; // 0x1C (Possibly larger?)
};

#endif // _FFCC_CHUNKFILE_H_
