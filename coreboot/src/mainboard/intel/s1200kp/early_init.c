/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <device/pci_ops.h>
#include <device/pnp_ops.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <superio/winbond/common/winbond.h>
#include <superio/winbond/w83667hg-a/w83667hg-a.h>

#define SERIAL_DEV PNP_DEV(0x2e, W83667HG_A_SP1)

void bootblock_mainboard_early_init(void)
{
	/*
	* Mirror the OEM LPC decode ranges so that COM1, the keyboard controller
	* and the Super I/O configuration ports are available for bootblock and
	* payload consumers (e.g. SeaBIOS) right from reset.
	*/
	pci_write_config16(PCH_LPC_DEV, LPC_EN, 0x3f0f);
	pci_write_config16(PCH_LPC_DEV, LPC_IO_DEC, 0x0010);

	winbond_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
}
