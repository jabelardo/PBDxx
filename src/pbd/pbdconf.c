
#include <pbd/pbdconf.h>
#include <stdlib.h>

pbd_conf pbd_default_conf = {
    true, malloc, free, realloc, calloc
};