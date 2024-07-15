#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// Definições de pinos e configurações para o LED interno
#define LED_PIN   PB7  // Pino 13 na placa do Arduino Mega 2560
#define LED_DELAY 1000 // Tempo do atraso em ms
#define UNUSED(x) (void)(x)

// Variável global para contar os milissegundos
volatile uint32_t millis_count = 0;

// Rotina de interrupção do Timer1
ISR(TIMER1_COMPA_vect)
{
    millis_count++; // Incrementa o contador de milissegundos
}

// Inicialização do Timer1 para interrupção a cada 1 ms
void timer1_init()
{
    // Configuração do Timer1 em modo CTC (Clear Timer on Compare Match)
    TCCR1A = 0;                          // Modo normal
    TCCR1B = (1 << WGM12) | (1 << CS11); // WGM12 para modo CTC, prescaler de 8
    OCR1A = 1000;                        // Comparação para interrupção a cada 1 ms
    TIMSK1 |= (1 << OCIE1A);             // Habilita a interrupção por comparação A
}

// Função para transmitir caracteres pela UART
void uart_transmit(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;        // Espera até o buffer de transmissão estar vazio
    UDR0 = data; // Transmite dados
}

// Função printf que redireciona para uart_transmit
int uart_putchar(char c, FILE *stream)
{
    UNUSED(stream);

    if (c == '\n')           // Verifica se foi adicionado quebra de linha
        uart_transmit('\r'); // Adiciona carriage return antes de newline
    uart_transmit(c);        // Transmite o caractere

    return 0;
}

// Função para inicializar UART para printf
void uart_init(void)
{
    UBRR0H = 0;
    UBRR0L = 103;                           // Configura baud rate em 9600
    UCSR0B |= (1 << TXEN0);                 // Habilita transmissão
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits de dados, 1 bit de parada
    stdout = fdevopen(uart_putchar, NULL);  // Redireciona stdout para uart_putchar
}

// Função millis() para retornar os milissegundos contados
uint32_t millis()
{
    uint32_t m;
    // Desabilita interrupções em millis_count para garantir leitura atômica
    cli();
    m = millis_count;
    sei();
    return m;
}

// Função para inicializar o LED interno
void gpio_init()
{
    // Configura o pino do LED como saída
    DDRB |= (1 << LED_PIN);
}

// Pisca o LED interno com base no tempo decorrido
void blink_led()
{
    static uint32_t last_time = 0;
    uint32_t current_time = millis();

    // Piscar a cada 500 ms
    if (current_time - last_time >= LED_DELAY) {
        last_time = current_time;
        PORTB ^= (1 << LED_PIN); // Inverte o estado do LED
    }
}

// Imprime o tempo atual a cada segundo na porta serial
void print_millis()
{
    static uint32_t last_print_time = 0;
    uint32_t current_time = millis();

    // Imprime a cada segundo (1000 ms)
    if (current_time - last_print_time >= 1000) {
        last_print_time = current_time;
        printf("Current millis: %lu\n", current_time);
    }
}

void print_version()
{
    // Imprime a versão do GCC
    printf("avr-gcc (GCC) %s\n", __VERSION__);

    // Imprime a versão da LibC
    printf("LibC version: %s\n\n", __AVR_LIBC_VERSION_STRING__);
}

void print_variable_types()
{
    // Exemplos de variáveis
    int i = 42;
    printf("int: %d\n", i);

    float f = M_PI;
    printf("float: %.2f\n", f);

    unsigned int ui = 12345;
    printf("unsigned int: %u\n", ui);

    long l = 1234567890;
    printf("long: %ld\n", l);

    unsigned long ul = (unsigned long)9876543210ULL;
    printf("unsigned long: %lu\n", ul);

    double d = M_PI;
    printf("double: %lf\n", d);

    // Ponteiro
    int *ptr = &i;
    printf("int pointer: %p\n", (void *)ptr);

    // Array
    int array[] = {1, 2, 3, 4, 5};
    printf("array: [%d, %d, %d, %d, %d]\n",
           array[0], array[1], array[2], array[3], array[4]);

    char c = 'A';
    printf("char: %c\n", c);

    // String (array de char)
    char str[] = "Hello, AVR!";
    printf("string: %s\n", str);
}

// Função principal
int main(void)
{
    uart_init();               // Inicializa UART para printf
    timer1_init();             // Inicializa timer1
    gpio_init();               // Inicializa as portas
    sei();                     // Habilita interrupções globais

    // Imprime as versões do GCC e da LibC
    print_version();

    // Imprime todos os tipos de variáveis
    print_variable_types();

    while (1) {                // Loop principal
        blink_led();           // Pisca o LED interno
        print_millis();        // Imprime o tempo atual a cada segundo
    }

    return 0;
}
