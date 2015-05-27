
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <libss.h>
#include <libsf.h>
#include <libsr.h>
#include <libst.h>

static void
ssrq_test0(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ss_rqfree(&q, &a);
}

static void
ssrq_test1(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);

	ss_rqadd(&q, an, 1);
	ss_rqadd(&q, bn, 2);
	ss_rqadd(&q, cn, 3);
	int i = 3;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n))) {
		t( i == n->v );
		i--;
	}
	ss_rqfree(&q, &a);

	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
}

static void
ssrq_test2(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);

	ss_rqadd(&q, an, 1);
	ss_rqadd(&q, bn, 2);
	ss_rqadd(&q, cn, 3);
	ss_rqdelete(&q, cn);
	int i = 2;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n))) {
		t( i == n->v );
		i--;
	}
	ss_rqfree(&q, &a);
	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
}

static void
ssrq_test3(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);

	ss_rqadd(&q, an, 1);
	ss_rqadd(&q, bn, 2);
	ss_rqdelete(&q, bn);
	ss_rqadd(&q, cn, 3);
	int i = 3;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n))) {
		t( i == n->v );
		i = 1;
	}
	ss_rqfree(&q, &a);
	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
}

static void
ssrq_test4(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);

	ss_rqadd(&q, an, 1);
	ss_rqdelete(&q, an);
	ss_rqadd(&q, bn, 2);
	ss_rqadd(&q, cn, 3);
	int i = 3;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n))) {
		t( i == n->v );
		i--;
	}
	ss_rqfree(&q, &a);
	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
}

static void
ssrq_test5(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);

	ss_rqadd(&q, an, 1);
	ss_rqadd(&q, bn, 2);
	ss_rqadd(&q, cn, 3);
	ss_rqupdate(&q, cn, 8);
	int i = 8;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n))) {
		t( i == n->v );
		if (i == 8)
			i = 2;
		else
			i = 1;
	}
	ss_rqfree(&q, &a);
	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
}

static void
ssrq_test6(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);

	ss_rqadd(&q, an, 1);
	ss_rqadd(&q, bn, 2);
	ss_rqadd(&q, cn, 3);
	ss_rqupdate(&q, cn, 8);
	ss_rqdelete(&q, bn);
	ss_rqdelete(&q, an);
	int i = 8;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n))) {
		t( i == n->v );
		i--;
	}
	ss_rqfree(&q, &a);
	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
}

static void
ssrq_test7(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 1, 10) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);

	ss_rqadd(&q, an, 1);
	ss_rqadd(&q, bn, 2);
	ss_rqadd(&q, cn, 3);
	ss_rqdelete(&q, bn);
	ss_rqdelete(&q, cn);
	ss_rqdelete(&q, an);
	int i = 0;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n))) {
		i++;
	}
	t( i == 0 );
	ss_rqfree(&q, &a);
	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
}

static void
ssrq_test8(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);
	ssrq q;
	t( ss_rqinit(&q, &a, 10, 100) == 0 );

	ssrqnode *an = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *bn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *cn = ss_malloc(&a, sizeof(ssrqnode));
	ssrqnode *dn = ss_malloc(&a, sizeof(ssrqnode));
	t( an != NULL );
	t( bn != NULL );
	t( cn != NULL );
	t( dn != NULL );
	ss_rqinitnode(an);
	ss_rqinitnode(bn);
	ss_rqinitnode(cn);
	ss_rqinitnode(dn);

	ss_rqadd(&q, an, 0);
	ss_rqadd(&q, bn, 10);
	ss_rqadd(&q, cn, 20);
	ss_rqadd(&q, dn, 30);
	int i = 30;
	ssrqnode *n = NULL;
	while ((n = ss_rqprev(&q, n)))
		i -= 10;
	ss_rqfree(&q, &a);
	ss_free(&a, an);
	ss_free(&a, bn);
	ss_free(&a, cn);
	ss_free(&a, dn);
}

stgroup *ssrq_group(void)
{
	stgroup *group = st_group("ssrq");
	st_groupadd(group, st_test("test0", ssrq_test0));
	st_groupadd(group, st_test("test1", ssrq_test1));
	st_groupadd(group, st_test("test2", ssrq_test2));
	st_groupadd(group, st_test("test3", ssrq_test3));
	st_groupadd(group, st_test("test4", ssrq_test4));
	st_groupadd(group, st_test("test5", ssrq_test5));
	st_groupadd(group, st_test("test6", ssrq_test6));
	st_groupadd(group, st_test("test7", ssrq_test7));
	st_groupadd(group, st_test("test8", ssrq_test8));
	return group;
}
