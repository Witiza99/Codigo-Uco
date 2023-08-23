;Mayor de un conjunto de números
;===============================

(deffacts hechos-a
  (p 9) (p 1) (p 3)
  (resultado)
)

(defrule r1-mayor
?d<- (p ?x)
 (not (p ?y&:(> ?y ?x)))

=>
(printout t ?x crlf)
;(retract ?d) ;Observar lo que ocurre al quitar el comentario y explicarlo
)


;Ordenar de mayor a menor
(deffacts hechos-a
  (p 9) (p 1) (p 3)
  (resultado)
)

(defrule r2-mayor-a-menor
?d<- (p ?x)
 (not (p ?y&:(> ?y ?x)))
 ?r <- (resultado $?resto)

=>
(printout t ?x crlf)
(retract ?r)
(assert (resultado ?x $?resto))
(retract ?d) ;Observar lo que ocurre al poner el comentario
) 
 

; El mayor elemento de un vector
;===============================

(deffacts hechos-b
  (v 28 99 1 4 7 9)
)

(defrule r2
 (v $?antes ?x $?despues )
 (not   (v $?antes1 ?y&:(> ?y ?x) $?despues1)  )
=>
 (printout t ?x crlf )

)



; Reordenar los elementos  de un vector
;======================================

(deffacts hechos-b
  (v 28 1 4 7 9)
  (nv)
)

(defrule r2
 ?f1<-(v $?antes ?x $?despues )
 ?f2<-(nv $?d)
 (not   (v $?antes1 ?y&:(> ?y ?x) $?despues1)  )
=>
 (printout t ?x crlf )
 (retract ?f1 ?f2)
 (assert (v ?antes ?despues))
 (assert (nv ?x ?d))
)