with open("sheepdog_randomread.log", "r") as file:
    ignore = True  # Flag to ignore lines until [Oct26 23:06] is found
    ignoreUntil = "[Oct26 23:06]"
    for line in file:
        if ignore and not line.startswith(ignoreUntil):
            continue
        ignore = False  # Stop ignoring lines once [Oct26 23:06] is found

        if len(line) >= 20 and line[16:20] == "OOOO":
            start = line.find("<<<")
            end = line.find(">>>")
            if start != -1 and end != -1:
                start += 3  # Move past '<<<'
                text = line[start:end]
                tokens = text.split(">,<")

                # Print tokens separated by tabs and add a newline
                print("\t".join(tokens))

