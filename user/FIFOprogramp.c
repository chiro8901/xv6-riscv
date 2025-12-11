#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
const int n = 20;

int
main(int argc, char *argv[])
{
  // pause(20);
  int p2c = open("p2c", O_WRONLY);
  if (p2c < 0) {
    fprintf(2, "open failed\n");
    exit(1);
  }
  for (int i = 1; i <= n; i++) {
    write(p2c, &i, 1);
    pause(10);
  }
  close(p2c);
  exit(0);
}
