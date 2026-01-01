/* SPDX-License-Identifier: CC-PDDC */

#undef SUPERIO_DEV
#undef SUPERIO_PNP_BASE
#define SUPERIO_DEV             SIO0
#define SUPERIO_PNP_BASE        0x2e

#define W83667HG_A_SHOW_SP1     1
#define W83667HG_A_SHOW_KBC     1

#include "superio/winbond/w83667hg-a/acpi/superio.asl"
