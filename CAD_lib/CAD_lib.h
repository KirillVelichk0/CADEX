#pragma once
#include <functional>
#include <memory>
#include <tuple>
class Curve {
public:
  //! Structure in format x, y, z
  using Point = std::tuple<double, double, double>;
  //! Component that returns some coord value provided by t
  using DerivativeComponent = std::function<double(double)>;
  //! Derivative - vector of polynoms
  using Derivative =
      std::tuple<DerivativeComponent, DerivativeComponent, DerivativeComponent>;
  virtual ~Curve() = default;
  //! Returns point coords provided by t param
  virtual Point GetPointByT(const double t) = 0;
  //! Returns first derivative
  virtual Derivative GetFirstDerivative() = 0;
};

class Circle : public Curve {
private:
  double r;

public:
  Circle(const double r);
  ~Circle() = default;
  Point GetPointByT(const double t) override;
  Derivative GetFirstDerivative() override;
  double GetR() const noexcept;
};

class Ellipse : public Curve {
private:
  double rX;
  double rY;

public:
  Ellipse(const double rX, const double rY);
  ~Ellipse() = default;
  Point GetPointByT(const double t) override;
  Derivative GetFirstDerivative() override;
};

class Helix : public Curve {
private:
  double r;
  double step;

public:
  Helix(const double r, const double step);
  ~Helix() = default;
  Point GetPointByT(const double t) override;
  Derivative GetFirstDerivative() override;
};

//! Since constructors are noexcept according to the standard, and checks are
//! needed, let’s move the checks to factories
std::unique_ptr<Curve> CreateCircle(const double r);
std::unique_ptr<Curve> CreateEllipse(const double rX, const double rY);
std::unique_ptr<Curve> CreateHelix(const double r, const double step);
