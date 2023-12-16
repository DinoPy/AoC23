#include <iostream>
#include <vector>

bool isValid(int row, int col, int numRows, int numCols) {
    return row >= 0 && row < numRows && col >= 0 && col < numCols;
}

int calculatePartSum(const std::vector<std::string>& schematic, int row, int col) {
    int numRows = schematic.size();
    int numCols = schematic[0].size();
    int sum = 0;

    // Check adjacent positions, including diagonals
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int newRow = row + dr;
            int newCol = col + dc;

            // Skip the center position
            if (dr == 0 && dc == 0) {
                continue;
            }

            // Check if the new position is valid
            if (isValid(newRow, newCol, numRows, numCols)) {
                // Check if the character at the new position is a digit
                if (std::isdigit(schematic[newRow][newCol])) {
                    // Convert the character to an integer and add it to the sum
                    sum += schematic[newRow][newCol] - '0';
                }
            }
        }
    }

    return sum;
}

int main() {
    // Example engine schematic as a vector of strings
    std::vector<std::string> schematic = {
        "467..114..",
        "...*......",
        "..35..633.",
        "......#...",
        "617*......",
        ".....+.58.",
        "..592.....",
        "......755.",
        "...$.*....",
        ".664.598.."
    };

    int numRows = schematic.size();
    int numCols = schematic[0].size();
    int totalSum = 0;

    // Iterate through the schematic to calculate the sum of part numbers
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // Check if the current position contains a digit
            if (std::isdigit(schematic[row][col])) {
                // Calculate the sum of part numbers at the current position
                totalSum += calculatePartSum(schematic, row, col);
            }
        }
    }

    // Output the result
    std::cout << "Sum of part numbers: " << totalSum << std::endl;

    return 0;
}

