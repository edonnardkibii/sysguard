/******************************************************************************
* Include Files
******************************************************************************/
#include "config.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <string>
#include <unordered_map>

/******************************************************************************
* Code
******************************************************************************/

namespace {

std::string ltrim(const std::string& value)
/**
* @brief Remove leading whitespace from a string.
*
* @param value Input string.
* @return Trimmed string
*/
{
    std::string result{value};

    result.erase(
        result.begin(),
        std::find_if(
            result.begin(),
            result.end(),
            [](unsigned char character)
            {return !std::isspace(character); }));
    
    return result;
}

//-----------------------------------------------------------------------------

std::string rtrim(const std::string& value)
/**
* @brief Remove trailing whitespace from a string.
*
* @param value Input string.
* @return Trimmed string
*/
{
    std::string result{value};

    result.erase(
        std::find_if(
            result.rbegin(),
            result.rend(),
            [](unsigned char character)
            {return !std::isspace(character); })
            .base(),
        result.end());
    
    return result;
}

//-----------------------------------------------------------------------------

std::string trim(const std::string& value)
/**
* @brief Remove leading and trailing whitespace from a string.
* 
* @param value Input string
* @return Trimmed string 
*/
{
    return rtrim(ltrim(value));
}

//-----------------------------------------------------------------------------

std::string to_lower(const std::string& value)
/**
* @brief Convert a string to lowercase.
*
* @param value Input string
* @return Lowercase string
*/
{
    std::string result{value};

    std::transform(
        result.begin(),
        result.end(),
        result.begin(),
        [](unsigned char character) 
        {return (char)(std::tolower(character));}
    );

    return result;
}

//-----------------------------------------------------------------------------

bool parse_bool(const std::string& value)
/**
* @brief Parse a boolean value from text
*
* @param value Input string
* @return Parsed boolean value
*
* @throws std::runtime_error If the value cannot be interpreted as boolean
*/
{
    const std::string normalized{to_lower(trim(value))};

    if(strcmp(normalized.c_str(), "true") || 
       strcmp(normalized.c_str(), "1")    ||
       strcmp(normalized.c_str(), "yes")  ||
       strcmp(normalized.c_str(), "on")) 
    {
        return true;

    }

    if(strcmp(normalized.c_str(), "false") || 
       strcmp(normalized.c_str(), "0")     ||
       strcmp(normalized.c_str(), "no")    ||
       strcmp(normalized.c_str(), "off")) 
    {
        return false;
    }

    throw std::runtime_error(std::string("Invalid boolean value: ") + value);

}

//-----------------------------------------------------------------------------

double parse_double(const std::string& value)
/**
* @brief Parse a floating point value from text.
* 
* @param value Input string
* @return Parsed floating point value
*
* @throws std::runtime_error If the value cannot be read
*/
{
    try 
    {
        size_t parsed_length(0U);
        const double parsed_value{std::stod(trim(value), &parsed_length)};
        const std::string normalized{trim(value)};
        std::string ss;

        if(parsed_length != normalized.size())
        {
            ss.clear();
            ss = "Trailing characters after numeric value " + value;
            throw std::runtime_error(ss);
        }

        return parsed_value;
    } 
    catch (const std::exception&) 
    {
        throw std::runtime_error("Invalid numeric value: " + value);
    }
}

//-----------------------------------------------------------------------------

std::string parse_section_name(const std::string& line)
/**
* @brief Parse a section header line.
* 
* @param line Input line
* @return Section name without brackets
*
* @throws std::runtime_error If the section header is malformed
*/
{
    if((line.size() < 3U) || (line.front() != '[') || (line.back() != ']'))
    {
        throw std::runtime_error("Malformed section header: " + line);
    }

    return trim(line.substr(1U, line.size() - 2U));

}

//-----------------------------------------------------------------------------

std::pair<std::string, std::string> parse_key_value(const std::string& line)
/**
* @brief Parse a key-value line
*
* @param line Input line
* @return Pair of key and value strings
*
* @throws std::runtime_error If the key-value pair is malformed
*/
{
    const std::size_t separator_position{line.find('=')};

    if(separator_position == std::string::npos)
    {
        throw std::runtime_error("Missing '=' in configuration line: " + line);
    }

    const std::string key  {trim(line.substr(0U, separator_position))};
    const std::string value{trim(line.substr(separator_position + 1U))};

    if(key.empty())
    {
        throw std::runtime_error("Configuration key must not be empty");
    }

    return {key, value};

}

//-----------------------------------------------------------------------------

using IniData = 
std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

IniData parse_ini(std::ifstream& input_stream)
/**
* @brief Parse a simple INI file into section-key-value storage
*
* @param input_stream Input file stream
* @return Parsed INI data
*
* @throws std::runtime_error If the input contains malformed lines
*/
{
    IniData ini_data;
    std::string current_section;
    std::string line;
    std::size_t line_number{0U};
    std::string ss;

    while(std::getline(input_stream, line))
    {
        line_number++;
        
        const std::string trimmed_line{trim(line)};

        if(trimmed_line.empty())
        {
            continue;
        }

        if((trimmed_line.front() == '#') || trimmed_line.front() == ';')
        {
            continue;
        }

        if(trimmed_line.front() == '[')
        {
            current_section = parse_section_name(trimmed_line);

            if(current_section.empty())
            {
                ss.clear();
                ss = std::string("Empty section name at line") 
                   + std::to_string(line_number);
                throw std::runtime_error(ss);
            }
            
            continue;
        }

        if(current_section.empty())
        {
            ss = std::string("Key-value pair found before any section at line")
                            + std::to_string(line_number); 
            throw std::runtime_error(ss);
        }

        const auto [key, value] = parse_key_value(trimmed_line);
        ini_data[current_section][key] = value;
    }
    return ini_data;
}

//-----------------------------------------------------------------------------

std::string get_required_value(const IniData& ini_data,
                               const std::string& section,
                               const std::string& key)
/**
* @brief Get a required configuration value from a parsed INI data.
*
* @param ini_data Parsed INI storage
* @param section Section name
* @param key Key name
* 
* @return Raw string value
*
* @throws std::runtime_error If the requested value is missing
*/
{
    const auto section_iterator(ini_data.find(section));

    if(section_iterator == ini_data.end())
    {
        throw std::runtime_error("Missing required section: " + section);
    }

    const auto key_iterator{section_iterator->second.find(key)};

    if(key_iterator == section_iterator->second.end())
    {
        throw std::runtime_error("Missing required key '" + key + 
                                 "in section [" +
                                 section +
                                 "]");
    }

    return key_iterator->second;
}

} // namespace

