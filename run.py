"""
"""

import os
os.environ['path'] += r";.\bin;"
import tkinter as tk
from tkinter import *
from tkinter import ttk
from tkinter.filedialog import *
from ttkbootstrap import Style
import video_fs_detec
import pathlib
import sys

def get_exe_path():
    """
    返回可执行程序的当前路径。 sys.argv 中保存了可执行程序的全路径
    :return:
    """
    return os.path.split(os.path.realpath(sys.argv[0]))[0]

class MY_GUI():
    def __init__(self,root):
        self.m_root_win = root

        screen_width = self.m_root_win.winfo_screenwidth()
        screen_height = self.m_root_win.winfo_screenheight()
        win_width = screen_width/5
        win_height = screen_height/5

        size = '%dx%d+%d+%d' % (win_width, win_height, (screen_width - win_width) / 2, (screen_height - win_height) / 2)

        # self.m_root_win.wm_attributes('-topmost',1) # 窗口置顶
        # self.m_root_win.attributes("-toolwindow", 2) # 去掉最大最小框
        self.m_root_win.title("videoMosaic v1.0.0    @yingchengpa")    #窗口名
        self.m_root_win.geometry(size) #  
        # self.ft = tf.Font(family='微软雅黑')
        self.m_video_file = tk.StringVar()
        self.m_out_dir  = tk.StringVar()

        self.m_log = tk.StringVar()

    def init_window(self):
        self.labes_in_video = Label(self.m_root_win, text="打开视频", font=("微软雅黑",10))
        self.labes_in_video.grid(row=0,column=0,padx=5,pady=5)

        self.name_in_video = Entry(self.m_root_win,textvariable=self.m_video_file)  #原始数据录入框
        self.name_in_video.insert(0, '')
        self.name_in_video.grid(row=0, column=1,padx=5,pady=5)

        self.btn_in_video = Button(self.m_root_win, text="选择文件", bg="lightblue", width=10,command=self.button_click_open_file)  # 调用内部方法  加()为直接调用
        self.btn_in_video.grid(row=0, column=2,padx=5,pady=5)

        self.labes_out_video = Label(self.m_root_win, text="保存目录", font=("微软雅黑",10))
        self.labes_out_video.grid(row=1,column=0,padx=5,pady=5)

        self.name_out_video = Entry(self.m_root_win,textvariable=self.m_out_dir)  #原始数据录入框
        self.name_out_video.insert(0, '')
        self.name_out_video.grid(row=1, column=1,padx=5,pady=5)

        self.btn_out_video = Button(self.m_root_win, text="保存目录", bg="lightblue", width=10,command=self.button_click_dir)  # 调用内部方法  加()为直接调用
        self.btn_out_video.grid(row=1, column=2,padx=5,pady=5)

        self.btn_do = Button(self.m_root_win, text="开始", bg="lightblue", width=10,command=self.button_click_do)  # 调用内部方法  加()为直接调用
        self.btn_do.grid(row=2, column=1,padx=5,pady=5)

        self.progressbar = tk.ttk.Progressbar(self.m_root_win,length=200)
        self.progressbar.grid(row=3, column=1,padx=5,pady=5)

        self.lable_bar = Label(self.m_root_win, text="", font=("微软雅黑",10))
        self.lable_bar.grid(row=3, column=2,padx=5,pady=5)
        
        self.log_label = Label(self.m_root_win)  #原始数据录入框
        self.log_label.grid(row=4, columnspan=4,padx=5,pady=5)

        ret = video_fs_detec.init_libfc()
        if ret:
            self.log_label['text'] = 'init success'
        else:
            self.log_label['text'] = 'init fail'

    def button_click_dir(self):
        fileDir = askdirectory()
        if fileDir.strip() != '':
            self.m_out_dir.set(fileDir)
        else:
            self.m_out_dir.set('')

    def button_click_open_file(self):
        file_path = askopenfilename()
        if file_path.strip() != '':
            self.m_video_file.set(file_path)
        else:
            self.m_video_file.set('')

    def button_click_do(self):
        if self.m_out_dir == '' or self.m_video_file == '':
            return 

        # 初始化变量
        video_fs_detec.init_libfc()

        fs = video_fs_detec.video_fs(self.m_video_file.get())

         # 初始化进度条
        self.progressbar['value'] = 0
        # 设置进度条的最大值
        self.progressbar['maximum'] = fs.get_total_frame()

        p = pathlib.Path(self.m_video_file.get())
        out_put = f'{self.m_out_dir.get()}\{p.stem}_new{p.suffix}'
        fs.video_fs(out_put,self.video_callback)

    def video_callback(self,current_frame,total_frame):
        self.progressbar['value'] = current_frame
        self.lable_bar['text'] = f'{round(current_frame*100/total_frame)}%'
        self.m_root_win.update()
                    
    
if __name__ == "__main__":
    style = Style() 
    root_win = style.master
    my_gui = MY_GUI(root_win)
    my_gui.init_window()
    root_win.mainloop()