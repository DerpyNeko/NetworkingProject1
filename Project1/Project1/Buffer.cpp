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

// long 64
void Buffer::WriteLong64LE(size_t index, long value)
{
	m_Buffer[index] = value;
	m_Buffer[index + 1] = value >> 8;
}

void Buffer::WriteLong64LE(long value)
{
	m_Buffer[mWriteIndex] = value;
	m_Buffer[mWriteIndex + 1] = value >> 8;
	mWriteIndex += 2;
}

long Buffer::ReadLong64LE(size_t index)
{
	uint16_t value = m_Buffer[index];
	value |= m_Buffer[index + 1] << 8;
	return value;
}

long Buffer::ReadLong64LE(void)
{
	uint16_t value = m_Buffer[mReadIndex];
	value |= m_Buffer[mReadIndex + 1] << 8;
	mReadIndex += 2;
	return value;
}
