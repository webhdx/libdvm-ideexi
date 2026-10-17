// SPDX-License-Identifier: GPL-2.0-only
#pragma once
#include <stdbool.h>
#include <dvm.h>

#ifdef __cplusplus
extern "C" {
#endif

// Swiss header has no extern "C" of its own
#include <ideexi.h> // __io_ataa (Slot A), __io_atab (Slot B), __io_atac (Serial Port 1, M.2 Loader)

// Select EXI clock: true = 32MHz (default), false = 16MHz
void dvmIdeExiSetSpeed32MHz(bool enable);

// Probe and mount IDE-EXI v2+ devices as "ataa", "atab" and "atac".
// Call after dvmInit()/dvmInitDefault(), which registers the filesystem drivers.
unsigned dvmProbeMountIdeExi(unsigned cache_pages, unsigned sectors_per_page);

#ifdef __cplusplus
}
#endif
