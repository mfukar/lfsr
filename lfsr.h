/*
 * Galois LFSR software implementation header file
 */
#include <stdint.h>

typedef	uint64_t lfsr_data_t;

typedef struct {
        lfsr_data_t data,
                    polynomial,
                    mask;
} lfsr_t;

void          GLFSR_init(lfsr_t *, lfsr_data_t, lfsr_data_t);
unsigned char GLFSR_next(lfsr_t *);
