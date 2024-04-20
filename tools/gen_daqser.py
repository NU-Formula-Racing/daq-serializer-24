# gen_daqser.py
# Responsible for generating DAQ Serializer code, that being:
# - daqser_can.hpp - Which contains the integration of the CAN bus with the DAQ Serializer
# - .drive files - Which contain the DAQ Serializer configuration

# Expected CSV format:
# Message ID,Message Name,Sender,Signal Name,Start Bit,Size,Factor,Offset,Min,Max,Unit,Cycle Time

import os
import sys
import re
import csv
import argparse

class CANSignal:
    def __init__(self, name, start_bit, size, factor, offset, min_val, max_val, unit):
        self.name = name
        self.start_bit = start_bit
        self.size = size
        self.factor = factor
        self.offset = offset
        self.min_val = min_val
        self.max_val = max_val
        self.unit = unit
        self.data_type = None

    def set_data_type(self, data_type):
        self.data_type = data_type

    def get_data_type(self):
        if self.data_type:
            return self.data_type
        
        # determine the data type based on the size of the signal
        if self.size <= 8:
            self.data_type = "bool"
        elif self.size <= 16:
            self.data_type = "float"
        elif self.size <= 32:
            self.data_type = "double"

        return self.data_type
    
class CANMessage:
    def __init__(self, name, id, sender, cycle_time):
        self.name = name
        self.id = id
        self.sender = sender
        self.cycle_time = cycle_time
        self.signals = []

    def add_signal(self, signal):
        self.signals.append(signal)

    def get_signals(self):
        return self.signals

    def get_signal(self, signal_name):
        for signal in self.signals:
            if signal.name == signal_name:
                return signal
        return None


def parse_dbc(dbc_file_path):
    def not_number(s):
        try:
            float(s)
            return False
        except ValueError:
            return True
        
    messages = {}
    with open(dbc_file_path, "r") as dbc_file:
        reader = csv.DictReader(dbc_file)
        for row in reader:
            message_id = row["Message ID"]
            message_name = row["Message Name"]
            sender = row["Sender"]
            # remove the brackets from the cycle time
            sender = sender[1:-1]
            # remove the quotes, either ' or ", from the sender
            sender = sender.replace("'", "").replace('"', "")
            print(sender)

            cycle_time = row["Cycle Time"]

            if not message_id or not message_name or not sender or not cycle_time:
                print("Invalid row. Skipping...")
                continue

            # make sure that the signal name, start bit, and size are not empty
            if not_number(row["Start Bit"]) or not_number(row["Size"]) or not row["Signal Name"]:
                print("Invalid signal. Skipping...")
                continue

            # we if factor, offset, min, and max are not provided, default them
            if not_number(row["Factor"]):
                row["Factor"] = 1.0
            if not_number(row["Offset"]):
                row["Offset"] = 0.0
            if not_number(row["Min"]):
                row["Min"] = 0.0
            if not_number(row["Max"]):  
                row["Max"] = 0.0

            # print(row)

            signal_name = row["Signal Name"]
            start_bit = int(row["Start Bit"])
            size = int(row["Size"])
            factor = float(row["Factor"])
            offset = float(row["Offset"])
            min_val = float(row["Min"])
            max_val = float(row["Max"])

            unit = row["Unit"]

            signal = CANSignal(signal_name, start_bit, size, factor, offset, min_val, max_val, unit)
            # find the message in the dictionary by message_name
            if message_name in messages:
                message = messages[message_name]
            else:
                message = CANMessage(message_name, message_id, sender, cycle_time)
                messages[message_name] = message

            message.add_signal(signal)

    return messages.values()

# UTILITIES
def all_boards(dbc_file_path):
    boards = []
    with open(dbc_file_path, "r") as dbc_file:
        reader = csv.DictReader(dbc_file)
        for row in reader:
            senders_raw = row["Sender"]
            # get rid of the brackets, and split the string into a list
            senders = senders_raw[1:-1].split(", ")
            for sender in senders:
                # remove ' and "
                sender = sender.replace("'", "").replace('"', "")
                if sender not in boards:
                    boards.append(sender)

    return boards


def gen_drive(dbc_file_path):
    schema_name = input("Enter schema name: ")
    version = input("Enter schema version: ")

    while True:
        # check that the version is the correct format
        # should be in the format of x.y.z
        if re.match(r"^\d+\.\d+\.\d+$", version):
            break
        else:
            print("Invalid version format. Please enter the version in the format x.y.z")
            version = input("Enter schema version: ")

    path = input("Enter the path to save the .drive file: ")
    while not os.path.isdir(path):
        print("Invalid path. Please enter a valid path")
        path = input("Enter the path to save the .drive file: ")

    available_boards = all_boards(dbc_file_path)
    print("Please select the boards to include in the schema:")
    for i, board in enumerate(available_boards):
        print(f"{i+1}. {board}")

    selected_boards = []
    while True:
        selection = input("Enter the number of the board to include, or 'done' to finish: ")
        if selection == "done":
            break
        try:
            selection = int(selection)
            if selection < 1 or selection > len(available_boards):
                print("Invalid selection. Please enter a valid number")
                continue
            selected_boards.append(available_boards[selection-1])
        except ValueError:
            print("Invalid selection. Please enter a valid number")
            continue

    print(f"Generating .drive file for {schema_name} version {version} with the following boards:")
    for board in selected_boards:
        print(board)

    # generate the .drive file
    drive_file_path = os.path.join(path, f"{schema_name}_v{version}.drive")
    with open(drive_file_path, "w") as drive_file:
        # write the schema name and version
        drive_file.write(f"meta {{\n")
        drive_file.write(f"\t.schema: '{schema_name}';\n")
        drive_file.write(f"\t.version: {version};\n")
        drive_file.write(f"}}\n\n")

        # write the board's signals
        messages = parse_dbc(dbc_file_path)
        for board in selected_boards:
            drive_file.write(f"# {board} Messages\n")
            for message in messages:
                if message.sender == board:
                    drive_file.write(f"def {message.name} {{\n")
                    for signal in message.signals:
                        drive_file.write(f"\t{signal.get_data_type()} {signal.name}; # {signal.unit};\n")
                    drive_file.write(f"}}\n\n")

    
def gen_cpp(dbc_file_path):
    pass

# main
def main():
    # commands for the user
    # -h, --help: show help
    # gen-drive: generate .drive files
    #  prompts the user for schema name, version number, and the list of boards to be included in the schema
    #  by default, the list of boards is all boards in the csv file
    # gen-cpp: generate daqser_can.hpp
    # the user can also specify the csv file to use for either command

    parser = argparse.ArgumentParser(description="Generate DAQ Serializer code")
    parser.add_argument("command", help="Command to execute", choices=["gen-drive", "gen-cpp"])
    parser.add_argument("-f", "--file", help="CSV file to use for generating the code")
    args = parser.parse_args()

    if args.file:
        dbc_file_path = args.file
    else:
        # default to the current directory, and look for a "dbc.csv" file
        dbc_file_path = os.path.join(os.getcwd(), "dbc.csv")
        print(dbc_file_path)
        if not os.path.exists(dbc_file_path):
            print("No CSV file found. Please specify a CSV file to use")
            sys.exit(1)

    print(f"Using {dbc_file_path} as the CSV file")

    if args.command == "gen-drive":
        gen_drive(dbc_file_path)
    elif args.command == "gen-cpp":
        gen_cpp(dbc_file_path)


if __name__ == "__main__":
    main()