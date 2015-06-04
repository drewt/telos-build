telos-build
===========

This is a meta repository which packages up various components needed to set up
a cross development environment for Telos.

Fetching the sources
--------------------

Simply pass the --recursive option to git-clone when cloning this repository.

    $ git clone --recursive https://github.com/drewt/telos-meta.git

Configuration
-------------

The build may be configured by editing the makefile directly.  There are three
parameters you may want to customize: the target, the installation prefix
(for the cross-toolchain), and the sysroot directory (where libc is installed).

Building
--------

Running `make` in this directory will build the toolchain, libc and kernel.
You must explicitly create the initial RAM disk by running `make initrd`.

    $ make
    # make initrd

Running
-------

A script is provided to run the kernel in QEMU.

    $ ./qemu
