#ifndef RANDOM_HPP__
#define RANDOM_HPP__

#include <stack>

#include "Random.h"

namespace {

  /**
   * Extract a random number of the templated length from the given sponge
   *
   * @param s  Sponge to use for randomization
   * @return a random number fitting in the templated length
   */
  template <typename T>
  T rand(Draupnir::Sponge &s) {
    T result = static_cast<T>(0);
    for (std::size_t i = 0; i < std::numeric_limits<T>::digits; i += 8) {
      result = static_cast<T>((result << 8) | s.squeeze());
    }
    return result;
  }

  /**
   * Determine whether the given vector holds a derangement
   *
   * This function assumes that the vector holds a permutation of the numbers
   * from 0 to size - 1.
   *
   * @param x  The vector to check
   * @return true if x[i] != i holds for every 0 <= i < size
   */
  bool isDerangement(std::vector<std::size_t> const &x) {
    for (std::size_t i = 0; i < x.size(); i++) {
      if (x[i] == i) {
        return false;
      }
    }
    return true;
  }

}

namespace Draupnir {

  /**
   * Extract a random number between 0 and the given limit of the templated length from the given sponge
   *
   * @param s  Sponge to use for randomization
   * @param high  Highest possible value to return
   * @return a random number between 0 and the given limit fitting in the templated length
   */
  template <typename T>
  T natural(Draupnir::Sponge &s, T const high) {
    T result = rand<T>(s);

    if (high != std::numeric_limits<T>::max()) {
      T delta = static_cast<T>(high + 1);
      T limit = static_cast<T>(std::numeric_limits<T>::max() - (std::numeric_limits<T>::max() % delta));
      while (result >= limit) {
        result = rand<T>(s);
      }
      result = result % delta;
    }

    return result;
  }

  /**
   * Generate a random real value between 0 and 1
   *
   * @param s  Sponge to use for randomization
   * @return the real number generated
   */
  long double real(Draupnir::Sponge &s) {
    return static_cast<long double>(natural<std::uint64_t>(s)) / static_cast<long double>(std::numeric_limits<std::uint64_t>::max());
  }

  /**
   * Generate a random permutation of the given size
   *
   * This function generates a random permutation of the given size using the
   * Fisher--Yates shuffling algorithm; the permutation's elements will be the
   * numbers between 0 and size - 1 inclusive.
   *
   * @param s  Sponge to use for randomization
   * @param size  Permutation size
   * @return a std::vector containing the generated permutation
   */
  std::vector<std::size_t> permutation(Draupnir::Sponge &s, std::size_t const size) {
    std::vector<std::size_t> result;
    result.reserve(size);
    for (std::size_t i = 0; i < size; i++) {
      std::size_t j = natural<std::size_t>(s, i);
      if (j != i) {
        result[i] = result[j];
      }
      result[j] = i;
    }
    return result;
  }

  /**
   * Generate a random cyclic permutation of the given size
   *
   * This function generates a random permutation of the given size using the
   * Sattolo shuffling algorithm; the permutation's elements will be the
   * numbers between 0 and size - 1 inclusive.
   *
   * @param s  Sponge to use for randomization
   * @param size  Permutation size
   * @return a std::vector containing the generated permutation
   */
  std::vector<std::size_t> cycle(Draupnir::Sponge &s, std::size_t const size) {
    std::vector<std::size_t> result;
    result.reserve(size);
    result[0] = 0;
    for (std::size_t i = 1; i < size; i++) {
      std::size_t j = natural<std::size_t>(s, i - 1);
      if (j != i) {
        result[i] = result[j];
      }
      result[j] = i;
    }
    return result;
  }

  /**
   * Generate a random derangement of the given size
   *
   * This function generates a random permutation of the given size using the
   * Fisher--Yates shuffling algorithm and applying rejection to the result;
   * the derangement's elements will be the numbers between 0 and size - 1
   * inclusive.
   *
   * @param s  Sponge to use for randomization
   * @param size  Permutation size
   * @return a std::vector containing the generated permutation
   */
  std::vector<std::size_t> derangement(Draupnir::Sponge &s, std::size_t const size) {
    std::vector<std::size_t> result = permutation(s, size);
    while (!isDerangement(result)) {
      result = permutation(s, size);
    }
    return result;
  }

