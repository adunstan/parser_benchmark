
create extension drive_parser;

\set query `cat parser_test.sql`

\timing

select drive_parser(:'query', 1000);

