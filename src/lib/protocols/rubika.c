/*
 * rubika.c

 */


#include "ndpi_protocol_ids.h"

#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_RUBIKA
#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_RUBIKA_MESSANGER
#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_RUBIKA_RUBINO
#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_RUBIKA_SERVICE
#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_RUBIKA_MESSANGER_FILE
#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_RUBIKA_RUBINO_FILE


#include "ndpi_api.h"
//int j = 1;
//int j = 1;
int rubika_1 = 0;
int rubika_2 = 0;
int rubika_3 = 0;
int rubika_4 = 0;
int rubika_5 = 0;
int messanger = 0;
int rubino = 0;
int services = 0;
int filemessanger = 0;

static void ndpi_int_rubika_add_connection(struct ndpi_detection_module_struct
                                           *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_RUBIKA, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found rubika\n");
}
static void ndpi_int_rubika_messanger_add_connection(struct ndpi_detection_module_struct
                                                     *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_RUBIKA_MESSANGER, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found rubika\n");
}
static void ndpi_int_rubika_rubino_add_connection(struct ndpi_detection_module_struct
                                                  *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_RUBIKA_RUBINO, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found rubika\n");
}
static void ndpi_int_rubika_rubino_file_add_connection(struct ndpi_detection_module_struct
                                                       *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_RUBIKA_RUBINO_FILE, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found rubika\n");
}
static void ndpi_int_rubika_service_add_connection(struct ndpi_detection_module_struct
                                                   *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_RUBIKA_SERVICE, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found rubika\n");
}

static void ndpi_int_rubika_message_file_add_connection(struct ndpi_detection_module_struct
                                                        *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_RUBIKA_MESSANGER_FILE, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found rubika\n");
}

static u_int8_t is_rubika_port_range(u_int16_t port) {
    if((port >= 500) && (port <= 600))
        return(1);


    return(0);
}



void ndpi_search_rubika(struct ndpi_detection_module_struct *ndpi_struct,
                      struct ndpi_flow_struct *flow) {
    struct ndpi_packet_struct *packet = &ndpi_struct->packet;

    NDPI_LOG_DBG(ndpi_struct, "search rubika\n");

    if (packet->payload_packet_len == 0)
        return;

    if (packet->tcp != NULL) {


        for(int i=0;i<packet->payload_packet_len;i++){
//            printf("%02x ",packet->payload[i]);

            if(packet->payload[i]==0x69 && packet->payload[i+1]==0x72 && packet->payload[i+2]==0x61 && packet->payload[i+3]==0x6e && packet->payload[i+4]==0x6c && packet->payload[i+5]==0x6d  && packet->payload[i+6]==0x73 ){
                rubika_1=1;


            }


            if(packet->payload[i]==0xc0 && packet->payload[i+1]==0x30 ){
                rubika_2=1;

            }

            if(packet->payload[i]== 0xff && packet->payload[i+1]== 0x01 ){
                rubika_3=1;

            }

            if(packet->payload[i]==0x6e && packet->payload[i+1]==0x6c  && packet->payload[i+2]==0x6d ){
                rubika_4=1;

            }

            if(packet->payload[i]== 0x2e && packet->payload[i+1]== 0x69  && packet->payload[i+2]== 0x72){
                rubika_5=1;

            }
            if(packet->payload[i]== 0x6d && packet->payload[i+1]== 0x65 && packet->payload[i+2]== 0x73 && packet->payload[i+3]== 0x73 && packet->payload[i+4]== 0x65 && packet->payload[i+5]== 0x6e  && packet->payload[i+6]== 0x67  && packet->payload[i+7]== 0x65  && packet->payload[i+8]== 0x72 ){

                if(packet->payload[i+9]== 0x38 ){
                    filemessanger = 1;

                }else{

                    messanger = 1;
                }
            }

            if(packet->payload[i]== 0x72 && packet->payload[i+1]== 0x75 && packet->payload[i+2]== 0x62 && packet->payload[i+3]== 0x69 && packet->payload[i+4]== 0x6e && packet->payload[i+5]== 0x6f ){
                rubino = 1;

            }

            if(packet->payload[i]== 0x73 && packet->payload[i+1]== 0x65 && packet->payload[i+2]== 0x72 && packet->payload[i+3]== 0x76 && packet->payload[i+4]== 0x69 && packet->payload[i+5]== 0x63 && packet->payload[i+6]== 0x65 && packet->payload[i+7]== 0x73 ){
                services = 1;

            }


        }

        if((rubika_1 ==1 && rubika_2==1  && rubika_3==1 && rubika_4==1 && rubika_5==1)){
            if(messanger==1){
                ndpi_int_rubika_messanger_add_connection(ndpi_struct, flow);
            }

            else if(filemessanger==1){
                ndpi_int_rubika_message_file_add_connection(ndpi_struct, flow);
            }
            else if(rubino==1){
                ndpi_int_rubika_rubino_add_connection(ndpi_struct, flow);
            }
            else if(services==1 ){
                ndpi_int_rubika_service_add_connection(ndpi_struct, flow);
            }
            else if( packet->payload_packet_len ==517){
                ndpi_int_rubika_messanger_add_connection(ndpi_struct, flow);
            }
            else if( packet->payload_packet_len ==260 || packet->payload_packet_len==259){
                ndpi_int_rubika_rubino_file_add_connection(ndpi_struct, flow);
            }

            else{
                ndpi_int_rubika_add_connection(ndpi_struct, flow);
            }

        }

    }


    NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
}


void init_rubika_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id) {

    ndpi_set_bitmask_protocol_detection("RUBIKA", ndpi_struct, *id,
                                        NDPI_PROTOCOL_RUBIKA,
                                        ndpi_search_rubika,
                                        NDPI_SELECTION_BITMASK_PROTOCOL_V4_V6_TCP_OR_UDP,
                                        SAVE_DETECTION_BITMASK_AS_UNKNOWN,
                                        ADD_TO_DETECTION_BITMASK);


    *id += 1;
}
