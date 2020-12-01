//==============================================================================
// Ejemplo del uso de FreeRTOS - Para MEGA2560
//--------------------------------------------
// EJERCICIO PARA TAREA, A EXPLICAR EN EQUIPO:
//--------------------------------------------
// Aumentar el número de tareas a 8, considerando:
// 1.) Para verificar la secuencia de ejecución de las tareas, utilice la
// siguiente notación para la ocurrencia de las tareas:
// 
// Tarea 1: --- 01
// Tarea 2: ----- 02
// Tarea 3: ------- 03
// Tarea 4: --------- 04
// Tarea 5: ----------- 05
// Tarea 6: ------------- 06
// Tarea 7: --------------- 07
// Tarea 8: ----------------- 08
// 
// En la ocurrencia de la tarea agregar si recibió o envió datos a otras 
// Tareas, por ejemplo, la siguiente línea indicaría que en esta instancia
// la Tarea 6 envió algo a la Tarea 4:
// Tarea 6: ------------- 06 [-> 4]
// En el siguiente caso, la Tarea 5 recibió algo de la Tarea 2.
// Tarea 5: ----------- 05 [<-2]

// 2.) Cambiar los siguientes parámetros para ejercitar las diversas opciones:
// a.) Prioridades de las tareas
// b.) Frecuencia de ejecución de las tareas. Algunas de ellas se ejecutarán 
// más veces que otras.
// c.) Conclusión de las tareas. Algunas tareas terminarán antes que otras.
// d.) Comunicación entre tareas. Verificar cuáles son las funciones o 
// directivas que se pueden emplear para que una tarea comunique algo a otra.
// Ejercitar que las comunicaciones se den después de que pasaron varias 
// ejecuciones, por ejemplo, que la tarea 3 comunique a la tarea 5 después de
// que la tarea 3 ha ocurrido por quinta vez. Hacer algo similar para otros
// casos.
// e.) Ejercitar dos características más que crea importantes de FrreRTOS en el
// mismo ejemplo.
// f.) Comentar adecuadamente las líneas del código.
// g.) Para la presentación, puede emplear el monitor serial, simulado o real,
// verificando que efectivamente ocurre la secuencia que planeó.
//==============================================================================
//#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>  

QueueHandle_t paraenv; 

//------------------------------------
//-----[ DEFINICIÓN de la TAREA ]-----
//------------------------------------
void Tarea1( void * parameter );
void Tarea2( void * parameter);
void Tarea3( void * parameter);
void Tarea4( void * parameter);
void Tarea5( void * parameter);
void Tarea6( void * parameter);
void Tarea7( void * parameter);
void Tarea8( void * parameter);

//---------------------
//-----[ AJUSTES ]-----
//---------------------
void setup() {
  Serial.begin(57600);
  Serial.println("-- INICIO --"); // Inicio
  delay(1000);

  paraenv = xQueueCreate(5, sizeof(String)); // Se crea un dato de tipo string para enviar no mas de 5 digitos

  
// Creación de las tareas:
  xTaskCreate(
    Tarea1,     // Función que ejecuta la tarea
    "Tarea1",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    2,          // Prioridad de la tarea
    NULL);      // Manejador (Handle) de la tarea

    
  xTaskCreate(
    Tarea2,     //Función que ejecuta la tarea
    "Tarea2",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    1,          // Prioridad de la tarea
    NULL);      // Manejador (Handle) de la tarea

     xTaskCreate(
    Tarea3,     //Función que ejecuta la tarea
    "Tarea3",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    1,          // Prioridad de la tarea
    NULL);      // Manejador (Handle) de la tarea

    
     xTaskCreate(
    Tarea4,     //Función que ejecuta la tarea
    "Tarea4",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    1,          // Prioridad de la tarea
    NULL);      // Manejador (Handle) de la tarea

         xTaskCreate(
    Tarea5,     //Función que ejecuta la tarea
    "Tarea5",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    3,          // Prioridad de la tarea
    NULL);      // Manejador (Handle) de la tarea

         xTaskCreate(
    Tarea6,     //Función que ejecuta la tarea
    "Tarea6",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    1,          // Prioridad d la tarea
    NULL);      // Manejador (Handle) de la tarea
    
        xTaskCreate(
    Tarea7,     //Función que ejecuta la tarea
    "Tarea7",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    1,          // Prioridad d la tarea
    NULL);      // Manejador (Handle) de la tarea

         xTaskCreate(
    Tarea8,     //Función que ejecuta la tarea
    "Tarea8",   // Cadena con el nombre de la tarea
    60,         // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    2,          // Prioridad d la tarea
    NULL);      // Manejador (Handle) de la tarea
}


