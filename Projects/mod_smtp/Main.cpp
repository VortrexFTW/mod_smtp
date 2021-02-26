#include "pch.h"

#include <stdio.h>
#include <stdlib.h>
#include <GalacticInterfaces.h>
#include <GalacticStrongPtr.h>

#include <smtp.h>

// The modules internal name (Also used for the namespace name)
MODULE_MAIN("smtp");

void ModuleRegister()
{
	SDK::RegisterFunction("send", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		bool bUseTLS = false;

        const char *szServer = State.CheckString(0);
		const char *szPort = State.CheckString(1);
		State.CheckBoolean(2, bUseTLS);
		const char *szUser = State.CheckString(3);
		const char *szPassword = State.CheckString(4);
		const char *szTo = State.CheckString(5);
		const char *szToName = State.CheckString(6);
		const char *szSubject = State.CheckString(7);
		const char *szBody = State.CheckString(8);
		const char *szFrom = State.CheckString(9);
		const char *szFromName = State.CheckString(9);

		smtp_connection_security pConnectionSecurity = SMTP_SECURITY_NONE;
		if(bUseTLS) {
			pConnectionSecurity = SMTP_SECURITY_TLS;
		}

		struct smtp *smtp;
		int rc;
		rc = smtp_open(szServer,
						szPort,
						pConnectionSecurity,
						SMTP_DEBUG,
						NULL,
						&smtp);
		rc = smtp_auth(smtp,
						SMTP_AUTH_PLAIN,
						szUser,
						szPassword);
		rc = smtp_address_add(smtp,
								SMTP_ADDRESS_FROM,
								szFrom,
								szFromName);
		rc = smtp_address_add(smtp,
								SMTP_ADDRESS_TO,
								szTo,
								szToName);
		rc = smtp_header_add(smtp,
							"Subject",
							szSubject);
		rc = smtp_mail(smtp,
						szBody);
		rc = smtp_close(smtp);
		//if(rc != SMTP_STATUS_OK){
		//	return pState->SetError("SMTP failed: %s", (const char*)smtp_status_code_errstr(rc));
		//}

		//SDK::NullValue Value();
		//State.Return(Value);
		return true;

		SDK_ENDTRY;
	});
}

void ModuleUnregister()
{
}
