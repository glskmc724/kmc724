import tkinter
import serial

class Main:
    def __init__(self):
        self.root = tkinter.Tk()
        self.uart = serial.Serial("/dev/ttyACM0", 115200)
        
        lbl = tkinter.Label(self.root, text = "Send UART Message")
        btn = tkinter.Button(self.root, text = "Send", command = self.btn_callback)
        lbl.grid(row = 0, column = 0)
        vcmd = self.root.register(self.entry_validate)
        self.ent = tkinter.Entry(self.root, validate = "all", validatecommand = (vcmd, "%P"))
        self.ent.grid(row = 1, column = 0)
        btn.grid(row = 1, column = 1)

    def run(self):
        self.root.mainloop()

    def btn_callback(self):
        if (self.ent.get() != ""):
            rot = self.ent.get()
            send = [0x07, 0x00, int(rot), 0x24]
            self.uart.write(send)

    def entry_validate(self, i):
        if str.isdigit(i) or i == "":
            return True
        else:
            return False

if __name__ == "__main__":
    main = Main()
    main.run()
