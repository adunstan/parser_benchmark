/*

build this into a Postgres shared library, then

create function drive_parser(query text, count int) returns void
strict volatile language c as '.../drive_parser.so';

\timing

select drive_parser('some-query', 1000);

 */

#include "postgres.h"

#include "fmgr.h"
#include "miscadmin.h"
#include "tcop/tcopprot.h"
#include "utils/builtins.h"
#include "utils/memutils.h"

PG_MODULE_MAGIC;

/* missing in 9.2 and earlier */
#ifndef ALLOCSET_DEFAULT_SIZES
#define ALLOCSET_DEFAULT_SIZES \
   ALLOCSET_DEFAULT_MINSIZE, ALLOCSET_DEFAULT_INITSIZE, ALLOCSET_DEFAULT_MAXSIZE
#endif


/*
 * drive_parser(query text, count int) returns void
 */
PG_FUNCTION_INFO_V1(drive_parser);
Datum
drive_parser(PG_FUNCTION_ARGS)
{
	text	   *txt = PG_GETARG_TEXT_PP(0);
	int32		count = PG_GETARG_INT32(1);
	char	   *query_string = text_to_cstring(txt);
	MemoryContext mycontext;

	mycontext = AllocSetContextCreate(CurrentMemoryContext,
									  "drive_parser work cxt",
									  ALLOCSET_DEFAULT_SIZES);

	while (count-- > 0)
	{
		List	   *parsetree_list;
		MemoryContext oldcontext;

		oldcontext = MemoryContextSwitchTo(mycontext);

		/* This times raw parsing only */
		parsetree_list = pg_parse_query(query_string);

		MemoryContextSwitchTo(oldcontext);

		MemoryContextReset(mycontext);

		CHECK_FOR_INTERRUPTS();
	}

	PG_RETURN_VOID();
}
