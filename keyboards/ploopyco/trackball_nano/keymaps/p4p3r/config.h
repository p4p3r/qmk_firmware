#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// My Ploopy Nano movements are inverted
// when using the default value.
#undef POINTING_DEVICE_ROTATION_90
#undef POINTING_DEVICE_ROTATION_180
#define POINTING_DEVICE_ROTATION_270
#undef POINTING_DEVICE_INVERT_X
#undef POINTING_DEVICE_INVERT_Y

#endif
