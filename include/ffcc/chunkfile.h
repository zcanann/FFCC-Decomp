#ifndef _FFCC_CHUNKFILE_H_
#define _FFCC_CHUNKFILE_H_

class CChunkFile
{
	class CChunk
	{
		CChunk();
		~CChunk();
	};
	
	CChunkFile();
	CChunkFile(void *);

	void SetBuf(void *);
	void PushChunk();
	void PopChunk();

	void GetNextChunk(CChunkFile::CChunk &);
	void GetAddress();
	void Get(void *, long);
	void Get1();
	void Get2();
	void Get4();
	void GetF4();
	void GetString();
	void Align(unsigned long);
};

#endif // _FFCC_CHUNKFILE_H_
