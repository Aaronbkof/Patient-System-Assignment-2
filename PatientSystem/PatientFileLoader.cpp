#include "PatientFileLoader.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include "Patient.h"
#include "Vitals.h"

using namespace std;

std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)
{
    vector<Patient*> patients{};
    std::ifstream inFile(file);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue; // skip empty lines

            // parse: patientId|lastName,firstName|birthDate|disease|vitals
            vector<string> parts;
            stringstream ss(line);
            string part;

            // split by '|'
            while (getline(ss, part, '|')) {
                parts.push_back(part);
            }

            if (parts.size() >= 4) { // need at least id, name, birth, disease
                // not used (for now) but for later parts will be relevant
                string patientId = parts[0];

                string fullName = parts[1];
                string birthDate = parts[2];
                string disease = parts[3];

                // take arguments of order last and first
                string lastName, firstName;
                size_t commaPos = fullName.find(',');
                if (commaPos != string::npos) {
                    lastName = fullName.substr(0, commaPos);
                    firstName = fullName.substr(commaPos + 1);
                }
                else {
                    lastName = fullName; // fallback if no comma
                    firstName = "";
                }

                // parse birth date - convert string using tm struct
                std::tm birthday = {};
                // using the example output gives dd/ format
                // You may need to adjust this parsing based on your date format
                stringstream dateStream(birthDate);
                string day, month, year;
                if (getline(dateStream, day, '-') &&
                    getline(dateStream, month, '-') &&
                    getline(dateStream, year)) {

                    // convert day using stringstream
                    stringstream dayStream(day);
                    dayStream >> birthday.tm_mday;

                    // convert month using stringstream
                    stringstream monthStream(month);
                    int monthValue;
                    monthStream >> monthValue;
                    birthday.tm_mon = monthValue - 1; // tm_mon is 0-based

                    // Convert year using stringstream
                    stringstream yearStream(year);
                    int yearValue;
                    yearStream >> yearValue;
                    birthday.tm_year = yearValue - 1900; // tm_year is years since 1900
                }

                // create Patient with correct constructor
                Patient* patient = new Patient(firstName, lastName, birthday);

                // add diagnosis separately
                patient->addDiagnosis(disease);

                // parse vitals if they exist (parts[4])
                if (parts.size() > 4 && !parts[4].empty()) {
                    parseVitalsForPatient(patient, parts[4]);
                }

                patients.push_back(patient);
            }
        }
        inFile.close();
    }
    else {
        cout << "Warning: Could not open file " << file << endl;
    }
    return patients;
}

void PatientFileLoader::parseVitalsForPatient(Patient* patient, const string& vitalsString) {
    // vitals format as per example output
    stringstream ss(vitalsString);
    string vitalRecord;

    while (getline(ss, vitalRecord, ';')) {
        if (vitalRecord.empty()) continue;

        // parse single vitals with figures below
        vector<string> vitalParts;
        stringstream vitalSS(vitalRecord);
        string value;

        while (getline(vitalSS, value, ',')) {
            vitalParts.push_back(value);
        }

        if (vitalParts.size() >= 4) {
            // convert temperature using stringstream
            stringstream tempStream(vitalParts[0]);
            float bodyTemp;
            tempStream >> bodyTemp;

            // convert blood pressure using stringstream
            stringstream bpStream(vitalParts[1]);
            int bloodPressure;
            bpStream >> bloodPressure;

            // convert heart rate using stringstream
            stringstream hrStream(vitalParts[2]);
            int heartRate;
            hrStream >> heartRate;

            // convert respiratory rate using stringstream
            stringstream rrStream(vitalParts[3]);
            int respiratoryRate;
            rrStream >> respiratoryRate;

            Vitals* vital = new Vitals(bodyTemp, bloodPressure, heartRate, respiratoryRate);
            patient->addVitals(vital);
        }
    }
}