#include "file_reading.hpp"


FileReader::FileReader(const std::string& filename) : _file(filename) {
    // Open csv file
    if (!_file.is_open()){
        std::cerr << "Failed to open csv file " << filename << std::endl;
    }
}



bool FileReader::getNextRow(std::vector<std::string>& row) {
    row.clear(); // Clear the existing contents

    if (!_file.is_open() || _file.eof()) {
        return false; // Return false if the file is not open or at the end
    }

    std::string line;
    
    // Tokenize the line based on the CSV delimiter (';')
    if (std::getline(_file, line)) { 
        std::istringstream iss(line);
        std::string token;

        while (std::getline(iss, token, ';')) {
            row.push_back(_cleanString(token)); // Clean data and add it to the row vector
        }
    }

    return true;
}


std::string FileReader::_cleanString(const std::string& input) {
    std::string result;

    for (char c : input) {
        if (c == ' ') {
            // Skip white spaces
            continue;
        } else if (c == ',') {
            // Substitute comma with a dot
            result += '.';
        } else {
            // Keep other characters
            result += c;
        }
    }

    return result;
}