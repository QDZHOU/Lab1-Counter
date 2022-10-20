#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    int i;
    int clk;
    int num = 0;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 1);
    tfp->open("counter.vcd");

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->en = 1;
    top->count;

    //run simulation for mant clock cycles
    for (i  = 0; i < 300; i++){

    for (clk = 0; clk < 2; clk++){
        tfp->dump (2*i+clk);//unit is in ps!!
        top->clk = !top->clk;
        top->eval();
    }
    //top->rst = (i<2)|(i==15);
    //top->en = (i>4);

    if(top->count == 9){
        num++;
        if(num<=3){
            top->en = 0;
        }else{
            top->en =1;
            num = 0;
            top->count = 0;
        }
    }
    if(Verilated::gotFinish()) exit(0);
  }
  tfp->close();
  exit(0);
}
