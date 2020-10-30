import csv
import sys

def line_to_tuple (line):
    return (
        (line['Valid'] == "Yes"),
        (line['Dirty'] == "Yes"),
        (line['Exclusive'] == "Yes"),
        (line['Share'] == "Yes"),
        (line['LastReader'] == "Yes"),
    )

def tuple_to_state (a_tuple):
    if (a_tuple == (False, False, False, False, False)):
        return "Invalid"
    elif (a_tuple == (True, False, False, False, True)):
        return "Shared"
    elif (a_tuple == (True, True, False, False, False)):
        return "Modified"
    elif (a_tuple == (True, False, True, False, False)):
        return "Exclusive"
    else:
        valid = a_tuple[0]
        dirty = a_tuple[1]
        exclusive = a_tuple[2]
        share = a_tuple[3]
        last_reader = a_tuple[4]
        # (valid, dirty, exclusive, share, last_reader) = a_tuple
        return (
            "{"
            + ("Valid" if valid else "Invalid")
            + ", "
            + ("Dirty" if dirty else "Clean")
            + ", "
            + ("Exclusive" if exclusive else "Not Exclusive")
            + ", "
            + ("Can Share" if share else "Can't Share")
            + ", "
            + ("Last Reader" if last_reader else "Not Last Reader")
            + "}"
        )

state_of_line = dict()
state_count = dict()

with open(sys.argv[1]) as csvfile:
    clusterdata = csv.DictReader(csvfile)
    for row in clusterdata:
        address = row['Address']
        current_state = (
            state_of_line[address] if (address in state_of_line) else None
        )
        new_state = tuple_to_state(line_to_tuple(row))

        if ((current_state == None) or (current_state == "Invalid")):
            state_of_line[address] = new_state
        elif (new_state != "Invalid"):
            state_of_line[address] = (current_state + " | " + new_state)

for entry in state_of_line:
    state = state_of_line[entry]

    print(entry + ": " + state)

    if (state in state_count):
        state_count[state] = (state_count[state] + 1)
    else:
        state_count[state] = 1

for entry in state_count:
    print(entry + ": " + str(state_count[entry]))
