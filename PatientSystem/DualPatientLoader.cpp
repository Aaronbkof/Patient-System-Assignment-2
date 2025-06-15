#include "DualPatientLoader.h"
#include "Patient.h"
#include <iostream>

// initialising a blank instance of the dualpatient loader object 
// also the loader vector is initialised to be blank
DualPatientLoader::DualPatientLoader()
{
}

// for cleaning up/deletion of the loader instance(s)
DualPatientLoader::~DualPatientLoader()
{
}

void DualPatientLoader::addPatientLoader(std::unique_ptr<AbstractPatientDatabaseLoader> newLoader)
{
    // add a new loader instance to the process
    // transfering ownership of the loader to vector
    patientLoaders.push_back(std::move(newLoader));
    
    // test notes to be commented
    std::cout << "Added a new patient loader. Total loaders: " << patientLoaders.size() << std::endl;
}

void DualPatientLoader::initialiseConnection()
{
    // test notes to be commented
    std::cout << "Initializing connections for all " << patientLoaders.size() << " loaders" << std::endl;

    // go through each loader in the collection and initialise it
    int x = 0;
    while (x < patientLoaders.size()) {
        patientLoaders[x]->initialiseConnection();
        x++;
    }

    // test notes to be commented
    std::cout << "All connections initialized!" << std::endl;
}

void DualPatientLoader::loadPatients(std::vector<Patient*>& allPatients)
{
    // test notes to be commented
    std::cout << "Loading patients from all sources..." << std::endl;

    // this is for keeping track of how many patients there are before loading
    int patientsBeforeLoading = allPatients.size();

    // go through each loader request loading of patients
    int x = 0;
    while (x < patientLoaders.size()) {
        int patientsBeforeThisLoader = allPatients.size();

        // add patients to the initialised allPatients vector
        patientLoaders[x]->loadPatients(allPatients);

        int patientsFromThisLoader = allPatients.size() - patientsBeforeThisLoader;
        
        // test notes to be commented
        std::cout << " successfully loaded " << patientsFromThisLoader << " patients from this source" << std::endl;
        x++;
    }

    int totalNewPatients = allPatients.size() - patientsBeforeLoading;
}

void DualPatientLoader::closeConnection()
{
    // Go through each loader and close its connection
    int x = 0;
    while (x < patientLoaders.size()) {
        patientLoaders[x]->closeConnection();
        x++;
    }
}