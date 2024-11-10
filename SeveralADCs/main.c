/*
 * SeveralADCs.c
 *
 * Created: 09/11/2024 11:09:21 a.m.
 * Author : LSL
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1<<0); //Pin D0 como salida
	DDRD |= (1<<1); //Pin D1 como salida
	DDRD |= (1<<2); //Pin D2 como salida
	
	/******************** ADC *********************/
	//ADC voltage reference selection
	ADMUX &=~ (1<<REFS1);
	ADMUX |= (1<<REFS0);
	
	//ADC data adjust
	ADMUX &=~ (1<<ADLAR); //Ajuste a la izquierda
	
	//Input channel selection
	//ADMUX &=~ (1<<MUX0); ADMUX &=~ (1<<MUX1); ADMUX &=~ (1<<MUX2); ADMUX &=~ (1<<MUX3); //Selección del ADC0
// 	ADMUX |=  (1<<MUX0); ADMUX |=  (1<<MUX1); ADMUX &=~ (1<<MUX2); ADMUX &=~ (1<<MUX3); //Selección del ADC3
	//ADMUX &=~  (1<<MUX0); ADMUX |=  (1<<MUX1); ADMUX |= (1<<MUX2); ADMUX &=~ (1<<MUX3); //Selección del ADC6
	ADCSRA |= (1 << ADATE); //Auto trigger habilitado
	
	//ADC enable
	ADCSRA |= (1<<ADEN);
	//ADC Start conversion
	ADCSRA |= (1<<ADSC);
	//ADC Prescaler select
	ADCSRA |= (1<<ADPS2); ADCSRA &=~ (1<< ADPS1); ADCSRA &=~ (1<<ADPS0); //Division entre 16 
	
	//int adc1 = 0, adc2 = 0;
	
    while (1)
    {	
		ADCSRA |= (1 << ADEN); //Se habilita el ADC
		ADCSRA |= (1<<ADSC); //Comienza la conversión de ADC

		ADMUX &=~ (1<<MUX0); ADMUX &=~ (1<<MUX1); ADMUX &=~ (1<<MUX2); ADMUX &=~ (1<<MUX3); //Selección del ADC0
		
		if(ADC>500){
			PORTD |= (1<<PORTD1);
		}else{
			PORTD &=~ (1<<PORTD1);
		}
		
		ADCSRA |= (1 << ADIF); //Se habilita cuando la conversión ADC termina
		
		_delay_ms(10);
		
		ADCSRA |= (1 << ADEN); //Se habilita el ADC
		ADCSRA |= (1<<ADSC); //Comienza la conversión de ADC

		ADMUX &=~ (1<<MUX0); ADMUX |= (1<<MUX1); ADMUX |= (1<<MUX2); ADMUX &=~ (1<<MUX3); //Selección del ADC6
		if(ADC>500){
			PORTD |= (1<<PORTD2);
		}else{
			PORTD &=~ (1<<PORTD2);
		}
				
		ADCSRA |= (1 << ADIF); //Se habilita cuando la conversión ADC termina
		
		_delay_ms(10);
				
		ADCSRA |= (1 << ADEN); //Se habilita el ADC
		ADCSRA |= (1<<ADSC); //Comienza la conversión de ADC

		ADMUX |= (1<<MUX0); ADMUX |= (1<<MUX1); ADMUX &=~ (1<<MUX2); ADMUX &=~ (1<<MUX3); //Selección del ADC3
		if(ADC>500){
			PORTD |= (1<<PORTD0);
		}else{
			PORTD &=~ (1<<PORTD0);
		}
		
		ADCSRA |= (1 << ADIF); //Se habilita cuando la conversión ADC termina
		_delay_ms(10);

    }
}

