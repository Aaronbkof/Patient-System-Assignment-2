#pragma once

#include "AbstractPatientDatabaseLoader.h"
#include <vector>
#include <memory>

// forward dec
class Patient;

/**
 * this class implements the Composite design pattern.
 * this class can load patients from dual sources (DB and .txt)
 */
class DualPatientLoader : public AbstractPatientDatabaseLoader
{
private:
    // a list of all the different loaders this composite manages
    // each loader knows how to load from a specific source (database, file, etc.)
    std::vector<std::unique_ptr<AbstractPatientDatabaseLoader>> patientLoaders;

public:
    DualPatientLoader();
    virtual ~DualPatientLoader();

    // add a new loader to the existing loaders
    // essentially adding a database loader, then add a file loader
    void addPatientLoader(std::unique_ptr<AbstractPatientDatabaseLoader> newLoader);

    // these methods are required by AbstractPatientDatabaseLoader
    // they will call the same method on ALL loaders (both)
    void initialiseConnection() override;
    void loadPatients(std::vector<Patient*>& allPatients) override;
    void closeConnection() override;
};