#include <sys/syscall.h>
#include <stdio.h>
#include <stddef.h>
#include <type.h>
#include <size.h>

int main(int argc, char const *argv[]) {
  printf("I'm loaded\n I'm closed\n" );
  sys_exit(0);
  return 0;
}
