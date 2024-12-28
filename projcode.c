#include <LPC214x.H>

int main()
{
    unsigned int status1, status2;
    int calorieRate, addingValue, healthyLimit;
    PINSEL0 = 0x00000000;
    IODIR0 = 0x00007B44; // Updated IODIR0 value to include LEDs
    calorieRate = 500; // Input calorie rate
    addingValue = 100; // Value to add or subtract from the calorie rate
    healthyLimit = 2000; // Healthy calorie limit
    
    // Initially, turn off all LEDs except LED 3
    IOSET0 = (1 << 12); // LED 3 on
    IOCLR0 = (1 << 14); // LED 4 off
    
    while (1)
    {
        status1 = (IOPIN0 & (1 << 1)); // switch 1
        status2 = (IOPIN0 & (1 << 6)); // switch 2
        
        // LED 1: Add the addingValue to the calorie rate
        if (status1)
        {
            IOSET0 = (1 << 8); // LED 1 on
            calorieRate += addingValue;
        }
        else
        {
            IOCLR0 = (1 << 8); // LED 1 off
        }
        
        // LED 2: Subtract the addingValue from the calorie rate
        if (status2)
        {
            IOSET0 = (1 << 10); // LED 2 on (Pin P0.10)
            calorieRate -= addingValue;
            
            if (calorieRate < 0)
                calorieRate = 0;
        }
        else
        {
            IOCLR0 = (1 << 10); // LED 2 off (Pin P0.10)
        }
        
        // LED 3: Calorie rate is lower than the input calorie rate
        if (calorieRate < 500) // Replace "500" with the desired input calorie rate value
        {
            IOSET0 = (1 << 12); // LED 3 on
            IOCLR0 = (1 << 14); // LED 4 off
        }
        else if (calorieRate >= healthyLimit)
        {
            // LED 4: Calorie rate is higher than or equal to the healthy limit
            IOSET0 = (1 << 14); // LED 4 on
            IOCLR0 = (1 << 12); // LED 3 off
        }
        else
        {
            IOCLR0 = (1 << 12); // LED 3 off
            IOCLR0 = (1 << 14); // LED 4 off
        }
    }
}
