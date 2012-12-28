/* vim: ft=c ff=unix fenc=utf-8
 * file: mimap.h
 * MiniIMAP4 lib
 */
#ifndef _MIMAP_1356622174_H_
#define _MIMAP_1356622174_H_
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MIMAP_BLSZ 4096
#define MIMAP_ACTIVE 0x1 /* connection established */
#define MIMAP_READY  0x2 /* ready for commands (logged in) */
#define MIMAP_CLOSE  0x8 /* connection closed */

union mimap_id
{
	/* all part must be contain only latin1 */
	uint32_t one;
	char part[4];
};

struct mimap_query
{
	union mimap_id id;
	/* query buffer */
	char *query;
	/* response buffer */
	char *response;
	/* fullness buffer */
	size_t query_fl;
	/* real size of buffer */
	size_t query_sz;
	size_t response_fl;
	size_t response_sz;
	/* link to next node */
	struct mimap_query *next;
};

struct mimap
{
	uint8_t status;
	/* pointer to list */
	struct mimap_query *qlist;
	/* pointer to last */
	struct mimap_query *qlast;
};

/* input recv buffer */
void mimap_ (struct mimap *mimap, const char *buffer, size_t bfsz);
/* query LOGIN to server */
void mimap_login (struct mimap *mimap, const char *login, const char *secret);
/* query SELECT to server, if isquery == false, then is not really query */
void mimap_select (struct mimap *mimap, const char *path, const bool isquery);
/* query APPEND to server, put message to SELECT'ed folder
 *  may be use in not really SELECT'ed folder (with isquery = false)
 * */
void mimap_append (struct mimap *mimap, const char *buffer, size_t bfsz);
void mimap_logout (struct mimap *mimap);

#endif /* _MIMAP_1356622174_H_ */

