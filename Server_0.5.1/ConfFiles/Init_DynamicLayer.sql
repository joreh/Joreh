DROP SCHEMA "sgis_dl" cascade;
CREATE schema "sgis_dl";

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_dl"."Team"(
id integer primary key, 
name char(30),
color char(30) default null);

ALTER TABLE "sgis_dl"."Team" OWNER TO postgres;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CREATE TABLE "sgis_dl"."Agent"(
id integer primary key, 
typeID integer ,
teamID integer ,
lat float,
lon float,
life integer,
g_pos geometry(point, 4326)
);

ALTER TABLE "sgis_dl"."Agent" OWNER TO postgres;


