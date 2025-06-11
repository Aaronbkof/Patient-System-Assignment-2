#pragma once

#include "Patient.h"


class HospitalAlertSystemFacade
{
public:
	HospitalAlertSystemFacade();
	virtual ~HospitalAlertSystemFacade();

	void sendAlertForPatient(Patient* p);

};

