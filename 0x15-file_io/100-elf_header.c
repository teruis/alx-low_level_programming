#include <main.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <elf_file>\n", argv[0]);
        return 98;
    }

    // Open the ELF file
    int elf = open(argv[1], O_RDONLY);
    if (elf == -1) {
        perror("open");
        return 98;
    }

    // Read the ELF header
    Elf32_Ehdr ehdr;
    ssize_t ret = pread(elf, &ehdr, sizeof(Elf32_Ehdr), 0);
    if (ret != sizeof(Elf32_Ehdr)) {
        perror("pread");
        close_elf(elf);
        return 98;
    }

    // Check if the file is an ELF file
    check_elf(ehdr.e_ident);

    // Print the ELF header information
    print_magic(ehdr.e_ident);
    print_class(ehdr.e_ident);
    print_data(ehdr.e_ident);
    print_version(ehdr.e_ident);
    print_abi(ehdr.e_ident);
    print_osabi(ehdr.e_ident);
    print_type(ehdr.e_type, ehdr.e_ident);
    print_entry(ehdr.e_entry, ehdr.e_ident);

    // Close the ELF file
    close_elf(elf);

    return 0;
}


// Functions

void check_elf(unsigned char *e_ident) {
    int index;

    for (index = 0; index < 4; index++) {
        if (e_ident[index] != 127 &&
            e_ident[index] != 'E' &&
            e_ident[index] != 'L' &&
            e_ident[index] != 'F') {
                printf("Not an ELF file\n");
                return;
        }
    }

    printf("ELF file\n");
}

void print_magic(unsigned char *e_ident) {
    printf("Magic:\n");
    for (int i = 0; i < 4; i++) {
        printf("%c ", e_ident[i]);
    }
    printf("\n");
}

void print_class(unsigned char *e_ident) {
    printf("Class:\n");
    switch (e_ident[4]) {
        case 1:
            printf("32-bit\n");
            break;
        case 2:
            printf("64-bit\n");
            break;
        default:
            printf("Unknown class\n");
            break;
    }
}

void print_data(unsigned char *e_ident) {
    printf("Data:\n");
    switch (e_ident[5]) {
        case 1:
            printf("REL\n");
            break;
        case 2:
            printf("RELA\n");
            break;
        default:
            printf("Unknown data\n");
            break;
    }
}

void print_version(unsigned char *e_ident) {
    printf("Version:\n");
    for (int i = 6; i < 8; i++) {
        printf("%c ", e_ident[i]);
    }
    printf("\n");
}

void print_abi(unsigned char *e_ident) {
    printf("ABI:\n");
    switch (e_ident[8]) {
        case 1:
            printf("OSBYTE\n");
            break;
        case 2:
            printf("UNIX\n");
            break;
        default:
            printf("Unknown ABI\n");
            break;
    }
}

void print_osabi(unsigned char *e_ident) {
    printf("OS/ABI:\n");
    switch (e_ident[9]) {
        case 1:
            printf("Linux\n");
            break;
        case 2:
            printf("Netware\n");
            break;
        default:
            printf("Unknown OS/ABI\n");
            break;
    }
}

void print_type(unsigned int e_type, unsigned char *e_ident) {
    switch (e_type) {
        case ET_EXEC:
            printf("Executable\n");
            break;
        case ET_DYN:
            printf("Dynamic object\n");
            break;
        case ET_CORE:
            printf("Core file\n");
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

void print_entry(unsigned long int e_entry, unsigned char *e_ident) {
    printf("Entry point address: %lu\n", e_entry);
}

void close_elf(int elf) {
    close(elf);
}
