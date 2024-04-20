#include <Arduino.h>
#include <CAN.h>
#include <virtualTimer.h>
#include <vector>

#include "daqser_can.hpp"
#include "daqser.hpp"

VirtualTimerGroup g_timerGroup;

// List of boards to listen to
std::vector<std::string> g_listenToBoards = {
    "BMS", "MCU", "WHEEL", "SUS", // etc
};

// Function to record and send data
// Called every 100ms
void recordData()
{
    //  Prepare data from the CAN bus for serialization
    daqser::updateSignals(g_listenToBoards);
    // Serialize the data, and get the raw bytes
    std::vector<std::uint8_t> byteData = daqser::serializeFrame();
    // send the data over lora or something
    // send(byteData);
}

void setup()
{
    Serial.begin(115200);
    // Initialize the daqser library
    daqser::initialize();
    // Tell daqser what schema we are using to serialize the data
    daqser::setSchema("test-api-basic", 1, 0, 1);
    // Tell daqser to record/send data from these boards
    g_timerGroup.AddTimer(100, recordData);
}

void loop()
{
    g_timerGroup.Tick();
}
