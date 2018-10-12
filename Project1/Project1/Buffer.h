#ifndef BUFFER_HG
#define BUFFER_HG

#include <vector>

class Buffer {
public:
	Buffer(size_t size);

	void WriteInt32LE(size_t index, int value);
	void WriteInt32LE(int value);

	int ReadInt32LE(size_t index);
	int ReadInt32LE(void);

	void WriteShort16LE(size_t index, short value);
	void WriteShort16LE(short value);

	short ReadShort16LE(size_t index);
	short ReadShort16LE(void);

	void WriteLong64LE(size_t index, long value);
	void WriteLong64LE(long value);

	long ReadLong64LE(size_t index);
	long ReadLong64LE(void);

private:
	std::vector<uint8_t> m_Buffer;

	int mReadIndex;
	int mWriteIndex;
};

#endif
