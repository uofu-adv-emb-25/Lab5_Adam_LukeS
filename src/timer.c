#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/sync.h>

// uses the pico timer
// period should be 20 ms
// min 20.00034 ms
// max 20.00034 ms
// mean 20.00034 ms
// stddev 4.6 ns
// d min 50.00%
// d max 50.00%
// d mean 50.00%
// d stddev 0.00%

// when busy
// min 20.00034 ms
// max 20.00034 ms
// mean 20.00034 ms
// stddev 0s
// d min 50.00%
// d max 50.00%
// d mean 50.00%
// d stddev 0.00%

#define OUT_PIN 2
#define DELAY_MS 10

int toggle = 1;
bool timer_callback(__unused struct repeating_timer *t)
{
    toggle = !toggle;
    gpio_put(OUT_PIN, toggle);
    //for (int i = 0; i < 65525; i++);
    return true;
}

int main(void)
{
    stdio_init_all();
    // Create a repeating timer that calls timer_callback.
    // If the delay is > 0 then this is the delay between the previous
    // callback ending and the next starting.
    // If the delay is negative (see below) then the next call to the
    // callback will be exactly 500ms after the start of the call to
    // the last callback
    repeating_timer_t timer;
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    add_repeating_timer_ms(-DELAY_MS, timer_callback, NULL, &timer);
    while(1) __nop();
    return 0;
}
