 #include <stdio.h>
#include <interrupts.h>

#pragma pack(push)		                // push of current alignment
#pragma pack (1) 		                // alignment of structures to 1 byte

// interruptions descriptor (given by prof)
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;
//
#pragma pack(pop)		                // recover current alignment

DESCR_INT * idt = (DESCR_INT *) 0;      // idt table with 255 possible entries

// function given by prof
static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}

void loadIDT() {
