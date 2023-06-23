#include "headers/headers.h"
void strclean (unsigned char * src) {
    // Run two pointers in parallel.

    

    // Process every source character.
    
      unsigned char *dst = src;
    

    while (*src) {
        // Only copy (and update destination pointer) if suitable.
        // Update source pointer always.

        if (isalpha(*src)){ *dst++ = *src;}else if(isdigit(*src)){*dst++ = *src;}
        src++;
        
    }

    // Finalise destination string.

    *dst = '\0';
//
}
      void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i],HEX);
  }
      }

std::string byteToString(const unsigned char* byteArray, size_t len) {
    char* str = new char[len + 1];
    memcpy(str, byteArray, len);
    str[len] = '\0';
    std::string result(str);
    delete[] str;
    return result;
}
void array_to_string(byte array[], unsigned int len, char buffer[])
{
   for (unsigned int i = 0; i < len; i++)
   {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
   }
   buffer[len*2] = '\0';

}
