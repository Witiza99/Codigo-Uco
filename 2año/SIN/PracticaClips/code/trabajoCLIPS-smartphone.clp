;Antonio Gómez Giménez 32730338G
;Alejandro Jesús Gaviño Belenguer 45382283V

;Modulo MAIN

;definimos modulo
(defmodule MAIN (export ?ALL))

;plantilla de los smartphone
(deftemplate MAIN::smartphone
	(slot id (type NUMBER))
	(slot modelo (type STRING))
	(slot marca (type STRING))
	(slot amperios (type INTEGER))
	(slot pulgadas (type FLOAT) (range 2.0 8.0))
	(slot precio (type FLOAT))
	(slot peso (type INTEGER))
	(slot camaraTrasera (type INTEGER))
	(slot camaraFrontal (type INTEGER))
	(slot S.O. (type STRING))
	(slot procesador (type STRING))
	(slot grafica (type STRING))
	(slot cargaRapida (type LEXEME))
	(slot bluetooth (type FLOAT))
	(slot USB (type STRING) (default "micro USB 2.0"))
	(slot almacenamiento (type INTEGER))
	(slot RAM (type INTEGER))
	(slot contador (type INTEGER))
)

;definimos la plantilla caracteristica-deseada
(deftemplate MAIN::caracteristica-deseada
	(slot nombre)
	(slot valor)
	(multislot marcado)
)

