#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

uint64_t getBit (const uint64_t number, const uint8_t index) { // changed bool to uint64 to simplify my solution
    uint64_t mask = 1;
    mask <<= index;
    uint64_t temp = mask & number;
    temp >>= index;
    return temp;
}


/**
 * Checkers here:
 */


/*Returns true for negative numbers*/
bool isNegative (uint64_t number) {   
    return ( getBit(number, 63) == 1 ); //check if bit #63 is equal to 1
}

bool isExpBitEqualTo (uint64_t number, uint64_t bit_value) { 
    for (uint8_t i = 62; i > 51; i--){
        if ( getBit(number, i) != bit_value ){
            return 0;        
        }
    }
    return 1;
}


// Exp bits == 0, last fraction bit == 1
bool isDenormal (uint64_t number) {   
    return ( isExpBitEqualTo(number, 0) ) && ( getBit(number, 0) == 1);
}      


// Exp bits are not simultaneously equal to 1 or to 0
bool isNormal(uint64_t number) {   
    return ( ! isExpBitEqualTo(number, getBit(number, 62)) );
}  


bool checkForPlusZero (uint64_t number) {
    return number == 0x0000000000000000;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return number == 0x7ff0000000000000;
}

bool checkForMinusInf (uint64_t number) {
    return number == 0xfff0000000000000;
}

bool checkForPlusNormal (uint64_t number) {
    return ( ( ! isNegative(number) ) && isNormal(number) );
}

bool checkForMinusNormal (uint64_t number) {
    return ( isNegative(number)  && isNormal(number) );
}

bool checkForPlusDenormal (uint64_t number) {
    return ( (! isNegative(number)) && isDenormal(number)  );
}

bool checkForMinusDenormal (uint64_t number) {
    return ( isNegative(number)  && isDenormal(number) );
}

// Negative, exp bits ==1, first fraction bit ==0, last fraction bit ==1
bool checkForSignalingNan (uint64_t number) {
    return isExpBitEqualTo(number, 1) && getBit(number, 51) == 0 && getBit(number, 0) == 1;
}

// Negative, exp bits ==1, first fraction bit ==1
bool checkForQuietNan (uint64_t number) {
    return isExpBitEqualTo(number, 1) && getBit(number, 51) == 1;
}

void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
