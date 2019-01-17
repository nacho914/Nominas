-- Function: insertamovimiento(integer, integer, integer, integer, integer, date)

-- DROP FUNCTION insertamovimiento(integer, integer, integer, integer, integer, date);

CREATE OR REPLACE FUNCTION insertamovimiento(
    integer,
    integer,
    integer,
    integer,
    integer,
    date)
  RETURNS integer AS
$BODY$

  DECLARE
    iIdempleado  ALIAS FOR $1;
    iIdpuesto 	 ALIAS FOR $2;
	iIdpuestoC 	 ALIAS FOR $3;
	iIdtipo 	 ALIAS FOR $4;
	ientregas 	 ALIAS FOR $5;
	fechamov 	 ALIAS FOR $6;
		
	iDuplicados INTEGER;
	iRegresa	INTEGER;
BEGIN
 
	SELECT COUNT(*) INTO iDuplicados FROM movimientos WHERE idempleado= iIdempleado AND fechaMovimiento = fechamov;

	
	IF(iDuplicados > 0) THEN

		iRegresa = -1;
		
	ELSE
		
		INSERT INTO movimientos(idempleado,puesto,puestoCubrio,tipoempleado,cantidadEntregas,fechaMovimiento) 
		VALUES (iIdempleado,iIdpuesto,iIdpuestoC,iIdtipo,ientregas,fechamov);
		iRegresa = 1;
		
	END IF; 	
 
	RETURN iRegresa;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE;
