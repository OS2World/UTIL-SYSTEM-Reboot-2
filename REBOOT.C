/* Reboot/2 version 1.0 Nick Bethmann, 22 Jun 92 */

#define  INCL_DOSFILEMGR
#define  INCL_DOSDEVICES

#include <OS2.h>
#include <stdlib.h>
#include <string.h>

int _cdecl main( void )
{

   HFILE    handle;
   short    action;
   unsigned err;

   /*
    *  Open the device driver.
    */
   err = DosOpen( "\\DEV\\DOS$",
                  &handle,
                  &action,
                  0L,
                  FILE_NORMAL,
                  FILE_OPEN,
                  OPEN_SHARE_DENYNONE, 0L );
   if ( err )
   {
      char buffer[80];
      char val[6];
         /* yes, printf would be easier, but MUCH bigger */
      strcpy( buffer, "\nDOS$ device open failed. err " );
      strcat( buffer, itoa(err, val, 10) );
      strcat( buffer, "\n" );
      DosWrite( 1, buffer, strlen(buffer), &err );
      return( 2 );
   }

   /*
    *  Shutdown the filesystem.
    */
   DosShutdown( 0 );

   /*
    *  Reboot the system, using Magic cookies found in boot.com 
    */
   DosDevIOCtl( NULL, NULL, 0xAB, 0xD5, handle );

}
