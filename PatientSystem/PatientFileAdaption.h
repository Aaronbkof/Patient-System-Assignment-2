#pragma once
#include "AbstractPatientDatabaseLoader.h"
#include "PatientFileLoader.h"
#include <string>
#include <vector>

// forward declaration
class Patient;

class PatientFileAdapter : public AbstractPatientDatabaseLoader
{
private:
    PatientFileLoader fileLoader;
    std::string fileName;

public:
    PatientFileAdapter(const std::string& filename) : fileName(filename) {}

    void initialiseConnection() override {
        // no connection initialization needed for file loading
    }

    void loadPatients(std::vector<Patient*>& patients) override {
        std::vector<Patient*> loadedPatients = fileLoader.loadPatientFile(fileName);

        // add loaded patients to provided vector
        for (Patient* patient : loadedPatients) {
            patients.push_back(patient);
        }
    }

    void closeConnection() override {
        // no connection cleanup needed for file loading
    }
};