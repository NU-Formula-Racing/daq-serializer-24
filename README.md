<div align="center">
  <img src="docs/img//drive-logo.png" width=25%>

  <br>

  <a href="https://evanbs.com/portfolio/1">
	<img src="https://img.shields.io/badge/Blog_Post-blah?style=for-the-badge&logo=checkmarx&logoColor=white&color=243E36" alt="Blog Post"/>
  </a>

  <a href="https://marketplace.visualstudio.com/items?itemName=evanbs.drive">
	<img src="https://img.shields.io/badge/Visual_Studio_Code-Extension-007ACC?style=for-the-badge&logo=visual-studio-code&logoColor=white&color=007ACC" alt="Visual Studio Code Extension"/>
  </a>

</div>

# daqser (daq-serializer)

**daqser** (daq-serializer) is a custom serialization protocol designed and implemented as a part of Northwestern Formula's Data Acquisition (DAQ) Effort. It aims to remove the overhead of encoding metadata (things that RL and TLV binary encoding schemes suffer from) into your serialized data.

daqser is intended to run in resource-limited environments, such as microcontrollers, and is designed to be fast and efficient. As of now, full support have been implemented for ESP32, Teensy 4.0, and Arduino.

## Why?

daqser was created to solve the problem of encoding metadata into serialized data. In a typical serialization protocol, metadata is encoded into the data, which can be a problem when you have a space-limited environment. daqser solves this problem by encoding metadata separately from the data, allowing for a more efficient serialization process. Specifically, daqser was developed with the intent of being used for wireless data transmission in a Formula SAE car, where large packets of data are not an option for us.


## Defining a DRIVE Schema

To ensure that the serialization protocol is robust, a user must define a schema in a **.drive** (**d**ata **r**elay **i**nstructions for **v**ehicle **e**ncoding). This is a proprietary schema file that describes what data to serialize, how it’s organized, and other meta information the serialization-protocol, such as the schema name and version.

A DRIVE Schema has a predefined structure:

1. **Meta** information about the serialization method
2. Type **definitions**
3. A data packet, called a **frame**

An example .drive file will look like this:

```
# meta information about the serialization method
meta
{
	# required meta-information (denoted with the '.')
	.schema : "nfr-serial-24";
	.version : 1.0.0;
}

# definitions
def DateTime
{
	long long timeSince1990;
}

def CarData
{
	DateTime timestamp;
	float ambientTemp;
	bool isOverheating;
	float coolantTemp;
	float coolantFlowRate;
	bool coolantLeak;
}

# frame definition (a special required definition)
frame(CarData)

```

The serialization process will use this as a schema when creating frames to store.

## Serialization Protocol

At a high level, a fully serialized message/collection of frames will look like this:

1. Metadata header
   1. Unique Byte Sequence to mark the start of car data
   2. Schema
   3. Version Numbers
2. Frames of data
   1. Sequence of Frames

**Serializing Metadata**

Metadata will only be stored/transmitted (depending on the application) at the start of serialization — it is a header. From a byte layout, it’ll look like this:

1. Schema Name Bytes
   1. Length of the string (serialized as a uint8_t)
   2. The characters within the string, encoded in UTF-8
2. Version Bytes
   1. uint8_t for Major Release (**1**.2.3)
   2. uint8_t for Minor Release (1.**2**.3)
   3. uint8_t for Patch (1.2.**3)**
   
By encoding this metadata, users are will be able to grab the correct DRIVE schema to deserialize the data. Because of this design, the deserializer and serializer will both need to have the same schema to work. This is a limitation of the protocol, but for many cases, the DRIVE Schema can simply be stored/transmitted with the data. 

**Serializing Frames**

First, we will reduce the data into purely primitive types, so our frame would look like this:

```
frame
{
	# START_DateTime
	long timeSince1990;
	# END_DateTime
	float ambientTemp;
	bool isOverheating;
	float coolantTemp;
	float coolantFlowRate;
	bool coolantLeak;
}
```

Then, for each field, we will flatten each field in the frame definition into it’s pure binary representation. There will be no padding. All data will be placed together as close together. The deserializer will use context from the schema to reconstruct the frame into it’s data types and data layout during runtime.

### Overview

