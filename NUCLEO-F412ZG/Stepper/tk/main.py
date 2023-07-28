import tkinter

class Main:
    def __init__(self):
        self.root = tkinter.Tk()
    
        lbl = tkinter.Label(self.root, text = "Send UART Message")
        btn = tkinter.Button(self.root, text = "Send", command = self.btn_callback)
        lbl.grid(row = 0, column = 0)
        btn.grid(row = 0, column = 1)

    def run(self):
        self.root.mainloop()

    def btn_callback(self):
        print("Callback")

if __name__ == "__main__":
    main = Main()
    main.run()