;defino todos los smartphone disponibles que tenemos
(deffacts MAIN::stock-moviles
    	(smartphone (id 1)(modelo "black shark 2")(marca "xiaomi")(amperios 4000)(pulgadas 6.39)(precio 467.64)(peso 205)(camaraTrasera 20)(camaraFrontal 20)(S.O. "android")(procesador "qualcomm snapdragon 885")(grafica "adreno 640")(cargaRapida "SI")(bluetooth 5.0)(USB "type-C")(almacenamiento 256)(RAM 12)(contador 0))
    	(smartphone (id 2)(modelo "iphone xs max")(marca "apple")(amperios 3174)(pulgadas 6.5)(precio 1314.79)(peso 208)(camaraTrasera 12)(camaraFrontal 7)(S.O. "ios")(procesador "apple k1")(grafica "apple gpu")(cargaRapida "SI")(bluetooth 5.0)(USB "lightning")(almacenamiento 512)(RAM 4)(contador 0))
    	(smartphone (id 3)(modelo "galaxy s10 plus")(marca "samsung")(amperios 4100)(pulgadas 6.4)(precio 885.0)(peso 175)(camaraTrasera 12)(camaraFrontal 10)(S.O. "android")(procesador "exynos 9820")(grafica "arm mali-g76 mp12")(cargaRapida "SI")(bluetooth 5.0)(USB "type-C")(almacenamiento 1000)(RAM 12)(contador 0))
    	(smartphone (id 4)(modelo "p30 pro")(marca "huawei")(amperios 4200)(pulgadas 6.47)(precio 948.99)(peso 192)(camaraTrasera 40)(camaraFrontal 32)(S.O. "android")(procesador "kirin 980")(grafica "arm mali-g76")(cargaRapida "SI")(bluetooth 5.0)(USB "type-C")(almacenamiento 512)(RAM 8)(contador 0))
    	(smartphone (id 5)(modelo "xperia xz3")(marca "sony")(amperios 3330)(pulgadas 6.0)(precio 798.76)(peso 193)(camaraTrasera 19)(camaraFrontal 13)(S.O. "android")(procesador "qualcomm snapdragon 845")(grafica "adreno 630")(cargaRapida "SI")(bluetooth 5.0)(USB "type-C")(almacenamiento 64)(RAM 4)(contador 0))
    	(smartphone (id 6)(modelo "v40 thinq")(marca "lg")(amperios 3300)(pulgadas 6.4)(precio 569.0)(peso 169)(camaraTrasera 12)(camaraFrontal 8)(S.O. "android")(procesador "qualcomm snapdragon 845")(grafica "adreno 630")(cargaRapida "SI")(bluetooth 5.0)(USB "type-C")(almacenamiento 128)(RAM 6)(contador 0))
    	(smartphone (id 7)(modelo "redmi go")(marca "xiaomi")(amperios 3000)(pulgadas 5.0)(precio 61.96)(peso 150)(camaraTrasera 8)(camaraFrontal 5)(S.O. "android")(procesador "qualcomm snapdragon 425")(grafica "adreno 308")(cargaRapida "NO")(bluetooth 4.1)(USB "micro")(almacenamiento 8)(RAM 1)(contador 0))
    	(smartphone (id 8)(modelo "iphone 5")(marca "apple")(amperios 1440)(pulgadas 4.0)(precio 164.0)(peso 149)(camaraTrasera 8)(camaraFrontal 1)(S.O. "ios")(procesador "apple a6")(grafica "apple graphics")(cargaRapida "NO")(bluetooth 4.0)(USB "lightning")(almacenamiento 16)(RAM 1)(contador 0))
    	(smartphone (id 9)(modelo "galaxy s2")(marca "samsung")(amperios 1650)(pulgadas 4.27)(precio 247.91)(peso 194)(camaraTrasera 8)(camaraFrontal 2)(S.O. "android")(procesador "exynos 4 dual")(grafica "samsung graphics")(cargaRapida "NO")(bluetooth 3.0)(USB "mini")(almacenamiento 16)(RAM 1)(contador 0))
    	(smartphone (id 10)(modelo "y6")(marca "huawei")(amperios 2200)(pulgadas 5.0)(precio 108.0)(peso 155)(camaraTrasera 8)(camaraFrontal 2)(S.O. "android")(procesador "qualcomm snapdragon 210")(grafica "adreno 304")(cargaRapida "NO")(bluetooth 4.1)(USB "micro")(almacenamiento 8)(RAM 1)(contador 0))
    	(smartphone (id 11)(modelo "xperia v")(marca "sony")(amperios 1750)(pulgadas 4.3)(precio 29.66)(peso 120)(camaraTrasera 8)(camaraFrontal 2)(S.O. "android")(procesador "qualcomm snapdragon s4 plus")(grafica "adreno 225")(cargaRapida "NO")(bluetooth 4.1)(USB "mini")(almacenamiento 8)(RAM 1)(contador 0))
    	(smartphone (id 12)(modelo "g flex")(marca "lg")(amperios 3500)(pulgadas 6.0)(precio 106.82)(peso 177)(camaraTrasera 13)(camaraFrontal 2)(S.O. "android")(procesador "qualcomm snapdragon 800")(grafica "adreno 330")(cargaRapida "NO")(bluetooth 4.0)(USB "micro")(almacenamiento 32)(RAM 2)(contador 0))
    	(smartphone (id 13)(modelo "redmi note 5a")(marca "xiaomi")(amperios 3080)(pulgadas 5.5)(precio 81.89)(peso 153)(camaraTrasera 13)(camaraFrontal 16)(S.O. "android")(procesador "qualcomm snapdragon 435")(grafica "adreno 308")(cargaRapida "NO")(bluetooth 4.2)(USB "micro")(almacenamiento 64)(RAM 4)(contador 0))
    	(smartphone (id 14)(modelo "iphone 6s")(marca "apple")(amperios 1715)(pulgadas 4.7)(precio 208.49)(peso 143)(camaraTrasera 12)(camaraFrontal 5)(S.O. "ios")(procesador "apple a9")(grafica "powervr gt7600")(cargaRapida "NO")(bluetooth 4.2)(USB "lightning")(almacenamiento 128)(RAM 2)(contador 0))
    	(smartphone (id 15)(modelo "galaxy j")(marca "samsung")(amperios 2600)(pulgadas 5.0)(precio 174.99)(peso 146)(camaraTrasera 13)(camaraFrontal 2)(S.O. "android")(procesador "qualcomm snapdragon 800")(grafica "adreno 330" )(cargaRapida "NO")(bluetooth 4.0)(USB "micro")(almacenamiento 16)(RAM 3)(contador 0))
    	(smartphone (id 16)(modelo "nova")(marca "huawei")(amperios 3020)(pulgadas 5.0)(precio 109.49)(peso 146)(camaraTrasera 12)(camaraFrontal 8)(S.O. "android")(procesador "qualcomm snapdragon 625")(grafica "adreno 506")(cargaRapida "SI")(bluetooth 4.0)(USB "type-C")(almacenamiento 32)(RAM 3)(contador 0))
    	(smartphone (id 17)(modelo "xperia z")(marca "sony")(amperios 2330)(pulgadas 5.0)(precio 156.01)(peso 146)(camaraTrasera 13)(camaraFrontal 2)(S.O. "android")(procesador "qualcomm snapdragon s4 pro")(grafica "adreno 320")(cargaRapida "NO")(bluetooth 4.0)(USB "micro")(almacenamiento 16)(RAM 2)(contador 0))
    	(smartphone (id 18)(modelo "leon")(marca "lg")(amperios 1900)(pulgadas 4.5)(precio 138.82)(peso 140)(camaraTrasera 5)(camaraFrontal 1)(S.O. "android")(procesador "qualcomm snapdragon 400")(grafica "adreno 305")(cargaRapida "NO")(bluetooth 4.0)(USB "micro")(almacenamiento 8)(RAM 1)(contador 0))
    	(smartphone (id 19)(modelo "mi mix 3")(marca "xiaomi")(amperios 3200)(pulgadas 6.39)(precio 436.99)(peso 218)(camaraTrasera 12)(camaraFrontal 24)(S.O. "android")(procesador "qualcomm snapdragon 845")(grafica "adreno 630")(cargaRapida "SI")(bluetooth 5.0)(USB "type-C")(almacenamiento 256)(RAM 8)(contador 0))
    	(smartphone (id 20)(modelo "iphone se")(marca "apple")(amperios 1642)(pulgadas 4.0)(precio 202.0)(peso 113)(camaraTrasera 12)(camaraFrontal 1)(S.O. "ios")(procesador "apple a9")(grafica "powervr gt7600")(cargaRapida "NO")(bluetooth 4.2)(USB "lightning")(almacenamiento 64)(RAM 2)(contador 0))
    	(smartphone (id 21)(modelo "galaxy m30")(marca "samsung")(amperios 5000)(pulgadas 6.4)(precio 229.0)(peso 175)(camaraTrasera 13)(camaraFrontal 16)(S.O. "android")(procesador "exynos 7904")(grafica "arm mali-g71mp2")(cargaRapida "NO")(bluetooth 5.0)(USB "type-C")(almacenamiento 128)(RAM 6)(contador 0))
    	(smartphone (id 22)(modelo "ascend g7")(marca "huawei")(amperios 3000)(pulgadas 5.5)(precio 245.27)(peso 165)(camaraTrasera 13)(camaraFrontal 5)(S.O. "android")(procesador "qualcomm snapdragon 410")(grafica "huawei graphics")(cargaRapida "NO")(bluetooth 4.0)(USB "micro")(almacenamiento 16)(RAM 2)(contador 0))
    	(smartphone (id 23)(modelo "xperia z3")(marca "sony")(amperios 3100)(pulgadas 5.2)(precio 156.01)(peso 152)(camaraTrasera 21)(camaraFrontal 2)(S.O. "android")(procesador "qualcomm snapdragon 801")(grafica "adreno 330")(cargaRapida "NO")(bluetooth 4.0)(USB "micro")(almacenamiento 16)(RAM 3)(contador 0))
  	 (smartphone (id 24)(modelo "k4")(marca "lg")(amperios 1940)(pulgadas 4.5)(precio 100.43)(peso 120)(camaraTrasera 5)(camaraFrontal 2)(S.O. "android")(procesador "mediatek 6735")(grafica "arm mali t720 mp2")(cargaRapida "NO")(bluetooth 4.1)(USB "micro")(almacenamiento 8)(RAM 1)(contador 0))
    	(smartphone (id 25)(modelo "mi a2")(marca "xiaomi")(amperios 3010)(pulgadas 5.99)(precio 156.39)(peso 168)(camaraTrasera 12)(camaraFrontal 20)(S.O. "android")(procesador "qualcomm snapdragon 660")(grafica "adreno 512")(cargaRapida "SI")(bluetooth 5.0)(USB "type-C")(almacenamiento 128)(RAM 6)(contador 0))
)

)

