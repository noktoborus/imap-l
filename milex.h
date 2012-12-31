/* vim: ft=c ff=unix fenc=utf-8
 * file: milex.h
 */
#ifndef _MILEX_1356959206_H_
#define _MILEX_1356959206_H_

#define MILEX_OK   0x0
#define MILEX_FAIL 0x1
#define MILEX_PROC 0x2
#define MILEX_SMASK 0x3
#define MILEX_FAIL_INTERNAL 0x4
#define MILEX_FAIL_PARSE    0x8
#define MILEX_T_STRING 0x1
#define MILEX_T_UINT   0x2
#define MILEX_T_SINT   0x3
#define MILEX_T_LIST   0x4

struct milex_value
{
	uint8_t type;
	size_t size;
	union
	{
		struct milex_value *list;
		char *vstring;
		unsigned int vuint;
		int vint;
	} value;
};

struct milex
{
	char *_crnt;
	size_t _crnt_fl;
	size_t _crnt_sz;
	struct milex_value value;
	uint8_t state;
};

/* \r, \n and bfsz == 0 match as EOL */
void milex_next (struct milex *lex, char *buffer, size_t bfsz);

#endif /* _MILEX_1356959206_H_ */

