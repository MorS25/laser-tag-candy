#define MOTOR_PIN A2
#define LED_PIN A1

void candyHandler(const char *event, const char *data)
{
    giveCandy("");
}


int giveCandy(String params) {
    digitalWrite(MOTOR_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(MOTOR_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
}

void setup() {
    Particle.subscribe("Give_Candy", candyHandler);
    
    Particle.function("giveCandy", giveCandy);
    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    
}
