# libdvm-ideexi

IDE-EXI / M.2 Loader disc interface for [libdvm](https://github.com/extremscorner/libdvm) (libogc2), for GameCube and Wii.

The driver (`source/ideexi.c`, `include/ideexi.h`) is the IDE-EXI ATA driver from Swiss.

## Build & install

Inside a devkitPro environment with `libogc2` and `libogc2-libdvm` installed:

```sh
dkp-makepkg -i        # builds a pacman package and installs it
# or, without packaging:
catnip build gamecube wii && catnip install gamecube wii
```

`pkgver` is derived from git history, so `dkp-makepkg` needs at least one commit.

## Usage

```c
#include <dvm_ideexi.h>

dvmInitDefault();                  // registers FAT/exFAT/ext2 drivers, mounts built-in devices
dvmProbeMountIdeExi(32, 8);        // mounts "ataa:", "atab:", "atac:" (M.2 Loader is "atac:")
```

Link with `-ldvm_ideexi -ldvm -lfat` (CMake: `target_link_libraries(app dvm_ideexi dvm fat)`).

The `__io_ataa` / `__io_atab` / `__io_atac` interfaces can also be passed directly to `dvmProbeMountDiscIface()`.

- EXI clock defaults to 32MHz; `dvmIdeExiSetSpeed32MHz(false)` switches to 16MHz.
- `dvmProbeMountIdeExi()` only probes slots reporting the IDE-EXI v2+ EXI ID (M.2 Loader does), so empty slots don't cost the driver's ~5s IDENTIFY timeout. IDE-EXI v1 adapters report no ID; mount them with `dvmProbeMountDiscIface()`.
- Driver logs go through `SYS_Report()`; route them with `SYS_EnableGecko()` or `SYS_STDIO_Report(true)`.
- `<ideexi.h>` (included by `dvm_ideexi.h`) exposes the raw driver API and `ataDriveInfo` (drive model, serial, size). The driver keeps this single global, so only one IDE-EXI device is supported at a time.

## License

GPL-2.0, see `LICENSE`.