;defino reglas

;regla de inicio, pasa el focus al menu
(defrule MAIN::inicio    
	=>
	(printout t "Iniciando el programa" crlf)
	(focus MENU)
	(return)
)

;==============================================================================================================================================================================================

;Modulo SALIDA

;definimos el mÃ³dulo salida
(defmodule SALIDA (import MAIN ?ALL)
    	(export ?ALL))

;reglas

;regla de fin, para salir del programa
(defrule SALIDA::fin
    =>
    (assert (puesta_cero))
    (printout t "Saliendo el programa..." crlf)
)

;puesta a 0, evitamos que se queden los contadores con > de 0 por si quiere hacer reset
(defrule SALIDA::todo_a_cero
    (puesta_cero)
    ?p<-(smartphone (contador ?x&:(neq ?x 0)))
    =>
    (modify ?p (contador 0))
)


;==============================================================================================================================================================================================

;Modulo MENU

;definimos el módulo menu
(defmodule MENU (import MAIN ?ALL)
    	(export ?ALL))

;reglas

;regla que lanza el menu y pasa el focus a la logica
(defrule lanzador_menu (initial-fact)=>
(printout t "---------------------------------------"   crlf)
(printout t "Introduce la marca deseada(apple, xiaomi, huawei, sony, samsung, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre marca) (valor ?r)))
  )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce los miliamperios deseados(entre 1000 y 6000, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre amperios) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce las pulgadas deseadas(entre 3.5 y 7.0 pulgadas, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre pulgadas) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce el precio deseado(entre 10 hasta 2000, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre precio) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce el peso deseado(entre 100 y 300 gramos, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre peso) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce la calidad de la camaraTrasera deseada(entre 1 y 30, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre camaraTrasera) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce la calidad de la camaraFrontal deseada(entre 1 y 30, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre camaraFrontal) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce el S.O. deseado(android o ios, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre S.O.) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce el procesador deseado(qualcomm snapdragon 885,qualcomm snapdragon s4 pro,qualcomm snapdragon 625, etc, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre procesador) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce la gráfica deseado(arm mali-g71mp2,apple gpu, powervr gt7600, etc, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre grafica) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce si se quiere carga rápida o no(SI o NO, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre cargaRapida) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce el bluetooth deseado(desde 3.0, 4.0, etc, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre bluetooth) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce tipo de USB deseado (mini, micro, type-C o 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre USB) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce el almacenamiento deseado (entre 6 y 64 GB, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre almacenamiento) (valor ?r)))
 )
