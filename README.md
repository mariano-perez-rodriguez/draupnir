# Draupnir
The Draupnir RNG.

- [Quick Start](#quick-start)
- [What's in a name?](#whats-in-a-name)
- [Usage](#usage)
- [How Draupnir Works](#how-draupnir-works)
- [Dieharder Results](#dieharder-results)
- [FAQs](#faqs)
- [Contributing](#contributing)
- [License](#license)

## Quick Start

## What's in a Name?

_Draupnir_ is a mythologcal artifact mentioned in the Norse mythos. To quote [Wikipedia](https://en.wikipedia.org/wiki/Draupnir):

> In Norse mythology, __Draupnir__ (Old Norse "the dripper") is a gold ring possessed by the god Odin with the ability to multiply itself:
> every ninth night, eight new rings 'drip' from Draupnir, each one of the same size and weight as the original.

We took Draupnir's ability to multiply itself as a metaphor for the RNG in question to _split_ according to different sub-salts given. In all
truth, this is a property of the _sponge_ construction, not specific to Draupnir itself, but since the name is as cool as the hypothetical son
of James Bond and Riddick would be, it kinda stuck.

## Usage

## How Draupnir Works

- [The Sponge Construction](#the-sponge-construction)
- [Draupnir's State Change unction](#draupnirs-state-change-function)
- [Draupnir's Output Function](#draupnirs-output-function)

Draupnir is based off of the concept of a _Cryptographic Sponge_ (see: [The Sponge Functions Corner](http://sponge.noekeon.org/)): a construction
that allows for a _reseedable_ and _splittable_ RNG to be built.

One of Draupnir's most central objectives is to be easy to understand and allow for a clean implementation.

### The Sponge Construction

A detailed analysis of the sponge construction is provided in the link above, but, just in case you're lazy, here's a quick summary.

A cryptographic sponge consists of three elements:

- A _state_ : a state is just that, a structure of a given size in bits (call it _t_ ), which is divided in two "parts": the _rate_ (call it _r_ ), and the _capacity_ (call it _c_ ).
- A _state change function_ : a state change function is just a function (call it _f_ ) that, given a state _s_, produces a new state _s' = f(s)_.
- An _output function_ : an output function is a function (call it _g_ ) that, given the "rate" portion of the state _r_, produces the sponge's output _x = g(r)_ ; in "standard" sponges, the output function is usually the identity function.

Now one can perform two operations on one such sponge:

- __Soaking:__ to soak the sponge in a datum _d_ means to replace the "rate" portion of the state with (a suitable padding of) _d_, and apply the state change function to the resulting state.
- __Squeezing:__ to squeeze the sponge means to extract the "rate" portion of the state applying the output function to it, and apply the state change function to the current state.

As an example of the generality of this construction (see the link above for many, _many_, more) note that by having two identical copies of a sponge, and soaking each on a different piece of data, one gets two sponges whose squeeze outputs differ from that point on (this is the property we call "split").

### Draupnir's State Change Function

### Draupnir's Output Function

## Dieharder Results

Draupnir has been tested with `dieharder 3.31.1`, using the following line:

````
dieharder -a -k 2 -Y 1 -g 201 -f draupnir.samples.bin
````

This asks for all tests (`-a`), using the "ks" flag indicating maximum precision (`-k 2`), with a "resolve ambiguity" strategy (`-Y 1`), for a "generator" to be read from a binary file (`-g 201`), which is called `draupnir.samples.bin` (`-f draupnir.samples.bin`).

The _only_ test consistently __failed__ by Draupnir is the one called `marsaglia_tsang_gcd`, on its second iteration only, __all__ the other tests are eventually passed.

Here are the results in a table:

|          Test Name | _N_ | _t_ samples | _p_ samples | _p_-value | Assesment |
|-------------------:|----:|------------:|------------:|:----------|:---------:|
|   diehard_birthdays|    0|          100|          100| 0.69112091|   PASSED  |
|      diehard_operm5|    0|      1000000|          100| 0.39297877|   PASSED  |
|  diehard_rank_32x32|    0|        40000|          100| 0.05465264|   PASSED  |
|    diehard_rank_6x8|    0|       100000|          100| 0.24812367|   PASSED  |
|   diehard_bitstream|    0|      2097152|          100| 0.88774232|   PASSED  |
|        diehard_opso|    0|      2097152|          100| 0.62553574|   PASSED  |
|        diehard_oqso|    0|      2097152|          100| 0.98243507|   PASSED  |
|         diehard_dna|    0|      2097152|          100| 0.73062286|   PASSED  |
|diehard_count_1s_str|    0|       256000|          100| 0.76970084|   PASSED  |
|diehard_count_1s_byt|    0|       256000|          100| 0.74479418|   PASSED  |
| diehard_parking_lot|    0|        12000|          100| 0.61281762|   PASSED  |
|    diehard_2dsphere|    2|         8000|          100| 0.66757201|   PASSED  |
|    diehard_3dsphere|    3|         4000|          100| 0.67702458|   PASSED  |
|     diehard_squeeze|    0|       100000|          100| 0.74950479|   PASSED  |
|        diehard_sums|    0|          100|          100| 0.42129740|   PASSED  |
|        diehard_runs|    0|       100000|          100| 0.55724635|   PASSED  |
|        diehard_runs|    0|       100000|          100| 0.28210197|   PASSED  |
|       diehard_craps|    0|       200000|          100| 0.08124852|   PASSED  |
|       diehard_craps|    0|       200000|          100| 0.43735816|   PASSED  |
| marsaglia_tsang_gcd|    0|     10000000|          100| 0.06376232|   PASSED  |
| __marsaglia_tsang_gcd__|    __0__|     __10000000__|          __200__| __0.00000000__|   __FAILED__  |
|         sts_monobit|    1|       100000|          100| 0.60339553|   PASSED  |
|            sts_runs|    2|       100000|          100| 0.93320042|   PASSED  |
|          sts_serial|    1|       100000|          100| 0.95962887|   PASSED  |
|          sts_serial|    2|       100000|          100| 0.21284345|   PASSED  |
|          sts_serial|    3|       100000|          100| 0.57901961|   PASSED  |
|          sts_serial|    3|       100000|          100| 0.97968337|   PASSED  |
|          sts_serial|    4|       100000|          100| 0.22011444|   PASSED  |
|          sts_serial|    4|       100000|          100| 0.20250975|   PASSED  |
|          sts_serial|    5|       100000|          100| 0.63117000|   PASSED  |
|          sts_serial|    5|       100000|          100| 0.03199571|   PASSED  |
|          sts_serial|    6|       100000|          100| 0.92243202|   PASSED  |
|          sts_serial|    6|       100000|          100| 0.95525059|   PASSED  |
|          sts_serial|    7|       100000|          100| 0.50307147|   PASSED  |
|          sts_serial|    7|       100000|          100| 0.10384985|   PASSED  |
|          sts_serial|    8|       100000|          100| 0.10987669|   PASSED  |
|          sts_serial|    8|       100000|          100| 0.20396988|   PASSED  |
|          sts_serial|    9|       100000|          100| 0.95999701|   PASSED  |
|          sts_serial|    9|       100000|          100| 0.10738426|   PASSED  |
|          sts_serial|   10|       100000|          100| 0.53049162|   PASSED  |
|          sts_serial|   10|       100000|          100| 0.75698803|   PASSED  |
|          sts_serial|   11|       100000|          100| 0.79591744|   PASSED  |
|          sts_serial|   11|       100000|          100| 0.07544543|   PASSED  |
|          sts_serial|   12|       100000|          100| 0.97078771|   PASSED  |
|          sts_serial|   12|       100000|          100| 0.96323051|   PASSED  |
|          sts_serial|   13|       100000|          100| 0.99023566|   PASSED  |
|          sts_serial|   13|       100000|          100| 0.84887682|   PASSED  |
|          sts_serial|   14|       100000|          100| 0.76010138|   PASSED  |
|          sts_serial|   14|       100000|          100| 0.61593083|   PASSED  |
|          sts_serial|   15|       100000|          100| 0.26188842|   PASSED  |
|          sts_serial|   15|       100000|          100| 0.79516113|   PASSED  |
|          sts_serial|   16|       100000|          100| 0.71278072|   PASSED  |
|          sts_serial|   16|       100000|          100| 0.99046023|   PASSED  |
|         rgb_bitdist|    1|       100000|          100| 0.95074089|   PASSED  |
|         rgb_bitdist|    2|       100000|          100| 0.96203775|   PASSED  |
|         rgb_bitdist|    3|       100000|          100| 0.45304210|   PASSED  |
|         rgb_bitdist|    4|       100000|          100| 0.94828504|   PASSED  |
|         rgb_bitdist|    5|       100000|          100| 0.25088161|   PASSED  |
|         rgb_bitdist|    6|       100000|          200| 0.19069530|   PASSED  |
|         rgb_bitdist|    7|       100000|          100| 0.87227971|   PASSED  |
|         rgb_bitdist|    8|       100000|          100| 0.44437447|   PASSED  |
|         rgb_bitdist|    9|       100000|          100| 0.32045887|   PASSED  |
|         rgb_bitdist|   10|       100000|          100| 0.96929463|   PASSED  |
|         rgb_bitdist|   11|       100000|          100| 0.92927031|   PASSED  |
|         rgb_bitdist|   12|       100000|          100| 0.92073328|   PASSED  |
|rgb_minimum_distance|    2|        10000|         1000| 0.97924765|   PASSED  |
|rgb_minimum_distance|    3|        10000|         1000| 0.19475217|   PASSED  |
|rgb_minimum_distance|    4|        10000|         1000| 0.32218774|   PASSED  |
|rgb_minimum_distance|    5|        10000|         1000| 0.17835486|   PASSED  |
|    rgb_permutations|    2|       100000|          100| 0.35165457|   PASSED  |
|    rgb_permutations|    3|       100000|          100| 0.87374184|   PASSED  |
|    rgb_permutations|    4|       100000|          100| 0.96679491|   PASSED  |
|    rgb_permutations|    5|       100000|          100| 0.97765359|   PASSED  |
|      rgb_lagged_sum|    0|      1000000|          100| 0.13012306|   PASSED  |
|      rgb_lagged_sum|    1|      1000000|          100| 0.80064974|   PASSED  |
|      rgb_lagged_sum|    2|      1000000|          100| 0.64547908|   PASSED  |
|      rgb_lagged_sum|    3|      1000000|          100| 0.20528101|   PASSED  |
|      rgb_lagged_sum|    4|      1000000|          100| 0.89607797|   PASSED  |
|      rgb_lagged_sum|    5|      1000000|          100| 0.46156818|   PASSED  |
|      rgb_lagged_sum|    6|      1000000|          100| 0.98153798|   PASSED  |
|      rgb_lagged_sum|    7|      1000000|          100| 0.23957484|   PASSED  |
|      rgb_lagged_sum|    8|      1000000|          100| 0.27447650|   PASSED  |
|      rgb_lagged_sum|    9|      1000000|          100| 0.20741585|   PASSED  |
|      rgb_lagged_sum|   10|      1000000|          100| 0.65248101|   PASSED  |
|      rgb_lagged_sum|   11|      1000000|          100| 0.84000184|   PASSED  |
|      rgb_lagged_sum|   12|      1000000|          100| 0.56591285|   PASSED  |
|      rgb_lagged_sum|   13|      1000000|          100| 0.66743248|   PASSED  |
|      rgb_lagged_sum|   14|      1000000|          100| 0.92192201|   PASSED  |
|      rgb_lagged_sum|   15|      1000000|          100| 0.40021153|   PASSED  |
|      rgb_lagged_sum|   16|      1000000|          100| 0.37060864|   PASSED  |
|      rgb_lagged_sum|   17|      1000000|          100| 0.32956741|   PASSED  |
|      rgb_lagged_sum|   18|      1000000|          100| 0.16922812|   PASSED  |
|      rgb_lagged_sum|   19|      1000000|          100| 0.59807610|   PASSED  |
|      rgb_lagged_sum|   20|      1000000|          100| 0.32537982|   PASSED  |
|      rgb_lagged_sum|   21|      1000000|          100| 0.28214054|   PASSED  |
|      rgb_lagged_sum|   22|      1000000|          100| 0.65505206|   PASSED  |
|      rgb_lagged_sum|   23|      1000000|          100| 0.49961494|   PASSED  |
|      rgb_lagged_sum|   24|      1000000|          100| 0.93415636|   PASSED  |
|      rgb_lagged_sum|   25|      1000000|          100| 0.90394945|   PASSED  |
|      rgb_lagged_sum|   26|      1000000|          100| 0.78311698|   PASSED  |
|      rgb_lagged_sum|   27|      1000000|          100| 0.86744138|   PASSED  |
|      rgb_lagged_sum|   28|      1000000|          100| 0.94472696|   PASSED  |
|      rgb_lagged_sum|   29|      1000000|          100| 0.75428908|   PASSED  |
|      rgb_lagged_sum|   30|      1000000|          100| 0.73513605|   PASSED  |
|      rgb_lagged_sum|   31|      1000000|          100| 0.09351219|   PASSED  |
|      rgb_lagged_sum|   32|      1000000|          100| 0.35163431|   PASSED  |
|     rgb_kstest_test|    0|        10000|         1000| 0.66925515|   PASSED  |
|     dab_bytedistrib|    0|     51200000|            1| 0.10452140|   PASSED  |
|             dab_dct|  256|        50000|            1| 0.88907266|   PASSED  |
|        dab_filltree|   32|     15000000|            1| 0.75331778|   PASSED  |
|        dab_filltree|   32|     15000000|            1| 0.60791940|   PASSED  |
|       dab_filltree2|    0|      5000000|            1| 0.04604818|   PASSED  |
|       dab_filltree2|    1|      5000000|            1| 0.85595577|   PASSED  |
|        dab_monobit2|   12|     65000000|            1| 0.20899930|   PASSED  |


Where only the last result of an ambiguity resolution run is shown and the failing text is highlighted.

## FAQs

- [What Systems does Draupnir Work on?](#what-systems-does-draupnir-work-on)
- [Is Draupnir Cryptographically Secure?](#is-draupnir-cryptographically-secure)
- [How Fast is Draupnir?](#how-fast-is-draupnir)
- [Is Draupnir Recommended for Password Hashing?](#is-draupnir-recommended-for-password-hashing)
- [Can I Use Draupnir in my Commercial Project?](#can-i-use-draupnir-in-my-commercial-project)

Here we present some frequently asked questions about Draupnir.

### What Systems does Draupnir Work on?

Draupnir has been compiled and developed with only Linux in mind, specifically for the `gcc` compiler, although the design per se is, obviously,
platform independent, we do not provide support for other operating systems or environments.

### Is Draupnir Cryptographically Secure?

To be completely honest, we don't know. Some people will feel nervous about the linearity of the operations used in Draupnir, and right they
should. Some people will point out that there's a deliberate information _loss_ in Draupnir when soaking in new input data, and right they are.
The point is that we don't know.

One way or another, it is important to point out that there are very few cases when you actually _need_ a cryptographically secure RNG, most of
the times, a _pseudorandom confusion sequence_ does the job just fine, so you could just use Draupnir in these cases and wait until some brave
soul determines whether it constitutes a cryptographically secure RNG or not.

### How Fast is Draupnir?

In its current implementation (and on my laptop), Draupnir can output roughly 1Mb per second. We're working on making Draupnir faster though.

### Is Draupnir Recommended for Password Hashing?

__A thousand times _NO_.__

Password hashing is a delicate matter, and there are a lot of things to take into account. Draupnir, even with its
relatively slow throughput, is far too fast to provide an adequate time barrier for attacks, furthermore, Draupnir's throughput can be
dramatically increased in an ASIC implementation.

You should use one of the hashes tailored for that role: `pbkdf2`, `bcrypt` or `scrypt` (for a detailed analysis of the password hashing problem
see: [Salted Password Hashing - Doing it Right](https://crackstation.net/hashing-security.htm) by Defuse.ca).

__tl;dr: NO.__

### Can I Use Draupnir in my Commercial Project?

_A priori_, yes, but see the full text of the AGPLv3 (GNU Affero General Public License, version 3) for applicable conditions.

## Contributing

There are a number of ways you can contribute to Draupnir's development:

- Propose new features (in the GitHub issue system).
- Report bugs (in the GitHub issue system, I'm sure there are a lot of these lurking in the shadows).
- Fix bugs (by submitting a pull request).
- Port Draupnir to another platform (although not officially supported now, if portability is not too much of a hassle, it can be provided).
- _Attack it!_ Attacking RNGs is the only sure way we can be certain of their concrete strengths (and weaknesses). Even breaking Draupnir would allow us to further our understanding of the techniques involved.

For a detailed discussion of this last point, see the entry on "strength" on [Ritter's Crypto Glossary _and_  Dictionary of Technical Cryptography](http://www.ciphersbyritter.com/GLOSSARY.HTM#Strength).

## License

Draupnir is free software, distributed under the [GNU Affero General Public License, version 3](https://www.gnu.org/licenses/agpl-3.0.html),
or (at your option) any later version.
