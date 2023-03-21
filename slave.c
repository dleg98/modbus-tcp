//SERVER-SLAVE
#include <stdio.h>
#include <stdlib.h>
#include <modbus.h>
#include <errno.h>  //added because the compiler complained it was missing.


int main(int argc, char *argv[]) {
modbus_t *ctx;
modbus_mapping_t *mb_mapping;
int socket;
//uint16_t value[1];
uint16_t tab_reg[1];
tab_reg[0]=54;

ctx = modbus_new_tcp("0.0.0.0", 502);  // Can be either NULL or "0.0.0.0"
 if (ctx == NULL) {
    fprintf(stderr, "Unable to allocate libmodbus context\n");
    return -1;
  }

modbus_set_debug(ctx, TRUE);


mb_mapping = modbus_mapping_new(0, 0, 10, 10); 
if (mb_mapping == NULL) {
    fprintf(
        stderr, "Failed to allocate the mapping: %s\n",
        modbus_strerror(errno)
    );
    modbus_free(ctx);
    return -1;
}

socket = modbus_tcp_listen(ctx, 1); 
 if (socket == -1) {
    fprintf(stderr, "%s\n", modbus_strerror(errno));
    modbus_free(ctx);
    return -1;
  }

modbus_tcp_accept(ctx, &socket); 

//uint16_t random=rand()%20;
for (;;) { 
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH]; 
    int rc; 
    
    rc = modbus_receive(ctx, query); 
    if (rc > 0)  { 
	 modbus_write_register(ctx,0x01,tab_reg[0]);
	//if(rt==-1) 
		//{
		//fprintf(stderr, "Faild to write to modbus register\n"); 
		//}
			//else printf("%d",random);

	sleep(2);
        modbus_reply(ctx, query, rc, mb_mapping); 
	
    } else if (rc == -1) { 
        break; 
    } 
} 

printf("Quit the loop: %s\n", modbus_strerror(errno)); 

modbus_mapping_free(mb_mapping); 
modbus_close(ctx); 
modbus_free(ctx); 

return 0; 
}





