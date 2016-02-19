#include <lws_config.h>
#include <stdio.h>
#include <stdlib.h>
#include <libwebsockets.h>

#ifndef BOOL
#define BOOL
typedef enum { false, true } bool;
#endif

//externalMessageEnqueue(uint8_t * msg, uint8_t msgSize, uint16_t listener_id);



struct Websocket_instance_type {
    uint16_t listener_id;
    //Connector// Pointer to receiver list
struct Msg_Handler ** gui_receiver_list_head;
struct Msg_Handler ** gui_receiver_list_tail;
// Handler Array
struct Msg_Handler * gui_handlers;

};

extern struct Websocket_instance_type Websocket_instance;


struct libwebsocket * Websocket_clients[16];
int Websocket_nb_client;

struct lws_context_creation_info Websocket_info;
struct libwebsocket_context *Websocket_context;


uint16_t add_client(struct libwebsocket *wsi) {
	uint16_t i = 0;
	bool done = false;
	while ((!done) && (i < 16)) {
		if(Websocket_clients[i] == NULL) {
			Websocket_clients[i] = wsi;
			done = true;
		}
		i++;
	}
	if (!done) {
            printf("[Websocket] Client list overflow\n");
            return -1;
	} else {
            Websocket_nb_client++;
            i=i-1;
            return i;
	}
}

uint16_t remove_client(struct libwebsocket *wsi) {
	uint16_t i = 0;
	bool done = false;
	while ((!done) && (i < 16)) {
            if(Websocket_clients[i] == wsi) {
                Websocket_clients[i] = NULL;
                done = true;
            }
            i++;
	}
	if (!done) {
            printf("[Websocket] Client not found\n");
            return -1;
	} else {
            Websocket_nb_client--;
            i=i-1;
            return i;
	}
}


static int Websocket_callback_http(struct libwebsocket_context * this,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len)
{
    return 0;
}

static int Websocket_callback_ThingML_protocol(struct libwebsocket_context * this,
                                   struct libwebsocket *wsi,
                                   enum libwebsocket_callback_reasons reason,
                                   void *user, void *in, size_t len)
{
   
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:{ // just log message that someone is connecting
            uint16_t clientID = add_client(wsi);
            //printf("[Websocket] New Client:%i\n", clientID);
		
            break;}

        case LWS_CALLBACK_RECEIVE: {
                Websocket_parser(in, len, Websocket_instance.listener_id);
            break;
        }
		
        /*case LWS_CALLBACK_WSI_DESTROY: {
                uint16_t clientID = remove_client(wsi);
		
                printf("[Websocket] Wsi destroyed:%i\n", clientID);
        }*/

        case LWS_CALLBACK_CLOSED: {
                uint16_t clientID = remove_client(wsi);
                //printf("[Websocket] Connexion with client closed:%i\n", clientID);
		
        }

        default:
            break;
    }
   
   
    return 0;
}

static struct libwebsocket_protocols protocols[] = {
    /* first protocol must always be HTTP handler */
    {
        "http-only",   // name
        Websocket_callback_http, // callback
        0              // per_session_data_size
    },
    {
        "ThingML-protocol", // protocol name - very important!
        Websocket_callback_ThingML_protocol,   // callback
        0                          // we don't use any per session data
    },
    {
        NULL, NULL, 0   /* End of list */
    }
};

void Websocket_parser(char * in_msg, int size, int listener_id) {
int len = strlen((char *) in_msg);
            //printf("[/*PORT_NAME*/] l:%i\n", len);
            if ((len % 3) == 0) {
                unsigned char msg[len % 3];
                unsigned char * p = in_msg;
                int buf = 0;
                int index = 0;
                bool everythingisfine = true;
                while ((index < len) && everythingisfine) {
                    if((*p - 48) < 10) {
                        buf = (*p - 48) + 10 * buf;
                    } else {
                        everythingisfine = false;
                    }
                    if ((index % 3) == 2) {
                        if(buf < 256) {
                                msg[(index-2) / 3] =  (uint8_t) buf;
                        } else {
                                everythingisfine = false;
                        }
                        buf = 0;
                    }
                    index++;
                    p++;
                }
                if(everythingisfine) {
                    externalMessageEnqueue(msg, (len / 3), listener_id);
                } else {
                }
}
}


void Websocket_set_listener_id(uint16_t id) {
	Websocket_instance.listener_id = id;
}

void Websocket_setup() {
    memset(&Websocket_info, 0, sizeof Websocket_info);
    lws_set_log_level(2,NULL);
    int port = 9000;
    const char *interface = NULL;
    // we're not using ssl
    const char *cert_path = NULL;
    const char *key_path = NULL;
    // no special options
    int opts = 0;
   
    Websocket_info.port = port;
    Websocket_info.iface = interface;
    Websocket_info.protocols = protocols;
    Websocket_info.extensions = libwebsocket_get_internal_extensions();
    Websocket_info.ssl_cert_filepath = NULL;
    Websocket_info.ssl_private_key_filepath = NULL;

    Websocket_info.gid = -1;
    Websocket_info.uid = -1;
    Websocket_info.options = opts;
    printf("[Websocket] Init WS Server on port:%i\n", port);
}

void Websocket_start_receiver_process() {

    printf("[Websocket] Start running WS Server\n");
    // create libwebsocket Websocket_context representing this server
    Websocket_context = libwebsocket_create_context(&Websocket_info);
   
    if (Websocket_context == NULL) {
        fprintf(stderr, "[Websocket] libwebsocket init failed\n");
        return -1;
    }
	
    printf("[Websocket] Starting server...\n");

    
	
    // infinite loop, to end this server send SIGTERM. (CTRL+C)
    while (1) {
        libwebsocket_service(Websocket_context, 50);
    }
	
    libwebsocket_context_destroy(Websocket_context);
}

void Websocket_forwardMessage(char * msg, int length) {
	
	unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + length + 1 +
						  LWS_SEND_BUFFER_POST_PADDING];
	unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];	
	unsigned char *q = p;
	
        
        int i, m;
        for(i = 0; i < length; i++) {
                *q = msg[i];
                q++;
        }
        *q = '\0';

	//printf("[Websocket] Trying to send:\n%s \n", p);

       for(i = 0; i < Websocket_nb_client; i++) {
m = libwebsocket_write(Websocket_clients[i], p, length + 1, LWS_WRITE_TEXT);
}

}

