/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/azalia_device.h>

/* The S1200KP platform does not expose onboard audio codecs. Provide empty
 * verb/config tables so the generic azalia driver links cleanly. */
const u32 cim_verb_data[] = {};
const u32 pc_beep_verbs[0] = {};

struct azalia_codec mainboard_azalia_codecs[] = {
        { /* terminator */ },
};

AZALIA_ARRAY_SIZES;
