#include <notas.h>

#define RGBblue 2
#define echopin 5
#define trigpin 6
#define buzzerpassive 7
#define activebuzzer 4

void setled(int led)
{
  pinMode(led, OUTPUT);
}

void setsonar(int echo, int trig)
{
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
}

void led(int led, int del)
{
    digitalWrite(led, HIGH);
    delay(del);
    digitalWrite(led, LOW);
    delay(del);
}

float sonar(int echo, int trig)
{
    float duration;
    float distance;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Mede a resposta do trigPin no echo Pin
    duration = pulseIn(echo, HIGH);
  
    // Determina a distância pela duração
    // Usar 343 metros por segundo (velocidade do som)
    distance = (duration/2) * 0.0343;

    return distance;
}

int melodia[] = {NOTE_AS4, NOTE_AS4, NOTE_CS4, NOTE_CS4, NOTE_F4, NOTE_F4, NOTE_DS4};
int duracaoNotas[] = {4, 4, 4, 4, 4, 4, 4};

void songpassive(int pinbuzzer)
{
    pinMode(pinbuzzer, OUTPUT);

    for (int notaatual = 0; notaatual < 8; notaatual++)
    {
        int noteduration = 1000 / duracaoNotas[notaatual];
        tone(buzzerpassive, melodia[notaatual]* 4, noteduration);
        int notepause = noteduration * 1.30;
        delay(notepause);
        noTone(buzzerpassive);
    }
    
}
