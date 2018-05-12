
int buttonCurrent = 0;
int pwrCurrent = 1;

int button = D1;
int pwr = A0;
int boardLed = D7;
int led = D0;
int speakerPin = D2;

const int songLength = 2;
char notes[] = "fb";
int beats[] = {4,2};
int tempo = 150;


char buttonString[40];
char pwrString[40];

void setup() {

pinMode(button, INPUT_PULLDOWN);
pinMode(pwr, OUTPUT);
digitalWrite(pwr, HIGH);
pinMode(boardLed, OUTPUT);

pinMode(speakerPin, OUTPUT);

Particle.subscribe("02", myHandler);


}


void loop() {


 //get the state of the button

 buttonCurrent = digitalRead(button);

 //turn it into a string (used for debugging)
 sprintf(buttonString, "%d", buttonCurrent);

 pwrCurrent = digitalRead(pwr);

 //turn it into a string (used for debugging)
 sprintf(pwrString, "%d", pwrCurrent);



 //if the button is not pressed


 if(buttonCurrent == HIGH){

     //SHAME! *DING DING DING*
     Particle.publish("01","hello");

     delay(250);

if(buttonCurrent == LOW){
    Particle.publish("01", "goodbye");
    delay(1000);
}



 }

 else{
     // do nothing
 }
}

void myHandler(const char*event, const char *data)

{
    if (strcmp(data,"hello")==0){
        digitalWrite(led,HIGH);
        digitalWrite(boardLed, HIGH);

        int i, duration;
        for (i= 0; i<songLength; i++){
            duration = beats[i]*tempo;
            if (notes[i]=='0'){
                delay(duration);}
                else{
                    tone(speakerPin, frequency(notes[i]), duration);
                    delay(duration);
                }
                delay(tempo/10);
                }



        delay(2000);
        digitalWrite(boardLed, LOW);
    }




    else {
        digitalWrite(led,LOW);
        digitalWrite(boardLed, LOW);
    }
}

int frequency(char note)
{
    int i;
    const int numNotes = 2;
    char names[] = {'f','b'};
    int frequencies[] = {330,392};

    for(i=0; i<numNotes;i++)
    {
        if (names[i] ==note)
        {return(frequencies[i]);
        }
    }
    return(0);
    }



    
