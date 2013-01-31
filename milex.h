/* vim: ft=c ff=unix fenc=utf-8
 * file: milex.h
 */
#ifndef _MILEX_1356959206_H_
#define _MILEX_1356959206_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MILEX_BFSZ 128
#define MILEX_BLVL 4

#define MILEX_PROC 0x0
#define MILEX_FAIL 0x1
#define MILEX_OK   0x2
#define MILEX_EOL  0x4
#define MILEX_QUOTE 0x8
#define MILEX_LIST  0x10
#define MILEX_TUPLE 0x20
/* types */
#define MILEX_T_NULL   0x0
#define MILEX_T_STRING 0x1
#define MILEX_T_UINT   0x2
#define MILEX_T_LIST   0x4
/* collect states */
#define MILEX_C_NONE   0x0
#define MILEX_C_MIXED  0x1
#define MILEX_C_INT    0x2
#define MILEX_C_LIST   0x3
#define MILEX_C_TUPLE  0x4

struct milex_value_t
{
	uint8_t type;
	size_t size;
	size_t max; // use in type == MILEX_T_LIST
	union
	{
		void *p;
		struct milex_value_t **list;
		char *vstring;
		uint32_t vint;
	} value;
};

struct milex
{
	char *_clt; // collect buffer
	size_t _clt_fl;
	size_t _clt_sz;
	struct milex_value_t *value;
	uint8_t state;
	// TODO: remove _clt_type, use state for detect type (MILEX_LIST | MILEX_OK as example)
	uint8_t _clt_type; // collect type
	uint8_t _clt_qcc; // depth count (for '[', '(')
};

/* \r, \n and bfsz == 0 match as EOL */
size_t milex_next (struct milex * restrict lex, const char * restrict buffer, size_t bfsz);

#endif /* _MILEX_1356959206_H_ */

