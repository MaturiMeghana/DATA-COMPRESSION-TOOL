#include <stdio.h>
#include <stdlib.h>


void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("Error opening files.\n");
        return;
    }

    char current, previous;
    int count = 1;

    previous = fgetc(in);
    while ((current = fgetc(in)) != EOF) {
        if (current == previous) {
            count++;
        } else {
            fprintf(out, "%d%c", count, previous);
            count = 1;
        }
        previous = current;
    }
    fprintf(out, "%d%c", count, previous);

    printf("File compressed successfully as %s\n", outputFile);
    fclose(in);
    fclose(out);
}


void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("Error opening files.\n");
        return;
    }

    int count;
    char ch;

    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    printf("File decompressed successfully as %s\n", outputFile);
    fclose(in);
    fclose(out);
}

int main() {
    int choice;
    char inputFile[100], outputFile[100];

    printf("RLE Compression Tool\n");
    printf("---------------------\n");
    printf("1. Compress File\n");
    printf("2. Decompress File\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter input file name (to compress): ");
        scanf("%s", inputFile);
        printf("Enter output file name (compressed result): ");
        scanf("%s", outputFile);
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        printf("Enter input file name (compressed file): ");
        scanf("%s", inputFile);
        printf("Enter output file name (decompressed result): ");
        scanf("%s", outputFile);
        decompressFile(inputFile, outputFile);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