So a correct message of three frames would look like this (# are just comments to annotate):

```
# schema_name
	name_len
	name_chars[]
# frame start...
# frame_1
	timeSince1990 # part of timestamp
	ambientTemp
	isOverheating
	coolantTemp
	coolantFlowRate
	coolantLeak
# frame_2
	timeSince1990 # part of timestamp
	ambientTemp
	isOverheating
	coolantTemp
	coolantFlowRate
	coolantLeak
# frame_3
	timeSince1990 # part of timestamp
	ambientTemp
	isOverheating
	coolantTemp
	coolantFlowRate
	coolantLeak
```

## Usage
In a simple arduino sketch, you can use the following code to serialize data:

```cpp
#include <Arduino.h>
#include <daqser.hpp>

#define VERSION_ARGS(major, minor, patch) major, minor, patch

#define SCHEMA_NAME "example_schema"
#define SCHEMA_VERSION VERSION_ARGS(1, 0, 0)

void setup()
{
  Serial.begin(9600);
  // Initialize the daqser library
  daqser::initialize();
  // Tell daqser what schema we are using to serialize the data
  daqser::setSchema(SCHEMA_NAME, SCHEMA_VERSION);
  // alternatively, you can set the schema using this:
  // This will set the schema to the current schema, which is should be an enviornment variable called
  // CUR_SCHEMA, which points to the file path of the schema
  // daqser::setSchemaToCur(); 
  // similarly, you can set the schema from serialized metadata, which is an std::vector<uint8_t>
  // this is useful if you are communicating with another device that is sending the schema
  // daqser::setSchemaFromSerializedMeta(std::vector<uint8_t> metadata);
}

void loop()
{
  // Set the data, maybe from a sensor
  daqser::set("temperature", 25.0f);
  daqser::set("isOverheating", false);
  daqser::set("coolantTemp", 30.0f);

  // similarly, you can get the data
  float temperature = daqser::get<float>("temperature");
  bool isOverheating = daqser::get<bool>("isOverheating");
  float coolantTemp = daqser::get<float>("coolantTemp");

  // you can also get the serialized metadata
  std::vector<uint8_t> metadata = daqser::serializedSchema();
  // or you can print it out, for debugging
  daqser::printSchema();
  // you can also get the schema, if you want to
  daqser::impl::Schema schema = daqser::getSchema();

  // when you are done modifying the data, you can serialize it
  std::vector<uint8_t> serialized = daqser::serializeFrame();
  // then you can do whatever, like send it over serial, or send it over a network
  // for example, sending it over serial
  Serial.write(serialized.data(), serialized.size());
}
```

If you are using NFR's CAN and Timer libraries, you can use the following code to listen to CAN messages and serialize them:

```cpp
#include <Arduino.h>
#include <daqser.hpp>
#include <daqser_can.hpp>
#include <virtualTimer.h>

#define VERSION_ARGS(major, minor, patch) major, minor, patch

#define SCHEMA_NAME "can_usage"
#define SCHEMA_VERSION VERSION_ARGS(1, 0, 0)

VirtualTimerGroup timerGroup;

// Function to record and send data
// Called every 100ms
void recordData()
{
  //  Prepare data from the CAN bus for serialization
  daqser::updateSignals();
}

// Report the data, send it over lora or something
void reportData()
{
  // Serialize the data, and get the raw bytes
  std::vector<std::uint8_t> byteData = daqser::serializeFrame();
  // send the data over lora or something
  // send(byteData);
  // print out the bytes
  std::cout << "Data(length:" << byteData.size() << "): ";
  for (std::uint8_t byte : byteData)
  {
    Serial.print(byte, HEX);
    Serial.print(" ");
  }
  Serial.println();
}


void setup()
{
  Serial.begin(9600);
  // Initialize the daqser library
  daqser::initialize();
  // Tell daqser what schema we are using to serialize the data
  daqser::setSchema(SCHEMA_NAME, SCHEMA_VERSION);
  daqser::initializeCAN();
  // Tell daqser to record/send data from these boards
  timerGroup.AddTimer(100, recordData);
  timerGroup.AddTimer(1000, reportData);
  
  daqser::initializeCAN();
}

void loop()
{
  timerGroup.Tick(millis());
  daqser::tickCAN();
}
```

For NU Formula specifically, we have the option to add enviornment variables that allow us to set the boards we are listening to over CAN. Otherwise, this functionality doesn't work, as the daqser_can integration is very specific to NU Formula's CAN usage. These enviornment variables follow the convention of RX_<board_name>, where board_name is the name of the board we are listening to. For example, if we are listening to the IMD board, we would set RX_IMD to 1 (or any other value).
