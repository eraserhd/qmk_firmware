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

#define POINTING_DEVICE_CS_PIN GP14
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP15
#define SPI_MOSI_PIN GP16
#define SPI_MISO_PIN GP17