  /**
   * Generate a uniform sampling with replacement (ie. simply a vector of random naturals)
   *
   * @param s  Sponge to use for randomization
   * @param total  Total number to sample from
   * @param size  Sample size to generate
   * @return a vector holding the sample
   */
  std::vector<std::size_t> uniformSamplingWithReplacement(Draupnir::Sponge &s, std::size_t const total, std::size_t const size) {
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < size; i++) {
      result[i] = natural<std::size_t>(s, total);
    }
    return result;
  }

  /**
   * Generate a uniform sampling without replacement using reservoir sampling
   *
   * @param s  Sponge to use for randomization
   * @param total  Total number to sample from
   * @param size  Sample size to generate
   * @return a vector holding the sample
   */
  std::vector<std::size_t> uniformSamplingWithoutReplacement(Draupnir::Sponge &s, std::size_t const total, std::size_t const size) {
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < size; i++) {
      result[i] = i;
    }
    for (std::size_t i = size; i < total; i++) {
      std::size_t j = natural<std::size_t>(s, i);
      if (j < size) {
        result[j] = i;
      }
    }
    return result;
  }

  /**
   * Generate a non-uniform sampling with replacement (ie. simply a vector of number yielded from a Vose method)
   *
   * @param s  Sponge to use for randomization
   * @param parts  Distribution specified as parts-to-parts
   * @param size  Sample size to generate
   * @return a vector holding the sample
   */
  std::vector<std::size_t> nonUniformSamplingWithReplacement(Draupnir::Sponge &s, std::vector<std::size_t> const parts, std::size_t const size) {
    // copy parts to weights, set multiplicities to 1, and calculate total weight
    std::vector<std::size_t> weight, alias, mult;
    std::size_t num = parts.size(), total = 0;
    for (std::size_t i = 0; i < num; i++) {
      weight[i] = parts[i];
      mult[i] = 1;
      total += weight[i];
    }
    // separate large and small weights
    std::stack<std::size_t> small, large;
    for (std::size_t i = 0; i < num; i++) {
      if (num * weight[i] < total * mult[i]) {
        small.push(i);
      } else {
        large.push(i);
      }
    }
    // perform alias building proper
    while (!small.empty() && !large.empty()) {
      std::size_t l = small.top(); small.pop();
      std::size_t g = large.top(); large.pop();
      alias[l] = g;
      weight[g] += weight[l]; mult[g]++;
      if (num * weight[g] < total * mult[g]) {
        small.push(g);
      } else {
        large.push(g);
      }
    }
    // generate "size" elements
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < size; i++) {
      std::size_t x = natural<std::size_t>(s, num);
      if (total * (real(s) + mult[x]) < num * weight[x]) {
        result[i] = x;
      } else {
        result[i] = alias[x];
      }
    }
    return result;
  }

  /**
   * Generate a non-uniform sampling without replacement using Chao's method
   *
   * @param s  Sponge to use for randomization
   * @param parts  Distribution specified as parts-to-parts
   * @param size  Sample size to generate
   * @return a vector holding the sample
   */
  std::vector<std::size_t> nonUniformSamplingWithoutReplacement(Draupnir::Sponge &s, std::vector<std::size_t> const parts, std::size_t const size) {
    std::vector<std::size_t> result;
    std::size_t sum = 0;
    for (std::size_t i = 0; i < size; i++) {
      result[i] = i;
      sum += parts[i];
    }
    for (std::size_t i = size; i < parts.size(); i++) {
      if (sum * real(s) <= parts[i]) {
        result[natural<std::size_t>(s, size - 1)] = i;
      }
      sum += parts[i];
    }
    return result;
  }

}

#endif /* RANDOM_HPP__ */

