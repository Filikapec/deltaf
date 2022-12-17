import tkinter as tk # pip install tk
import customtkinter # pip install customtkinter
import PIL.Image, PIL.ImageTk # pip install pillow

customtkinter.set_appearance_mode("dark")  # Modes: "System" (standard), "Dark", "Light"
customtkinter.set_default_color_theme("blue")  # Themes: "blue" (standard), "green", "dark-blue"

class App(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        # configure window
        self.title("Webcam with customtkinter and TK.Canvas")
        self.geometry('1100x580')

        # configure grid layout (4x4)
        self.grid_columnconfigure(1, weight=1)
        self.grid_columnconfigure((2, 3), weight=0)
        self.grid_rowconfigure((0, 1, 2), weight=1)

        # create sidebar frame with widgets
        self.sidebar_frame = customtkinter.CTkFrame(self, width=350, corner_radius=0)
        self.sidebar_frame.grid(row=0, column=0, rowspan=4, sticky="nsew")
        self.sidebar_frame.grid_rowconfigure(4, weight=1)
        self.logo_label = customtkinter.CTkLabel(self.sidebar_frame, text="Video Source", font=customtkinter.CTkFont(size=20, weight="bold"))
        self.logo_label.grid(row=0, column=0, padx=20, pady=(20, 10))

        # fill combobox with video devices
        self.combobox = customtkinter.CTkOptionMenu(self.sidebar_frame, command=self.optionmenu_callback)
        self.combobox.grid(row=1, column=0, padx=20, pady=(20, 10))

        # connect button
        self.sidebar_button_1 = customtkinter.CTkButton(self.sidebar_frame, text="Connect Camera")
        self.sidebar_button_1.grid(row=2, column=0, padx=20, pady=10)


    def optionmenu_callback(self, choice):
        pass

if __name__ == "__main__":
    app = App()
    app.mainloop()