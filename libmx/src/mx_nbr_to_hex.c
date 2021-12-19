#include "../inc/libmx.h"

char  *mx_nbr_to_hex(unsigned long nbr) {
    int n = nbr;
    int l = 0;
    int r;

    while (nbr != 0) {
        r = nbr % 16;
        nbr /= 16;
        l++;
    }

    if (l == 0)
        return 0;

    char *h = mx_strnew(l);

    for (int i = l - 1; i >= 0; i--) {
        r = n % 16;

        if (r < 10)
            h[i] = r + 48;
        else
            h[i] = r + 32 + 55;

        n /= 16;
    }

    return h;

}

