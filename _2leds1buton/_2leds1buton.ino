int switchPin = 9;    // pin du bouton (
int ledpin1 =2;   //  le nom de la led est choisie au hasard
int ledpin2 =3;  
void setup() {

  pinMode(switchPin, INPUT);
  // cette ligne signifie que switchpin(bouton)est une entrée
  pinMode(ledpin1, OUTPUT); //led1== sortie
  pinMode(ledpin2, OUTPUT); //led2== sortie
  digitalWrite(ledpin1, LOW);
}
void loop() {
  
  if (digitalRead(switchPin) == HIGH) // si le bouton est HIGH ( soit appuyer) voici ce qui se passe:
  {
   digitalWrite(ledpin2, LOW); //si le bouton est HIGH
  digitalWrite(ledpin1, HIGH); //si le bouton est HIGH
}
  else // inversement si il n'est pas appuyer
  {
      digitalWrite(ledpin2, HIGH); //si le bouton est LOW
  digitalWrite(ledpin1, LOW); //si le bouton est LOW
  }
  
}
