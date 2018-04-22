

/**
* CRC constructor. Performs the cyclic redundancy check.
* Constructor sets the divisor to the binary string 10101
*/
template <typename T>
CRC16<T>::CRC16() {
    this->divisor = 0b10111011; // 10101 in binary
}

/**
* Finds the number of bits in a given value.
* @param val a T value which is passed by reference and not changed.
* @return unsigned char representing the number of bits in val. 
*/
template <typename T>
unsigned char CRC16<T>::numBits(const T &val) {
    if (val == 0)
        return 0;
    return (unsigned char)(log2(val)) + 1;
}

/**
 * Runs the CRC algorithm for a given binary value, utilizing the
 * default divisor of 0x51 (hexadecimal). This function has O(n) complexity
 * where n is the number of bytes in the value. This appends the crc val to the end
 * of the given value, acting as the transmitter method.
 * @param value a T representing the number to be evaluated. ***Value must be able to be shifted left by 4 bits
 * @return the remainder of the algorithm
 */
template <typename T>
T CRC16<T>::transmit(T value) {
    T newDivisor = this->divisor;
    unsigned char divisorBitSize = numBits(this->divisor);
    T crc = value << (divisorBitSize-1); // append zero's
    unsigned char numBitsCrc = numBits(crc);
    newDivisor = this->divisor << (numBitsCrc - divisorBitSize); 

    while (numBitsCrc >= divisorBitSize) {
        if (numBitsCrc == numBits(newDivisor)) {
            crc = crc^newDivisor;
            numBitsCrc = numBits(crc);
        }
        newDivisor = this->divisor << (numBitsCrc - divisorBitSize); 
    }
    return (value << (divisorBitSize-1))^crc;
}

/**
 * Runs the CRC algorithm for a given binary value, utilizing the
 * default divisor of 0x51 (hexadecimal). This function has O(n) complexity
 * where n is the number of bytes in the value. This acts as the receiver method,
 * informing the client of whether the data was corrupted or not. 
 * @param value a T representing the number to be evaluated. 
 * @return boolean indicating whether there is a remainder of 0 at the end
 *     of this algorithm. 
 */
template <typename T>
bool CRC16<T>::receive(T value) {
    T newDivisor = this->divisor;
    unsigned char divisorBitSize = numBits(this->divisor);
    unsigned char numBitsCrc = numBits(value);

    newDivisor = this->divisor << (numBitsCrc - divisorBitSize); 

    while(numBitsCrc >= divisorBitSize) {
        if (numBitsCrc == numBits(newDivisor)) {
            value = value^newDivisor;
            numBitsCrc = numBits(value);
        }
        newDivisor = this->divisor << (numBitsCrc - divisorBitSize); 
    }
    return value == 0;
}

/**
* Encapsulation method for divisor field.
* @param newDivisor newDivisor value to be filled in for divisor.
*     cannot be less than or equal to 0
*/
template <typename T>
void CRC16<T>::setDivisor(T newDivisor) {
    if (newDivisor <= 0) {
        return;
    }
    divisor = newDivisor;
}