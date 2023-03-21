//CLIENT-MASTER
#include <stdio.h>
#include <stdlib.h>
#include <modbus.h>
#include <errno.h>  //added because the compiler complained it was missing.

int main(int argc, char *argv[]) {
modbus_t *ctx;
uint16_t tab_reg[64];
int rc, i;

ctx = modbus_new_tcp("192.168.100.102", 502); // 192.168.0.33 is the ip address of the target device (modbus server) 
if (ctx == NULL) {
   fprintf(stderr, "Unable to allocate libmodbus context\n");
   return -1;
 }
modbus_set_debug(ctx, TRUE);


//modbus_connect(ctx); 
if (modbus_connect(ctx) == -1) {
    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
    modbus_free(ctx);
    return -1;
}


rc = modbus_read_registers(ctx, 0x01, 1, tab_reg); 

if (rc == 1) { 
    printf("Read registers: "); 
   // for ( i=0; i<10; i++) { 
        printf("%d ", tab_reg[0]); 
   // } 
    printf("\n");
    printf("%f\n", *(float*)tab_reg);  // added because my server had a float value in the first two registers (32 bits)
} else { 
    fprintf(stderr, "Failed to read registers: %s\n", modbus_strerror(errno)); 
} 

modbus_close(ctx); 
modbus_free(ctx); 
return 0; 
}
