module seven_seg_decoder(clk, bcd, seven_seg);

input [3:0] bcd;
input clk;
output reg [6:0] seven_seg;

always @(posedge clk)
    begin   
        case (bcd)
            4'b0000 : begin seven_seg = 7'b1111110; end
            4'b0001 : begin seven_seg = 7'b0110000; end
            4'b0010 : begin seven_seg = 7'b1101101; end
            4'b0011 : begin seven_seg = 7'b1111001; end
            4'b0100 : begin seven_seg = 7'b0110011; end
            4'b0101 : begin seven_seg = 7'b1011011; end
            4'b0110 : begin seven_seg = 7'b1011111; end
            4'b0111 : begin seven_seg = 7'b1110000; end
            4'b1000 : begin seven_seg = 7'b1111111; end
            4'b1001 : begin seven_seg = 7'b1110011; end
            default : begin seven_seg = 7'b0000000; end
        endcase
    end
endmodule