#include "../inc/uls.h"

int main(int argc, const char *argv[]) {
	struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int max_len = 0;
	int count = 0;
	int files = 0;
	int result = 0;
	int kolfile = 0;
	int kolfile_1 = 0;
	int probel = 0;
	int l = 0;
	for(int j = 1; j < argc; j++) {
		kolfile++;  
	}
	for(int j = 1; j < argc; j++) {
		kolfile_1++;  
	}
	check_dir(argc, argv, &count, &files);
	if (argc == 1)
	{
		ls(".",0,0,0,0,size.ws_col,0);
	}
	else if (argc > 1) {
		if (argv[1][0] == '-') {
			int op_a = 0, op_l = 0, op_A = 0, op_one = 0;
			int count_flags = 0;
			bool t = false;
			for(int k = 1; k < argc; k++) {
				if (argv[k][0] == '-' && t != true) {
					count_flags++;
					char *p = (char*)(argv[k] + 1);
					while(*p){
						if(*p == 'a') { op_a = 1;}
						else if(*p == 'A') { op_A = 1;}
						else if(*p == 'l') { op_l = 1;}
						else if(*p == '1') { op_one = 1;}
						else {
							mx_printerr("uls: illegal option -- ");
							write(STDERR_FILENO, p, 1);
							mx_printerr("\nusage: uls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
							exit(0);
						}
						p++;
					}
				} 
				else {
					t = true;
					if (err(argv[k]) == 0) {
						mx_printerr("uls: ");
						mx_printerr(argv[k]);
						mx_printerr(": No such file or directory");
						mx_printerr("\n");	
					}
				}
			}

			kolfile = argc - count_flags - 1 - count;

			char **mass = (char **)malloc(sizeof(char *) * (count + 1));
			char **mass_files = (char **)malloc(sizeof(char *) * (kolfile + 1));
			int indx_d = 0;
			int indx_f = 0;
			for (int idx = count_flags + 1; idx < argc; idx++) {
				
				if (err(argv[idx]) == 1) {
					mass[indx_d] = mx_strdup(argv[idx]);
					indx_d++;
					
				}
				if (err(argv[idx]) == 2) {
					mass_files[indx_f] = mx_strdup(argv[idx]);
					indx_f++;
					l++;
				}
			}
			mass = sort_arr(mass, indx_d);
			mass_files = sort_arr(mass_files, indx_f);

			l_file(mass_files, indx_f, op_one, size.ws_col);
			if (count == 0 && files == 0)
				ls(".",op_a,op_l,op_A,op_one,size.ws_col,0);
			else {
				for (int i = 0; i < indx_d; i++) {
					if (err(mass[i]) == 1) {
						if (kolfile_1 -1 > 1){
							if(l >= 1)
								mx_printstr("\n");
								mx_printstr(mass[i]);
								mx_printstr(":\n");
						}
						ls(mass[i],op_a,op_l,op_A,op_one,size.ws_col,0);
						l++;
					}
				}
			}	
		}
        else {
			char **mass = (char **)malloc(sizeof(char *) * kolfile);
			int indx2 = 0;

			for(int idx = 1; idx < argc; idx++, indx2++) {
				mass[indx2] = mx_strdup(argv[idx]);
			}
			mass = sort_arr(mass, kolfile);

			for(int i = 0; i < kolfile; i++) {
				if(mx_strlen(mass[i]) > max_len) {
					max_len = mx_strlen(mass[i]);
				}
			}

			int counttab = 1;
			for(int i = 8; i <= max_len; i += 8){
				counttab++;
			}

			for(int k = 0; k < argc - 1; k++) {
				result = err(mass[k]);
				if(result == 0) {
					mx_printerr("uls: ");
					mx_printerr(mass[k]);
					mx_printerr(" : No such file or directory");
					mx_printerr("\n");	
				}
			}
			for(int k = 0; k < argc - 1; k++) {
				result = err(mass[k]);
				if(result == 2) {
					mx_printstr(mass[k]);
					if(k + 1 != kolfile) {
						if(size.ws_col != 0)
							tab(counttab, mx_strlen(mass[k]));
						else
							mx_printstr("\n");
					}
					probel++;
				}
			}
			if(probel > 0)
				mx_printstr("\n");
			if(count > 0 && probel != 0 && size.ws_col != 0)
				mx_printstr("\n");
			int tmp = 0;
			for(int i = 0; i < argc - 1; i++) {
				if(count > 0) {
					if (mass[i][0] != '-' && err(mass[i]) == 1) {
						tmp++;
						int lol = 0;
						for (int j = mx_strlen(mass[i]); j > 0; j--) {
							if (mass[i][j] == '/') {
								lol = 1;
							}
						}
						if(kolfile > 1) {
							mx_printstr(mass[i]);
							mx_printstr(":\n");
						}
						ls(mass[i],0,0,0,0,size.ws_col,lol);

							if(kolfile - probel - tmp != 0){
								mx_printstr("\n");
							}
					}
				}
			}
        }
	}
	return 0;
}

