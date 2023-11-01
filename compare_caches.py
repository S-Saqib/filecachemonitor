def read_lines(filename):
    with open(filename, 'r') as file:
        return set(file.read().splitlines())

client_lines = read_lines('client_cached_pages.txt')
server0_lines = read_lines('server0_cached_pages.txt')
server1_lines = read_lines('server1_cached_pages.txt')
server2_lines = read_lines('server2_cached_pages.txt')

serverAll_lines = server0_lines.union(server1_lines.union(server2_lines))

print("Similarity between client and server caches (unified)")
# Find common lines
common_lines = client_lines.intersection(serverAll_lines)

# Find lines only in client cache
unique_to_client = client_lines.difference(serverAll_lines)

# Find lines only in unified server cache
unique_to_server_unified = serverAll_lines.difference(client_lines)

print(str(len(common_lines)) + " pages in both client and server (unified).")
#for line in common_lines:
    #print(line)

print(str(len(unique_to_client)) + " pages only in client.")
#for line in unique_to_client:
    #print(line)

print(str(len(unique_to_server_unified)) + " pages only in server (unified).")
#for line in unique_to_server_unified:
    #print(line)

print("Similarity between server caches")
# Find common lines
otherServerLines = server1_lines.union(server2_lines)

common_lines = server0_lines.intersection(otherServerLines)

# Find lines only in server cache
unique_to_server0 = server0_lines.difference(otherServerLines)

# Find lines only in unified server cache
unique_to_other_servers = otherServerLines.difference(server0_lines)

print(str(len(common_lines)) + " pages in both gateway and backup servers.")
#for line in common_lines:
    #print(line)

print(str(len(unique_to_server0)) + " pages only in gateway server.")
#for line in unique_to_server0:
    #print(line)

print(str(len(unique_to_other_servers)) + " pages only in backup servers (unified).")
#for line in unique_to_other_servers:
    #print(line)

