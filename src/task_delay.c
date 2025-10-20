#include <stdio.h>
#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>

// should use the task delay from the RTOS
// precision is up to the mercy of the scheduler
// period should be 20 ms
// min 20.00034 ms
// max 20.00034 ms
// mean 20.00034 ms
// stddev 4.6 ns
// d min 50.00%
// d max 50.00%
// d mean 50.00%
// d stddev 0.00%
// drift (calculated from mean) 1.224 s / hour

// when busy
// min 24.0004 ms
// max 24.0004 ms
// mean 24.0004 ms
// stddev 4.6 ns
// d min 50.00%
// d max 50.00%
// d mean 50.00%
// d stddev 0.00%
// drift (calculated from mean) 14.401 s / hour

#define OUT_PIN 2
#define DELAY_MS 10

void main_task(__unused void *params)
{
    int toggle = 0;
    while (1) {
        toggle = !toggle;
        gpio_put(OUT_PIN, toggle);
        //for (int i = 0; i < 65525; i++);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}

int main(void)
{
    stdio_init_all();
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
    const char *rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1UL, &task);
    vTaskStartScheduler();
    return 0;
}
