#include "inject.h"

#include <string.h>

#include "crc.h"

void bin_inject(u8* sav, const u8* bindata, size_t binlength, const u8* titledata) {
	int savpos = 65540;
	size_t vpksize = binlength - 81;
	size_t vpksize2 = binlength - 83;

	memcpy(sav + savpos, titledata, 35);
	savpos += 35;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x04;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x00;
	sav[savpos++] = vpksize & 0xFF;
	sav[savpos++] = (vpksize >> 8) & 0xFF;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x00;
	sav[savpos++] = 0x00;
	sav[savpos++] = vpksize2 & 0xFF;
	sav[savpos++] = (vpksize2 >> 8) & 0xFF;
	memcpy(sav + savpos, bindata + 83, vpksize2);
	savpos += vpksize2;

	crcaitsith(sav);
}
