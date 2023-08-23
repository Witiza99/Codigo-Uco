;EJERCICIOS DE CLASE
;SUMAR LOS ELEMENTOS DE UN  VECTOR

; Conocimientos necesarios:
; Variables globales, control del razonamiento, la función bind, etc.
; El alumno deberá consultar el libro para estudiar las funciones y órdenes que 
; aparecen en el programa.

; Cuestiones importantes a comprender:
; - Cómo es el ciclo de ejecución que realiza el motor de inferencia
; - Cómo se realiza la comparación de patrones: Comodines y variables
; - Qué hay que representar mediante hechos y variables globales:
;   Información: vector y suma
;   Objetivos: para el control del razonamiento
; - Cómo controlar el razonamiento: 
;      prioridades de las reglas
;      patrones relacionados con la tarea a realizar


;EJEMPLOS DE USO DE VARIABLES GLOBALES, COMODINES MULTICAMPO Y 
;CONTROL DE RAZONAMIENTO MEDIANTE PATRONES EN RELACIÓN
;CON EL OBJETIVO A ALCANZAR

;***************************************************************
;                 PRINCIPIO DE RESOLUCIÓN
;                 =======================
;La tarea de sumar los elementos del vector la dividimos en dos subtareas:
; 1.- Sumamos los elementos del vector y le asociamos el valor de la suma a 
;     una variable global.
; 2.- Presentamos el resultado de la suma 
; Para que primero se realice la suma controlamos el razonamiento mediante prioridades de
; las reglas. Teniendo menor prioridad la regla de presentación.
; La tarea de la suma s realiza mediante una regla que incluye un patrón con comodines multicampo
; y una variable. Esto hará que cada vez que se aplique la regla se utilizará un valor del vector
; Se ha utilizado también un patrón para controlar que estamos en la tarea suma.
;***************************************************************

; La información ha quedado representada mediante una variable global y un hecho ordenado
; Para controlar el razonamiento nos ayudamos de un hecho ordenado (objetivo sumar) que
; deberá emparejar con el E.C. patrón  de las reglas que conforman estas tareas.


;VARIABLES GLOBALES
(defglobal ?*s* = 0 )

;HECHOS INICIALES
(deffacts vectores
  (v 1 2 3 4 5)
  (objetivo sumar)
)

(defrule sumar  
  (objetivo sumar)
  (v $?antes ?x $?despues) ;Ejemplo de comodines multicampo
 =>
   (bind ?*s*  (+ ?*s* ?x) );Asignar o ligar  un valor a una variable global
)

(defrule presentaSuma
         (declare (salience -10)) ;Control del razonamiento mediante prioridades
?ob<-    (objetivo sumar)
=>
  (printout t "Suma: " ?*s* crlf)
  (retract ?ob)
  (assert (suma ?*s*))
  (bind ?*s* 0)
  
)

;***************************************************************

;HECHOS INICIALES
(deffacts vectores
  (v 1 2 3 4 5)
  (suma 0)
  ;(objetivo sumar)
)
 

(defrule r1
  ?f1 <- (v  ?x $?despues)
  ?f2 <- (suma ?s)
  =>
  (retract ?f2)
  (retract ?f1)
  (assert (suma (+ ?s ?x)))
  (assert (v ?despues))
 )
 

 