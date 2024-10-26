# ArduGator
#### ~          See You Later, Aligator


## Introducción

Mi objetivo es crear un badUSB que desplieuge un sistema de persistencia en un sistema con permisos de administrador y layout de teclado en Español.

Para esto voy a utilizar una arduino pro micro y la libreria Keyboard.h nativa de Arduino.

La fase de crear el bad-USB esta finalizada al 100% y ya solo faltaria desarrollar el sistema de persistencia y hacer que el badUSB lo descargue y programe para el proximo startup.


## Proceso de desarrollo

## Keyboard.print() esta fatal implementado

La función Keyboard.print() de Keyboard.h funciona fatal, según unas pruebas que hcie se salta 1/3 de los caracteres (de media).

Supuse que procesa los caracteres mucho más rapido que su propio bus de datos de HID.

Esto se soluciono facilimente con una función: printString(), que recorre el string caracter por caracter y utiliza keyboard.write() y un delay. 

Esto lo mantiene más configurable (velocidad de escritura) y lo econtré mucho más fiable (98% de caracteres correctos)

### mapSpanishToUS()

En las primeras pruebas tansolo estaba abriendo notepad.x mediante el menu de ejectución mediante Win+R.

En esa fase no encontré nigún problema hasta que traté de abrir una terminal de administrador de la misma forma.

El comando utiliza varios guiones que aparecian como /.
Comparando el layout de teclado americano con el Español me di cuenta que correspondía.

Para un caso concreto como era el mío podria haber "traducido" todos los simbolos para que correspondiese conel que yo quería, o simplemente haber cambiado mi ojbetvio a teclados americanos. Sin embargo me imapcto no encontrar ninguna librería en github que me solucionase el problema (al menos no que funcionase y estuviese mantenida) asique decidí crearme un esquema que se solucionase esto para cualquier proyecto futuro.

En el proceso me dí cuenta además de que algunos caracteres eran inaccesibles por la presencia de AltGr y algunos caracteres que requieren Shift que se volvían inaccesibles al no tener un equivalente en el otro Layout.

Todo esto lo hacia basante impredecible para "traducir" caracteres asique decidi crear dos funciones: pressShiftedKey y pressGrKey.

Estas funciones utilizan Keyboard.press() y release() en lugar de write() para escribir el caracter recibido, lo cual lo hacia bastante más consistente y flexible.

Aparte, para enmascarar todo esto creé mapSpanishToUs, funcion que mediante un switch case facilitaba mucho la "traduccion" de distintos caracteres, manteniendolo organizado y modular en caso de ser necesario.

Aparte como default le añadi un fallback a simplemente utilizar keyboard.write() con el caracter recibido. De esta forma se podian pasar todos los caracteres por ahi, no solo los que necesitasen traducción.

Gracias a esto implementarlo fue simplemente sustituir en printString el keyboard.write(char) por mapSpanishToUs(char)


### runCommand y bypassUAC

Para hacerme la vida mas sencilla cree dos funciones, una que utiliza Win+R y ejecuta el comando pasado como parametro y otra que utiliza las flechas y el enter para aceptar el UAC.


Esto me permite ajustar los tiempos y configurarlo todo de forma mucho más encapsulada, observable y adaptable.

## Pruebas Realizadas

Las pruebas sobre la precisión de escritura de el badUSB con print y con write se realizaron escribiendo 10 cadenas de 100 caracteres aleatorios con cada función y comparando los resultados.

Las pruebas hasta ahora realizadas de fucionalidad han sido, abrir un NotePad y escribir un mensaje (el hola mundo de los badUSB) y abrir una terminal de administrador.

Como un primer acercamiento a la segunda fase del proyecto, la persistencia, la ultima prueba realizada ha sido descargar del propio repo de github mediante Invoke-WebRequest un fichero con permisos de administrador en el desktop.


## Conclusiones

El apartado badUSB esta finalizado y actualmente me encuentro investigando y haciendo pruebas de cifrados de msfvenom y tecnicas de ofuscación para crear backdoors distintas y que no detecte el Defender y poderlas programar como tareas.

El codigo esta muy comentado y hay un TODO con los objetivos a realizar para más información



