#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident) {
    // Check if the file is an ELF file
    for (int i = 0; i < 4; i++) {
        if (e_ident[i] != 127 && e_ident[i] != 'E' && e_ident[i] != 'L' && e_ident[i] != 'F') {
            printf("Error: Not an ELF file\n");
            return;
        }
    }

    // Print the ELF magic numbers
    printf("Magic:   ");

    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x", e_ident[i]);

        if (i == EI_NIDENT - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
}

void print_magic(unsigned char *e_ident) {
    // Print the magic numbers of an ELF header
    printf("  Magic:   ");

    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x", e_ident[i]);

        if (i == EI_NIDENT - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
}

void print_class(unsigned char *e_ident) {
    // Print the class of an ELF header
    switch (e_ident[EI_CLASS]) {
        case ELFCLASSNONE:
            printf("none\n");
            break;
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_CLASS]);
    }
}

void print_version(unsigned char *e_ident) {
    // Print the version number of an ELF header
    printf("  Version:      ");

    for (int i = 0; i < EV_NAMLEN; i++) {
        printf("%02x", e_ident[i]);

        if (i == EV_NAMLEN - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
}

void print_abi(unsigned char *e_ident) {
    // Print the ABI version number of an ELF header
    switch (e_ident[EI_ABIVERSION]) {
        case EV_ABIVERSION_UNKNOWN:
            printf("Unknown\n");
            break;
        case EV_ABIVERSION_SVR4:
            printf("SVR4\n");
            break;
        case EV_ABIVERSION_PPC:
            printf("PPC\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_ABIVERSION]);
    }
}

void print_osabi(unsigned char *e_ident) {
    // Print the OS ABI version number of an ELF header
    switch (e_ident[EI_OSABIVERSION]) {
        case EV_OSABIVERSION_UNKNOWN:
            printf("Unknown\n");
            break;
        case EV_OSABIVERSION_LINUX:
            printf("Linux\n");
            break;
        case EV_OSABIVERSION_NETBSD:
            printf("NetBSD\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_OSABIVERSION]);
    }
}

void print_type(unsigned int e_type, unsigned char *e_ident) {
    // Print the type of an ELF header
    switch (e_type) {
        case ET_EXEC:
            printf("Executable\n");
            break;
        case ET_DYN:
            printf("Dynamic object\n");
            break;
        case ET_REL:
            printf("Relocatable object\n");
            break;
        default:
            printf("<unknown: %x>\n", e_type);
    }
}

void print_entry(unsigned long int e_entry, unsigned char *e_ident) {
    // Print the entry point address of an ELF header
    printf("  Entry point:     ");

    printf("%p\n", e_entry);
}

int main() {
    // Open the ELF file
    int elf = open("example.elf", O_RDONLY);

    // Check if the file is an ELF file
    check_elf((unsigned char *)malloc(4));

    // Read the ELF header
    read(elf, (void *)&e_ident, sizeof(e_ident));

    // Print the ELF magic numbers
    print_magic((unsigned char *)&e_ident);

    // Print the class of the ELF header
    print_class((unsigned char *)&e_ident);

    // Print the version number of the ELF header
    print_version((unsigned char *)&e_ident);

    // Print the ABI version number of the ELF header
    print_abi((unsigned char *)&e_ident);

    // Print the OS ABI version number of the ELF header
    print_osabi((unsigned char *)&e_ident);

    // Print the type of the ELF header
    print_type(e_ident[EI_TYPE], (unsigned char *)&e_ident);

    // Print the entry point address of the ELF header
    print_entry(e_ident[EI_ENTRY], (unsigned char *)&e_ident);

    // Close the ELF file
    close(elf);

    return 0;
}
