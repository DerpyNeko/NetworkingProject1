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

	int ReadShort16LE(size_t index);
	int ReadShort16LE(void);

	void WriteShort16LE(size_t index, short value);
	void WriteShort16LE(short value);

	int ReadShort16LE(size_t index);
	int ReadShort16LE(void);

private:
	std::vector<uint8_t> m_IntBuffer;
	std::vector<uint8_t> m_ShortBuffer;

	int mReadIndex;
	int mWriteIndex;
};

#endif
