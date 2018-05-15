#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "hidapi/hidapi.h"

#include "comms.h"
#include "filterwheel.h"

int main(int argc, char* argv[]) {
  unsigned char response;
  unsigned char buf[2];
  struct hid_device_info *devs, *cur_dev;
  struct filter_options opts;

  opts = parse_options(argc, argv);

  hid_device *dev = hid_open(0x1278, 0x0920, NULL);

  if (dev == NULL) {
    printf("An error occured: Could not open device.\n" );
    return 1;
  }

  if (opts.op == GET_FILTER) {
    printf("%d\n", current_filter(dev));
  } else if (opts.op == CHANGE_FILTER){
    change_filter(opts.filter, dev);  
  }


  hid_close(dev);

  hid_exit();

  return 0;
}


struct filter_options parse_options(int argc, char* argv[]) {
  struct filter_options opts = {CHANGE_FILTER, 0};
  char c;
  int opt_index = 0;

  static struct option long_options[] = {
    {"get", 0, NULL, 'g'},
    {"help", 0, NULL, 'h'},
  };

  while ((c = getopt_long(argc, argv, "gh", long_options, &opt_index)) != -1 ) {
    switch (c) {
      case 'g':
        opts.op = GET_FILTER;
        break;
      case 'h':
        print_help_and_exit(0);
      case '?':
        printf("Unknown option: %d \n", c);
        print_help_and_exit(1);
      default:
        break;
    }
  }

  if (opts.op == CHANGE_FILTER) {
    if (argc != 2) {
      printf("Incorrect number of arguments!");
      print_help_and_exit(1);
    }
    opts.filter = atoi(argv[argc -1]);
    if (opts.filter == 0) {
      printf("Filter number must be a natural number.");
      print_help_and_exit(1);
    }
  } 
  return opts;
}

void print_help_and_exit(char exit_status) {
  printf("usage: filterwheel [-g] [-h] [filter_number]\n");
  printf("\tfilter_number:  The number of the filter that you want to use\n");
  printf("\t-g, --get:      Get the current filter\n");
  printf("\t-h, --help:     Print this help message\n");
  exit(exit_status);
}
