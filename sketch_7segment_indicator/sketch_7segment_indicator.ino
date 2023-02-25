/*
 программа для вывода не 7-ми седментом индикаторе:
1 вариант - перечисление цифр из массива Number на одном индикаторе
2 вариант - отображение слова на всех индикаторах Lion
*/
byte Number[10] = {
  0b01111110, //0
  0b01100000, //1 
  0b10110110, //2 
  0b10011110, //3 
  0b11001100, //4 
  0b11011010, //5 
  0b11111010, //6 
  0b00001110, //7 
  0b11111110, //8
  0b11011110, //9
};

byte lion[4] = {
  0b01110000, // L
  0b00001000, // i
  0b10111000, // o
  0b10101000, // n
};

void setup() {
  for (int i=2;i<=13;i++){
      pinMode(i, OUTPUT);
  }
  for (int i=10;i<=13;i++){
      digitalWrite(i, HIGH);
  }
}

void loop() {

  for (int i=0;i<=3;i++){
    // всё выключаем
    for (int j=10;j<=13;j++){
      digitalWrite(j, HIGH);
    }
    // end str
    digitalWrite(9+4-i, LOW);

    for (int k=2;k<=9;k++){
      digitalWrite(k, bitRead(lion[i], k-2));
    }      
    delay(6);
  }

}

