/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ops.h>

static void mainboard_init(struct device *dev)
{
	struct device *peg = dev_find_slot(0, PCI_DEVFN(1, 0));

	/*
	 * The S1200KP boots exclusively with the PEG slot populated (NVIDIA
	 * GT610). Ensure legacy VGA forwarding is enabled so SeaBIOS can run
	 * the option ROM and expose the device as the primary console.
	 */
	if (peg) {
		pci_or_config16(peg, PCI_COMMAND,
			      PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
			      PCI_COMMAND_MASTER);
		pci_or_config16(peg, PCI_BRIDGE_CONTROL, PCI_BRIDGE_CTL_VGA);
	}
}

static void mainboard_enable(struct device *dev)
{
	dev->ops->init = mainboard_init;
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};
