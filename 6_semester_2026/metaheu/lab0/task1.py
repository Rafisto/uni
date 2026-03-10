def read_tsp(filename: str):
    with open(filename, 'r') as file:
        lines = file.readlines()
        read_section = False
        for i, line in enumerate(lines):
            if line.strip() == 'NODE_COORD_SECTION':
                read_section = True
                continue
            if not read_section or line.strip() == '':
                continue
            if line.strip() == 'EOF':
                break

            parts = line.split()
            if len(parts) < 3:
                continue
