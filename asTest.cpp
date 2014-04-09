
//
// TESTING AREA
// FMMT666(ASkr) 2014; www askrprojects.net
//

#include "asSerialCollection.h"

#include "asTest.h"



asSerialCollection *asSerials = new asSerialCollection;




int Mount( void )
{
	return asSerials->Mount();
}


bool UnMount( int handle )
{
	return asSerials->UnMount( handle );
}


bool Check( int handle, int port )
{
	return asSerials->Check( handle, port );
}


bool Open( int handle, int port )
{
	return asSerials->Open( handle, port );
}


bool Close( int handle )
{
	return asSerials->Close( handle );
}


bool SendByte( int handle, int byte )
{
	return asSerials->SendByte( handle, byte );
}


int BufferCount( int handle )
{
	return asSerials->BufferCount( handle );
}

