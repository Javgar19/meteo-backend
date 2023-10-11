#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <chrono>
#include "file_reading.hpp"
#include "../libs/nlohmann/json.hpp"


class FileProcessor : public FileReader {
public:
    FileProcessor(const std::string& filename);

    nlohmann::json writeData(const std::string& city, const std::string& unit,
     const std::string& dateFrom, const std::string& dateTo);

private:
    nlohmann::json _jsonObject;
    std::string _city, _unit, _dateFrom, _dateTo;

    bool _matchRequestParams(std::vector<std::string> row);
    float _setTempUnit(float temperature);

};

#endif 