#ifndef DRAUPNIR_H_
#define DRAUPNIR_H_

#include <cstdint>

namespace Draupnir {

  /**
   * Initial state consisting of all 0s
   *
   */
  extern const std::uint8_t zeros[512];

  /**
   * Initial state consisting of all 1s
   *
   */
  extern const std::uint8_t ones[512];

  /**
   * Initial state consisting of the decimal expansion of e
   *
   * Here, "e" is the Euler constant, the base for natural logarithms.
   *
   */
  extern const std::uint8_t e[512];

  /**
   * Initial state consisting of the decimal expansion of pi
   *
   * Here, "pi" is the ratio of the diameter to the circumference.
   *
   */
  extern const std::uint8_t pi[512];

  /**
   * Initial state consisting of the decimal expansion of gamma
   *
   * Here, "gamma" is the Euler-Mascheroni constant.
   *
   */
  extern const std::uint8_t gamma[512];

  /**
   * Initial state consisting of the decimal expansion of omega
   *
   * Here, "gamma" is W(1), where "W" is Lambert's W function.
   *
   */
  extern const std::uint8_t omega[512];

  /**
   * Initial state consisting of the decimal expansion of 1/e
   *
   * Here, "e" is the Euler constant, the base for natural logarithms.
   *
   */
  extern const std::uint8_t invE[512];

  /**
   * Initial state consisting of the decimal expansion of 1/pi
   *
   * Here, "pi" is the ratio of the diameter to the circumference.
   *
   */
  extern const std::uint8_t invPi[512];

  /**
   * Initial state consisting of the decimal expansion of 1/gamma
   *
   * Here, "gamma" is the Euler-Mascheroni constant.
   *
   */
  extern const std::uint8_t invGamma[512];

  /**
   * Initial state consisting of the decimal expansion of 1/omega
   *
   * Here, "gamma" is W(1), where "W" is Lambert's W function.
   *
   */
  extern const std::uint8_t invOmega[512];

  /**
   * Initial state consisting of the decimal expansion of sqrt(2)
   *
   */
  extern const std::uint8_t sqrt2[512];

  /**
   * Initial state consisting of the decimal expansion of sqrt(3)
   *
   */
  extern const std::uint8_t sqrt3[512];

  /**
   * Initial state consisting of the decimal expansion of sqrt(5)
   *
   */
  extern const std::uint8_t sqrt5[512];

  /**
   * Initial state consisting of the decimal expansion of sqrt(7)
   *
   */
  extern const std::uint8_t sqrt7[512];

  /**
   * Initial state consisting of the decimal expansion of sqrt(11)
   *
   */
  extern const std::uint8_t sqrt11[512];

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(2)
   *
   */
  extern const std::uint8_t invSqrt2[512];

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(3)
   *
   */
  extern const std::uint8_t invSqrt3[512];

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(5)
   *
   */
  extern const std::uint8_t invSqrt5[512];

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(7)
   *
   */
  extern const std::uint8_t invSqrt7[512];

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(11)
   *
   */
  extern const std::uint8_t invSqrt11[512];
}

#endif /* DRAUPNIR_H_ */

