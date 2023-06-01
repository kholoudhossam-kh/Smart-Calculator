#include "mbed.h"

uint8_t Keypad_4x4_adjustKeyNumber(uint8_t buttonNumber);
BusOut	Disp(PORT0_8_IRQn,PORT0_9_IRQn,PORT0_10_IRQn,PORT0_11_IRQn,PORT0_12_IRQn,PORT0_13_IRQn,PORT0_14_IRQn,PORT0_15_IRQn)
uint8_t Keypad_getPressedKey(void)
{
	uint8_t column, row;
	Gpio_init_in(Port0,PORT0_0_IRQn);
	Gpio_init_in(Port0,PORT0_1_IRQn);
	Gpio_init_in(Port0,PORT0_2_IRQn);
	Gpio_init_in(Port0,PORT0_3_IRQn);
	Gpio_init_in(Port0,PORT0_4_IRQn);
	Gpio_init_in(Port0,PORT0_5_IRQn);
	Gpio_init_in(Port0,PORT0_6_IRQn);
	Gpio_init_in(Port0,PORT0_7_IRQn);
	while (true)
	{
		for (row = 0; row < 4; row++)
		{
			Gpio_init_out(Port0,PORT0_0_IRQn + row);
			Gpio_init_out_ex(Port0,Port0,PORT0_0_IRQn + row,1);
			for (column = 0; column < 4; column++)
			{
				if (Gpio_read(PORT0_4_IRQn + column)) == 1)
				{
					return Keypad_4x4_adjustKeyNumber(
							(column * 4) + row + 1);
				}
			}
			Gpio_init_in(Port0,PORT0_0_IRQn + row);
		}
	}
}

uint8_t Keypad_4x4_adjustKeyNumber(uint8_t buttonNumber)
{
	uint8_t keypadButton = 0;
	switch (buttonNumber)
	{
		case 1:
			keypadButton = 1;
		break;
		case 2:
			keypadButton = 2;
		break;
		case 3:
			keypadButton = 3;
		break;
		case 4:
			keypadButton = '+';
		break;
		case 5:
			keypadButton = 4;
		break;
		case 6:
			keypadButton = 5;
		break;
		case 7:
			keypadButton = 6;
		break;
		case 8:
			keypadButton = '-';
		break;
		case 9:
			keypadButton = 7;
		break;
		case 10:
			keypadButton = 8;
		break;
		case 11:
			keypadButton = 9;
		break;
		case 12:
			keypadButton = '*';
		break;
		case 13:
			keypadButton = 13;
		break;
		case 14:
			keypadButton = 0;
		break;
		case 15:
			keypadButton = '/';
		break;
		case 16:
			keypadButton = '=';
		break;
		default:
			keypadButton = buttonNumber;
		break;
	}
	return keypadButton;
}

void SevenSeg_init(void)
{
    Gpio_init_out_ex(Port0,Port0,PORT0_15_IRQn,0);
}

void SevenSeg_displayNumber(uint8 number)
{
    if (number < 0)
    {
	Disp = 0x77;
    }
    else {
	switch (number)
	{
		case 0:
			Disp = 0x3F;
		break;
		case 1:
			Disp = 0x06;
		break;
		case 2:
			Disp = 0x5B;
		break;
		case 3:
			Disp = 0x4F;
		break;
		case 4:
			Disp = 0x66;
		break;
		case 5:
			Disp = 0x6D;
		break;
		case 6:
			Disp = 0x7D;
		break;
		case 7:
			Disp = 0x07;
		break;
		case 8:
			Disp = 0x7F;
		break;
		case 9:
			Disp = 0x67;
		break;
        default:
            Disp = 0x71;
        break;
	}
    }
}

int main(void)
{
	uint8_t key, firstValue, secondValue;
    uint8_t trial = 0;
    SevenSeg_init();
	while (true)
	{
		key = Keypad_getPressedKey();
		if ((key >= 0) && (key <= 9))
		{
			switch(trial)
            {
                case 0:
                firstValue = key;
                trial = 1;
                break;
                case 1:
                secondValue = key;
                SevenSeg_displayNumber(firstValue + secondValue);
                trial = 0;
                break;
            }
		}
	}
}