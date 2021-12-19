#include "../inc/uls.h"

int max_wrd(const char *dir) {
	struct dirent *d;  
 	int max_dlinna = 0,samaya_dlinnaya = 0;
 
	DIR *dh = opendir(dir);
	while ((d = readdir(dh)) != NULL)
	{	
		if (d->d_name[0] == '.'){
			continue;
		}

		samaya_dlinnaya = mx_strlen(d->d_name);
		if(samaya_dlinnaya>max_dlinna)
		{
			max_dlinna=samaya_dlinnaya;
		}
	}
	closedir(dh);
	return max_dlinna;
}

void space(int m_len, char *len) {
	int dlen = mx_strlen(len);
	for(int i = 0; i < m_len + 8 - dlen; i++) { 
		mx_printstr(" "); 
	}
}

void space1(int m_len, char *len, int n) {
	int dlen = 0;
	dlen = mx_strlen(len);
	int k = m_len + n - dlen;
	for(int i = 0; i < k; i++) { 
		mx_printstr(" ");
	}
}

void tab(int counttab, int len){
	for(int i = len; i < counttab * 8;i +=8) {
		mx_printchar('\t');
	}
}

char **sort_arr(char **arr, int kolfiles) {
    char *buff;
    if (kolfiles > 1) {
        for (int i = 0; i < kolfiles; i++) {
            for (int j = 0; j < kolfiles; j++) {
                if (mx_strcmp(arr[i], arr[j]) > 0) {
                    buff = mx_strdup(arr[i]);
                    arr[i] = mx_strdup(arr[j]);
                    arr[j] = mx_strdup(buff);
                }
            }
        }
        for (int i = 0; i < kolfiles/2; i++) {
            buff = mx_strdup(arr[i]);
            arr[i] = mx_strdup(arr[kolfiles - 1 - i]);
            arr[kolfiles - 1 - i] = mx_strdup(buff);
        }
    }
    return arr;
}


