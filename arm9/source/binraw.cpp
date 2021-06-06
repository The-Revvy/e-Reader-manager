#include "rs.h"

#include <cstdio>
#include <cstring>
#include <vector>

void deinterleave_dotcode(unsigned char* data, unsigned char* interleave, int dotcodepointer, int size, int dotcodeinterleave)
{
	for (int i = 0; i < 0x40; i++)
		data[i] = interleave[(i * dotcodeinterleave) + dotcodepointer];
}

int raw2bin(std::vector<std::vector<unsigned char>>& bins, const std::vector<std::vector<unsigned char>>& raws)
{
	unsigned char data[64];

	unsigned char NEDC_STR[] = "NINTENDO";
	int MultiStrip;
	int multistrip_type;
	unsigned char bin_header[24];
	std::vector<unsigned char> bin_heap(0x10008);
	std::vector<unsigned char> dotcodetemp_heap(0x15C28);
	std::vector<unsigned char> raw_heap(0x15C28);
	unsigned char* bin = bin_heap.data();
	unsigned char* dotcodetemp = dotcodetemp_heap.data();
	unsigned char* raw = raw_heap.data();
	int dotcodepointer = 0;
	int dotcodeinterleave;

	int result;
	int i, j, k;
	int size;
	int numraw, numbin = 0;


	numraw = raws.size();
	if (numraw == 0)
		return -2; //Invalid raw file.

	initialize_rs();
	for (k = 0; k < numraw; k++)
	{
		size = raws[k].size();
		//if((size!=0x750)&&(size!=0xB60))
		if (size == 0)
			continue;
		//return -2; //Invalid raw nedc size.

		memcpy(raw, raws[k].data(), size > 0x15C28 ? 0x15C28 : size);

		for (i = 0; i < 0x0C; i++)
			for (j = 0; j < 2; j++)
				bin_header[(i * 2) + j] = raw[(i * 0x68) + j];
		result = correct_errors(bin_header, 24, 16);
		if (result < 0)
			continue;
		//return -3; //NEDC Read Error

	//j=((size==0xB60)?0xB38:0x724);
		j = (bin_header[4] * bin_header[7] * 0x68);
		int kk = j % 0x66;
		j /= 0x66;
		if (kk > 0)
			j++;

		dotcodeinterleave = bin_header[7];
		dotcodepointer = 0;

		for (i = 2; i < j; i++)
		{
			if ((i % 0x68) == 0) i += 2;
			dotcodetemp[dotcodepointer++] = raw[i];
		}

		deinterleave_dotcode(data, dotcodetemp, 0, size, dotcodeinterleave);
		result = correct_errors(data, 0x40, 0x10);
		if (result < 0)
			continue;
		//return -3; //NEDC Read Error
		for (i = 0; i < 8; i++)
			if (data[i + 0x1A] != NEDC_STR[i])
			{
				MultiStrip = 1;
				multistrip_type = 1;
				break;
			}
		if (i == 8)
		{
			multistrip_type = 0;
		}
		else
		{
			continue;
			//return -2		//Not an NEDC dotcode.
		}

		for (i = 0; i < 0x30; i++)
			bin[i] = data[i];

		for (i = 1; i < dotcodeinterleave; i++)
		{
			deinterleave_dotcode(data, dotcodetemp, i, size, dotcodeinterleave);
			result = correct_errors(data, 0x40, 0x10);
			if (result < 0)
				break;
			//return -3; //RS_econding failed
			for (j = 0; j < 0x30; j++)
				bin[(i * 0x30) + j] = data[j];
		}
		if (result < 0)
			continue;

		int outsize = ((size == 0xB60) ? 0x840 : 0x540);
		bins.emplace_back();
		std::vector<unsigned char>& outbin = bins.back();
		outbin.resize(outsize);
		memcpy(outbin.data(), bin, outsize);

		numbin++;
	}

	free_rs();

	return (numbin > 0) ? 0 : -1;
}
