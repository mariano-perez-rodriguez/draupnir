# Draupnir Test Results

Here we present test results for different configurations of the Draupnir RNG.

## Index

- [Methodology](#methodology)
  - [About the Constants](#about-the-constants)
- [Initial State = _π_](#initial-state--π)
- [Initial State = _e_](#initial-state--e)
- [Initial State = _γ_](#initial-state--γ)
- [Initial State = _Ω_](#initial-state--Ω)
- [Initial State = _1 / π_](#initial-state--1--π)
- [Initial State = _1 / e_](#initial-state--1--e)
- [Initial State = _1 / γ_](#initial-state--1--γ)
- [Initial State = _1 / Ω_](#initial-state--1--Ω)
- [Initial State = _√2_](#initial-state--2)
- [Initial State = _√3_](#initial-state--3)
- [Initial State = _√5_](#initial-state--5)
- [Initial State = _√7_](#initial-state--7)
- [Initial State = _√11_](#initial-state--11)
- [Initial State = _1 / √2_](#initial-state--1--2)
- [Initial State = _1 / √3_](#initial-state--1--3)
- [Initial State = _1 / √5_](#initial-state--1--5)
- [Initial State = _1 / √7_](#initial-state--1--7)
- [Initial State = _1 / √11_](#initial-state--1--11)

* * *

## Methodology

The only parameter changed is the initial state, the width is fixed to 64 bits, the generator is fixed to the ECMA one, the initial value and xoring mask are fixed to the all-1s pattern, the soaking rounds parameter is fixed to 8, and the squeezing rounds parameter is fixed to 1.

The test results are presented as the formatted output of the results of:
````sh
dieharder -a -k 2 -Y 1 -g 201 -f draupnir.samples.bin
````
where `draupnir.samples.bin` is a 1Gb file generated by Draupnir. Only the last result of an ambiguity resolution run is shown. Any failing test is highlighted.

### About the Constants

The following constants (and their inverses) are used to initialize the Draupnir RNG:

- ___π___ : the ratio of circumference to diameter (see [Wikipedia, π](https://en.wikipedia.org/wiki/Pi)),
- ___e___ : the base of the natural logarithms (see [Wikipedia, e](https://en.wikipedia.org/wiki/E_%28mathematical_constant%29)),
- ___γ___ : the Euler-Mascheroni constant (see [Wikipedia, γ](https://en.wikipedia.org/wiki/Euler%E2%80%93Mascheroni_constant)),
- ___Ω___ : the Omega constant (see [Wikipedia, Ω](https://en.wikipedia.org/wiki/Omega_constant))
- ___√2___ : the square root of 2,
- ___√3___ : the square root of 3,
- ___√5___ : the square root of 5,
- ___√7___ : the square root of 7,
- ___√11___ : the square root of 11,

all of them were chosen because they are transcendental (or strongly suspected to be) and non-biased.

## Initial State = _π_


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

## Initial State = _e_

|          Test Name | _N_ | _t_ samples | _p_ samples | _p_-value | Assesment |
|-------------------:|----:|------------:|------------:|:----------|:---------:|
|   diehard_birthdays|    0|          100|          100| 0.26919453|  PASSED   |
|      diehard_operm5|    0|      1000000|          100| 0.16884554|  PASSED   |
|  diehard_rank_32x32|    0|        40000|          100| 0.27581109|  PASSED   |
|    diehard_rank_6x8|    0|       100000|          100| 0.66432281|  PASSED   |
|   diehard_bitstream|    0|      2097152|          100| 0.38439444|  PASSED   |
|        diehard_opso|    0|      2097152|          100| 0.44277254|  PASSED   |
|        diehard_oqso|    0|      2097152|          100| 0.02356951|  PASSED   |
|         diehard_dna|    0|      2097152|          100| 0.33056949|  PASSED   |
|diehard_count_1s_str|    0|       256000|          100| 0.42521477|  PASSED   |
|diehard_count_1s_byt|    0|       256000|          100| 0.61012598|  PASSED   |
| diehard_parking_lot|    0|        12000|          100| 0.68180941|  PASSED   |
|    diehard_2dsphere|    2|         8000|          100| 0.93858769|  PASSED   |
|    diehard_3dsphere|    3|         4000|          100| 0.93666638|  PASSED   |
|     diehard_squeeze|    0|       100000|          100| 0.34322281|  PASSED   |
|        diehard_sums|    0|          100|          100| 0.17972349|  PASSED   |
|        diehard_runs|    0|       100000|          100| 0.82283301|  PASSED   |
|        diehard_runs|    0|       100000|          100| 0.81299791|  PASSED   |
|       diehard_craps|    0|       200000|          100| 0.56909659|  PASSED   |
|       diehard_craps|    0|       200000|          100| 0.62340713|  PASSED   |
| marsaglia_tsang_gcd|    0|     10000000|          100| 0.47039053|  PASSED   |
| marsaglia_tsang_gcd|    0|     10000000|          100| 0.27135941|  PASSED   |
|         sts_monobit|    1|       100000|          100| 0.10086753|  PASSED   |
|            sts_runs|    2|       100000|          100| 0.08037274|  PASSED   |
|          sts_serial|    1|       100000|          100| 0.27081135|  PASSED   |
|          sts_serial|    2|       100000|          100| 0.96820176|  PASSED   |
|          sts_serial|    3|       100000|          100| 0.37270446|  PASSED   |
|          sts_serial|    3|       100000|          100| 0.08237393|  PASSED   |
|          sts_serial|    4|       100000|          100| 0.28586588|  PASSED   |
|          sts_serial|    4|       100000|          100| 0.13058794|  PASSED   |
|          sts_serial|    5|       100000|          100| 0.66968082|  PASSED   |
|          sts_serial|    5|       100000|          100| 0.41646243|  PASSED   |
|          sts_serial|    6|       100000|          100| 0.95666611|  PASSED   |
|          sts_serial|    6|       100000|          100| 0.91748793|  PASSED   |
|          sts_serial|    7|       100000|          100| 0.35199467|  PASSED   |
|          sts_serial|    7|       100000|          100| 0.74086307|  PASSED   |
|          sts_serial|    8|       100000|          100| 0.13796611|  PASSED   |
|          sts_serial|    8|       100000|          100| 0.05069722|  PASSED   |
|          sts_serial|    9|       100000|          100| 0.63581601|  PASSED   |
|          sts_serial|    9|       100000|          100| 0.73722359|  PASSED   |
|          sts_serial|   10|       100000|          100| 0.40833076|  PASSED   |
|          sts_serial|   10|       100000|          100| 0.69209809|  PASSED   |
|          sts_serial|   11|       100000|          100| 0.18833553|  PASSED   |
|          sts_serial|   11|       100000|          100| 0.16783305|  PASSED   |
|          sts_serial|   12|       100000|          100| 0.21845603|  PASSED   |
|          sts_serial|   12|       100000|          100| 0.88669691|  PASSED   |
|          sts_serial|   13|       100000|          100| 0.17429194|  PASSED   |
|          sts_serial|   13|       100000|          100| 0.37132293|  PASSED   |
|          sts_serial|   14|       100000|          100| 0.75666695|  PASSED   |
|          sts_serial|   14|       100000|          100| 0.95090826|  PASSED   |
|          sts_serial|   15|       100000|          100| 0.90038892|  PASSED   |
|          sts_serial|   15|       100000|          100| 0.78530381|  PASSED   |
|          sts_serial|   16|       100000|          100| 0.78676125|  PASSED   |
|          sts_serial|   16|       100000|          100| 0.23208770|  PASSED   |
|         rgb_bitdist|    1|       100000|          100| 0.25127484|  PASSED   |
|         rgb_bitdist|    2|       100000|          100| 0.84999452|  PASSED   |
|         rgb_bitdist|    3|       100000|          100| 0.89771832|  PASSED   |
|         rgb_bitdist|    4|       100000|          100| 0.45441698|  PASSED   |
|         rgb_bitdist|    5|       100000|          100| 0.61429746|  PASSED   |
|         rgb_bitdist|    6|       100000|          100| 0.88113487|  PASSED   |
|         rgb_bitdist|    7|       100000|          100| 0.57974761|  PASSED   |
|         rgb_bitdist|    8|       100000|          100| 0.89529590|  PASSED   |
|         rgb_bitdist|    9|       100000|          100| 0.94565152|  PASSED   |
|         rgb_bitdist|   10|       100000|          100| 0.49196232|  PASSED   |
|         rgb_bitdist|   11|       100000|          100| 0.10108980|  PASSED   |
|         rgb_bitdist|   12|       100000|          200| 0.94697672|  PASSED   |
|rgb_minimum_distance|    2|        10000|         1000| 0.87670249|  PASSED   |
|rgb_minimum_distance|    3|        10000|         1000| 0.18101134|  PASSED   |
|rgb_minimum_distance|    4|        10000|         1000| 0.19003916|  PASSED   |
|rgb_minimum_distance|    5|        10000|         1000| 0.07977120|  PASSED   |
|    rgb_permutations|    2|       100000|          100| 0.56047484|  PASSED   |
|    rgb_permutations|    3|       100000|          100| 0.76166130|  PASSED   |
|    rgb_permutations|    4|       100000|          100| 0.46830372|  PASSED   |
|    rgb_permutations|    5|       100000|          200| 0.75750863|  PASSED   |
|      rgb_lagged_sum|    0|      1000000|          100| 0.97892173|  PASSED   |
|      rgb_lagged_sum|    1|      1000000|          100| 0.76349192|  PASSED   |
|      rgb_lagged_sum|    2|      1000000|          100| 0.40145912|  PASSED   |
|      rgb_lagged_sum|    3|      1000000|          100| 0.89253610|  PASSED   |
|      rgb_lagged_sum|    4|      1000000|          100| 0.95886472|  PASSED   |
|      rgb_lagged_sum|    5|      1000000|          100| 0.41160610|  PASSED   |
|      rgb_lagged_sum|    6|      1000000|          100| 0.87348384|  PASSED   |
|      rgb_lagged_sum|    7|      1000000|          100| 0.81728195|  PASSED   |
|      rgb_lagged_sum|    8|      1000000|          100| 0.94655642|  PASSED   |
|      rgb_lagged_sum|    9|      1000000|          100| 0.77865368|  PASSED   |
|      rgb_lagged_sum|   10|      1000000|          100| 0.32911395|  PASSED   |
|      rgb_lagged_sum|   11|      1000000|          100| 0.76051072|  PASSED   |
|      rgb_lagged_sum|   12|      1000000|          100| 0.85088889|  PASSED   |
|      rgb_lagged_sum|   13|      1000000|          100| 0.73633217|  PASSED   |
|      rgb_lagged_sum|   14|      1000000|          100| 0.81211858|  PASSED   |
|      rgb_lagged_sum|   15|      1000000|          100| 0.79704395|  PASSED   |
|      rgb_lagged_sum|   16|      1000000|          100| 0.35199156|  PASSED   |
|      rgb_lagged_sum|   17|      1000000|          100| 0.32973893|  PASSED   |
|      rgb_lagged_sum|   18|      1000000|          100| 0.13043915|  PASSED   |
|      rgb_lagged_sum|   19|      1000000|          100| 0.21741424|  PASSED   |
|      rgb_lagged_sum|   20|      1000000|          100| 0.07393875|  PASSED   |
|      rgb_lagged_sum|   21|      1000000|          100| 0.94638327|  PASSED   |
|      rgb_lagged_sum|   22|      1000000|          100| 0.30391753|  PASSED   |
|      rgb_lagged_sum|   23|      1000000|          100| 0.59288388|  PASSED   |
|      rgb_lagged_sum|   24|      1000000|          100| 0.81374109|  PASSED   |
|      rgb_lagged_sum|   25|      1000000|          100| 0.22536683|  PASSED   |
|      rgb_lagged_sum|   26|      1000000|          100| 0.87509559|  PASSED   |
|      rgb_lagged_sum|   27|      1000000|          100| 0.85276547|  PASSED   |
|      rgb_lagged_sum|   28|      1000000|          100| 0.25947740|  PASSED   |
|      rgb_lagged_sum|   29|      1000000|          100| 0.53805258|  PASSED   |
|      rgb_lagged_sum|   30|      1000000|          100| 0.84417853|  PASSED   |
|      rgb_lagged_sum|   31|      1000000|          100| 0.22136514|  PASSED   |
|      rgb_lagged_sum|   32|      1000000|          100| 0.65164575|  PASSED   |
|     rgb_kstest_test|    0|        10000|         1000| 0.55696401|  PASSED   |
|     dab_bytedistrib|    0|     51200000|            1| 0.07797385|  PASSED   |
|             dab_dct|  256|        50000|            1| 0.92717333|  PASSED   |
|        dab_filltree|   32|     15000000|            1| 0.08584606|  PASSED   |
|        dab_filltree|   32|     15000000|            1| 0.96272629|  PASSED   |
|       dab_filltree2|    0|      5000000|            1| 0.49029050|  PASSED   |
|       dab_filltree2|    1|      5000000|            1| 0.46930514|  PASSED   |
|        dab_monobit2|   12|     65000000|            1| 0.94792086|  PASSED   |

## Initial State = _γ_

## Initial State = _Ω_

## Initial State = _1 / π_

## Initial State = _1 / e_

## Initial State = _1 / γ_

## Initial State = _1 / Ω_

## Initial State = _√2_

## Initial State = _√3_

## Initial State = _√5_

## Initial State = _√7_

## Initial State = _√11_

## Initial State = _1 / √2_

## Initial State = _1 / √3_

## Initial State = _1 / √5_

## Initial State = _1 / √7_

## Initial State = _1 / √11_
