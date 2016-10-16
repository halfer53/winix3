#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int i = 0;
  int length = 0;
  int wordslength = 0;
  int temp = 0;
  int recordtype = 0;



        //exit(EXIT_SUCCESS);

  // char *lines[100][128] = {"S503006467",
	// "S60303c933",
	// "S32D000000001EE300059DE000039FE000043D0E13371DDD00019DE000008DE000059DE000018DE000069DE00002DA",
	// "S32D0000000A600002360D0100010101000D8DE000038FE000041EE1000550F000001EE300059DE000039FE00004E2",
	// "S32D000000143D0E13371DDD00029DE0000090E000018DE000059DE00002600002360D0100010101000D8DE0000328",
	// "S32D0000001E8FE000041EE1000550F000001EE300059DE000039FE000043D0E13371DDD00039DE000008DE0000573",
	// "S32D000000289DE000018DE000069DE00002600002360D0100010101000D8DE000038FE000041EE1000550F000005D",
	// "S32D000000321EE300029CE000009DE000018DE000029DE000023D0E00071DDD00038DD000001DDB00022DD800000A",
	// "S32D0000003CB0DFFFFA3D0E00071DDD00008CE000029CD00000010100008CE000008DE000011EE1000250F00000CB",
	// "S32D000000461EE300019DE000003D0E00071DDD00038DD000001DDB00012DD80000B0DFFFFA3D0E00071DDD00018E",
	// "S32D0000005081D000008DE000001EE1000150F000001EE3000696E0000197E000029CE000039DE000049FE0000509",
	// "S32D0000005A370E3B9A177DCA008DE000062DDA0000B0D000041D0100309DE00000600000324000007D8DE0000675",
	// "S32D000000642DD60000B0D0000A1D01002D9DE00000600000323D0EFFFF1DDDFFFF8CE000060DD4000C9DE0000664",
	// "S32D0000006E400000701776000A8DE000062D72000DB0DFFFFC4000007B8DE0000606D600071D68000A1DD00030B7",
	// "S32D000000789DE00000600000321776000A2D7A0000B0DFFFF786E0000187E000028CE000038DE000048FE0000564",
	// "S32D000000821EE1000650F000001EE3000596E0000197E000029DE000039FE000041701001C8DE000050DDE00077A",
	// "S32D0000008C16DB000F3D66000AB0D000041D6000309DE0000060000032400000971D62000A1DD000419DE000004E",
	// "S32D0000009660000032177200042D760000B0DFFFF086E0000187E000028DE000038FE000041EE1000550F0000005",
	// "S32D000000A01EE300049CE000019DE000029FE00003400000AB8DE000041CD100019CE000048DD000009DE000000B",
	// "S32D000000AA600000328DE000048DD000002DDA0000B0DFFFF68CE000018DE000028FE000031EE1000450F00000AC",
	// "S32D000000B41EE3000796E0000197E000029CE000039DE000049FE0000517E1000717710001400000F88DE000076E",
	// "S32D000000BE8DD000003DDA0025B0D000318DE000071DD100019DE000078DE0000786D000001D0100739DE0000605",
	// "S32D000000C82D68000DB0D000198DE000062D62000DB0D000033D680064B0D00004400000EB3D680078B0D00009DF",
	// "S32D000000D2400000EB8D7000009DE0000060000054177100018DE000071DD100019DE00007400000F88D70000002",
	// "S32D000000DC9DE0000060000084177100018DE000071DD100019DE00007400000F88D7000009DE00000600000A073",
	// "S32D000000E6177100018DE000071DD100019DE00007400000F88DE000071CD100019CE000078DD000009DE0000085",
	// "S32D000000F060000032400000F88DE000071CD100019CE000078DD000009DE00000600000328DE000078DD00000F6",
	// "S32D000000FA2DDA0000B0DFFFC10101000086E0000187E000028CE000038DE000048FE000051EE1000750F0000016",
	// "S32D000001041EE300039CE000009DE00001400001158DE000038DD000008CE000048CC000002DD8000CB0D000015E",
	// "S32D0000010E400001208DE000031DD100019DE000038DE000041DD100019DE000040D0100009DE000028CE00003A6",
	// "S32D000001188CC000002DC8000DB0D000058DE000048DD000008CE000022DDA000CB0DFFFE88DE000038DD0000054",
	// "S32D000001228CE000048CC0000001D2000C8CE000008DE000011EE1000350F000001EE3000397E000009CE0000100",
	// "S32D0000012C9DE000020701000040000130177000018DE000031CD100019CE000038DD000002DDA0000B0DFFFF95D",
	// "S32D000001360101000787E000008CE000018DE000021EE1000350F000001EE300049BE000009CE000019DE0000291",
	// "S32D000001408DE000049DE000034000014B8DE000041CD100019CE000048CE000051BC100019BE000058CC000001B",
	// "S32D0000014A9CD000008DE000058DD000002DDA0000B0DFFFF48DE0000490D0000081E000038BE000008CE00001B6",
	// "S32D000001548DE000021EE1000450F000001EE3000496E0000097E000019CE000029DE000030601000007010000CB",
	// "S32D0000015E40000160166000018DE000040D61000D8DD000002DDA0000B0DFFFFA4000016E0D6000078CE00004F0",
	// "S32D000001680DD1000C8CE000050C71000C8CC000009CD00000177000018DE000050D71000D8DD000002DDA0000E4",
	// "S32D00000172B0DFFFF30D6000078CE000040DD1000C90D0000081E0000486E0000087E000018CE000028DE000039F",
	// "S32D0000017C1EE1000450F000001EE3000496E0000097E000019CE000029DE00003070100000601000087E00006A5",
	// "S32D000001864000018F8DE000040D61000D8CE000050C71000C8CC000009CD0000016600001177000018DE000076A",
	// "S32D000001908CE000060DD0000C2D70000DB0DFFFF38DE000040D61000D90D000000101000686E0000087E0000199",
	// "S32D0000019A8CE000028DE000031EE1000450F000001EE3000D9DE000029FE0000390E000041D0100049DE00006EE",
	// "S32D000001A490E000001DE100059DE00001600000210D0100019DE0000481E000078DE000028FE000031EE1000DD6",
	// "S32D000001AE50F000001EE3000D9DE000029FE0000390E000041D0100059DE000068DE0000D9DE0000790E000004C",
	// "S32D000001B81DE100059DE00001600000210D0100019DE0000481E000078DE000028FE000031EE1000D50F00000F2",
	// "S32D000001C21EE3000D9DE000029FE0000390E0000C1D0100069DE0000590E000001DE100049DE00001600000008E",
	// "S32D000001CC0D0100019DE0000C010100008DE000028FE000031EE1000D50F000001EE3000D9DE000029FE000032F",
	// "S32D000001D690E0000C1D0100079DE0000590E000001DE100049DE00001600000000D0100019DE0000C01010000EE",
	// "S32D000001E08DE000028FE000031EE1000D50F000001EE3000796E0000297E000039CE000049DE000059FE0000643",
	// "S32D000001EA900003C917010080CD0003C99DE000000D0100078CE000070CCB000D2DCB000DB0D00002C6000342DF",
	// "S32D000001F4400001F6C600034096E0000160000157177E00012D720000B0DFFFF1C10003C986E0000287E000035B",
	// "S32D000001FE8CE000048DE000058FE000061EE1000750F000001EE3000596E0000097E000019BE000029CE0000346",
	// "S32D000002089DE0000406010000070100004000022B8DE000050D71000D8DD000003DD20039B0D0000D1D0100017D",
	// "S32D000002128CE000050C71000C8CC000001CC200308BE000061BB200010BB200071BBA00020DDA000B0DC4000DC0",
	// "S32D0000021C0660000D4000022A1D0100018CE000050C71000C8CC000001CC200378BE000061BB200010BB2000758",
	// "S32D000002261BBA00020DDA000B0DC4000D0660000D177000018DE000062D70000DB0DFFFDE0101000686E0000011",
	// "S32D0000023087E000018BE000028CE000038DE000041EE1000550F00000200D000050F00000000003C20000027300",
	// "S32D0000023A000003B90000029E000003B4000002A9000003B100000269000003AC0000025D000003A70000025BA4",
	// "S32D0000024400000000000002B71EE3000497E000009CE000019DE000028DE000049DE000031C0100212DC2000D30",
	// "S32D0000024EB0D000058DE000033DD2007EB0D000021701000140000255070100000101000787E000008CE00001E9",
	// "S32D000002588DE000021EE1000450F000000101000050F000001EE300039DE000009FE0000190E00002600001D3DD",
	// "S32D000002620D0100019DE00002010100008DE000008FE000011EE1000350F000001EE300029DE000009FE00001BF",
	// "S32D0000026C600001C20D0100010101000D8DE000008FE000011EE1000250F000001EE3000F94E0000695E00007FF",
	// "S32D0000027696E0000897E000099BE0000A9CE0000B9DE0000C9FE0000D6000019E0D0100010701000D1D01003CBE",
	// "S32D000002800476000D0546000D0656000D1C0100180B66000C9BE0000E0448000D0558000D0668000C177800649D",
	// "S32D0000028ACD0003889DE000008DE0000E9DE0000196E0000295E0000394E0000497E00005600000B4010100007E",
	// "S32D0000029484E0000685E0000786E0000887E000098BE0000A8CE0000B8DE0000C8FE0000D1EE1000F50F0000059",
	// "S32D0000029E1EE300039DE000019FE00002CD00036D9DE00000600000B4010100008DE000018FE000021EE100037E",
	// "S32D000002A850F000001EE300039DE000019FE00002CD0003669DE00000600000B490E00000600001AF0D0100018F",
	// "S32D000002B20101000D8DE000018FE000021EE1000350F000001EE300049DE000029FE000038DE000042DDA000070",
	// "S32D000002BCB0D0000201010000400002C7CD00034F9DE000008DE000058DD000009DE00001600000B4310EFFFF4D",
	// "S32D000002C6111DFFFF8DE000028FE000031EE1000450F000001EE3000B94E0000295E0000396E0000497E00005CA",
	// "S32D000002D09CE000069DE000079FE000080501000040000335CD0003479DE00000600000B40601000060000046A0",
	// "S32D000002DA0D0100019D60041B8D60041B3DDA000DB0D00001400002F18D60041B3DDA0008B0D000082D6800009F",
	// "S32D000002E4B0D000048D60041B9DE00000600000321662000116620001400002EE8D60041B9DE000006000003210",
	// "S32D000002EE166000013D600063B0DFFFE81D6000010601000D90D0041BCD0003449DE00000600000B4040100003A",
	// "S32D000002F8C700041B4000031D177100018D7000009DE0000A2DD80000B0D000068DE0000A9DE00000600002465E",
	// "S32D000003020D0100012DD80000B0DFFFF58D7000002DD80000B0D000050D01000414D0000197D003E94000030D15",
	// "S32D0000030C177100018D7000009DE000092DD80000B0D000068DE000099DE00000600002460D0100012DDA00007B",
	// "S32D00000316B0DFFFF58D7000002DD80000B0D000030D01000717D1000190D000008D7000002DDA0000B0DFFFDBE6",
	// "S32D00000320C500023840000323155100028D5000009DE0000A0C01000D2DC90000B0D000088D0003E99DE00000F0",
	// "S32D0000032A8DE0000A9DE00001600001040D0100012DDA0000B0DFFFF294E00000CD0003E99DE000018D5000012C",
	// "S32D0000033470D00000400002D50101000084E0000285E0000386E0000487E000058CE000068DE000078FE0000841",
	// "S32D0000033E1EE1000B50F00000000000300000000000000031000000000000000D0000000A000000000000005778",
	// "S32D00000348000000490000004E00000049000000580000003E0000002000000000000000550000006E0000006BC3",
	// "S32D000003520000006E0000006F000000770000006E00000020000000630000006F0000006D0000006D000000618E",
	// "S32D0000035C0000006E0000006400000020000000270000002500000073000000270000000D0000000A0000000084",
	// "S32D00000366000000420000007900000065000000210000000D0000000A00000000000000500000006C00000061F4",
	// "S32D000003700000006300000065000000680000006F0000006C000000640000006500000072000000200000006693",
	// "S32D0000037A0000006F000000720000002000000053000000480000005500000054000000440000004F0000005726",
	// "S32D000003840000004E0000000D0000000A00000000000000550000007000000074000000690000006D0000006572",
	// "S32D0000038E000000200000006900000073000000200000002500000064000000640000002000000025000000648F",
	// "S32D00000398000000680000002000000025000000640000006D0000002000000025000000640000002E00000025BD",
	// "S32D000003A200000064000000730000000D0000000A0000000000000065000000780000006500000063000000009A",
	// "S32D000003AC000000660000006F000000720000006B000000000000007000000073000000000000006500000078B1",
	// "S32D000003B600000069000000740000000000000073000000680000007500000074000000640000006F000000772E",
	// "S329000003C00000006E00000000000000750000007000000074000000690000006D000000650000000011",
	// "S705000002CB2D"
  //
  // };

  char *init_code[4][31] = {"S503000407",
											"S603000205",
											"S30D000000000101000050F00000B0",
											"S70500000000FA"};

  for ( i = 0; i < 2; i++) {
    temp = exec_phase1_readLength((*init_code)[i],&recordtype);
    if (recordtype != 0 && temp != -1) {
      if (recordtype == 5) {
        length = temp;

      }else if(recordtype == 6){
        wordslength = temp;
      }else{
        printf("incorrect initial record count\n" );
        return;
      }
    }
  }
  //first recordtype 5,and 6 is consumed

  printf("lenght %d\n",length );
  i = exec_phase2(init_code,length,2,wordslength);
  printf("wordsLoaded %d\n", i);
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
			if(a[i] <= 57)
			 val += (a[i]-48)*(1<<(4*(len-1-i)));
			else
			 val += (a[i]-55)*(1<<(4*(len-1-i)));
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

int exec_phase1_readLength(char *line, int* type){
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

				//printf("%s\r\n",line);
        //printf("loop %d\n",linecount );
				//Start code, always 'S'
				assert(line[index++] == 'S',"Expecting S");

				recordType = line[index++] - '0';
        if (recordType == 5 || recordType == 6) {
          *type = recordType;
        }else{
          printf("recordType %d\n",recordType );
          printf("format is incorrect\n" );
          return -1;
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
        // printf("readChecksum %d\n",readChecksum );
        // printf("checksum %d\n",checksum );
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
					return -1;
				}
        return data;
}
//*(unsigned long*)FREE_MEM_BEGIN = (unsigned int)memVal;
//FREE_MEM_BEGIN++;
int exec_phase2(char *(*lines),int length,int lines_start_index,int wordsLength){
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
  int linecount = lines_start_index;

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
										printf("0x%08x,\n",(unsigned int)memVal );
                    //printf("%d,\n",(unsigned int)memVal );
								}

								break;


						case 7: //entry point for the program.
								// CPU.PC = (uint)address;
                printf("addr 0x%08x\n", (unsigned int)address);
								break;
				}
        if (linecount >= length) {
          break;
        }
		}

		return wordsLoaded;

}
