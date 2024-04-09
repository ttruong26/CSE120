#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>

using namespace std;

// Function to parse lines from the text file and populate the lineSegments vector
void parseLines(const string& filename, vector<pair<int, int>>& lineSegments) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int x1, y1, x2, y2;
        ss >> x1 >> y1 >> x2 >> y2;
        lineSegments.emplace_back(x1, y1);
        lineSegments.emplace_back(x2, y2);
    }

    file.close();
}

int main() {
    string filename = "extracted_LINES.txt"; // Change the filename accordingly
    vector<pair<int, int>> lineSegments;

    // Parse the lines from the file
    parseLines(filename, lineSegments);

    // Output the parsed line segments
    cout << "Parsed line segments:" << endl;
    cout << "{ ";
    for (const auto& segment : lineSegments) {
        cout << "{ " << segment.first << ", " << segment.second << " }, ";
    }
    cout << "}" << endl;

    return 0;
}
