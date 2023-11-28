-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION drive_parser" to load this file. \quit

CREATE FUNCTION drive_parser(query text, count int)
RETURNS void
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT IMMUTABLE PARALLEL SAFE;

