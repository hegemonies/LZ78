#ifndef CODER_H
#define CODER_H
#include <inttypes.h>
#include "lz78.h"

enum {
    MaxCodeLength = 4
};

typedef struct {
    uint8_t code[MaxCodeLength];
    size_t length;
} CodeUnit;

int encode(uint32_t code_point, CodeUnit *code_units);

void encode_file(FILE *out, Code *code, Dictionary dic);

uint32_t decode(const CodeUnit *code_unit);

int decode_file(FILE *in, Code *code);

int read_next_code_unit(FILE *in, CodeUnit *code_units);

int write_code_unit(FILE *out, const CodeUnit *code_unit);

void write_to_file_decode(FILE *out, Code *code, Dictionary dic);

#endif