# Model info

Model: USS-DBS28-30
Series No: USS-DBS2203176

# Terminal settings

```
port is        : /dev/ttyUSB0
flowcontrol    : none
baudrate is    : 9600
parity is      : none
databits are  : 8
stopbits are  : 1
escape is      : C-a
local echo is  : no
noinit is      : no
noreset is    : no
hangup is      : no
nolock is      : no
send_cmd is    : sz -vv
receive_cmd is : rz -vv -E
imap is        :
omap is        :
emap is        : crcrlf,delbs,
logfile is    : none
initstring    : none
exit_after is  : not set
exit is        : no
```

# Data format

In "raw" mode, a series of measurements will look like:

```
+    307.63g 
+    307.62g 
+    307.63g 
```

If you convert ASCII characters to hex, you'll see the following:

```
[2b][20][20][20][20][20][20][20][30][2e][30][30][67][20][20]
[2b][20][20][20][20][20][20][20][30][2e][30][30][67][20][20]
[2b][20][20][20][20][20][20][20][30][2e][30][30][67][20][20]
```

There's 15 bytes of data, plus 1 byte for the carriage return and then another byte for the newline, for **17 bytes total**.

(The manual incorrectly states that there are 14 bytes)

Note that:

* All measurements begin with either a "+" or "-", even a zero measurement
* The unit description is 3 characters max, and always appears immediately after the last digit

# Units

According to the manual, the supported unit descriptions are: g, kg, ct, T, TAR, dr, PKT, GN, TMR, gsm, tlJ, mo, dwt, oz, lb, tlT, ozt, tlH, %

Below is a table of these units. Since the full unit name is never listed in the manual, there are a few units that I'm unable to identify.

```
| Unit Abbreviation | Unit name if known, "N/A" otherwise | Information about unit                                              |
|-------------------|-------------------------------------|---------------------------------------------------------------------|
| g                 | gram                                | https://en.wikipedia.org/wiki/Gram                                  |
| kg                | kilogram                            | https://en.wikipedia.org/wiki/Kilogram                              |
| ct                | carat                               | https://en.wikipedia.org/wiki/Carat_(mass)                          |
| T                 | tola                                | https://en.wikipedia.org/wiki/Tola_(unit)                           |
| TAR               | N/A                                 |                                                                     |
| dr                | dram                                | https://en.wikipedia.org/wiki/Dram_(unit)                           |
| PKT               | N/A                                 |                                                                     |
| GN                | grain                               | https://en.wikipedia.org/wiki/Grain_(unit)                          |
| TMR               | N/A                                 |                                                                     |
| gsm               | N/A                                 |                                                                     |
| tlJ               | tael (Japan/China)                  | https://en.wikipedia.org/wiki/Tael                                  |
| mo                | momme                               | https://en.wikipedia.org/wiki/Japanese_units_of_measurement#Momme   |
| dwt               | pennyweight                         | https://en.wikipedia.org/wiki/Pennyweight                           |
| oz                | ounce                               | https://en.wikipedia.org/wiki/Ounce#International_avoirdupois_ounce |
| lb                | pound                               | https://en.wikipedia.org/wiki/Pound_(mass)                          |
| tlT               | tael (Taiwan)                       | https://en.wikipedia.org/wiki/Tael                                  |
| ozt               | troy ounce                          | https://en.wikipedia.org/wiki/Troy_weight                           |
| tlH               | tael (Hong Kong)                    | https://en.wikipedia.org/wiki/Tael                                  |
| '%'               | N/A                                 |                                                                     |
```

Of the 19 supported units, 5 are unknown.

In addition to the supported units, my program also allows measurements to be shown in milligrams and centigrams. This brings the total number of supported units to 16.

Below is the conversion table for each unit.

