#include "Buffer.h"

Buffer::Buffer(size_t size) : mWriteIndex(0), mReadIndex(0)
{
	m_Buffer.resize(size, 0);
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
	m_Buffer[index] = value[0];

	for (unsigned int i = 1; i < value.length(); i++)
	{
		m_Buffer[index + i] = value[i];
		index = i;
	}

	//mWriteIndex += (index + 2);
}

void Buffer::WriteStringLE(std::string value)
{
	int index = 0;
	m_Buffer[mWriteIndex] = value[index];

	for (unsigned int i = 1; i < value.length(); i++)
	{
		m_Buffer[mWriteIndex + i] = value[i];
		index = i;
	}

	mWriteIndex += (index + 2);
}

std::string Buffer::ReadStringLE(size_t index)
{
	std::string value = "";
	value = m_Buffer[index];

	for (int i = 1; i < mWriteIndex; i++)
	{
		if (m_Buffer[index + i] == '\0')
		{
			mReadIndex += (index + 2);
			break;
		}

		value += m_Buffer[index + i];
		index = i;
	}


	return value;
}

std::string Buffer::ReadStringLE(void)
{
	int index = 0;
	std::string value = "";
	value = m_Buffer[mReadIndex];

	for (int i = 1; i < mWriteIndex; i++)
	{
		if (m_Buffer[mReadIndex + i] == '\0')
		{
			mReadIndex += (index + 2);
			break;
		}

		value += m_Buffer[mReadIndex + i];
		index = i;
	}

	
	return value;
}
