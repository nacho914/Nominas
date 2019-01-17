CREATE TABLE empleados
(
  id serial,
  nombre text,
  apellidopaterno text,
  apellidomaterno text,
  puesto integer,
  tipoempleado integer,
  status integer default 1,
  CONSTRAINT empleados_pkey PRIMARY KEY (id)
);