(printout t "---------------------------------------"   crlf)
(printout t "Introduce la RAM deseada (entre 1 y 6 GB, 0 si no desea rellenar este campo): "   crlf)
(bind ?r (read))
(if (neq ?r 0)
	then
 	(assert (caracteristica-deseada (nombre RAM) (valor ?r)))
 )

 (focus LOGICA)
 (return)
)


;==============================================================================================================================================================================================

;Modulo MOSTRAR

;definimos modulo
(defmodule MOSTRAR (import MAIN ?ALL)
    	(export ?ALL))

;reglas del modulo mostrar

;regla que muestra el o los smartphone con mayor contador
(defrule MOSTRAR::mostrar_smartphone
	
	?p<- (smartphone(modelo ?mod)(marca ?mar)(amperios ?amp)(pulgadas ?pul)(precio ?pre)(peso ?pes)(camaraTrasera ?camT)(camaraFrontal ?camF)(S.O. ?so)(procesador ?pro)(grafica ?gra)(cargaRapida ?car)(bluetooth ?blu)(USB ?usb)(almacenamiento ?alm)(RAM ?ram)(contador ?con))
	(not (smartphone(contador ?y&:(> ?y ?con))))
	=>
	 (printout t "El smartphone sería el modelo "?mod" de la marca "?mar" con "?pul" pulgadas y "?amp"miliamperios, siendo su peso "?pes". El precio del smartphone sería "?pre" euros y los megapixeles de su camara trasera y delantera serían "?camT " y " ?camF" megapixeles respectivamente, el procesador es "?pro", su gráfica "?gra", respecto a la carga rápida "?car" tiene, su bluetooth es "?blu",su usb es "?usb" su almacenamiento "?alm" y por ultimo su RAM es "?ram"Gb." crlf)
)

