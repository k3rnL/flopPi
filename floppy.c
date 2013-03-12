#include "floppy.h"



int main(int argc, int ** argv) {
	
	int choix = NULL;

	if (wiringPiSetup() == -1)
		exit (1);
	//jouerNote(10000,100);
	position = 0;	
	printf("Floppy Players\nBy k3rnL\nv1.1\n\n");
	printf("Frequence. 1-7 aigu / 8-12 medium / 13-25 basse");
	printf("\n\n1.Note\n2.Modulation\n3.Test mario brosse(toi les fesses)");
	scanf("%d", &choix);
	//changeDirection();
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
	
	
	
	while(i < temps) {
		compteurPosition();
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

int directionPouet() {
	if (direction == 1) {
			return 1;
		} else {
			return 0;
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
	  compteurPosition();
  }

}

void compteurPosition() {
	if(directionPouet()) {
	
		if(position == 64) {
			changeDirection();
		} else if (position < 64) {
			position++;
		}
		
	} else if (directionPouet() == 0) {
		
		if(position == 0) {
			changeDirection();
		} else if (position > 0) {
			position--;
		}
	}
}


void PlaySong(int index,int tempo)
{
  

  /**********MUSIQUE**********/

float song0[] = 
  {
    E2,EIGHTH, E2,QUARTER, E2,EIGHTH, REST,EIGHTH, C2,EIGHTH, E2,QUARTER, G2,HALF, G,HALF, 
    REST,ETERNITY
  };
float song1[] = 
  {
    C2,DOTTED_QUARTER, G,EIGHTH, REST,QUARTER, E,QUARTER, REST,EIGHTH, A2,QUARTER, B2,EIGHTH, REST,EIGHTH, A2S,EIGHTH, A2,QUARTER,
    G,DOTTED_EIGHTH, E2,DOTTED_EIGHTH, G2,EIGHTH, A3,QUARTER, F2,EIGHTH, G2,EIGHTH, REST,EIGHTH, E2,QUARTER, C2,EIGHTH, D2,EIGHTH, B2,DOTTED_QUARTER,
    REST,ETERNITY  
  };
float song2[] = 
  {
    C2,DOTTED_QUARTER, G,EIGHTH, REST,QUARTER, E,QUARTER, REST,EIGHTH, A2,QUARTER, B2,EIGHTH, REST,EIGHTH, A2S,EIGHTH, A2,QUARTER,
    G,DOTTED_EIGHTH, E2,DOTTED_EIGHTH, G2,EIGHTH, A3,QUARTER, F2,EIGHTH, G2,EIGHTH, REST,EIGHTH, E2,QUARTER, C2,EIGHTH, D2,EIGHTH, B2,DOTTED_QUARTER,
    REST,ETERNITY  
  };
float song3[] = 
  {
    REST,QUARTER, G2,EIGHTH, F2S,EIGHTH, F2,EIGHTH, D2S,QUARTER, E2,EIGHTH, REST,EIGHTH, GS,EIGHTH, A2,EIGHTH, C2,EIGHTH, REST,EIGHTH, A2,EIGHTH, C2,EIGHTH, D2,EIGHTH,
    REST,QUARTER, G2,EIGHTH, F2S,EIGHTH, F2,EIGHTH, D2S,QUARTER, E2,EIGHTH, REST,EIGHTH, C3,QUARTER, C3,EIGHTH, C3,HALF,
    REST,ETERNITY  
  };
float song4[] = 
  {
    REST,QUARTER, G2,EIGHTH, F2S,EIGHTH, F2,EIGHTH, D2S,QUARTER, E2,EIGHTH, REST,EIGHTH, GS,EIGHTH, A2,EIGHTH, C2,EIGHTH, REST,EIGHTH, A2,EIGHTH, C2,EIGHTH, D2,EIGHTH,
    REST,QUARTER, D2S,QUARTER, REST,EIGHTH, D2,DOTTED_QUARTER, C2,HALF, REST,HALF,
    REST,ETERNITY  
  };
float song5[] = 
  {
    C2,EIGHTH, C2,QUARTER, C2,EIGHTH, REST,EIGHTH, C2,EIGHTH, D2,QUARTER, E2,EIGHTH, C2,QUARTER, A2,EIGHTH, G,HALF,
    C2,EIGHTH, C2,QUARTER, C2,EIGHTH, REST,EIGHTH, C2,EIGHTH, D2,EIGHTH, E2,EIGHTH, REST,WHOLE,
    REST,ETERNITY  
  };
float song6[] = 
{
    C2,EIGHTH, C2,QUARTER, C2,EIGHTH, REST,EIGHTH, C2,EIGHTH, D2,QUARTER, E2,EIGHTH, C2,QUARTER, A2,EIGHTH, G,HALF,
    E2,EIGHTH, E2,QUARTER, E2,EIGHTH, REST,EIGHTH, C2,EIGHTH, E2,QUARTER, G2,QUARTER, REST, HALF,
    REST,ETERNITY  
};

float* songs[] = {
	song0,
	song1,
	song2,
	song3,
	song4,
	song5,
	song6, };
  printf("pouet %d", index);
	int x;
	float* song = songs[index]; 
	 for(x= 0; x<10000; x=x+2)
	{
		int noteval = (int)(song[x] / 64.0f);
		int dur = (int)((float)tempo * song[x+1]);
		
		if(dur < 0)
		  break;
		
		jouerFrequence(noteval, dur);

		delay(10);
	}
  
}

void test() {
	int i = 0;
	while(1) {
	PlaySong(i,140);
	i++;
	if(i == 7) break;
	}

	printf("POUET");


}
