#include "../inc/uls.h"

char *converter (mode_t val, char *dir) {
    char *convert = malloc(sizeof(char) * 11 + 1);
    convert[0] = (val & S_IFDIR) ? 'd' : '-';
    convert[1] = (val & S_IRUSR) ? 'r' : '-';
    convert[2] = (val & S_IWUSR) ? 'w' : '-';
    convert[3] = (val & S_IXUSR) ? 'x' : '-';
    convert[4] = (val & S_IRGRP) ? 'r' : '-';
    convert[5] = (val & S_IWGRP) ? 'w' : '-';
    convert[6] = (val & S_IXGRP) ? 'x' : '-';
    convert[7] = (val & S_IROTH) ? 'r' : '-';
    convert[8] = (val & S_IWOTH) ? 'w' : '-';
    convert[9] = (val & S_IXOTH) ? 'x' : '-';
    if (listxattr(dir, NULL, 0, XATTR_NOFOLLOW) > 1) {
        convert[10] = '@';
    }
    else if (acl_get_file(dir , ACL_TYPE_EXTENDED)) {
        convert[10] = '+';
    }
    else {
        convert[10] = ' ';
    }
    if(S_ISLNK(val)) {
        convert[0] = 'l';
    }
    if (val & S_ISVTX) {
        convert[9] = 't';
    }
    convert[11] = '\0';
    return convert;
}

char *ptime(char *e_time, char *t_t, char *name){
	struct stat list;
	lstat(name, &list);
	t_t = 4 + ctime((time_t *)&list.st_mtime);
        
        if (time(NULL) - list.st_mtime > 15811200) {
            e_time = mx_strndup(t_t, mx_strlen(t_t) - 14);
            e_time = mx_strjoin(e_time, mx_strndup(19 + ctime((time_t *)&list.st_mtime), 5));
        } 
        else {
            e_time = mx_strndup(t_t, mx_strlen(t_t) - 9);
        }

return e_time;
}

int get_max_gid(char **mass) {
    int max_res = 0;
    int i = 0;
    int n = 0;
    struct group gr;
    struct stat s;
    while (mass[i] != NULL) {
        lstat(mass[i], &s);
        n = 0;
        if (getgrgid(s.st_gid) == NULL) {
            n = mx_strlen(mx_itoa(s.st_gid));
        }
        else {
            gr = *getgrgid(s.st_gid);
            n = mx_strlen(gr.gr_name);
        }
        if (n > max_res) {
            max_res = n;
        }
        i++;
    }
    return max_res;
}

