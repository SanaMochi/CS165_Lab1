#include <string.h>
#include <stdio.h>
//#include <md5.c>

int main(int argc, char* argv[]) {
//fflush(stdout);
printf("wtf0\n");
fflush(stdout);
  const char stringnum[64] = "abcdefghijklmnopqrstuvwxyz";
  char ret[9] = {0};
  char salt[10] = "hfT7jp2q";
  char pass[40] = {0};
  int i, j, k, l, m, n;
printf("wtf\n");
fflush(stdout);
  for(i = 0; i < strlen(stringnum); i = i + 1){
    ret[0] = stringnum[i];
    for(j = 0; j < strlen(stringnum); j = j + 1){
      ret[1] = stringnum[j];
      for(k = 0; k < strlen(stringnum); k = k + 1){
	ret[2] = stringnum[k];
	for(l = 0; l < strlen(stringnum); l = l + 1){
	  ret[3] = stringnum[l];
	  for(m = 0; m < strlen(stringnum); m = m + 1){
	    ret[4] = stringnum[m];
	    for(n = 0; n < strlen(stringnum); n = n + 1){
	      ret[5] = stringnum[n];
  printf("wtf before strcpy\n");
  fflush(stdout);
  // char newCrypt = md5_crypt(ret, salt);
  printf("wtf func call\n");
  fflush(stdout);
  //	      strcpy(pass, &newCrypt);
  printf("wtf after strcpy\n");
  fflush(stdout);
	      if ("wPwz7GC6xLt9eQZ9eJkaq." == pass) printf("Found password: %d", pass);
	      printf(ret);
              printf("\n");
	    }
	  }
	}
      }
    }
  }
    
  
  return 0;
}
