#include <stdio.h>

typedef enum {
    SUCCESS,
    HOUSE_WIDTH_TOO_SMALL,
    HOUSE_HEIGHT_TOO_SMALL,
    FENCE_LENGTH_NEGATIVE_OR_ZERO,
} InputError;

void repeat_char(char str[], const size_t size, const char c) {
    if (size == 0) {
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        str[i] = c;
    }

    str[size - 1] = '\0';
}

InputError print_house(const int houseWidth, const int houseHeight, const int fenceLength) {
    if (houseWidth < 3) {
        return HOUSE_WIDTH_TOO_SMALL;
    }
    if (houseHeight < 3) {
        return HOUSE_HEIGHT_TOO_SMALL;
    }
    if (fenceLength <= 0) {
        return FENCE_LENGTH_NEGATIVE_OR_ZERO;
    }

    int roofHeight;

    if (houseWidth % 2 == 0) {
        roofHeight = (houseWidth - 2) / 2;
    } else {
        roofHeight = houseWidth / 2;
    }

    if (houseWidth % 2 == 0) {
        for (int i = 0; i < roofHeight; i++) {
            // +1 pro \0
            const size_t middleSpaceLength = 1 + i * 2;
            // Namísto middleSpaceLength+1 by mělo být +2, ale middleSpaceLength má +1 kvůli \0.
            const size_t outerSpaceLength = 1 + (houseWidth - (middleSpaceLength + 1)) / 2;

            char outerSpace[outerSpaceLength];
            repeat_char(outerSpace, outerSpaceLength, ' ');
            char middleSpace[middleSpaceLength];
            repeat_char(middleSpace, middleSpaceLength, ' ');

            printf("%s/%s\\\n", outerSpace, middleSpace);
        }
    } else {
        for (int i = 0; i < roofHeight; i++) {
            if (i == 0) {
                const size_t spacesLength = 1 + (houseWidth - 1) / 2;
                char spaces[spacesLength];
                repeat_char(spaces, spacesLength, ' ');

                printf("%s^\n", spaces);

                continue;
            }

            // Normálně by to bylo i*2-1, ale s +1 pro \0 se to zruší.
            const int middleSpaceLength = i * 2;
            // To samý jak první outerSpaceLength.
            const int outerSpaceLength = 1 + (houseWidth - (middleSpaceLength + 1)) / 2;

            char outerSpace[outerSpaceLength];
            repeat_char(outerSpace, outerSpaceLength, ' ');
            char middleSpace[middleSpaceLength];
            repeat_char(middleSpace, middleSpaceLength, ' ');

            printf("%s/%s\\\n", outerSpace, middleSpace);
        }
    }

    // Normálně by to bylo houseWidth-2, ale s +1 pro \0 to přejde na -1.
    const size_t baseLength = houseWidth - 1;
    char base[baseLength];
    repeat_char(base, baseLength, '-');

    printf("+%s+\n", base);

    char fence[fenceLength + 1];

    for (int i = 0; i < fenceLength; i++) {
        if (i % 2 == 0) {
            fence[i] = '-';
        } else {
            fence[i] = '|';
        }
    }

    fence[fenceLength] = '\0';

    char interior[houseWidth - 1]; // -1 = -2 + 1

    interior[houseWidth - 2] = '\0';

    for (int i = 0; i < houseHeight - 2; i++) {
        for (int j = 0; j < houseWidth - 2; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    interior[j] = '#';
                } else {
                    interior[j] = '*';
                }
            } else {
                if (j % 2 == 0) {
                    interior[j] = '*';
                } else {
                    interior[j] = '#';
                }
            }
        }

        printf("|%s| %s\n", interior, fence);
    }

    printf("+%s+ %s\n", base, fence);

    return SUCCESS;
}

int main(void) {
    int houseWidth, houseHeight, fenceLength;

    printf("Enter the house width, the house height, and the fence length. Each number must be greater than 0 and separated by commas. The house width and height must be greater or equal to 3.\n");
    scanf("%d,%d,%d", &houseWidth, &houseHeight, &fenceLength);

    printf("\n");

    switch (print_house(houseWidth, houseHeight, fenceLength)) {
        case SUCCESS:
            return 0;
        case HOUSE_WIDTH_TOO_SMALL:
            printf("House width is smaller than 3.\n");
            return -1;
        case HOUSE_HEIGHT_TOO_SMALL:
            printf("House height is smaller than 3.\n");
            return -1;
        case FENCE_LENGTH_NEGATIVE_OR_ZERO:
            printf("Fence length negative or zero.\n");
            return -1;
    }
}