```
| -                   | Gram (g)            | Milligram (mg)       | Centigram (cg)       | Kilogram (kg)           | Carats (ct)            | Tola (T)           | TAR ??? | Dram (dr)           | PKT ??? | Grain (gn)           | TMR ??? | Grammage (GSM) ??? | Tael Japan (tlJ)        | Momme (mo)         | Pennyweight (dwt)  | Ounces (oz)            | Pounds (lb)                | Tael Taiwan (tlT)      | Troy Ounce (ozt)          | Tael Hongkong (tlH)     |
|---------------------|---------------------|----------------------|----------------------|-------------------------|------------------------|--------------------|---------|---------------------|---------|----------------------|---------|--------------------|-------------------------|--------------------|--------------------|------------------------|----------------------------|------------------------|---------------------------|-------------------------|
| Gram (g)            | 1                   | 1000 mg/g            | 100 cg/g             | 0.001 kg/g              | 5 ct/g                 | 11.6638038 T/g     | ???     | 1.77184519 dr/g     | ???     | 0.0647989 gn/g       | ???     | ???                | 50 tlJ/g                | 3.75 mo/g          | 0.6430149 dwt/g    | 0.035274 oz/g          | 0.0022 lb/g                | 37.5 tlT/g             | 0.0321507432 ozt/g        | 37.799364169 tlH/g      |
| Milligram (mg)      | 0.001 g/mg          | 1                    | 0.1 cg/mg            | 0.000001 kg/mg          | 0.005 ct/mg            | 0.0116638 T/mg     | ???     | 0.0017718 dr/mg     | ???     | 6.47989 gn/mg        | ???     | ???                | 0.05 tlJ/mg             | 0.00375 mo/mg      | 6.43014 dwt/mg     | 3.52740 * 1^(-5) oz/mg | 2.20462 * 1^(-6) lb/mg     | 0.0375 tlT/mg          | 0.03110348 ozt/mg         | 0.0378 tlH/mg           |
| Centigram (cg)      | 0.01 g/cg           | 10 mg/cg             | 1                    | 0.00001 kg/cg           | 0.05 ct/cg             | 0.116638 T/cg      | ???     | 0.01771845 dr/cg    | ???     | 6.47989 gn/cg        | ???     | ???                | 0.5 tlJ/cg              | 0.0375 mo/cg       | 0.00643 dwt/cg     | 3.5274 * 1^(-4) oz/cg  | 2.20462 * 1^(-5) lb/cg     | 0.375 tlT/cg           | 0.3110348 ozt/cg          | 0.37799366 tlH/cg       |
| Kilogram (kg)       | 1000 g/kg           | 0.000001 mg/kg       | 100,000 cg/kg        | 1                       | 5,000 ct/kg            | 11,663.8038 T/kg   | ???     | 1,771.8451953 dr/kg | ???     | 64.7989 gn/kg        | ???     | ???                | 50,000 tlJ/kg           | 3,750 mo/kg        | 643.0149 dwt/kg    | 35.274 oz/kg           | 2.20462 lb/kg              | 37,500 tlT/kg          | 31,104.199066 ozt/kg      | 37,800.0378 tlH/kg      |
| Carats (ct)         | 0.2 g/ct            | 200 mg/ct            | 20 cg/ct             | 0.0002 kg/ct            | 1                      | 2.33276076 T/ct    | ???     | 0.354369 dr/ct      | ???     | 0.01295978 gn/ct     | ???     | ???                | 10 tlJ/ct               | 0.75 mo/ct         | 0.1286029 dwt/ct   | 0.0070548 oz/ct        | 4.40924 * 1^(-4) lb/ct     | 7.5 tlT/ct             | 6.220696 ozt/ct           | 7.5598932543 tlH/ct     |
| Tola (T)            | 0.08573532418 g/T   | 85.73532418 mg/T     | 8.573532418 cg/T     | 0.00008573532418 kg/T   | 0.4286766209 ct/T      | 1                  | ???     | 0.1519097 dr/T      | ???     | 0.0055555555555 gn/T | ???     | ???                | 4.2867676 tlJ/T         | 0.321507465 mo/T   | 0.055129 dwt/T     | 0.0030242279 oz/T      | 1.8901381 * 1^(-4) lb/T    | 3.2150747 lb/T         | 2.666666 ozt/T            | 3.24074083 tlH/T        |
| TAR ???             | ???                 | ???                  | ???                  | ???                     | ???                    | ???                | 1       | ???                 | ???     | ???                  | ???     | ???                | ???                     | ???                | ???                | ???                    | ???                        | ???                    | ???                       | ???                     |
| Dram (dr)           | 0.56438339119 g/dr  | 564.38339119 mg/dr   | 56.438339119 cg/dr   | 0.00056438339119 kg/dr  | 2.82191695595 ct/dr    | 6.582857142 T/dr   | ???     | 1                   | ???     | 0.036571423 gn/dr    | ???     | ???                | 28.21917267 tlJ/dr      | 2.1164377263 mo/dr | 0.36290696 dwt/dr  | 0.01990 oz/dr          | 0.00124425 lb/dr           | 21.1643795 tlT/dr      | 17.554287573 ozt/dr       | 21.33356 tlH/dr         |
| PKT ???             | ???                 | ???                  | ???                  | ???                     | ???                    | ???                | ???     | ???                 | 1       | ???                  | ???     | ???                | ???                     | ???                | ???                | ???                    | ???                        | ???                    | ???                       | ???                     |
| Grain (gn)          | 15.4323607345 g/gn  | 15432.3607345 mg/gn  | 1,543.23607345 cg/gn | 0.0154323607345 kg/gn   | 77.1618036725 ct/gn    | 180 T/gn           | ???     | 27.3437541377 dr/gn | ???     | 1                    | ???     | ???                | 771.618036725932 tlJ/gn | 57.871375 mo/gn    | 9.92323878 dwt/gn  | 0.5443611 oz/gn        | 0.034022 lb/gn             | 578.71375 tlT/gn       | 480 ozt/gn                | 583.3334267 tlH/gn      |
| TMR ???             | ???                 | ???                  | ???                  | ???                     | ???                    | ???                | ???     | ???                 | ???     | ???                  | 1       | ???                | ???                     | ???                | ???                | ???                    | ???                        | ???                    | ???                       | ???                     |
| Grammage (GSM) ???  | ???                 | ???                  | ???                  | ???                     | ???                    | ???                | ???     | ???                 | ???     | ???                  | ???     | 1                  | ???                     | ???                | ???                | ???                    | ???                        | ???                    | ???                       | ???                     |
| Tael Japan (tlJ)    | 0.02 g/tlJ          | 20 mg/tlJ            | 2 cg/tlJ             | 0.00002 kg/tlJ          | 0.1 ct/tlJ             | 0.233276 T/tlJ     | ???     | 0.0354369 dr/tlJ    | ???     | 0.001295978 gn/tlJ   | ???     | ???                | 1                       | 0.075 mo/tlJ       | 0.01286029 dwt/tlJ | 7.0548 * 1^(-4) oz/tlJ | 4.40924 * 1^(-5) lb/tlJ    | 0.75 tlT/tlJ           | 0.622072 ozt/tlJ          | 0.75598761 tlH/tlJ      |
| Momme (mo)          | 0.26666666666 g/mo  | 266.6666666666 mg/mo | 26.666666666 cg/mo   | 0.00026666666666 kg/mo  | 1.33333333333333 ct/mo | 3.1103476799 T/mo  | ???     | 0.47249205 dr/mo    | ???     | 0.0172797 gn/mo      | ???     | ???                | 13.333333333 tlJ/mo     | 1                  | 0.17147 dwt/mo     | 0.0094064 oz/mo        | 5.878986667 * 1^(-4) lb/mo | 5.714285 tlT/mo        | 8.29426183 ozt/mo         | 99.79243 tlH/mo         |
| Pennyweight (dwt)   | 1.55517384 g/dwt    | 1,555.17384 mg/dwt   | 155.517384 cg/dwt    | 0.00155517384 kg/dwt    | 7.7758692 ct/dwt       | 18.139242544 T/dwt | ???     | 2.7555272 dr/dwt    | ???     | 0.10077355 gn/dwt    | ???     | ???                | 77.758692 tlJ/dwt       | 5.8319019 mo/dwt   | 1                  | 0.0548572 oz/dwt       | 0.00342856 lb/dwt          | 58.3192395 tlT/dwt     | 48.371337 ozt/dwt         | 58.7848 tlH/dwt         |
| Ounces (oz)         | 28.3494925441 g/oz  | 28,349.4925441 mg/oz | 2,834.94925 cg/oz    | 0.02834949 kg/oz        | 141.74746 ct/oz        | 330.66291 T/oz     | ???     | 50.230912 dr/oz     | ???     | 1.8370159 gn/oz      | ???     | ???                | 1,417.474627 tlJ/oz     | 106.31059 mo/oz    | 18.22914611 dwt/oz | 1                      | 0.0625 lb/oz               | 1,063.829787234 tlT/oz | 881.834 ozt/oz            | 968.054211 tlH/oz       |
| Pounds (lb)         | 453.592909436 g/lb  | 453,592.909436 mg/lb | 45,359.2909436 cg/lb | 0.4535929 kg/lb         | 2,267.96454 ct/lb      | 5,290.6187 T/lb    | ???     | 803.6964148 dr/lb   | ???     | 29.39232157 gn/lb    | ???     | ???                | 22,679.645 tlJ/lb       | 1,700.97341 mo/lb  | 291.6669993 dwt/lb | 16 oz/lb               | 1                          | 17,045.4545648 tlT/lb  | 14.6139742 ozt/lb         | 17,182.130584 tlH/lb    |
| Tael Taiwan (tlT)   | 0.02666666666 g/tlT | 26.66666666 mg/tlT   | 2.666666666 cg/tlT   | 0.00002666666666 kg/tlT | 0.1333333333 ct/tlT    | 0.31103476 T/tlT   | ???     | 0.0472492 dr/tlT    | ???     | 0.00172797 gn/tlT    | ???     | ???                | 1.333333333 tlJ/tlT     | 0.175 mo/tlT       | 0.017147 dwt/tlT   | 0.00094 oz/tlT         | 0.0000586666666 lb/tlT     | 1                      | 8.573535 * 1^(-4) ozt/tlT | 1.0079832271591 tlH/tlT |
| Troy Ounce (ozt)    | 31.10348 g/ozt      | 32.15074326 mg/ozt   | 3.215074326 cg/ozt   | 0.00003215 kg/ozt       | 0.1607537163 ct/ozt    | 0.3749999614 T/ozt | ???     | 0.0569661398 dr/ozt | ???     | 0.00208333 gn/ozt    | ???     | ???                | 1.60753 tlJ/ozt         | 0.12056528 mo/ozt  | 0.0206734 dwt/ozt  | 0.001134 oz/ozt        | 0.068427656 lb/ozt         | 1,166.38 tlT/ozt       | 1                         | 1,175.69186527 tlH/ozt  |
| Tael Hongkong (tlH) | 0.02645547146 g/tlH | 26.45547 mg/tlH      | 2.645547 cg/tlH      | 0.000026455 kg/tlH      | 0.132277 ct/tlH        | 0.30857142 T/tlH   | ???     | 0.0468745 dr/tlH    | ???     | 0.00171428544 gn/tlH | ???     | ???                | 1.322773 tlJ/tlH        | 0.0100208 mo/tlH   | 0.0170112 dwt/tlH  | 0.001033 oz/tlH        | 0.0000582 lb/tlH           | 0.99208 tlT/tlH        | 0.000850563 ozt/tlH       | 1                       |
```