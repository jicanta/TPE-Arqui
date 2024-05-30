#include <font.h>
#include <stdint.h>

uint8_t * getCharMapping(uint8_t c) {
	return pixel_chars + CHAR_HEIGHT * (c-31);
}