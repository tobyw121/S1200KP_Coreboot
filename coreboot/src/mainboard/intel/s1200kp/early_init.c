/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <device/pci_ops.h>
#include <device/pnp_ops.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <superio/nuvoton/common/nuvoton.h>
#include <superio/nuvoton/nct6776/nct6776.h>

#define SERIAL_DEV PNP_DEV(0x2e, NCT6776_SP1)

void bootblock_mainboard_early_init(void)
{
	pci_write_config16(PCI_DEV(0, 0x1f, 0), 0x82, 0x3f0f);
	pci_write_config16(PCI_DEV(0, 0x1f, 0), 0x80, 0x0010);

	nuvoton_pnp_enter_conf_state(SERIAL_DEV);
	pnp_set_logical_device(SERIAL_DEV);

	/* Route SP1 to 0x3f8/IRQ4 for early serial debugging. */
	nuvoton_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);

	nuvoton_pnp_exit_conf_state(SERIAL_DEV);
}
