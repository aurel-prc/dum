#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS,
    HOUSE_WIDTH_NEGATIVE_OR_ZERO,
    HOUSE_HEIGHT_TOO_SMALL,
    FENCE_LENGTH_NEGATIVE_OR_ZERO,
} InputError;

// Returns NULL if allocation failed.
char* repeat_char(const char c, const int count) {
    char* str = malloc((count + 1) * sizeof(char));

    if (str == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        str[i] = c;
    }

    str[count] = '\0';

    return str;
}

InputError print_house(const int houseWidth, const int houseHeight, const int fenceLength) {
    if (houseWidth <= 0) {
        return HOUSE_WIDTH_NEGATIVE_OR_ZERO;
    } if (houseHeight < 3) {
        return HOUSE_HEIGHT_TOO_SMALL;
    } if (fenceLength <= 0) {
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
            const int middleSpaceLength = i * 2;
            const int outerSpaceLength = (houseWidth - (middleSpaceLength + 2)) / 2;

            char* outerSpace = repeat_char(' ', outerSpaceLength);
            char* middleSpace = repeat_char(' ', middleSpaceLength);

            printf("%s/%s\\\n", outerSpace, middleSpace);

            free(outerSpace);
            free(middleSpace);
        }
    } else {
        for (int i = 0; i < roofHeight; i++) {
            if (i == 0) {
                char* spaces = repeat_char(' ', (houseWidth - 1) / 2);
                printf("%s^\n", spaces);
                free(spaces);
                continue;
            }

            const int middleSpaceLength = i * 2 - 1;
            const int outerSpaceLength = (houseWidth - (middleSpaceLength + 2)) / 2;

            char* outerSpace = repeat_char(' ', outerSpaceLength);
            char* middleSpace = repeat_char(' ', middleSpaceLength);

            printf("%s/%s\\\n", outerSpace, middleSpace);

            free(outerSpace);
            free(middleSpace);
        }
    }

    char* base = repeat_char('-', houseWidth - 2);
    printf("+%s+\n", base);

    char fence[fenceLength + 1];

    for (int j = 0; j < fenceLength * 2; j++) {
        if (j % 2 == 0) {
            fence[j] = '-';
        } else {
            fence[j] = '|';
        }
    }

    fence[fenceLength] = '\0';

    char* betweenWallsSpace = repeat_char(' ', houseWidth - 2);

    for (int i = 0; i < houseHeight - 2; i++) {
        printf("|%s| %s\n", betweenWallsSpace, fence);
    }

    free(betweenWallsSpace);
    printf("+%s+ %s\n", base, fence);
    free(fence);
    free(base);

    return SUCCESS;
}

int main(void)
{
    int houseWidth, houseHeight, fenceLength;

    printf("Enter the house width, the house height, and the fence length. Each number must be greater than 0 and separated by commas. The house height must be greater or equal to 3.\n");
    scanf("%d,%d,%d", &houseWidth, &houseHeight, &fenceLength);
    printf("House width: %d House height: %d Fence length: %d", houseWidth, houseHeight, fenceLength);

    printf("\n");

    switch (print_house(houseWidth, houseHeight, fenceLength)) {
        case SUCCESS:
            return 0;
        case HOUSE_WIDTH_NEGATIVE_OR_ZERO:
            printf("House width is negative or zero.\n");
            return -1;
        case HOUSE_HEIGHT_TOO_SMALL:
            printf("House height is negative or ero.\n");
            return -1;
        case FENCE_LENGTH_NEGATIVE_OR_ZERO:
            printf("Fence length negative or zero.\n");
            return -1;
    }
}
