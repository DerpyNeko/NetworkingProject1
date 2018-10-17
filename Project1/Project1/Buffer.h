// Buffer.h
// Jenny Moon & Ryan O'Donnell

#ifndef BUFFER_HG
#define BUFFER_HG

#include <vector>

class Buffer {
public:
	Buffer(size_t size);

	void ResizeBuffer();

	void WriteInt32LE(size_t index, int value);
	void WriteInt32LE(int value);

	int ReadInt32LE(size_t index);
	int ReadInt32LE(void);

	void WriteShort16LE(size_t index, short value);
	void WriteShort16LE(short value);

	short ReadShort16LE(size_t index);
	short ReadShort16LE(void);

	void WriteStringLE(size_t index, std::string value);
	void WriteStringLE(std::string value);

	std::string ReadStringLE(size_t index);
	std::string ReadStringLE(void);

private:
	std::vector<uint8_t> m_Buffer;

	int mReadIndex;
	int mWriteIndex;
};

#endif
