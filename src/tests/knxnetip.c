#include "testfw.h"
#include "../knx/knxnetip.h"
#include "../msgbuilder.h"

deftest(knxnetip_connreq, {
	knxnetip_connreq packet_in = {
		KNXNETIP_CONNREQ_TUNNEL,
		KNXNETIP_LAYER_TUNNEL,
		{KNXNETIP_PROTO_UDP, 0, 0},
		{KNXNETIP_PROTO_UDP, 0, 0}
	};

	// Generate
	msgbuilder mb;
	msgbuilder_init(&mb, 0);
	assert(knxnetip_generate_connreq(&mb, &packet_in));

	// Parse
	knxnetip_packet packet_out;
	assert(knxnetip_parse(mb.buffer, mb.used, &packet_out));

	// Check
	assert(packet_out.service == KNXNETIP_CONNECTION_REQUEST);
	assert(packet_out.connection_request.type == packet_in.type);
	assert(packet_out.connection_request.layer == packet_in.layer);
	assert(packet_out.connection_request.control_host.protocol == packet_in.control_host.protocol);
	assert(packet_out.connection_request.control_host.address == packet_in.control_host.address);
	assert(packet_out.connection_request.control_host.port == packet_in.control_host.port);
	assert(packet_out.connection_request.tunnel_host.protocol == packet_in.tunnel_host.protocol);
	assert(packet_out.connection_request.tunnel_host.address == packet_in.tunnel_host.address);
	assert(packet_out.connection_request.tunnel_host.port == packet_in.tunnel_host.port);
})

deftest(knxnetip, {
	runsubtest(knxnetip_connreq);
})
