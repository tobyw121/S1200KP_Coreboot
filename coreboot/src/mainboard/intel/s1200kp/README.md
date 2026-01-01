# Intel S1200KP bring-up notes

**Board:** Intel S1200KP (server, 2012)
**CPU:** Intel Xeon E3-1220 v2 (Ivy Bridge, 4C/4T, no iGPU)
**Chipset/PCH:** Intel C206 (6-Series/C200, Cougar Point)
**OEM BIOS:** KPC2060H.86B.0023.2012.0710.2049 (2012-07-10)

## PCI devices
- PEG: NVIDIA GeForce GT 610 (10de:104a) + HDMI audio (10de:0e08)
- LAN1 (PCH GbE): Intel 82579LM (8086:1502)
- LAN2 (PCIe): Intel 82574L (8086:10d3)
- SATA AHCI: 8086:1c02, SMBus: 8086:1c22, LPC: 8086:1c56, MEI: 8086:1c3a
- PCH HDA: not present (autoport: "HDAudio not found on PCH")

## Memory
- 2× Kingston DDR3-1600 4GB (99U5584-005.A00LF)
- SPD addresses: 0x50, 0x52 (DIMM1/DIMM2 on channel A)

## SPI flash
- Size: 4 MB (BOARD_ROMSIZE_KB_4096)
- Regions: Descriptor 0x000000-0x000FFF; GbE 0x001000-0x002FFF; ME 0x003000-0x184FFF; BIOS 0x185000-0x3FFFFF

## Super I/O
- Detected by superiotool: Nuvoton NCT6775F / NCT5572D (id 0xb473) at 0x2e
- Port glue uses the NCT5572D driver to match the detected ID.

## Serial/keyboard
- COM1 @ 0x3f8 IRQ4 via Super I/O
- PS/2 keyboard/mouse @ 0x60/0x64 IRQ1/12
