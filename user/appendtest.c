#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void
test_append(void)
{
  int fd;
  char buf[20];
  int n;

  printf("append test starting\n");

  // 1. 新規作成 (O_CREATE | O_TRUNC)
  fd = open("append.txt", O_CREATE | O_WRONLY | O_TRUNC);
  if(fd < 0){
    printf("create failed\n");
    exit(1);
  }
  write(fd, "AAA", 3);
  close(fd);

  // 2. 追記モードでオープン (O_APPEND)
  fd = open("append.txt", O_WRONLY | O_APPEND);
  if(fd < 0){
    printf("open append failed\n");
    exit(1);
  }
  write(fd, "BBB", 3);
  close(fd);

  // 3. 結果確認
  fd = open("append.txt", O_RDONLY);
  if(fd < 0){
    printf("open read failed\n");
    exit(1);
  }
  n = read(fd, buf, sizeof(buf));
  if(n < 0){
    printf("read failed\n");
    exit(1);
  }
  buf[n] = 0;
  close(fd);

  if(strcmp(buf, "AAABBB") == 0){
    printf("append test passed: content is '%s'\n", buf);
  } else {
    printf("append test failed: content is '%s', expected 'AAABBB'\n", buf);
  }
}

int
main(void)
{
  test_append();
  exit(0);
}