const double EPS = 1e-9;
bool equal(double a, double b) {
  return abs(a - b) < EPS;
}
bool lessThan(double a, double b) {
  return a < b - EPS;
}
bool greaterThan(double a, double b) {
  return a > b + EPS;
}
