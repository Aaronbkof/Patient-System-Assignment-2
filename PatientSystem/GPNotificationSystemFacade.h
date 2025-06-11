#pragma once

#include "Patient.h"


class GPNotificationSystemFacade {
public:
	GPNotificationSystemFacade();
	virtual ~GPNotificationSystemFacade();

	void sendGPNotificationForPatient(Patient* p);
};

