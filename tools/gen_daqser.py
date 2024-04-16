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

def board_messages(dbc_file_path, board):
    messages = []
    with open(dbc_file_path, "r") as dbc_file:
        reader = csv.DictReader(dbc_file)
        for row in reader:
            senders_raw = row["Sender"]
            senders = senders_raw[1:-1].split(", ")
            if board in senders:
                message = row["Message Name"]
                if message not in messages:
                    messages.append(message)
    return messages

def message_signals(dbc_file_path, message):
    signals = []
    with open(dbc_file_path, "r") as dbc_file:
        reader = csv.DictReader(dbc_file)
        for row in reader:
            if row["Message Name"] == message:
                signal = row["Signal Name"]
                if signal not in signals:
                    signals.append(signal)
    return signals


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
        drive_file.write(f"\t.version: {version}\n")
        drive_file.write(f"}}\n\n")

        # write the board's signals
        for board in selected_boards:
            drive_file.write(f"# {board}\n")
            messages = board_messages(dbc_file_path, board)

            for message in messages:
                drive_file.write(f"message {message} {{\n")
                signals = message_signals(dbc_file_path, message)
                for signal in signals:
                    drive_file.write(f"\t{signal}\n")
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