/*
 * Copyright (c) 2014 The Chromium OS Authors.
 *
 * Part of this file is adapted from coreboot
 * src/arch/x86/include/arch/cpu.h and
 * src/arch/x86/lib/cpu.c
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ASM_CPU_H
#define _ASM_CPU_H

enum {
	X86_VENDOR_INVALID = 0,
	X86_VENDOR_INTEL,
	X86_VENDOR_CYRIX,
	X86_VENDOR_AMD,
	X86_VENDOR_UMC,
	X86_VENDOR_NEXGEN,
	X86_VENDOR_CENTAUR,
	X86_VENDOR_RISE,
	X86_VENDOR_TRANSMETA,
	X86_VENDOR_NSC,
	X86_VENDOR_SIS,
	X86_VENDOR_ANY = 0xfe,
	X86_VENDOR_UNKNOWN = 0xff
};

struct cpuid_result {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
};

/*
 * Generic CPUID function
 */
static inline struct cpuid_result cpuid(int op)
{
	struct cpuid_result result;
	asm volatile(
		"mov %%ebx, %%edi;"
		"cpuid;"
		"mov %%ebx, %%esi;"
		"mov %%edi, %%ebx;"
		: "=a" (result.eax),
		  "=S" (result.ebx),
		  "=c" (result.ecx),
		  "=d" (result.edx)
		: "0" (op)
		: "edi");
	return result;
}

/*
 * Generic Extended CPUID function
 */
static inline struct cpuid_result cpuid_ext(int op, unsigned ecx)
{
	struct cpuid_result result;
	asm volatile(
		"mov %%ebx, %%edi;"
		"cpuid;"
		"mov %%ebx, %%esi;"
		"mov %%edi, %%ebx;"
		: "=a" (result.eax),
		  "=S" (result.ebx),
		  "=c" (result.ecx),
		  "=d" (result.edx)
		: "0" (op), "2" (ecx)
		: "edi");
	return result;
}

/*
 * CPUID functions returning a single datum
 */
static inline unsigned int cpuid_eax(unsigned int op)
{
	unsigned int eax;

	__asm__("mov %%ebx, %%edi;"
		"cpuid;"
		"mov %%edi, %%ebx;"
		: "=a" (eax)
		: "0" (op)
		: "ecx", "edx", "edi");
	return eax;
}

static inline unsigned int cpuid_ebx(unsigned int op)
{
	unsigned int eax, ebx;

	__asm__("mov %%ebx, %%edi;"
		"cpuid;"
		"mov %%ebx, %%esi;"
		"mov %%edi, %%ebx;"
		: "=a" (eax), "=S" (ebx)
		: "0" (op)
		: "ecx", "edx", "edi");
	return ebx;
}

static inline unsigned int cpuid_ecx(unsigned int op)
{
	unsigned int eax, ecx;

	__asm__("mov %%ebx, %%edi;"
		"cpuid;"
		"mov %%edi, %%ebx;"
		: "=a" (eax), "=c" (ecx)
		: "0" (op)
		: "edx", "edi");
	return ecx;
}

static inline unsigned int cpuid_edx(unsigned int op)
{
	unsigned int eax, edx;

	__asm__("mov %%ebx, %%edi;"
		"cpuid;"
		"mov %%edi, %%ebx;"
		: "=a" (eax), "=d" (edx)
		: "0" (op)
		: "ecx", "edi");
	return edx;
}

/* Standard macro to see if a specific flag is changeable */
static inline int flag_is_changeable_p(uint32_t flag)
{
	uint32_t f1, f2;

	asm(
		"pushfl\n\t"
		"pushfl\n\t"
		"popl %0\n\t"
		"movl %0,%1\n\t"
		"xorl %2,%0\n\t"
		"pushl %0\n\t"
		"popfl\n\t"
		"pushfl\n\t"
		"popl %0\n\t"
		"popfl\n\t"
		: "=&r" (f1), "=&r" (f2)
		: "ir" (flag));
	return ((f1^f2) & flag) != 0;
}

static inline void mfence(void)
{
	__asm__ __volatile__("mfence" : : : "memory");
}

/**
 * cpu_enable_paging_pae() - Enable PAE-paging
 *
 * @cr3:	Value to set in cr3 (PDPT or PML4T)
 */
void cpu_enable_paging_pae(ulong cr3);

/**
 * cpu_disable_paging_pae() - Disable paging and PAE
 */
void cpu_disable_paging_pae(void);

/**
 * cpu_has_64bit() - Check if the CPU has 64-bit support
 *
 * @return 1 if this CPU supports long mode (64-bit), 0 if not
 */
int cpu_has_64bit(void);

/**
 * cpu_vendor_name() - Get CPU vendor name
 *
 * @vendor:	CPU vendor enumeration number
 *
 * @return:	Address to hold the CPU vendor name string
 */
const char *cpu_vendor_name(int vendor);

#define CPU_MAX_NAME_LEN	49

/**
 * cpu_get_name() - Get the name of the current cpu
 *
 * @name: Place to put name, which must be CPU_MAX_NAME_LEN bytes including
 * @return pointer to name, which will likely be a few bytes after the start
 * of @name
 * \0 terminator
 */
char *cpu_get_name(char *name);

/**
 *
* x86_cpu_get_desc() - Get a description string for an x86 CPU
*
* This uses cpu_get_name() and is suitable to use as the get_desc() method for
* the CPU uclass.
*
* @dev:		Device to check (UCLASS_CPU)
* @buf:		Buffer to place string
* @size:	Size of string space
* @return 0 if OK, -ENOSPC if buffer is too small, other -ve on error
*/
int x86_cpu_get_desc(struct udevice *dev, char *buf, int size);

/**
 * cpu_call64() - Jump to a 64-bit Linux kernel (internal function)
 *
 * The kernel is uncompressed and the 64-bit entry point is expected to be
 * at @target.
 *
 * Paging must be enabled by cpu_paging_enable().
 *
 * This function is used internally - see cpu_jump_to_64bit() for a more
 * useful function.
 *
 * @setup_base:	Pointer to the setup.bin information for the kernel
 * @target:	Pointer to the start of the kernel image
 */
void cpu_call64(uint64_t target, ulong setup_base);

/**
 * cpu_jump_to_64bit() - Jump to a 64-bit Linux kernel
 *
 * The kernel is uncompressed and the 64-bit entry point is expected to be
 * at @target.
 *
 * @setup_base:	Pointer to the setup.bin information for the kernel
 * @target:	Pointer to the start of the kernel image
 */
int cpu_jump_to_64bit(ulong setup_base, uint64_t target);

/**
 * cpu_set_paging() - Enable 64-bit paging
 *
 * Assuming U-Boot area is identically mapped.
 *
 * @pgtable:	Address of PML4 table
 */
int cpu_set_paging(uint64_t *pgtable);

int cpu_paging_enable(void);
int cpu_paging_disable(void);

unsigned long cpu_page_remap(unsigned long start, unsigned long size, uint64_t phys_addr);

#endif
