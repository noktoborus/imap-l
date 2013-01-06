/* vim: ft=c ff=unix fenc=utf-8
 * file: milex.c
 */
#include "milex.h"

void
milex_parse (struct milex *lex)
{
	register size_t i;
	if (!lex->_clt_fl)
		return;
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
		if (buffer[i] == '\n' || buffer[i] == '\r' || (buffer[i] == ' ' && lex->_clt_st != MILEX_C_QUOTE))
		{
			if (buffer[i] != ' ')
				lex->state |= MILEX_EOL;
			break;
		}
		else
		{
			if (buffer[i] == '"')
			{
				if (lex->_clt_fl >= 1 && lex->_clt[lex->_clt_fl - 1] == '\\')
				{
					lex->_clt[lex->_clt_fl - 1] = '"';
				}
				else
				{
					if (lex->_clt_st == MILEX_C_QUOTE)
						lex->_clt_st = MILEX_C_MIXED;
					else
						lex->_clt_st = MILEX_C_QUOTE;
				}
			}
			else
			{
				// append new char
				if (lex->_clt_sz <= lex->_clt_fl + 1)
				{
					char *tmp = realloc (lex->_clt, lex->_clt_sz + MILEX_BFSZ);
					if (!tmp)
					{
						lex->state = MILEX_FAIL | MILEX_FAIL_INTERNAL;
						break;
					}
					lex->_clt = tmp;
					lex->_clt_sz += MILEX_BFSZ;
				}
				if (lex->_clt_st == MILEX_C_NONE && (buffer[i] >= '0' && buffer[i] <= '9'))
					lex->_clt_st = MILEX_C_INT;
				lex->_clt[lex->_clt_fl++] = buffer[i];
			}
		}
	}
	if (!(lex->state & MILEX_FAIL))
	{
		lex->_clt[lex->clt_fl] = '\0';
		lex->state |= MILEX_OK;
		milex_parse (lex);
		if (!(lex->state & MILEX_FAIL))
			lex->state = MILEX_PROC;
	}
}

