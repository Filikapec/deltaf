#include "pinout.h"
#include "Point3D.h"
#include "Point2D.h"
#include <math.h>

String naredbe[30];
Point3D pozicije[30];
int brojkomandi=0;

Point3D ADG = {74.35,0,242.5},
AGG={161.33, 0, 329.47},
BDG={-37.18, 64.39, 242.5},
BGG={-80.67, 139.72, 329.47},
CDG={-37.18, -64.39, 242.5},
CGG={-80.67, -139.72, 329.47};

Point3D offsetA = {32.94, 0, 7.5},
offsetB = {-16.44, 28.54, 7.5},
offsetC = {-16.44, -28.54, 7.5};

float duzinaVeza = 264;

Slider SliderA, SliderB, SliderC;

void setup() {
  Serial.begin(9600);
  PodesiPinove();
  InicijalizujSlidere(SliderA, SliderB, SliderC);
}

void loop() {
  if(Serial.available()) {
    CitajSerijsku();
    for(int i=0; i<brojkomandi; i++) {
      Izvrsi(pozicije[i]);
    }
    
  }
}

void Izvrsi(Point3D Target) {
  Kinematika(Target);
}

Point3D StringToPoint3D(String input) {
  String xval = input.substring(0, input.indexOf(' '));
  String yval = input.substring(input.indexOf(' '), input.lastIndexOf(' '));
  String zval = input.substring(input.lastIndexOf(' '), input.length());
  Point3D izlaz = {xval.toFloat(), yval.toFloat(), zval.toFloat()};
  return izlaz;
}

void CitajSerijsku() {
  String ulaz = Serial.readString();
    if(ulaz.charAt(0)=='R') {
      String komcount = ulaz.substring(1, ulaz.length());
      brojkomandi = komcount.toInt();
      Serial.print("Cekam "); Serial.println(brojkomandi);
      for(int i=0; i<brojkomandi; i++) {
        while(!Serial.available()) {
          delay(5);
        }
        naredbe[i] = Serial.readString();
        pozicije[i] = StringToPoint3D(naredbe[i]);
        Serial.print("Primljen broj ");
        Serial.println(i);
      }
    }
    for(int i = 0; i < brojkomandi; i++) {
      
    }
}

void Kinematika(Point3D Target) {
  Point3D TA = Saberi3D(Target, offsetA);
  Point3D TB = Saberi3D(Target, offsetB);
  Point3D TC = Saberi3D(Target, offsetC);
  //Debug(TA); Debug(TB); Debug(TC);

  float alfa = ugao3D(AGG, ADG, TA);
  float beta = ugao3D(BGG, BDG, TB);
  float gama = ugao3D(CGG, CDG, TC);

  float d1 = rastojanje(ADG, TA);
  float d2 = rastojanje(BDG, TB);
  float d3 = rastojanje(CDG, TC);

  Point2D TargetA2D = ConvertToRavan(alfa, d1);
  Point2D TargetB2D = ConvertToRavan(beta, d2);
  Point2D TargetC2D = ConvertToRavan(gama, d3);

  Point2D PA = Slider2DPozicija(TargetA2D, duzinaVeza);
  Point2D PB = Slider2DPozicija(TargetB2D, duzinaVeza);
  Point2D PC = Slider2DPozicija(TargetC2D, duzinaVeza);

  float PozicijaSlideraA = 123 - udaljenostTacke2D(PA);
  float PozicijaSlideraB = 123 - udaljenostTacke2D(PB);
  float PozicijaSlideraC = 123 - udaljenostTacke2D(PC);

  int putanjastpA, putanjastpB, putanjastpC;
  putanjastpA = (int)(PozicijaSlideraA * 200 / 8);
  putanjastpB = (int)(PozicijaSlideraB * 200 / 8);
  putanjastpC = (int)(PozicijaSlideraC * 200 / 8);

  Point3D oiz = {(float)(round(putanjastpA)), (float)(round(putanjastpB)), (float)(round(putanjastpC))};
  //Point3D oiz = {PozicijaSlideraA, PozicijaSlideraB, PozicijaSlideraC};
  Debug(oiz);

  //sumultanoKretanje(putanjastpA, putanjastpB, putanjastpC, 6000);
  kretanje(putanjastpA, putanjastpB, putanjastpC);
  
}

void Debug(Point3D a) {
  Serial.print(a.x); Serial.print(' ');
  Serial.print(a.y); Serial.print(' ');
  Serial.println(a.z);
}
