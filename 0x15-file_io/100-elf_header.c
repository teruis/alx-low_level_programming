#include "main.h"
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <sys/mman.h>

#define ELF_HEADER_SIZE 52

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <elf_filename>\n", argv[0]);
        exit(98);
    }

    // Open the ELF file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Failed to open ELF file");
        exit(98);
    }

    // Read the ELF header
    char buffer[ELF_HEADER_SIZE];
    ssize_t ret = read(fd, buffer, ELF_HEADER_SIZE);
    if (ret != ELF_HEADER_SIZE) {
        printf("Failed to read ELF header\n");
        exit(98);
    }

    // Check the ELF header magic number
    if (memcmp(buffer, "\x7f\x45\x4c\x46\x02\x01\x01\x00", 8) != 0) {
        printf("Not an ELF file\n");
        exit(98);
    }

    // Print the ELF header information
    printf("Magic:    %s\n", buffer);
    printf("Class:          %s\n", buffer + 8);
    printf("Data:          %s\n", buffer + 14);
    printf("Version:       %d\n", buffer[18]);
    printf("OS/ABI:        %s\n", buffer + 19);
    printf("ABI Version:  %d\n", buffer[21]);
    printf("Type:          %s\n", buffer + 22);
    printf("Entry point address: 0x%08x\n", buffer[27]);

    // Print the section headers
    printf("Section header string table index: %d\n", buffer[31]);

    // Print the program headers
    printf("Program headers:\n");
    for (int i = 0; i < 9; i++) {
        printf("Header %d: %s\n", i + 1, buffer + 32 + i * 4);
    }

    close(fd);
    return 0;
}
