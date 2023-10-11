#ifndef FILE_READING_HPP
#define FILE_READING_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief 
 * 
 */
class FileReader {
public:
   
    FileReader(const std::string& filename);

    /**
     * @brief Get the Next Row object
     * 
     * @param row 
     * @return true 
     * @return false 
     */
    bool getNextRow(std::vector<std::string>& row);

private:
    std::ifstream _file;

    /**
     * @brief 
     * 
     * @param input 
     * @return std::string 
     */
    std::string _cleanString(const std::string& input);
};

#endif 