import tkinter as tk # pip install tk
import customtkinter # pip install customtkinter
import PIL.Image, PIL.ImageTk # pip install pillow
import cv2 # pip install opencv-python
from pygrabber.dshow_graph import FilterGraph # pip install pygrabber
import numpy as np

customtkinter.set_appearance_mode("dark")  # Modes: "System" (standard), "Dark", "Light"
customtkinter.set_default_color_theme("blue")  # Themes: "blue" (standard), "green", "dark-blue"

class App(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        # configure window
        self.title("DELTA F Kontrola")
        self.geometry("1100x580")

        # configure grid layout (4x4)
        self.grid_columnconfigure(1, weight=1)
        self.grid_columnconfigure((2, 3), weight=0)
        self.grid_rowconfigure((0, 1, 2), weight=1)

        # create sidebar frame with widgets
        self.sidebar_frame = customtkinter.CTkFrame(self, width=350, corner_radius=0)
        self.sidebar_frame.grid(row=0, column=0, rowspan=4, sticky="nsew")
        self.sidebar_frame.grid_rowconfigure(4, weight=1)
        self.logo_label = customtkinter.CTkLabel(self.sidebar_frame, text="DELTA F", font=customtkinter.CTkFont(size=20, weight="bold"))
        self.logo_label.grid(row=0, column=0, padx=20, pady=(20, 10))

        #get the available video devices
        self.graph = FilterGraph()
 
        # fill combobox with availible video devices
        self.combobox = customtkinter.CTkOptionMenu(self.sidebar_frame, values=self.graph.get_input_devices())
        self.combobox.grid(row=1, column=0, padx=20, pady=(20, 10))

        # connect button
        self.sidebar_button_1 = customtkinter.CTkButton(self.sidebar_frame, text="Connect Camera", command=self.sidebar_button_event)
        self.sidebar_button_1.grid(row=2, column=0, padx=20, pady=10)

        self.tabview = customtkinter.CTkTabview(self, width=250)
        self.tabview.grid(row=0, column=2, padx=(20, 0), pady=(20, 0), sticky="nsew")
        self.tabview.add("Stani/Kreni")
        self.tabview.add("Objekt 1")
        self.tabview.add("Objekt 2")
        self.tabview.tab("Stani/Kreni").grid_columnconfigure(0, weight=1)  # configure grid of individual tabs
        self.tabview.tab("Objekt 1").grid_columnconfigure(0, weight=1)
        self.slider_progressbar_frame = customtkinter.CTkFrame(self.tabview.tab("Objekt 1"), fg_color="transparent")
        self.slider_progressbar_frame.grid(row=1, column=1, columnspan=2, padx=(20, 0), pady=(20, 0), sticky="nsew")
        self.slider_progressbar_frame.grid_columnconfigure(0, weight=1)
        self.slider_progressbar_frame.grid_rowconfigure(4, weight=1)
        #HSV1
        self.labelH1 = customtkinter.CTkLabel(self.slider_progressbar_frame, text="Hue")
        self.labelH1.grid(row=0, column=0, padx=(0,0), pady=(0, 0), sticky="nw")
        self.slider_1 = customtkinter.CTkSlider(self.slider_progressbar_frame, from_=0, to=180, number_of_steps=180)
        self.slider_1.grid(row=1, column=0, padx=(0, 0), pady=(10, 10), sticky="ew")
        self.labelS1 = customtkinter.CTkLabel(self.slider_progressbar_frame, text="Saturation")
        self.labelS1.grid(row=3, column=0, padx=(0,0), pady=(0, 0), sticky="nw")
        self.slider_2 = customtkinter.CTkSlider(self.slider_progressbar_frame, from_=0, to=255, number_of_steps=180)
        self.slider_2.grid(row=4, column=0, padx=(20, 10), pady=(10, 10), sticky="ew")
        self.labelV1 = customtkinter.CTkLabel(self.slider_progressbar_frame, text="Value")
        self.labelV1.grid(row=6, column=0, padx=(0,0), pady=(0, 0), sticky="nw")
        self.slider_3 = customtkinter.CTkSlider(self.slider_progressbar_frame, from_=0, to=255, number_of_steps=180)
        self.slider_3.grid(row=7, column=0, padx=(20, 10), pady=(10, 10), sticky="ew")
        #HSV2
        self.slider_4 = customtkinter.CTkSlider(self.slider_progressbar_frame, from_=0, to=180, number_of_steps=180)
        self.slider_4.grid(row=2, column=0, padx=(0, 0), pady=(10, 10), sticky="ew")
        self.slider_5 = customtkinter.CTkSlider(self.slider_progressbar_frame, from_=0, to=255, number_of_steps=180)
        self.slider_5.grid(row=5, column=0, padx=(20, 10), pady=(10, 10), sticky="ew")
        self.slider_6 = customtkinter.CTkSlider(self.slider_progressbar_frame, from_=0, to=255, number_of_steps=180)
        self.slider_6.grid(row=8, column=0, padx=(20, 10), pady=(10, 10), sticky="ew")

        self.scaling_label = customtkinter.CTkLabel(self.sidebar_frame, text="UI Scaling:", anchor="w")
        self.scaling_label.grid(row=7, column=0, padx=20, pady=(10, 0))
        self.scaling_optionemenu = customtkinter.CTkOptionMenu(self.sidebar_frame, values=["80%", "90%", "100%", "110%", "120%"], command=self.change_scaling_event)
        self.scaling_optionemenu.grid(row=8, column=0, padx=20, pady=(10, 20))

    def klizac(self, stagod):
        value = self.slider_1.get()
        print(self.slider_1.get())

    
    def change_scaling_event(self, new_scaling: str):
        new_scaling_float = int(new_scaling.replace("%", "")) / 100
        customtkinter.set_widget_scaling(new_scaling_float)

    def sidebar_button_event(self):
        print("try to open camera: " + self.combobox.get())   

        for i, device in enumerate(self.graph.get_input_devices() ):   
            if device == self.combobox.get():
                self.video_source = i

        # main window
        self.vid = MyVideoCapture(self.video_source)

        # Create a canvas that can fit the above video source size
        self.canvas = tk.Canvas(self, width=250, height = self.vid.height)  #width = self.vid.width
        self.canvas.grid(row=0, column=1, padx=(20, 0), pady=(20, 0), sticky="nsew")

        self.delay = 15
        self.update()        


    # Get a frame from the video source
    def update(self):        
        return_value, frame = self.vid.get_frame()        

        if return_value:
            try:
                #analyze Frame and check for QR Code
                frame = self.analyzeFrame(frame)
                
                self.photo = PIL.ImageTk.PhotoImage(image = PIL.Image.fromarray(frame))
                self.canvas.create_image(0, 0, image = self.photo, anchor = tk.NW)

            except BaseException:
                    '''import sys
                    print(sys.exc_info()[0])
                    import traceback
                    print(traceback.format_exc())  '''
            finally:
                pass

        self.after(self.delay, self.update)

    #search for QR Code in frame
    def analyzeFrame(self, frame):
        font = cv2.FONT_HERSHEY_SIMPLEX
        img = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        #lower = np.array([0, 0, 0])
        lower = np.array([self.slider_1.get(), self.slider_2.get(), self.slider_3.get()])
        #upper = np.array([180, 115, 102])
        upper = np.array([self.slider_4.get(), self.slider_5.get(), self.slider_6.get()])
        mask = cv2.inRange(img, lower, upper)

        mask_contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        if len(mask_contours) != 0:
            for mask_contour in mask_contours:
                if cv2.contourArea(mask_contour) > 500:
                    x, y, w, h = cv2.boundingRect(mask_contour)
                    wpixprenos = w
                    hpixprenos = h
                    cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3) #drawing rectangle
                    cv2.circle(frame, (int(x+w/2), int(y+h/2)), 15, (50,255, 20))
        return frame


class MyVideoCapture:
    def __init__(self, video_source=0):
        # Open the video source
        self.vid = cv2.VideoCapture(video_source)
        if not self.vid.isOpened():
            raise ValueError("Unable to open video source", video_source)

        # Get video source width and height
        self.width = self.vid.get(cv2.CAP_PROP_FRAME_WIDTH)
        self.height = self.vid.get(cv2.CAP_PROP_FRAME_HEIGHT)

    def get_frame(self):
        if not self.vid.isOpened():
            return (return_value, None)

        return_value, frame = self.vid.read()
        if return_value:
            # Return a boolean success flag and the current frame converted to BGR
            return (return_value, cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
        else:
            return (return_value, None)

    # Release the video source when the object is destroyed
    def __del__(self):
        if self.vid.isOpened():
            self.vid.release()


if __name__ == "__main__":
    app = App()
    app.mainloop()