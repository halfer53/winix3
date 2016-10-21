#include <sys/syscall.h>
#include <stdio.h>
#include <stddef.h>
#include <type.h>
#include <size.h>

int main(int argc, char const *argv[]) {
  int pid = 0;
  pid = fork();
  printf("My child pid is %d\n",pid );
  return 0;
}
