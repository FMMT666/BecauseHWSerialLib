//
// BecauseHW!SerialLib,
// derived from asSerial, a CSerial wrapper object
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


#include "asSerialCollect.h"
#include "asSerialCollectCWrap.h"


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


bool Config( int handle, long baud, int bits, int parity, int stop)
{
	return asSerials->Config( handle, baud, bits, parity, stop );
}


int ReadByte( int handle )
{
	return asSerials->ReadByte( handle );
}


bool BufferFlush( int handle )
{
	return asSerials->BufferFlush( handle );
}


bool SendArray( int handle, int *pData, int length)
{
	return asSerials->SendArray( handle, pData, length );
}


int ReadArrayN( int handle, int length, int *pData)
{
	return asSerials->ReadArrayN( handle, length, pData );
}

