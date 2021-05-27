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
struct FileInput::TLEContent FileInput::parseTLE(const std::array<std::string,3> &lines){
    TLEContent tle;
    //line 1
    tle.name = lines[0];
    //line 2
    tle.catalog_nr = stoi(lines[1].substr(2, 5));
    tle.set_nr = stoi(lines[1].substr(64, 4));
    tle.epoch_year = stoi(lines[1].substr(18, 2));
    tle.epoch_day = stod(lines[1].substr(20, 12));
    tle.fst_derivative = stod(lines[1].substr(33, 10));
    tle.snd_derivative = stod(lines[1].substr(44, 8));
    tle.drag_term = stod(lines[1].substr(53, 8));
    //line 3
    tle.inclination = stod(lines[2].substr(8, 8));
    tle.right_ascension = stod(lines[2].substr(17, 8));
    tle.eccentricity = stod(lines[2].substr(26, 7));
    tle.arg_of_perigee = stod(lines[2].substr(34, 8));
    tle.mean_anomaly = stod(lines[2].substr(43, 8));
    return tle;
}

void FileInput::setDebrisValues(Debris::Debris &d, const struct FileInput::TLEContent &tle){

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
        if(ss.peek() == ','){
            ss.ignore();
        }
    }
}

void FileInput::readDebrisTXT() {
    std::ifstream input_file(input_file_name);
    std::string line;
    struct TxtLineContent line_content;
    struct TLEContent tle_content;
    Debris::Debris d;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            if (line.empty() or line[0] == '#') {
                continue;
            }
            // reached tle block?
            if (line != "TLE") {
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
            }else{
                std::array<std::string,3> lines;
                while (std::getline(input_file, lines[0])
                    && std::getline(input_file, lines[1])
                    && std::getline(input_file, lines[2])) {
                    if (lines[0].empty() || lines[1].empty() || lines[2].empty()) {
                        continue;
                    }
                    tle_content = parseTLE(lines);
                    setDebrisValues(d, tle_content);
                    // for now don't add anything
//                    debris->addDebris(d);
                }
            }
        }
    }
}

Debris::DebrisContainer &FileInput::getDebris()  {
    return *debris;
}

void FileInput::setDebris(Debris::DebrisContainer &debris) {
    FileInput::debris = &debris;
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

double FileInput::getWriteDeltaT()  {
    return write_delta_t;
}

void FileInput::setWriteDeltaT(double writeDeltaT) {
    write_delta_t = writeDeltaT;
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

