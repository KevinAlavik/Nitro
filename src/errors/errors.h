#include <stdint.h>

#include "cpu/cpu.h"

void division_err_handler() {
    err("Division Error");
}

void debug_exception_handler() {
    err("Debug Exception");
}

void non_maskable_interrupt_handler() {
    err("Non-maskable Interrupt");
}

void breakpoint_trap_handler() {
    err("Breakpoint Trap");
}

void overflow_trap_handler() {
    err("Overflow Trap");
}

void bound_range_exceeded_handler() {
    err("Bound Range Exceeded");
}

void invalid_opcode_handler() {
    err("Invalid Opcode");
}

void device_not_available_handler() {
    err("Device Not Available");
}

void double_fault_handler() {
    err("Double Fault");
    hcf();
}

void coprocessor_segment_overrun_handler() {
    err("Coprocessor Segment Overrun");
}

void invalid_tss_handler() {
    err("Invalid TSS");
}

void segment_not_present_handler() {
    err("Segment Not Present");
}

void stack_segment_fault_handler() {
    err("Stack-Segment Fault");
}

void general_protection_fault_handler() {
    err("General Protection Fault");
}

void page_fault_handler() {
    err("Page Fault");
    hcf();  // Halt the system after handling page fault
}

void debug_handler() {
    err("Debug");
    // You may choose to return instead of halting the system for debug
}

void breakpoint_handler() {
    err("Breakpoint");
    // You may choose to return instead of halting the system for breakpoint
}

void overflow_handler() {
    err("Overflow");
}

void machine_check_handler() {
    err("Machine Check");
}

void triple_fault_handler() {
    err("Triple Fault");
    hcf();  // Halt the system after handling triple fault
}

void fpu_error_interrupt_handler() {
    err("FPU Error Interrupt");
}

void simd_floating_point_exception_handler() {
    err("SIMD Floating-Point Exception");
}

void alignment_check_handler() {
    err("Alignment Check");
}

void register_error_handlers() {
    set_idt_gate(0x0, (uint64_t)&division_err_handler, 0x28, 0x8E);
    set_idt_gate(0x1, (uint64_t)&debug_exception_handler, 0x28, 0x8E);
    set_idt_gate(0x2, (uint64_t)&non_maskable_interrupt_handler, 0x28, 0x8E);
    set_idt_gate(0x3, (uint64_t)&breakpoint_trap_handler, 0x28, 0x8E);
    set_idt_gate(0x4, (uint64_t)&overflow_trap_handler, 0x28, 0x8E);
    set_idt_gate(0x5, (uint64_t)&bound_range_exceeded_handler, 0x28, 0x8E);
    set_idt_gate(0x6, (uint64_t)&invalid_opcode_handler, 0x28, 0x8E);
    set_idt_gate(0x7, (uint64_t)&device_not_available_handler, 0x28, 0x8E);
    set_idt_gate(0x8, (uint64_t)&double_fault_handler, 0x28, 0x8E);
    set_idt_gate(0x9, (uint64_t)&coprocessor_segment_overrun_handler, 0x28, 0x8E);
    set_idt_gate(0xA, (uint64_t)&invalid_tss_handler, 0x28, 0x8E);
    set_idt_gate(0xB, (uint64_t)&segment_not_present_handler, 0x28, 0x8E);
    set_idt_gate(0xC, (uint64_t)&stack_segment_fault_handler, 0x28, 0x8E);
    set_idt_gate(0xD, (uint64_t)&general_protection_fault_handler, 0x28, 0x8E);
    set_idt_gate(0xE, (uint64_t)&page_fault_handler, 0x28, 0x8E);
    set_idt_gate(0x1, (uint64_t)&debug_handler, 0x28, 0x8E);
    set_idt_gate(0x3, (uint64_t)&breakpoint_handler, 0x28, 0x8E);
    set_idt_gate(0x4, (uint64_t)&overflow_handler, 0x28, 0x8E);
    set_idt_gate(0x12, (uint64_t)&machine_check_handler, 0x28, 0x8E);
    set_idt_gate(0x1E, (uint64_t)&simd_floating_point_exception_handler, 0x28, 0x8E);
    set_idt_gate(0x11, (uint64_t)&alignment_check_handler, 0x28, 0x8E);
}