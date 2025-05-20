| Parte               | Núcleo técnico                                                                                            | Entregables claves                                                                                               | Dependencias                                                      |
| ------------------- | --------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------- |
| 1. LED + TouchPad   | • Re-configuración del LED RGB (Lab 1)  • Nueva librería para 6 botones touch y su algoritmo de detección | • Proyecto **Laboratorio\_2a** funcional • Descripción breve del API Touch • Algoritmo en pseudocódigo           | Sólo requiere haber clonado las libs del Lab 1                    |
| 2. Wi-Fi (AP + STA) | • Análisis ESP-NETIF y Event Loop • Implementar AP • Implementar STA • Comparar configuraciones           | • Proyecto **Laboratorio\_2b** • Pseudocódigos AP/STA • Capturas de datos en monitor                             | Parte 1 puede seguir en paralelo; no depende del servidor web     |
| 3. Servidor Web     | • Página HTML/CSS/JS embebida • Montaje del http\_server • Enviar/recibir datos • Persistencia mínima     | • Web “Hola mundo” accesible desde PC/móvil • Código + archivos embebidos • Respuesta a pregunta de persistencia | Necesita Wi-Fi configurado, pero la página puede diseñarse antes  |


| Rol / Persona                   | Foco principal         | Tareas concretas                                                                                                                                                                                                                    | Paralelización                                                                            | Esfuerzo aprox. |
| ------------------------------- | ---------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------- | --------------- |
| **P1 – Firmware & Periféricos** | Hardware de bajo nivel | 1. Migrar LED RGB al repo nuevo.<br>2. Investigar API Touch & schematic; escribir resumen.<br>3. Codificar librería TouchPad y pruebas con LED.                                                                                     | Comienza inmediatamente (independiente de Wi-Fi).                                         | 30 %            |
| **P2 – Conectividad Wi-Fi**     | Redes y sistema        | 1. Documentar ESP-NETIF y Event Loop.<br>2. Escribir pseudocódigo AP y STA.<br>3. Implementar AP y registrar datos.<br>4. Implementar STA y registrar datos.                                                                        | Empieza lectura/documentación en paralelo con P1; codificación AP mientras P3 diseña web. | 35 %            |
| **P3 – Web & UX**               | Front-end embebido     | 1. Diseñar página HTML/CSS/JS simple (offline).<br>2. Revisar ejemplos http\_server y escribir pseudocódigo.<br>3. Tras Wi-Fi listo, montar servidor y probar desde PC/móvil.<br>4. Definir qué parámetros de IoT persistir y cómo. | Diseño web puede avanzar en paralelo a todo; integración espera a que P2 exponga red.     | 35 %            |


Coordinación y buenas prácticas
Repositorio único con ramas feature/parte-1, feature/parte-2, feature/parte-3 y Pull Requests diarios.

Kanban simple (To-do / Doing / Review / Done) para visualizar bloqueos.

Convenciones: clang-format, comentarios Doxygen, commits cortos.

Revisiones cruzadas: cada PR lo revisa alguien de otro rol → asegura involucramiento de los tres (criterio A del lab).

Documentación viva en README por parte, respondiendo preguntas teóricas y pegando pseudocódigos solicitados.

Pruebas: usar idf.py monitor con timestamp y registrar capturas necesarias para evidencias de AP/STA y TouchPad.

Backup/entrega: tag v1.0-entrega la víspera y verificar que compila desde cero.

Con esta división cada persona sostiene un área principal pero todos participan en revisiones y demo final, cumpliendo la evaluación por completitud, participación y buenas prácticas.