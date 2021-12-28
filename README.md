# Another clocktwo clone

After already developing a prototype of a word clock, this is now my second attempt at creating this awesome piece of furniture from scratch. I learned from some of the lessons of the first version and applied my best practices in this project. Below an instruction set on how I build it.

![png](design/example.gif)


### Hardware (same as last time):
1. Arduino Uno (https://store.arduino.cc/products/arduino-uno-rev3)
2. AZDelivery RTC Chip (https://www.amazon.de/dp/B01M2B7HQB/ref=twister_B07ZQGBH14?_encoding=UTF8&psc=1)
3. WS2812E LED Strip (https://www.amazon.de/gp/product/B088FJLRFP/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&th=1)
4. copper cables (https://www.amazon.de/gp/product/B01BI1G88C/ref=ppx_yo_dt_b_asin_title_o02_s01?ie=UTF8&psc=1)
5. power cable (https://www.amazon.de/gp/product/B075TXKC9D/ref=ppx_yo_dt_b_asin_title_o00_s01?ie=UTF8&psc=1)

### Woodwork
1. Base 40.8 x 40.8
2. Top/Bot seperator 40.8 x 5
3. Left/Right seperator 36.8 x 5
4. LED plate 33.4 x 38.6
5. Acryl plate with satin effect 40.8 x 40.8
6. Acryl plate with non reflective glass 36.8 x 36.8
7. Front cover 40.8 x 40.8 with 36.8 x 36.8 cut in middle

Most of the wood can be ordered at https://expresszuschnitt.de/ - I chose for multiplex for all components. 

### Design
I used the attached pdf file as template in https://www.formulor.de/ to get a laser cut letter plate, which was afterwards placed between the 2 Arcyl plates. Design also available as svg (usage of pdf for Formulor recommended).

### Building process
I used some stain to process the wood before assembly. The front cover can be removed by using some inlays for the front screws. After multiple runs of applying stain and using grind, the box was assembled. LED strips were soldered together to form a 10x11 matrix and placed on blocks inside the box so that the Controller & connections still have some room. RTC module was glued inside. 

### Arduino Software Dependencies

Download via Library Manager in Arduino IDE or install via ZIP.

1. http://www.rinkydinkelectronics.com/library.php?id=73
2. FastLED

