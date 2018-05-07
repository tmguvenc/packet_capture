/*******************************************************************
* DOSYA_ADI =
*		Makrolar.h
*
* REVIZYON GEÇMÝÞÝ:
*  		@author: tmguvenc	 mayis 2018
*
*/

#ifndef PACKET_CAPTURE_MACROS_H
#define PACKET_CAPTURE_MACROS_H

#if defined (_WIN32) && defined (_MSC_VER)
#	ifdef PACKET_CAPTURE_EXPORTS
#		define PACKET_CAPTURE_EXPORT __declspec(dllexport)
#	else
#		define PACKET_CAPTURE_EXPORT __declspec(dllimport)
#	endif
#else
#	define PACKET_CAPTURE_EXPORT 
#endif


#endif // !PACKET_CAPTURE_MACROS_H