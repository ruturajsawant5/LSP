#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TLV_OVERHEAD_SIZE 2

/* Macros for iterating through TLVs */
#define ITERATE_TLV_BEGIN(start_ptr, type, length, tlv_ptr, buffer_size) \
    for (uint8_t *ptr = start_ptr; \
         (ptr < start_ptr + buffer_size) && \
         ((type = *ptr), (length = *(ptr + 1)), (tlv_ptr = ptr + TLV_OVERHEAD_SIZE), 1); \
         ptr += TLV_OVERHEAD_SIZE + length)

#define ITERATE_TLV_END(start_ptr, type, length, tlv_ptr, buffer_size)

/* TLV Codes */
#define NAME_TLV_CODE 1    // String format, Unit Data length 32B
#define WEBSITE_TLV_CODE 2 // String format, Unit Data length 64B
#define EMP_ID_TLV_CODE 3  // Integer format, Unit Data length 8B
#define IP_ADDRESS_TLV_CODE 4 // IP Address format, Unit Data length 16B

/* Helper function to get unit data size for each TLV */
static uint8_t get_unit_data_size(uint8_t tlv_type) {
    switch (tlv_type) {
        case NAME_TLV_CODE:
            return 32;
        case WEBSITE_TLV_CODE:
            return 64;
        case EMP_ID_TLV_CODE:
            return 8;
        case IP_ADDRESS_TLV_CODE:
            return 16;
        default:
            return 0;
    }
}

/* Function to decode and print TLV buffer */
void decode_tlv_buffer(unsigned char *tlv_buffer, uint32_t tlv_buffer_size) {
    uint8_t tlv_type;
    uint8_t tlv_len;
    uint8_t *tlv_value;

    int units = 0, i = 0;

    ITERATE_TLV_BEGIN(tlv_buffer, tlv_type, tlv_len, tlv_value, tlv_buffer_size) {
        units = tlv_len / get_unit_data_size(tlv_type);

        switch (tlv_type) {
            case NAME_TLV_CODE:
                for (i = 0; i < units; i++) {
                    printf("TLV Type = %d, Name = %s\n", tlv_type,
                           tlv_value + (i * get_unit_data_size(tlv_type)));
                }
                break;

            case WEBSITE_TLV_CODE:
                for (i = 0; i < units; i++) {
                    printf("TLV Type = %d, Website Name = %s\n", tlv_type,
                           tlv_value + (i * get_unit_data_size(tlv_type)));
                }
                break;

            case EMP_ID_TLV_CODE:
                for (i = 0; i < units; i++) {
                    printf("TLV Type = %d, Emp ID = %lu\n", tlv_type,
                           *(uint64_t *)(tlv_value + (i * get_unit_data_size(tlv_type))));
                }
                break;

            case IP_ADDRESS_TLV_CODE:
                for (i = 0; i < units; i++) {
                    uint8_t *ip_addr = tlv_value + (i * get_unit_data_size(tlv_type));
                    printf("TLV Type = %d, IP Address = %d.%d.%d.%d\n", tlv_type,
                           ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
                }
                break;

            default:
                ; // Ignore unrecognized TLV types
        }
    }
    ITERATE_TLV_END(tlv_buffer, tlv_type, tlv_len, tlv_value, tlv_buffer_size);
}

/* Function to prepare the TLV buffer */
unsigned char *prepare_tlv_buffer(uint32_t *total_buffer_size) {
    *total_buffer_size = 288;
    unsigned char *tlv_buffer = calloc(1, *total_buffer_size);
    unsigned char *temp = NULL;

    // NAME_TLV_CODE
    *tlv_buffer = NAME_TLV_CODE;
    *(tlv_buffer + 1) = 64;
    strncpy((char *)(tlv_buffer + TLV_OVERHEAD_SIZE), "Abhishek Sagar", 32);
    strncpy((char *)(tlv_buffer + TLV_OVERHEAD_SIZE + 32), "Shivani", 32);

    temp = tlv_buffer + TLV_OVERHEAD_SIZE + (32 * 2);

    // WEBSITE_TLV_CODE
    *temp = WEBSITE_TLV_CODE;
    *(temp + 1) = 128;
    strncpy((char *)(temp + TLV_OVERHEAD_SIZE), "www.csepracticals.com", 64);
    strncpy((char *)(temp + TLV_OVERHEAD_SIZE + 64), "www.facebook.com", 64);

    temp += TLV_OVERHEAD_SIZE + (64 * 2);

    // EMP_ID_TLV_CODE
    *temp = EMP_ID_TLV_CODE;
    *(temp + 1) = 24;

    uint64_t *emp_id = (uint64_t *)(temp + TLV_OVERHEAD_SIZE);
    *emp_id = 52437;
    *(emp_id + 1) = 52438;
    *(emp_id + 2) = 52439;

    temp += TLV_OVERHEAD_SIZE + (8 * 3);

    // IP_ADDRESS_TLV_CODE
    *temp = IP_ADDRESS_TLV_CODE;
    *(temp + 1) = 64;

    uint8_t ip_addresses[][4] = {
        {122, 1, 1, 1}, {122, 1, 1, 2}, {122, 1, 1, 3}, {122, 1, 1, 4}};
    uint8_t *ip_data = temp + TLV_OVERHEAD_SIZE;

    for (int i = 0; i < 4; i++) {
        memcpy(ip_data + (i * 16), ip_addresses[i], 4);
    }

    return tlv_buffer;
}

int main(int argc, char **argv) {
    uint32_t total_buffer_size = 0;
    unsigned char *tlv_buffer = prepare_tlv_buffer(&total_buffer_size);
    if (tlv_buffer && total_buffer_size)
        decode_tlv_buffer(tlv_buffer, total_buffer_size);
    free(tlv_buffer);
    return 0;
}
