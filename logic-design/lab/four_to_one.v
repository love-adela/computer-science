module mux_4to1_case ( 
  input [3:0] a,                 
  input [3:0] b,                 
  input [3:0] c,                 
  input [3:0] d,                 
  input [1:0] sel,               
  output reg [3:0] out);         
 
  always @ (a or b or c or d or sel) begin
     case (sel)
        2'b00 : out <= a;
        2'b01 : out <= b;
        2'b10 : out <= c;
        2'b11 : out <= d;
     endcase
  end
endmodule
 

module tb_4to1_mux ( 
  reg [3:0] a;      // 4-bit input called a
  reg [3:0] b;
  reg [3:0] c;
  reg [3:0] d;
  wire [3:0] out;
  reg [1:0] sel;
  integer i;

  mux_4to1_case  mux0 (   
    .a (a),
    .b (b),
    .c (c),
    .d (d),
    .sel (sel),
    .out (out)); 

  initial begin
    $monitor ("[%0t] sel=0x%0h a=0x%0h b=0x%0h b=0x%0h c=0x%0h out=0x%0h", 
endmodule
