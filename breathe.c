#include <gb/gb.h>
#include <gb/drawing.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void game_loop();
void writeExercise();
void clear();

UINT8 b[5] = {1, 2, 4, 6, 8};
UINT8 m[5] = {1, 2, 3, 4, 5};
UINT16 ms[5] = {600, 300, 120, 70, 38};
UINT8 r = 2;
UINT8 rev = 0;
UINT8  j, f;
UINT8 t = 0;
UINT8 id = 0;
UINT8 tid = 0;
UINT8 cycc = 0;
UINT8 comp;
UINT8 sound = 0;


int main()
{
    NR50_REG = 0xFF;
    NR51_REG = 0xFF;
    NR52_REG = 0x80;

    DISPLAY_ON;
    SHOW_SPRITES;
	writeExercise();

    while(1)
    {
        game_loop();
    }
}



void breathing()
{	
	if (rev == 0)
	{
		r += 1;
	}
	else if (rev == 1)
	{
		r -= 1;
	}
	if (r > 49)
	{
		rev = 1;
		if(sound == 1)
		{
			NR10_REG = 0x38U;
	        NR11_REG = 0x60U;
	        NR12_REG = 0xE1U;
	        NR13_REG = 0xDCU;
	        NR14_REG = 0xC6U;

	        NR51_REG |= 0x11;
		}
		clear();
	}
	else if (r < 3)
	{ 
		rev = 0;
		cycc++;
		if(sound == 1)
		{
			NR10_REG = 0x38U;
	        NR11_REG = 0x60U;
	        NR12_REG = 0xE1U;
	        NR13_REG = 0xDCU;
	        NR14_REG = 0xC6U;

	        NR51_REG |= 0x11;
		}
		clear();
	}
	color (BLACK, WHITE, SOLID);
	circle(80, 72, r, M_NOFILL);
	wait_vbl_done();
	delay(ms[id]);
}

void clear()
{
	for (j = 0; j < 20; j++) { 
					for (f = 0; f < 18; f++) { 
						gotogxy(j, f);
						wrtchr(' '); 
					}
				}
}

void writeExercise()
{
	clear();
	comp = b[id]* m[tid];
	
	gotogxy(5,1);
	gprintf("BREATHE GB");
	gotogxy(0,6);
	gprintf("A: ~ %u breathes/min", b[id]);
	
	gotogxy(0,8);
	gprintf("B: ~ %u minute(s) ", m[tid]);
	
	gotogxy(0,10);
	if (sound == 0)
	{
		gprintf("SELECT: Sound OFF");
	}
	else if (sound == 1)
	{
		gprintf("SELECT: Sound ON");
	}
	
	gotogxy(4,14);
	gprintf("Press START");
}

void game_loop()
{
	if (joypad() == J_A && t == 0) { 
				waitpadup();
				id++;
				if (id > 4)
				{
					id = 0;
				}
				writeExercise();	
	}
	if (joypad() == J_B && t == 0) { 
				waitpadup();
				tid++;
				if (tid > 4)
				{
					tid = 0;
				}
				writeExercise();
					
	}
	if (joypad() == J_SELECT && t == 0)
	{
		if (sound == 0)
		{
			sound = 1;
		}
		else
		{
			sound = 0;
		}
		writeExercise();
	}
	if (joypad() == J_START && t == 0)
	{
		clear();
		t = 1;
	}
	if (t > 0)
	{
		if(cycc == comp)
		{
			clear();
			cycc = 0;
			t = 0;
			writeExercise();
		}
		else
		{
			breathing();
		}
	}
	
}


