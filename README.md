# daq-serializer-24
For the purposes of data recording and serialization, we will be employing our own custom protocol, which aims to minimize the byte size of our data for faster transmission, allow for data-flexibility, and work on resource-limited environments. 

At a high level, this serialization protocol will use a user-defined schema to serialize the data into timestamps, or frames, of car data. 

## Why?

So why are we creating a new protocol instead of using well-known encoding schemes? There are a few reasons:

- We want to ********minimize******** the byte size of our data. Therefore, text-based formats, like JSON or XML are too big. We should serialize our data in bytes.
- We want to ensure that our protocol is **********flexible.********** The types of sensor data might change throughout the course of the year. Additionally, it would be nice if future years could use this format as well.

If we need these things, then why don’t we use libraries like Google’s Protobuf? Well:

- We do not need many of Protobuf’s features. All of our data is primitive. The C++ library in particular can be a bit unwieldy as well.
- We need version information for the schema in our serialization. This way, we can still use old data when we inevitably change the schema.
- Most of our data is the same type (float), therefore domain-specific optimizations can be created just for NFR.
- Microcontrollers are relatively low in resources — if our system is slow to serialize data, then the speed of serialization becomes more of a bottleneck than data size. Protobuf can have a lot of overhead.

## Defining a Schema for our Data

To ensure that the serialization protocol is robust, a user must define a schema in a ************.drive************ (**d**ata **r**elay **i**nstructions for ********v********ehicle ****e****ncoding). This is a proprietary schema file that describes what data to serialize, how it’s organized, and other meta information the serialization-protocol, such as the schema name and version.

An .drive file has a predefined structure:

1. **Meta** information about the serialization method
2. Type **definitions**
3. A data packet, called a ************frame************ definition

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

# frame definition (a special required definition
frame(CarData)

```

The serialization process will use this as a schema when creating frames to store.

## Serialization Protocol

Suppose that we implement a method of parsing schemas, and get to the final system of writing our data into bytes. How do we do this? At a high level, a fully serialized drive session will look like:

1. Metadata header
    1. Unique Byte Sequence to mark the start of car data
    2. Schema
    3. Version Numbers
2. Frames
    1. Sequence of Frames

****************************************Serializing Metadata****************************************

Metadata will only be stored at the start of serialization — it is a header. From a byte layout, it’ll look like this:

1. Unique Byte Sequence — TBD
2. Schema Name Bytes
    1. ,
    2. Length of the string (serialized as a int)
    3. The characters within the string
3. Version Bytes
    1. Short for Major Release Number (**********1.**********2.3)
    2. Short for Minor Release (1.**2**.3)
    3. Short for Build (1.2.**3)**

After the metadata is correctly processed, a sequence of metadata will be written

************************************Serializing Frames************************************

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

Then, for each field, we will flatten each field in the frame definition into it’s pure binary representation. There will be no padding. All data will be placed together as close together. The deserializer will use context from the schema to reconstruct the frame into it’s data types and data layout during runtime

### Overview

So a correct message of three frames would look like this (# are just comments to annotate):

```
data_start (unique bit identifier)
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
