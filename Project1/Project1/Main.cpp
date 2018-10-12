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
	myShortBuffer->WriteShort16LE(9999999900);
	myShortBuffer->WriteShort16LE(300);

	printf("value100: %d\n", myShortBuffer->ReadShort16LE());
	printf("value200: %d\n", myShortBuffer->ReadShort16LE());
	printf("value300: %d\n", myShortBuffer->ReadShort16LE());

	delete myIntBuffer;
	delete myShortBuffer;
	system("pause");
	return 0;
}