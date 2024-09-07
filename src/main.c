#include <stdio.h>
#include <string.h>

typedef enum {NEVER, EVERY, LAST} occurrence;

struct NumberFormat {
    occurrence og;  // Occurrence of "og" between numbers
    occurrence e;   // Occurrence of "e" in "hundrede" or "tusinde"
    int use_et;     // Whether to use "et" before hundred and thousand
};

#include "main.h"


void dansketal(int number, char* buffer, struct NumberFormat format) {
    // Negativt tal
    if (number < 0) {
        strcat(buffer, "minus ");
        number = -number;
    }

    convert_to_danish(number, buffer, format);
}

// Tilføjer "og"
void append_and(char* buffer, struct NumberFormat format, int is_last) {
    if ((format.og == EVERY) || (format.og == LAST && is_last)) {
        strcat(buffer, "og ");
    }
}

void convert_to_danish(int number, char* buffer, struct NumberFormat format) {
    const char* ones[] = {
        "nul", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni", "ti",
        "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"
    };
    const char* tens[] = {
        "", "", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems"
    };

    if (number < 20) {
        strcat(buffer, ones[number]);
    } else if (number < 100) {
        int ten = number / 10;
        int rem = number % 10;
        if (rem == 0) {
            strcat(buffer, tens[ten]);
        } else {
            strcat(buffer, ones[rem]);  // Tilføjer ones
            strcat(buffer, "og");       // Tilføjer og
            strcat(buffer, tens[ten]);  // Tilføjer tens
        }
    } else if (number < 1000) {
        int hundred = number / 100;
        int rem = number % 100;

        if (hundred == 1 && !format.use_et) {
            strcat(buffer, "hundred");
        } else {
            strcat(buffer, ones[hundred]);
            strcat(buffer, " ");
            strcat(buffer, format.e == NEVER ? "hundred" : "hundrede");
        }

        if (rem > 0) {
            strcat(buffer, " ");
            append_and(buffer, format, 1);
            convert_to_danish(rem, buffer, format);
        }
    } 
}


int main() {
    char buffer[1024] = {0};
    struct NumberFormat format = {LAST, EVERY, 0};

    dansketal(12555, buffer, format);
    printf("%s\n", buffer);

    return 0;
}