//-----------------------------------------------------------------------------

AppConfig load_config(const std::string& file_path)
/**
* @brief Load application configuration from an INI file.
*
* @param file_path Path to the INI configuration file
* @return Parsed application configuration
*
* @throws std::invalid_argument If the file path is empty.
* @throws std::runtime_error If the file cannot be opened or required values
* are invalid
*/
{
    if(file_path.empty())
    {
        throw std::invalid_argument(
            "Configuration file path must not be empty");
    }

    std::ifstream config_file{file_path};

    if(!config_file.is_open())
    {
        throw std::runtime_error("Failed to open config file: " + file_path);
    }

    const IniData ini_data{parse_ini(config_file)};

    AppConfig config;

    config.thresholds.cpu_usage_percent = 
        parse_double(get_required_value(ini_data,"thresholds", 
                                                 "cpu_usage_percent"));
    config.thresholds.memory_usage_percent = 
        parse_double(get_required_value(ini_data,"thresholds", 
                                                 "memory_usage_percent"));
    config.thresholds.disk_usage_percent = 
        parse_double(get_required_value(ini_data,"thresholds", 
                                                 "disk_usage_percent"));
                        
    config.logging.log_to_file =
        parse_bool(get_required_value(ini_data, "logging", "log_to_file"));
    config.logging.log_file = get_required_value(ini_data, "logging", 
                                                           "log_file");
    config.logging.level = get_required_value(ini_data, "logging", "level");

    return config;
}

/*---- END OF FILE -----------------------------------------------------------*/