//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "Unit2.h"
//---------------------------------------------------------------------------
class ThreadDetectionDossard : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall ThreadDetectionDossard(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
