#define dirA 2
#define dirB 3
#define dirC 4
#define stpA 5
#define stpB 6
#define stpC 7
#define en 8
#define mag 12

void PodesiPinove() {
  pinMode(dirA, OUTPUT);
  pinMode(stpA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(stpB, OUTPUT);
  pinMode(dirC, OUTPUT);
  pinMode(stpC, OUTPUT);
  pinMode(en, OUTPUT);
  digitalWrite(en, HIGH);
  pinMode(mag, OUTPUT);
}

typedef struct {
  int dir;
  int stp;
  int poz = 0;
} Slider;



void Uhvati(int yn) {
  if(yn) {
    digitalWrite(en, HIGH);
    delay(20);
    digitalWrite(mag, HIGH);
    delay(20);
    digitalWrite(en, LOW);
  } else {
    digitalWrite(mag, LOW);
  }
}

 void InicijalizujSlidere(Slider a, Slider b, Slider c) {
  /*a.dir = dirA;
  b.dir = dirB;
  c.dir = dirC;
  a.stp = stpA;
  b.stp = stpB;
  c.stp = stpC;
  a.poz = 15;
  b.poz = 0;
  c.poz = 0;
  a = Slider{dirA, stpB, 20};
  b = Slider{dirB, stpB, 0};
  c = Slider{dirC, stpC, 0};*/
}

unsigned long eventTimeA, eventTimeB, eventTimeC;
unsigned long prevA=0, prevB=0, prevC=0;
void kretanje(int a, int b, int c, unsigned long trajanje) {
  digitalWrite(dirA, a>=0);
  digitalWrite(dirB, b>=0);
  digitalWrite(dirC, c>=0);
  eventTimeA = trajanje/abs(a);
  eventTimeB = trajanje/abs(b);
  eventTimeC = trajanje/abs(c);

  int counterA=0, counterB=0, counterC=0;
  
  unsigned long pocetak = millis();
  digitalWrite(en, LOW);
  while(counterA<abs(a) || counterB<abs(b) || counterC<abs(c)) {
    unsigned long currentTime = millis();

    if(currentTime-prevA>=eventTimeA && a != 0 && counterA<abs(a)) {
      digitalWrite(stpA, LOW);
      digitalWrite(stpA, HIGH);
      counterA++;
      prevA = currentTime;
    }
    if(currentTime-prevB>=eventTimeB && b != 0 && counterB<abs(b)) {
      digitalWrite(stpB, LOW);
      digitalWrite(stpB, HIGH);
      counterB++;
      prevB = currentTime;
    }
    if(currentTime-prevC>=eventTimeC && c != 0 && counterC<abs(c)) {
      digitalWrite(stpC, LOW);
      digitalWrite(stpC, HIGH);
      counterC++;
      prevC = currentTime;
    }
  }/*
  for(counterA; counterA<abs(a); counterA++){
    digitalWrite(stpA, LOW);
    delay(3);
    digitalWrite(stpA, HIGH);
    delay(3);
  }
  for(counterB; counterB<abs(b); counterB++){
    digitalWrite(stpB, LOW);
    delay(3);
    digitalWrite(stpB, HIGH);
    delay(3);
  }
  for(counterC; counterC<abs(c); counterC++){
    digitalWrite(stpC, LOW);
    delay(3);
    digitalWrite(stpC, HIGH);
    delay(3);
  }*/
  digitalWrite(en, HIGH);
  
}
