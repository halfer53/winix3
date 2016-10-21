#include "winix.h"

proc_t *exec_new_proc(size_t *lines, size_t length, size_t entry, int priority, char *name){
	proc_t *p = NULL;
	if(p = getsys_free_proc()) {
		p = exec_proc(p,lines,length,entry,priority,name);
	}
  assert(p != NULL,"Exec failed");
  return p;
}

proc_t *exec_replace_existing_proc(proc_t *p,size_t *lines, size_t length, size_t entry, int priority, char *name){
	assert(p != NULL, "can't exec null process");
	sys_free(p->rbase);
	proc_set_default(p);
	p = exec_proc(p,lines,length,entry,priority,name);
  assert(p != NULL,"Exec failed");
  return p;
}


static proc_t *exec_proc(proc_t *p,size_t *lines, size_t length, size_t entry, int priority, char *name){
	void *ptr_base = NULL;
	int i = 0;

	assert(p != NULL, "can't exec null process");

		//it's best to malloc text segment and stack together, so they stick together, and it's easier to manage
		ptr_base = sys_malloc(length + DEFAULT_STACK_SIZE);
		assert(ptr_base != NULL,"memory is full");
		memcpy(ptr_base, lines,length);

		//p->sp = (size_t *)ptr_base + (size_t)DEFAULT_STACK_SIZE + length;
		p->sp = (size_t *)(length + DEFAULT_STACK_SIZE); //SP should be the same if virtual address is take into account

		p->priority = priority;
		p->pc = (void (*)())entry; //PC should be the same if virtual address is taken into account
		//p->ra = original->ra;
		p->rbase = ptr_base;

		//Initialise protection table
		//TODO: this loop allows unrestricted access to all memory.
		//Update to only enable memory blocks belonging to the process.
		p->ptable = p->protection_table;
		for(i = 0; i < PROTECTION_TABLE_LEN; i++) {
			p->protection_table[i] = 0xffffffff;
		}

		strcpy(p->name,name);

		//Set the process to runnable, and enqueue it.
		p->state = RUNNABLE;

		p->length = length;
		//process_overview();
		//kprintf("before at p %d, proc_i %d\r\n",priority,ready_q[priority][HEAD]->proc_index );
		add_to_scheduling_queue(p);
		//kprintf("before at p %d, proc_i %d\r\n",priority,ready_q[priority][HEAD]->proc_index );
		//process_overview();
	return p;
}



int winix_load_srec_data_length(char *line){
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

				kprintf("%s\r\n",line);
        //kprintf("loop %d\n",linecount );
				//Start code, always 'S'
				assert(line[index++] == 'S',"Expecting S");

				recordType = line[index++] - '0';
        if (recordType == 5 || recordType == 6) {

        }else{
          kprintf("recordType %d\n",recordType );
          kprintf("format is incorrect\n" );
          return -1;
        }
        tempBufferCount = Substring(buffer,line,index,2);
				//kprintf("record value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				byteCount = hex2int(buffer,tempBufferCount);
        index += 2;
        checksum += byteCount;

				assert(byteCount<255,"byteCount bigger than 255");

						tempBufferCount = Substring(buffer,line,index,(byteCount-1)*2 );
						//kprintf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						data = hex2int(buffer,tempBufferCount);
            //kprintf("data %d\n", data);
            index += (byteCount-1)*2;
            checksum += data;

				//Checksum, two hex digits. Inverted LSB of the sum of values, including byte count, address and all data.
				//readChecksum = (byte)Convert.ToInt32(line.Substring(index, 2), 16);
        //kprintf("checksum %d\n",checksum );
				tempBufferCount = Substring(buffer,line,index,2);
				//kprintf("read checksum value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				readChecksum = hex2int(buffer,tempBufferCount);
        // kprintf("readChecksum %d\n",readChecksum );
        // kprintf("checksum %d\n",checksum );
        //kprintf("checksum %d\r\n",checksum );
        if (checksum > 255) {
          byteCheckSum = (byte)(checksum & 0xFF);
          //kprintf("checksum %d\r\n",byteCheckSum );
          byteCheckSum = ~byteCheckSum;
        }else{
          byteCheckSum = ~byteCheckSum;
          byteCheckSum = checksum;
        }
        //kprintf("checksum %d\r\n",byteCheckSum );
				if (readChecksum != byteCheckSum){
					kprintf("failed checksum\r\n" );
					return -1;
				}
        return data;
}



