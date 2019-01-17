-- Function: actualizaempleado(character, character, character, integer, integer, integer)

-- DROP FUNCTION actualizaempleado(character, character, character, integer, integer, integer);

CREATE OR REPLACE FUNCTION actualizaempleado(
    character,
    character,
    character,
    integer,
    integer,
    integer)
  RETURNS integer AS
$BODY$

  DECLARE
		cNombre  	ALIAS FOR $1;
		cPaterno 	ALIAS FOR $2;
		cMaterno 	ALIAS FOR $3;
		iRol 	 	ALIAS FOR $4;
		iTipo 	 	ALIAS FOR $5;
		iIdEmpleado ALIAS FOR $6;
		
		iRegresa	INTEGER;
		iDuplicados	INTEGER;
BEGIN

	SELECT COUNT(1) INTO iDuplicados FROM empleados WHERE nombre = cNombre AND apellidopaterno = cPaterno AND apellidomaterno=cMaterno;

	if iDuplicados > 1 THEN
		iRegresa = -1;
	ELSE
		UPDATE empleados SET nombre = cNombre,apellidopaterno = cPaterno,apellidomaterno=cMaterno,puesto=iRol,tipoempleado=iTipo WHERE id = iIdEmpleado;
		iRegresa = 1;
	END IF;
		
	RETURN iRegresa;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE;