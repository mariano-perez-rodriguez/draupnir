#include "Environment.h"

#include <algorithm>


namespace Draupnir {

/**
 * Construct a new execution environment
 *
 * @param ss  Ostream to use for output
 */
Environment::Environment(std::ostream &stream) noexcept : stack {}, out {stream} {}

/**
 * Remove the given number of elements from the top of the stack
 *
 * @param n  Number of elements to remove
 * @return the resulting Environment
 */
Environment &Environment::drop(std::size_t n) noexcept {
  std::size_t nn = std::max(0ul, std::min(stack.size(), n));
  if (0 != nn) {
    stack.erase(stack.end() - nn, stack.end());
  }
  return *this;
}

/**
 * Copy the given number of elements at the top of the stack the given number of times
 *
 * @param n  Number of times to copy
 * @param m  Number of elements to copy
 * @return the resulting Environment
 */
Environment &Environment::copy(std::size_t n, std::size_t m) noexcept {
  std::size_t mm = std::max(0ul, std::min(stack.size(), m));
  if (0 != mm) {
    for (std::size_t i = 0; i < n; i++) {
      for (std::size_t j = 0; j < mm; j++) {
        stack.push_back(std::unique_ptr<Sponge>(stack[stack.size() - mm + j]->clone()));
      }
    }
  }
  return *this;
}




}

