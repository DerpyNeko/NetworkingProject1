// TODO: the project
#include "Buffer.h"

int main(int argc, char **argv)
{
	Buffer* myIntBuffer = new Buffer(512);
	myIntBuffer->WriteInt32LE(100);
	myIntBuffer->WriteInt32LE(200);
	myIntBuffer->WriteInt32LE(513);

	printf("value100: %d\n", myIntBuffer->ReadInt32LE());
	printf("value200: %d\n", myIntBuffer->ReadInt32LE());
	printf("value300: %d\n", myIntBuffer->ReadInt32LE());

	Buffer* myShortBuffer = new Buffer(512);
	myShortBuffer->WriteShort16LE(100);
	myShortBuffer->WriteShort16LE(99);
	myShortBuffer->WriteShort16LE(300);

	printf("value100: %d\n", myShortBuffer->ReadShort16LE());
	printf("value200: %d\n", myShortBuffer->ReadShort16LE());
	printf("value300: %d\n", myShortBuffer->ReadShort16LE());

	Buffer* myStringBuffer = new Buffer(512);
	myStringBuffer->WriteStringLE("12444");
	myStringBuffer->WriteStringLE("123123");
	myStringBuffer->WriteStringLE("99385");

	printf("value100: %s\n", myStringBuffer->ReadStringLE());
	printf("value200: %s\n", myStringBuffer->ReadStringLE());
	printf("value300: %s\n", myStringBuffer->ReadStringLE());


	delete myIntBuffer;
	delete myShortBuffer;
	delete myStringBuffer;
	system("pause");
	return 0;
}