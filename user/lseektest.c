#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void
test(void)
{
  int fd;
  char buf[10];
  int off;

  printf("lseek test starting\n");

  // テスト用ファイル作成
  fd = open("lseektest.txt", O_CREATE | O_RDWR | O_TRUNC);
  if(fd < 0){
    printf("open failed\n");
    exit(1);
  }

  // "hello" を書き込む (5バイト)
  if(write(fd, "hello", 5) != 5){
    printf("write failed\n");
    exit(1);
  }

  // 1. SEEK_SET: 先頭に戻す
  off = lseek(fd, 0, SEEK_SET);
  printf("1. lseek(fd, 0, SEEK_SET) -> %d (expected 0)\n", off);
  
  // 読み込み確認
  if(read(fd, buf, 5) != 5){
    printf("read failed\n");
    exit(1);
  }
  buf[5] = 0;
  printf("   read content: %s\n", buf);

  // 2. SEEK_SET: 200バイト目に移動
  off = lseek(fd, 200, SEEK_SET);
  printf("2. lseek(fd, 200, SEEK_SET) -> %d (expected 200)\n", off);

  // 書き込み (ファイル拡張が発生)
  if(write(fd, "world", 5) != 5){
    printf("write at 200 failed\n");
    exit(1);
  }

  // 3. SEEK_CUR: 現在位置(205)から5バイト戻る
  off = lseek(fd, -5, SEEK_CUR);
  printf("3. lseek(fd, -5, SEEK_CUR) -> %d (expected 200)\n", off);
  
  // 読み込み確認
  if(read(fd, buf, 5) != 5){
    printf("read at 200 failed\n");
    exit(1);
  }
  buf[5] = 0;
  printf("   read content: %s\n", buf);

  // 4. SEEK_END: 末尾(205)からさらに100バイト拡張
  off = lseek(fd, 100, SEEK_END);
  printf("4. lseek(fd, 100, SEEK_END) -> %d (expected 305)\n", off);

  close(fd);
  printf("lseek test finished\n");
}

int
main(void)
{
  test();
  exit(0);
}