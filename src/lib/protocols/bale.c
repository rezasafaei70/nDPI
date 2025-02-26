/*
 * bale.c

 */


#include "ndpi_protocol_ids.h"

#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_BALE
#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_BALE_FILE
#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_BALE_MESSAGE


#include "ndpi_api.h"
int j = 1;
int bale_1 = 0;
int bale_2 = 0;
int bale_3 = 0;
int bale_file1 = 0;
int bale_file2 = 0;
int bale_file3 = 0;
int bale_file4 = 0;
int bale_file5 = 0;
int bale_message = 0;
static void ndpi_int_bale_add_connection(struct ndpi_detection_module_struct
                                         *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_BALE, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found bale\n");
}

static void ndpi_int_bale_file_add_connection(struct ndpi_detection_module_struct
                                              *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_BALE_FILE, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found bale\n");
}

static void ndpi_int_bale_message_add_connection(struct ndpi_detection_module_struct
                                                 *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_BALE_MESSAGE, NDPI_PROTOCOL_UNKNOWN,
                               NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found bale\n");
}


void ndpi_search_bale(struct ndpi_detection_module_struct *ndpi_struct,
                      struct ndpi_flow_struct *flow) {
    struct ndpi_packet_struct *packet = &ndpi_struct->packet;

    NDPI_LOG_DBG(ndpi_struct, "search bale\n");
//    printf("rr  %d", packet->payload_packet_len);
    if (packet->payload_packet_len == 0)
        return;

    if (packet->tcp != NULL) {



//      printf(" reza \n ");

        for (int i = 0; i < packet->payload_packet_len; i++) {
//            printf("%02x  ",packet->payload[i]);
//
            if (packet->payload[i] == 0xff && packet->payload[i + 4] == 0x27 && packet->payload[i + 5] == 0x05 &&
                packet->payload[i + 6] == 0x07 && packet->payload[i + 11] == 0x20) {
                bale_1 =  1;

            }

            if (packet->payload[i] == 0xfe && packet->payload[i + 4] == 0x23 && packet->payload[i + 5] == 0x05 &&
                packet->payload[i + 6] == 0x07) {
                bale_2 = 1;

            }

            if (packet->payload[i] == 0xd6 && packet->payload[i + 1] == 0xcd && packet->payload[i + 2] == 0x85 &&
                packet->payload[i + 3] == 0x20
                && packet->payload[i + 4] == 0x53 && packet->payload[i + 5] == 0xb1 && packet->payload[i + 6] == 0x7e && packet->payload[i + 7] == 0xd5
                    ) {

                bale_3 = 1;

            }


            if (packet->payload[i] == 0xaa && packet->payload[i + 1] == 0x03 && packet->payload[i + 2] == 0x03
                    ) {
                bale_file1 = 1;
            }
            if (packet->payload[i] == 0xae && packet->payload[i + 1] == 0x01 && packet->payload[i + 2] == 0x00 &&
                packet->payload[i + 3] == 0x00
                    ) {

                bale_file2 = 1;

            }

            if (packet->payload[i] == 0x1d && packet->payload[i + 1] == 0x00 && packet->payload[i + 2] == 0x17 &&
                packet->payload[i + 3] == 0x00
                && packet->payload[i + 4] == 0x18 && packet->payload[i + 5] == 0x00 && packet->payload[i + 6] == 0x0b
                    ) {

                bale_file3 = 1;

            }

            if (packet->payload[i] == 0x69 && packet->payload[i + 1] == 0x6c && packet->payload[i + 2] == 0x6f &&
                packet->payload[i + 3] == 0x6f
                && packet->payload[i + 4] == 0x2e && packet->payload[i + 5] == 0x62 && packet->payload[i + 6] == 0x61 &&
                packet->payload[i + 7] == 0x6c
                    ) {

                bale_file4 = 1;

            }

            if (packet->payload[i] == 0x14 && packet->payload[i + 1] == 0x00 && packet->payload[i + 2] == 0x9c &&
                packet->payload[i + 3] == 0x00
                && packet->payload[i + 4] == 0x9d && packet->payload[i + 5] == 0x00 && packet->payload[i + 6] == 0x2f &&
                packet->payload[i + 7] == 0x00
                    ) {

                bale_file5 = 1;

            }


        }

        if (bale_1 == 1 && bale_2 == 1 && bale_3 == 1) {
            ndpi_int_bale_message_add_connection(ndpi_struct, flow);
        }
        if (bale_file1 == 1 && bale_file2 == 1 && bale_file3 == 1 && bale_file4 == 1 && bale_file5 == 1) {
            ndpi_int_bale_file_add_connection(ndpi_struct, flow);
        }

        u_int32_t source_ip = ntohl(packet->iph->saddr);
        u_int32_t dest_ip = ntohl(packet->iph->daddr);

        if(ndpi_ips_match(source_ip, dest_ip, 0xB90DE740, 28)
           || ndpi_ips_match(source_ip, dest_ip, 0x25E489D0, 28)
           || ndpi_ips_match(source_ip, dest_ip, 0x2BD4478, 24)
                ){

            if (bale_1 == 1 && bale_2 == 1 && bale_3 == 1) {
                ndpi_int_bale_message_add_connection(ndpi_struct, flow);
            }


        }



    }


    NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
}


void init_bale_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id) {
    ndpi_set_bitmask_protocol_detection("BALE", ndpi_struct, *id,
                                        NDPI_PROTOCOL_BALE,
                                        ndpi_search_bale,
                                        NDPI_SELECTION_BITMASK_PROTOCOL_V4_V6_TCP_OR_UDP,
                                        SAVE_DETECTION_BITMASK_AS_UNKNOWN,
                                        ADD_TO_DETECTION_BITMASK);


    *id += 1;
}
