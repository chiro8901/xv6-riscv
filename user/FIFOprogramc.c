#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

const int n = 20;

int
main(int argc, char *argv[])
{
  pause(20);
  int p2c = open("p2c", O_RDONLY);
  if (p2c < 0) {
    fprintf(2, "open failed\n");
    exit(1);
  }
  unsigned char k;
  int pid = getpid();

  while(1) {
    k = 0;
    int n = read(p2c, &k, 1);
    if(n == 0){
        break;
    }
    printf("[Child %d] %d : ", pid, k);
    if(k % 15 == 0){
    printf("FizzBuzz\n");
    }else if(k % 5 == 0){
    printf("Buzz\n");        
    }else if(k % 3 == 0){
    printf("Fizz\n");        
    }else{
    printf("%d\n", k);
    }
    pause(20);
  }
  close(p2c);
  exit(0);
}
