module ex1(
  input ex_in1_scalar,
  input ex_in2_scalar,
  output ex_out_scalar,
  input [3:0] ex_in1_vector,
  input [3:0] ex_in2_vector,
  output [3:0] ex_out_vector
  );

  wire ex_wire1;
  wire [3:0] ex_wire2;

  assign ex_wire1 = ex_in1_scalar & ex_in2_scalar;
  assign ex_wire2 = ex_in1_vector & ex_in2_vector;

  assign ex_out_scalar = ~ ex_wire1;
  assign ex_out_vector = ~ ex_wire2;

endmodule
