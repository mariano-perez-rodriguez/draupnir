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
