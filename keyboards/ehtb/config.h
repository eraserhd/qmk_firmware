// Copyright 2023 Jason Felice (@eraserhd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define POINTING_DEVICE_CS_PIN GP13
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

#define POINTING_DEVICE_TASK_THROTTLE_MS 10

#define POINTING_DEVICE_ROTATION_90 1
#define POINTING_DEVICE_INVERT_Y 1
#define PMW33XX_CPI 1000
