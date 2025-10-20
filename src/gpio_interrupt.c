#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/sync.h>

#define IN_PIN 2
#define OUT_PIN 3

// dealay
// min 1.3392 us
// max 1.3476 us
// mean 1.3432 us
// stddev 2.344 ns

// loaded delay
// min 7.4432
// max 7.4516
// mean 7.4472
// 2.272 ns

int toggle = 1;
void irq_callback(uint gpio, uint32_t event_mask)
{
    if (gpio != IN_PIN) return;
    for (int i = 0; i < 127; i++)
    toggle = !toggle;
    if (event_mask & GPIO_IRQ_EDGE_RISE) {
        gpio_put(OUT_PIN, true);
    } else if (event_mask & GPIO_IRQ_EDGE_FALL) {
        gpio_put(OUT_PIN, false);
    }
}

int main(void)
{
    stdio_init_all();

    gpio_init(IN_PIN);
    gpio_set_dir(IN_PIN, GPIO_IN);

    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    gpio_put(OUT_PIN, toggle);

    gpio_set_irq_enabled_with_callback(IN_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL , true, irq_callback);
    while(1) __wfi();
    return 0;
}