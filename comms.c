#include <unistd.h>
#include <stdio.h>

#include "hidapi/hidapi.h"

#include "comms.h"

char current_filter(hid_device *dev) {
  unsigned char cmd[2], res[2];
  int tret;
  cmd[0] = 0;
  cmd[1] = 0;

  hid_write(dev, cmd, 2);
  tret = hid_read_timeout(dev, res, 2, 5000);
  if (tret > 0) {
    return res[0];
  } else if (tret == 0) {
    return -1;
  }
}

enum Result change_filter(unsigned char filter,
                   hid_device *dev) {
  unsigned char cmd[2];
  char res, start;
  cmd[0] = filter;
  cmd[1] = 0;

  start = current_filter(dev);
  if (start == -1) {
    printf("Cannot get current filter\n");
    return ERR;
  }
  else if (start == filter)
    return OK;

  while (start == 0) {
    usleep(100000);
    start = current_filter(dev);
    printf("Current Filter %d\n", start);
  }

  if (start == -1) {
    return ERR;
  }

  // Wait to prevent locks maybe?
  usleep(100000);
  hid_write(dev, cmd, 2);
  
  do {
    usleep(100000);
    res = current_filter(dev);
    if (res == -1)
      return ERR;
  } while (res == 0 || res == start);

  return OK;
}

