#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << argv[0] << std::endl;
        return 1;
    }

    const char* filepath = argv[1];
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error ");
        return 1;
    }

    int fd1 = dup(fd);
    int fd2 = dup(fd);
    if (fd1 == -1 || fd2 == -1) {
        perror("Error");
        close(fd);
        return 1;
    }

    const char* line1 = "first line\n";
    const char* line2 = "second line\n";

    write(fd1, line1, strlen(line1));
    write(fd2, line2, strlen(line2));

    close(fd1);
    close(fd2);
    close(fd);
    
    return 0;
}