int winix_load_srec_mem_val(char *(*lines), int length,int lines_start_index,int wordsLength){
	char memValues[1];
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
	size_t memVal = 0;
  int i = 0;
  int j = 0;
  int linecount = lines_start_index;

	while(1){

		char* line = lines[linecount];
    linecount++;
    index = 0;
    checksum = 0;

				//kprintf("%s\r\n",line);
        //kprintf("loop %d\n",linecount );
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
								kprintf("unknown record type");
								return 0;
				}
				tempBufferCount = Substring(buffer,line,index,2);
				//kprintf("record value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				byteCount = hex2int(buffer,tempBufferCount);
        index += 2;
        checksum += byteCount;

				//byteCount = ((int)line[index++])*10 + ((int)line[index++]);
				//int byteCount = Convert.ToInt32(line.Substring(index, 2), 16);
				//kprintf("byteCount %d\r\n",byteCount);



				//Address, 4, 6 or 8 hex digits determined by the record type
				for (i = 0; i < addressLength; i++)
				{
						tempBufferCount = Substring(buffer,line,index+i*2,2);
						//kprintf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						checksum += hex2int(buffer,tempBufferCount);
						//string ch = line.Substring(index + i * 2, 2);
						//checksum += Convert.ToInt32(ch, 16);
				}
        if (addressLength!=0) {
          tempBufferCount = Substring(buffer,line,index,addressLength*2);
  				//kprintf("temp address value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
  				address = hex2int(buffer,tempBufferCount);
        }


				//address = Convert.ToInt32(line.Substring(index, addressLength * 2), 16);
        //kprintf("index %d\n",index );
        index += addressLength * 2;
        //kprintf("index %d\n",index );
				byteCount -= addressLength ;
        //kprintf("byteCount %d\n",byteCount );
				//Data, a sequence of bytes.
				//data.length = 255
				assert(byteCount<255,"byteCount bigger than 255");
				for (i = 0; i < byteCount-1; i++)
				{
						tempBufferCount = Substring(buffer,line,index,2);
						//kprintf("temp byte value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
						data[i] = hex2int(buffer,tempBufferCount);
						//data[i] = (byte)Convert.ToInt32(line.Substring(index, 2), 16);
						index += 2;
						checksum += data[i];
				}

				//Checksum, two hex digits. Inverted LSB of the sum of values, including byte count, address and all data.
				//readChecksum = (byte)Convert.ToInt32(line.Substring(index, 2), 16);

				tempBufferCount = Substring(buffer,line,index,2);
				//kprintf("read checksum value %s, value in base 10: %d,length %d\r\n",buffer,hex2int(buffer,tempBufferCount),tempBufferCount);
				readChecksum = hex2int(buffer,tempBufferCount);
        //kprintf("checksum %d\r\n",checksum );
				byteCheckSum = (byte)(checksum & 0xFF);
        //kprintf("checksum %d\r\n",byteCheckSum );
        byteCheckSum = ~byteCheckSum;
        //kprintf("checksum %d\r\n",byteCheckSum );
				if (readChecksum != byteCheckSum){
					kprintf("failed checksum\r\n" );
					return -1;
				}

				//Put in memory
				assert((byteCount-1) % 4 == 0, "Data should only contain full 32-bit words.");
        //kprintf("recordType %d\n", recordType);
        //kprintf("%lu\n",(size_t)data[0] );
        //kprintf("byteCount %d\n",byteCount );
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
                        	//kprintf("0x%08x\n",(unsigned int)memVal );
										}
                    memValues[wordsLoaded] = memVal;
										wordsLoaded++;

                    if (wordsLoaded > wordsLength) {
                      kprintf("words exceed max length\n" );
                      return -1;
                    }
										//kprintf("0x%08x\n",(unsigned int)memVal );
								}

								break;


						case 7: //entry point for the program.
								// CPU.PC = (uint)address;
								break;
				}
        if (linecount >= length) {
          break;
        }
		}

		return wordsLoaded;
}
