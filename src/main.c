#include <stdio.h>
#include <string.h>

typedef enum {NEVER, EVERY, LAST} occurrence;

struct NumberFormat {
    occurrence og;  // Brug af "og" mellem tal
    occurrence e;   // Brug af "e" i "hundrede" eller "tusinde"
    int use_et;     // Bruge "et" før hundred eller tusinde
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
    } else if (number < 1000000) {
        int thousand = number / 1000;
        int rem = number % 1000;

        if (thousand == 1 && !format.use_et) {
            strcat(buffer, "tusind");
        } else {
            convert_to_danish(thousand, buffer, format);
            strcat(buffer, " ");
            strcat(buffer, format.e == NEVER ? "tusind" : "tusinde");
        }

        if (rem > 0) {
            strcat(buffer, " ");
            if (rem < 100) {  // Tilføj kun "og", hvis der er under 100 tilbage
                append_and(buffer, format, 1);
            }
            convert_to_danish(rem, buffer, format);
        }
    } else if (number < 1000000000) {
        int million = number / 1000000;
        int rem = number % 1000000;

        if (million == 1 && !format.use_et) {
            strcat(buffer, "million");
        } else {
            convert_to_danish(million, buffer, format);
            strcat(buffer, " ");
            strcat(buffer, format.e == NEVER ? "million" : "millioner");
        }

        if (rem > 0) {
            strcat(buffer, " ");
            if (rem < 100) {  // Tilføj kun "og", hvis der er under 100 tilbage
                append_and(buffer, format, 1);
            }
            convert_to_danish(rem, buffer, format);
        }
    }
}


int main() {
    struct NumberFormat format = {LAST, EVERY, 0};

    while (1)
    {
        char buffer[1024] = {0};
        int num = input_number();
        dansketal(num, buffer, format);
        printf("%s\n", buffer);
    }

    return 0;
}
