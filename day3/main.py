import sys
file_name = sys.argv[1]

grid = open(file_name).read().splitlines()
cs = set()

# go thorough every row w/ index
for r, row in enumerate(grid):
    # go thorugh every column w/ index
    for c, ch in enumerate(row):
        # if char is a digit or "." we skip, currently looking for symbols
        if ch.isdigit() or ch == ".":
            continue
        print(f" Symbol Coords: {r}:{c}")

        # we will loop through every index row that's adjacent to the current row
        for cr in [r - 1, r, r + 1]:
            # we will loop through every index column that's adjacent to the current column
            for cc in [c - 1, c, c + 1]:
                # cover for edge cases: if we are out of bounds for both columns and rows we ship as well as the current value is not a number
                if cr < 0 or cr >= len(grid) or cc < 0 or cc >= len(grid[cr]) or not grid[cr][cc].isdigit():
                    continue
                print(f"{grid[cr][cc]}")
                # we will move the cursor back until the symbol we are at is not a digit. we will say cc -1 (when accesing grid) to look ahead
                while cc > 0 and grid[cr][cc-1].isdigit():
                    cc -= 1
                cs.add((cr, cc))

print(cs)
ns = []

for r, c in cs:
    s = ""
    while c < len(grid[r]) and grid[r][c].isdigit():
        s += grid[r][c]
        c += 1
    ns.append(int(s))

print(sum(ns))
