module uart
(
    input sclk,
    input rst_n,
    input i_uart_rx,
    output o_uart_tx,
    output [7:0] o8_uart_state,
    output [7:0] o8_next_state,
    output [7:0] o8_data_cnt,
    output [7:0] o8_data,
    output [31:0] o32_sclk_cnt
);

    uart_rx uart_rx(
        .sclk(sclk),
        .rst_n(rst_n),
        .i_uart_rx(i_uart_rx),
        .o8_uart_state(o8_uart_state),
        .o8_next_state(o8_next_state),
        .o8_data_cnt(o8_data_cnt),
        .o8_data(o8_data),
        .o32_sclk_cnt(o32_sclk_cnt)
    );
    
endmodule;