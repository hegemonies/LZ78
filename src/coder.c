#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "coder.h"
#include "lz78.h"

int encode(uint32_t code_point, CodeUnit *code_units)
{
	uint8_t count = 0;
	for (uint32_t i = code_point; i > 0; i >>= 1) {
		count++;
	}
	if (count <= 7) {
		code_units->code[0] = code_point;
		code_units->length = 1;
		return 0;
	} else if (count <= 11) {
		code_units->code[0] = 0xC0 | (code_point >> 6);
		code_units->code[1] = 0x80 | (code_point & 0x3F);
		code_units->length = 2;
		return 0;
	} else if (count <= 16) {
		code_units->code[0] =  0xE0 | (code_point >> 12);
		code_units->code[1] =  0x80 | ((code_point & 0xFC0) >> 6);
		code_units->code[2] =  0x80 | (code_point & 0x3F);
		code_units->length = 3;
		return 0;
	} else if (count <= 21) {
		code_units->code[0] = 0xF0 | (code_point >> 18);
		code_units->code[1] = 0x80 | ((code_point & 0x3F000) >> 12);
		code_units->code[2] = 0x80 | ((code_point & 0xFC0) >> 6);
		code_units->code[3] = 0x80 | (code_point & 0x3F);
		code_units->length = 4;
		return 0;
	}
	return -1;
}

void encode_file(FILE *out, Code *code, Dictionary dic)
{
	for (int i = 1; i < dic.size; i++) {
		CodeUnit code_unit;

		uint32_t code_point;
		code_point = code[i].num;
		
		encode(code_point, &code_unit);
		write_code_unit(out, &code_unit);

		code_point = code[i].str;
		encode(code_point, &code_unit);
		write_code_unit(out, &code_unit);
	}
}

uint32_t decode(const CodeUnit *code_unit)
{
	uint32_t code_point;
	if ((code_unit->code[0] >> 7) == 0) {
		return (code_point = code_unit->code[0]);
	} else if (code_unit->code[0] <= 0xDF) {
			return (code_point = (((code_unit->code[0] & 0x1F) << 6) | (code_unit->code[1] & 0x3F)));
	} else if (code_unit->code[0] <= 0xEF) {
			return (((code_unit->code[0] & 0xF) << 12) | ((code_unit->code[1] & 0x3F) << 6) | (code_unit->code[2] & 0x3F));
	} else if (code_unit->code[0] <= 0xF7) {
			return (((code_unit->code[0] & 0x7) << 18) | ((code_unit->code[1] & 0x3F) << 12) | ((code_unit->code[2] & 0x3F) << 6) | (code_unit->code[3] & 0x3F));
	}
	return 0;
}

int decode_file(FILE *in, Code *code)
{
	CodeUnit code_units;

	uint8_t buf;
	fread(&buf, 1, 1, in);
	int i;
	for (i = 1; !feof(in); i++) {
		uint8_t enum_bit = 0;
		while(buf & (1 << (7 - enum_bit))) {
			enum_bit++;
		}
		if (enum_bit == 1) {
			fread(&buf, 1, 1, in);
			continue;
		}
		if (enum_bit == 0) {
			enum_bit = 1;
		}
		if (enum_bit <= MaxCodeLength) {
			code_units.length = 0;
			for (int i = 1; i <= enum_bit; i++) {
				code_units.code[i - 1] = buf;
				code_units.length++;
				if (i == enum_bit) {
					break;
				}
				fread(&buf, 1, 1, in);
				if (feof(in)) {
					break;
				}
				if ((buf & 0xC0) != 0x80) {
					break;
				}
			}
		}
		uint32_t tmp = decode(&code_units);
		code[i].num = tmp;

		fread(&buf, 1, 1, in);

		code[i].str = buf;

		fread(&buf, 1, 1, in);
		//printf("%d\n", i);
	}

	code[i].num = 0;
	code[i].str = '~';
	return 0;
}


void write_to_file_decode(FILE *out, Code *code, Dictionary dic)
{
	for (int i = 1; i < dic.size; i++) {
		if (code[i].num == 0) {
			printf("1 :=: %c\n", code[i].str);
			fprintf(out, "%c", code[i].str);
		} else {
			printf("2 :=: %s.%c.%d\n", dic.dic_i[code[i].num].str, code[i].str, code[i].num);
			fprintf(out, "%s", dic.dic_i[code[i].num].str);
			fprintf(out, "%c", code[i].str);
		}
	}
}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{
	if (fwrite(code_unit->code, 1, code_unit->length, out) == code_unit->length) {
		return 0;
	}
	return -1;
}