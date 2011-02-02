/*
 * Galois LFSR software implementation.
 *
 * © 2010 Michael Foukarakis
 */
#include <stdint.h>

typedef	uint64_t	lfsr_data;

typedef struct {
	lfsr_data	data;
	lfsr_data	polynomial;
	lfsr_data	mask;
} lfsr_t;

void 		GLFSR_init(lfsr_t *, lfsr_data, lfsr_data);
unsigned char	GLFSR_next(lfsr_t *);
