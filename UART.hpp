#ifndef uartHPP
#define uartHPP

template<class T>
UARTClass& operator << (UARTClass& theSerial, const T& theValue)
{
    theSerial.print(theValue);
    return theSerial;
}

#endif
