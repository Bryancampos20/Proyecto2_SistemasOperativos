# Proyecto 2 Sistemas Operativos

## Descripción del Proyecto

Este proyecto implementa un sistema distribuido que simula una red de nodos interconectados para la gestión eficiente de procesos y recursos compartidos. El sistema incorpora funcionalidades clave como asignación dinámica de procesos, balanceo de carga, sincronización de recursos compartidos, manejo de fallos, y escalabilidad.

El objetivo es ofrecer una solución robusta y modular que permita el funcionamiento continuo de los nodos, incluso en presencia de fallos, garantizando la redistribución de procesos y la sincronización adecuada en el acceso a los recursos.

## Características Principales

1. **Gestión de Procesos**  
   - Asignación dinámica de procesos al nodo menos cargado.  
   - Redistribución automática en caso de fallo de un nodo.

2. **Balanceo de Carga**  
   - Optimización de la distribución de procesos entre los nodos activos.

3. **Sincronización de Recursos Compartidos**  
   - Exclusión mutua para garantizar el acceso seguro a los recursos compartidos.  

4. **Manejo de Fallos**  
   - Detección de fallos en nodos.  
   - Redistribución automática de procesos asignados al nodo fallido.

5. **Escalabilidad**  
   - Permite agregar nuevos nodos dinámicamente sin interrumpir el funcionamiento.

## Estructura del Proyecto

- **`node.c` y `node.h`**: Implementación de las funcionalidades relacionadas con los nodos, como la gestión de procesos y el manejo de recursos compartidos.
- **`network.c` y `network.h`**: Implementación de la red que permite la comunicación y coordinación entre nodos.
- **Casos de Prueba**:  
  - **`test_case1.c`**: Asignación de procesos a nodos.  
  - **`test_case2.c`**: Sincronización de recursos compartidos.  
  - **`test_case3.c`**: Manejo de fallos de nodos.  
  - **`test_case4.c`**: Balanceo de carga en la red.  
  - **`test_case5.c`**: Acceso sincronizado a recursos compartidos.  
  - **`test_case6.c`**: Redistribución automática de procesos tras fallo de nodo.  
  - **`test_case7.c`**: Escalabilidad del sistema al agregar nodos dinámicamente.  
  - **`test_case8.c`**: Redistribución automática cuando un nodo alcanza su límite de capacidad.

## Requisitos

- **Compilador**: `gcc` con soporte para hilos (`-lpthread`).
- **Sistema Operativo**: Unix/Linux o macOS.
- **Lenguaje**: C.

## Instrucciones de Uso

1. **Clonar el Repositorio**  

```bash
git clone <URL_DEL_REPOSITORIO>
cd Proyecto2_SistemasOperativos
```

2. **Compilar el Proyecto**  
El proyecto incluye un archivo `Makefile` para simplificar la compilación.  
Ejecuta el siguiente comando:  

```bash
make
```


3. **Ejecutar los Casos de Prueba**  
Cada prueba se puede ejecutar de la siguiente manera:  
- Para el **Caso de Prueba 1**:
  ```
  ./test_case1
  ```
- Para el **Caso de Prueba 2**:
  ```
  ./test_case2
  ```
- Repetir para los demás casos: `./test_case3`, `./test_case4`, etc.

4. **Limpiar el Proyecto**  
Para eliminar los archivos generados, ejecuta:  

 ```
make clean
 ```

 ## Arquitectura del Sistema

El sistema está diseñado de forma modular:
- **Nodos**: Manejan procesos y sincronizan recursos compartidos.
- **Red**: Coordina la comunicación entre nodos y asegura el balanceo de carga y manejo de fallos.
- **Recursos Compartidos**: Implementan exclusión mutua para el acceso seguro.

## Contacto

Si tienes preguntas o sugerencias, no dudes en contactar al autor del proyecto:  
**Bryan Campos**  
_Email_: bryancampos20@gmail.com  
_LinkedIn_: [Perfil LinkedIn](https://www.linkedin.com/in/bryan-campos-castro-138a3a189/)
