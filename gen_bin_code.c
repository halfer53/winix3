#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int i = 0;
  int length = 0;
  int wordslength = 0;
  int temp = 0;
  int recordtype = 0;
  char **lines = NULL;
  int success = 0;
  int counter = 0;

  FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("shell.srec", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    if ((read = getline(&line, &len, fp)) != -1) {
      if (length = exec_phase1_readLength(line,5)) {
        //printf(" length %d\n",length );
        if ((read = getline(&line, &len, fp)) != -1) {
          if (wordslength = exec_phase1_readLength(line,6)) {
            success = 1;
            length -= 2;
            //printf("wordslength %d\n",wordslength );
          }
        }
      }
    }
    if (success == 1) {
      if (lines = (char **)malloc(length * sizeof(char *))) {
          for ( i = 0; i < length; i++) {
            if (lines[i] = (char *)malloc(128 * sizeof(char))) {
              success = 2;
            }else{
              success = 0;
            }
          }
      }else{
        success = 0;
      }
    }
    if (success == 2) {
      while ((read = getline(&line, &len, fp)) != -1) {
          if (len < 128) {
            strcpy(lines[counter] ,line);
          }else{
            printf("line too big %d\n",(int)len );
          }

          counter++;
      }
    }



    fclose(fp);
    if (line)
        free(line);
  //first recordtype 5,and 6 is consumed

  printf("size_t shell_code[] = {\n" );
  i = exec_phase2(lines,length,wordslength);
  printf("int shell_code_length =  %d;\n", wordslength);
  printf("size_t init_code[2] = {0x01010000,0x50f00000};\n" );
  printf("size_t init_pc = 0x0;\n" );

  return 0;

}
void assert(int expression, const char *message) {
	if(!expression) {
		printf("\r\nAssertion Failed ");
    printf("%s\r\n",message );
	}
}
int hex2int(char *a, int len)
{
    int i;
    int val = 0;

    for(i=0;i<len;i++){
			if(a[i] <= 57){
			 val += (a[i]-48)*(1<<(4*(len-1-i)));
      }

			else{
			 val += (a[i]-55)*(1<<(4*(len-1-i)));
      }

		}

    return val;
}

int Substring(char* buffer,char* original,int start_index,int length){
	int i = 0;
	int count = 0;
	for(i = start_index; i<length+start_index; i++)
  {
        buffer[count] = original[i];
				count++;
  }
	buffer[count] = '\0';
	return count;
}

typedef unsigned char byte;

