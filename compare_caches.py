def read_lines(filename):
    with open(filename, 'r') as file:
        return set(file.read().splitlines())

file1_lines = read_lines('client_cached_pages.txt')
file2_lines = read_lines('server_cached_pages.txt')

# Find common lines
common_lines = file1_lines.intersection(file2_lines)

# Find lines only in file 1
unique_to_file1 = file1_lines.difference(file2_lines)

# Find lines only in file 2
unique_to_file2 = file2_lines.difference(file1_lines)

print(str(len(common_lines)) + " pages in both client and server.")
#for line in common_lines:
    #print(line)

print(str(len(unique_to_file1)) + " pages only in client.")
#for line in unique_to_file1:
    #print(line)

print(str(len(unique_to_file2)) + " pages only in server.")
#for line in unique_to_file2:
    #print(line)
