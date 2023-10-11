#include "file_processing.hpp"
#include <iomanip>

FileProcessor::FileProcessor(const std::string& filename)
 : FileReader(filename) {

    // Get the current timestamp in the json headers
    auto currentTime = std::chrono::system_clock::now();
    _jsonObject["timestamp"] = std::chrono::system_clock::to_time_t(currentTime);
    
}

nlohmann::json FileProcessor::writeData(const std::string& city, const std::string& unit,
 const std::string& dateFrom, const std::string& dateTo = ""){
    
    // Set private attributes
    _city = city;
    _unit = unit;
    _dateFrom = dateFrom;
    _dateTo = dateTo;

    // Set rest of the JSON headers
    _jsonObject["city"] = city;
    _jsonObject["unit"] = unit;

    std::vector<std::string> row;
    int iEntry = 0;
    std::setprecision(1);

    // Skip csv headers
    getNextRow(row);

    while(getNextRow(row)){
        // Add data matching the requested data
        if(_matchRequestParams(row)){
            _jsonObject["data"][iEntry++] = {{"date", row[0]}, 
                                             {"T_max", _setTempUnit(std::stof(row[2]))}, 
                                             {"T_min", _setTempUnit(std::stof(row[3]))}, 
                                             {"humidity", std::stof(row[4])}};
        }
    }
    
    return _jsonObject;
 }


bool FileProcessor::_matchRequestParams(std::vector<std::string> row){
    // Compare the city
    if (row[1] != _city)
        return false;

    // Compare the dates
    if (_dateTo.empty())
        _dateTo = _dateFrom;

    return (row[0] >= _dateFrom) && (row[0] <= _dateTo);
        
}

float FileProcessor::_setTempUnit(float temperature){
        return (_unit == "F") ? 32+9/5*temperature : temperature;
}