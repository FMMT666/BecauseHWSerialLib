//
// asSerial, a CSerial wrapper object
// FMMT666(ASkr), 2010, 2012, 2013, 2014; www askrprojects.net
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include <windows.h>

#include "asSerialCollection.h"

using namespace std;




//
// TODO:
//   - asSerialCollection as singleton
//   - SendVector() method
//   - ReadVector() method
//




//************************************************************************************************
//** asSerialCollection **************************************************************************
//**                    **************************************************************************
//**                    **************************************************************************
//************************************************************************************************

//************************************************************************************************
//*** asSerialCollection::asSerialCollection
//***
//***
//************************************************************************************************
asSerialCollection::asSerialCollection()
{
}



//************************************************************************************************
//*** asSerialCollection::~asSerialCollection
//***
//***
//************************************************************************************************
asSerialCollection::~asSerialCollection()
{
	UnMountAll();
}


//************************************************************************************************
//*** asSerialCollection::GetFreeHandle
//***
//*** Determines and returns a free handle number.
//***
//*** RETURNS:
//***    >0 -> valid handle
//***     0 -> no free handle was found
//************************************************************************************************
int asSerialCollection::GetFreeHandle()
{
	for( int i=1; i<=MAX_SERIAL_OBJECTS; ++i )
	{
		if( CheckHandleFree( i ) )
			return i;
	}

	return 0;
}



//************************************************************************************************
//*** asSerialCollection::CheckHandleFree
//***
//*** Checks if a handle is free for usage.
//***
//*** RETURNS:
//***    true -> handle is free (not used)
//***   false -> handle is already in use
//************************************************************************************************
bool asSerialCollection::CheckHandleFree( int handle )
{
	// discard invalid handle numbers
	if( ( handle < 1 ) || ( handle > MAX_SERIAL_OBJECTS ) )
		return false;

	// check if handle is in use
	if( asSerialMap.find( handle ) == asSerialMap.end() )
		return true;	// handle is free
	else
		return false; // handle is in use

}



//************************************************************************************************
//*** asSerialCollection::Mount
//***
//*** Creates a serial object and returns its handle.
//***
//*** RETURNS:
//***    >0 -> valid handle, serial object was created
//***     0 -> no free handle was found, something went wrong
//************************************************************************************************
int asSerialCollection::Mount( void )
{
	int handle;
	if( (handle = GetFreeHandle() ) > 0 )
	{
		try
		{
			asSerialMap.emplace( handle, new asSerial );
		}
		catch(...)
		{
			handle = 0;
		}
	}// END if handle > 0

  return handle;
}



//************************************************************************************************
//*** asSerialCollection::Mount
//***
//*** Creates a serial object, trying using "handle" as the handle number.
//*** If "handle" is already in use, a different, free handle will be determined.
//***
//*** RETURNS:
//***    >0 -> valid handle number, serial object was created
//***     0 -> no free handle was found, something went wrong
//************************************************************************************************
int asSerialCollection::Mount( int handle )
{
	// check if this handle is free, otherwise get another, free number
	if( !CheckHandleFree( handle ) )
		handle = GetFreeHandle();


	if( handle > 0 )
	{
		try
		{
			asSerialMap.emplace( handle, new asSerial );
		}
		catch(...)
		{
			handle = 0;
		}
	}// END if handle > 0

  return handle;
}



