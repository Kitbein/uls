#include "../inc/uls.h"

void ls(const char *dir,int op_a,int op_l, int op_A, int op_one, int ws, int finder)
{
	int max_len = max_wrd(dir);
	int i = 0; 
	int index = 0;
	int chet = 0;
	int cat = 0;
	int min_dir = 0;
	char *t_t = NULL;
	char *e_time = NULL;
	char *path = NULL;
	struct dirent *d;
	struct group grup;
	struct passwd inf;
	int counttab = 1;
	for(int i = 8; i <= max_len; i += 8){
		counttab++;
	}
	DIR *dh;
	dh = opendir(dir);
	int kolfile = 0;
	while ((d = readdir(dh)) != NULL ) {
		if (d->d_name[0] == '.')
			continue; 
		kolfile++;
	}
	closedir(dh);
	char **mass = (char **)malloc(sizeof(char *) * (kolfile + 1));	
	dh = opendir(dir);
	while ((d = readdir(dh)) != NULL) {
		if (d->d_name[0] == '.') {
			continue;
		}
		mass[index] = mx_strdup(d->d_name);
		index++;
	}
	closedir(dh);
	if (kolfile < 12) {
		min_dir++;
	}
	mass = sort_arr(mass, kolfile);

	/////////////////////////////////////////////////////////////////FLAG -a
	if (op_a) {
		dh = opendir(dir);
		while ((d = readdir(dh)) != NULL)
		{
			if (d->d_name[0] != '.')
				continue;
			mx_printstr(d->d_name);
			if (ws == 0) {
				mx_printstr("\n");
				cat = 1;
			}	
			if (cat == 0)
				space(max_len,d->d_name);
			if (cat == 0) {
				if (op_one) 
					mx_printstr("\n");
			}
		}
		closedir(dh);
		dh = opendir(dir);
		while ((d = readdir(dh)) != NULL)
		{
			if (d->d_name[0] == '.' || !mx_isupper(d->d_name[0]))
				continue;
			mx_printstr(d->d_name);
			if (cat == 0)
				space(max_len,d->d_name);
			if (cat == 0) {
				if (op_one) 
					mx_printstr("\n");
			}
			if (ws == 0) 
				mx_printstr("\n");
		}
		closedir(dh);
		dh = opendir(dir);
		while ((d = readdir(dh)) != NULL)
		{
			if (d->d_name[0] == '.' || mx_isupper(d->d_name[0]))
				continue;
			if (i != 0) {
				if (cat == 0) {
					if (op_one) 
						mx_printstr("\n");
				}
				if (ws == 0) 
					mx_printstr("\n");
			}
			mx_printstr(d->d_name);
			if (cat == 0)
				space(max_len,d->d_name);
			i++;
		}
	}
	/////////////////////////////////////////////////////////////////FLAG -A
	else if (op_A) {
		dh = opendir(dir);
		while ((d = readdir(dh)) != NULL)
		{
			if (d->d_name[0] != '.')
				continue;
			if (d->d_name[0] == '.' && d->d_name[1] == '.')	
				continue;
			if (d->d_name[0] == '.' && d->d_name[1] == '\0')	
				continue;
			mx_printstr(d->d_name);
			if (ws == 0) {
				mx_printstr("\n");
				cat = 1;
			}	
			if (cat == 0)
				space(max_len,d->d_name);
			if (cat == 0) {
				if (op_one) 
					mx_printstr("\n");
			}
		}
		closedir(dh);
		dh = opendir(dir);
		while ((d = readdir(dh)) != NULL)
		{
			if (d->d_name[0] == '.' || !mx_isupper(d->d_name[0]))
				continue;
			mx_printstr(d->d_name);
			if (cat == 0)
				space(max_len,d->d_name);
			if (cat == 0) {
				if (op_one) 
					mx_printstr("\n");
			}
			if (ws == 0) 
				mx_printstr("\n");
		}
		closedir(dh);
		dh = opendir(dir);
		while ((d = readdir(dh)) != NULL)
		{
			if (d->d_name[0] == '.' || mx_isupper(d->d_name[0]))
				continue;
			if (i != 0) {
				if (cat == 0) {
					if (op_one) 
						mx_printstr("\n");
				}
				if (ws == 0) 
					mx_printstr("\n");
			}
			mx_printstr(d->d_name);
			if (cat == 0) 
				space(max_len,d->d_name);
			i++;
		}
	}
	/////////////////////////////////////////////////////////////////FLAG -l
	else if (op_l) {

		path = NULL;
		int max_stmode = 0;
		int max_size = 0;
		int max_gid = get_max_gid(mass);
		int max_name = 0;
		int total = 0;
		int max_link = 0;
		for(int i = 0; i < kolfile; i++) {
			if (mass[0][0] == '.') {
				continue;
			}
			if (err(dir) != 2) {
				path = mx_strdup(dir);
				path = mx_strjoin(path, "/");
				path = mx_strjoin(path, mass[i]);
			}
			struct stat s;
			lstat(path, &s);
			
			inf = *getpwuid(s.st_uid);
			if(mx_strlen(inf.pw_name) > max_name) {
				max_name = mx_strlen(inf.pw_name);
			}
			if(mx_strlen(mx_itoa(s.st_nlink)) > max_link) {
				max_link = mx_strlen(mx_itoa(s.st_nlink));
			}
			if(mx_strlen(converter(s.st_mode, path)) > max_stmode) {
				max_stmode = mx_strlen(converter(s.st_mode, path));
			}
			
			if(mx_strlen(mx_itoa(s.st_size)) > max_size) {
				max_size = mx_strlen(mx_itoa(s.st_size));
			}
			if(mass[0][0] != '.'){
				total += s.st_blocks;
			}
		}
		
		mx_printstr("total ");
		mx_printint(total);
		mx_printchar('\n');
		for(int i = 0; i < kolfile; i++) {
			if ('.'==mass[0][0] ) continue;
			if (ws != 0) {
				if(!op_one){
					struct stat s;
					path = mx_strdup(dir);
					path = mx_strjoin(path, "/");
					path = mx_strjoin(path, mass[i]);
					lstat(path, &s);
					mx_printstr(converter(s.st_mode, path));
					space1(max_stmode, converter(s.st_mode, path),1);
					space1(max_link, mx_itoa(s.st_nlink), 0);
					mx_printint(s.st_nlink);
					mx_printstr(" ");
					inf = *getpwuid(s.st_uid);
					mx_printstr(inf.pw_name);
					space1(max_name, inf.pw_name, 2);
					//mx_printstr("  ");
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
					mx_printstr(ptime(e_time,t_t, path));
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
						struct stat s;
						path = mx_strdup(dir);
						path = mx_strjoin(path, "/");
						path = mx_strjoin(path, mass[i]);
						lstat(path, &s);
						mx_printstr(converter(s.st_mode, path));
						space1(max_stmode, converter(s.st_mode, path),1);
						space1(max_link, mx_itoa(s.st_nlink), 0);
						mx_printint(s.st_nlink);
						mx_printstr(" ");
						inf = *getpwuid(s.st_uid);
						mx_printstr(inf.pw_name);
						space1(max_name, inf.pw_name, 2);
						//mx_printstr("  ");
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
						mx_printstr(ptime(e_time,t_t, path));
						mx_printstr(" ");
						mx_printstr(mass[i]);
						//mx_printstr(" ");
						mx_printchar('\n');
					}
					else {
						mx_printstr(mass[i]);
						mx_printchar('\n');
					}
			}
		}
	}
	/////////////////////////////////////////////////////////////////file
	else if (finder) {
		int stolb = ws / (counttab * 8); 
		int col = stolb;
		int row = 0; 
		if (col != 0) {
			row = kolfile % col != 0 ? kolfile/col + 1 : kolfile/col;
		}
		int full_file = row * col;
		int kaka = full_file - kolfile;
		int end_full_line = row - kaka; 
		int r_e = 0;
		if(min_dir == 0) {
			if (ws != 0) {
				for (int i = 0; i < row; i++) {
					int elem = 0;
					for (int j = 0; j < col; j++) {
						if(r_e + 1 > end_full_line) {
							if (j + 1 >= col) {
								break;
							}
							mx_printstr(mass[elem + i]);
							if (j + 1 < stolb) {
								tab(counttab, mx_strlen(mass[elem + i]));
							}
							elem += row;
						}
						else {
							mx_printstr(mass[elem + i]);
							if (j + 1 < stolb) {
								tab(counttab, mx_strlen(mass[elem + i]));
							}
							elem += row;
						}
					}
					r_e++;
					mx_printstr("\n");
				}
			}
			else {
				for(int i = 0; i < kolfile; i++){
					mx_printstr(mass[i]);
					mx_printstr("\n");
				}
			}
		}
		else {
			for(int j = 0; j < kolfile; j++) {
				if (mass[0][0] == '.') {
					continue;
				}
				if (i != 0) {
					if (cat == 0) {
						if (op_one) 
							mx_printstr("\n");
					}
					if (ws == 0) 
						mx_printstr("\n");
				}
				mx_printstr(mass[j]);
					if(cat == 0) {
						if (ws != 0)
							tab(counttab, mx_strlen(mass[j]));
					}
				else
					mx_printchar('\n');
				if	(i +1 == kolfile)
					mx_printchar('\n');	
				i++;
			}
		}
	}	
	/////////////////////////////////////////////////////////////////ls
	else {
		for(int j = 0; j < kolfile; j++) {
			if (mass[0][0] == '.') {
				continue;
			}
			if (i != 0) {
				if (cat == 0) {
					if (op_one) 
						mx_printstr("\n");
				}
				if (ws == 0) 
					mx_printstr("\n");
			}
			mx_printstr(mass[j]);
			if (i + 2!= chet){
				if(cat == 0) {
					if (ws != 0)
						tab(counttab, mx_strlen(mass[j]));
				}
			}
			else
				mx_printchar('\n');
			if	(i +1 == kolfile)
				mx_printchar('\n');	
			i++;
		}
	}

}

