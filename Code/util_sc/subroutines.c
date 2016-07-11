/******************************************************************************/
/******************************************************************************/
/****************             Subroutines                **********************/
/******************************************************************************/
/******************************************************************************/



/************************************************************************************************************************************************
 * void getRandomBytes(BYTE* buffer, unsigned int size)
 *
 * Generate 's = 8*ceil(size/8)' random bytes and put them in
 * buffer[0],...,buffer[s-1].
 ************************************************************************************************************************************************/

void getRandomBytes(BYTE* buffer, unsigned int size) {

  unsigned int i;
  BYTE temp_buffer[8];

  for (i=8; i<=size; i += 8) {
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(8, temp_buffer, buffer + i - 8);
  }

  switch (8 - i + size) {
  case 1:
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(1, temp_buffer, buffer + i - 8);
    break;
  case 2:
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(2, temp_buffer, buffer + i - 8);
    break;
  case 3:
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(3, temp_buffer, buffer + i - 8);
    break;
  case 4:
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(4, temp_buffer, buffer + i - 8);
    break;
  case 5:
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(5, temp_buffer, buffer + i - 8);
    break;
  case 6:
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(6, temp_buffer, buffer + i - 8);
    break;
  case 7:
    multosGetRandomNumber(temp_buffer);
    multosBlockCopyFixedLength(7, temp_buffer, buffer + i - 8);
    break;
  default:
    break;
  }

}
