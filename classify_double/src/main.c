#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


const uint8_t SIGN_INDEX = 63;
const uint8_t EXP_START_INDEX = 52;
const uint8_t EXP_END_INDEX = 62;
const uint8_t FRAC_START_INDEX = 0;
const uint8_t FRAC_END_INDEX = 51;


/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    return ((number >> index) & 1);
}

/**
 * Utils functions
 */

bool checkForSign(uint64_t number) {
    return getBit(number, SIGN_INDEX);
}

bool checkForAllZeroes(uint64_t number, uint8_t index_start, uint8_t index_end) {
    bool result = true;
    for (uint8_t index = index_start; index <= index_end; index++) {
        result &= (!getBit(number, index));
    }
    return result;
}

bool checkForAllOnes(uint64_t number, uint8_t index_start, uint8_t index_end) {
    bool result = true;
    for (uint8_t index = index_start; index <= index_end; index++) {
        result &= (getBit(number, index));
    }
    return result;
}

bool checkForDenormal(uint64_t number) {
    return checkForAllZeroes(number, EXP_START_INDEX, EXP_END_INDEX);
}

bool checkForNormal(uint64_t number) {
    return (
        !checkForAllZeroes(number, EXP_START_INDEX, EXP_END_INDEX) && 
        !checkForAllOnes(number, EXP_START_INDEX, EXP_END_INDEX)
    );
}

bool checkForInf(uint64_t number) {
    return (
        checkForAllOnes(number, EXP_START_INDEX, EXP_END_INDEX) &&
        checkForAllZeroes(number, FRAC_START_INDEX, FRAC_END_INDEX)
    );
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == 0x0000000000000000;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return (checkForInf(number) && !checkForSign(number));
}

bool checkForMinusInf (uint64_t number) {
    return (checkForInf(number) && checkForSign(number));
}

bool checkForPlusNormal (uint64_t number) {
    return (!checkForSign(number) && checkForNormal(number));
}

bool checkForMinusNormal (uint64_t number) {
    return (checkForSign(number) && checkForNormal(number));
}

bool checkForPlusDenormal (uint64_t number) {
    return (!checkForSign(number) && checkForDenormal(number));
}

bool checkForMinusDenormal (uint64_t number) {
   return (checkForSign(number) && checkForDenormal(number));
}

bool checkForSignalingNan (uint64_t number) {
    return (
        checkForAllOnes(number, EXP_START_INDEX, EXP_END_INDEX) && 
        checkForAllZeroes(number, FRAC_END_INDEX, FRAC_END_INDEX)
    );
}

bool checkForQuietNan (uint64_t number) {
   return (
        checkForAllOnes(number, EXP_START_INDEX, EXP_END_INDEX) && 
        checkForAllOnes(number, FRAC_END_INDEX, FRAC_END_INDEX)
    );
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

