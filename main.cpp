#include "mbed.h"

uint8_t Keypad_4x4_adjustKeyNumber(uint8_t buttonNumber);
BusOut	Disp(P0_8,P0_9,P0_10,P0_11,P0_12,P0_13,P0_14,P0_15);
uint8_t Keypad_getPressedKey(void)
{
	uint8_t column, row;
	DigitalIn P0_0 (P0_0);
	DigitalIn P0_1 (P0_1);
	DigitalIn P0_2 (P0_2);
	DigitalIn P0_3 (P0_3);
	DigitalIn P0_4 (P0_4);
	DigitalIn P0_5 (P0_5);
	DigitalIn P0_6 (P0_6);
	DigitalIn P0_7 (P0_7);

	while (true)
	{
		for (row = 0; row < 4; row++)
		{
            if (row == 0)
            {
                DigitalOut P0_0 (P0_0);
                P0_0 = 1;
            }
            else if (row == 1)
            {
                DigitalOut P0_1 (P0_1);
                P0_1 = 1;
            }
            else if (row == 2)
            {
                DigitalOut P0_2 (P0_2);
                P0_2 = 1;
            }
            else {
                DigitalOut P0_3 (P0_3);
                P0_3 = 1;
            }
			for (column = 0; column < 4; column++)
			{  
            if (column == 0 && P0_4 == 1)
            {
					return Keypad_4x4_adjustKeyNumber(
							(column * 4) + row + 1);
            }
            else if (column == 1 && P0_5 == 1)
            {
					return Keypad_4x4_adjustKeyNumber(
							(column * 4) + row + 1);
            }
            else if (column == 2 && P0_6 == 1)
            {
					return Keypad_4x4_adjustKeyNumber(
							(column * 4) + row + 1);
            }
            else if (column == 3 && P0_7 == 1) {
					return Keypad_4x4_adjustKeyNumber(
							(column * 4) + row + 1);
            }
			}

            if (row == 0)
            {
                DigitalIn P0_0 (P0_0);
            }
            else if (row == 1)
            {
                DigitalIn P0_1 (P0_1);
            }
            else if (row == 2)
            {
                DigitalIn P0_2 (P0_2);
            }
            else {
                DigitalIn P0_3 (P0_3);
            }
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

void SevenSeg_displayNumber(uint8_t number)
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
	uint8_t key, firstValue, operation,secondValue;
    uint8_t trial = 0;
	while (true)
	{
		key = Keypad_getPressedKey();
			switch(trial)
            {
                case 0:
                	firstValue = key;
					trial = 1;
                break;
                case 1:
                	operation = key;
					trial = 2;
                break;
				case 2:
					secondValue = key;
				switch(operation)
				{
					case '+':
					SevenSeg_displayNumber(firstValue + secondValue);
					break;
					case '-':
					SevenSeg_displayNumber(firstValue - secondValue);
					break;
					default:
					SevenSeg_displayNumber(firstValue);
					break;
				}
					trial = 0;
				break;
            }
	}
}