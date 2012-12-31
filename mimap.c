/* vim: ft=c ff=unix fenc=utf-8
 * file: mimap.c
 */
#include "mimap.h"

#define LEX_BLSZ 128

void
mimap_ (struct mimap *mimap, const char *buffer, size_t bfsz)
{
	if (!mimap || mimap->status & MIMAP_CLOSE)
		return;
	if (bfsz == 0)
	{
		mimap->status |= MIMAP_CLOSE;
		return;
	}
	if (!buffer)
		return;
	//

}

void
mimap_login (struct mimap *mimap, const char *login, const char *secret)
{
}

void
mimap_select (struct mimap *mimap, const char *path, const bool isquery)
{
}

void
mimap_append (struct mimap *mimap, const char *buffer, size_t bfsz)
{
}

void
mimap_logout (struct mimap *mimap)
{
}

