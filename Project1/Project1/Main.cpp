#include "Buffer.h"

int main(int argc, char **argv)
{
	Buffer* myIntBuffer = new Buffer(5);
	myIntBuffer->WriteInt32LE(100);
	myIntBuffer->WriteInt32LE(200);
	myIntBuffer->WriteInt32LE(999999999);

	printf("value100: %d\n", myIntBuffer->ReadInt32LE());
	printf("value200: %d\n", myIntBuffer->ReadInt32LE());
	printf("value300: %d\n", myIntBuffer->ReadInt32LE());

	Buffer* myShortBuffer = new Buffer(5);
	myShortBuffer->WriteShort16LE(100);
	myShortBuffer->WriteShort16LE(99);
	myShortBuffer->WriteShort16LE(9999);

	printf("value100: %d\n", myShortBuffer->ReadShort16LE());
	printf("value200: %d\n", myShortBuffer->ReadShort16LE());
	printf("value300: %d\n", myShortBuffer->ReadShort16LE());

	Buffer* myStringBuffer = new Buffer(5);
	myStringBuffer->WriteStringLE("Supreme Lord Kazzak");
	myStringBuffer->WriteStringLE("Dreadlord Varimathras");
	myStringBuffer->WriteStringLE("C'Thun, God of Madness and Chaos");

	printf("value100: %s\n", myStringBuffer->ReadStringLE().c_str());
	printf("value200: %s\n", myStringBuffer->ReadStringLE().c_str());
	printf("value300: %s\n", myStringBuffer->ReadStringLE().c_str());


	delete myIntBuffer;
	delete myShortBuffer;
	delete myStringBuffer;
	system("pause");
	return 0;
}