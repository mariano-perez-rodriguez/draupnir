# Draupnir
The Draupnir RNG.

## Index

- [Quick Start](#quick-start)
- [What's in a name?](#whats-in-a-name)
- [Usage](#usage)
 - [Command Line](#command-line)
 - [Library](#library)
- [How Draupnir Works](#how-draupnir-works)
 - [The Sponge Construction](#the-sponge-construction)
 - [Draupnir's State Change Function](#draupnirs-state-change-function)
 - [Draupnir's Output](#draupnirs-output)
 - [Draupnir's Input](#draupnirs-input)
- [Dieharder Results](#dieharder-results)
- [FAQs](#faqs)
 - [What Systems does Draupnir Work on?](#what-systems-does-draupnir-work-on)
 - [Is Draupnir Cryptographically Secure?](#is-draupnir-cryptographically-secure)
 - [How Fast is Draupnir?](#how-fast-is-draupnir)
 - [Is Draupnir Recommended for Password Hashing?](#is-draupnir-recommended-for-password-hashing)
 - [Are there any Test Vectors Available?](#are-there-any-test-vectors-available)
 - [Can I Use Draupnir in my Commercial Project?](#can-i-use-draupnir-in-my-commercial-project)
- [Contributing](#contributing)
- [License](#license)

* * *

## Quick Start

In order to clone the repository, just do:

````sh
git clone https://github.com/mariano-perez-rodriguez/draupnir.git
````

this will create a directory called `draupnir` under the current one, containing the repository.

From there, just do:

````sh
cd draupnir
make
````

to build the `draupnir` binary; you can use `make mode=debug` for a debug build. If everything went well, you will see a new `release/bin` directory. To run draupnir, use:

````sh
release/bin/draupnir
````

and you're done! See the [usage](#usage) section for more information.

## What's in a Name?

_Draupnir_ is a mythologcal artifact mentioned in the Norse mythos. To quote [Wikipedia](https://en.wikipedia.org/wiki/Draupnir):

> In Norse mythology, __Draupnir__ (Old Norse "the dripper") is a gold ring possessed by the god Odin with the ability to multiply itself:
> every ninth night, eight new rings 'drip' from Draupnir, each one of the same size and weight as the original.

We took Draupnir's ability to multiply itself as a metaphor for the RNG in question to _split_ according to different sub-salts given. In all
truth, this is a property of the _sponge_ construction, not specific to Draupnir itself, but since the name is as cool as the hypothetical son
of James Bond and Riddick would be, it kinda stuck.

## Usage

- [Command Line](#command-line)
- [Library](#library)

Draupnir can be used either as a standalone command line program, or as a library component in your own programs (either in source form or as a pre-compiled object).

### Command Line

### Library

In order to use Draupnir in your projects, you must simply include `Draupnir.h` and link against `Draupnir.so` (see [INSTALL.md](./INSTALL.md) for building instructions).

Now you can write:

````cpp
DraupnirCrc64 r = Draupnir::crc64();
````

for the default configuration, or, for instance:

````cpp
DraupnirCrc64 r = Draupnir::crc64().initialState(Draupnir::invGamma);
````

to have Draupnir initialized with _1 / γ_.

If you're running `C++11` or above and want to use the `auto` type specifier you'll need to write:

````cpp
auto r = Draupnir::crc64().build();
````

or

````cpp
auto r = Draupnir::crc64().initialState(Draupnir::invGamma).build();
````

note the `.build()` method call added; otherwise, `r`'s type will be deduced to be `DraupnirCrc64Builder` instead of `DraupnirCrc64` (but, this may be what you want: having a pre-specified builder).

Actually, `Draupnir` acts as a static class, providing named static constants (eg. `Draupnir::invGamma`) and [named constructors](https://isocpp.org/wiki/faq/ctors#named-ctor-idiom) (`crc64` is the only one for now). The named constructors in `Draupnir` each generate an object of type `DraupnirXXXBuilder`, where `XXX` is the "flavor" being constructed (`crc64` in this case), these in turn act as [named parameter](https://isocpp.org/wiki/faq/ctors#named-parameter-idiom) realizations of the "actual" `DraupnirXXX` (`DraupnirCrc64` in this case) object.

## How Draupnir Works

- [The Sponge Construction](#the-sponge-construction)
- [Draupnir's State Change Function](#draupnirs-state-change-function)
- [Draupnir's Output](#draupnirs-output)
- [Draupnir's Input](#draupnirs-input)

Draupnir is based off of the concept of a _Cryptographic Sponge_ (see: [The Sponge Functions Corner](http://sponge.noekeon.org/)): a construction
that allows for a _reseedable_ and _splittable_ RNG to be built; note though, that Draupnir is _not_ a cryptographic sponge in the strictest sense: its "input rate state-space" and "output rate state-space" are not identical.

One of Draupnir's most central objectives is to be easy to understand and allow for a clean implementation.

### The Sponge Construction

A detailed analysis of the sponge construction is provided in the link above, but, just in case you're lazy, here's a quick summary.

A cryptographic sponge consists of two elements:

- A _state_ : a state is just that, a structure of a given size in bits (call it _t_ ), which is divided in two "parts": the _rate_ (call it _r_ ), and the _capacity_ (call it _c_ ).
- A _state change function_ : a state change function is just a function (call it _f_ ) that, given a state _s_, produces a new state _s' = f(s)_.

Now one can perform two operations on one such sponge:

- __Soaking:__ to soak the sponge in a datum _d_ means to replace the "rate" portion of the state with (a suitable padding of) _d_, and apply the state change function to the resulting state.
- __Squeezing:__ to squeeze the sponge means to extract the "rate" portion of the state, and apply the state change function to the current state.

As an example of the generality of this construction (see the link above for many, _many_, more) note that by having two identical copies of a sponge, and soaking each on a different piece of data, one gets two sponges whose squeeze outputs differ from that point on (this is the property we call "split").

### Draupnir's State Change Function

Draupnir's general design allows for a state change function parameterized by a _hash_ function. A hash function _H : **2**<sup>✱</sup> → **2**<sup>k</sup>_ (where ___2___ represents the set containing the numbers 0 and 1) is used to construct a _(k × k)_-bit _state_.

In its current implementation, Draupnir only supports the _crc64_ hash, which takes an arbitrary length string and transforms it into a 64 bit hashed result (nb. we're working on adding additional hashes to Draupnir's repertoire).

Given the hash function _H_, and the _(k × k)_-bit state _S_, Draupnir generates a new _(k × k)_-bit state _T_ as follows:

- let _T_ be a "temporary" _(k × k)_-bit state,
- for _0 ≤ i < k_, do:
 - apply _H_ to the _i_-th row of _S_, store the result as the _i_-th column of _T_,
- overwrite _S_ with _T_.

That's it!

What this state change function does is calculate the hash by _rows_ and store it by _columns_, nothing more.

### Draupnir's Output

### Draupnir's Input

## [Dieharder](http://www.phy.duke.edu/~rgb/General/dieharder.php) Results

Draupnir has been tested with `dieharder 3.31.1`, using the following line:

````sh
dieharder -a -k 2 -Y 1 -g 201 -f draupnir.samples.bin
````

This asks for all tests (`-a`), using the "ks" flag indicating maximum precision (`-k 2`), with a "resolve ambiguity" strategy (`-Y 1`), for a "generator" to be read from a binary file (`-g 201`), which is called `draupnir.samples.bin` (`-f draupnir.samples.bin`), this file is a 1GiB binary file generated by Draupnir.

Draupnir eventually (we say _eventually_ because in ambiguity resolution mode, a single test may be run multiple times until a non-ambiguous determination is reached) passes _all_ the `dieharder` tests in their default configuration.

Here are the results in a table:

|          Test Name | _N_ | _t_ samples | _p_ samples | _p_-value | Assesment |
|-------------------:|----:|------------:|------------:|:----------|:---------:|
|   diehard_birthdays|    0|          100|          100| 0.63064540|  PASSED   |
|      diehard_operm5|    0|      1000000|          100| 0.03515999|  PASSED   |
|  diehard_rank_32x32|    0|        40000|          100| 0.99366480|  PASSED   |
|    diehard_rank_6x8|    0|       100000|          100| 0.81220479|  PASSED   |
|   diehard_bitstream|    0|      2097152|          100| 0.95534811|  PASSED   |
|        diehard_opso|    0|      2097152|          100| 0.94393360|  PASSED   |
|        diehard_oqso|    0|      2097152|          100| 0.98087088|  PASSED   |
|         diehard_dna|    0|      2097152|          100| 0.95769403|  PASSED   |
|diehard_count_1s_str|    0|       256000|          100| 0.49225429|  PASSED   |
|diehard_count_1s_byt|    0|       256000|          100| 0.88281751|  PASSED   |
| diehard_parking_lot|    0|        12000|          100| 0.43004782|  PASSED   |
|    diehard_2dsphere|    2|         8000|          100| 0.51435477|  PASSED   |
|    diehard_3dsphere|    3|         4000|          100| 0.28920569|  PASSED   |
|     diehard_squeeze|    0|       100000|          100| 0.67876168|  PASSED   |
|        diehard_sums|    0|          100|          100| 0.66044170|  PASSED   |
|        diehard_runs|    0|       100000|          100| 0.04674612|  PASSED   |
|        diehard_runs|    0|       100000|          100| 0.98217621|  PASSED   |
|       diehard_craps|    0|       200000|          100| 0.49183776|  PASSED   |
|       diehard_craps|    0|       200000|          100| 0.46006937|  PASSED   |
| marsaglia_tsang_gcd|    0|     10000000|          100| 0.20904964|  PASSED   |
| marsaglia_tsang_gcd|    0|     10000000|          100| 0.01648035|  PASSED   |
|         sts_monobit|    1|       100000|          100| 0.48969331|  PASSED   |
|            sts_runs|    2|       100000|          100| 0.39693806|  PASSED   |
|          sts_serial|    1|       100000|          200| 0.49587339|  PASSED   |
|          sts_serial|    2|       100000|          200| 0.19663377|  PASSED   |
|          sts_serial|    3|       100000|          200| 0.43291004|  PASSED   |
|          sts_serial|    3|       100000|          200| 0.18233658|  PASSED   |
|          sts_serial|    4|       100000|          200| 0.96692485|  PASSED   |
|          sts_serial|    4|       100000|          200| 0.56005169|  PASSED   |
|          sts_serial|    5|       100000|          200| 0.87878990|  PASSED   |
|          sts_serial|    5|       100000|          200| 0.74775083|  PASSED   |
|          sts_serial|    6|       100000|          200| 0.86294971|  PASSED   |
|          sts_serial|    6|       100000|          200| 0.85268807|  PASSED   |
|          sts_serial|    7|       100000|          200| 0.37983973|  PASSED   |
|          sts_serial|    7|       100000|          200| 0.10117355|  PASSED   |
|          sts_serial|    8|       100000|          200| 0.15770631|  PASSED   |
|          sts_serial|    8|       100000|          200| 0.41611920|  PASSED   |
|          sts_serial|    9|       100000|          200| 0.93148930|  PASSED   |
|          sts_serial|    9|       100000|          200| 0.90275330|  PASSED   |
|          sts_serial|   10|       100000|          200| 0.58921179|  PASSED   |
|          sts_serial|   10|       100000|          200| 0.58830610|  PASSED   |
|          sts_serial|   11|       100000|          200| 0.62760477|  PASSED   |
|          sts_serial|   11|       100000|          200| 0.70437632|  PASSED   |
|          sts_serial|   12|       100000|          200| 0.92911851|  PASSED   |
|          sts_serial|   12|       100000|          200| 0.19846138|  PASSED   |
|          sts_serial|   13|       100000|          200| 0.88282809|  PASSED   |
|          sts_serial|   13|       100000|          200| 0.72430544|  PASSED   |
|          sts_serial|   14|       100000|          200| 0.58871871|  PASSED   |
|          sts_serial|   14|       100000|          200| 0.47935487|  PASSED   |
|          sts_serial|   15|       100000|          200| 0.14544557|  PASSED   |
|          sts_serial|   15|       100000|          200| 0.53219509|  PASSED   |
|          sts_serial|   16|       100000|          200| 0.13139076|  PASSED   |
|          sts_serial|   16|       100000|          200| 0.57874754|  PASSED   |
|         rgb_bitdist|    1|       100000|          100| 0.42567409|  PASSED   |
|         rgb_bitdist|    2|       100000|          100| 0.55714722|  PASSED   |
|         rgb_bitdist|    3|       100000|          100| 0.66063937|  PASSED   |
|         rgb_bitdist|    4|       100000|          100| 0.26377560|  PASSED   |
|         rgb_bitdist|    5|       100000|          100| 0.12805612|  PASSED   |
|         rgb_bitdist|    6|       100000|          100| 0.47967016|  PASSED   |
|         rgb_bitdist|    7|       100000|          100| 0.14175432|  PASSED   |
|         rgb_bitdist|    8|       100000|          100| 0.97145223|  PASSED   |
|         rgb_bitdist|    9|       100000|          100| 0.40135356|  PASSED   |
|         rgb_bitdist|   10|       100000|          100| 0.32587425|  PASSED   |
|         rgb_bitdist|   11|       100000|          100| 0.98519018|  PASSED   |
|         rgb_bitdist|   12|       100000|          100| 0.29674658|  PASSED   |
|rgb_minimum_distance|    2|        10000|         1000| 0.76972901|  PASSED   |
|rgb_minimum_distance|    3|        10000|         1000| 0.93211566|  PASSED   |
|rgb_minimum_distance|    4|        10000|         1000| 0.39127666|  PASSED   |
|rgb_minimum_distance|    5|        10000|         1000| 0.11212254|  PASSED   |
|    rgb_permutations|    2|       100000|          100| 0.72450965|  PASSED   |
|    rgb_permutations|    3|       100000|          100| 0.22921651|  PASSED   |
|    rgb_permutations|    4|       100000|          100| 0.34243965|  PASSED   |
|    rgb_permutations|    5|       100000|          100| 0.60468421|  PASSED   |
|      rgb_lagged_sum|    0|      1000000|          100| 0.81703915|  PASSED   |
|      rgb_lagged_sum|    1|      1000000|          100| 0.45637948|  PASSED   |
|      rgb_lagged_sum|    2|      1000000|          100| 0.95207442|  PASSED   |
|      rgb_lagged_sum|    3|      1000000|          100| 0.80228102|  PASSED   |
|      rgb_lagged_sum|    4|      1000000|          100| 0.39828888|  PASSED   |
|      rgb_lagged_sum|    5|      1000000|          100| 0.20938165|  PASSED   |
|      rgb_lagged_sum|    6|      1000000|          100| 0.56671011|  PASSED   |
|      rgb_lagged_sum|    7|      1000000|          100| 0.08812106|  PASSED   |
|      rgb_lagged_sum|    8|      1000000|          100| 0.17108848|  PASSED   |
|      rgb_lagged_sum|    9|      1000000|          100| 0.31404455|  PASSED   |
|      rgb_lagged_sum|   10|      1000000|          100| 0.98738722|  PASSED   |
|      rgb_lagged_sum|   11|      1000000|          100| 0.51733467|  PASSED   |
|      rgb_lagged_sum|   12|      1000000|          100| 0.91767471|  PASSED   |
|      rgb_lagged_sum|   13|      1000000|          100| 0.33031728|  PASSED   |
|      rgb_lagged_sum|   14|      1000000|          100| 0.32253236|  PASSED   |
|      rgb_lagged_sum|   15|      1000000|          100| 0.53337340|  PASSED   |
|      rgb_lagged_sum|   16|      1000000|          100| 0.67937772|  PASSED   |
|      rgb_lagged_sum|   17|      1000000|          100| 0.25573759|  PASSED   |
|      rgb_lagged_sum|   18|      1000000|          100| 0.60761161|  PASSED   |
|      rgb_lagged_sum|   19|      1000000|          100| 0.22868094|  PASSED   |
|      rgb_lagged_sum|   20|      1000000|          100| 0.46505306|  PASSED   |
|      rgb_lagged_sum|   21|      1000000|          100| 0.56312916|  PASSED   |
|      rgb_lagged_sum|   22|      1000000|          100| 0.48896176|  PASSED   |
|      rgb_lagged_sum|   23|      1000000|          100| 0.06160357|  PASSED   |
|      rgb_lagged_sum|   24|      1000000|          100| 0.71473587|  PASSED   |
|      rgb_lagged_sum|   25|      1000000|          100| 0.98301624|  PASSED   |
|      rgb_lagged_sum|   26|      1000000|          100| 0.20179028|  PASSED   |
|      rgb_lagged_sum|   27|      1000000|          100| 0.86533400|  PASSED   |
|      rgb_lagged_sum|   28|      1000000|          100| 0.63597088|  PASSED   |
|      rgb_lagged_sum|   29|      1000000|          100| 0.70753809|  PASSED   |
|      rgb_lagged_sum|   30|      1000000|          100| 0.21715355|  PASSED   |
|      rgb_lagged_sum|   31|      1000000|          100| 0.00699472|  PASSED   |
|      rgb_lagged_sum|   32|      1000000|          100| 0.57913639|  PASSED   |
|     rgb_kstest_test|    0|        10000|         1000| 0.50575968|  PASSED   |
|     dab_bytedistrib|    0|     51200000|            1| 0.52505240|  PASSED   |
|             dab_dct|  256|        50000|            1| 0.60605756|  PASSED   |
|        dab_filltree|   32|     15000000|            1| 0.16824354|  PASSED   |
|        dab_filltree|   32|     15000000|            1| 0.04785636|  PASSED   |
|       dab_filltree2|    0|      5000000|            1| 0.09302336|  PASSED   |
|       dab_filltree2|    1|      5000000|            1| 0.10770671|  PASSED   |
|        dab_monobit2|   12|     65000000|            1| 0.07515807|  PASSED   |

Where only the last result of an ambiguity resolution run is shown.

See [doc/RESULTS.md](doc/RESULTS.md) for more.

## FAQs

- [What Systems does Draupnir Work on?](#what-systems-does-draupnir-work-on)
- [Is Draupnir Cryptographically Secure?](#is-draupnir-cryptographically-secure)
- [How Fast is Draupnir?](#how-fast-is-draupnir)
- [Is Draupnir Recommended for Password Hashing?](#is-draupnir-recommended-for-password-hashing)
- [Are there any Test Vectors Available?](#are-there-any-test-vectors-available)
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

In its current implementation (and on my laptop), Draupnir can output roughly between 1Mb and 1.3Mb per second. We're working on making Draupnir faster though.

Note though, that a hardware implementation would be orders of magnitude faster, since most of the transition operations are heavily parallelizable.

### Is Draupnir Recommended for Password Hashing?

__A thousand times _NO_.__

Password hashing is a delicate matter, and there are a lot of things to take into account. Draupnir, even with its
relatively slow throughput, is far too fast to provide an adequate time barrier for attacks, furthermore, Draupnir's throughput can be
dramatically increased in an ASIC implementation.

You should use one of the hashes tailored for that role: `pbkdf2`, `bcrypt` or `scrypt` (for a detailed analysis of the password hashing problem
see: [Salted Password Hashing - Doing it Right](https://crackstation.net/hashing-security.htm) by Defuse.ca).

__tl;dr: NO.__

### Are there any Test Vectors Available?

Here are the first 1024 bytes generated using the default configuration (ECMA generator, all-1s initial value, all-1s xoring mask, 8 soaking rounds, 1 squeezing round, and π initial state):

````
6f60f4f0 a8909e47 edfe5bac 31d1057d 21bf17a1 70154574 dba6fba7 aa7a75d6
09bd6301 33b534cb b9c1038d 57f5f72d 7e08ef5a 9b147a51 402df398 1ad3f669
67a098f6 56d37e6f 936dec6b 59111010 ce2d74a3 18b10ff4 2b380072 00c04cf1
2c353bb7 84fc798c eaf7662a ff20f383 67b6a1eb 5f4eb59e ba1b5f2e 1ad09b1c
b2636438 dd6e9616 fa866131 68005b9a 69d9eea2 b2655f6b 2234cc0f e77dcb37
a1a2c1c1 1dd59835 b2ce42c2 947665f0 bfef306a 9aa77759 ba1e57d3 27a10281
f8d24598 e6b61354 93faffa0 ff82d09c 86abee74 a22e3850 4f44db41 52300256
1d97a271 e6f21292 129dc83f ecf465c0 e9ebaab7 2a090f49 4a535139 fa0fa739
00ee1551 6756ef89 16e95962 5ba94ebc e50e3fb9 3a335199 022d8a9d 3fb50fbc
2ff954b0 0f588015 8c98acb7 c58db2f7 8727e42f 260025ad 43843075 8282c9dc
609a3052 8e71c42a 37c62aba 95e15792 d26079e4 dfaf41ae 1b02b608 e06c3529
cec44b7a d0f866bb 2a2aa4ef 3dea9d06 b68e6f3b 1b0d05bf 533daa7c dec2e98f
b831c530 44df4a1f 871e97bd 1399721e 98c35b39 b14babd7 f5cdf09f 5c29c30e
1076e409 f9e82015 711fc0d8 02cc4c7a 2e2d0cfe f237c614 9d697803 3839256c
dffde3b0 10dfa6cd 62bee1a0 bca9edc5 d0038145 28d7bab6 0443430a ef6bf16c
87288399 76cc9b5f 8ce1a73a 9235cdf9 bad41483 a95aad35 f6e174a7 6d0021f0
f3ca8462 cf18beed 06ccffff 60b9d16b f1cda774 e8492459 ea68fb6e 80c7b931
0b1fb35e 39bc5ef2 f2713262 aafe0fed 0319f677 17f92168 9a481526 888cf7f3
7f6cc77a 631907f6 cf186d31 23ce972d b75e5b05 90527ee0 cf219155 9a855373
ca6383a9 34bafe91 94883d03 65ed4d1f 8bf36934 3d0ecb16 75724d02 d4baeb68
94ed9173 968549a4 0dfe73c6 fdbc0294 07c5bcfa 481d1858 0c643c62 8d9da082
4a3574f5 96a95c34 0d96351f 476cda9a 1331f36c abf255f8 3e780f4f 23ba1cbc
11c7e9c8 caefa821 c4ab8269 fdbc3956 acae2208 cd0507fb ca72d0e6 52e2c069
f9559380 47c72f6f a52bdbc8 246ad5e2 d15f694d add0dc67 276f3d66 f0215bd5
35c742e0 8f8ef55b 69e9b883 923f8fd6 351a8f03 a28cf6c7 8f5e59fc 771fcd94
77928d42 435f7ef5 4629157e 2a710bce a0c8af6d 0c619f9f bcae35f2 37763114
a66d7f23 7d7bcdb2 312ee495 8500144a aeb4c31b fec4ac0a c7c33783 b46194e3
75649902 e56f33ce 7b90bbc4 2b833dda 55ec2967 5db5503a 517a1ac1 56ed382b
511dea3c f11fa280 23f932d5 54b5a6ef a0172394 1e26f4e3 bdffd6f9 48e65f96
9022b3b6 b70fb714 e0c73276 1a8728b4 832566b8 8a10fe65 ee8f97ab a891b63c
658cf4ec ec8db780 9773bb7c c6349618 e686c705 894e6ba3 46d61bb1 303bcf90
4e399c0d f7a7fdef 20ba8e24 a0c885a6 eea4b561 7ee3d124 9fc9cfd0 a46f2016
````
grouped in bundles of 32 bits.

See [doc/TESTVECTORS.md](doc/TESTVECTORS.md) for more.

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

See the file [LICENSE.md](./LICENSE.md) for the full text.
