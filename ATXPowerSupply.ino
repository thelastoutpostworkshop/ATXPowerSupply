
const int leds[] = {19, 18, 14, 15, 16, 17, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int ledsCount = sizeof(leds) / sizeof(leds[0]);

class LEDMatrix
{
private:
    // LED pins
    int leds[16];

    enum Sequence
    {
        CHECKERBOARD = 0,
        WAVE,
        FLASH,
        RAINFALL,
        SPIRAL,
        BOUNCINGBALL,
        SCANNERPATTERN,
        CORNERCROSS,
        RANDOMLEDS,
        ALTERNATEBLINKING,
        OPPOSITECORNER,
        SIMULATESOUNDLEVEL
    };

    const int squencesCount = 11;

    Sequence getRandomSequence()
    {
        int randomValue = random(squencesCount);
        return static_cast<Sequence>(randomValue);
    }

public:
    // Constructor
    LEDMatrix(int ledPins[16])
    {
        for (int i = 0; i < 16; i++)
        {
            leds[i] = ledPins[i];
        }
    }

    void playRandomSequence(void)
    {
        Sequence s = getRandomSequence();
        unsigned long delay = random(50, 500);
        unsigned long duration = random(10000L, 60000L);
        switch (s)
        {
        case CHECKERBOARD:
            Serial.println("checkerboard");
            checkerboard(delay, duration);
            break;
        case WAVE:
            Serial.println("wave");
            wave(delay, duration);
            break;
        case FLASH:
            Serial.println("flashAll");
            flashAll(delay, duration);
            break;
        case RAINFALL:
            Serial.println("rainfall");
            rainfall(delay, duration);
            break;
        case BOUNCINGBALL:
            Serial.println("bouncingBall");
            bouncingBall(delay, duration);
            break;
        case SCANNERPATTERN:
            Serial.println("scannerPattern");
            scannerPattern(delay, duration);
            break;
        case CORNERCROSS:
            Serial.println("cornerCross");
            cornerCross(delay, duration);
            break;
        case SPIRAL:
            Serial.println("spiral");
            spiral(delay, duration);
            break;
        case RANDOMLEDS:
            Serial.println("randomLed");
            randomLed(delay, duration);
            break;
        case ALTERNATEBLINKING:
            Serial.println("alternateBlinking");
            alternateBlinking(delay, duration);
            break;
        case OPPOSITECORNER:
            Serial.println("lightFromCornerToOpposite");
            lightFromCornerToOpposite(delay, duration);
            break;
        case SIMULATESOUNDLEVEL:
            Serial.println("simulateSound");
            simulateSound(delay, duration);
            break;
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
    void checkerboard(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
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
        int posX = 0;                          // Current horizontal position
        int posY = 0;                          // Current vertical position
        int directionX = random(0, 2) * 2 - 1; // Random horizontal direction of ball (-1 or 1)
        int directionY = random(0, 2) * 2 - 1; // Random vertical direction of ball (-1 or 1)

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

            // If ball hits an edge, randomize the bouncing direction
            if (posX == 0 || posX == 3)
            {
                directionX = random(0, 2) * 2 - 1; // Random horizontal direction of ball (-1 or 1)
            }
            if (posY == 0 || posY == 3)
            {
                directionY = random(0, 2) * 2 - 1; // Random vertical direction of ball (-1 or 1)
            }
        }
    }

    void scannerPattern(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        // Start with horizontal (row-wise) scanning
        bool horizontalScan = true;

        while (millis() - startTime < duration)
        {
            for (int i = 0; i < 4; i++)
            {
                // Switch off all LEDs
                for (int j = 0; j < 16; j++)
                {
                    digitalWrite(leds[j], LOW);
                }

                // Switch on the LEDs in the current row/column
                for (int j = 0; j < 4; j++)
                {
                    if (horizontalScan)
                    {
                        // Illuminate row
                        digitalWrite(leds[i * 4 + j], HIGH);
                    }
                    else
                    {
                        // Illuminate column
                        digitalWrite(leds[j * 4 + i], HIGH);
                    }
                }

                delay(delayTime);
            }

            // Alternate between horizontal and vertical scanning
            horizontalScan = !horizontalScan;
        }
    }

    void randomLed(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        // Continue animation until duration time has passed
        while (millis() - startTime < duration)
        {
            for (int i = 0; i < 16; i++)
            {
                int r = random(2);
                if (r == 0)
                {
                    digitalWrite(leds[i], HIGH);
                }
                else
                {
                    digitalWrite(leds[i], LOW);
                }
            }
            delay(delayTime);
        }
    }
    void clearDisplay(void)
    {
        all(LOW);
    }
    void cornerCross(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        // Continue animation until duration time has passed
        while (millis() - startTime < duration)
        {
            // Turn on opposite corners
            digitalWrite(leds[0], HIGH);  // Top left
            digitalWrite(leds[15], HIGH); // Bottom right

            delay(delayTime);

            // Turn off opposite corners
            digitalWrite(leds[0], LOW);  // Top left
            digitalWrite(leds[15], LOW); // Bottom right

            delay(delayTime);

            // Turn on other set of opposite corners
            digitalWrite(leds[3], HIGH);  // Top right
            digitalWrite(leds[12], HIGH); // Bottom left

            delay(delayTime);

            // Turn off other set of opposite corners
            digitalWrite(leds[3], LOW);  // Top right
            digitalWrite(leds[12], LOW); // Bottom left

            delay(delayTime);
        }
    }

    void alternateBlinking(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        // Select two distinct random rows
        int row1 = random(0, 4); // Rows are 0-indexed
        int row2;
        do
        {
            row2 = random(0, 4);
        } while (row2 == row1);

        while (millis() - startTime < duration)
        {
            // Turn on the LEDs in the first row
            for (int i = 0; i < 4; i++)
            {
                digitalWrite(leds[row1 * 4 + i], HIGH); // Adjust this if your setup differs
            }

            // Wait for a short period of time
            delay(delayTime);

            // Turn off the LEDs in the first row
            for (int i = 0; i < 4; i++)
            {
                digitalWrite(leds[row1 * 4 + i], LOW); // Adjust this if your setup differs
            }

            // Turn on the LEDs in the second row
            for (int i = 0; i < 4; i++)
            {
                digitalWrite(leds[row2 * 4 + i], HIGH); // Adjust this if your setup differs
            }

            // Wait for a short period of time
            delay(delayTime);

            // Turn off the LEDs in the second row
            for (int i = 0; i < 4; i++)
            {
                digitalWrite(leds[row2 * 4 + i], LOW); // Adjust this if your setup differs
            }
        }
    }
    void lightFromCornerToOpposite(unsigned long delayTime, unsigned long duration)
    {
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
        {
            // Choose a random corner
            int corner = random(0, 4); // 0: top-left, 1: top-right, 2: bottom-left, 3: bottom-right
            int startX, startY, stepX, stepY;

            // Determine start points and direction of movement
            switch (corner)
            {
            case 0: // top-left
                startX = startY = 0;
                stepX = stepY = 1;
                break;
            case 1: // top-right
                startX = 3;
                startY = 0;
                stepX = -1;
                stepY = 1;
                break;
            case 2: // bottom-left
                startX = 0;
                startY = 3;
                stepX = 1;
                stepY = -1;
                break;
            case 3: // bottom-right
                startX = startY = 3;
                stepX = stepY = -1;
                break;
            }

            // Move through the LEDs
            for (int i = 0; i < 4; i++)
            {
                // Turn on the current LED and its neighbors
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        int x = startX + i * stepX + dx;
                        int y = startY + i * stepY + dy;
                        if (x >= 0 && x < 4 && y >= 0 && y < 4)
                        {
                            digitalWrite(leds[y * 4 + x], HIGH);
                        }
                    }
                }

                // Check if the duration has passed
                if (millis() - startTime >= duration)
                {
                    return;
                }

                // Wait for a short period of time
                delay(delayTime);
            }

            // After lighting up the diagonal and its neighbors, wait before moving to the next corner
            delay(delayTime);
        }

        // When duration has passed, turn off all LEDs
        for (int i = 0; i < 16; i++)
        {
            digitalWrite(leds[i], LOW);
        }
    }

    void simulateSound(unsigned long delayTime, unsigned long duration)
    {
        int minSoundValue = 0;
        int maxSoundValue = 1023;
        unsigned long startTime = millis();

        while (millis() - startTime < duration)
        {
            int soundLevel = random(minSoundValue, maxSoundValue + 1);

            for (int i = 0; i < 16; i++)
            {
                // LEDs will light up based on the simulated sound level
                int threshold = map(i, 0, 15, minSoundValue, maxSoundValue);
                if (soundLevel >= threshold)
                {
                    digitalWrite(leds[i], HIGH);
                }
                else
                {
                    digitalWrite(leds[i], LOW);
                }
            }
            delay(100);
        }
    }
};

LEDMatrix ledMatrix(leds);

void setup()
{
    randomSeed(analogRead(0));
    Serial.begin(9600);
    ledMatrix.begin();
    ledMatrix.flashAll(300, 10000);
}

void loop()
{
    // ledMatrix.playRandomSequence();
    // ledMatrix.all(LOW);
    // unsigned long delay = random(10000L, 30000L);
    // unsigned long duration = random(60000L, 300000L);
    // Serial.println("randomLed in Loop");
    // ledMatrix.randomLed(delay, duration);
    // ledMatrix.all(LOW);

    ledMatrix.simulateSound(200, 10000);
}