_pkgname=libdvm-ideexi
pkgname="libogc2-${_pkgname}-git"
pkgver=r0.0000000
pkgrel=1
pkgdesc='IDE-EXI / M.2 Loader disc interface for libdvm on GameCube and Wii.'
arch=('any')
license=('GPL-2.0-only')
groups=('gamecube-dev' 'wii-dev')
depends=('devkitPPC>=r49' 'libogc2' 'libogc2-libdvm')
makedepends=('catnip' 'cmake' 'git' 'libogc2-cmake' 'ninja')
provides=("libogc2-${_pkgname}")
conflicts=("libogc2-${_pkgname}")
options=(!strip libtool staticlibs !buildflags)

prepare() {
	cd "${startdir}"
	git update-index --assume-unchanged PKGBUILD
}

pkgver() {
	cd "${startdir}"
	printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short=7 HEAD)"
}

build() {
	cd "${startdir}"
	catnip build gamecube wii
}

package() {
	cd "${startdir}"
	DESTDIR="${pkgdir}" catnip install gamecube wii
	for platform in gamecube wii; do
		install -Dm 644 LICENSE -t "${pkgdir}${DEVKITPRO}/libogc2/${platform}/share/licenses/${_pkgname}"
	done
}
