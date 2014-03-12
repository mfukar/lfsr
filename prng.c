/**
 * @file        prng.c
 * @author      Michael Foukarakis
 * @date        Created:     Wed Mar 12, 2014 14:03 GMT
 *              Last Update: Wed Mar 12, 2014 14:05 GMT
 * @description PRNG using linear feedback shift registers.
 *              One shift register is used to provide data, while another register is used
 *              to "clock" data output; meaning a data bit is output when the clock
 *              register outputs a one bit, otherwise the data bit is dropped.
 *------------------------------------------------------------------------
 * -*- coding: utf-8 -*-
 *------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"

lfsr_t glfsr_d0;
lfsr_t glfsr_c0;

int main(int argc, char **argv)
{
    unsigned char bit0, bitc0, bitr = 0;
    char byte = 0, bitpos = 7;
    unsigned long long bitcounter = 0, ones = 0, zeros = 0, dropped = 0;
    lfsr_data_t polynom_d, init_value_d,
                polynom_c, init_value_c;

    if (argc < 5) {
        fprintf(stderr, "Usage: %s <data_polynomial> <data_seed> <clock_polynomial> <clock_seed>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen("bitstream.bin", "w");
    if(!fp) {
            fprintf(stderr, "Error opening output file.\n");
            exit(-1);
    }

    sscanf(argv[1], "%lx", &polynom_d);
    sscanf(argv[2], "%lx", &init_value_d);
    GLFSR_init(&glfsr_d0, polynom_d, init_value_d);

    sscanf(argv[3], "%lx", &polynom_c);
    sscanf(argv[4], "%lx", &init_value_c);
    GLFSR_init(&glfsr_c0, polynom_c, init_value_c);

    do {
        bit0  = GLFSR_next(&glfsr_d0);
        bitc0 = GLFSR_next(&glfsr_c0);

        if (glfsr_d0.data == init_value_d)
            printf("GLFSR D0 overflow at %llu.\n", bitcounter);

        if (glfsr_c0.data == init_value_c)
            printf("GLFSR C0 overflow at %llu.\n", bitcounter);

        printf("Next bits: %d, %d\t= ", bit0, bitc0);

        if (bitc0) {
            bitr = bit0;
            printf("%d\n", bitr);

            if (bitpos < 0) {
                fprintf(fp, "%c", byte);
                bitpos = 7;
                byte = 0;
            }

            byte |= bitr << bitpos;
            bitpos--;

            bitr ? ones++ : zeros++;
        } else {
            printf("dropped\n");
            dropped++;
        }

        bitcounter++;
    } while (!((glfsr_d0.data == init_value_d) && (glfsr_c0.data == init_value_c)));

    fclose(fp);
    printf("\nNumber of steps: %llu (%llu bytes)\nOnes: %llu, zeros: %llu, dropped: %llu\n", bitcounter, (zeros + ones) / 8, ones, zeros, dropped);

    return 0;
}
