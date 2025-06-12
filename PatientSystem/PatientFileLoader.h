#pragma once
#include <string>
#include <vector>
// forward declare the patient class
class Patient;

class PatientFileLoader
{
public:
    // loads a list of patients from a file and returns a vector of those patients
    std::vector<Patient*> loadPatientFile(const std::string& file);

private:
    // helper method to parse vitals string and add to patient
    void parseVitalsForPatient(Patient* patient, const std::string& vitalsString);
};