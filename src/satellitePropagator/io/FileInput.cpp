//
// Created by Oliver on 13.05.21.
//

#include "FileInput.h"

FileInput::~FileInput() = default;

void FileInput::readDebrisData()
{
    switch (input_file_type) {
    case TXT:
        readDebrisTXT();
        break;
    }
}

struct FileInput::TxtLineContent FileInput::tokenizeLine(
    const std::string& line)
{
    TxtLineContent l;
    auto split_pos = line.find('=');
    l.token = line.substr(0, split_pos);
    l.value = line.substr(split_pos + 1);
    return l;
}

void FileInput::setDebrisValues(Debris::Debris& d, const std::string& line)
{
    auto position_split_pos = line.find('|');
    auto velocity_split_pos = line.find('|', position_split_pos + 1);
    auto acc_split_pos = line.find('|', velocity_split_pos + 1);
    auto aom_split_pos = line.find('|', acc_split_pos + 1);
    auto bc_inv_split_pos = line.find('|', aom_split_pos + 1);
    std::string position_str = line.substr(0, position_split_pos);
    std::string velocity_str = line.substr(position_split_pos + 1, velocity_split_pos);
    std::string acc_t0_str = line.substr(velocity_split_pos + 1, acc_split_pos);
    std::string acc_t1_str = line.substr(acc_split_pos + 1, aom_split_pos);
    std::string aom_str = line.substr(aom_split_pos + 1, bc_inv_split_pos);
    std::string bc_inv_str = line.substr(bc_inv_split_pos + 1);
    std::array<double, 3> vec {};

    auto x_split_pos = position_str.find(',');
    auto y_split_pos = position_str.find(',', x_split_pos + 1);
    vec[0] = stod(position_str.substr(0, x_split_pos));
    vec[1] = stod(position_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(position_str.substr(y_split_pos + 1));
    d.setPosition(vec);

    x_split_pos = velocity_str.find(',');
    y_split_pos = velocity_str.find(',', x_split_pos + 1);
    vec[0] = stod(velocity_str.substr(0, x_split_pos));
    vec[1] = stod(velocity_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(velocity_str.substr(y_split_pos + 1));
    d.setVelocity(vec);

    x_split_pos = acc_t0_str.find(',');
    y_split_pos = acc_t0_str.find(',', x_split_pos + 1);
    vec[0] = stod(acc_t0_str.substr(0, x_split_pos));
    vec[1] = stod(acc_t0_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(acc_t0_str.substr(y_split_pos + 1));
    d.setAccT0(vec);

    x_split_pos = acc_t1_str.find(',');
    y_split_pos = acc_t1_str.find(',', x_split_pos + 1);
    vec[0] = stod(acc_t1_str.substr(0, x_split_pos));
    vec[1] = stod(acc_t1_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(acc_t1_str.substr(y_split_pos + 1));
    d.setAccT1(vec);

    d.setAom(stod(aom_str));

    d.setBcInv(stod(bc_inv_str));
}

void FileInput::setConfigValues(const std::string& line)
{
    std::stringstream ss(line);
    for (int i = 0; i < 8; ++i) {
        ss >> acc_config[i];
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }
}

void FileInput::readDebrisTXT()
{
    std::ifstream input_file(input_file_path);
    std::string line;
    struct TxtLineContent line_content;
    Debris::Debris d;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            if (line.empty() or line[0] == '#') {
                continue;
            }
            line_content = tokenizeLine(line);
            if (line_content.value.empty()) {
                // no value
                continue;
            }
            if (line_content.token == "delta_t") {
                delta_t = stod(line_content.value);
            } else if (line_content.token == "write_delta_t") {
                write_delta_t = stod(line_content.value);
            } else if (line_content.token == "start_t") {
                start_t = stod(line_content.value);
            } else if (line_content.token == "end_t") {
                end_t = stod(line_content.value);
            } else if (line_content.token == "acc_config") {
                setConfigValues(line_content.value);
            } else if (line_content.token == "debris") {
                setDebrisValues(d, line_content.value);
                debris->addDebris(d);
            } else {
                // unknown token
            }
        }
    }
}

const Debris::DebrisContainer& FileInput::getDebris() const
{
    return *debris;
}

Debris::DebrisContainer& FileInput::getDebris()
{
    return *debris;
}

void FileInput::setDebris(Debris::DebrisContainer& debris)
{
    FileInput::debris = &debris;
}

const std::filesystem::path& FileInput::getInputFilePath() const
{
    return input_file_path;
}

std::filesystem::path& FileInput::getInputFilePath()
{
    return input_file_path;
}

void FileInput::setInputFilePath(const std::filesystem::path& inputFilePath)
{
    input_file_path = inputFilePath;
}

FileInput::Type FileInput::getInputFileType() const
{
    return input_file_type;
}

void FileInput::setInputFileType(FileInput::Type inputFileType)
{
    input_file_type = inputFileType;
}

double FileInput::getDeltaT() const
{
    return delta_t;
}

void FileInput::setDeltaT(double deltaT)
{
    delta_t = deltaT;
}

double FileInput::getWriteDeltaT() const
{
    return write_delta_t;
}

void FileInput::setWriteDeltaT(double writeDeltaT)
{
    write_delta_t = writeDeltaT;
}

double FileInput::getStartT() const
{
    return start_t;
}

void FileInput::setStartT(double startT)
{
    start_t = startT;
}

double FileInput::getEndT() const
{
    return end_t;
}

void FileInput::setEndT(double endT)
{
    end_t = endT;
}

const std::array<bool, 8>& FileInput::getAccConfig() const
{
    return acc_config;
}

std::array<bool, 8>& FileInput::getAccConfig()
{
    return acc_config;
}

void FileInput::setAccConfig(const std::array<bool, 8>& accConfig)
{
    acc_config = accConfig;
}
