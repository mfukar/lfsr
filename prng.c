#include <stdio.h>
#include <stdlib.h>
#include "lfsr.h"

lfsr_t glfsr_d0;
lfsr_t glfsr_c0;

int main(int argc, char **argv) {
    unsigned char bit0;
    unsigned char bitc0;
    unsigned char bitr = 0;
    char byte = 0, bitpos = 7;
    unsigned int bitcounter = 0, ones = 0, zeros = 0, dropped = 0;
    unsigned int polynom_d, init_value_d;
    unsigned int polynom_c, init_value_c;
    FILE *f;

    if (argc < 5) {
        fprintf(stderr, "Too few arguments: data_polynom data_init_value control_polynom control_init_value\n");
        exit(1);
    }

    f = fopen("output.bin", "w");

    if (f == NULL) {
        fprintf(stderr, "Cannot open output data file (output.bin)\n");
        exit(2);
    }

    sscanf(argv[1], "%x", &polynom_d);
    sscanf(argv[2], "%x", &init_value_d);
    GLFSR_init(&glfsr_d0, polynom_d, init_value_d);
    printf("GLFSR D0: using polynom 0x%X, initial value: 0x%X.\n", polynom_d, init_value_d);

    sscanf(argv[3], "%x", &polynom_c);
    sscanf(argv[4], "%x", &init_value_c);
    GLFSR_init(&glfsr_c0, polynom_c, init_value_c);
    printf("GLFSR C0: using polynom 0x%X, initial value: 0x%X.\n", polynom_c, init_value_c);

    do {
        bit0 = GLFSR_next(&glfsr_d0);
        bitc0 = 1;//GLFSR_next(&glfsr_c0);

        if (glfsr_d0.data == init_value_d)
            printf("GLFSR D0 overflow at %d.\n", bitcounter);

        if (glfsr_c0.data == init_value_c)
            printf("GLFSR C0 overflow at %d.\n", bitcounter);

        printf("Next bits: %d, %d\t= ", bit0, bitc0);

        if (bitc0) {
            bitr = bit0;
            printf("%d\n", bitr);

            if (bitpos < 0) {
                fprintf(f, "%c", byte);
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

    fclose(f);

    printf("\nNumber of steps: %d (%d bytes), ones: %d, zeros: %d, dropped: %d\n", bitcounter, (zeros + ones) / 8, ones, zeros, dropped);
    return 0;
}