;regla que pasa el focus a la salida
(defrule MOSTRAR::cambiar_modulo_SALIDA
	(declare (salience -26))
	=>
	(focus SALIDA)
	(return)
)
	



;==============================================================================================================================================================================================


;Modulo LOGICA

;definimos modulo
(defmodule LOGICA (import MAIN ?ALL)
    	(export ?ALL))

;definimos reglas

;regla para cambiar el focus al modulo mostrar
(defrule LOGICA::fin-logica
	(declare (salience -1001))
	(not (caracteristica-deseada))
	=>
	(focus MOSTRAR)
	(return)
)

;regla para evitar casos en que no empareje una caracteristica-deseada evitando que el programa se quede siempre en este punto
(defrule LOGICA::solucion-pillarse
	(declare (salience -1000))
	?h<-(caracteristica-deseada)
	=>
	(retract ?h)
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_marca
    ?h<-(caracteristica-deseada (nombre marca)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(marca ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
    =>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_amperios
    ?h<-(caracteristica-deseada (nombre amperios)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(amperios ?amp&:(or(> ?amp ?x)(eq ?amp ?x)))(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_pulgadas
    ?h<-(caracteristica-deseada (nombre pulgadas)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(pulgadas ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_precio
    ?h<-(caracteristica-deseada (nombre precio)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(precio ?pre&:(or(< ?pre ?x)(eq ?pre ?x)))(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_peso
    ?h<-(caracteristica-deseada (nombre peso)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(peso ?pes&:(or(< ?pes ?x)(eq ?pes ?x)))(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_camaraTrasera
    ?h<-(caracteristica-deseada (nombre camaraTrasera)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(camaraTrasera ?ct&:(or(> ?ct ?x)(eq ?ct ?x)))(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_camaraFrontal
    ?h<-(caracteristica-deseada (nombre camaraFrontal)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(camaraFrontal ?cf&:(or(> ?cf ?x)(eq ?cf ?x)))(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_S.O.
    ?h<-(caracteristica-deseada (nombre S.O.)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(S.O. ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_proceador
    ?h<-(caracteristica-deseada (nombre procesador)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(procesador ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_grafica
    ?h<-(caracteristica-deseada (nombre grafica)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(grafica ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)


;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_cargaRapida
    ?h<-(caracteristica-deseada (nombre cargaRapida)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(cargaRapida ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_bluetooth
    ?h<-(caracteristica-deseada (nombre bluetooth)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(bluetooth ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_USB
    ?h<-(caracteristica-deseada (nombre USB)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(USB ?x)(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_almacenamiento
    ?h<-(caracteristica-deseada (nombre almacenamiento)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(almacenamiento ?al&:(or(> ?al ?x)(eq ?al ?x)))(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)

;regla para aumentar el contador
(defrule LOGICA::aumentar_contador_RAM
    ?h<-(caracteristica-deseada (nombre RAM)(valor ?x)(marcado $?todo))
    ?p<- (smartphone (id ?y2)(RAM ?ram&:(or(> ?ram ?x)(eq ?ram ?x)))(contador ?c))
    (not (caracteristica-deseada (marcado $? ?y&:(eq ?y ?y2) $?)))
	=>
    (modify ?p (contador (+ ?c 1)))
    (modify ?h (marcado ?todo ?y2))
)
