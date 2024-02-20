#include "CAD_lib/CAD_lib.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <memory>
#include <omp.h>
#include <random>
#include <sstream>
#include <vector>
int main(int argc, char *argv[]) {
  int N = 10;
  if (argc == 2) {
    std::istringstream ss(argv[1]);
    ss >> N;
    if (N <= 0 || ss.bad()) {
      std::exit(1);
    }
  }
  std::vector<std::shared_ptr<Curve>> curves(N);
#pragma omp parallel
  {
#pragma omp for
    {
      for (int i = 0; i < N; i++) {
        std::int64_t seed = std::chrono::high_resolution_clock::now()
                                .time_since_epoch()
                                .count();
        std::mt19937_64 generator(seed);
        std::uniform_int_distribution curveDistr(1, 3);
        auto curveId = curveDistr(generator);
        std::uniform_real_distribution<> radiusDistr(0.01, 10000);

        std::shared_ptr<Curve> curve;
        switch (curveId) {
        case 1:
          curve = CreateCircle(radiusDistr(generator));
          break;
        case 2:
          curve = CreateEllipse(radiusDistr(generator), radiusDistr(generator));
          break;
        case 3: {
          std::uniform_real_distribution<> stepDistr(-1000, 1000);
          curve = CreateHelix(radiusDistr(generator), stepDistr(generator));
        } break;
        }
        curves[i] = curve;
      }
    }
#pragma omp barrier
  }
  for (auto &curve : curves) {
    auto [x, y, z] = curve->GetPointByT(M_PI_4);
    auto [derivX, derivY, derivZ] = curve->GetFirstDerivative();
    auto derivXVal = derivX(M_PI_4);
    auto derivYVal = derivY(M_PI_4);
    auto derivZVal = derivZ(M_PI_4);

    std::cout << "Point value is: " << x << ":" << y << ":" << z
              << ", first derivative point value is: " << derivXVal << ":"
              << derivYVal << ":" << derivZVal << std::endl;
  }
  std::vector<std::shared_ptr<Circle>> circles;

#pragma omp parallel
  {
#pragma omp for
    {
      for (int i = 0; i < N; i++) {
        auto curve = curves[i];
        if (std::shared_ptr<Circle> circle =
                std::dynamic_pointer_cast<Circle>(curve);
            circle != nullptr) {
#pragma omp critical(circles)
          { circles.push_back(circle); }
        }
      }
    }
#pragma omp barrier
  }
  //! Just use C++ 17 feature
  std::sort(std::execution::par_unseq, circles.begin(), circles.end(),
            [](auto l, auto r) { return l->GetR() < r->GetR(); });
  double sum = 0;
#pragma omp parallel reduction(+ : sum)
  {
#pragma omp for
    for (int i = 0; i < circles.size(); ++i)
      sum += circles[i]->GetR();
  }

  return 0;
}
