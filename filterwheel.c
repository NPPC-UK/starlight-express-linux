#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

  return 0;
}


struct filter_options parse_options(int argc, char* argv[]) {
  struct filter_options opts = {CHANGE_FILTER, 0};
  char c;
  while ((c = getopt(argc, argv, "g")) != -1 ) {
    switch (c) {
      case 'g':
        opts.op = GET_FILTER;
        break;
      default:
        printf("Unknown option: %o \n", c);
    }
  }

  if (opts.op == CHANGE_FILTER) {
    if (argc != 2) {
      printf("Incorrect number of arguments!");
      exit(1);
    }
    opts.filter = atoi(argv[argc -1]);
    if (opts.filter == 0) {
      printf("Filter number must be a natural number.");
      exit(1);
    }
  } 
  return opts;
}






