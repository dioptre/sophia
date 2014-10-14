
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <libsr.h>
#include <libsv.h>
#include <libsm.h>
#include <libsl.h>
#include <libsd.h>
#include <libsi.h>
#include <libso.h>
#include <sophia.h>

static void*
so_ctl(soobj *obj, va_list args srunused)
{
	so *o = (so*)obj;
	return &o->ctl;
}

static int
so_open(soobj *o, va_list args)
{
	so *e = (so*)o;
	if (so_active(e))
		return -1;
	so_statusset(&e->status, SO_RECOVER);
	srlist *i, *n;
	sr_listforeach_safe(&e->db.list, i, n) {
		soobj *o = srcast(i, soobj, link);
		int rc = o->i->open(o, args);
		if (srunlikely(rc == -1))
			return -1;
	}
	so_statusset(&e->status, SO_ONLINE);
	return 0;
}

static int
so_destroy(soobj *o)
{
	so *e = (so*)o;
	int rcret = 0;
	int rc;
	so_statusset(&e->status, SO_SHUTDOWN);
	srlist *i, *n;
	sr_listforeach_safe(&e->db.list, i, n) {
		soobj *o = srcast(i, soobj, link);
		rc = so_objdestroy(o);
		if (srunlikely(rc == -1))
			rcret = -1;
	}
	/* destroy */
	so_objindex_free(&e->ctlcursor);
	so_objindex_free(&e->db);
	sr_mutexfree(&e->apilock);
	sr_seqfree(&e->seq);
	free(e);
	return rcret;
}

static void*
so_type(soobj *o srunused, va_list args srunused) {
	return "env";
}

static soobjif soif =
{
	.ctl      = so_ctl,
	.open     = so_open,
	.destroy  = so_destroy,
	.error    = NULL,
	.set      = NULL,
	.get      = NULL,
	.del      = NULL,
	.begin    = NULL,
	.commit   = NULL,
	.rollback = NULL,
	.cursor   = NULL,
	.object   = NULL,
	.type     = so_type,
	.copy     = NULL
};

soobj *so_new(void)
{
	so *e = malloc(sizeof(*e));
	if (srunlikely(e == NULL))
		return NULL;
	memset(e, 0, sizeof(*e));
	so_statusset(&e->status, SO_OFFLINE);
	so_objinit(&e->o, SOENV, &soif, &e->o /* self */);
	so_ctlinit(&e->ctl, e);
	so_objindex_init(&e->db);
	so_objindex_init(&e->ctlcursor);
	sr_mutexinit(&e->apilock);
	sr_seqinit(&e->seq);
	sr_allocinit(&e->a, sr_allocstd, NULL);
	sr_errorinit(&e->error);
	sr_init(&e->r, &e->error, &e->a, &e->seq, NULL, NULL);
	return &e->o;
}