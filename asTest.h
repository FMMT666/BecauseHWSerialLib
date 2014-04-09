
#ifdef __cplusplus

extern "C"
{
	int Mount( void );										// creates a serial object with the first, free number
	bool UnMount( int handle );						// unmounts and destroys the serial object referenced by "handle"
	bool Check( int handle, int port );		// checks if a serial port (COM port) exists
	bool Open( int handle, int port );		// opens the serial COM port "port" on the object referenced by "handle"
	bool Close( int handle );							// closes the serial port referenced by handle (if open)
	bool SendByte( int handle, int byte );// sends a byte over the serial port referenced by "handle"
	int BufferCount( int handle );				// count the number of bytes in the receive buffer
}

#else

#include <stdbool.h>

extern int Mount( void );										// creates a serial object with the first, free number
extern bool UnMount( int handle );						// unmounts and destroys the serial object referenced by "handle"
extern bool Check( int handle, int port );		// checks if a serial port (COM port) exists
extern bool Open( int handle, int port );		// opens the serial COM port "port" on the object referenced by "handle"
extern bool Close( int handle );							// closes the serial port referenced by handle (if open)
extern bool SendByte( int handle, int byte );// sends a byte over the serial port referenced by "handle"
extern int BufferCount( int handle );				// count the number of bytes in the receive buffer

#endif // __cplusplus
