// SPDX-License-Identifier: GPL-2.0-only
#include <dvm_ideexi.h>

void dvmIdeExiSetSpeed32MHz(bool enable)
{
	_ideexi_speed = enable ? EXI_SPEED32MHZ : EXI_SPEED16MHZ;
}

unsigned dvmProbeMountIdeExi(unsigned cache_pages, unsigned sectors_per_page)
{
	static const struct {
		const char* name;
		int chn;
		DISC_INTERFACE* iface;
	} slots[] = {
		{ "ataa", 0, &__io_ataa },
		{ "atab", 1, &__io_atab },
		{ "atac", 2, &__io_atac },
	};

	unsigned num_mounted = 0;

	for (unsigned i = 0; i < sizeof(slots) / sizeof(slots[0]); i ++) {
		// Check the EXI ID first: the driver's IDENTIFY wait takes ~5s on an empty slot
		if (ide_exi_inserted(slots[i].chn)) {
			num_mounted += dvmProbeMountDiscIface(slots[i].name, slots[i].iface, cache_pages, sectors_per_page);
		}
	}

	return num_mounted;
}