//************************************************************************************************
//*** asSerialCollection::UnMount
//***
//*** Destroy the serial object references by "handle".
//***
//*** RETURNS:
//***    >0 -> valid handle number, serial object was created
//***     0 -> no free handle was found, something went wrong
//************************************************************************************************
bool asSerialCollection::UnMount( int handle )
{
	bool ret = false;

	auto serialObj = asSerialMap.find( handle );
	if( serialObj != asSerialMap.end() )
	{
		delete serialObj->second;
		asSerialMap.erase( handle );
		ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::UnMountAll
//***
//*** Destroys all serial objects.
//***
//*** RETURNS:
//***   true -> ok
//************************************************************************************************
void asSerialCollection::UnMountAll( )
{
	for( auto serObj=asSerialMap.begin(); serObj != asSerialMap.end(); ++serObj )
		delete serObj->second;

	asSerialMap.clear();

}



//************************************************************************************************
//*** asSerialCollection::Check
//***
//*** Checks if the serial port "port" exists and is free for usage.
//***
//*** RETURNS:
//***    true -> yep, this COM port can be used
//***   false -> unfortunately, this COM port does either not exist or is not free
//************************************************************************************************
bool asSerialCollection::Check( int handle, int port )
{
	bool ret = false;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->Check( port ) )
			ret = true;
	}// END serObj != NULL

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::Config
//***
//*** Configures the serial object, referenced by "handle".
//***
//*** RETURNS:
//***    true -> all ok
//***   false -> an error occurred
//************************************************************************************************
bool asSerialCollection::Config( int handle, long baud, int bits, int parity, int stop)
{
	bool ret = false;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->ConfigComm( baud, bits, parity, stop ) == ERROR_SUCCESS )
			ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::Open
//***
//*** Opens the serial port "port" on handle "handle".
//***
//*** RETURNS:
//***    true -> all ok
//***   false -> an error occurred
//************************************************************************************************
bool asSerialCollection::Open( int handle, int port )
{
	bool ret = false;

	auto serObj = GetSerialObj( handle );
	if( ( serObj != NULL ) && ( serObj->Check( port ) ) )
	{
		if( serObj->Open( port ) == ERROR_SUCCESS )
			ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::Close
//***
//*** Closes the serial port on handle "handle".
//***
//*** RETURNS:
//***    true -> all ok
//***   false -> an error occurred
//************************************************************************************************
bool asSerialCollection::Close( int handle )
{
	bool ret = false;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->Close() == ERROR_SUCCESS )
			ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::SendByte
//***
//*** Sends a byte over the serial port referenced by "handle".
//***
//*** RETURNS:
//***    true -> all ok
//***   false -> an error occurred
//************************************************************************************************
bool asSerialCollection::SendByte( int handle, int byte )
{
	bool ret = false;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->SendRawByte( byte ) == ERROR_SUCCESS )
			ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::SendArray
//***
//*** Sends an array over the serial port referenced by "handle".
//***
//*** TODO: This came from an external C interface and needs a complete rework.
//***
//*** RETURNS:
//***    true -> all ok
//***   false -> an error occurred
//************************************************************************************************
bool asSerialCollection::SendArray( int handle, int *pData, int length )
{
	int i;

	bool ret = false;

	//********************
	// TODO: NEEDS REWORK
	//********************

	unsigned char *tmp = new unsigned char[(length)+8];
	unsigned char *org = tmp;
	int *pj = pData;

	if( tmp != NULL )
	{
		for( i = 0; i < length; i++ )
			*(tmp++) = *(pj++) & 0xff;

		tmp = org;

		auto serObj = GetSerialObj( handle );
		if( serObj != NULL )
		{
			if( serObj->SendRaw( (int*)org, length ) == ERROR_SUCCESS )
				ret = true;
		}

		delete[] tmp;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::BufferCount
//***
//*** Counts the number of received bytes in the receive buffer.
//***
//*** RETURNS:
//***    < 0 -> ERROR (buffer overflow; out of memory)
//***    >=0 -> number of bytes available
//************************************************************************************************
int asSerialCollection::BufferCount( int handle )
{
	int ret = -1;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
		ret = serObj->BufferCount( );

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::ReadByte
//***
//*** Reads an already received byte from the receive buffer.
//*** Although the underlaying serial interface objects supports "BLOCKING" and
//*** "NONBLOCKING" reads, this one only uses "NONBLOCKING".
//***
//*** RETURNS:
//***    < 0 -> buffer is empty
//***    >=0 -> the byte itself
//************************************************************************************************
int asSerialCollection::ReadByte( int handle )
{
	int ret = -1;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
		ret = serObj->RecvRawByte( NONBLOCKING );

	return ret;

}



//************************************************************************************************
//*** asSerialCollection::BufferFlush
//***
//*** Empties the complete receive buffer.
//***
//*** RETURNS:
//***    < 0 -> buffer is empty
//***    >=0 -> the byte itself
//************************************************************************************************
bool asSerialCollection::BufferFlush( int handle )
{
	bool ret = false;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		serObj->BufferFlush();
		ret = true;
	}

	return ret;

}



//************************************************************************************************
//*** asSerialCollection::ReadArrayN
//***
//*** Reads a number of bytes from the receive buffer.
//***
//*** TODO: This came from an external C interface and needs a complete rework.
//***
//*** RETURNS:
//***    < 0 -> an error occurred
//***   >= 0 -> number of bytes written back
//************************************************************************************************
int asSerialCollection::ReadArrayN( int handle, int length, int *pData )
{
	int ret = -1;

	//********************
	// TODO: NEEDS REWORK
	//********************

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		ret = 0;
		for( int i = 0; i < length; ++i )
		{
			if( (*pData++ = serObj->RecvRawByte(0) ) >= 0 )
				ret++;
		}
	}

	return ret;

}



//************************************************************************************************
//*** asSerialCollection::ReadPacket
//***
//*** Reads a data packet from the receive buffer.
//***
//*** TODO: This came from an external C interface and needs a complete rework.
//***
//*** RETURNS:
//***    < 0 -> an error occurred
//***   >= 0 -> number of bytes written back
//************************************************************************************************
int asSerialCollection::ReadPacket( int handle, int length, int *pData )
{
	int ret = -1;

	//********************
	// TODO: NEEDS REWORK
	//********************

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		// holy mackerel...
		//   a) memset
		//   b) 0xff ???
		memset( (int *)pData, 0xff, length * sizeof(int) );

		// Results are written to <bytes>
		ret = serObj->RecvRawPacketByte( pData, length );
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::CountPacket
//***
//*** Returns the number of received and complete data packets in the buffer.
//***
//*** RETURNS:
//***    < 0 -> an error occurred
//***   >= 0 -> number of packets in the receive buffer
//************************************************************************************************
int asSerialCollection::CountPacket( int handle )
{
	int ret = -1;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		ret = serObj->BufferCountPackets();
	}

	return ret;

}



//************************************************************************************************
//*** asSerialCollection::SendPacket
//***
//*** Sends a data packet over the serial port referenced by "handle".
//***
//*** RETURNS:
//***   true -> packet was sent
//***  false -> an error occurred
//************************************************************************************************
bool asSerialCollection::SendPacket( int handle, int *pData, int length )
{
	bool ret = false;

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->SendPacket( pData, length ) == ERROR_SUCCESS )
			ret = true;
	}

	return ret;

}



//************************************************************************************************
//*** asSerialCollection::SetPacketStart
//***
//*** Sets the packet start sequence byte.
//***
//*** TODO: This came from an external C interface and needs a complete rework.
//***
//*** RETURNS:
//***   true -> OK
//***  false -> ERROR
//************************************************************************************************
bool asSerialCollection::SetPacketStart( int handle, int *pData )
{
	bool ret = false;

	//********************
	// TODO: NEEDS REWORK
	//********************

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->ConfigPacketStart( pData ) == ERROR_SUCCESS	)
			ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::SetPacketEnd
//***
//*** Sets the packet end delimiter byte.
//***
//*** TODO: This came from an external C interface and needs a complete rework.
//***
//*** RETURNS:
//***   true -> OK
//***  false -> ERROR
//************************************************************************************************
bool asSerialCollection::SetPacketEnd( int handle, int *pData )
{
	bool ret = false;

	//********************
	// TODO: NEEDS REWORK
	//********************

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->ConfigPacketEnd( pData ) == ERROR_SUCCESS	)
			ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** asSerialCollection::SetPacketChar
//***
//*** Sets the special packet character.
//***
//*** TODO: This came from an external C interface and needs a complete rework.
//***
//*** RETURNS:
//***   true -> OK
//***  false -> ERROR
//************************************************************************************************
bool asSerialCollection::SetPacketChar( int handle, int specialChar )
{
	bool ret = false;

	//********************
	// TODO: NEEDS REWORK
	//********************

	auto serObj = GetSerialObj( handle );
	if( serObj != NULL )
	{
		if( serObj->ConfigPacketChar( specialChar ) == ERROR_SUCCESS	)
			ret = true;
	}

	return ret;
}



//************************************************************************************************
//*** PRIVATE asSerialCollection::GetSerialObj
//***
//*** Returns a pointer to the serial object, references by "handle".
//***
//*** RETURNS:
//***   NULL      -> no such object exists
//***   asSerial* -> pointer to the object referenced by "handle"
//************************************************************************************************
asSerial* asSerialCollection::GetSerialObj( int handle )
{

	auto serialObj = asSerialMap.find( handle );
	if( serialObj != asSerialMap.end() )
		return serialObj->second;
	else
		return NULL;
}


