#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    int fd_source, fd_destination;

    if (argc != 3) {
        fprintf(stderr, "Use: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat src_stat;
    if (stat(argv[1], &src_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    if (!S_ISREG(src_stat.st_mode)) {
        fprintf(stderr, "%s must be a regular file\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    fd_source = open(argv[1], O_RDONLY);
    fd_destination = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_destination == -1) {
        perror("open dest.");
        close(fd_source);
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    ssize_t nread, nwrite;

    while ((nread = read(fd_source, buf, src_stat.st_size)) > 0) {
        ssize_t total = 0;
        while (total < nread) {
            nwrite = write(fd_destination, buf, nread - total);
                if (nwrite < 0) {
                perror("Writing error");
                exit(EXIT_FAILURE);
            }
            total += nwrite;
        }
    }

    if (nread < 0) {
        perror("Reading error");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Content copied successfully\n");

    close(fd_source);
    close(fd_destination);
    return 0;
}