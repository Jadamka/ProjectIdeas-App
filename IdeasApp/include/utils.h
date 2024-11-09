#ifndef DEF_UTILS_H
#define DEF_UTILS_H

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))    // for single pointer, for example (char* [])
#define ARRAY_SIZE_2P(a) (sizeof(*a) / sizeof(*a[0])) // for double pointer, for example: (char**)

#endif
