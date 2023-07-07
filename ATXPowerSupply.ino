
const int leds[] = {19, 18, 14, 15, 16, 17, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int ledsCount = sizeof(leds) / sizeof(leds[0]);

void setup(void)
{
    for (int i = 0; i < ledsCount; i++)
    {
        pinMode(leds[i], OUTPUT);
        digitalWrite(leds[i], HIGH);
    }
}

void loop(void)
{
}