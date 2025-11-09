#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int getTempCategory(float temp)
{
    // 0 = cold 1 = warm 2 = hot
    if (temp <= 15.0f)
        return 0; 
    else if (temp > 15.0f && temp < 30.0f)
        return 1; 
    else
        return 2;
}


int getHumidityCategory(float hum)
{
    if (hum <= 40.0f)
        return 0; // Low
    else if (hum > 40.0f && hum < 70.0f)
        return 1; // Medium
    else
        return 2; // High
}

string getFanSpeed(int temp_cat, int hum_cat)
{
    int speed = 0; 

    switch (temp_cat)
    {
    case 0: // Cold
        switch (hum_cat)
        {
        case 0:
            speed = 0;
            break; 
        case 1:
            speed = 1;
            break; 
        case 2:
            speed = 1;
            break; 
        }
        break;

    case 1: // Warm
        switch (hum_cat)
        {
        case 0:
            speed = 1;
            break; 
        case 1:
            speed = 1;
            break; 
        case 2:
            speed = 2;
            break; 
        }
        break;

    case 2: 
        switch (hum_cat)
        {
        case 0:
            speed = 1;
            break; // Low -> Medium
        case 1:
            speed = 2;
            break; // Medium -> High
        case 2:
            speed = 2;
            break; // High -> High
        }
        break;

    default:
        return "Unknown";
    }

    switch (speed)
    {
    case 0:
        return "Low";
    case 1:
        return "Medium";
    case 2:
        return "High";
    default:
        return "Unknown";
    }
}

int main()
{
    vector<float> temperatures = {12.5, 20.0, 31.0, 16.5};
    vector<float> humidities = {35.0, 50.0, 75.0, 65.0};

    if (temperatures.size() != humidities.size())
    {
        cout << "Mismatched data sizes." << endl;
        return 1;
    }

    cout << "Temp\tHum\tFan Speed" << endl;
    cout << "-----------------------------" << endl; 

    for (size_t i = 0; i < temperatures.size(); ++i)
    {
        int temp_cat = getTempCategory(temperatures[i]);
        int hum_cat = getHumidityCategory(humidities[i]);
        string fan_speed = getFanSpeed(temp_cat, hum_cat);

        cout << temperatures[i] << "\t" << humidities[i] << "\t" << fan_speed << endl;
    }

    return 0;
}
