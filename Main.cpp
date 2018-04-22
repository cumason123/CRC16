#include "CRC16.h"
#include <stdio.h>
int main() {
	long int val = 0xFFF;
	CRC16<long int> *crc16 = new CRC16<long int>();
	printf("%X\n", crc16->receive(crc16->transmit(val)+3));
}