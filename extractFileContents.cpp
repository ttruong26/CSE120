#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void extractContent(const string &inputFile, const map<string, string> &phraseToFile)
{
    ifstream inFile(inputFile);
    if (!inFile)
    {
        cerr << "Unable to open input file: " << inputFile << endl;
        return;
    }

    map<string, ofstream> fileMap; // Map to store output file streams

    string line;

    while (getline(inFile, line))
    {
        // Check if the line starts with any of the specified phrases
        for (const auto &pair : phraseToFile)
        {
            const string &phrase = pair.first;
            if (line.compare(0, phrase.length(), phrase) == 0)
            {
                const string &filename = pair.second;

                // Check if we've encountered this phrase before
                if (fileMap.find(filename) == fileMap.end())
                {
                    // If not, create a new file
                    fileMap[filename].open(filename + ".txt");
                }
                // Write the line to the appropriate file (doesn't work)
                if (phrase == "DATA")
                {
                    // Write the phrase into the file
                    fileMap[filename] << line << endl;
                    // Append all lines under the phrase into the corresponding file
                    while (getline(inFile, line))
                    {
                        // Check if we've encountered another section
                        if (line.find("Cairn:") == 0 || line.find("LINES") == 0)
                            break;
                        fileMap[filename] << line << endl;
                    }
                    // Continue to the next line after writing the DATA section
                    continue;
                }
                // else if (phrase == "LINES") {
                //     // Write the phrase into the file
                //     fileMap[filename] << line << endl;
                //     // Append all lines under the phrase into the corresponding file
                //     while (getline(inFile, line)) {
                //         if (line.find("Cairn:") == 0 || line.find("DATA") == 0)
                //             break;
                //         fileMap[filename] << line << endl;
                //     }
                // }
                else
                {
                    fileMap[filename] << line << endl;
                }
                break; // Move to the next line after writing
            }
        }
    }

    // Close all output files
    for (auto &pair : fileMap)
    {
        pair.second.close();
    }

    inFile.close();
    std::cout << "Content successfully extracted from .map file to .txt file." << std::endl;
}

int main()
{
    std::string mapFile;
    std::cout << "Please enter a .map file to open: ";
    std::cin >> mapFile;

    // Specify the phrases and corresponding output file names
    map<string, string> phraseToFile = {
        {"Cairn: GoalWithHeading", "extracted_GOALS"},
        {"LINES", "extracted_LINES"},
        {"DATA", "extracted_DATA"}};

    extractContent(mapFile, phraseToFile);

    return 0;
}
