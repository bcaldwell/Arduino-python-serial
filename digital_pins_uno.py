import tkinter as tk


counter = 0 
def counter_label(label):
  def count():
    global counter
    counter += 1
    label.config(text=str(counter))
    label.after(1000, count)
  print (label)
  count()

def click_one(newbuttonname):
	print (newbuttonname)

def change_state(pin):
	pin = pin [4:]
	print (pin)
	pin1.configure(highlightbackground="green")
 
 
root = tk.Tk()
root.title("Counting Seconds")
label = tk.Label(root, fg="green")
label.pack()
counter_label(label)
button = tk.Button(root, text=counter, width=25, bg = "red", command=root.destroy)
button.pack()

pin1 = tk.Button(root, text = "Pin 1", highlightbackground = "red", command = lambda: change_state(pin1.cget("text")))
pin1.pack()

root.mainloop()