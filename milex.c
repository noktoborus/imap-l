/* vim: ft=c ff=unix fenc=utf-8
 * file: milex.c
 */
#include "milex.h"

void
milex_parse (struct milex *lex)
{
	register size_t i;
	// TODO: set lex->valast
	switch (lex->_clt_type)
	{
		case MILEX_C_INT:
			if (!lex->_clt_fl)
				break;
			lex->valast->type = MILEX_T_UINT;
			lex->valast->type = stroul (lex->_clt, NULL, 10);
			break;
		case MILEX_C_MIXED:
			// check NIL (None)
			break;
		case MILEX_C_QUOTE:
			// must trow exception
			break;
		case MILEX_C_TUPLE:
			// check NULL "[]"
			if (!lex->_clt_fl)
				lex->valast->type = MILEX_T_NULL;
			else
			{
				// TODO: recursive to milex_next
			}
			break;
		case MILEX_C_LIST:
			// check NULL "()"
			if (!lex->_clt_fl)
				lex->valast->type = MILEX_T_NULL;
			else
			{
				// TODO: recursive to milex_next
			}
			break;
	}
}

size_t
milex_next (struct milex *restrict lex, const char *restrict buffer, size_t bfsz)
{
	register size_t i;
	if (!lex || !buffer)
		return 0;
	if (bfsz == 0 && (lex->state == MILEX_PROC))
		lex->state = MILEX_EOL;
	for (i = 0; i < bfsz && !(lex->state & (MILEX_EOL | MILEX_FAIL)); i ++)
	{
		switch (buffer[i])
		{
			case '\n':
				lex->state = MILEX_OK | MILEX_EOL;
				break;
			case '"':
				// skip if already in another quotes (lists, ...)
				if (lex->state != MILEX_PROC || lex->state != MILEX_QUOTE)
					break;
				if (lex->_clt_fl > 0 && lex->_clt[lex->_clt_fl - 1] == '\\')
				{
					lex->_clt[lex->_clt_fl - 1] = '"';
				}
				else
				if (lex->state == MILEX_QUOTE)
					lex->state = MILEX_PROC;
				else
					lex->state = MILEX_QUOTE;
				break;
			case '[':
				switch (lex->state)
				{
					case MILEX_PROC:
						if (lex->_clt_fl > 0)
						{
							lex->state = MILEX_OK;
							i --;
						}
						else
							lex->state = MILEX_TUPLE;
						break;
					case MILEX_TUPLE:
						lex->_clt_qcc ++;
						break;
				}
				break;
			case '(':
				switch (lex->state)
				{
					case MILEX_PROC:
						if (lex->_clt_fl > 0)
						{
							// finalize previous node
							lex->state = MILEX_OK;
							i --;
						}
						else
							lex->state = MILEX_LIST;
						break;
					case MILEX_LIST:
						lex->_clt_qcc ++;
						break;
				}
				break;
			case ']':
				if (lex->state == MILEX_TUPLE)
				{
					if (lex->_clt_qcc > 0)
						lex->_clt_qcc --;
					else
					{
						lex->state = MILEX_OK;
						lex->_clt_type = MILEX_C_TUPLE;
					}
				}
				break;
			case ')':
				if (lex->state == MILEX_LIST)
				{
					if (lex->_clt_qcc > 0)
						lex->_clt_qcc --;
					else
					{
						lex->state = MILEX_OK;
						lex->_clt_type = MILEX_C_LIST;
					}
				}
				break;
			default:
				if (lex->_clt_fl + 2 > lex->_clt_sz)
				{
					char *tmp;
					// resize
					tmp = realloc ((void*)lex->_clt, lex->_clt_sz + MILEX_BFSZ);
					if (!tmp)
					{
						lex->state = MILEX_FAIL;
						break;
					}
					lex->_clt = tmp;
				}
				// append
				lex->_clt[lex->_clt_fl ++] = buffer[i];
				lex->_clt[lex->_clt_fl] = '\0';
				// check for integer
				if (lex->state == MILEX_PROC && (buffer[i] >= '0' && buffer[i] <= '9'))
					lex->_clt_type = MILEX_C_INT;
				else
				if (lex->_clt_type == MILEX_C_INT && (buffer[i] < '0' || buffer[i] > '9'))
					lex->_clt_type = MILEX_C_MIXED;
				break;
		}
		if (lex->state & MILEX_OK)
		{
			if (lex->_clt_type == MILEX_C_NONE && lex->_clt_fl > 0)
				lex->_clt_type = MILEX_C_MIXED;
			milex_parse (lex);
			lex->_clt_type = MILEX_C_NONE;
		}
	}
	return i;
}

