CREATE TABLE movimientos
(
  idmovimiento serial,
  idempleado integer,
  puesto integer,
  puestocubrio integer,
  tipoempleado integer,
  cantidadentregas integer,
  fechamovimiento date,
  fechamovto timestamp without time zone DEFAULT now(),
  CONSTRAINT movimientos_pkey PRIMARY KEY (idmovimiento)
);