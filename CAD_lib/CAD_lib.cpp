#include "CAD_lib.h"
#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
Circle::Circle(const double r) : r(r) {}
Circle::Point Circle::GetPointByT(const double t) {
  return {this->r * std::cos(t), this->r * std::sin(t), 0};
}
Circle::Derivative Circle::GetFirstDerivative() {
  DerivativeComponent xDerComp = [r = this->r](const double t) {
    return r * -1 * std::sin(t);
  };
  DerivativeComponent yDerComp = [r = this->r](const double t) {
    return r * std::cos(t);
  };
  DerivativeComponent zDerComp = [](const double r) { return 0; };

  return {xDerComp, yDerComp, zDerComp};
}
double Circle::GetR() const noexcept { return this->r; }
Ellipse::Ellipse(const double rX, const double rY) : rX(rX), rY(rY) {}
Ellipse::Point Ellipse::GetPointByT(const double t) {
  return {this->rX * std::cos(t), this->rY * std::sin(t), 0};
}
Ellipse::Derivative Ellipse::GetFirstDerivative() {
  DerivativeComponent xDerComp = [r = this->rX](const double t) {
    return r * -1 * std::sin(t);
  };
  DerivativeComponent yDerComp = [r = this->rY](const double t) {
    return r * std::cos(t);
  };
  DerivativeComponent zDerComp = [](const double r) { return 0; };
  return {xDerComp, yDerComp, zDerComp};
}
Helix::Helix(const double r, const double step) : r(r), step(step) {}
Helix::Point Helix::GetPointByT(const double t) {
  return {this->r * std::cos(t), this->r * std::sin(t),
          this->step / (2 * M_PI) * t};
}
Helix::Derivative Helix::GetFirstDerivative() {
  DerivativeComponent xDerComp = [r = this->r](const double t) {
    return r * std::cos(t);
  };
  DerivativeComponent yDerComp = [r = this->r](const double t) {
    return r * std::sin(t);
  };
  DerivativeComponent zDerComp = [step = this->step](const double t) {
    return step / (2 * M_PI);
  };
  return {xDerComp, yDerComp, zDerComp};
}
std::unique_ptr<Curve> CreateCircle(const double r) {
  if (r <= 0) {
    throw std::invalid_argument("Radius must be positive. Cur radius value: " +
                                std::to_string(r));
  }
  return std::make_unique<Circle>(r);
}
std::unique_ptr<Curve> CreateEllipse(const double rX, const double rY) {
  if (rX <= 0 || rY <= 0) {
    throw std::invalid_argument(
        "Radiuses must be positive. Cur x radius value: " + std::to_string(rX) +
        ". Cur y radiud value: " + std::to_string(rY));
  }
  return std::make_unique<Ellipse>(rX, rY);
}
std::unique_ptr<Curve> CreateHelix(const double r, const double step) {
  if (r <= 0) {
    throw std::invalid_argument("Radius must be positive. Cur radius value: " +
                                std::to_string(r));
  }
  return std::make_unique<Helix>(r, step);
}
