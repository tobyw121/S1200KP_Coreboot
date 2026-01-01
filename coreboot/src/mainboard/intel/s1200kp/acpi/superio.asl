/* SPDX-License-Identifier: CC-PDDC */

#undef SUPERIO_DEV
#undef SUPERIO_PNP_BASE
#define SUPERIO_DEV             SIO0
#define SUPERIO_PNP_BASE        0x2e

#define NCT5572D_SHOW_SP1       1
#define NCT5572D_SHOW_KBC       1

#include "superio/nuvoton/nct5572d/acpi/superio.asl"
