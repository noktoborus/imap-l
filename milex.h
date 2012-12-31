/* vim: ft=c ff=unix fenc=utf-8
 * file: milex.h
 */
#ifndef _MILEX_1356959206_H_
#define _MILEX_1356959206_H_

struct milex
{
	uint8_t state;
	char *_current;
};

/* \r, \n and bfsz == 0 match as EOL */
void milex_next (struct milex *lex, char *buffer, size_t bfsz);

#endif /* _MILEX_1356959206_H_ */

