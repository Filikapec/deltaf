#define pi 3.141592

typedef struct {
  float x,y;
} Point2D;

float degtorad(float deg) {
  return deg*pi/180;
}

Point2D ConvertToRavan(float ugao, float dist) {
  Point2D T;
  T.x = cos(degtorad(45-ugao))*dist;
  T.y = sin(degtorad(45-ugao))*dist;
  return T;
}

float analiticka(Point2D T, float r) {
  float x1 = (T.x+T.y+sqrt(-T.x*T.x+2*T.x*T.y-T.y*T.y+2*r*r))/(2);
  return x1;
}

Point2D Slider2DPozicija(Point2D T, float r) {
  float x1y1 = analiticka(T,r);
  Point2D P = {x1y1, x1y1};
  return P;
}

float rastojanje2D(Point2D a, Point2D b) {
  float d = sqrt( (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) );
  return d;
}

float udaljenostTacke2D(Point2D a) {
  float d = sqrt( a.x*a.x + a.y*a.y);
  return d;
}
