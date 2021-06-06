#include <nds.h>

// sav -> must be a 0x20000 byte long block containing the current e-reader save
// bindata -> should contain the data to inject in bin format
// binlength -> length of the data in bindata
// titledata -> must be a 35 byte long block containing the title that should be displayed
void bin_inject(u8* sav, const u8* bindata, size_t binlength, const u8* titledata);
