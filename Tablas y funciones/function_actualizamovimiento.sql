-- Function: actualizamovimiento(integer, integer, integer, integer, integer, date, integer)

-- DROP FUNCTION actualizamovimiento(integer, integer, integer, integer, integer, date, integer);

CREATE OR REPLACE FUNCTION actualizamovimiento(
    integer,
    integer,
    integer,
    integer,
    integer,
    date,
    integer)
  RETURNS integer AS
$BODY$

  DECLARE
    iIdempleado  ALIAS FOR $1;
    iIdpuesto 	 ALIAS FOR $2;
	iIdpuestoC 	 ALIAS FOR $3;
	iIdtipo 	 ALIAS FOR $4;
	ientregas 	 ALIAS FOR $5;
	fechamov 	 ALIAS FOR $6;
	idMov 	 	 ALIAS FOR $7;
		
		iRegresa	INTEGER;
		iDuplicados INTEGER;
BEGIN

	SELECT COUNT(1) INTO iDuplicados FROM movimientos WHERE idempleado= iIdempleado AND fechaMovimiento = fechamov;

	IF iDuplicados >= 1 THEN

		UPDATE movimientos SET idempleado = iIdempleado,puesto= iIdpuesto,puestoCubrio=iIdpuestoC,tipoempleado=iIdtipo,cantidadEntregas=ientregas,fechaMovimiento=fechamov
		WHERE idmovimiento = idMov;
		iRegresa = 1;
	ELSE

		iRegresa = -1;
	END IF;
	

	RETURN iRegresa;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE;
