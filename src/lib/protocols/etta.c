/*
 * etta.c

 */


#include "ndpi_protocol_ids.h"

#define NDPI_CURRENT_PROTO NDPI_PROTOCOL_ETTA



#include "ndpi_api.h"

static void ndpi_int_etta_add_connection(struct ndpi_detection_module_struct
                                         *ndpi_struct, struct ndpi_flow_struct *flow) {
    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_ETTA, NDPI_PROTOCOL_UNKNOWN, NDPI_CONFIDENCE_DPI);
    NDPI_LOG_INFO(ndpi_struct, "found etta\n");
}



void ndpi_search_etta(struct ndpi_detection_module_struct *ndpi_struct,
                      struct ndpi_flow_struct *flow) {
    struct ndpi_packet_struct *packet = &ndpi_struct->packet;

    NDPI_LOG_DBG(ndpi_struct, "search etta\n");
//    printf("%u rr ",packet->payload_packet_len);
    if (packet->payload_packet_len == 0)
        return;

    if (packet->tcp != NULL) {

        for (int i = 0; i < packet->payload_packet_len; i++) {
//            printf("%02x  ",packet->payload[i]);

        }



    }


    NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
}


void init_etta_dissector(struct ndpi_detection_module_struct *ndpi_struct, u_int32_t *id) {
    ndpi_set_bitmask_protocol_detection("ETTA", ndpi_struct, *id,
                                        NDPI_PROTOCOL_ETTA,
                                        ndpi_search_etta,
                                        NDPI_SELECTION_BITMASK_PROTOCOL_V4_V6_TCP_OR_UDP,
                                        SAVE_DETECTION_BITMASK_AS_UNKNOWN,
                                        ADD_TO_DETECTION_BITMASK);


    *id += 1;
}
