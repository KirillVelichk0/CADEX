#include "../CAD_lib/CAD_lib.h"
#include <cmath>
#include <limits>
int main(int argc, char *argv[]) {
  auto i = 5;
  auto doubleIsBad = [](const double expected, const double actual,
                        const double mult) {
    return std::abs(expected - actual) >
           std::numeric_limits<double>::epsilon() * mult;
  };
  {
    auto circle = CreateCircle(10);
    auto [x, y, z] = circle->GetPointByT(M_PI_2l);
    if (doubleIsBad(0, x, 10) || doubleIsBad(10, y, 10)) {
      return 1;
    }
  }
  {
    auto circle = CreateCircle(10);
    auto [x, y, z] = circle->GetPointByT(M_PIl);
    if (doubleIsBad(-10, x, 10) || doubleIsBad(0, y, 10)) {
      return 1;
    }
  }
  try {
    auto circle = CreateCircle(0);
    return 1;
  } catch (...) {
  }

  {
    auto circle = CreateCircle(13.32);
    auto [derX, derY, derZ] = circle->GetFirstDerivative();
    if (doubleIsBad(-13.32, derX(M_PI_2l), 13.32)) {
      return 1;
    }
  }
  return 0;
}
