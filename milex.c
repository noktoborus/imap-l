/* vim: ft=c ff=unix fenc=utf-8
 * file: milex.c
 */
#include "milex.h"

void
milex_next (struct milex *lex, char *buffer, size_t bfsz)
{
	if (!lex || !buffer)
		return;
	if (bfsz == 0 && (lex->state == MILEX_PROC)
		lex->state = MILEX_OK;
}

