#include <stdio.h>
#include <pico/stdlib.h>

#define OUT_PIN 2
#define DELAY_MS 10

// uses the picotool sleep (probably form systick)
// sleeping may not play nice with the RTOS
// period should be 20 ms
// min 20.00034 ms
// max 20.00034 ms
// mean 20.00034 ms
// stddev 0
// d min 50.00%
// d max 50.00%
// d mean 50.00%
// d stddev 0.00%
// drift (calculated from mean) 1.224 s / hour

// when busy
// min 24.19416 ms
// max 24.19416 ms
// mean 24.19416 ms
// stddev 0 s
// d min 50.00%
// d max 50.00%
// d mean 50.00%
// d stddev 0.00%
// drift (calculated from mean) 15.098 s / hour

int main(void)
{
    int toggle = 0;
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    while (true) {
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        //for (int i = 0; i < 65525; i++);
        sleep_ms(DELAY_MS);
    }
}
