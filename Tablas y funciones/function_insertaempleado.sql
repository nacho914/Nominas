-- Function: insertaempleado(character, character, character, integer, integer)

-- DROP FUNCTION insertaempleado(character, character, character, integer, integer);

CREATE OR REPLACE FUNCTION insertaempleado(
    character,
    character,
    character,
    integer,
    integer)
  RETURNS integer AS
$BODY$

  DECLARE
        cNombre  ALIAS FOR $1;
        cPaterno ALIAS FOR $2;
		cMaterno ALIAS FOR $3;
		iRol 	 ALIAS FOR $4;
		iTipo 	 ALIAS FOR $5;
		
		iDuplicados INTEGER;
		iRegresa	INTEGER;
BEGIN
 
	SELECT COUNT(1) INTO iDuplicados FROM empleados WHERE nombre = cNombre AND apellidopaterno = cPaterno AND apellidomaterno=cMaterno;
	
	IF(iDuplicados = 0) THEN

		INSERT INTO empleados(nombre,apellidopaterno,apellidomaterno,puesto,tipoempleado) VALUES (cNombre,cPaterno,cMaterno,iRol,iTipo);

		SELECT id into iRegresa FROM empleados WHERE nombre = cNombre AND apellidopaterno=cPaterno AND  apellidomaterno = cMaterno;
		
	ELSE
		iRegresa = -1;
	END IF; 	
 
	RETURN iRegresa;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE;
