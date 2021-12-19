#ifndef ULS_H
#define ULS_H


#include "../libmx/inc/libmx.h"

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

void check_dir(int argc, const char *argv[], int *count, int *all_files);
char *ptime(char *e_time, char *t_t, char *name);
char **sort_arr(char **arr, int kolfiles);
void tab(int counttab, int len);
int err(const char *dir);
char* get_mode(mode_t m,char* str);
char *converter (mode_t val, char *dir);
void ls(const char *dir,int op_a,int op_l, int op_A, int op_one, int ws, int finder);
int max_wrd(const char *dir);
void space(int m_len, char *len);
void space1(int m_len, char *len, int n);
int get_max_gid(char **mass);
const char **sort_arr1(const char *arr[], int kolfiles);
void l_file(char **mass, int len, int op_one, int ws);

#endif
