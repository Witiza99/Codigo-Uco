;REPRESENTACIÓN DE LA INFORMACIÓN
;================================

;Definir una plantilla para representar relaciones de familiares de personas

;Primero definimos una plantilla para representar personas

(deftemplate persona
   (slot nombre)
   (slot apellidos)
   (slot dni)
   (slot ordenado)
)

; Definimos una plantilla para representar una relación familiar

(deftemplate rf
     (slot tipo)
     (slot dni-1)
     (slot dni-2)     
)

(deffacts objetivos
  (objetivo presentar-personas)
 )
 
; Representamos las personas 

(deffacts personas
   (persona (nombre Juan)(apellidos Fernandez)(dni 1)(ordenado 0))
   (persona (nombre Pedro)(apellidos Martinez)(dni 2)(ordenado 0))
   (persona (nombre Juan)(apellidos Fernandez)(dni 3)(ordenado 0))
   (persona (nombre Pedro)(apellidos Valenzuela)(dni 4)(ordenado 0))
   (persona (nombre Juan)(apellidos Sanchez)(dni 5)(ordenado 0))
   (persona (nombre Pedro)(apellidos Zapata)(dni 6)(ordenado 0))
)

;Representamos las relaciones  familiares
(deffacts relaciones
  (rf (tipo hijo_de) (dni-1 1) (dni-2 2) )
)


; REPRESENTACIÓN DEL CONOCIMIENTO
;================================


;Crear una regla para que presente los datos de las personas por pantalla ordenados alfabeticamente
(defrule presentacion
 (objetivo presentar-personas)
 ?p<- (persona (apellidos ?ap)(ordenado 0))
 (not (persona (apellidos ?y&:(eq (str-compare ?y ?ap) 1)) (ordenado 0)   ))
  =>
 (printout t  ?ap crlf)
 (modify ?p (ordenado 1))
 )
 

 ;Crear una regla para que presente los relaciones familiares de las personas por pantalla
(defrule presentacion-rf
  
  (rf (tipo ?t) (dni-1 ?dn1) (dni-2 ?dn-2) )
  
   
  (persona  (dni ?dn1) (nombre ?n1) (apellidos ?ap1)   )
  
  (persona  (dni ?dn2) (nombre ?n2) (apellidos ?ap2)   )
  (test (neq ?dn1 ?dn2))
 =>
 (printout t ?n1 " " ?ap1 "es " ?t  " de " ?n2 " " ?ap2  crlf)
 (printout t ?dn1 " " ?dn2 crlf )
 )
 

; INFERIR OTRA RELACIÓN FAMILIAR DE AQUI 
;=======================================
; SI UNA PERSONA ES HIJA DE OTRA, ESTA OTRA ES PADRE DE LA PERSONA




   