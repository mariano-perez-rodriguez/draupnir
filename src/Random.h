#ifndef RANDOM_H__
#define RANDOM_H__

#include <limits>
#include <vector>

#include "Sponge.h"

namespace Draupnir {

  namespace Random {

    /**
     * Extract a random number between 0 and the given limit of the templated length from the given sponge
     *
     * @param s  Sponge to use for randomization
     * @param high  Highest possible value to return
     * @return a random number between 0 and the given limit fitting in the templated length
     */
    template <typename T>
    T natural(Draupnir::Sponge &s, T const high = std::numeric_limits<T>::max());

    /**
     * Generate a random real value between 0 and 1
     *
     * @param s  Sponge to use for randomization
     * @return the real number generated
     */
    long double real(Draupnir::Sponge &s);

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
    std::vector<std::size_t> permutation(Draupnir::Sponge &s, std::size_t const size);

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
    std::vector<std::size_t> cycle(Draupnir::Sponge &s, std::size_t const size);

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
    std::vector<std::size_t> derangement(Draupnir::Sponge &s, std::size_t const size);

    /**
     * Generate a uniform sampling with replacement (ie. simply a vector of random naturals)
     *
     * @param s  Sponge to use for randomization
     * @param total  Total number to sample from
     * @param size  Sample size to generate
     * @return a vector holding the sample
     */
    std::vector<std::size_t> uniformSampleWithReplacement(Draupnir::Sponge &s, std::size_t const total, std::size_t const size);

    /**
     * Generate a uniform sampling without replacement using reservoir sampling
     *
     * @param s  Sponge to use for randomization
     * @param total  Total number to sample from
     * @param size  Sample size to generate
     * @return a vector holding the sample
     */
    std::vector<std::size_t> uniformSampleWithoutReplacement(Draupnir::Sponge &s, std::size_t const total, std::size_t const size);

    /**
     * Generate a non-uniform sampling with replacement (ie. simply a vector of number yielded from a Vose method)
     *
     * @param s  Sponge to use for randomization
     * @param parts  Distribution specified as parts-to-parts
     * @param size  Sample size to generate
     * @return a vector holding the sample
     */
    std::vector<std::size_t> nonUniformSampleWithReplacement(Draupnir::Sponge &s, std::vector<std::size_t> const parts, std::size_t const size);

    /**
     * Generate a non-uniform sampling without replacement using Chao's method
     *
     * @param s  Sponge to use for randomization
     * @param parts  Distribution specified as parts-to-parts
     * @param size  Sample size to generate
     * @return a vector holding the sample
     */
    std::vector<std::size_t> nonUniformSampleWithoutReplacement(Draupnir::Sponge &s, std::vector<std::size_t> const parts, std::size_t const size);

  }

}

#include "Random.hpp"

#endif /* RANDOM_H__ */

