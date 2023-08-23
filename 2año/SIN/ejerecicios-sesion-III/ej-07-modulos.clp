(defmodule MAIN (export ?ALL))

(deftemplate MAIN::persona
(slot nombre)
(slot apellido)
(slot dni))

(deffacts datos
(persona (nombre gabriel) (apellido garcia) (dni 1))
(persona (nombre jose) (apellido garcia) (dni 2))
(persona (nombre carlos) (apellido garcia) (dni 3))
(persona (nombre juan) (apellido ruiz) (dni 4))
(persona (nombre francisco) (apellido ruiz) (dni 5))
(persona (nombre tomas) (apellido ruiz) (dni 6)))

(deftemplate MAIN::info
(slot dni1)
(slot dni2)
(slot relacion))

(deffacts relaciones
(info (dni1 1) (dni2 2) (relacion padre-hijo))
(info (dni1 2) (dni2 3) (relacion padre-hijo))
(info (dni1 4) (dni2 5) (relacion padre-hijo))
(info (dni1 5) (dni2 6) (relacion padre-hijo)))

(defrule MAIN::foco
=>
(focus A B C))

(defrule MAIN::fin
(declare (salience -10))
(objetivo fin)
=>
(printout t "Fin del programa" crlf))

(defmodule A (import MAIN deftemplate info)
	     (import MAIN deftemplate persona)
	     (export ?ALL))

(defrule A::nietos
(info (dni1 ?z) (dni2 ?x) (relacion padre-hijo))
(info (dni1 ?x) (dni2 ?y) (relacion padre-hijo))
=>
(assert (es-nieto dni1 ?y dni2 ?z)))

(defmodule B (export ?ALL)
	     (import MAIN deftemplate persona)
	     (import MAIN deftemplate info))

(defrule B::abuelos
(info (dni1 ?z) (dni2 ?x) (relacion padre-hijo))
(info (dni1 ?y) (dni2 ?z) (relacion padre-hijo))
=>
(assert (es-abuelo dni1 ?y dni2 ?x)))

(defmodule C (export ?ALL)
	     (import MAIN ?ALL)
	     (import A ?ALL)
	     (import B ?ALL))

(defrule C::mensaje
(declare (salience 10))
=>
(printout t "---Lista de nietos---" crlf))

(defrule C::lista
(es-nieto dni1 ?x dni2 ?)
(persona (nombre ?a) (apellido ?b) (dni ?x))
=>
(printout t "Nombre: " ?a " " "Apellido: " ?b " " "DNI: " ?x crlf)
(assert (objetivo fin))
)

