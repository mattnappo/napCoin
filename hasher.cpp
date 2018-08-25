#include "napcoin.h"
#include "json/json.hpp"
#include "argon2/argon2.h"
#include <string>

#define HASHLEN 32
#define SALTLEN 16
using namespace std;
#include <string.h>
#include <stdlib.h>

char* strdup (const char* s) {
  size_t slen = strlen(s);
  char* result = (char *)malloc(slen + 1);
  if(result == NULL) {
    return NULL;
  }
  memcpy(result, s, slen+1);
  return result;
}
string hash_block(string contents) {
  string TO_HASH = contents;
  uint8_t hash1[HASHLEN];
  uint8_t hash2[HASHLEN];
  uint8_t salt[SALTLEN];
  memset( salt, 0x00, SALTLEN );
  uint8_t *pwd = (uint8_t *)strdup(TO_HASH.c_str());
  uint32_t pwdlen = strlen((char *)pwd);
  uint32_t t_cost = 2;            // 1-pass computation
  uint32_t m_cost = (1<<16);      // 64 mebibytes memory usage
  uint32_t parallelism = 1;       // number of threads and lanes
  argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdlen, salt, SALTLEN, hash1, HASHLEN);
  argon2_context context = {
    hash2,  /* output array, at least HASHLEN in size */
    HASHLEN, /* digest length */
    pwd, /* password array */
    pwdlen, /* password length */
    salt,  /* salt array */
    SALTLEN, /* salt length */
    NULL, 0, /* optional secret data */
    NULL, 0, /* optional associated data */
    t_cost, m_cost, parallelism, parallelism,
    ARGON2_VERSION_13, /* algorithm version */
    NULL, NULL, /* custom memory allocation / deallocation functions */
    /* by default only internal memory is cleared (pwd is not wiped) */
    ARGON2_DEFAULT_FLAGS
  };
  int rc = argon2i_ctx( &context );
  if (ARGON2_OK != rc) {
    printf("Error: %s\n", argon2_error_message(rc));
    exit(1);
  }
  free(pwd);
  stringstream hexstr;
  for (int i = 0; i < HASHLEN; ++i) {
    int a = static_cast< int >(hash2[i]);
    hexstr << setfill('0') << setw(2) << hex << a;
  }
  string hash = hexstr.str();
  return hash;
}