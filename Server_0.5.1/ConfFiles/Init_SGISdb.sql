-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

DROP SCHEMA if exists "sgis_common" cascade;
CREATE Schema "sgis_common";

DROP SCHEMA if exists "sgis_ms" cascade;
CREATE Schema "sgis_ms";

DROP SCHEMA if exists "sgis_dl" cascade;
CREATE schema "sgis_dl";

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_common".groundType(
  id integer,
  name varchar(255),
  color varchar(255)
);

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_dl"."Team"(
id integer primary key,
name varchar(255),
color varchar(255) default null);

ALTER TABLE "sgis_dl"."Team" OWNER TO mehrab;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_dl"."Agent"(
id integer primary key,
typeID integer ,
teamID integer ,
lat float,
lon float,
life integer,
startView float,
endView float,
g_pos geometry(point, 4326)
);

ALTER TABLE "sgis_dl"."Agent" OWNER TO mehrab;




-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_common"."AgentType"(
id integer primary key,
name char(30),
color char(30) default null,
description character varying default null);

ALTER TABLE "sgis_common"."AgentType" OWNER TO mehrab;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_ms"."ground"(
id integer primary key,
gtype character varying(80),
geom geometry(POLYGON, 4326));

ALTER TABLE "sgis_ms"."ground" OWNER TO mehrab;


-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_ms"."raster"(
id integer primary key,
rasterFile character varying(200));

ALTER TABLE "sgis_ms"."raster" OWNER TO mehrab;



-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE OR REPLACE FUNCTION "sgis_common"."F_IsExistsSchema"(character varying)
  RETURNS bigint AS
$$
select (select count(*) from information_schema.schemata where schema_name = $1)
 as resault

$$
LANGUAGE sql VOLATILE;
ALTER FUNCTION "sgis_common"."F_IsExistsSchema"(character varying) OWNER TO mehrab;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--CREATE OR REPLACE FUNCTION "sgis_common"."F_GetSGISTables"()
--  RETURNS boolean AS
--$$ begin

--select (select count(*) from information_schema.schemata where schema_name = $1)
-- as resault

--end; $$
--LANGUAGE sql VOLATILE
--ALTER FUNCTION "sgis_common"."F_GetSGISTables"() OWNER TO postgres;



-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE OR REPLACE FUNCTION "sgis_common"."F_IsExistsTable"(character varying, character varying)
RETURNS boolean AS
$$ begin
        IF  EXISTS(SELECT * FROM information_schema.tables WHERE (table_schema = $1 AND table_name = $2))
        THEN
                RETURN 't';
        ELSE
                RETURN 'f';
        END IF;
end; $$
LANGUAGE 'plpgsql';
ALTER FUNCTION "sgis_common"."F_IsExistsTable"(character varying, character varying) OWNER TO postgres;


-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE OR REPLACE FUNCTION "sgis_common"."F_AgentInsert"(integer, integer, integer, double precision, double precision, integer, double precision, double precision)
RETURNS integer AS
$$
    INSERT INTO "sgis_dl"."Agent" VALUES($1, $2, $3, $4, $5, $6, $7, $8, st_setsrid(st_point($4, $5),4326));
    SELECT 1 AS RESULT;
$$
LANGUAGE SQL;
ALTER FUNCTION "sgis_common"."F_AgentInsert"(integer, integer, integer, double precision, double precision, integer, double precision, double precision) OWNER TO postgres;


-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE OR REPLACE FUNCTION "sgis_common"."F_UpdateAgentPos"(integer, double precision, double precision, double precision, double precision, double precision)
RETURNS integer AS
$$
    UPDATE "sgis_dl"."Agent" SET g_pos = st_setsrid(st_point($2, $3),4326), lat = $2, lon = $3, startView = $5, endView = $6, life = $4 where id = $1;
    SELECT 1 AS RESULT;
$$
LANGUAGE SQL;
ALTER FUNCTION "sgis_common"."F_UpdateAgentPos"(integer, double precision, double precision, double precision, double precision, double precision) OWNER TO postgres;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE OR REPLACE FUNCTION "sgis_common"."F_GetAgentsGroundType"()
RETURNS TABLE(a integer, b character varying)
AS
$$
    SELECT a.id, g.gtype from sgis_ms.ground g, sgis_dl."Agent" a
    where st_containsproperly(g.geom, a.g_pos) order by a.id;
$$
LANGUAGE 'sql' VOLATILE;
ALTER FUNCTION "sgis_common"."F_GetAgentsGroundType"() OWNER TO postgres;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE OR REPLACE FUNCTION "sgis_common"."F_IsObservable"(int, int, double precision, character varying)
RETURNS boolean
AS
$$
    select count(*) = 0 from (select  a.id, b.id
    from sgis_dl."Agent" a, sgis_dl."Agent" b, sgis_ms.ground c
    where a.id = $1
    and b.id = $2
    and c.gType = $4
    and ((st_DWithin(a.g_pos, b.g_pos, $3) = 't' and st_disjoint(st_makeline(a.g_pos, b.g_pos), c.geom) = 'f')
    or st_DWithin(a.g_pos, b.g_pos, $3) = 'f')
    )as resault;

$$
LANGUAGE 'sql' VOLATILE;
ALTER FUNCTION "sgis_common"."F_IsObservable"(int, int, double precision, character varying) OWNER TO postgres;


-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE OR REPLACE FUNCTION "sgis_common"."F_GetAgentsView"(double precision)
RETURNS TABLE(a integer, b integer)
AS
$$
    SELECT a.id, b.id from sgis_dl."Agent" a, sgis_dl."Agent" b
    where st_DWithin(a.g_pos, b.g_pos, $1) and a.id <> b.id
    and st_azimuth(a.g_pos, b.g_pos) >= a.startView
    and st_azimuth(a.g_pos, b.g_pos) <= a.endView
    and "sgis_common"."F_IsObservable"(a.id, b.id, $1, '5')
    order by a.id;
$$
LANGUAGE 'sql' VOLATILE;
ALTER FUNCTION "sgis_common"."F_GetAgentsView"(double precision) OWNER TO postgres;




