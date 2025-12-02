# clementine clock

this is an orange/mandarin-themed clock to set timers & alarms for my room. I decided to make a clock because I usually don't have access
to my phone when I go to sleep at school, and I needed an easy way to know the time and to wake up at the right time. I chose a clementine
theme because I like oranges.

on the main PCB board, there is a 4-digit 7-segment LCD display (showing the time), a small button, and a speaker. there is also wires on the
main PCB board connecting a rotary encoder (adjusting the time) on the top of the orange, a 3 AA battery case, and a big button (snooze & stop) at the
"stem" of the clementine. the case is a 3D-printed cylindrical clementine case.

![3dfront](https://vdisxgivmydncdlltgmb.supabase.co/storage/v1/object/public/project-images/clementineclock.png)
![3dback](https://vdisxgivmydncdlltgmb.supabase.co/storage/v1/object/public/project-images/clementineclock2.png)

![pcb](https://vdisxgivmydncdlltgmb.supabase.co/storage/v1/object/public/project-images/clementineclockpcb1.png)
![schematic](https://vdisxgivmydncdlltgmb.supabase.co/storage/v1/object/public/project-images/clementineclockschematic.png)

## bill of materials
| Reference    | Item               | Description                                    | Qty | Unit Price (USD) | Total (USD) | URL |
|--------------|--------------------|------------------------------------------------|-----|-------------------|-------------|-----|
| U1           | Microcontroller    | Seeed XIAO RP2040                              | 1   | 4.68              | 4.68        | https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/102010428/14672129 |
| J1_DISPLAY   | LCD Display        | Grove LCD Screen (104030003)                   | 1   | 6.50              | 6.50        | https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/104030003/5488009 |
| U2           | Voltage Regulator  | MIC5219-3.3YM5 3.3V LDO                        | 1   | 1.19              | 1.19        | https://www.digikey.com/en/products/detail/microchip-technology/MIC5219-3-3YM5-TR/771750 |
| U3           | Audio Amplifier    | PAM8302AAD                                     | 1   | 0.48              | 0.48        | https://www.digikey.com/en/products/detail/diodes-incorporated/pam8302aadcr/4033280 |
| LS1          | Speaker            | SC250708-1 8Ω Speaker                          | 1   | 2.96              | 2.96        | https://www.digikey.com/en/products/detail/db-unlimited/SC250708-1/9990569 |
| SW1          | Rotary Encoder     | ACZ11BR4E-15FD1-20C                             | 1   | 3.22              | 3.22        | https://www.digikey.com/en/products/detail/same-sky-formerly-cui-devices/acz11br4e-15fd1-20c/1923364 |
| SW2          | Pushbutton (Big)   | RP3502ARED                                     | 1   | 2.29              | 2.29        | https://www.digikey.com/en/products/detail/e-switch/RP3502ARED/280448 |
| SW3          | Pushbutton (Small) | Y97HT21A2FAFP                                  | 1   | 0.24              | 0.24        | https://www.digikey.com/en/products/detail/c-k/Y97HT21A2FAFP/3861375 |
| SW4          | Power Switch       | PCM12SMTR slide SPST                           | 1   | 1.14              | 1.14        | https://www.digikey.com/en/products/detail/c-k/PCM12SMTR/1640112 |
| BT1_HOLDER   | Battery Holder     | Kitronik 2273 3×AAA w/ JST                     | 1   | 1.87              | 1.87        | https://www.digikey.com/en/products/detail/kitronik-ltd/2273/8635437 |
| BT1          | Battery Connector  | B2B-PH-K-S JST-PH 2-pin header                 | 1   | 0.10              | 0.10        | https://www.digikey.com/en/products/detail/jst-sales-america-inc/B2B-PH-K-S/926611 |
| J1           | LCD Header         | PRPC004SAAN-RC 1×4 2.54mm                      | 1   | 0.34              | 0.34        | https://www.digikey.com/en/products/detail/adam-tech/RS1-04-G/9829303 |
| C1           | Capacitor          | 10µF 10V X7R 0805                               | 1   | 1.02              | 1.02        | https://www.digikey.com/en/products/detail/kemet/c0805x106j8rac7210/7423434 |
| C2           | Capacitor          | 22µF 10V X5R 0805                               | 1   | 0.15              | 0.15        | https://www.digikey.com/en/products/detail/yageo/cc0805mrx5r6bb226/7164395 |
| C3           | Capacitor          | 0.22µF 50V X7R 0805                             | 1   | 0.15              | 0.15        | https://www.digikey.com/en/products/detail/kemet/c0805c224k5ractu/754753 |
| C4           | Capacitor          | 1µF 50V X7R 0805                                | 1   | 0.81              | 0.81        | https://www.digikey.com/en/products/detail/kemet/C0805C105K5RACTU/3317615 |
| C5           | Capacitor          | 10nF 250V 0805                                  | 1   | 0.08              | 0.08        | https://www.digikey.com/en/products/detail/nextgen-components/0805B103K251DC/18668378 |
| C6           | Capacitor          | 4.7µF 50V X5R 0805                              | 1   | 0.19              | 0.19        | https://www.digikey.com/en/products/detail/murata-electronics/grm21br61h475ke51l/4905540 |
| R1           | Resistor           | 100kΩ 1% 0805                                   | 1   | 0.10              | 0.10        | https://www.digikey.com/en/products/detail/stackpole-electronics-inc/rmcf0805ft100k/1760712 |
| R2           | Resistor           | 1kΩ 1% 0805                                     | 1   | 0.10              | 0.10        | https://www.digikey.com/en/products/detail/stackpole-electronics-inc/rmcf0805ft1k00/1760090 |
| D1           | LED                | Red 0805 LED                                    | 1   | 0.19              | 0.19        | https://www.digikey.com/en/products/detail/würth-elektronik/150080RS75000/4489918 |
| **TOTAL**    | —                  | —                                              | —   | **Tax + Shipping = 10** | **37.8** | |



## made for [Blueprint](https://blueprint.hackclub.com/)
## find the Journal (devlogs) and project on Blueprint [here](https://blueprint.hackclub.com/projects/2563)
