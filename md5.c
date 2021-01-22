#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//taking from slides, translating to see what it does; will change to avoid problems LMAO

const char base64[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//static char* ret;

char* 
to64(long v, int n) 
{
  static char str[5];
  char* rt = str;
  int i;

  if(n > 4) return NULL;
  memset(str, '\0', sizeof(str)); // empties str

  for(i = 1; i <= n; i++) {
    *rt++ = base64[v & 0x3f]; // new vals into str based on base64
    v >>= 6;
  }
  return (str);

}

char*
md5_crypt(const char* pw, const char* salt)
{
  //Trying to use the hashwrapper thing given by the hashlib2plus example
  // hashwrapper *md5Wrapper = new md5wrapper();
  static char ret[120]; // from 6 numbers that are 20 bits long
  MD5_CTX ctx, ctx2;
  static char* magic = "$1$";
  char res[16];
  char h[16];
  //strcpy(res, pw);
  //strcat(res, magic);
  //strcat(res, salt);

  MD5_Init(&ctx2); //initialize context before compute hash
  MD5_Update(&ctx2, pw, strlen(pw)); //hash (added separately)
  MD5_Update (&ctx2, salt, strlen(salt));
  MD5_Update(&ctx2, pw, strlen(pw)); 
  MD5_Final(h, &ctx2); // get final result
  
  int l = strlen(pw);

// Contextualize pw, magic & salt
  MD5_Init(&ctx);
  MD5_Update(&ctx, pw, l);
  MD5_Update(&ctx, magic, 1);
  MD5_Update(&ctx, salt, strlen(salt));

  // Replace res with the hashed string of pw + salt + pw ??
  char* sub;
  char tmp1[16];
//  MD5_Init(&ctx);
// int num = fmin(16.0, 1.0);
  while (l > 0) {
/*  memcpy(tmp1, h, num);
    strcpy(h, tmp1);
    strcat(res, sub);
*/  if (l > 16) 
      MD5_Update(&ctx, h, 16);
    else MD5_Update(&ctx, h, l);
    l = l - 16;
  }

  int i = strlen(pw);
  for (i; i != 0; i >>= 1) {
    if (i & 1) {
//    res += '\x00'; //no idea what this is for... maybe extra conditions for looping? unknown
      MD5_Update(&ctx, h + i, 1);
//    strcat(res, '\x00');  
  }
    else {
//    res += pw[0];
      MD5_Update(&ctx, pw + i, 1);
    }
  }
// h = MD5(res);
//  MD5_Update(&ctx, res, strlen(res)); //second time hashing the new Alternate (is that word LMAO)
  MD5_Final(h, &ctx);

//  MD5_Init(&ctx2);
  i = 0;
  for (i; i < 1000; i++) {
  MD5_Init(&ctx2);
    char* tmp; //temp string
    if (i % 2 == 1) {
//    strcat(tmp,pw);
      MD5_Update(&ctx2, pw, strlen(pw));
    }
    else {
//    strcat(tmp,h);
      MD5_Update(&ctx2, h, 16); //find out what it should be
    }
    if (i % 3 != 0) {
//    strcat(tmp, salt);
      MD5_Update(&ctx2, salt, strlen(salt)); //find out what it should be
    }
    if (i % 7 != 0) {
//    strcat(tmp, pw);
      MD5_Update(&ctx2, pw, strlen(pw));
    }
    if (i % 2 == 1) {
//    strcat(tmp, h);
      MD5_Update(&ctx2, h, 16);
    }
    else {
//    strcat(tmp,pw);
      MD5_Update(&ctx2, pw, strlen(pw));
    }
//    MD5_Update(&ctx, tmp, strlen(tmp));
    MD5_Final(h, &ctx);
  }
//  char *retr = to64(((h[0] << 16) | (h[6] << 8) | (h[12])), 4);
  strcpy(ret,to64(((h[0] << 16) | (h[6] << 8) | (h[12])), 4));//, sizeof(ret));
  strcat(ret, to64(((h[1] << 16) | (h[7] << 8) | (h[13])), 4));//, sizeof(ret));
  strcat(ret, to64(((h[2] << 16) | (h[8] << 8) | (h[14])), 4));//, sizeof(ret));
  strcat(ret, to64(((h[3] << 16) | (h[9] << 8) | (h[15])), 4));//, sizeof(ret));
  strcat(ret, to64(((h[4] << 16) | (h[10] << 8) | (h[5])), 4));//, sizeof(ret));
  strcat(ret, to64(h[11], 2));//, sizeof(ret));
  return ret;

}

