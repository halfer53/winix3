proc_t *exec_new_proc(size_t *lines, size_t length, size_t entry, int priority, char *name);
proc_t *exec_replace_existing_proc(proc_t *p,size_t *lines, size_t length, size_t entry, int priority, char *name);
static proc_t *exec_proc(proc_t *p,size_t *lines, size_t length, size_t entry, int priority, char *name);
int winix_load_srec_data_length(char *line);
int winix_load_srec_mem_val(char *(*lines), int length,int lines_start_index,int wordsLength);
