#include "Buffer.h"

Buffer::Buffer(size_t size) : mWriteIndex(0), mReadIndex(0)
{
	m_IntBuffer.resize(size);
	m_ShortBuffer.resize(size);
}

void Buffer::WriteInt32LE(size_t index, int value)
{
	m_IntBuffer[index] = value;
	m_IntBuffer[index + 1] = value >> 8;
	m_IntBuffer[index + 2] = value >> 16;
	m_IntBuffer[index + 3] = value >> 24;
}

void Buffer::WriteInt32LE(int value)
{
	m_IntBuffer[mWriteIndex] = value;
	m_IntBuffer[mWriteIndex + 1] = value >> 8;
	m_IntBuffer[mWriteIndex + 2] = value >> 16;
	m_IntBuffer[mWriteIndex + 3] = value >> 24;
	mWriteIndex += 4;
}

int Buffer::ReadInt32LE(size_t index)
{
	uint32_t value = m_IntBuffer[index];
	value |= m_IntBuffer[index + 1] << 8;
	value |= m_IntBuffer[index + 2] << 16;
	value |= m_IntBuffer[index + 3] << 24;
	return value;
}

int Buffer::ReadInt32LE(void)
{
	int32_t value = m_IntBuffer[mReadIndex];
	value |= m_IntBuffer[mReadIndex + 1] << 8;
	value |= m_IntBuffer[mReadIndex + 2] << 16;
	value |= m_IntBuffer[mReadIndex + 3] << 24;
	mReadIndex += 4;
	return value;
}

void Buffer::WriteShort16LE(size_t index, short value)
{
	m_ShortBuffer[index] = value;
	m_ShortBuffer[index + 1] = value >> 8;
}

void Buffer::WriteShort16LE(short value)
{
	m_ShortBuffer[mWriteIndex] = value;
	m_ShortBuffer[mWriteIndex + 1] = value >> 8;
	mWriteIndex += 2;
}

int Buffer::ReadShort16LE(size_t index)
{
	uint16_t value = m_ShortBuffer[index];
	value |= m_ShortBuffer[index + 1] << 8;
	return value;
}

int Buffer::ReadShort16LE(void)
{
	uint16_t value = m_ShortBuffer[mReadIndex];
	value |= m_ShortBuffer[mReadIndex + 1] << 8;
	mReadIndex += 2;
	return value;
}

void Buffer::WriteShort16LE(size_t index, short value)
{
	m_ShortBuffer[index] = value;
	m_ShortBuffer[index + 1] = value >> 8;
}

void Buffer::WriteShort16LE(short value)
{
	m_ShortBuffer[mWriteIndex] = value;
	m_ShortBuffer[mWriteIndex + 1] = value >> 8;
	mWriteIndex += 2;
}

int Buffer::ReadShort16LE(size_t index)
{
	uint16_t value = m_ShortBuffer[index];
	value |= m_ShortBuffer[index + 1] << 8;
	return value;
}

int Buffer::ReadShort16LE(void)
{
	uint16_t value = m_ShortBuffer[mReadIndex];
	value |= m_ShortBuffer[mReadIndex + 1] << 8;
	mReadIndex += 2;
	return value;
}
