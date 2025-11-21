#include <stdio.h>
#include <stdlib.h>

#define HOURS_IN_DAY 24

// Thresholds for alerting
#define TEMP_THRESHOLD 40.0
#define HUMIDITY_THRESHOLD 85.0
#define PRESSURE_THRESHOLD 1020.0

// Structure to store weather data
typedef struct {
    float temperature;
    float humidity;
    float pressure;
} WeatherData;

// Function prototypes
void recordHourlyReadings(WeatherData *data, int hours);
void computeDailyAverages(WeatherData *data, int hours, float *avgTemp, float *avgHumidity, float *avgPressure);
void checkAlerts(WeatherData *data, int hours);
void displaySummary(float avgTemp, float avgHumidity, float avgPressure);

int main() {
    WeatherData *dayData = (WeatherData *)malloc(HOURS_IN_DAY * sizeof(WeatherData));
    if (dayData == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }

    printf("Weather Monitoring System: Enter hourly readings for 24 hours.\n");

    recordHourlyReadings(dayData, HOURS_IN_DAY);

    float avgTemp, avgHumidity, avgPressure;
    computeDailyAverages(dayData, HOURS_IN_DAY, &avgTemp, &avgHumidity, &avgPressure);

    displaySummary(avgTemp, avgHumidity, avgPressure);

    checkAlerts(dayData, HOURS_IN_DAY);

    free(dayData);
    return 0;
}

// Function to record hourly readings from the user
void recordHourlyReadings(WeatherData *data, int hours) {
    for (int i = 0; i < hours; i++) {
        printf("Hour %d:\n", i + 1);
        printf("  Temperature (°C): ");
        scanf("%f", &data[i].temperature);
        printf("  Humidity (%%): ");
        scanf("%f", &data[i].humidity);
        printf("  Pressure (hPa): ");
        scanf("%f", &data[i].pressure);
    }
}

// Function to compute daily averages of temperature, humidity and pressure
void computeDailyAverages(WeatherData *data, int hours, float *avgTemp, float *avgHumidity, float *avgPressure) {
    float tempSum = 0, humiditySum = 0, pressureSum = 0;

    for (int i = 0; i < hours; i++) {
        tempSum += data[i].temperature;
        humiditySum += data[i].humidity;
        pressureSum += data[i].pressure;
    }

    *avgTemp = tempSum / hours;
    *avgHumidity = humiditySum / hours;
    *avgPressure = pressureSum / hours;
}

// Function to display daily average summary
void displaySummary(float avgTemp, float avgHumidity, float avgPressure) {
    printf("\nDaily Averages:\n");
    printf("  Average Temperature: %.2f °C\n", avgTemp);
    printf("  Average Humidity: %.2f %%\n", avgHumidity);
    printf("  Average Pressure: %.2f hPa\n", avgPressure);
}

// Function to check and display alerts for extreme conditions
void checkAlerts(WeatherData *data, int hours) {
    printf("\nAlerts for Extreme Conditions:\n");
    int alertFlag = 0;

    for (int i = 0; i < hours; i++) {
        if (data[i].temperature > TEMP_THRESHOLD) {
            printf("  Hour %d: Temperature exceeds threshold (%.2f °C > %.2f °C)\n", i + 1, data[i].temperature, TEMP_THRESHOLD);
            alertFlag = 1;
        }
        if (data[i].humidity > HUMIDITY_THRESHOLD) {
            printf("  Hour %d: Humidity exceeds threshold (%.2f %% > %.2f %%)\n", i + 1, data[i].humidity, HUMIDITY_THRESHOLD);
            alertFlag = 1;
        }
        if (data[i].pressure > PRESSURE_THRESHOLD) {
            printf("  Hour %d: Pressure exceeds threshold (%.2f hPa > %.2f hPa)\n", i + 1, data[i].pressure, PRESSURE_THRESHOLD);
            alertFlag = 1;
        }
    }

    if (!alertFlag) {
        printf("  No extreme condition alerts for the day.\n");
    }
}
