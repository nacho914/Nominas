INSERT INTO VALORES(descripcion, valor) values('VALOR ENTREGA',5);
INSERT INTO VALORES(descripcion, valor) values('PORC ISR',9);
INSERT INTO VALORES(descripcion, valor) values('PORC TOPE ISR',12);
INSERT INTO VALORES(descripcion, valor) values('SUELDO MAX ISR',16000);
INSERT INTO VALORES(descripcion, valor) values('PORC VALE',4);

INSERT INTO tipo(idtipo,descripcion) values(1,'INTERNO');
INSERT INTO tipo(idtipo,descripcion) values(2,'EXTERNO');


INSERT INTO rol(idrol,descripcion,sueldobasehora,horasjornada,bono) values(1,'CHOFER',30,8,10); 
INSERT INTO rol(idrol,descripcion,sueldobasehora,horasjornada,bono) values(2,'CARGADOR',30,8,5); 
INSERT INTO rol(idrol,descripcion,sueldobasehora,horasjornada,bono) values(3,'AUXILIARES',30,8,0); 

INSERT INTO password VALUES('PASSWORD');