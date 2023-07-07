
const int leds[] = {19, 18, 14, 15, 16, 17, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int ledsCount = sizeof(leds) / sizeof(leds[0]);

class LEDMatrix
{
public:
    // LED pins
    int leds[16];

    // Constructor
    LEDMatrix(int ledPins[16])
    {
        for (int i = 0; i < 16; i++)
        {
            leds[i] = ledPins[i];
        }
    }

    // Initialize all LED pins as OUTPUT
    void begin()
    {
        for (int i = 0; i < 16; i++)
        {
            pinMode(leds[i], OUTPUT);
        }
    }

    void all(int value)
    {
        for (int i = 0; i < 16; i++)
        {
            digitalWrite(leds[i], value);
        }
    }

    // Turn on LEDs by row
    void rowOn(int rowNum, int delayTime)
    {
        for (int i = rowNum * 4; i < (rowNum * 4) + 4; i++)
        {
            digitalWrite(leds[i], HIGH);
            delay(delayTime);
            digitalWrite(leds[i], LOW);
        }
    }

    // Turn on LEDs by column
    void columnOn(int colNum, int delayTime)
    {
        for (int i = colNum; i < 16; i += 4)
        {
            digitalWrite(leds[i], HIGH);
            delay(delayTime);
            digitalWrite(leds[i], LOW);
        }
    }

    // Zigzag pattern
    void zigzag(int delayTime)
    {
        for (int i = 0; i < 4; i++)
        {
            rowOn(i, delayTime);
        }
        for (int i = 2; i >= 0; i--)
        {
            rowOn(i, delayTime);
        }
    }

    // Rapidly blink all LEDs
    void blink(int delayTime, int numBlinks)
    {
        for (int j = 0; j < numBlinks; j++)
        {
            for (int i = 0; i < 16; i++)
            {
                digitalWrite(leds[i], HIGH);
            }
            delay(delayTime);
            for (int i = 0; i < 16; i++)
            {
                digitalWrite(leds[i], LOW);
            }
            delay(delayTime);
        }
    }

    // Checkerboard pattern
    void checkerboard(int delayTime, int count)
    {
        for (int j = 0; j < count; j++)
        {
            for (int i = 0; i < 16; i++)
            {
                if ((i / 4 % 2 == 0 && i % 2 == 0) || (i / 4 % 2 == 1 && i % 2 == 1))
                {
                    digitalWrite(leds[i], HIGH);
                }
                else
                {
                    digitalWrite(leds[i], LOW);
                }
            }
            delay(delayTime);
            for (int i = 0; i < 16; i++)
            {
                if ((i / 4 % 2 == 0 && i % 2 == 0) || (i / 4 % 2 == 1 && i % 2 == 1))
                {
                    digitalWrite(leds[i], LOW);
                }
                else
                {
                    digitalWrite(leds[i], HIGH);
                }
            }
            delay(delayTime);
        }
        all(LOW);
    }

    // Wave pattern with specified duration and delay
    void wave(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
        {
            // Light up the outer frame
            for (int i = 0; i < 4; i++)
            {
                digitalWrite(leds[i], HIGH);      // Top row
                digitalWrite(leds[15 - i], HIGH); // Bottom row
            }
            digitalWrite(leds[4], HIGH); // Left column
            digitalWrite(leds[7], HIGH);
            digitalWrite(leds[8], HIGH);
            digitalWrite(leds[11], HIGH); // Right column

            delay(delayTime);

            // Turn off the outer frame and light up the inner frame
            for (int i = 0; i < 4; i++)
            {
                digitalWrite(leds[i], LOW);      // Top row
                digitalWrite(leds[15 - i], LOW); // Bottom row
            }
            digitalWrite(leds[4], LOW); // Left column
            digitalWrite(leds[7], LOW);
            digitalWrite(leds[8], LOW);
            digitalWrite(leds[11], LOW); // Right column

            digitalWrite(leds[5], HIGH); // Inner frame
            digitalWrite(leds[6], HIGH);
            digitalWrite(leds[9], HIGH);
            digitalWrite(leds[10], HIGH);

            delay(delayTime);

            // Turn off the inner frame
            digitalWrite(leds[5], LOW);
            digitalWrite(leds[6], LOW);
            digitalWrite(leds[9], LOW);
            digitalWrite(leds[10], LOW);

            delay(delayTime);
        }
    }

    void flashAll(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
        {
            all(HIGH);

            delay(delayTime);

            // Turn off all LEDs
            all(LOW);

            delay(delayTime);
        }
    }
};

LEDMatrix ledMatrix(leds);

void setup()
{
    ledMatrix.begin();
    // ledMatrix.wave(200, 10000);
    ledMatrix.flashAll(200, 10000);
    ledMatrix.all(LOW);
}

void loop()
{

}