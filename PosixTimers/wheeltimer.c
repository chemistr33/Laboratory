#include <errno.h>
#include <memory.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static void print_current_system_time() {
  time_t t;
  time(&t); // get current time
  printf("%s", ctime(&t));
}

typedef struct pair_ {
  int a;
  int b;
} pair_t;
pair_t pair = {10, 20};

void timer_callback_system_time(union sigval arg) {
  print_current_system_time();
  pair_t *pair = (pair_t *)arg.sival_ptr; // extract the user data structure
  printf("pair : [%u %u]\n", pair->a, pair->b);
}

void timer_demo() {

  int ret;
  struct sigevent evp;
  timer_t timer;
  memset(&timer, 0, sizeof(timer_t));
  memset(&evp, 0, sizeof(struct sigevent));
  evp.sigev_value.sival_ptr = (void *)&pair;
  evp.sigev_notify = SIGEV_THREAD;
  evp.sigev_notify_function = timer_callback_system_time;
  ret = timer_create(CLOCK_REALTIME, &evp, &timer);
  if (ret < 0) {
    printf("Timer Creation Failed, errno = %d\n", errno);
  }

  struct itimerspec ts;
  ts.it_value.tv_sec = 5;
  ts.it_value.tv_nsec = 0;
  ts.it_interval.tv_sec = 1;
  ts.it_interval.tv_nsec = 0;

  ret = timer_settime(timer, 0, &ts, NULL);
  if (ret < 0) {
    printf("Timer Arming Failed, errno = %d\n", errno);
    exit(0);
  } else {
    print_current_system_time();
    printf("Timer Armed Successfully\n");
  }
}

int main() {
  print_current_system_time();
  timer_demo();
  pause();
  return 0;
}
