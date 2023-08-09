module uart_clk_gen
(
    input sclk,
    input rst_n,
    output o_uart_clk
);

    reg [31:0] r_clk_cnt;
    reg r_uart_clk;

    always @(posedge sclk or negedge rst_n)
    begin
        if (!(rst_n))
            r_uart_clk = 1'b0;
        else
            if (r_clk_cnt == 32'd434)
                r_uart_clk = ~r_uart_clk;
    end

endmodule;