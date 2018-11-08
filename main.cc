#include "helpers.h"
#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Display help message.
int display_help() {
  printf("demo - Print hello to the screen.\n"
         "Commands:\n"
         " --help,  -h   Print this help screen\n");
  return 0;
}

// Thread routine that handles delivering the message.
void *hello_routine(void *) {
  demo::say_hello();
  return nullptr;
}

int main(int argc, char *argv[]) {
  // Loop, parsing arguments.
  // See: man 3 getopt_long for details.
  for (;;) {
    int option_index = 0;
    static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                           {0, 0, 0, 0}};

    const int c = getopt_long(argc, argv, "h", long_options, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
    case 'h':
      return display_help();
    default:
      printf("demo: invalid option specified\n");
      exit(EXIT_FAILURE);
    }
  }

  // Say hello in a very contrived way by creating another thread.
  pthread_t thread_id = 0;
  const int status =
      pthread_create(&thread_id, nullptr, hello_routine, nullptr);
  if (status != 0) {
    perror("failed to create thread");
    return EXIT_FAILURE;
  }

  // Join on the thread.
  pthread_join(thread_id, nullptr);

  return EXIT_SUCCESS;
}
