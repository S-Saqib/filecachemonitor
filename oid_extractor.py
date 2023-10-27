unique_strings = set()  # Create a set to store unique strings from the first column

with open("sheepdog_oid_offset.txt", "r") as file:  # Replace "input.txt" with your file name
    for line in file:
        columns = line.strip().split('\t')  # Split the line into columns by tabs
        if len(columns) >= 1:
            first_column = columns[0]  # Get the first column
            unique_strings.add(first_column)  # Add the first column to the set

# Print the unique strings in the first column
for string in unique_strings:
    print(string)