int exec_phase1_readLength(char *line, int requiredType){
  int i=0;

  int index = 0;
	int checksum = 0;
  byte byteCheckSum = 0;
	int recordType = 0;
	int byteCount = 0;
	char buffer[128];
	char tempBufferCount = 0;

  int wordsCount = 0;
  int length = 0;
  int readChecksum = 0;
  int data = 0;

        index = 0;
        checksum = 0;
        //printf("%s\n",line );
				//printf("%s\r\n",line);
        //printf("loop %d\n",linecount );
				//Start code, always 'S'
				assert(line[index++] == 'S',"Expecting S");

				recordType = line[index++] - '0';
        if (recordType == requiredType) {

        }else{
          printf("recordType %d\n",recordType );
          printf("format is incorrect\n" );
          return 0;
        }
        tempBufferCount = Substring(buffer,line,index,2);
				//printf("record value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				byteCount = hex2int(buffer,tempBufferCount);
        index += 2;
        checksum += byteCount;

				assert(byteCount<255,"byteCount bigger than 255");

						tempBufferCount = Substring(buffer,line,index,(byteCount-1)*2 );
						//printf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						data = hex2int(buffer,tempBufferCount);
            //printf("data %d\n", data);
            index += (byteCount-1)*2;
            checksum += data;

				//Checksum, two hex digits. Inverted LSB of the sum of values, including byte count, address and all data.
				//readChecksum = (byte)Convert.ToInt32(line.Substring(index, 2), 16);
        //printf("checksum %d\n",checksum );
				tempBufferCount = Substring(buffer,line,index,2);
				//printf("read checksum value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				readChecksum = hex2int(buffer,tempBufferCount);
         //printf("readChecksum %d\n",readChecksum );
         //printf("checksum %d\n",checksum );
        //printf("checksum %d\r\n",checksum );
        if (checksum > 255) {
          byteCheckSum = (byte)(checksum & 0xFF);
          //printf("checksum %d\r\n",byteCheckSum );
          byteCheckSum = ~byteCheckSum;
        }else{
          byteCheckSum = ~byteCheckSum;
          byteCheckSum = checksum;
        }
        //printf("checksum %d\r\n",byteCheckSum );
				if (readChecksum != byteCheckSum){
					printf("failed checksum\r\n" );
					return 0;
				}

        return data;
}
//*(unsigned long*)FREE_MEM_BEGIN = (unsigned int)memVal;
//FREE_MEM_BEGIN++;
int exec_phase2(char **lines,int length,int wordsLength){
  // char* lines[] = {"S32D000000008107300090073004120000003828000DB08FFFFB600000096000000E1220000140000003810730038F",
	// 			"S32D0000000A91073002812000139107300350F000001901FFFF199A000219930001B09FFFFE50F0000000000076C3",
	// 			"S32D000000140000007900000038000000380000003F00000000000000390000005B0000003F0000003F0000000084",
	// 			"S30D0000001E0000000000000000D4",
	// 			"S70500000000FA"};
  char memValues[wordsLength];
  int wordsCount = 0;
	int wordsLoaded = 0;
	int index = 0;
	int checksum = 0;
  byte byteCheckSum = 0;
	int recordType = 0;
	int addressLength = 0;
	int byteCount = 0;
	char buffer[128];
	char tempBufferCount = 0;
	int address = 0;
	byte data[255];
	int readChecksum = 0;
	int datalength = 0;
	unsigned long memVal = 0;
  int i = 0;
  int j = 0;
  int linecount = 0;

	while(1){
		//Read line from terminal
		// for(i = 0; i < BUF_LEN - 1; i++) {
		// 	buf[i] = getc(); 	//read
    //
		// 	if(buf[i] == '\r') { //test for end
		// 		break;
		// 	}
		// 	putc(buf[i]); 		//echo
		// }

		char* line = lines[linecount];

    linecount++;
    index = 0;
    checksum = 0;

				//printf("%s\r\n",line);
        //printf("loop %d\n",linecount );
				//Start code, always 'S'
				assert(line[index++] == 'S',"Expecting S");

				//Record type, 1 digit, 0-9, defining the data field
				//0: Vendor-specific data
				//1: 16-bit data sequence
				//2: 24 bit data sequence
				//3: 32-bit data sequence
				//5: Count of data sequences in the file. Not required.
				//7: Starting address for the program, 32 bit address
				//8: Starting address for the program, 24 bit address
				//9: Starting address for the program, 16 bit address
				recordType = line[index++] - '0';

				switch (recordType)
				{
						case 0:
						case 1:
						case 9:
								addressLength = 2;
								break;

            case 5:
            case 6:
                addressLength = 0;
                break;

						case 2:
						case 8:
								addressLength = 3;
								break;

						case 3:
						case 7:
								addressLength = 4;
								break;

						default:
								printf("unknown record type");
								return 0;
				}
				tempBufferCount = Substring(buffer,line,index,2);
				//printf("record value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				byteCount = hex2int(buffer,tempBufferCount);
        index += 2;
        checksum += byteCount;

				//byteCount = ((int)line[index++])*10 + ((int)line[index++]);
				//int byteCount = Convert.ToInt32(line.Substring(index, 2), 16);
				//printf("byteCount %d\r\n",byteCount);



				//Address, 4, 6 or 8 hex digits determined by the record type
				for (i = 0; i < addressLength; i++)
				{
						tempBufferCount = Substring(buffer,line,index+i*2,2);
						//printf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						checksum += hex2int(buffer,tempBufferCount);
						//string ch = line.Substring(index + i * 2, 2);
						//checksum += Convert.ToInt32(ch, 16);
				}
        if (addressLength!=0) {
          tempBufferCount = Substring(buffer,line,index,addressLength*2);
  				//printf("temp address value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
  				address = hex2int(buffer,tempBufferCount);
        }


				//address = Convert.ToInt32(line.Substring(index, addressLength * 2), 16);
        //printf("index %d\n",index );
        index += addressLength * 2;
        //printf("index %d\n",index );
				byteCount -= addressLength ;
        //printf("byteCount %d\n",byteCount );
				//Data, a sequence of bytes.
				//data.length = 255
				assert(byteCount<255,"byteCount bigger than 255");
				for (i = 0; i < byteCount-1; i++)
				{
						tempBufferCount = Substring(buffer,line,index,2);
						//printf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						data[i] = hex2int(buffer,tempBufferCount);
						//data[i] = (byte)Convert.ToInt32(line.Substring(index, 2), 16);
						index += 2;
						checksum += data[i];
				}

				//Checksum, two hex digits. Inverted LSB of the sum of values, including byte count, address and all data.
				//readChecksum = (byte)Convert.ToInt32(line.Substring(index, 2), 16);

				tempBufferCount = Substring(buffer,line,index,2);
				//printf("read checksum value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				readChecksum = hex2int(buffer,tempBufferCount);
        //printf("checksum %d\r\n",checksum );
				byteCheckSum = (byte)(checksum & 0xFF);
        //printf("checksum %d\r\n",byteCheckSum );
        byteCheckSum = ~byteCheckSum;
        //printf("checksum %d\r\n",byteCheckSum );
				if (readChecksum != byteCheckSum){
					printf("failed checksum\r\n" );
					return;
				}

				//Put in memory
				assert((byteCount-1) % 4 == 0, "Data should only contain full 32-bit words.");
        //printf("recordType %d\n", recordType);
        //printf("%lu\n",(unsigned long)data[0] );
        //printf("byteCount %d\n",byteCount );
        switch (recordType)
				{
						case 3: //data intended to be stored in memory.

								for (i = 0; i < byteCount-1; i += 4)
								{
										memVal = 0;
										for (j = i; j < i + 4; j++)
										{

												memVal <<= 8;
												memVal |= data[j];
                        	//printf("0x%08x\n",(unsigned int)memVal );
										}
                    memValues[wordsLoaded] = memVal;
										wordsLoaded++;

                    if (wordsLoaded > wordsLength) {
                      printf("words exceed max length\n" );
                      return;
                    }
										printf("0x%08x,",(unsigned int)memVal );
                    //printf("%d,\n",(unsigned int)memVal );
								}

								break;


						case 7: //entry point for the program.
								// CPU.PC = (uint)address;
                printf("\n};\nint shell_pc =  0x%08x;\n", (unsigned int)address);
								break;
				}
        if (linecount >= length) {
          break;
        }
		}

		return wordsLoaded;

}
