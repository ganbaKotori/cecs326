/* to compile: gcc -Wall md5.c -lssl */
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h> /* strlen */
#include <stdio.h> /* printf */
#include <openssl/evp.h> /* md5 hash */
#include <openssl/md5.h>
int main(int argc, char* argv[])
{

	int src_fd;
	int dest_fd;
	char 
  /* Digest variables */
  EVP_MD_CTX md_context;
  const EVP_MD* md = EVP_md5();
  unsigned int md_length;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  int i; /* loop variable */

  /* Initialise the digest */
  EVP_DigestInit(&md_context, md);

  /* Feed data into the digest */
  EVP_DigestUpdate(&md_context, argv[1], strlen(argv[1]));

  /* Get the digest and it's length */
  EVP_DigestFinal(&md_context, md_value, &md_length);

  /* Print the result */
  for (i = 0; i < md_length; i++)
  {
    printf("%x",md_value[i]);
  }
  printf("\n");

  close(src_fd);
  close(dest_fd);
  return 0;
}
