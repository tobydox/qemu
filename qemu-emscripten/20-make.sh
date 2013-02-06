#!/bin/sh

. ./00-build-vars.sh

cd $BUILD

make -j4 -k

cd $TARGET

echo Linking LLVM bitcode files - ignore above linking errors
llvm-link -o qemu-system-i386.bc ../util/*.o ../qobject/*.o ../qapi/*.o ../trace/*.o ../xbzrle.o ../glib.o ../pixman.o ../pixman-32.o ../pixman-64.o ../aio-posix.o ../async.o ../audio/audio.o ../audio/noaudio.o ../backends/rng-egd.o ../backends/rng-random.o ../backends/rng.o ../block.o ../block/blkdebug.o ../block/blkverify.o ../block/commit.o ../block/raw-posix.o ../block/raw.o ../block/stream.o ../blockdev.o ../blockjob.o ../disas/i386.o ../dma-helpers.o ../hmp.o ../hw/acpi.o ../hw/acpi_piix4.o ../hw/apm.o ../hw/block-common.o ../hw/cdrom.o ../hw/cirrus_vga.o ../hw/dma.o ../hw/e1000.o ../hw/fdc.o ../hw/fifo.o ../hw/fw_cfg.o ../hw/hd-geometry.o ../hw/hid.o ../hw/hpet.o ../hw/i2c.o ../hw/i8254.o ../hw/i8254_common.o ../hw/i8259.o ../hw/i8259_common.o ../hw/ide/ahci.o ../hw/ide/atapi.o ../hw/ide/core.o ../hw/ide/isa.o ../hw/ide/pci.o ../hw/ide/piix.o ../hw/ide/qdev.o ../hw/irq.o ../hw/isa-bus.o ../hw/loader.o ../hw/msmouse.o ../hw/null-machine.o ../hw/pam.o ../hw/parallel.o ../hw/pci/msi.o ../hw/pci/msix.o ../hw/pci/pci.o ../hw/pci/pci_bridge.o ../hw/pci/pci_host.o ../hw/pci/pcie.o ../hw/pci/pcie_aer.o ../hw/pci/pcie_host.o ../hw/pci/pcie_port.o ../hw/pci/shpc.o ../hw/pci/slotid_cap.o ../hw/pci_bridge_dev.o ../hw/pckbd.o ../hw/pcspk.o ../hw/pflash_cfi01.o ../hw/pm_smbus.o ../hw/ps2.o ../hw/qdev-addr.o ../hw/qdev-monitor.o ../hw/qdev-properties-system.o ../hw/qdev-properties.o ../hw/qdev.o ../hw/serial-isa.o ../hw/serial-pci.o ../hw/serial.o ../hw/smbus.o ../hw/smbus_eeprom.o ../hw/sysbus.o hw/i386/../mc146818rtc.o ../hw/vga-isa.o ../hw/vga-pci.o ../hw/vmmouse.o ../hw/watchdog.o ../iohandler.o ../main-loop.o ../net/checksum.o ../net/dump.o ../net/hub.o ../net/net.o ../net/queue.o ../net/socket.o ../net/util.o ../os-posix.o ../page_cache.o ../qapi-types.o ../qapi-visit.o ../qemu-char.o ../qemu-coroutine-io.o ../qemu-coroutine-lock.o ../qemu-coroutine-sleep.o ../qemu-coroutine.o ../qemu-log.o ../qemu-timer.o ../qmp-marshal.o ../qmp.o ../qom/container.o ../qom/cpu.o ../qom/object.o ../qom/qom-qobject.o ../qtest.o ../readline.o ../tcg-runtime.o ../thread-pool.o ../ui/console.o ../ui/cursor.o ../ui/input.o ../ui/keymaps.o ../ui/qemu-pixman.o ../ui/sdl.o ../ui/sdl_zoom.o ../ui/x_keymap.o ../vl.o arch_init.o balloon.o cpu-exec.o cpus.o cputlb.o disas.o dump.o exec.o fpu/softfloat.o gdbstub.o hw/device-hotplug.o hw/i386/../apic.o hw/i386/../apic_common.o hw/i386/../debugcon.o hw/i386/../debugexit.o hw/i386/../ioapic.o hw/i386/../ioapic_common.o hw/i386/../kvmvapic.o hw/i386/../multiboot.o hw/i386/../pc-testdev.o hw/i386/../pc.o hw/i386/../pc_piix.o hw/i386/../pc_sysfw.o hw/i386/../pci/pci-hotplug.o hw/i386/../piix_pci.o hw/i386/../smbios.o hw/i386/../vmport.o hw/vga.o ioport.o kvm-stub.o memory.o memory_mapping.o monitor.o savevm.o target-i386/arch_dump.o target-i386/arch_memory_mapping.o target-i386/cc_helper.o target-i386/cpu.o target-i386/excp_helper.o target-i386/fpu_helper.o target-i386/helper.o target-i386/int_helper.o target-i386/kvm-stub.o target-i386/machine.o target-i386/mem_helper.o target-i386/misc_helper.o target-i386/seg_helper.o target-i386/smm_helper.o target-i386/svm_helper.o target-i386/translate.o tcg/optimize.o tcg/tcg.o tci.o disas/tci.o translate-all.o xen-stub.o


cp ../pc-bios/acpi-dsdt.aml .
cp ../pc-bios/bios.bin .
cp ../pc-bios/vgabios-cirrus.bin .
cp ../pc-bios/pxe-e1000.rom .

$EMSCRIPTEN/emcc \
	qemu-system-i386.bc \
	--embed-file acpi-dsdt.aml \
	--embed-file bios.bin \
	--embed-file vgabios-cirrus.bin \
	--embed-file pxe-e1000.rom \
	-s UNALIGNED_MEMORY=1 \
	-O0 \
	--closure 0 \
	-v \
	-s EXPORTED_FUNCTIONS="['_main']" \
	-s TOTAL_MEMORY=300000000 \
	-o qemu.js


