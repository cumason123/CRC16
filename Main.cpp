#include "CRC16/CRC16.h"
#include <stdio.h>
#include <random>
#include <stdlib.h>     /* srand, rand */

bool unittest(CRC16<long int> &crc16, long int val, unsigned char remainder = 0) {
	printf("Unit test on value %d\n", val);
	bool success = crc16.receive(crc16.transmit(val)+remainder);
	bool unitSuccess = (remainder==0)==success;
	printf("Success val: %d\n\n", unitSuccess);
	return unitSuccess;
}
int main() {
    int iSecret;
    float correctness = 0.0;
	CRC16<long int> crc16;
	srand (time(NULL));
	unsigned short iterations = 65535;
	unsigned short numIncorrect;
	for (int i = 0; i < iterations; i++) {
			iSecret = rand() % 3 + 1;
			printf("%d\n", i);
			bool success = unittest(crc16, i, iSecret%3);
			correctness += success;
			if (success == 0) {
				numIncorrect++;
			}
	}
	printf("Number correct: %d\n", correctness);
	printf("Number incorrect: %d\n", numIncorrect);
	printf("Success rate: %f\n", correctness/(iterations));
}