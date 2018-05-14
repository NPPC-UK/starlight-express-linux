#ifndef filterwheel
#define filterwheel

enum operation {CHANGE_FILTER, GET_FILTER};

struct filter_options {
  enum operation op;
  unsigned char filter;
};


struct filter_options parse_options(int argc, char* argv[]);

#endif
