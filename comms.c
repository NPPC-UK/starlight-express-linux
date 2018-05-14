#include <unistd.h>
#include <stdio.h>

#include "hidapi/hidapi.h"

unsigned char current_filter(hid_device *dev) {
  unsigned char cmd[2], res[2];
  cmd[0] = 0;
  cmd[1] = 0;

  hid_write(dev, cmd, 2);
  hid_read(dev, res, 2);

  return res[0];
}

void change_filter(unsigned char filter,
                   hid_device *dev) {
  unsigned char cmd[2];
  unsigned char res, start;
  cmd[0] = filter;
  cmd[1] = 0;

  start = current_filter(dev);
  if (start == filter) {
    return;
  }

  while (start == 0) {
    usleep(100000);
    start = current_filter(dev);
  }

  hid_write(dev, cmd, 2);
  
  do {
    usleep(100000);
    res = current_filter(dev);
  } while (res == 0 || res == start);

  return;
}

