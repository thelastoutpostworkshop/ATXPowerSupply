
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

    void movingDot(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
        {
            // Cycle through each LED on the perimeter
            for (int i = 0; i < 16; i++)
            {
                // Turn off all LEDs
                for (int j = 0; j < 16; j++)
                {
                    digitalWrite(leds[j], LOW);
                }

                // Turn on current LED
                digitalWrite(leds[i], HIGH);
                delay(delayTime);
            }
        }
    }

    void rainfall(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
        {
            for (int column = 0; column < 4; column++)
            {
                // Turn off all LEDs
                for (int i = 0; i < 16; i++)
                {
                    digitalWrite(leds[i], LOW);
                }

                // Turn on LEDs in a column
                for (int row = 0; row < 4; row++)
                {
                    digitalWrite(leds[column + (4 * row)], HIGH);
                }
                delay(delayTime);
            }
        }
    }

    void spiral(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
        {
            for (int i = 0; i < 4; i++)
            { // Loop for each layer
                for (int j = i; j < 4 - i; j++)
                { // Top row
                    digitalWrite(leds[i * 4 + j], HIGH);
                    delay(delayTime);
                    digitalWrite(leds[i * 4 + j], LOW);
                }
                for (int j = i + 1; j < 4 - i; j++)
                { // Right column
                    digitalWrite(leds[j * 4 + 4 - i - 1], HIGH);
                    delay(delayTime);
                    digitalWrite(leds[j * 4 + 4 - i - 1], LOW);
                }
                for (int j = i + 1; j < 4 - i; j++)
                { // Bottom row
                    digitalWrite(leds[(4 - i - 1) * 4 + 4 - j - 1], HIGH);
                    delay(delayTime);
                    digitalWrite(leds[(4 - i - 1) * 4 + 4 - j - 1], LOW);
                }
                for (int j = i + 1; j < 4 - i - 1; j++)
                { // Left column
                    digitalWrite(leds[(4 - j - 1) * 4 + i], HIGH);
                    delay(delayTime);
                    digitalWrite(leds[(4 - j - 1) * 4 + i], LOW);
                }
            }
        }
    }

    void bouncingBall(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();
        int directionX = 1; // Horizontal direction of ball
        int directionY = 1; // Vertical direction of ball
        int posX = 0;       // Current horizontal position
        int posY = 0;       // Current vertical position

        while (millis() - startTime < duration)
        {
            // Switch off all LEDs
            for (int i = 0; i < 16; i++)
            {
                digitalWrite(leds[i], LOW);
            }

            // Switch on the LED at current ball position
            digitalWrite(leds[posY * 4 + posX], HIGH);

            delay(delayTime);

            // Move ball position
            posX += directionX;
            posY += directionY;

            // Bounce if ball hits an edge
            if (posX == 0 || posX == 3)
            {
                directionX = -directionX;
            }
            if (posY == 0 || posY == 3)
            {
                directionY = -directionY;
            }
        }
    }
};

LEDMatrix ledMatrix(leds);

void setup()
{
    ledMatrix.begin();
    // ledMatrix.wave(200, 10000);
    // ledMatrix.flashAll(200, 10000);
    // ledMatrix.movingDot(200, 10000);
    ledMatrix.bouncingBall(200, 10000);
}

void loop()
{
}