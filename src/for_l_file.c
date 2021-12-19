#include "../inc/uls.h"

void l_file(char **mass, int len, int op_one, int ws)
{
	char *t_t = NULL;
	char *e_time = NULL;
	struct group grup;
	struct passwd inf;

    int max_stmode = 0;
    int max_size = 0;
    int max_gid = get_max_gid(mass);
    int max_name = 0;
    int max_link = 0;

    for(int i = 0; i < len; i++) {
        struct stat s;
        lstat(mass[i], &s);
        inf = *getpwuid(s.st_uid);
        if(mx_strlen(inf.pw_name) > max_name) {
            max_name = mx_strlen(inf.pw_name);
        }
        if(mx_strlen(mx_itoa(s.st_nlink)) > max_link) {
            max_link = mx_strlen(mx_itoa(s.st_nlink));
        }
        if(mx_strlen(converter(s.st_mode, mass[i])) > max_stmode) {
            max_stmode = mx_strlen(converter(s.st_mode, mass[i]));
        }
        
        if(mx_strlen(mx_itoa(s.st_size)) > max_size) {
            max_size = mx_strlen(mx_itoa(s.st_size));
        }
    }
    for(int i = 0; i < len; i++) {
        struct stat s;
        lstat(mass[i], &s);
        if (ws != 0) {
            if(!op_one){
                mx_printstr(converter(s.st_mode, mass[i]));
                space1(max_stmode, converter(s.st_mode, mass[i]),1);
                space1(max_link, mx_itoa(s.st_nlink), 0);
                mx_printint(s.st_nlink);
                mx_printstr(" ");
                mx_printstr(inf.pw_name);
                space1(max_name, inf.pw_name, 2);
                if (getgrgid(s.st_gid) == NULL) {
                    mx_printint(s.st_gid);
                    space1(max_gid, mx_itoa(s.st_gid), 0);
                }
                else {
                    grup = *getgrgid(s.st_gid);
                    mx_printstr(grup.gr_name);
                    space1(max_gid, grup.gr_name, 0);
                }

                space1(max_size, mx_itoa(s.st_size),2);
                mx_printint(s.st_size);
                mx_printstr(" ");
                mx_printstr(ptime(e_time,t_t, mass[i]));
                mx_printstr(" ");
                mx_printstr(mass[i]);
                mx_printstr(" ");
                mx_printchar('\n');
            }
            else {
                mx_printstr(mass[i]);
                mx_printchar('\n');
            }
        }
        else {
            if(!op_one){
                mx_printstr(converter(s.st_mode, mass[i]));
                space1(max_stmode, converter(s.st_mode, mass[i]),1);
                space1(max_link, mx_itoa(s.st_nlink), 0);
                mx_printint(s.st_nlink);
                mx_printstr(" ");
                mx_printstr(inf.pw_name);
                space1(max_name, inf.pw_name, 2);
                if (getgrgid(s.st_gid) == NULL) {
                    mx_printint(s.st_gid);
                    space1(max_gid, mx_itoa(s.st_gid), 0);
                }
                else {
                    grup = *getgrgid(s.st_gid);
                    mx_printstr(grup.gr_name);
                    space1(max_gid, grup.gr_name, 0);
                }

                space1(max_size, mx_itoa(s.st_size),2);
                mx_printint(s.st_size);
                mx_printstr(" ");
                mx_printstr(ptime(e_time,t_t, mass[i]));
                mx_printstr(" ");
                mx_printstr(mass[i]);
                mx_printchar('\n');
            }
            else {
                mx_printstr(mass[i]);
                mx_printchar('\n');
            }
        }
    }
}

