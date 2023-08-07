#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <elf.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s elf_filename\n", argv[0]);
        return 98;
    }
    char filename[BUFFER_SIZE];
    strcpy(filename, argv[1]);

    // Open the file in binary mode
    int fd = open(filename, O_RDONLY | O_BINARY);
    if (fd == -1) {
        perror("open");
        return 98;
    }

    // Lseek to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Read the ELF header
    Elf32_Ehdr ehdr;
    read(fd, &ehdr, sizeof(ehdr));

    // Display the ELF header information
    printf("Magic:\t%08x\n", ehdr.e_ident[EI_MAGIC]);
    printf("Class:\t%08x\n", ehdr.e_ident[EI_CLASS]);
    printf("Data:\t%08x\n", ehdr.e_ident[EI_DATA]);
    printf("Version:\t%08x\n", ehdr.e_version);
    printf("OS/ABI:\t%08x\n", ehdr.e_osabi);
    printf("ABI Version:\t%08x\n", ehdr.e_abiversion);
    printf("Type:\t%08x\n", ehdr.e_type);
    printf("Entry Point Address:\t%p\n", ehdr.e_entry);

    // Close the file
    close(fd);

    return 0;
}
