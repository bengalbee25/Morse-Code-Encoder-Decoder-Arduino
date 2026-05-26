int tonePin = 2;
int toneFreq = 1000;
int ledPin = 13;
int buttonPin = 8;
int debounceDelay = 30;

 int dotLength = 240; 
 int dotSpace = dotLength;
 int dashLength = dotLength*3;
 int letterSpace = dotLength*3;
 int wordSpace = dotLength*7; 
float wpm = 1200./dotLength;
  
int t1, t2, onTime, gap;
bool newLetter, newWord, letterFound, keyboardText;
int lineLength = 0;
int maxLineLength = 20; 

char* letters[] = 
{
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." 
};

char* numbers[] = 
{
"-----", ".----", "..---", "...--", "....-", 
".....", "-....", "--...", "---..", "----." 
};

String dashSeq = "";
char keyLetter, ch;
int i, index;

void setup() 
{
  delay(500);
  pinMode(ledPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println();
  Serial.println("-------------------------------");
  Serial.println("Morse Code encoder/decoder");
  Serial.print("Speed=");
  Serial.print(wpm);
  Serial.print("wpm, ");
  Serial.print("dot=");
  Serial.print(dotLength);
  Serial.println("ms");   
  

  tone(tonePin, toneFreq);
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);
  noTone(tonePin);
  delay(600);


   Serial.print("A .-  ");
   index = 'A'-65;
   flashSequence(letters[index]);
   delay(wordSpace);

   Serial.print("B -...  ");
   index = 'B'-65;
   flashSequence(letters[index]);
   delay(wordSpace);

   Serial.print("C -.-.  ");
   index = 'C'-65;
   flashSequence(letters[index]);
   delay(wordSpace);

  Serial.println();
  Serial.println("-------------------------------");
  Serial.println("Click field in Serial Monitor,");
  Serial.println("type text and press Enter, or");
  Serial.println("Key in Morse Code to decode:");
  Serial.println("-------------------------------");
      
  newLetter = false; 
  newWord = false;  
  keyboardText = false; 
}

void loop() 
{

  if (Serial.available() > 0)
  {
    if (keyboardText == false) 
    {
      Serial.println();
      Serial.println("-------------------------------");
    }
    keyboardText = true;
    ch = Serial.read();
    if (ch >= 'a' && ch <= 'z')
    { ch = ch-32; }
    
    if (ch >= 'A' && ch <= 'Z')
    {
      Serial.print(ch); 
      Serial.print(" ");
      Serial.println(letters[ch-'A']);
      flashSequence(letters[ch-'A']);
      delay(letterSpace);
    }
    if (ch >= '0' && ch <= '9')
    {
      Serial.print(ch);
      Serial.print(" ");
      Serial.println(numbers[ch-'0']);
      flashSequence(numbers[ch-'0']);
      delay(letterSpace);
    }
    if (ch == ' ')
    {
      Serial.println("_");
      delay(wordSpace);    
    } 

 
     if (Serial.available() <= 0) 
     {
      Serial.println();
      Serial.println("Enter text or Key in:");
      Serial.println("-------------------------------");
      keyboardText = false;
     }
  }
 
  if (digitalRead(buttonPin) == LOW ) 
  {
    newLetter = true; 
    newWord = true;
    t1=millis(); 
    digitalWrite(ledPin, HIGH); 
    tone(tonePin, toneFreq);
    delay(debounceDelay);     
    while (digitalRead(buttonPin) == LOW ) 
      {delay(debounceDelay);}
      delay(debounceDelay);
       
    t2 = millis();  
    onTime=t2-t1;  
    digitalWrite(ledPin, LOW); 
    noTone(tonePin); 
    


    if (onTime <= dotLength*1.5)  
      {dashSeq = dashSeq + ".";} 
    else 
      {dashSeq = dashSeq + "-";}
  }  
  

  gap=millis()-t2; 
  if (newLetter == true && gap>=letterSpace)  
  { 
    

    letterFound = false; keyLetter = 63; 
    for (i=0; i<=25; i++)
    {
      if (dashSeq == letters[i]) 
      {
        keyLetter = i+65;
        letterFound = true;   
        break ;     
      }
    }
    if(letterFound == false) 
    {
      for (i=0; i<=10; i++)
      {
      if (dashSeq == numbers[i]) 
        {
          keyLetter = i+48;
          letterFound = true;   
          break ;     
        }
      }
    }    
    Serial.print(keyLetter);
    if(letterFound == false) 
    {
      tone(tonePin, 100, 500);
    }  
    newLetter = false; 
    dashSeq = "";
    lineLength=lineLength+1;
  }  
  

  if (newWord == true && gap>=wordSpace*1.5)
    { 
     newWord = false; 
     Serial.print("_");  
     lineLength=lineLength+1;
     

    digitalWrite(ledPin, HIGH);
    delay(25);
    digitalWrite(ledPin, LOW);       
    } 


  if (lineLength >= maxLineLength) 
    {
      Serial.println();
      lineLength = 0;
    }      
} 

void flashSequence(char* sequence)
{
  int i = 0;
  while (sequence[i] == '.' || sequence[i] == '-')
  {
    flashDotOrDash(sequence[i]);
    i++;
  }
}

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
  tone(tonePin, toneFreq);
  if (dotOrDash == '.')
   { delay(dotLength); }
     else
   { delay(dashLength); }

  digitalWrite(ledPin, LOW);
  noTone(tonePin);
  delay(dotLength); 
}


