module TERASIC_10to8(
	// global clock & reset
	input		clk,
	input		reset_n,
	

	// streaming sink
	input	[29:0]            	sink_data,
	input								sink_valid,
	output							sink_ready,
	input								sink_sop,
	input								sink_eop,

	// streaming source
	output	[23:0]			  	   source_data,
	output								source_valid,
	input									source_ready,
	output								source_sop,
	output								source_eop

	
);

wire [3:0] package_id/* synthesis keep */; 
wire is_control_id/* synthesis keep */;
reg is_control_package/*synthesis noprune*/;


assign is_control_id = (sink_data[3:0] == 4'hf)?1'b1:1'b0;

always @(posedge clk or negedge reset_n)
begin
	if (~reset_n)
		is_control_package <= 1'b0;
	else if (sink_sop & sink_valid)
		is_control_package <= is_control_id;
end

assign source_data = ((sink_sop & is_control_id) | (~sink_sop & is_control_package))?{sink_data[27:20], sink_data[17:10], sink_data[7:0]}:{sink_data[29:22], sink_data[19:12], sink_data[9:2]};
assign source_valid = sink_valid;
assign sink_ready = source_ready;
assign source_sop = sink_sop;
assign source_eop = sink_eop;


endmodule

