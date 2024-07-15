#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

volatile uint8_t ledState = 0;

int main()
{
    // Configura o pino 13 (LED) como saída
    DDRB |= (1 << DDB5);

    sei(); // Habilita interrupções globais

    // Imprime a versão do compilador GCC e o padrão do C++ utilizado
    printf("Versão do GCC: %d\n", __GNUC__);
    printf("Padrão do C++: %ld\n", __cplusplus);

    while (1)
    {
        ledState = !ledState;        // Inverte o estado do LED

        if (ledState)
        {
            PORTB |= (1 << PORTB5);  // Liga o LED
        }
        else
        {
            PORTB &= ~(1 << PORTB5); // Desliga o LED
        }

        _delay_ms(BLINK_DELAY_MS);   // Atraso em milissegundos
    }

    return 0;
}
