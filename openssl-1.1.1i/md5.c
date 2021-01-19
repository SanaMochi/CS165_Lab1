#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//taking from slides, translating to see what it does; will change to avoid problems LMAO

//moved here for convenience lol you can move it back later if you want, I just wanted to look at it all w/o switching files

const char base64[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//static char* ret;

char* 
to64(long v, int n) 
{
  static char buf[5];
  char* s = buf;
  
  if(n > 4)
    return NULL;
  memset(buf, '\0', sizeof(buf));
  
  while(--n >= 0){
    *s++ = base64[v & 0x3f];
    v >>= 6;
  }
  return (buf);
}

char*
md5_crypt(const char* pw, const char* salt)
{
  //Trying to use the hashwrapper thing given by the hashlib2plus example
  // hashwrapper *md5Wrapper = new md5wrapper();
  static char ret[120];
  MD5_CTX ctx, ctx2;
  const char* magic = "$1$";
  char res[16];
  char h[16];
  //strcpy(res, pw);
  //strcat(res, magic);
  //strcat(res, salt);

  MD5_Init(&ctx); //initialize context before compute hash
  MD5_Update(&ctx, pw, strlen(pw)); //hash (added separately)
  MD5_Update (&ctx, salt, strlen(salt));
  MD5_Update(&ctx, pw, strlen(pw)); 
  MD5_Final(h, &ctx); // get final result
  
  int l = strlen(pw);

  // Replace res with the hashed string of pw + salt + pw ??
  char* sub;
  char tmp1[16];
  MD5_Init(&ctx);
  int num = fmin(16.0, 1.0);
  while (l > 0) {
    memcpy(tmp1, h, num);
    strcpy(h, tmp1);
    strcat(res, sub);
    l = l - 16;
  }
  int i = strlen(pw);
  for (i; i != 0; i >>= 1) {
    if (i & 1) {
      // res += '\x00'; //no idea what this is for... maybe extra conditions for looping? unknown
  printf("wtf before x00\n");
  fflush(stdout);
  //   strcat(res, '\x00');  
  printf("wtf after x00\n");
  fflush(stdout);
  }
    else {
//      res += pw[0];
    printf("wtf before pw0\n");
    fflush(stdout);
      char pw0 = pw[0];
      strcat(res, &pw0);
    printf("wtf after pw0\n");
    fflush(stdout);
    }
  }
//  printf("wtf bt update & pw0");
//  fflush(stdout);
  MD5_Update(&ctx, res, strlen(res)); //second time hashing the new Alternate (is that word LMAO)
//  printf("wtf bt update & final\n");
//  fflush(stdout);
  MD5_Final(h, &ctx);
//  printf("wtf bt Init & Final\n");
//  fflush(stdout);
  MD5_Init(&ctx2);
  i = 0;
//  printf("wtf bt Init and for loop\n");
//  fflush(stdout);
  for (i; i < 1000; i++) {
    char* tmp; //temp string
    if (i % 2 == 1) {
//  printf("wtf before i%2\n");
//  fflush(stdout);
//    strcat(tmp,pw);
      MD5_Update(&ctx2, pw, strlen(pw));
//  printf("wtf after 1%2\n");
//  fflush(stdout);
    }
    else {
//  printf("wtf before strcat tmp, h\n");
//  fflush(stdout);
//    strcat(tmp,h);
      MD5_Update(&ctx2, h, 16); //find out what it should be
//  printf("wtf after strcat tmp, h\n");
//  fflush(stdout);
    }
    if (i % 3 != 0) {
//  printf("wtf in i%3 start\n");
//  fflush(stdout);
//      strcat(tmp, salt);
      MD5_Update(&ctx2, salt, strlen(salt)); //find out what it should be
//  printf("wtf in i%3 end \n");
//  fflush(stdout);
    }
    if (i % 7 != 0) {
//  printf("wtf in 1%7 start\n");
//  fflush(stdout);  
//    strcat(tmp, pw);
      MD5_Update(&ctx2, pw, strlen(pw));
//  printf("wtf in 1%7 end\n");
//  fflush(stdout);
    }
    if (i % 2 == 1) {
//  printf("wtf in 1%2 start in else\n");
//  fflush(stdout);
//    strcat(tmp, h);
      MD5_Update(&ctx2, h, 16);
//  printf("wtf in 1%2 end in else\n");
//  fflush(stdout);
    }
    else {
//  printf("wtf else start\n");
//  fflush(stdout);
//    strcat(tmp,pw);
      MD5_Update(&ctx2, pw, strlen(pw));
//  printf("wtf else end\n");
//  fflush(stdout);
    }
//    MD5_Update(&ctx, tmp, strlen(tmp));
  }
  MD5_Final(h, &ctx2);
  printf("wtf before strcpy md5\n");
  fflush(stdout);
//  static char ret[200];
//  char* temp = to64(((h[0] << 16) | (h[6] << 8) | (h[12])), 4);
  strcpy(ret,to64(((h[0] << 16) | (h[6] << 8) | (h[12])), 4));//, sizeof(ret));
  printf("wtf1\n");
  fflush(stdout);
  strcat(ret, to64(((h[1] << 16) | (h[7] << 8) | (h[13])), 4));//, sizeof(ret));
  printf("wtf2\n");
  fflush(stdout);
  strcat(ret, to64(((h[2] << 16) | (h[8] << 8) | (h[14])), 4));//, sizeof(ret));
  printf("wtf3\n");
  fflush(stdout);
  strcat(ret, to64(((h[3] << 16) | (h[9] << 8) | (h[15])), 4));//, sizeof(ret));
  strcat(ret, to64(((h[4] << 16) | (h[10] << 8) | (h[5])), 4));//, sizeof(ret));
  strcat(ret, to64(h[11], 2));//, sizeof(ret));
  printf("wtf before ret");
  fflush(stdout);
  return ret;
}

