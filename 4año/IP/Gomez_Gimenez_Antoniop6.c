const unsigned long period = 50;
unsigned long prevMillis = 0;
 
byte iRow = 0, iCol = 0;
const byte countRows = 3;
const byte countColumns = 4;
 
const byte rowsPins[countRows] = {7, 6, 5};// COMPLETAR
const byte columnsPins[countColumns] = {12, 11, 10, 9};// COMPLETAR
 
char keys[countRows][countColumns] = {{'1', '2', '3', '+'}, {'4', '5', '6', '-'}, {'7', '8', '9', '0'}};// COMPLETAR

// Leer el estado del teclado
bool readKeypad()
{
  bool teclaPulsada = false;
 
  // Barrido de columnas
  for (byte c = 0; c < countColumns; c++)
  {
    // Poner columna a LOW
    pinMode(columnsPins[c],OUTPUT);
    digitalWrite(columnsPins[c], LOW);
    
    // Barrer todas las filas comprobando pulsaciones
    for (byte r = 0; r < countRows; r++)
    {
      if (digitalRead(rowsPins[r]) == LOW)   
      {
        // Pulsacion detectada, guardar fila y columna
        // COMPLETAR 
        iRow = r;
        iCol = c;
        teclaPulsada = true;
      }
    }
    // Devolver la columna a alta impedancia    
    // COMPLETAR
    digitalWrite(columnsPins[c], HIGH);
  }
  return teclaPulsada;
}

void setup()
{
  Serial.begin(9600);
 
  // Columnas en alta impedancia (MODO "INPUT")
  for (byte c = 0; c < countColumns; c++)
  {
    pinMode(columnsPins[c], INPUT);//COMPLETAR
  }
 
  // Filas en pullup (MODO "INPUT_PULLUP")
  for (byte r = 0; r < countRows; r++)
  {
    pinMode(rowsPins[r], INPUT_PULLUP);//COMPLETAR
  }
}

void loop()
{   
  if (millis() - prevMillis > period)   // Espera no bloqueante
  {
    prevMillis = millis();
    if (readKeypad())   // Detección de tecla pulsada
    {
      Serial.print("La tecla pulsada es: ");// COMPLETAR 
      Serial.println(keys[iRow][iCol]);
    }
  }
}