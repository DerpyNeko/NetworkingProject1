#include "Buffer.h"

Buffer::Buffer(size_t size) : mWriteIndex(0), mReadIndex(0)
{
	m_Buffer.resize(size);
}

// int 32
void Buffer::WriteInt32LE(size_t index, int value)
{
	m_Buffer[index] = value;
	m_Buffer[index + 1] = value >> 8;
	m_Buffer[index + 2] = value >> 16;
	m_Buffer[index + 3] = value >> 24;
}

void Buffer::WriteInt32LE(int value)
{
	m_Buffer[mWriteIndex] = value;
	m_Buffer[mWriteIndex + 1] = value >> 8;
	m_Buffer[mWriteIndex + 2] = value >> 16;
	m_Buffer[mWriteIndex + 3] = value >> 24;
	mWriteIndex += 4;
}

int Buffer::ReadInt32LE(size_t index)
{
	uint32_t value = m_Buffer[index];
	value |= m_Buffer[index + 1] << 8;
	value |= m_Buffer[index + 2] << 16;
	value |= m_Buffer[index + 3] << 24;
	return value;
}

int Buffer::ReadInt32LE(void)
{
	int32_t value = m_Buffer[mReadIndex];
	value |= m_Buffer[mReadIndex + 1] << 8;
	value |= m_Buffer[mReadIndex + 2] << 16;
	value |= m_Buffer[mReadIndex + 3] << 24;
	mReadIndex += 4;
	return value;
}

// short 16
void Buffer::WriteShort16LE(size_t index, short value)
{
	m_Buffer[index] = value;
	m_Buffer[index + 1] = value >> 8;
}

void Buffer::WriteShort16LE(short value)
{
	m_Buffer[mWriteIndex] = value;
	m_Buffer[mWriteIndex + 1] = value >> 8;
	mWriteIndex += 2;
}

short Buffer::ReadShort16LE(size_t index)
{
	uint16_t value = m_Buffer[index];
	value |= m_Buffer[index + 1] << 8;
	return value;
}

short Buffer::ReadShort16LE(void)
{
	uint16_t value = m_Buffer[mReadIndex];
	value |= m_Buffer[mReadIndex + 1] << 8;
	mReadIndex += 2;
	return value;
}

// String
void Buffer::WriteStringLE(size_t index, std::string value)
{
	m_Buffer[index] = value[index];
	m_Buffer[index + 1] = value[index] >> 8;
}

void Buffer::WriteStringLE(std::string value)
{
	m_Buffer[mWriteIndex] = value[mWriteIndex];
	m_Buffer[mWriteIndex + 1] = value[mWriteIndex] >> 8;
	mWriteIndex += 2;
}

std::string Buffer::ReadStringLE(size_t index)
{
	std::string value = (char*)m_Buffer[index];
	value[index] |= m_Buffer[index + 1] << 8;
	return value;
}

std::string Buffer::ReadStringLE(void)
{
	std::string value (m_Buffer.begin(), m_Buffer.end());
	value[mReadIndex] |= m_Buffer[mReadIndex + 1] << 8;
	mReadIndex += 1;
	return value;
}
