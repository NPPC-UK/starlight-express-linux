#ifndef comms
#define comms

#include "hidapi/hidapi.h"

// Returns the current filter
// A return value of 0 indicates that the filter wheel
// is still moving
char current_filter(hid_device *dev);

// Changes the filter on the filterwheel
// Blocks until the filter is in position.
//
// Assumes the filter wheel is not currently moving
enum Result change_filter(unsigned char filter, hid_device *dev);

enum Result {OK, ERR};

#endif
