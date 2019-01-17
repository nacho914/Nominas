-- Function: obtenernomina()

-- DROP FUNCTION obtenernomina();

CREATE OR REPLACE FUNCTION obtenernomina()
  RETURNS SETOF datonomina AS
$BODY$

	DECLARE
	iValorEntrega INT DEFAULT 0;
	iPorcISR   INT DEFAULT 0;
	iPorTopeISR   INT DEFAULT 0;
	iSueloTop   INT DEFAULT 0;
	iPorVale   INT DEFAULT 0;
	iSueldoBase   INT DEFAULT 0;
	iBonoDef   INT DEFAULT 0;
	iHoras   INT DEFAULT 0;
	iSueldoTotal  INT DEFAULT 0;
	iSueldo   INT DEFAULT 0;
	iIdEmp   INT DEFAULT 0;
	iBono   INT DEFAULT 0;
	iTipoempleado INT DEFAULT 0;
	iExtra   INT DEFAULT 0;
	Mov   RECORD;
	cNombre   CHAR;
	DatoNom   DatoNomina;
	BEGIN 
		
		--DatoNom := ( 0, 0, 0, 0, '', 0, '', 0 );
		SELECT valor INTO iValorEntrega FROM valores WHERE descripcion = 'VALOR ENTREGA';
		SELECT valor INTO iPorcISR FROM valores WHERE descripcion = 'PORC ISR';
		SELECT valor INTO iPorTopeISR FROM valores WHERE descripcion = 'PORC TOPE ISR';
		SELECT valor INTO iSueloTop FROM valores WHERE descripcion = 'SUELDO MAX ISR';
		SELECT valor INTO iPorVale FROM valores WHERE descripcion = 'PORC VALE';
		
		FOR iIdEmp IN 
		SELECT idempleado FROM movimientos GROUP BY idempleado ORDER BY idempleado
		LOOP
			DatoNom := ( 0, '', 0, 0, 0, 0, 0, 0);
			iSueldo = 0;
			iBono = 0;
			iExtra = 0;
			SELECT (TRIM(nombre)||' '|| trim(apellidopaterno) || ' '||TRIM(apellidoMaterno))::text AS nombre,tipoempleado INTO DatoNom.nombre, iTipoempleado FROM empleados WHERE id = iIdEmp;
			DatoNom.idempleado = iIdEmp;
			FOR mov IN
			SELECT  puesto, puestocubrio, cantidadentregas FROM movimientos WHERE idempleado = iIdEmp
			LOOP
				IF( mov.puestocubrio != 0) THEN 
				
					SELECT sueldobasehora,horasjornada,bono INTO iSueldoBase,iHoras,iBonoDef FROM rol WHERE idrol = mov.puestocubrio; 
				
				ELSE 
					
					SELECT sueldobasehora,horasjornada,bono INTO iSueldoBase,iHoras,iBonoDef FROM rol WHERE idrol = mov.puesto;
				
				END IF;

				iSueldo = iSueldo +(iSueldoBase * iHoras);
				iBono =  iBono +(iBonoDef * iHoras);
				iExtra = iExtra +( mov.cantidadentregas * iValorEntrega);
				
			END LOOP;
			
			iSueldoTotal = iSueldo+iBono+iExtra;
			DatoNom.sueldo = iSueldo;
			DatoNom.Bono = iBono;
			DatoNom.Extra = iExtra;
			
			IF iSueldoTotal > iSueloTop THEN
			
				DatoNom.isr = ((iSueldoTotal::float / 100::float)::float * iPorTopeISR);
			ELSE
				DatoNom.isr = ((iSueldoTotal::float / 100::float)::float * iPorcISR);
			END IF;
			
			IF iTipoempleado = 1 THEN
				DatoNom.vale = ((iSueldoTotal::float / 100::float)::float * iPorVale);
			ELSE
				DatoNom.vale = 0;
			END IF;
			
			DatoNom.sueldoTotal =  (iSueldoTotal+DatoNom.vale) - DatoNom.isr;
			
			RETURN  next DatoNom; 
		
		END LOOP;


		RETURN; 
	END;
$BODY$
  LANGUAGE plpgsql VOLATILE;
