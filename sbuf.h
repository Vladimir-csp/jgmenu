/*
 * Simple C string buffer implementatioun.
 *
 * Copyright Johan Malm 2016
 *
 * The buffer is a byte array which is at least (len + 1) bytes in size.
 * The sbuf functions are designed too maintain/add '\0' at the end,
 * allowing the buffer to be used be used as a C string
 * (i.e. buf[len] == 0).
 *
 * sbuf_init allocates one byte so that the buffer can always be safely:
 *	- assumed to be a valid C string (i.e. buf != NULL)
 *	- freed (i.e. buf must not to point to memory on the stack)
 *
 * Exampel life cycle:
 *	struct sbuf s;
 *	sbuf_init(&s);
 *	sbuf_addch(&s, 'F');
 *	sbuf_addstr(&s, "oo");
 *	printf("%s\n", s.buf);
 *	free(s.buf);
 */

#ifndef SBUF_H
#define SBUF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "util.h"

struct sbuf {
	char *buf;
	int bufsiz;
	int len;
	struct list_head list;
};

extern void sbuf_init(struct sbuf *s);
extern void sbuf_addch(struct sbuf *s, char ch);
extern void sbuf_addstr(struct sbuf *s, const char *data);
extern void sbuf_cpy(struct sbuf *s, const char *data);
extern void sbuf_prepend(struct sbuf *s, const char *data);
extern void sbuf_shift_left(struct sbuf *s, int n_bytes);
extern void sbuf_expand_tilde(struct sbuf *s);
extern void sbuf_ltrim(struct sbuf *s);
extern void sbuf_rtrim(struct sbuf *s);
extern void sbuf_trim(struct sbuf *s);
extern void sbuf_split(struct list_head *sl, const char *data, char field_separator);
extern void sbuf_list_append(struct list_head *sl, const char *data);
extern void sbuf_list_prepend(struct list_head *sl, const char *data);
extern void sbuf_list_free(struct list_head *sl);

#endif /* SBUF_H */
