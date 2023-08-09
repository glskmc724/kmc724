module uart_rx
(
    input sclk,
    input rst_n,
    input i_uart_rx,
    output [7:0] o8_uart_state,
    output [7:0] o8_next_state,
    output [7:0] o8_data_cnt,
    output [7:0] o8_data,
    output [31:0] o32_sclk_cnt
);
    
    parameter BUS_IDLE = 8'd0,
                START_BIT = 8'd1,
                DATA_BITS = 8'd2,
                STOP_BIT = 8'd3;
                
    reg [7:0] r8_uart_state;
    reg [7:0] r8_next_state;
    reg [7:0] r8_data_cnt;
    reg [7:0] r8_data;
    reg [31:0] r32_sclk_cnt;
    
    assign o8_uart_state = r8_uart_state;
    assign o8_next_state = r8_next_state;
    assign o8_data_cnt = r8_data_cnt;
    assign o8_data = r8_data;
    assign o32_sclk_cnt = r32_sclk_cnt;
    
    always @(posedge sclk or negedge rst_n)
    begin
        if (!(rst_n))
        begin
            r8_uart_state <= BUS_IDLE;
            r8_data <= 8'd0;
        end
        else
        begin
            r8_uart_state <= r8_next_state;
            
            if (r8_uart_state == BUS_IDLE && r8_next_state == BUS_IDLE)
            begin
                r8_data <= 8'd0;
            end
            else if (r8_uart_state == BUS_IDLE && r8_next_state == START_BIT)
            begin
                r8_data <= 8'd0;
            end
            else if (r8_uart_state == START_BIT && r8_next_state == DATA_BITS)
            begin
                r8_data <= 8'd0;
            end
            else if (r8_uart_state == DATA_BITS && r8_next_state == DATA_BITS)
            begin
                if (i_uart_rx == 1'b1 && r32_sclk_cnt < 8'd5)
                begin
                    r8_data <= r8_data | (1'b1 << r8_data_cnt);
                end
            end
            else if (r8_uart_state == DATA_BITS && r8_next_state == STOP_BIT)
            begin
                r8_data <= 8'd0;
            end
            else if (r8_uart_state == STOP_BIT && r8_next_state == BUS_IDLE)
            begin
                r8_data <= 8'd0;
            end
            else
            begin
                r8_data <= 8'd0;
            end
        end
    end
    
    always @(posedge sclk or negedge rst_n)
    begin
        if (!(rst_n))
        begin
            r8_next_state <= BUS_IDLE;
            r8_data_cnt <= 8'd0;
            r32_sclk_cnt = 32'd0;
        end
        else
        begin
            case (r8_uart_state)
                BUS_IDLE:
                begin
                    if (i_uart_rx == 1'b0)
                    begin
                        r8_next_state <= START_BIT;
                        r8_data_cnt <= 8'd0;
                        r32_sclk_cnt <= 1'b0;
                    end
                end             
                START_BIT:
                begin
                    r32_sclk_cnt <= r32_sclk_cnt + 1'b1;
                    
                    if (r32_sclk_cnt == 32'd865)
                    begin
                        r8_next_state <= DATA_BITS;
                        r8_data_cnt <= 8'd0;
                        r32_sclk_cnt <= 32'd0;
                    end                 
                end
                DATA_BITS:
                begin
                    r32_sclk_cnt <= r32_sclk_cnt + 1'b1;
                                        
                    if (r32_sclk_cnt == 32'd867)
                    begin
                        r8_data_cnt <= r8_data_cnt + 1'b1;
                        r32_sclk_cnt <= 32'd0;
                    end

                    if (r8_data_cnt != 8'd8)
                    begin
                        r8_next_state <= DATA_BITS;
                    end
                    else
                    begin
                        r8_next_state <= STOP_BIT;
                    end
                    
                end
                STOP_BIT:
                begin
                    r8_next_state <= BUS_IDLE;
                    r8_data_cnt <= 8'd0;
                end
            endcase             
        end
    end

endmodule;