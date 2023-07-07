
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
    void checkerboard(int delayTime)
    {
        for (int j = 0; j < 20; j++)
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
};

LEDMatrix ledMatrix(leds);

void setup()
{
    ledMatrix.begin();
}

void loop()
{
    ledMatrix.rowOn(1, 200);
    delay(1000);
    ledMatrix.columnOn(2, 200);
    delay(1000);
    ledMatrix.zigzag(200);
    delay(1000);
    ledMatrix.blink(100, 10);
    delay(1000);
    ledMatrix.checkerboard(500);
    delay(1000);
}