SHELL = /bin/sh

target = i386-telos
prefix = $(CURDIR)/prefix
bindir = $(prefix)/bin

# if this is to be something different, the headers from sysroot/ need to be
# copied to the new location, or else gcc will be unhappy
sysroot = $(CURDIR)/sysroot

gcc_built = $(bindir)/i386-telos-gcc
binutils_built = $(bindir)/i386-telos-ld
toolchain_built = $(binuitls_built) $(gcc_built)
libc_built = $(sysroot)/usr/lib/libc.a

all: kernel libc

gcc: $(gcc_built)
binutils: $(binutils_built)
toolchain: $(binutils_built) $(gcc_built)
libc: $(libc_built)

$(binutils_built):
	cd build/binutils && \
		../../binutils/configure --target=$(target) \
			--prefix="$(prefix)" --with-sysroot="$(sysroot)" \
			--disable-werror && \
		$(MAKE) && \
		$(MAKE) install

$(gcc_built): $(binutils_built)
	export PATH="$(bindir):$$PATH" && \
		cd build/gcc && \
		../../gcc/configure --target=$(target) --prefix="$(prefix)" \
			--with-sysroot="$(sysroot)" --enable-languages=c && \
		$(MAKE) all-gcc all-target-libgcc && \
		$(MAKE) install-gcc install-target-libgcc

$(libc_built): $(toolchain_built)
	export PATH="$(bindir):$$PATH" && \
		cd build/libc && \
		../../libc/configure --prefix=/usr --target=$(target) && \
		$(MAKE) && \
		$(MAKE) DESTDIR="$(sysroot)" install
	rm -rf $(sysroot)/usr/include $(sysroot)/usr/lib
	mv $(sysroot)/usr/$(target)/include $(sysroot)/usr/include
	mv $(sysroot)/usr/$(target)/lib $(sysroot)/usr/lib
	rm -rf $(sysroot)/usr/$(target)

kernel: $(toolchain_built)
	export PATH="$(bindir):$$PATH" && cd kernel && $(MAKE)

# initrd depends on toolchain and libc, but we don't specify them here to
# prevent building them as root
initrd:
	export PATH="$(bindir):$$PATH" && cd initrd && $(MAKE)

binutils-clean:
	cd build/binutils && $(MAKE) clean
	rm -f $(binutils_built)

gcc-clean:
	cd build/gcc && $(MAKE) clean
	rm -f $(gcc_built)

libc-clean:
	cd build/libc && $(MAKE) clean
	rm -f $(libc_built)

kernel-clean:
	cd kernel && $(MAKE) clean

initrd-clean:
	cd initrd && $(MAKE) clean

all-clean: binutils-clean gcc-clean libc-clean kernel-clean

.PHONY: build-dirs gcc binutils toolchain toolchain-install libc kernel initrd \
	all-clean binutils-clean gcc-clean libc-clean kernel-clean initrd-clean
