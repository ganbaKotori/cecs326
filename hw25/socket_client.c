#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
int main() {
  int s;
  char message[80] = "this shouldnt be here";
  struct sockaddr_in      srv_addr;
  /* Get a socket. */
  s = socket(PF_INET, SOCK_DGRAM, 0);
  /* Put server's address into a socket structure */
  //memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_addr.s_addr = inet_addr("134.139.248.3");
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(7);
  /* Request the connection to the server */
  bind(s, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
  /*Get time from serve*/
  read(s, message, 80);
  printf("%s\n",message);
  close(s);
  return 0;
}
