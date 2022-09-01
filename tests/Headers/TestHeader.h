#include "TestHeader.generated.h"


SKCLASS  (  Reliable,    DisplayName= "RenderContext",   Foo  =bar,Thing1=    "Hello World",ok=s)
class Context : public SKObject
{
	SK_GENERATED_BODY();

	SKPROPERTY()
	float testProperty = 0.f;
};