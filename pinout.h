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
    digitalWrite(mag, HIGH);
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
  
  unsigned long pocetak = millis();
  digitalWrite(en, LOW);
  while(millis()-pocetak<trajanje) {
    unsigned long currentTime = millis();

    if(currentTime-prevA>=eventTimeA && a != 0) {
      digitalWrite(stpA, LOW);
      digitalWrite(stpA, HIGH);
      prevA = currentTime;
    }
    if(currentTime-prevB>=eventTimeB && b != 0) {
      digitalWrite(stpB, LOW);
      digitalWrite(stpB, HIGH);
      prevB = currentTime;
    }
    if(currentTime-prevC>=eventTimeC && c != 0) {
      digitalWrite(stpC, LOW);
      digitalWrite(stpC, HIGH);
      prevC = currentTime;
    }
  }
  digitalWrite(en, HIGH);
  
}
