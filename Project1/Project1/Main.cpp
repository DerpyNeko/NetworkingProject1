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

	Buffer* myLongBuffer = new Buffer(512);
	myLongBuffer->WriteLong64LE(100);
	myLongBuffer->WriteLong64LE(990);
	myLongBuffer->WriteLong64LE(300);

	printf("value100: %d\n", myLongBuffer->ReadLong64LE());
	printf("value200: %d\n", myLongBuffer->ReadLong64LE());
	printf("value300: %d\n", myLongBuffer->ReadLong64LE());


	delete myIntBuffer;
	delete myShortBuffer;
	delete myLongBuffer;
	system("pause");
	return 0;
}