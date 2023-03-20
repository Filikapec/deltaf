typedef struct {
  float x,y,z;
} Point3D;

Point3D Saberi3D(Point3D a, Point3D b) {
  Point3D suma = {a.x+b.x, a.y+b.y, a.z+b.z};
  return suma;
}

float ugao3D(Point3D a, Point3D b, Point3D c) {
  //struct v1 = (struct Vector3)(a.x - b.x, a.y - b.y, a.z - b.z);
  Point3D v1;  v1.x = a.x - b.x;  v1.y = a.y - b.y;  v1.z = a.z - b.z;
  Point3D v2;  v2.x = c.x - b.x;  v2.y = c.y - b.y;  v2.z = c.z - b.z;
  float v1mag = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
  Point3D v1norm = {v1.x / v1mag, v1.y / v1mag, v1.z / v1mag};
  float v2mag = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
  Point3D v2norm = {v2.x / v2mag, v2.y / v2mag, v2.z / v2mag};
  float res = v1norm.x * v2norm.x + v1norm.y * v2norm.y + v1norm.z * v2norm.z;
  float angle = acos(res);
  return angle * 180 / 3.14;
}

float rastojanje(Point3D a, Point3D b) {
  float d = sqrt( (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y) + (b.z-a.z)*(b.z-a.z) );
  return d;
}
