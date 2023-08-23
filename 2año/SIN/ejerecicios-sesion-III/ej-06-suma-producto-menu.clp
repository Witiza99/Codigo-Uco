;2.-  Programa para sumar y multiplicar los elementos de un vector


(defglobal ?*s* = 0
           ?*p* = 1
)
(deffacts datos (vector 1 2 3 4))

(defrule suma ;suma todos los elementos de un vector
  ?ob <- (objetivo sumar)
         (vector $?antes ?y $?resto)
=>
   (bind ?*s* (+ ?*s* ?y))
)

(defrule presentaSuma
         (declare (salience -10))
?ob<-    (objetivo sumar)
=>
  (printout t "Suma: " ?*s* crlf)
  (retract ?ob)
  (assert (suma ?*s*))
  (bind ?*s* 0)
  (printout t "Pulse c para continuar... " crlf)
  (read)
)


(defrule producto ;Multiplica todos los elementos de un vector haciendo uso de 
                  ;variables globales
       (objetivo producto)
       (vector $?antes ?y $?resto)
=>
   (bind ?*p* (* ?*p* ?y))
 
)
  

(defrule presentaProducto
     (declare (salience -10))
?ob<-(objetivo producto)
=>
  (printout t "Producto: " ?*p* crlf)
  (printout t "Pulse c para continuar... " crlf)
  (read)
  (retract ?ob)
  (assert (producto ?*p*))
  (bind ?*p* 1)

)

 


;3. 
; a) Crear una función sin argumentos para presentar un menú de opciones, 
; b) Crear una función cont () que seleccione una de las posibles opciones
; c) 
(deffunction menu ()
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t " "   crlf)
  (printout t "---------------------------------------"   crlf)
  (printout t "1. Suma: "   crlf)
  (printout t "2. Producto: "   crlf)
  (printout t "3. Obtener el mayor elemento: "   crlf)
  (printout t "4. Salir: "   crlf)
  (printout t "---------------------------------------"   crlf)
)

 
(deffunction cont()
  (menu)
  (printout t "¿Elija una opcion?(1 2 3 4) ")
  (bind ?r (read))
  (while (neq ?r 1 2 3) do
           (printout t "¿Elija una opcion?(1 2 3 4) ")
           (bind ?r (read))
   )
 ;(printout t ?r crlf)
  (if (eq ?r 1)
    then
     (assert (objetivo sumar))
  )
   (if (eq ?r 2)
     then 
     (assert (objetivo producto))
   )
    (if (eq ?r 3)
     then 
     (assert (objetivo mayorElemento))
   )
   (if (eq ?r 4)
     then
      (printout t "Programa finalizado" crlf)
      (printout t "==================="crlf)
      halt
   )
)

(defrule r
  (not (objetivo ?))
  =>
  (cont)
)