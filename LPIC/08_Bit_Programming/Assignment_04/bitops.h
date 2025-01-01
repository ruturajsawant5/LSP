#ifndef BITSOP_H
#define BITSOP_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// 1. Function to print the bit pattern of a uint32_t number
void print_bit_pattern(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" "); // Group bits in sets of 4
    }
    printf("\n");
}

// 2. Macro to set xth bit in number n
#define SET_BIT(n, bit) ((n) |= (bit))

// 3. Macro to unset xth bit in number n
#define UNSET_BIT(n, bit) ((n) &= ~(bit))

// 4. Macro to check if xth bit is set
#define IS_BIT_SET(n, bit) (((n) & (bit)) != 0)

// 5. Macro to toggle xth bit in number n
#define TOGGLE_BIT(n, bit) ((n) ^= (bit))

// 6. Macro to compute the complement of number n (without modifying n)
#define COMPLEMENT(n) (~(n))

// 7. Function to count the number of bits set in a uint32_t number
uint8_t count_bit_set(uint32_t n) {
    uint8_t count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// 8. Function to rotate the bit pattern of number n by k units to the right
uint32_t rotate_right(uint32_t n, uint8_t k) {
    return (n >> k) | (n << (32 - k));
}

// 9. Function to apply a mask on an IP address and print the resultant bit pattern
void apply_mask_and_print(const char* ip_address, uint8_t mask) {
    uint32_t ip = 0;
    sscanf(ip_address, "%u.%u.%u.%u", (uint32_t *)&((uint8_t*)&ip)[3], (uint32_t *)&((uint8_t*)&ip)[2], (uint32_t *)&((uint8_t*)&ip)[1], (uint32_t *)&((uint8_t*)&ip)[0]);
    uint32_t subnet_mask = (~0U) << (32 - mask);
    uint32_t result = ip & subnet_mask;
    print_bit_pattern(result);
}

// 10. Function to extract bits in interval [p, q] and set remaining bits to zero
uint32_t extract_bits(uint32_t n, uint8_t p, uint8_t q) {
    uint32_t mask = ((1U << (q - p + 1)) - 1) << p;
    return n & mask;
}

// 11. Function to test whether n is a power of two
bool isPowerOfTwo(uint32_t n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

#endif // BITSOP_H