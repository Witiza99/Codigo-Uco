 ; Problema 1
 ;Dados varias cadenas de caracteres presentarlas 
 ;de forma ordenada
 
 (deffacts datos
  (nombre "aaz")
  (nombre "b")
  (nombre "c")
  )
  
  (defrule ordenar
   (nombre ?x)
   (not (nombre ?y&:(eq (str-compare ?y ?x) -1)))
  =>
  (printout t ?x crlf)
  )
  
 ;Problema 2   
    
REPRESENTACION INFORMACION DE PERSONAS
======================================   
(deftemplate persona
   (slot nombre)
   (slot apellidos)
   (slot dni)
   (slot ordenado)
)

(deffacts objetivos
  (objetivo presentar-personas)
 )
 
; Representamos las personas 

(deffacts personas
   (persona (nombre Juan)(apellidos Alvarez)(dni 1)(ordenado 0))
   (persona (nombre Pedro)(apellidos Martinez)(dni 2)(ordenado 0))
   (persona (nombre Juan)(apellidos Fernandez)(dni 3)(ordenado 0))
   (persona (nombre Pedro)(apellidos Valenzuela)(dni 4)(ordenado 0))
   (persona (nombre Juan)(apellidos Sanchez)(dni 5)(ordenado 0))
   (persona (nombre Pedro)(apellidos Zapata)(dni 6)(ordenado 0))
)


; REPRESENTACIÓN DEL CONOCIMIENTO
;================================

;Crear una regla para que presente los datos de las personas por pantalla ordenados alfabeticamente
(defrule presentacion
 (objetivo presentar-personas)
 ?p<- (persona (apellidos ?ap)(ordenado 0)); Liga los apellidos a la variale ?ap
 
 (not (persona (apellidos ?y&:(eq (str-compare ?ap ?y) -1)) (ordenado 0)   ))
  =>
 (printout t  ?ap crlf)
 (modify ?p (ordenado 1))
 )
 