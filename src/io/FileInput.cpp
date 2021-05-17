//
// Created by Oliver on 13.05.21.
//

#include "FileInput.h"

FileInput::~FileInput() {

}

void FileInput::readDebrisData() {
    switch (input_file_type) {
        case TXT:
            readDebrisTXT();
            break;
    }
}

struct FileInput::TxtLineContent FileInput::tokenizeLine(const std::string& line) {
    TxtLineContent l;
    auto split_pos = line.find('=');
    l.token = line.substr(0, split_pos);
    l.value = line.substr(split_pos + 1);
    return l;
}

void FileInput::setDebrisValues(Debris::Debris &d, const std::string &line) {
    auto position_split_pos = line.find("|");
    auto velocity_split_pos = line.find("|", position_split_pos + 1);
    auto acc_split_pos = line.find("|", velocity_split_pos + 1);
    std::string position_str = line.substr(0, position_split_pos);
    std::string velocity_str = line.substr(position_split_pos + 1, velocity_split_pos);
    std::string acc_t0_str = line.substr(velocity_split_pos + 1, acc_split_pos);
    std::string acc_t1_str = line.substr(acc_split_pos + 1);
    std::array<double,3> vec;

    auto x_split_pos = position_str.find(",");
    auto y_split_pos = position_str.find("," , x_split_pos + 1);
    vec[0] = stod(position_str.substr(0, x_split_pos));
    vec[1] = stod(position_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(position_str.substr(y_split_pos + 1));
    d.setPosition(vec);

    x_split_pos = velocity_str.find(",");
    y_split_pos = velocity_str.find("," , x_split_pos + 1);
    vec[0] = stod(velocity_str.substr(0, x_split_pos));
    vec[1] = stod(velocity_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(velocity_str.substr(y_split_pos + 1));
    d.setVelocity(vec);

    x_split_pos = acc_t0_str.find(",");
    y_split_pos = acc_t0_str.find("," , x_split_pos + 1);
    vec[0] = stod(acc_t0_str.substr(0, x_split_pos));
    vec[1] = stod(acc_t0_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(acc_t0_str.substr(y_split_pos + 1));
    d.setAccT0(vec);

    x_split_pos = acc_t1_str.find(",");
    y_split_pos = acc_t1_str.find("," , x_split_pos + 1);
    vec[0] = stod(acc_t1_str.substr(0, x_split_pos));
    vec[1] = stod(acc_t1_str.substr(x_split_pos + 1, y_split_pos));
    vec[2] = stod(acc_t1_str.substr(y_split_pos + 1));
    d.setAccT1(vec);
}

void FileInput::setConfigValues(const std::string &line) {
    std::stringstream ss(line);
    for (int i = 0; i < 8; ++i) {
        ss >> acc_config[i];
        if(ss.peek() == 's'){
            ss.ignore();
        }
    }
}

void FileInput::readDebrisTXT() {
    std::ifstream input_file(input_file_name);
    std::string line;
    struct TxtLineContent content;
    Debris::Debris d;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            if (line.empty() or line[0] == '#') {
                continue;
            }
            content = tokenizeLine(line);
            if (content.value.empty()) {
                // no value
                continue;
            }
            if (content.token == "delta_t") {
                delta_t = stod(content.value);
            } else if (content.token == "start_t") {
                start_t = stod(content.value);
            } else if (content.token == "end_t") {
                end_t = stod(content.value);
            } else if (content.token == "acc_config"){
                setConfigValues(content.value);
            }else if (content.token == "debris"){
                setDebrisValues(d, content.value);
                debris.addDebris(d);
            }else {
                // unknown token
            }
        }
    }
}

Debris::DebrisContainer &FileInput::getDebris()  {
    return debris;
}

void FileInput::setDebris(Debris::DebrisContainer &debris) {
    FileInput::debris = debris;
}

 std::string &FileInput::getInputFileName()  {
    return input_file_name;
}

void FileInput::setInputFileName( std::string &inputFileName) {
    input_file_name = inputFileName;
}

FileInput::Type FileInput::getInputFileType()  {
    return input_file_type;
}

void FileInput::setInputFileType(FileInput::Type inputFileType) {
    input_file_type = inputFileType;
}

double FileInput::getDeltaT()  {
    return delta_t;
}

void FileInput::setDeltaT(double deltaT) {
    delta_t = deltaT;
}

double FileInput::getStartT()  {
    return start_t;
}

void FileInput::setStartT(double startT) {
    start_t = startT;
}

double FileInput::getEndT()  {
    return end_t;
}

void FileInput::setEndT(double endT) {
    end_t = endT;
}

 std::array<bool, 8> &FileInput::getAccConfig()  {
    return acc_config;
}

void FileInput::setAccConfig( std::array<bool, 8> &accConfig) {
    acc_config = accConfig;
}

