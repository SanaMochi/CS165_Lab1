//Using OpenSSL, as provided by the slides

#include <string.h>
#include <stdio.h>
//#include <md5.c>

int main(int argc, char* argv[]) {
  const char stringnum[64] = "abcdefghijklmnopqrstuvwxyz";
  char rt[9] = {0};
  char salt[10] = "4fTgjp6q";
  char pass[40] = {0};
  int i, j, k, l, m, n;
  for(i = 0; i < strlen(stringnum); i = i + 1){
    rt[0] = stringnum[i];
    for(j = 0; j < strlen(stringnum); j = j + 1){
      rt[1] = stringnum[j];
      for(k = 0; k < strlen(stringnum); k = k + 1){
	rt[2] = stringnum[k];
	for(l = 0; l < strlen(stringnum); l = l + 1){
	  rt[3] = stringnum[l];
	  for(m = 0; m < strlen(stringnum); m = m + 1){
	    rt[4] = stringnum[m];
	    for(n = 0; n < strlen(stringnum); n = n + 1){
	      rt[5] = stringnum[n];
  printf("wtf before func call\n");
  fflush(stdout);
              char newCrypt = md5_crypt(rt, salt);
  printf("wtf before strcpy\n");
  fflush(stdout);
	      strcpy(pass, &newCrypt);
  printf("wtf after strcpy\n");
  fflush(stdout);
	      if ("2bBqhtSK.CKnOMysAG1BE0" == pass) printf("Found password: %d", pass);
	      printf(rt);
              printf("\n");
	    }
	  }
	}
      }
    }
  }
  
  return 0;
}
