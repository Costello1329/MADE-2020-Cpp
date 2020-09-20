#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    uint64_t mask = 1 << index;
    uint64_t tmp = mask & number;
    tmp >>= index;
    return tmp;
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    uint64_t zero = 0;
    return !(zero ^ number);
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    if (!getBit(number, 63)) {
        for (uint8_t i = 0; i <= 51; i++) {
            if (getBit(number, i)) {
                return 0;
            }
        }
        
        for (uint8_t i = 52; i <= 62; i++) {
            if (!getBit(number, i)) {
                return 0;
            }
        }
    }else{
        return 0;
    }
    return 1;
}

bool checkForMinusInf (uint64_t number) {
    if (getBit(number, 63)) {
        for (uint8_t i = 0; i <= 51; i++) {
            if (getBit(number, i)) {
                return 0;
            }
        }
        
        for (uint8_t i = 52; i <= 62; i++) {
            if (!getBit(number, i)) {
                return 0;
            }
        }
    }else{
        return 0;
    }
    return 1;
}

bool checkForPlusNormal (uint64_t number) {
    int zeros = 0, ones = 0;
    
    if (!getBit(number, 63)) {
        for (uint8_t i = 52; i < 63; i++){
            if (getBit(number, i) & 1) {
                ones++;
            }else{
                zeros++;
            }
        }
        if (zeros == 11  || ones == 11) {
            return 0;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}

bool checkForMinusNormal (uint64_t number) {
    int zeros = 0, ones = 0;
    
    if (getBit(number, 63)) {
        for (uint8_t i = 52; i < 63; i++){
            if (getBit(number, i) & 1) {
                ones++;
            }else{
                zeros++;
            }
        }
        if (zeros == 11  || ones == 11) {
            return 0;
        }else{
            return 1;
        }
    }else{
        return 0;
    }

}

bool checkForPlusDenormal (uint64_t number) {
    int zeros = 0, ones = 0;
    for(uint8_t i = 52; i <= 63; i++){
        if (getBit(number, i)) {
            return 0;
        }
    }
    
    for (uint8_t i = 0; i <= 51; i++) {
        if (getBit(number, i)) {
            ones++;
        }else{
            zeros++;
        }
    }
    
    if (zeros == 52) {
        return 0;
    }else{
        return 1;
    }
}

bool checkForMinusDenormal (uint64_t number) {
    int zeros = 0, ones = 0;
    if (getBit(number, 63)) {
        for(uint8_t i = 52; i <= 62; i++){
            if (getBit(number, i)) {
                return 0;
            }
        }
        
        for (uint8_t i = 0; i <= 51; i++) {
            if (getBit(number, i)) {
                ones++;
            }else{
                zeros++;
            }
        }
        
        if (zeros == 52) {
            return 0;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
    
}

bool checkForSignalingNan (uint64_t number) {
    int zeros = 0, ones = 0;
    
    for(uint8_t i = 52; i <= 62; i++){
        if (!getBit(number, i)) {
            return 0;
        }
    }
    
    for (uint8_t i = 0; i <= 51; i++) {
        if (getBit(number, i)) {
            ones++;
        }else{
            zeros++;
        }
    }
    
    if (zeros == 52) {
        return 0;
    }else{
        return 1;
    }
}

bool checkForQuietNan (uint64_t number) {
    for(uint8_t i = 52; i <= 62; i++){
        if (!getBit(number, i)) {
            return 0;
        }
    }
    
    if (getBit(number, 51)) {
        return 1;
    }else{
        return 0;
    }
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


int main(){
    //printf("%i", convertToUint64(1.3));
    uint64_t x = convertToUint64(NAN);
    for (uint8_t i = 0; i < 64; i++) {
        printf("%d", getBit(x, 63 - i));
    }
    printf("\n");
    printf("%d", checkForPlusDenormal(x));
    
    
}
