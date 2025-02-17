void make_rev(unsigned char *data, int len);
void make_pow(unsigned char *data, int len);
void invert_error_bytes(unsigned char *data, int len);
void reverse_byte_order(unsigned char *data, int len);
void zerofill_error_bytes(unsigned char *data, int len);
void generate_gf();
void gen_poly();
void append_error_info(unsigned char *data, int dtalen, int errlen);
int verify_error_info(unsigned char *data, int dtalen, int errlen);

int correct_errors(unsigned char *data, int dtalen, int errlen, unsigned char *erasure=0);
int eras_dec_rs(int *eras_pos,int no_eras);
void initialize_rs(int bits=8, int polynomial=0x187, int index=0x78, int errlen=16);
void free_rs();
int is_rs_initialized();
