OUTPUT_ARCH(mips)
ENTRY(entry)
SECTIONS {
	. = 0x80580000;
	.text : {
		*(.text.entry)
		*(.text)
		*(.rodata)
	}

	.data : {
		*(.data)
	}

	.bss : {
		*(.bss)
	}

	workspace = .;
}
