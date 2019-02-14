#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// for gettid
#include <sys/types.h>
#include <sys/syscall.h>
#include <stddef.h>

// for fprintf
#include <stdint.h>


static pid_t gettid(void)
{
  return syscall(SYS_gettid);
}

static void* fileio_thread_main(void* args)
{
  pid_t pid = getpid();
  pid_t tid = gettid();
  fprintf(stdout, "start fileio thread. (pid, tid): %jd %jd\n", (intmax_t) pid, (intmax_t) tid);

  while (1) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
      printf("open(\"/dev/urandom\")[1]: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    unsigned x = 0;
    fread(&x, sizeof(x), 1, urandom);
    printf("fread(\"/dev/urandom\")[1] = 0x%08x\n", x);

    FILE *urandom2 = fopen("/dev/urandom", "r");
    if (!urandom2) {
      printf("fopen(\"/dev/urandom\")[2]: %s\n", strerror(errno));
    } else {
      x = 0;
      fread(&x, sizeof(x), 1, urandom2);
      printf("fread(\"/dev/urandom\")[2] = 0x%08x\n", x);
    }

    x = 0;
    fread(&x, sizeof(x), 1, urandom);
    printf("fread(\"/dev/urandom\")[1] = 0x%08x\n",x);

    if (urandom2)
      fclose(urandom2);
    fclose(urandom);
    sleep(1);
  }
}

static void* others_main(void* args)
{
  while(1) {
    sleep(1);
  }
}

int main(void)
{
  const int nr_threads = 3;

  pid_t pid = getpid();
  pid_t tid = gettid();
  fprintf(stdout, "start fileio thread. (pid, tid): %jd %jd\n", (intmax_t) pid, (intmax_t) tid);

  while (1) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
      printf("open(\"/dev/urandom\")[1]: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }

    unsigned x = 0;
    fread(&x, sizeof(x), 1, urandom);
    printf("fread(\"/dev/urandom\")[1] = 0x%08x\n", x);

    FILE *urandom2 = fopen("/dev/urandom", "r");
    if (!urandom2) {
      printf("fopen(\"/dev/urandom\")[2]: %s\n", strerror(errno));
    } else {
      x = 0;
      fread(&x, sizeof(x), 1, urandom2);
      printf("fread(\"/dev/urandom\")[2] = 0x%08x\n", x);
    }

    x = 0;
    fread(&x, sizeof(x), 1, urandom);
    printf("fread(\"/dev/urandom\")[1] = 0x%08x\n",x);

    if (urandom2)
      fclose(urandom2);
    fclose(urandom);
    sleep(1);
  }

  return 0;
}
