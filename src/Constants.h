#ifndef CONSTANTS_H__
#define CONSTANTS_H__

#include <cstdint>
#include <array>

namespace Draupnir {

  /**
   * Initial state consisting of all 0s
   *
   */
  extern const std::array<std::uint8_t, 512> zeros;

  /**
   * Initial state consisting of all 1s
   *
   */
  extern const std::array<std::uint8_t, 512> ones;

  /**
   * Initial state consisting of the decimal expansion of e
   *
   * Here, "e" is the Euler constant, the base for natural logarithms.
   *
   */
  extern const std::array<std::uint8_t, 512> e;

  /**
   * Initial state consisting of the decimal expansion of pi
   *
   * Here, "pi" is the ratio of the diameter to the circumference.
   *
   */
  extern const std::array<std::uint8_t, 512> pi;

  /**
   * Initial state consisting of the decimal expansion of gamma
   *
   * Here, "gamma" is the Euler-Mascheroni constant.
   *
   */
  extern const std::array<std::uint8_t, 512> gamma;

  /**
   * Initial state consisting of the decimal expansion of omega
   *
   * Here, "gamma" is W(1), where "W" is Lambert's W function.
   *
   */
  extern const std::array<std::uint8_t, 512> omega;

  /**
   * Initial state consisting of the decimal expansion of 1/e
   *
   * Here, "e" is the Euler constant, the base for natural logarithms.
   *
   */
  extern const std::array<std::uint8_t, 512> invE;

  /**
   * Initial state consisting of the decimal expansion of 1/pi
   *
   * Here, "pi" is the ratio of the diameter to the circumference.
   *
   */
  extern const std::array<std::uint8_t, 512> invPi;

  /**
   * Initial state consisting of the decimal expansion of 1/gamma
   *
   * Here, "gamma" is the Euler-Mascheroni constant.
   *
   */
  extern const std::array<std::uint8_t, 512> invGamma;

  /**
   * Initial state consisting of the decimal expansion of 1/omega
   *
   * Here, "gamma" is W(1), where "W" is Lambert's W function.
   *
   */
  extern const std::array<std::uint8_t, 512> invOmega;

  /**
   * Initial state consisting of the decimal expansion of sqrt(2)
   *
   */
  extern const std::array<std::uint8_t, 512> sqrt2;

  /**
   * Initial state consisting of the decimal expansion of sqrt(3)
   *
   */
  extern const std::array<std::uint8_t, 512> sqrt3;

  /**
   * Initial state consisting of the decimal expansion of sqrt(5)
   *
   */
  extern const std::array<std::uint8_t, 512> sqrt5;

  /**
   * Initial state consisting of the decimal expansion of sqrt(7)
   *
   */
  extern const std::array<std::uint8_t, 512> sqrt7;

  /**
   * Initial state consisting of the decimal expansion of sqrt(11)
   *
   */
  extern const std::array<std::uint8_t, 512> sqrt11;

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(2)
   *
   */
  extern const std::array<std::uint8_t, 512> invSqrt2;

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(3)
   *
   */
  extern const std::array<std::uint8_t, 512> invSqrt3;

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(5)
   *
   */
  extern const std::array<std::uint8_t, 512> invSqrt5;

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(7)
   *
   */
  extern const std::array<std::uint8_t, 512> invSqrt7;

  /**
   * Initial state consisting of the decimal expansion of 1/sqrt(11)
   *
   */
  extern const std::array<std::uint8_t, 512> invSqrt11;

}

#endif /* CONSTANTS_H__ */

