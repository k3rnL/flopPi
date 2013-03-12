#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
int direction = 1;
int pinStep = 7;
int pinDirection = 0;



int main(int argc, int ** argv) {
	
	int choix = NULL;

	if (wiringPiSetup() == -1)
		exit (1);
		
	printf("Floppy Players\nBy k3rnL\nv1.02\n\n");
	printf("Frequence. 1-7 aigu / 8-12 medium / 13-25 basse");
	printf("\n\n1.Note\n2.Modulation");
	scanf("%d", &choix);
	
	if (choix == 1) note();
	if (choix == 2) modulation();
	if (choix == 3) test();
	return 0;
}

void note() {
	while(1) {
		int frequence = NULL;
		int temps = NULL;
		
		printf("\nEntrer frequence (0 pour quitter) : ");
		scanf("%d",&frequence);
		if (frequence == 0) break;
		
		printf("Entrer dur�e de note : ");
		scanf("%d", &temps);
		
		jouerNote(frequence, temps);
	}
}

void modulation() {
	while(1) {
		int freqMin;
		int freqMax;
		int repeat;
		
		printf("\nEntrer frequence debut (0 pour quitter) : ");
		scanf("%d",&freqMin);
		if (freqMin == 0) break;
		
		printf("Entrer frequence max : ");
		scanf("%d", &freqMax);
		
		printf("Entrer nombre de fois a r�p�ter : ");
		scanf("%d", &repeat);
		
		jouerModulation(freqMin, freqMax, repeat);
	}
}
void jouerNote(int frequence, int temps) {
	
	int i = NULL;
	
	pinMode(pinStep, OUTPUT);
	pinMode(pinDirection, OUTPUT);
	
	changeDirection();
	
	while(i < temps) {
		i++;
		digitalWrite(pinStep, 1);
		digitalWrite(pinStep, 0);
		usleep(frequence);
		
		
	}
}

void jouerModulation(int frequenceMin, int frequenceMax, int repeat, int temps) {

	pinMode(pinStep, OUTPUT);
	pinMode(pinDirection, OUTPUT);
	int freqMin = frequenceMin * 2;
	int freqMax = frequenceMax * 2;
	int i = NULL;
	
	while (i < repeat) {
		while(freqMin < freqMax) {
			freqMin++;
			digitalWrite(pinStep, 1);
			digitalWrite(pinStep, 0);
			usleep(freqMin);
		}
		
		freqMin = frequenceMin * 2;
		freqMax = frequenceMax * 2;
		changeDirection();
		
		while(freqMin < freqMax) {
			freqMax--;
			digitalWrite(pinStep, 1);
			digitalWrite(pinStep, 0);
			usleep(freqMax);
		}
		freqMin = frequenceMin;
		freqMax = frequenceMax;
		i++;
	}
}

void changeDirection() {
	if (direction == 1) {
			digitalWrite(pinDirection, 1);
			direction = 0;
		} else {
			digitalWrite(pinDirection, 0);
			direction = 1;
	}
}

void jouerFrequence(int freq, int t)  // freq in hz, t in ms
{  
  // Added special handling for rests (avoids pops)
  if (freq == 0)
  {
    delay(t);
    return;
  }
 
  int hperiod;                               //calculate 1/2 period in us
  long cycles, i;

  pinMode(pinStep, OUTPUT);                   // turn on output pin
  hperiod = (500000 / freq) - 7;             // subtract 7 us to make up for digitalWrite overhead
  cycles = ((long)freq * (long)t) / 1000;    // calculate cycles
  
  for (i=0; i<= cycles; i++)
  {
      // play note for t ms 
      digitalWrite(pinStep, HIGH); 
      delayMicroseconds(hperiod);
      digitalWrite(pinStep, LOW); 
      delayMicroseconds(hperiod - 1);     // - 1 to make up for digitaWrite overhead
  }

}


void PlaySong(int songIndex, int tempo)
{
  
  if (songIndex < 0 || songIndex >= cNumSongs)
  {
    return;
  }
  

  
  float* song = songs[songIndex];
  
  int x;
  for(x= 0; x<10000; x=x+2)
  {
    int noteval = (int)(song[x] / 64.0f);
    int dur = (int)((float)tempo * song[x+1]);
    
    if(dur < 0)
      break;
    
    freqout(noteval, dur);
 
    for (int i=0; i<6; i++)
    {
      boolean ledOn = (i == (millis() % 6));
      digitalWrite(regionLEDs[i], ledOn ? HIGH : LOW);
    }

    delay(10);
  }
}

void test() {
	jouerNote(10000, 10);
	jouerNote(20000, 15);
	jouerNote(15000, 5);
	jouerNote(25000, 20);
	jouerNote(10000, 10);
	jouerNote(20000, 15);
	jouerNote(15000, 5);
	jouerNote(25000, 20);
	jouerNote(10000, 10);
	jouerNote(20000, 15);
	jouerNote(15000, 5);
	jouerNote(25000, 20);
	jouerNote(10000, 10);
	jouerNote(20000, 15);
	jouerNote(15000, 5);
	jouerNote(25000, 20);

}
