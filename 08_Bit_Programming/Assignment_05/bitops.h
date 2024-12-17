#ifndef BITSOP_H
#define BITSOP_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

// 12. Function to check if the bitmap is full (all bits set to 1)
bool bitmap_is_full(uint32_t *bitmap, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (bitmap[i] != ~0U) {
            return false;
        }
    }
    return true;
}

// 13. Function to match a pattern in a bitmap
bool bitmap_pattern_match(uint32_t *bitmap, const char *binary_string, int n_bits, int *i) {
    int bitmap_size = n_bits / 32 + (n_bits % 32 != 0);
    int pattern_length = strlen(binary_string);

    for (int start = 0; start <= n_bits - pattern_length; start++) {
        bool match = true;
        for (int j = 0; j < pattern_length; j++) {
            if (binary_string[j] != 'x') {
                int bit_pos = start + j;
                int word_index = bit_pos / 32;
                int bit_index = bit_pos % 32;
                bool bit_value = (bitmap[word_index] >> bit_index) & 1;
                if (binary_string[j] == '1' && !bit_value) {
                    match = false;
                    break;
                }
                if (binary_string[j] == '0' && bit_value) {
                    match = false;
                    break;
                }
            }
        }
        if (match) {
            *i = start;
            return true;
        }
    }
    return false;
}

// 14. Iteration macros
#define ITERATE_BITMAP_BEGIN(bitmap_ptr, bit_state) \
    for (size_t _idx = 0; _idx < (sizeof((bitmap_ptr)) / sizeof(uint32_t)) * 32; _idx++) { \
        (bit_state) = ((bitmap_ptr)[_idx / 32] >> (_idx % 32)) & 1;

#define ITERATE_BITMAP_END(bitmap_ptr, bit_state) }

#endif // BITSOP_H