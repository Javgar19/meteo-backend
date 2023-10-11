#include <iostream>
#include "./libs/nlohmann/json.hpp"
#include "./file_handler/file_processing.hpp"


int main(int argc, char **argv){

    if(argc < 5){
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }

    // Parse command line arguments
    const std::string filename = argv[1];
    const std::string city = argv[2];
    const std::string unit = argv[3];
    const std::string dateFrom = argv[4];
    const std::string dateTo = (argc == 6) ? argv[5] : "";

    FileProcessor fileProcessor(filename);
    nlohmann::json json_obj = fileProcessor.writeData(city, unit, dateFrom, dateTo);
    
    std::cout << std::setw(4) << json_obj;
    return 0;
}