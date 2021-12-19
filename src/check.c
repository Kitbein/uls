#include "../inc/uls.h"

void check_dir(int argc, const char *argv[], int *count, int *all_files) {
    DIR *dh;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            dh = opendir(argv[i]);
            if (dh) {
                *count += 1;
            }
            *all_files += 1;
        }
    }
}


int err(const char *dir) {
    DIR *dh;
	dh = opendir(dir);
    if (!dh) {
        if (errno == EACCES) {
            return 3;
        }
        else if (errno == ENOENT) {
            return  0;
        }
        else {
            return  2;
        }
    }
    else {
        return 1;
    }
}

    