//-----------------------
//-----[ PRINCIPAL ]-----
//-----------------------
void loop() {
  delay(1000);  // Retardo para imprimir ocurrencias (Ejercitar)
}

//==============================================================================
//---------------------
//-----[ TAREA 1 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea1( void * parameter ){
    for( int i = 0;i<10;i++ ){    // Número de veces que ocurre esta tarea
        Serial.println("--- 01"); // Evidencia de ocurrencia
        delay(1000);              // Espera...
    }
    Serial.println("--> 01");     // Conclusión de la tarea
    vTaskDelete( NULL );          // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 2 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea2( void * parameter){
    for( int i = 0;i<5;i++ ){       //Número de veces que ocurre esta tarea
        Serial.println("----- 02"); //Evidencia de ocurrencia
        delay(1000);                //Espera...
    }
    Serial.println("--> 02");       // Conclusión de la tarea
    vTaskDelete( NULL );            //Se "borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 3 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea3( void * parameter){
    for( int i = 0;i<3;i++ ){        //Número de veces que ocurre esta tarea
        Serial.println("------- 03"); //Evidencia de ocurrencia
        delay(1000);                  //Espera...
    }
    Serial.println("--> 03");         // Conclusión de la tarea
    vTaskDelete( NULL );              //Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 4 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea4( void * parameter){
    for( int i = 0;i<10;i++ ){          //Número de veces que ocurre esta tarea
        Serial.println("--------- 04"); //Evidencia de ocurrencia
        delay(1000);                    //Espera...
    }
    Serial.println("--> 04");           // Conclusión de la tarea
    vTaskDelete( NULL );                //Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 5 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea5( void * parameter){
     for( int i = 0;i<10;i++ ){                 // Número de veces que ocurre esta tarea
        switch (i){
          case 0:     // Primera ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          case 1:     // Segunda ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          case 2:     // Tercera ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          case 3:     // Cuarta ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          case 4:     // Quinta ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          case 5:     // Sexta ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          case 6:     // Séptima ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          case 7:     // Octava ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          
          case 8:     // Novena ejecución T1
                {
            Serial.print("----------- 05");   // Evidencia de ocurrencia
                      // Función para enviar dato a Tarea 6
          String enviar = "[<-6]";
          xQueueSend(paraenv, &enviar , portMAX_DELAY);// Función para enviar dato a Tarea 6
          Serial.println("[->6]");
          
          break;
          }
          case 9:     // Décima ejecución T1
            Serial.println("----------- 05");   // Evidencia de ocurrencia
          break;
          default:
            Serial.println("------------ 05");   // Evidencia de ocurrencia
          break;
        }
        delay(1000);                            // Espera...
    }
    Serial.println("--> 05");                   // Conclusión de la tarea
    vTaskDelete( NULL );                        // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 6 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea6( void * parameter){
    for( int i = 0;i<10;i++ ){              //Número de veces que ocurre esta tarea
        Serial.println("------------- 06"); //Evidencia de ocurrencia
        delay(1000);                        //Espera
        
        if(i==5){                           //Si realiza la tarea 5 veces
          Serial.print("------------- 06");
          String recibir;
          if (xQueueReceive(paraenv, &recibir, portMAX_DELAY) == pdPASS) {
            Serial.println(recibir);
          }
          
        }
    }
    Serial.println("--> 06");               // Conclusión de la tarea
    vTaskDelete( NULL );                    //Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 7 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea7( void * parameter){
    for( int i = 0;i<20;i++ ){                //Número de veces que ocurre esta tarea
        Serial.println("--------------- 07"); //Evidencia de ocurrencia
        delay(1000);                          //Espera...
    }
    Serial.println("--> 07");                 // Conclusión de la tarea
    vTaskDelete( NULL );                      //Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 8 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea8( void * parameter){
    for( int i = 0;i<10;i++ ){                  //Número de veces que ocurre esta tarea
        Serial.println("----------------- 08"); //Evidencia de ocurrencia
        delay(1000);                            //Espera..
    }
    Serial.println("--> 08");                   // Conclusión de la tarea
    vTaskDelete( NULL );                        //Se "Borra"
}
