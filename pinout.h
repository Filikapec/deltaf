#define dirA 2
#define dirB 3
#define dirC 4
#define stpA 5
#define stpB 6
#define stpC 7
#define en 8

void PodesiPinove() {
  pinMode(dirA, OUTPUT);
  pinMode(stpA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(stpB, OUTPUT);
  pinMode(dirC, OUTPUT);
  pinMode(stpC, OUTPUT);
  pinMode(en, OUTPUT);
  digitalWrite(en, HIGH);
}

typedef struct {
  int dir, stp;
  int poz = 0;
} Slider;

 void InicijalizujSlidere(Slider a, Slider b, Slider c) {
  a.dir = dirA;
  b.dir = dirB;
  c.dir = dirC;
  a.stp = stpA;
  b.stp = stpB;
  c.stp = stpC;
  a.poz = 0;
  b.poz = 0;
  c.poz = 0;
}

void kretanje(int a, int b, int c) {
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, HIGH);
  digitalWrite(dirC, HIGH);
  digitalWrite(en, LOW);
  for(int i=0; i<a; i++) {
    digitalWrite(stpA, HIGH);
    delay(5);
    digitalWrite(stpA, LOW);
    delay(5);
  }
  for(int i=0; i<b; i++) {
    digitalWrite(stpB, HIGH);
    delay(5);
    digitalWrite(stpB, LOW);
    delay(5);
  }
  for(int i=0; i<c; i++) {
    digitalWrite(stpC, HIGH);
    delay(5);
    digitalWrite(stpC, LOW);
    delay(5);
  }
  digitalWrite(en, HIGH);
}
