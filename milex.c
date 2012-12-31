/* vim: ft=c ff=unix fenc=utf-8
 * file: milex.c
 */
#include "milex.h"

void
milex_parse (struct milex *lex)
{
	/* TODO */
}

void
milex_next (struct milex *restrict lex, const char *restrict buffer, size_t bfsz)
{
	register size_t i = 0;
	if (!lex || !buffer)
		return;
	if (bfsz == 0 && (lex->state == MILEX_PROC))
		lex->state = MILEX_EOL | MILEX_OK;
	for (; i < bfsz; i ++)
	{
		if (buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == ' ')
		{
			milex_parse (lex);
			lex->state = MILEX_OK;
			if (buffer[i] != ' ')
				lex->state |= MILEX_EOL;
		}
	}
}

