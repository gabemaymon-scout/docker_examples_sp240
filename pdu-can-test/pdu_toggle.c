#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <csp/csp.h>
#include <csp/csp_debug.h>
#include <csp/drivers/can_socketcan.h>

#define PDU_NODE_ADDR 1 // Target PDU Address
#define PDU_PARAM_PORT 10 // Standard parameter server port
#define CLIENT_PORT 15 // Arbitrary local source port
#define CLIENT_ADDR 2 // Local container address
#define DEVICE_NAME "vcan0" // Command Configuration

#define PARAM_CMD_SET 0x02
#define PARAM_ID_CH_ON 120 // ID 120 from parameter list

void send_pdu_channel_state(uint8_t state_mask)
{
    csp_packet_t * packet;

    // 1. Allocate a standard CSP memory buffer
    packet = csp_buffer_get(0);
    if (packet == NULL)
    {
        printf("Failed to allocate packet buffer\n");
        return;
    }

    // 2. Build the manual packet data payload bytes
    packet->data[0] = PARAM_CMD_SET; // Byte 0: SET command type
    packet->data[1] = (uint8_t)(PARAM_ID_CH_ON & 0xFF); // Byte 1: Parameter ID Low Byte
    packet->data[2] = (uint8_t)((PARAM_ID_CH_ON >> 8) & 0xFF); // Byte 2: Parameter ID High Byte
    packet->data[3] = state_mask; // Byte 3: Value data (u08 size)

    // Total size: Command (1) + ID (2) + Value Data (1) = 4 bytes
    packet->length = 4;

    printf(
        "Sending PDU Payload [0x%02X, ID: %d, Value: 0x%02X]...\n",
        packet->data[0],
        PARAM_ID_CH_ON,
        packet->data[3]
    );

    // 3. Fire the connectionless datagram matching Space Inventor's signature
    csp_sendto(
        CSP_PRIO_NORM,
        PDU_NODE_ADDR,
        PDU_PARAM_PORT,
        CLIENT_PORT,
        CSP_O_NONE,
        packet
    );
}

int main(int argc, char * argv[])
{
    csp_iface_t * iface;
    int ret;

    /* Initialize core CSP system hooks */
    csp_init();

    /* Open the hardware SocketCAN channel layer */
    ret = csp_can_socketcan_open_and_add_interface(
        DEVICE_NAME,
        CSP_IF_CAN_DEFAULT_NAME,
        CLIENT_ADDR,
        1000000,
        true,
        &iface
    );

    if (ret != CSP_ERR_NONE)
    {
        printf("Failed to bind SocketCAN interface: %d\n", ret);
        return 1;
    }

    iface->is_default = 1;

    printf("--- Executing PDU Channel Control Script ---\n");

    // Command: Turn ON Channel 1 (Bit index 0 = 0x01)
    send_pdu_channel_state(0x01);
    sleep(2); // Keep channel active for 2 seconds

    // Command: Turn OFF Channel 1 (Bit index 0 = 0x00)
    send_pdu_channel_state(0x00);

    printf("Commands successfully sent to the network bus.\n");

    return 0;
}