#ifndef _CRC16_H_
#define _CRC16_H_
#include <math.h>       /* log2 */


template <typename T>
class CRC16 {
public:
	CRC16();
	T transmit(T value);
	bool receive(T value);
	void setDivisor(T newDivisor);
private:
	T divisor;
	unsigned char numBits(const T &val);
};

#include "CRC16.cpp"
#endif

