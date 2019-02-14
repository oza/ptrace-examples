//#define _POSIX_C_SOURCE 200112L

#define _XOPEN_SOURCE

/* C standard library */
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* POSIX */
#include <unistd.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/types.h>

/* Linux */
#include <syscall.h>
#include <sys/ptrace.h>

#define FATAL(...) \
  do { \
    fprintf(stderr, "strace: " __VA_ARGS__); \
    fputc('\n', stderr); \
    exit(EXIT_FAILURE); \
  } while (0)

#if !defined(PTRACE_O_EXITKILL)
#define PTRACE_O_EXITKILL (1 << 20)
#endif

int
main(int argc, char **argv)
{
  if (argc <= 1)
    FATAL("too few arguments: %d", argc);

  pid_t pid = atoi(argv[1]);

  /* parent */
  int ret = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
  //waitpid(pid, &status, 0);
  if (ret < 0) {
    perror("ptrace");
    FATAL("failed to attach");
  }
  int status;
  ///waitpid(pid, &status, __WALL);
  waitid(P_PID, pid, NULL, WSTOPPED);
  ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);

  for (;;) {
    /* Enter next system call */
    if (ptrace(PTRACE_SYSCALL, pid, 0, 0) == -1)
      FATAL("%s", strerror(errno));
    if (waitid(P_PID, pid, NULL, WCONTINUED) == -1)
      FATAL("%s", strerror(errno));

    // /* Gather system call arguments */
    // struct user_regs_struct regs;
    // if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1)
    //   FATAL("%s", strerror(errno));
    // long syscall = regs.orig_rax;

    // /* Print a representation of the system call */
    // fprintf(stderr, "%ld(%ld, %ld, %ld, %ld, %ld, %ld)",
    //     syscall,
    //     (long)regs.rdi, (long)regs.rsi, (long)regs.rdx,
    //     (long)regs.r10, (long)regs.r8,  (long)regs.r9);

    fprintf(stdout, "hooked. waiting...\n");
    sleep(1);

    /* Run system call and stop on exit */
    //if (ptrace(PTRACE_SYSCALL, pid, 0, 0) == -1)
    //  FATAL("%s", strerror(errno));
    //if (waitid(P_PID, pid, NULL, WCONTINUED) == -1)
    //  FATAL("%s", strerror(errno));

    /* Get system call result */
    //if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1) {
    //  fputs(" = ?\n", stderr);
    //  if (errno == ESRCH)
    //    exit(regs.rdi); // system call was _exit(2) or similar
    //  FATAL("%s", strerror(errno));
    //}

    /* Print system call result */
    //fprintf(stderr, " = %ld\n", (long)regs.rax);
  }
}
